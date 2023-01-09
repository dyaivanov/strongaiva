#include "YoloDetector.h"
#include <fstream>

YoloDetector::YoloDetector(bool _use_CUDA, int _cnt_classes, const string &_cfg, const string &_weights, const string &_names,
                           double _min_confidences, int _min_size, int _max_size, bool _greedy, bool _draw_text, const vector<cv::Scalar> &_color)
{
    m_use_CUDA = _use_CUDA;
    m_NUM_CLASSES = _cnt_classes;
    m_min_confidences = _min_confidences;
    m_MIN_SIZE = _min_size;
    m_MAX_SIZE = _max_size;
    m_GREEDY = _greedy;
    m_draw_text = _draw_text;
    for(int i=0; i<_color.size(); i++)
        mColors.push_back(_color[i]);

    darknet = cv::dnn::readNetFromDarknet(_cfg, _weights);

    if(m_use_CUDA)
    {
        darknet.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        darknet.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    }
    else
    {
        darknet.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        darknet.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }

    output_names = darknet.getUnconnectedOutLayersNames();

    std::ifstream class_file(_names);
    if (!class_file)
    {
        std::cerr << "failed to open obj.names\n";
        //            return 0;
    }

    std::string line;
    while (std::getline(class_file, line)) {
        class_names.push_back(line);
        classes.append(QString::fromStdString(line));
    }

}

void YoloDetector::drawBoxes(cv::Mat &frame)
{
    //27.04.2022
    int n = confidences.size();
    for(int i=0; i<n; i++)
    {
        if(confidences[i] > m_min_confidences) //good quality
        if(boxes[i].width > m_MIN_SIZE && boxes[i].width < m_MAX_SIZE && boxes[i].height > m_MIN_SIZE && boxes[i].height < m_MAX_SIZE) //size ok
        {
            int classIndex = idx[i];

            cv::Scalar color = mColors[classIndex]; //05.05.2022

            //05.05.2022 text
            if(m_draw_text)
                {
                char str[50];
                sprintf(str, "%s=%.1f", class_names[classIndex].c_str(), confidences[i]);
                putText(frame, str, Point(boxes[i].x, boxes[i].y-7), FONT_HERSHEY_SIMPLEX, 0.5, color, 1);
                }

            //27.04.2022
            //printf("conf = %.1f\n", confidences[i]);
            cv::rectangle(frame, boxes[i], color, 2);
        }
    }
}

void YoloDetector::getRects(vector<cv::Rect> &_v_out) //26.05.2022
{
    int n = confidences.size();
    for(int i=0; i<n; i++)
    {
        if(confidences[i] > m_min_confidences) //good quality
        if(boxes[i].width > m_MIN_SIZE && boxes[i].width < m_MAX_SIZE && boxes[i].height > m_MIN_SIZE && boxes[i].height < m_MAX_SIZE) //size ok
        {
           // int classIndex = idx[i];
            _v_out.push_back(boxes[i]);
        }
    }
}

bool YoloDetector::ClassIdInFrame(int _id) //27.09.2022
{
    int n = confidences.size();
    for(int i=0; i<n; i++)
    {
        if(confidences[i] > m_min_confidences) //good quality
        if(boxes[i].width > m_MIN_SIZE && boxes[i].width < m_MAX_SIZE && boxes[i].height > m_MIN_SIZE && boxes[i].height < m_MAX_SIZE) //size ok
        {
           // int classIndex = idx[i];
           if(_id == idx[i])
               return true;
        }
    }

    return false;
}

bool YoloDetector::getMaxRect(Rect &_r_out) //26.05.2022
{
    _r_out.width = 0;

    int n = confidences.size();
    for(int i=0; i<n; i++)
    {
        if(confidences[i] > m_min_confidences) //good quality
        if(boxes[i].width > m_MIN_SIZE && boxes[i].width < m_MAX_SIZE && boxes[i].height > m_MIN_SIZE && boxes[i].height < m_MAX_SIZE) //size ok
        {
           // int classIndex = idx[i];
           // _v_out.push_back(boxes[i]);
            if(boxes[i].width > _r_out.width)
                _r_out = boxes[i];
        }
    }

    if(_r_out.width == 0)
        return false;
    return true;
}

void YoloDetector::detect(const Mat &frame)
{
    std::vector<cv::Mat> detections;
//    cv::dnn::blobFromImage(frame, blob, 0.00392, cv::Size(608, 608), cv::Scalar(), true, false, CV_32F);
    cv::dnn::blobFromImage(frame, blob, 1.0 / 255, cv::Size(416, 416), cv::Scalar(), true, false, CV_32F);

    darknet.setInput(blob);
    darknet.forward(detections, output_names);

    std::vector<int> indices[MAX_NUM_CLASSES];
    std::vector<cv::Rect> tboxes[MAX_NUM_CLASSES];
    std::vector<float> scores[MAX_NUM_CLASSES];

    for (auto& output : detections)
    {
        const auto num_boxes = output.rows;
        for (int i = 0; i < num_boxes; i++)
        {
            auto x = output.at<float>(i, 0) * frame.cols;
            auto y = output.at<float>(i, 1) * frame.rows;
            auto width = output.at<float>(i, 2) * frame.cols;
            auto height = output.at<float>(i, 3) * frame.rows;
            cv::Rect rect(x - width/2, y - height/2, width, height);

            for (int c = 0; c < m_NUM_CLASSES; c++)
            {
                auto confidence = *output.ptr<float>(i, 5 + c);
//                if (confidence > 0) qDebug() << confidence;
                if (confidence >= CONFIDENCE_THRESHOLD)
                {
                    tboxes[c].push_back(rect);
                    scores[c].push_back(confidence);
                }
            }
        }
    }

    for (int c = 0; c < m_NUM_CLASSES; c++)
        cv::dnn::NMSBoxes(tboxes[c], scores[c], 0.0, NMS_THRESHOLD, indices[c]);

    confidences.clear(); //!!! 27.04.2022
    boxes.clear();
    idx.clear();

    for (int c = 0; c < m_NUM_CLASSES; c++)
    {
        for (size_t i = 0; i < indices[c].size(); ++i)
        {
//            const auto color = cv::Scalar(255, 0, 0);

            auto id = indices[c][i];
//            qDebug() << id;
            const auto& rect = tboxes[c][id];
            float conf = scores[c][id];

            confidences.append(conf);
            boxes.append(rect);
            idx.append(c);
        }
    }

}

