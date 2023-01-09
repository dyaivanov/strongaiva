#ifndef POSEPROCESSOR_H
#define POSEPROCESSOR_H

#include <QDebug>
#include <QObject>
//#include <QImage>
#include <QThread>
#include <QtCore/QCoreApplication>
#include <ctime>
//#include <QPainter>
//#include <QPen>

//#include "faceprocessor.h" //26.05.2022

#include <opencv2/opencv.hpp>

//#include "virtualcapture.h" //comm 27.02.2022



//#define OPENPOSE_FLAGS_DISABLE_POSE //comm 21.07.2022

#include <openpose/headers.hpp>


/*
#define OPENPOSE_FLAGS_DISABLE_PRODUCER
#define OPENPOSE_FLAGS_DISABLE_DISPLAY
#include <openpose/flags.hpp>
// OpenPose dependencies
#include <openpose/headers.hpp>
*/

#include "SkeletonExtractor.h"

using namespace std;

class PoseProcessor : public QObject {

    Q_OBJECT

private:
    double m_fMIN_QUANT_SKELETON;
    int m_iMIN_SIZE_SKELETON;
    int m_iMAX_SIZE_SKELETON;
    int m_iDRAW_SKELETONS;

    int m_iUSE_ANALIZE_HANDS_UP;
    cv::Scalar m_scCOLOR_HANDS_UP;

    int m_iUSE_ANALIZE_HEAD_NOT_VISIBLE;
    cv::Scalar m_scCOLOR_HEAD_NOT_VISIBLE;

    int m_iUSE_ANALIZE_BODY_LYING;
    cv::Scalar m_scCOLOR_BODY_LYING;

    int m_iUSE_ANALIZE_FIGHT;
    int m_iFIGHT_HIT_HAND_TO_FACE;
    int m_iFIGHT_HIT_FOOT_TO_FACE;
    int m_iFIGHT_HIT_FOOT2_TO_FACE;
    int m_iFIGHT_HIT_FOOT_TO_PELVIS;
    cv::Scalar m_scCOLOR_FIGHT;

    int m_im_width; //31.07.2022
    int m_im_height;

    //27.09.2022
    bool m_bHandsUp;
    bool m_bHeadNotVisible;
    bool m_bBodyLying;
    bool m_bFight;

public:
    vector<Skeleton> vs;
    vector<cv::Rect> vFights;

    PoseProcessor(int _iUSE_ANALIZE_FACES, //28.09.2022
                  double _fMIN_QUANT_SKELETON, int _iMIN_SIZE_SKELETON, int _iMAX_SIZE_SKELETON, int _iDRAW_SKELETONS,
                  int _iUSE_ANALIZE_HANDS_UP, cv::Scalar _scCOLOR_HANDS_UP,
                  int _iUSE_ANALIZE_HEAD_NOT_VISIBLE, cv::Scalar _scCOLOR_HEAD_NOT_VISIBLE,
                  int _iUSE_ANALIZE_BODY_LYING, cv::Scalar _scCOLOR_BODY_LYING,
                  int _iUSE_ANALIZE_FIGHT, int _iFIGHT_HIT_HAND_TO_FACE, int _iFIGHT_HIT_FOOT_TO_FACE, int _iFIGHT_HIT_FOOT2_TO_FACE, int _iFIGHT_HIT_FOOT_TO_PELVIS, cv::Scalar _scCOLOR_FIGHT);
    void process(cv::Mat &input);
    void AnalizeFight();

    bool GetBigestSkeleton(Skeleton &_sct); //29.05.2022
    bool GetCenterNoseSkeleton(Skeleton &_sct); //31.07.2022
    void GetAllPointsSkeletons(vector<cv::Point> &_v_out); //25.09.2022

    void GetAllSkeletonsNose(vector<cv::Point> &_v_out); //05.12.2022

    //27.09.2022
    void GetAlarm(bool &_bHandsUp, bool &_bHeadNotVisible, bool &_bBodyLying, bool &_bFight);

    bool PointOK(const cv::Point &_p);
    void drawL(cv::Mat &input);

private:
    void configureWrapper(op::Wrapper& opWrapper, int _iUSE_ANALIZE_FACES); //29.09.2022
    op::Wrapper opWrapper {
        op::ThreadManagerMode::Asynchronous
    };
    std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>> datumProcessed;
};

#endif // POSEPROCESSOR_H
