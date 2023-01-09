#include "PoseProcessor.h"

//#define OPENPOSE_FLAGS_DISABLE_PRODUCER
//#define OPENPOSE_FLAGS_DISABLE_DISPLAY
#include <openpose/flags.hpp> //21.07.2022

PoseProcessor:: PoseProcessor(int _iUSE_ANALIZE_FACES, //28.09.2022
                              double _fMIN_QUANT_SKELETON, int _iMIN_SIZE_SKELETON, int _iMAX_SIZE_SKELETON, int _iDRAW_SKELETONS,
                              int _iUSE_ANALIZE_HANDS_UP, cv::Scalar _scCOLOR_HANDS_UP,
                              int _iUSE_ANALIZE_HEAD_NOT_VISIBLE, cv::Scalar _scCOLOR_HEAD_NOT_VISIBLE,
                              int _iUSE_ANALIZE_BODY_LYING, cv::Scalar _scCOLOR_BODY_LYING,
                              int _iUSE_ANALIZE_FIGHT, int _iFIGHT_HIT_HAND_TO_FACE, int _iFIGHT_HIT_FOOT_TO_FACE, int _iFIGHT_HIT_FOOT2_TO_FACE, int _iFIGHT_HIT_FOOT_TO_PELVIS, cv::Scalar _scCOLOR_FIGHT)
{
    //27.09.2022
    m_bHandsUp = false;
    m_bHeadNotVisible = false;
    m_bBodyLying = false;
    m_bFight = false;

    //31.07.2022
    m_im_width = 0;
    m_im_height = 0;

    //06.05.2022
    m_fMIN_QUANT_SKELETON = _fMIN_QUANT_SKELETON;
    m_iMIN_SIZE_SKELETON = _iMIN_SIZE_SKELETON;
    m_iMAX_SIZE_SKELETON = _iMAX_SIZE_SKELETON;
    m_iDRAW_SKELETONS = _iDRAW_SKELETONS;

    m_iUSE_ANALIZE_HANDS_UP = _iUSE_ANALIZE_HANDS_UP;
    m_scCOLOR_HANDS_UP = _scCOLOR_HANDS_UP;

    m_iUSE_ANALIZE_HEAD_NOT_VISIBLE = _iUSE_ANALIZE_HEAD_NOT_VISIBLE;
    m_scCOLOR_HEAD_NOT_VISIBLE = _scCOLOR_HEAD_NOT_VISIBLE;

    m_iUSE_ANALIZE_BODY_LYING = _iUSE_ANALIZE_BODY_LYING;
    m_scCOLOR_BODY_LYING = _scCOLOR_BODY_LYING;

    m_iUSE_ANALIZE_FIGHT = _iUSE_ANALIZE_FIGHT;
    m_iFIGHT_HIT_HAND_TO_FACE = _iFIGHT_HIT_HAND_TO_FACE;
    m_iFIGHT_HIT_FOOT_TO_FACE = _iFIGHT_HIT_FOOT_TO_FACE;
    m_iFIGHT_HIT_FOOT2_TO_FACE = _iFIGHT_HIT_FOOT2_TO_FACE;
    m_iFIGHT_HIT_FOOT_TO_PELVIS = _iFIGHT_HIT_FOOT_TO_PELVIS;
    m_scCOLOR_FIGHT = _scCOLOR_FIGHT;


    // opWrapper.disableMultiThreading();

    configureWrapper(opWrapper, _iUSE_ANALIZE_FACES); //28.02.2022 //29.09.2022
    opWrapper.start();

//    QObject::connect(this, SIGNAL(sendGraphData(double, int)), MainWindow::debugGraph, SLOT(onAppendData(double, int)));


//    QFile file("table.txt");
//    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
//        // We're going to streaming text to the file
//        QTextStream stream(&file);

//        stream << "Расстояние до камеры\t"
//                  "Лев. кисть-локоть\tЛев. локоть-плечо\tЛев. плечо-таз\tЛев.таз-колено"
//                  "\tПрав. кисть-локоть\tПрав. локоть-плечо\tПрав. плечо-таз\tПрав.таз-колено"
//                  "\tЛев. плечо-Прав. плечо";

//        file.close();
//    }
}

void PoseProcessor::configureWrapper(op::Wrapper& opWrapper, int _iUSE_ANALIZE_FACES) //28.02.2022 //29.09.2022
{
    //FLAGS_camera_resolution = "800x600";

    //FLAGS_body = 1;
    FLAGS_net_resolution = "-1x224"; //"-1x224"; //21.07.2022
    //FLAGS_number_people_max = 1; //01.08.2022


    //FLAGS_face_net_resolution = "128x128"; //26.07.2022
    FLAGS_face_net_resolution = "320x320"; //368x368
    if(_iUSE_ANALIZE_FACES == 1) //29.09.2022
        FLAGS_face = true;
    else
        FLAGS_face = false;
    //FLAGS_face_detector = 0;

    FLAGS_hand_net_resolution = "320x320"; //"224x224"; //"128x128"; //26.07.2022
    FLAGS_hand = false;
    //FLAGS_hand_detector = 0;

    FLAGS_num_gpu = -1; //07.10.2022

    // Configuring OpenPose

            // logging_level
            op::checkBool(
                0 <= FLAGS_logging_level && FLAGS_logging_level <= 255, "Wrong logging_level value.",
                __LINE__, __FUNCTION__, __FILE__);
            op::ConfigureLog::setPriorityThreshold((op::Priority)FLAGS_logging_level);
            op::Profiler::setDefaultX(FLAGS_profile_speed);

            // Applying user defined configuration - GFlags to program variables
            // producerType
            op::ProducerType producerType;
            op::String producerString;
            std::tie(producerType, producerString) = op::flagsToProducer(
                op::String(FLAGS_image_dir), op::String(FLAGS_video), op::String(FLAGS_ip_camera), FLAGS_camera,
                FLAGS_flir_camera, FLAGS_flir_camera_index);
            // cameraSize
            const auto cameraSize = op::flagsToPoint(op::String(FLAGS_camera_resolution), "-1x-1");
            // outputSize
            const auto outputSize = op::flagsToPoint(op::String(FLAGS_output_resolution), "-1x-1");
            // netInputSize
            const auto netInputSize = op::flagsToPoint(op::String(FLAGS_net_resolution), "-1x128"); //368"); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // faceNetInputSize
            const auto faceNetInputSize = op::flagsToPoint(op::String(FLAGS_face_net_resolution), "368x368 (multiples of 16)");
            // handNetInputSize
            const auto handNetInputSize = op::flagsToPoint(op::String(FLAGS_hand_net_resolution), "368x368 (multiples of 16)");
            // poseMode
            const auto poseMode = op::flagsToPoseMode(FLAGS_body);
            // poseModel
            const auto poseModel = op::flagsToPoseModel(op::String(FLAGS_model_pose));
            // JSON saving
            if (!FLAGS_write_keypoint.empty())
                op::opLog(
                    "Flag `write_keypoint` is deprecated and will eventually be removed. Please, use `write_json`"
                    " instead.", op::Priority::Max);
            // keypointScaleMode
            const auto keypointScaleMode = op::flagsToScaleMode(FLAGS_keypoint_scale);
            // heatmaps to add
            const auto heatMapTypes = op::flagsToHeatMaps(FLAGS_heatmaps_add_parts, FLAGS_heatmaps_add_bkg,
                                                          FLAGS_heatmaps_add_PAFs);
            const auto heatMapScaleMode = op::flagsToHeatMapScaleMode(FLAGS_heatmaps_scale);
            // >1 camera view?
            const auto multipleView = (FLAGS_3d || FLAGS_3d_views > 1 || FLAGS_flir_camera);
            // Face and hand detectors
            const auto faceDetector = op::flagsToDetector(FLAGS_face_detector);
            const auto handDetector = op::flagsToDetector(FLAGS_hand_detector);

            //FLAGS_num_gpu = -1;
            //printf("___ %s\n", FLAGS_face_net_resolution.c_str()); //---
            //printf("___ %d\n", faceNetInputSize); //---


            // Enabling Google Logging
            const bool enableGoogleLogging = true;

            // Pose configuration (use WrapperStructPose{} for default and recommended configuration)
            //27.12.2022
            const op::WrapperStructPose wrapperStructPose{
                poseMode, netInputSize, /*FLAGS_net_resolution_dynamic,*/ outputSize, keypointScaleMode, FLAGS_num_gpu,
                FLAGS_num_gpu_start, FLAGS_scale_number, (float)FLAGS_scale_gap,
                op::flagsToRenderMode(FLAGS_render_pose, multipleView), poseModel, !FLAGS_disable_blending,
                (float)FLAGS_alpha_pose, (float)FLAGS_alpha_heatmap, FLAGS_part_to_show, op::String(FLAGS_model_folder),
                heatMapTypes, heatMapScaleMode, FLAGS_part_candidates, (float)FLAGS_render_threshold,
                FLAGS_number_people_max, FLAGS_maximize_positives, FLAGS_fps_max, op::String(FLAGS_prototxt_path),
                op::String(FLAGS_caffemodel_path), (float)FLAGS_upsampling_ratio, enableGoogleLogging};
            opWrapper.configure(wrapperStructPose);


            //25.07.2022 face
            // Face configuration (use op::WrapperStructFace{} to disable it)
               const op::WrapperStructFace wrapperStructFace{
                   FLAGS_face, faceDetector, faceNetInputSize,
                   op::flagsToRenderMode(FLAGS_face_render, multipleView, FLAGS_render_pose),
                   (float)FLAGS_face_alpha_pose, (float)FLAGS_face_alpha_heatmap, (float)FLAGS_face_render_threshold};
               opWrapper.configure(wrapperStructFace); //!!!!!!!!!!!!!!!!!!!!!!

            //25.07.2022 hands
            const op::WrapperStructHand wrapperStructHand{
                FLAGS_hand, handDetector, handNetInputSize, FLAGS_hand_scale_number, (float)FLAGS_hand_scale_range,
                op::flagsToRenderMode(FLAGS_hand_render, multipleView, FLAGS_render_pose), (float)FLAGS_hand_alpha_pose,
                (float)FLAGS_hand_alpha_heatmap, (float)FLAGS_hand_render_threshold};
            opWrapper.configure(wrapperStructHand); //!!!!!!!!!!!!!!!!!!!!!!

//            // Face configuration (use op::WrapperStructFace{} to disable it)
//            const op::WrapperStructFace wrapperStructFace{
//                FLAGS_face, faceDetector, faceNetInputSize,
//                op::flagsToRenderMode(FLAGS_face_render, multipleView, FLAGS_render_pose),
//                (float)FLAGS_face_alpha_pose, (float)FLAGS_face_alpha_heatmap, (float)FLAGS_face_render_threshold};
//            opWrapper.configure(wrapperStructFace); //!!!!!!!!!!!!!!!!!!!!!!
//            // Hand configuration (use op::WrapperStructHand{} to disable it)
//            const op::WrapperStructHand wrapperStructHand{};/*
//                FLAGS_hand, handDetector, handNetInputSize, FLAGS_hand_scale_number, (float)FLAGS_hand_scale_range,
//                op::flagsToRenderMode(FLAGS_hand_render, multipleView, FLAGS_render_pose), (float)FLAGS_hand_alpha_pose,
//                (float)FLAGS_hand_alpha_heatmap, (float)FLAGS_hand_render_threshold};*/
//            opWrapper.configure(wrapperStructHand); //!!!!!!!!!!!!!!!!!!!!!!
//            // Extra functionality configuration (use op::WrapperStructExtra{} to disable it)
//            const op::WrapperStructExtra wrapperStructExtra{};/*
//                FLAGS_3d, FLAGS_3d_min_views, FLAGS_identification, FLAGS_tracking, FLAGS_ik_threads};*/
//            opWrapper.configure(wrapperStructExtra);
//            // Producer (use default to disable any input)
//            const op::WrapperStructInput wrapperStructInput{
//                producerType, producerString, FLAGS_frame_first, FLAGS_frame_step, FLAGS_frame_last,
//                FLAGS_process_real_time, FLAGS_frame_flip, FLAGS_frame_rotate, FLAGS_frames_repeat,
//                cameraSize, op::String(FLAGS_camera_parameter_path), FLAGS_frame_undistort, FLAGS_3d_views};
//            opWrapper.configure(wrapperStructInput);
//            // Output (comment or use default argument to disable any output)
//            const op::WrapperStructOutput wrapperStructOutput{};/*
//                FLAGS_cli_verbose, op::String(FLAGS_write_keypoint), op::stringToDataFormat(FLAGS_write_keypoint_format),
//                op::String(FLAGS_write_json), op::String(FLAGS_write_coco_json), FLAGS_write_coco_json_variants,
//                FLAGS_write_coco_json_variant, op::String(FLAGS_write_images), op::String(FLAGS_write_images_format),
//                op::String(FLAGS_write_video), FLAGS_write_video_fps, FLAGS_write_video_with_audio,
//                op::String(FLAGS_write_heatmaps), op::String(FLAGS_write_heatmaps_format), op::String(FLAGS_write_video_3d),
//                op::String(FLAGS_write_video_adam), op::String(FLAGS_write_bvh), op::String(FLAGS_udp_host),
//                op::String(FLAGS_udp_port)};*/
//            opWrapper.configure(wrapperStructOutput);
//            // GUI (comment or use default argument to disable any visual output)
//            const op::WrapperStructGui wrapperStructGui{
//                op::flagsToDisplayMode(FLAGS_display, FLAGS_3d), !FLAGS_no_gui_verbose, FLAGS_fullscreen};
//            opWrapper.configure(wrapperStructGui);
//            // Set to single-thread (for sequential processing and/or debugging and/or reducing latency)
//            if (FLAGS_disable_multi_thread)
//                opWrapper.disableMultiThreading();
}

void PoseProcessor::process(cv::Mat &input/*, VirtualCapture &capture*/) { //27.02.2022
    cv::Mat small1; //small1 26.05.2022
    input.copyTo(small1);

    //27.09.2022
    m_bHandsUp = false;
    m_bHeadNotVisible = false;
    m_bBodyLying = false;
    m_bFight = false;

    //31.07.2022
    m_im_width = input.cols;
    m_im_height = input.rows;

//    cv::resize(small, small, cv::Size(400, 400));
    const op::Matrix imageToProcess = OP_CV2OPCONSTMAT(small1);
    datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
//    s = SkeletonExtractor::createFromOpenposeZed(datumProcessed, capture, 1920.0f / 400.0f,  1080.0f / 400.0f);

    //02.05.2022 comm
    /*
    char buf[10];
    sprintf(buf, "1=%d", datumProcessed->size());
    if(!datumProcessed->empty())
    {
        char buf1[10];
        sprintf(buf1, "2=%s", datumProcessed->at(0)->poseKeypoints.printSize().c_str());
        l_out.write(buf1);

        char buf2[10];
        sprintf(buf2, "3=%s", datumProcessed->at(0)->faceKeypoints.printSize().c_str());
        l_out.write(buf2);
    }
    */

    //s = SkeletonExtractor::createFromOpenposeZed(datumProcessed, capture, 1.0f,  1.0f); //comm 27.02.2022
    /*s =*/ SkeletonExtractor::createFromOpenpose(datumProcessed, 1.0f,  1.0f, vs); //27.02.2022


    //26.05.2022
    //if(1)
    //    AnalizeFaces(input);


    if(m_iUSE_ANALIZE_FIGHT == 1) //06.05.2022
        AnalizeFight(); //30.04.2022

//    QList<Skeleton> skeletons = SkeletonExtractor::createAllFromOpenposeZed(datumProcessed, capture, 1.0f,  1.0f);
//    QList<Skeleton> skeletons = SkeletonExtractor::createAllFromOpenposeZed(datumProcessed, capture, 1920.0f / 400.0f,  1080.0f / 400.0f);
//    skeletonFilter.append(skeletons);


//    shadow // че это не помню
//    for(int i = 0; i < input.rows; i++) {
//        for(int j = 0; j < input.cols; j++) {
//            if (pointCloud.at<cv::Vec3f>(i, j)[2] > 1 || pointCloud.at<cv::Vec3f>(i, j)[2] != pointCloud.at<cv::Vec3f>(i, j)[2] || pointCloud.at<cv::Vec3f>(i, j)[2] == 0) {
//                input.at<cv::Vec3b>(i,j)[0] = input.at<cv::Vec3b>(i,j)[0] - (input.at<cv::Vec3b>(i,j)[0] * 0.7);
//                input.at<cv::Vec3b>(i,j)[1] = input.at<cv::Vec3b>(i,j)[1] - (input.at<cv::Vec3b>(i,j)[1] * 0.7);
//                input.at<cv::Vec3b>(i,j)[2] = input.at<cv::Vec3b>(i,j)[2] - (input.at<cv::Vec3b>(i,j)[2] * 0.7);
//            }
//        }
//    }
}

//26.05.2022
/*
void PoseProcessor::AnalizeFaces(cv::Mat &_frame)
{

    int n = vs.size();
    for(int i=0; i<n; i++)
    {
        m_fp.process(_frame, vs[i]);
        //printf("1\n");
        cv::Mat out_face;
        if(m_fp.GetImage(out_face, true))
        //printf("2\n");
            imshow("face", out_face);
        //printf("3\n");
    }

}
*/

bool PoseProcessor::GetBigestSkeleton(Skeleton &_sct) //29.05.2022
{
    if(vs.size() == 0)
        return false;

    int max_size = 0;
    int i_pos = -1;
    for(int i=0; i < vs.size(); i++)
    {
        cv::Rect b_rect = vs[i].getBoundingBox();

        if(max_size < b_rect.width)
        {
            max_size = b_rect.width;
            i_pos = i;
        }

        if(max_size < b_rect.height)
        {
            max_size = b_rect.height;
            i_pos = i;
        }
    }

    if(i_pos == -1)
        return false;

    _sct = vs[i_pos];
    return true;
}

//Взять скелет у которого нос ближе всего к центру кадра
bool PoseProcessor::GetCenterNoseSkeleton(Skeleton &_sct) //31.07.2022
{
    if(vs.size() == 0)
        return false;

    //int max_size = 0;
    int i_pos = -1;

    float dist_min = 10000.;
    //Point3f3i cent_image_point(0,0,0, m_im_width/2, m_im_height/2, 0); //03.10.2022 comm
    Point3f3i cent_image_point(m_im_width/2, m_im_height/2, 0); //03.10.2022 add

    for(int i=0; i < vs.size(); i++)
    {
        /*
        cv::Rect b_rect = vs[i].getBoundingBox();

        if(max_size < b_rect.width)
        {
            max_size = b_rect.width;
            i_pos = i;
        }

        if(max_size < b_rect.height)
        {
            max_size = b_rect.height;
            i_pos = i;
        }
        */

        float dist_nose_to_centr = vs[i].getPixelDictance(vs[i].nose, cent_image_point);
        if(dist_nose_to_centr < dist_min)
        {
            dist_min = dist_nose_to_centr;
            i_pos = i;
        }
    }

    //printf("dist_min = %.1f\n", dist_min);

    if(i_pos == -1)
        return false;

    _sct = vs[i_pos];
    return true;
}

void PoseProcessor::GetAllPointsSkeletons(vector<cv::Point> &_v_out) //25.09.2022
{
    Skeleton s; //28.04.2022
    for(int i=0;i<vs.size();i++)
    {
        s = vs[i];

        if(s.isSkeletonRectOkSize(m_iMIN_SIZE_SKELETON, m_iMAX_SIZE_SKELETON)) //06.05.2022
        if(s.GetQuantSkeleton() > m_fMIN_QUANT_SKELETON) //06.05.2022
        {
        cv::Point pH(s.nose.pixelX, s.nose.pixelY);
        _v_out.push_back(pH);
        cv::Point pN(s.neck.pixelX, s.neck.pixelY);
        _v_out.push_back(pN);
        cv::Point pRS(s.rightShoulder.pixelX, s.rightShoulder.pixelY);
        _v_out.push_back(pRS);
        cv::Point pLS(s.leftShoulder.pixelX, s.leftShoulder.pixelY);
        _v_out.push_back(pLS);
        cv::Point pRE(s.rightElbow.pixelX, s.rightElbow.pixelY);
        _v_out.push_back(pRE);
        cv::Point pLE(s.leftElbow.pixelX, s.leftElbow.pixelY);
        _v_out.push_back(pLE);
        cv::Point pRW(s.rightWrist.pixelX, s.rightWrist.pixelY);
        _v_out.push_back(pRW);
        cv::Point pLW(s.leftWrist.pixelX, s.leftWrist.pixelY);
        _v_out.push_back(pLW);
        cv::Point pRP(s.rightPelvis.pixelX, s.rightPelvis.pixelY);
        _v_out.push_back(pRP);
        cv::Point pLP(s.leftPelvis.pixelX, s.leftPelvis.pixelY);
        _v_out.push_back(pLP);
        //
        cv::Point pRK(s.rightKnee.pixelX, s.rightKnee.pixelY);
        _v_out.push_back(pRK);
        cv::Point pLK(s.leftKnee.pixelX, s.leftKnee.pixelY);
        _v_out.push_back(pLK);
        cv::Point pRF(s.rightFoot.pixelX, s.rightFoot.pixelY);
        _v_out.push_back(pRF);
        cv::Point pLF(s.leftFoot.pixelX, s.leftFoot.pixelY);
        _v_out.push_back(pLF);
        cv::Point pCP(s.centerPelvis.pixelX, s.centerPelvis.pixelY);
        _v_out.push_back(pCP);
        //
        cv::Point pLF2(s.leftFoot2.pixelX, s.leftFoot2.pixelY);
        _v_out.push_back(pLF2);
        cv::Point pRF2(s.rightFoot2.pixelX, s.rightFoot2.pixelY);
        _v_out.push_back(pRF2);
        }
    }
}

void PoseProcessor::GetAllSkeletonsNose(vector<cv::Point> &_v_out) //05.12.2022
{
    Skeleton s; //28.04.2022
    for(int i=0;i<vs.size();i++)
    {
        s = vs[i];

        if(s.isSkeletonRectOkSize(m_iMIN_SIZE_SKELETON, m_iMAX_SIZE_SKELETON)) //06.05.2022
        if(s.GetQuantSkeleton() > m_fMIN_QUANT_SKELETON) //06.05.2022
        {
        cv::Point pH(s.neck.pixelX, s.neck.pixelY);
        _v_out.push_back(pH);
        }
    }
}

void PoseProcessor::AnalizeFight()
{
    vFights.clear();

    int n = vs.size();
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
        {
            if(vs[i].isSkeletonRectOkSize(m_iMIN_SIZE_SKELETON, m_iMAX_SIZE_SKELETON)) //06.05.2022
            if(vs[j].isSkeletonRectOkSize(m_iMIN_SIZE_SKELETON, m_iMAX_SIZE_SKELETON)) //06.05.2022
            if(vs[i].GetQuantSkeleton() > m_fMIN_QUANT_SKELETON && vs[j].GetQuantSkeleton() > m_fMIN_QUANT_SKELETON) //06.05.2022
            //тела бойцов одного размера
            if(vs[i].isBodyEqval(vs[j]))
            {
                bool b1=false, b2=false, b3=false, b4=false, b5=false, b6=false, b7=false, b8=false;

                if(m_iFIGHT_HIT_HAND_TO_FACE)
                {
                b1 = vs[i].isHitHandToFace(vs[j]);
                b2 = vs[j].isHitHandToFace(vs[i]);
                if(b1 || b2)
                    printf("HitHandToFace\n");
                }

                if(m_iFIGHT_HIT_FOOT_TO_FACE)
                {
                b3 = vs[i].isHitFootToFace(vs[j]);
                b4 = vs[j].isHitFootToFace(vs[i]);
                if(b3 || b4)
                    printf("isHitFootToFace\n");
                }

                if(m_iFIGHT_HIT_FOOT2_TO_FACE)
                {
                b5 = vs[i].isHitFoot2ToFace(vs[j]);
                b6 = vs[j].isHitFoot2ToFace(vs[i]);
                if(b5 || b6)
                    printf("isHitFoot2ToFace\n");
                }

                if(m_iFIGHT_HIT_FOOT_TO_PELVIS)
                {
                b7 = vs[i].isHitFootToPelvis(vs[j]);
                b8 = vs[j].isHitFootToPelvis(vs[i]);
                if(b7 || b8)
                    printf("isHitFootToPelvis\n");
                }

                if(b1 || b2 || b3 || b4 || b5 || b6 || b7 || b8)
                    vFights.push_back(vs[i].getRectSum(vs[j]));
            }
        }
}

bool PoseProcessor::PointOK(const cv::Point &_p)
{
    if(_p.x == 0 || _p.y == 0)
        return false;

    return true;
}

void DrawRectBlend(cv::Mat &input, cv::Rect _r, cv::Scalar _col, float maxFadeRange = 20, float transparency = 0.4)
{
    // define your overlay position
       cv::Rect overlay = _r;

       //float maxFadeRange = 20;

       // precompute fading mask:
       cv::Size size = input.size();
       cv::Mat maskTmp = cv::Mat(size, CV_8UC1, cv::Scalar(255));

       // draw black area where overlay is placed, because distance transform will assume 0 = distance 0
       cv::rectangle(maskTmp, overlay, 0, -1);

       cv::Mat distances;
       cv::distanceTransform(maskTmp, distances, cv::DIST_L1, cv::DIST_MASK_PRECISE);

       cv::Mat blendingMask = cv::Mat(size, CV_8UC1);

       // create blending mask from
       for (int j = 0; j < blendingMask.rows; ++j)
       for (int i = 0; i < blendingMask.cols; ++i)
       {
           float dist = distances.at<float>(j, i);

           float maskVal = (maxFadeRange - dist)/maxFadeRange * 255; // this will scale from 0 (maxFadeRange distance) to 255 (0 distance)
           if (maskVal < 0) maskVal = 0;

           blendingMask.at<unsigned char>(j, i) = maskVal;
       }

       cv::Scalar overlayColor = _col;//cv::Scalar(255, 0, 0);

       // color a whole image in overlay colors so that rect and blurred area are coverered by that color
       cv::Mat overlayImage = cv::Mat(size, CV_8UC3, overlayColor);

       // this has created all the stuff that is expensive and can be precomputed for a fixes roi overlay


       //float transparency = 0.2f; // 50% transparency





       // now for each image: just do this:
       //cv::Mat result = input.clone();


       for (int j = 0; j < blendingMask.rows; ++j)
       for (int i = 0; i < blendingMask.cols; ++i)
       {
           const unsigned char & blendingMaskVal = blendingMask.at<unsigned char>(j, i);

           if (blendingMaskVal) // only blend in areas where blending is necessary
           {
               float alpha = transparency * blendingMaskVal / 255.0f;

               //result                                                                                 //result
               input.at<cv::Vec3b>(j, i) = (alpha)*overlayImage.at<cv::Vec3b>(j, i) + (1.0f - alpha)*input.at<cv::Vec3b>(j, i);
           }

       }

       //input = result;
}

void PoseProcessor::drawL(cv::Mat &input) {
    Skeleton s; //28.04.2022
    for(int i=0;i<vs.size();i++)
    {
        s = vs[i];

        if(s.isSkeletonRectOkSize(m_iMIN_SIZE_SKELETON, m_iMAX_SIZE_SKELETON)) //06.05.2022
        if(s.GetQuantSkeleton() > m_fMIN_QUANT_SKELETON) //06.05.2022
        {

        //руки полностью подняты вверх
        if(m_iUSE_ANALIZE_HANDS_UP == 1) //06.05.2022
        if(s.isHandsUpFull())
            {
            //27.09.2022
            m_bHandsUp = true;

            DrawRectBlend(input, s.getBoundingBox(), m_scCOLOR_HANDS_UP); //cv::Scalar(255,0,0));
            }

        /*
        //стоит спиной
        if(!s.isBodyFront())
            {
            DrawRectBlend(input, s.getBoundingBox(), cv::Scalar(0,0,255));
            }
        */

        //стоит передом и лицо не видно
        if(m_iUSE_ANALIZE_HEAD_NOT_VISIBLE == 1) //06.05.2022
        if(s.isBodyFront() && s.isHeadNotVisible())
            {
            //27.09.2022
            m_bHeadNotVisible = true;

            DrawRectBlend(input, s.getBoundingBox(), m_scCOLOR_HEAD_NOT_VISIBLE); //cv::Scalar(0,255,0));
            }

        //тело лежит
        if(m_iUSE_ANALIZE_BODY_LYING == 1) //06.05.2022
        if(s.isBodyLying())
            {
            //27.09.2022
            m_bBodyLying = true;

            DrawRectBlend(input, s.getBoundingBox(), m_scCOLOR_BODY_LYING); //cv::Scalar(0,255,255));
            }


        if(m_iDRAW_SKELETONS == 1) //06.05.2022
        {



        if(1) //26.07.2022 draw hand L !!!
        {
            for(int fp = 0; fp < s.lhand.size(); fp++)
                if(s.lhand[fp].pixelZ > 30) //!!! score 70per
                cv::circle(input, cv::Point(s.lhand[fp].pixelX, s.lhand[fp].pixelY), 1, cv::Scalar(255, 255, 255, 255), 1);
        }

        if(1) //26.07.2022 draw hand R !!!
        {
            for(int fp = 0; fp < s.rhand.size(); fp++)
                if(s.rhand[fp].pixelZ > 30) //!!! score 70per
                cv::circle(input, cv::Point(s.rhand[fp].pixelX, s.rhand[fp].pixelY), 1, cv::Scalar(255, 255, 255, 255), 1);
        }

        cv::Point pH(s.nose.pixelX, s.nose.pixelY);
        if(!s.isPartPresent(s.nose)) pH.x = 0; //03.10.2022
        cv::Point pN(s.neck.pixelX, s.neck.pixelY);
        if(!s.isPartPresent(s.neck)) pN.x = 0; //03.10.2022
        cv::Point pRS(s.rightShoulder.pixelX, s.rightShoulder.pixelY);
        if(!s.isPartPresent(s.rightShoulder)) pRS.x = 0; //03.10.2022
        cv::Point pLS(s.leftShoulder.pixelX, s.leftShoulder.pixelY);
        if(!s.isPartPresent(s.leftShoulder)) pLS.x = 0; //03.10.2022
        cv::Point pRE(s.rightElbow.pixelX, s.rightElbow.pixelY);
        if(!s.isPartPresent(s.rightElbow)) pRE.x = 0; //03.10.2022
        cv::Point pLE(s.leftElbow.pixelX, s.leftElbow.pixelY);
        if(!s.isPartPresent(s.leftElbow)) pLE.x = 0; //03.10.2022
        cv::Point pRW(s.rightWrist.pixelX, s.rightWrist.pixelY);
        if(!s.isPartPresent(s.rightWrist)) pRW.x = 0; //03.10.2022
        cv::Point pLW(s.leftWrist.pixelX, s.leftWrist.pixelY);
        if(!s.isPartPresent(s.leftWrist)) pLW.x = 0; //03.10.2022
        cv::Point pRP(s.rightPelvis.pixelX, s.rightPelvis.pixelY);
        if(!s.isPartPresent(s.rightPelvis)) pRP.x = 0; //03.10.2022
        cv::Point pLP(s.leftPelvis.pixelX, s.leftPelvis.pixelY);
        if(!s.isPartPresent(s.leftPelvis)) pLP.x = 0; //03.10.2022
        //
        //28.04.2022
        cv::Point pRK(s.rightKnee.pixelX, s.rightKnee.pixelY);
        if(!s.isPartPresent(s.rightKnee)) pRK.x = 0; //03.10.2022
        cv::Point pLK(s.leftKnee.pixelX, s.leftKnee.pixelY);
        if(!s.isPartPresent(s.leftKnee)) pLK.x = 0; //03.10.2022
        cv::Point pRF(s.rightFoot.pixelX, s.rightFoot.pixelY);
        if(!s.isPartPresent(s.rightFoot)) pRF.x = 0; //03.10.2022
        cv::Point pLF(s.leftFoot.pixelX, s.leftFoot.pixelY);
        if(!s.isPartPresent(s.leftFoot)) pLF.x = 0; //03.10.2022
        cv::Point pCP(s.centerPelvis.pixelX, s.centerPelvis.pixelY);
        if(!s.isPartPresent(s.centerPelvis)) pCP.x = 0; //03.10.2022
        //
        cv::Point pLF2(s.leftFoot2.pixelX, s.leftFoot2.pixelY);
        if(!s.isPartPresent(s.leftFoot2)) pLF2.x = 0; //03.10.2022
        cv::Point pRF2(s.rightFoot2.pixelX, s.rightFoot2.pixelY);
        if(!s.isPartPresent(s.rightFoot2)) pRF2.x = 0; //03.10.2022

        if(PointOK(pH) && PointOK(pN))
            cv::line(input, pH, pN, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pN) && PointOK(pRS))
            cv::line(input, pN, pRS, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pN) && PointOK(pLS))
            cv::line(input, pN, pLS, cv::Scalar(0, 255, 0, 255), 2);

        //if(PointOK(pN) && PointOK(pRP))
        //    cv::line(input, pN, pRP, cv::Scalar(0, 255, 0, 255), 2);

        //if(PointOK(pN) && PointOK(pLP))
        //    cv::line(input, pN, pLP, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pRS) && PointOK(pRE))
            cv::line(input, pRS, pRE, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pRE) && PointOK(pRW))
            cv::line(input, pRE, pRW, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pLS) && PointOK(pLE))
            cv::line(input, pLS, pLE, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pLE) && PointOK(pLW))
            cv::line(input, pLE, pLW, cv::Scalar(0, 255, 0, 255), 2);

        //28.04.2022
        if(PointOK(pRP) && PointOK(pRK))
            cv::line(input, pRP, pRK, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pLP) && PointOK(pLK))
            cv::line(input, pLP, pLK, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pRK) && PointOK(pRF))
            cv::line(input, pRK, pRF, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pLK) && PointOK(pLF))
            cv::line(input, pLK, pLF, cv::Scalar(0, 255, 0, 255), 2);

        //
        if(PointOK(pLF) && PointOK(pLF2))
            cv::line(input, pLF, pLF2, cv::Scalar(0, 255, 0, 255), 2);

        if(PointOK(pRF) && PointOK(pRF2))
            cv::line(input, pRF, pRF2, cv::Scalar(0, 255, 0, 255), 2);

        //taz
        if(PointOK(pRP) && PointOK(pLP))
            cv::line(input, pRP, pLP, cv::Scalar(0, 255, 0, 255), 2);

        //pozv
        if(PointOK(pN) && PointOK(pCP))
            cv::line(input, pN, pCP, cv::Scalar(0, 255, 0, 255), 2);


        if(s.isPartPresent(s.nose)) //03.10.2022
            cv::circle(input, cv::Point(s.nose.pixelX, s.nose.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
       // cv::putText(input, "H", cv::Point2f(s.nose.pixelX, s.nose.pixelY),
       //             cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

       // cv::line(input, cv::Point(s.nose.pixelX, s.nose.pixelY), cv::Point(s.neck.pixelX, s.neck.pixelY), cv::Scalar(255, 255, 255, 255));

    if(s.isPartPresent(s.neck)) //03.10.2022
        cv::circle(input, cv::Point(s.neck.pixelX, s.neck.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "N", cv::Point2f(s.neck.pixelX, s.neck.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.rightShoulder)) //03.10.2022
        cv::circle(input, cv::Point(s.rightShoulder.pixelX, s.rightShoulder.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RS", cv::Point2f(s.rightShoulder.pixelX, s.rightShoulder.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.rightElbow)) //03.10.2022
        cv::circle(input, cv::Point(s.rightElbow.pixelX, s.rightElbow.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RE", cv::Point2f(s.rightElbow.pixelX, s.rightElbow.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.rightWrist)) //03.10.2022
        cv::circle(input, cv::Point(s.rightWrist.pixelX, s.rightWrist.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RW", cv::Point2f(s.rightWrist.pixelX, s.rightWrist.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.rightPelvis)) //03.10.2022
        cv::circle(input, cv::Point(s.rightPelvis.pixelX, s.rightPelvis.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
   // cv::putText(input, "RP", cv::Point2f(s.rightPelvis.pixelX, s.rightPelvis.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.rightKnee)) //03.10.2022
        cv::circle(input, cv::Point(s.rightKnee.pixelX, s.rightKnee.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RK", cv::Point2f(s.rightKnee.pixelX, s.rightKnee.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.leftShoulder)) //03.10.2022
        cv::circle(input, cv::Point(s.leftShoulder.pixelX, s.leftShoulder.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "LS", cv::Point2f(s.leftShoulder.pixelX, s.leftShoulder.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.leftElbow)) //03.10.2022
        cv::circle(input, cv::Point(s.leftElbow.pixelX, s.leftElbow.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "LE", cv::Point2f(s.leftElbow.pixelX, s.leftElbow.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.leftWrist)) //03.10.2022
        cv::circle(input, cv::Point(s.leftWrist.pixelX, s.leftWrist.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "LW", cv::Point2f(s.leftWrist.pixelX, s.leftWrist.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.leftPelvis)) //03.10.2022
        cv::circle(input, cv::Point(s.leftPelvis.pixelX, s.leftPelvis.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "LP", cv::Point2f(s.leftPelvis.pixelX, s.leftPelvis.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    if(s.isPartPresent(s.leftKnee)) //03.10.2022
        cv::circle(input, cv::Point(s.leftKnee.pixelX, s.leftKnee.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
   // cv::putText(input, "LK", cv::Point2f(s.leftKnee.pixelX, s.leftKnee.pixelY),
    //            cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    //28.04.2022
    if(s.isPartPresent(s.rightFoot)) //03.10.2022
        cv::circle(input, cv::Point(s.rightFoot.pixelX, s.rightFoot.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RK", cv::Point2f(s.rightKnee.pixelX, s.rightKnee.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    //28.04.2022
    if(s.isPartPresent(s.leftFoot)) //03.10.2022
        cv::circle(input, cv::Point(s.leftFoot.pixelX, s.leftFoot.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RK", cv::Point2f(s.rightKnee.pixelX, s.rightKnee.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    //28.04.2022
    if(s.isPartPresent(s.rightFoot2)) //03.10.2022
        cv::circle(input, cv::Point(s.rightFoot2.pixelX, s.rightFoot2.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RK", cv::Point2f(s.rightKnee.pixelX, s.rightKnee.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    //28.04.2022
    if(s.isPartPresent(s.leftFoot2)) //03.10.2022
        cv::circle(input, cv::Point(s.leftFoot2.pixelX, s.leftFoot2.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RK", cv::Point2f(s.rightKnee.pixelX, s.rightKnee.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

    //28.04.2022
    if(s.isPartPresent(s.centerPelvis)) //03.10.2022
        cv::circle(input, cv::Point(s.centerPelvis.pixelX, s.centerPelvis.pixelY), 1, cv::Scalar(255, 255, 255, 255), 8);
    //cv::putText(input, "RK", cv::Point2f(s.rightKnee.pixelX, s.rightKnee.pixelY),
     //           cv::FONT_HERSHEY_PLAIN, 2,  cv::Scalar(255, 255, 255, 255), 2);

        } //if m_iDRAW_SKELETONS

        } //GetQuant ok
    }

    //драки //30.04.2022
    for(int i=0; i<vFights.size(); i++)
    {
        //27.09.2022
        m_bFight = true;

        DrawRectBlend(input, vFights[i], m_scCOLOR_FIGHT); //cv::Scalar(0,0,255));
    }
}

//27.09.2022
void PoseProcessor::GetAlarm(bool &_bHandsUp, bool &_bHeadNotVisible, bool &_bBodyLying, bool &_bFight)
{
    _bHandsUp = m_bHandsUp;
    _bHeadNotVisible = m_bHeadNotVisible;
    _bBodyLying = m_bBodyLying;
    _bFight = m_bFight;
}
