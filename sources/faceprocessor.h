#ifndef FACEPROCESSOR_H
#define FACEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp> //clane 25.07.2022

#include "EyeDetector.h"

#define OK_PER_POINT_FACE 60 //60%

class FaceProcessor {
private:    
    int m_iTOTAL_BLINK;
    bool m_bEYE_CLOSE;
    void checkEyesBlinking();


    bool m_bMouthOpen;
    void checkMouthOpen();

    cFaceKeyPoint faceDetails;
    cv::Mat currentFace;

    bool m_bBlinked;
    bool m_bFaceFound;

    int m_iPerFaceVisible;
    void checkPerFaceVisible();

    int m_iFaceTilt;

    int m_bFaceDown;
    void checkFaceDown();

    int m_bFaceLeft;
    int m_bFaceRight;
    void checkFaceLeftRigth();

    bool m_bLipsClosed;
    void checkLipsClosed();

    bool m_bEyebrowsRaised;
    bool m_bEyebrowsLowered;
    void checkEyebrowsUpDown();






    //25.07.2022 растяжка гистограммы
    void applyCLAHE(cv::Mat &srcArry, cv::Mat &dstArry);

    bool isPointPresent(int _part)
    {
        if(faceDetails.part(_part).prec() > OK_PER_POINT_FACE)
            return true;

        return false;
    }

    //-1 err
    double GetDist(int _part1, int _part2)
    {
        if(isPointPresent(_part1) && isPointPresent(_part2))
            return sqrt(pow(faceDetails.part(_part1).x() - faceDetails.part(_part2).x(), 2) + pow(faceDetails.part(_part1).y() - faceDetails.part(_part2).y(), 2));

        return -1;
    }

    //-1 err
    double GetDistX(int _part1, int _part2)
    {
        if(isPointPresent(_part1) && isPointPresent(_part2))
            return fabs(faceDetails.part(_part1).x() - faceDetails.part(_part2).x());

        return -1;
    }

public:
    EyeDetector eyeDetector;

    bool isEyesDown(); //глаза вниз
    bool isEyesCenter();
    bool isEyesLeft();
    bool isEyesRight();

    bool isEyeClose(); //глаза закрыты 25.10.2022
    bool isBlinked(); //моргнул
    bool isMouthOpen(); //рот открыт
    bool isFaceVisible(); //лицо видимо/поступило на обработку
    int perFaceVisible(); //процент видимости лица [0-100]
    int GetFaceTilt(); //поворот лица
    bool isFaceDown(); //голова опущена
    bool isFaceLeft(); //голова повернута влево
    bool isFaceRight(); //голова повернута вправо
    bool isLipsClosed(); //губы сомкнуты
    bool isEyebrowsRaised(); //брови подняты
    bool isEyebrowsLowered(); //брови опущены

    FaceProcessor();
    void process(cv::Mat &frame, cFaceKeyPoint &_faceDetails, bool _face_found, double _face_tilt);
    bool GetImage(cv::Mat &_frame, bool showPoints);
};

#endif // FACEPROCESSOR_H
