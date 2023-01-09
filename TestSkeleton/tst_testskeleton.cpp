#include <QtTest>

#include "PoseProcessor.h"
#include "mini.h"
#include <opencv2/opencv.hpp>
using namespace cv;

#define TIME_SLEEP_TEST_MS 1500

class TestSkeleton : public QObject
{
    Q_OBJECT

public:
    TestSkeleton();
    ~TestSkeleton();

private:
    //[PARAM_DETECT_POSE]
    double fMIN_QUANT_SKELETON;
    int iMIN_SIZE_SKELETON;
    int iMAX_SIZE_SKELETON;
    int iDRAW_SKELETONS;

    int iUSE_ANALIZE_HANDS_UP;
    cv::Scalar scCOLOR_HANDS_UP;

    int iUSE_ANALIZE_HEAD_NOT_VISIBLE;
    cv::Scalar scCOLOR_HEAD_NOT_VISIBLE;

    int iUSE_ANALIZE_BODY_LYING;
    cv::Scalar scCOLOR_BODY_LYING;

    int iUSE_ANALIZE_FIGHT;
    int iFIGHT_HIT_HAND_TO_FACE;
    int iFIGHT_HIT_FOOT_TO_FACE;
    int iFIGHT_HIT_FOOT2_TO_FACE;
    int iFIGHT_HIT_FOOT_TO_PELVIS;
    cv::Scalar scCOLOR_FIGHT;

    //[PARAM_DETECT_BEHAVIOR]
    int iUSE_DETECT_BEHAVIOR;

    cv::Scalar GetScalarCol(string _str);

    //ТЕСТЫ
private slots:
    void TorsoTilt();
    void ShouldersRaised();
    void HandsChest();
    void HandsUp();
    void Facepalm();
};

//цвет из 255,0,0 в cv::Scalar
cv::Scalar TestSkeleton::GetScalarCol(string _str)
{
    int r=0,g=0,b=0;
    sscanf(_str.c_str(), "%d,%d,%d", &r, &g, &b);
    cv::Scalar ret(b, g, r);
    return ret;
}

TestSkeleton::TestSkeleton()
{
    QString qs = QDir::currentPath();
    qs += "/release";
    QDir::setCurrent(qs);

    try {
    mINI::INIFile file("../../../inputdata/configStrongAI.ini");
    mINI::INIStructure ini;
    file.read(ini);

    //read [PARAM_DETECT_POSE]
    fMIN_QUANT_SKELETON = std::stof(ini["PARAM_DETECT_POSE"]["MIN_QUANT_SKELETON"]);
    iMIN_SIZE_SKELETON = std::stoi(ini["PARAM_DETECT_POSE"]["MIN_SIZE_SKELETON"]);
    iMAX_SIZE_SKELETON = std::stoi(ini["PARAM_DETECT_POSE"]["MAX_SIZE_SKELETON"]);
    iDRAW_SKELETONS = std::stoi(ini["PARAM_DETECT_POSE"]["DRAW_SKELETONS"]);

    iUSE_ANALIZE_HANDS_UP = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_HANDS_UP"]);
    scCOLOR_HANDS_UP = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_HANDS_UP"]);

    iUSE_ANALIZE_HEAD_NOT_VISIBLE = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_HEAD_NOT_VISIBLE"]);
    scCOLOR_HEAD_NOT_VISIBLE = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_HEAD_NOT_VISIBLE"]);

    iUSE_ANALIZE_BODY_LYING = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_BODY_LYING"]);
    scCOLOR_BODY_LYING = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_BODY_LYING"]);

    iUSE_ANALIZE_FIGHT = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_FIGHT"]);
    iFIGHT_HIT_HAND_TO_FACE = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_HAND_TO_FACE"]);
    iFIGHT_HIT_FOOT_TO_FACE = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_FOOT_TO_FACE"]);
    iFIGHT_HIT_FOOT2_TO_FACE = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_FOOT2_TO_FACE"]);
    iFIGHT_HIT_FOOT_TO_PELVIS = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_FOOT_TO_PELVIS"]);
    scCOLOR_FIGHT = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_FIGHT"]);

    //25.09.2022
    //read [PARAM_DETECT_BEHAVIOR]
    iUSE_DETECT_BEHAVIOR = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["USE_DETECT_BEHAVIOR"]);

    }
    catch(...)
    {
    printf("Err read ini!\n");
    exit(0);
    }
}

TestSkeleton::~TestSkeleton()
{
}

//Проверка детекции наклона туолвища человека
void TestSkeleton::TorsoTilt()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/Skeleton/TorsoTilt.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        Skeleton s;
        //Взять центральный скелет
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Определить наклон туловища
            int iTorsoTilt = s.TorsoTiltDeg();
            //Если наклон более 45 градусов - тест пройден
            if(iTorsoTilt > 45)
                bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением скелета
        poseProcessor->drawL(frame);
        imshow("TorsoTilt", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

//Проверка детекции поднятых плеч человека
void TestSkeleton::ShouldersRaised()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/Skeleton/ShouldersRaised.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        Skeleton s;
        //Взять центральный скелет
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Определить подняты ли плечи
            bool bShouldersRaised = s.isShouldersRaised();
            if(bShouldersRaised)
                bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением скелета
        poseProcessor->drawL(frame);
        imshow("ShouldersRaised", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}


//Проверка детекции руки к груди человека
void TestSkeleton::HandsChest()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/Skeleton/HandsChest.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        Skeleton s;
        //Взять центральный скелет
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Определить состояние руки к груди
            bool bHandsChest = s.isHandsChest();
            if(bHandsChest)
                bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением скелета
        poseProcessor->drawL(frame);
        imshow("HandsChest", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

//Проверка детекции руки человека подняты вверх
void TestSkeleton::HandsUp()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/Skeleton/HandsUp.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        Skeleton s;
        //Взять центральный скелет
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Определить подняты ли руки вверх
            bool bHandsUp = s.isHandsUpFull();
            if(bHandsUp)
                bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением скелета
        poseProcessor->drawL(frame);
        imshow("HandsUp", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

//Проверка детекции состояния рука к лицу
void TestSkeleton::Facepalm()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/Skeleton/Facepalm.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        Skeleton s;
        //Взять центральный скелет
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Определить состояние руки к лицу
            bool bFacepalm = s.isFacepalm();
            if(bFacepalm)
                bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением скелета
        poseProcessor->drawL(frame);
        imshow("Facepalm", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

QTEST_APPLESS_MAIN(TestSkeleton)

#include "tst_testskeleton.moc"
