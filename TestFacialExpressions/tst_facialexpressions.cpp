#include <QtTest>

#include "faceprocessor.h"
#include "PoseProcessor.h"
#include "mini.h"
using namespace cv;

#define TIME_SLEEP_TEST_MS 1500

class FacialExpressions : public QObject
{
    Q_OBJECT

public:
    FacialExpressions();
    ~FacialExpressions();

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
    void EyeClose();
    void MouthOpen();
    void FaceVisible();
    void FaceTilt();
    void FaceDown();
    void FaceLeft();
    void FaceRight();
    void LipsClosed();
    void EyebrowsRaised();
    void EyebrowsLowered();
};

FacialExpressions::FacialExpressions()
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

//цвет из 255,0,0 в cv::Scalar
cv::Scalar FacialExpressions::GetScalarCol(string _str)
{
    int r=0,g=0,b=0;
    sscanf_s(_str.c_str(), "%d,%d,%d", &r, &g, &b);
    cv::Scalar ret(b, g, r);
    return ret;
}

FacialExpressions::~FacialExpressions()
{
}

void FacialExpressions::EyeClose()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/EyeClose.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 0.);

            //Глаза закрыты
            if(faceProcessor.isEyeClose())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("EyeClose", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::MouthOpen()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/MouthOpen.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 0.);

            //Рот открыт
            if(faceProcessor.isMouthOpen())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("MouthOpen", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::FaceVisible()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/FaceVisible.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 0.);

            //Видимость лица больше 60 процентов, но меньше 80
            if(faceProcessor.perFaceVisible() > 60 && faceProcessor.perFaceVisible() < 80)
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("FaceVisible", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::FaceTilt()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/FaceTilt.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Наклон лица больше 20 градусов
            if(faceProcessor.GetFaceTilt() > 20)
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("FaceTilt", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::FaceDown()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/FaceDown.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Лицо опущено
            if(faceProcessor.isFaceDown())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("FaceDown", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::FaceLeft()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/FaceLeft.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Лицо повернуто влево
            if(faceProcessor.isFaceLeft())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("FaceLeft", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::FaceRight()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/FaceRight.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Лицо повернуто вправо
            if(faceProcessor.isFaceRight())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("FaceRight", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::LipsClosed()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/LipsClosed.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Губы сжаты
            if(faceProcessor.isLipsClosed())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("LipsClosed", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::EyebrowsRaised()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/EyebrowsRaised.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Брови подняты
            if(faceProcessor.isEyebrowsRaised())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("EyebrowsRaised", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void FacialExpressions::EyebrowsLowered()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FacialExpressions/EyebrowsLowered.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        FaceProcessor faceProcessor;

        Skeleton s;
        //Взять центральный скелет для веделния ключевых точек лица
        if(poseProcessor->GetCenterNoseSkeleton(s))
        {
            //Подготовка вектора ключевых точек лица
            vector<cPointFace> v_keypoints_face;
            for(int fp = 0; fp < (int)s.face.size(); fp++)
                {
                cPointFace point_face(s.face[fp].pixelX, s.face[fp].pixelY, s.face[fp].pixelZ);
                v_keypoints_face.push_back(point_face);
                }

            //Обработка кадра с целью детекции области глаз и зрачков
            cFaceKeyPoint faceDetails(v_keypoints_face);
            faceProcessor.process(frame, faceDetails, true, 30.);

            //Брови опущены
            if(faceProcessor.isEyebrowsLowered())
                bOK = true;
        }

        if(bOK)
        {
        faceProcessor.GetImage(frame, true);
        imshow("EyebrowsLowered", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

QTEST_APPLESS_MAIN(FacialExpressions)

#include "tst_facialexpressions.moc"
