#include <QtTest>

#include "EyeDetector.h"
#include "PoseProcessor.h"
#include "mini.h"
using namespace cv;

#define TIME_SLEEP_TEST_MS 1500

class EyeDetection : public QObject
{
    Q_OBJECT

public:
    EyeDetection();
    ~EyeDetection();

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
    void EyesCenter();
    void EyesLeft();
    void EyesRight();
    void EyesDown();
};

//цвет из 255,0,0 в cv::Scalar
cv::Scalar EyeDetection::GetScalarCol(string _str)
{
    int r=0,g=0,b=0;
    sscanf_s(_str.c_str(), "%d,%d,%d", &r, &g, &b);
    cv::Scalar ret(b, g, r);
    return ret;
}

EyeDetection::EyeDetection()
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

EyeDetection::~EyeDetection()
{
}

void EyeDetection::EyesCenter()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/EyeDetection/FaceEyeCentr.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        EyeDetector eyeDetector;

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
            eyeDetector.processing(frame, faceDetails);


            //Определение направления взгляда
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_DOWN)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2, frame.rows/2 + 100), Scalar(0,255,0), 2);
                printf("DOWN!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_LEFT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 - 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("LEFT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_RIGHT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 + 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("RIGHT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_CENTER)
                printf("CENTER!\n");


            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением данных детекции глаз
        circle(frame, eyeDetector.leftPupil, 9, Scalar(0,255,0));
        circle(frame, eyeDetector.rightPupil, 9, Scalar(0,255,0));
        rectangle(frame, eyeDetector.leftEyeRegion, Scalar(0,255,0));
        rectangle(frame, eyeDetector.rightEyeRegion, Scalar(0,255,0));
        imshow("EyesCenter", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void EyeDetection::EyesLeft()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/EyeDetection/FaceEyeLeft.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        EyeDetector eyeDetector;

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
            eyeDetector.processing(frame, faceDetails);


            //Определение направления взгляда
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_DOWN)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2, frame.rows/2 + 100), Scalar(0,255,0), 2);
                printf("DOWN!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_LEFT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 - 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("LEFT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_RIGHT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 + 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("RIGHT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_CENTER)
                printf("CENTER!\n");


            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением данных детекции глаз
        circle(frame, eyeDetector.leftPupil, 9, Scalar(0,255,0));
        circle(frame, eyeDetector.rightPupil, 9, Scalar(0,255,0));
        rectangle(frame, eyeDetector.leftEyeRegion, Scalar(0,255,0));
        rectangle(frame, eyeDetector.rightEyeRegion, Scalar(0,255,0));
        imshow("EyesLeft", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void EyeDetection::EyesRight()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/EyeDetection/FaceEyeRight.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        EyeDetector eyeDetector;

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
            eyeDetector.processing(frame, faceDetails);


            //Определение направления взгляда
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_DOWN)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2, frame.rows/2 + 100), Scalar(0,255,0), 2);
                printf("DOWN!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_LEFT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 - 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("LEFT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_RIGHT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 + 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("RIGHT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_CENTER)
                printf("CENTER!\n");


            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением данных детекции глаз
        circle(frame, eyeDetector.leftPupil, 9, Scalar(0,255,0));
        circle(frame, eyeDetector.rightPupil, 9, Scalar(0,255,0));
        rectangle(frame, eyeDetector.leftEyeRegion, Scalar(0,255,0));
        rectangle(frame, eyeDetector.rightEyeRegion, Scalar(0,255,0));
        imshow("EyesRight", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

void EyeDetection::EyesDown()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/EyeDetection/FaceEyeDown.jpg");

    if(!frame.empty())
    {
        PoseProcessor* poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);

        //Обработка кадра
        poseProcessor->process(frame);

        EyeDetector eyeDetector;

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
            eyeDetector.processing(frame, faceDetails);


            //Определение направления взгляда
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_DOWN)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2, frame.rows/2 + 100), Scalar(0,255,0), 2);
                printf("DOWN!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_LEFT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 - 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("LEFT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_RIGHT)
                {
                arrowedLine(frame, Point(frame.cols/2, frame.rows/2), Point(frame.cols/2 + 100, frame.rows/2), Scalar(0,255,0), 2);
                printf("RIGHT!\n");
                }
            if(eyeDetector.getGazeDirection() == eyeDetector.DIR_CENTER)
                printf("CENTER!\n");


            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с наложением данных детекции глаз
        circle(frame, eyeDetector.leftPupil, 9, Scalar(0,255,0));
        circle(frame, eyeDetector.rightPupil, 9, Scalar(0,255,0));
        rectangle(frame, eyeDetector.leftEyeRegion, Scalar(0,255,0));
        rectangle(frame, eyeDetector.rightEyeRegion, Scalar(0,255,0));
        imshow("EyesDown", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete poseProcessor;
    }

    QVERIFY(bOK);
}

QTEST_APPLESS_MAIN(EyeDetection)

#include "tst_eyedetection.moc"
