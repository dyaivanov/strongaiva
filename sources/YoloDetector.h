#ifndef YOLODETECTOR_H
#define YOLODETECTOR_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

constexpr float CONFIDENCE_THRESHOLD = 0.2;
constexpr float NMS_THRESHOLD = 0.4;
constexpr int MAX_NUM_CLASSES = 10;

class YoloDetector
{
private:
    cv::dnn::Net darknet;
    Mat blob;
    vector<cv::String> output_names;

    vector<string> class_names;

    QList<cv::Rect> boxes;
    QList<int> idx;
    QList<QString> classes;
    QList<float> confidences;

    bool m_use_CUDA;
    int m_NUM_CLASSES;
    double m_min_confidences;
    int m_MIN_SIZE;
    int m_MAX_SIZE;
    bool m_GREEDY;
    bool m_draw_text;
    vector<cv::Scalar> mColors;


public:
    YoloDetector(bool _use_CUDA, int _cnt_classes, const string &_cfg, const string &_weights, const string &_names, double _min_confidences, int _min_size, int _max_size, bool _greedy, bool _draw_text, const vector<cv::Scalar> &_color);
    void drawBoxes(Mat &_frame);
    void detect(const Mat &_frame);
    void getRects(vector<cv::Rect> &_v_out); //26.05.2022
    bool ClassIdInFrame(int _id); //27.09.2022
    bool getMaxRect(Rect &_r_out); //26.05.2022
};

#endif // YOLODETECTOR_H
