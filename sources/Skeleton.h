#ifndef SKELETON_H
#define SKELETON_H

#include <opencv2/opencv.hpp>

#include <QDebug>
#include <QString>
#include <QMap>

#include <vector>
using namespace std;

#include "Point3f3i.h"

class Skeleton
{
public:
    Skeleton();

    //31.07.2022
    bool m_bVisible;
    void SetEmptySkeleton()
    {
        m_bVisible = false;
    }
    //
    bool isVisible()
    {
        return m_bVisible;
    }

    //    nose;             //0
    //    neck;             //1
    //    rightShoulder;    //2
    //    rightElbow;       //3
    //    rightWrist;       //4
    //    leftShoulder;     //5
    //    leftElbow;        //6
    //    leftWrist;        //7
    //    centerPelvis;     //8
    //    rightPelvis;      //9
    //    rightKnee;        //10
    //    rightFoot;        //11
    //    leftPelvis;       //12
    //    leftKnee;         //13
    //    leftFoot;         //14
    //    rightEye;         //15
    //    leftEye;          //16
    //    rightEar;         //17
    //    leftEar;          //18
    //    leftFoot2;          //19
    //    rightFoot2;          //22

    vector<Point3f3i> face; //26.07.2022
    vector<Point3f3i> lhand; //26.07.2022
    vector<Point3f3i> rhand; //26.07.2022

    Point3f3i nose;
    Point3f3i neck;
    Point3f3i rightShoulder;
    Point3f3i rightElbow;
    Point3f3i rightWrist;
    Point3f3i leftShoulder;
    Point3f3i leftElbow;
    Point3f3i leftWrist;
    Point3f3i centerPelvis;
    Point3f3i rightPelvis;
    Point3f3i rightKnee;
    Point3f3i rightFoot;
    Point3f3i leftPelvis;
    Point3f3i leftKnee;
    Point3f3i leftFoot;
    Point3f3i rightEye;
    Point3f3i leftEye;
    Point3f3i rightEar;
    Point3f3i leftEar;
    Point3f3i leftFoot2;
    Point3f3i rightFoot2;

    bool isLefter(Point3f3i what, Point3f3i than);
    bool isUpper(Point3f3i what, Point3f3i than);
    bool isLower(Point3f3i what, Point3f3i than);
    bool isPartPresent(Point3f3i p);

    bool isHandsUpFull(); //+
    bool isBodyLying(); //
    bool isBodyFront(); //+
    bool isHeadNotVisible(); //+-
    bool isHandsUp();
    bool isHandsDownFree();

    //02.08.2022
    //наклон туловища относительно вертикали в градусах
    int TorsoTiltDeg();

    //плечи подняты
    bool isShouldersRaised();

    //руки к груди
    bool isHandsChest();

    //рука лицо
    bool isFacepalm();


    //драка
    ///////

    //тела одного размера
    //min_body_otn = 1. - тела одинакового размера
    bool isBodyEqval(Skeleton &_s, float min_body_otn = 0.7);

    //Удар рукой в лицо скелету _s
    bool isHitHandToFace(Skeleton &_s);

    //Удар ногой(пяткой) в лицо скелету _s
    bool isHitFootToFace(Skeleton &_s);

    //Удар ногой(пыром) в лицо скелету _s
    bool isHitFoot2ToFace(Skeleton &_s);

    //Удар ногой в таз скелету _s
    bool isHitFootToPelvis(Skeleton &_s);

    //Дистанция между точками на плоскости
    float getPixelDictance(Point3f3i p1, Point3f3i p2);

    //Огр рамка скелета
    cv::Rect getBoundingBox(); //29.04.2022

    //Вернуть общую bound rect скелетов
    cv::Rect getRectSum(Skeleton &_s);

    double GetQuantSkeleton();

    bool isSkeletonRectOkSize(int _iMin, int _iMax);
};

#endif // SKELETON_H
