#include <QtTest>

#include "YoloDetector.h"
#include "mini.h"

#define TIME_SLEEP_TEST_MS 1500

class FaceDetection : public QObject
{
    Q_OBJECT

public:
    FaceDetection();
    ~FaceDetection();

private:
    //[PARAM_DETECT_FACES]
    int iUSE_DETECT_DNN_FACES = 0;
    int iCOMPUTE_DNN_CUDA_FACES = 0;
    int iNUM_CLASSES_FACES = 0;
    string sPATH_CFG_FACES;
    string sPATH_WEIGHTS_FACES;
    string sPATH_NAMES_FACES;
    double fCONFIDENCES_FACES = 0.;
    int iMIN_SIZE_FACES = 0;
    int iMAX_SIZE_FACES = 0;
    int iGREEDY_RECTS_FACES = 0;
    int iDRAW_TEXT_FACES = 0;
    vector<cv::Scalar> vColors_FACES;

    cv::Scalar GetScalarCol(string _str);

//ТЕСТЫ
private slots:
    void OneFace();
    void ManyFace();
    void CloseFace();

};

//цвет из 255,0,0 в cv::Scalar
cv::Scalar FaceDetection::GetScalarCol(string _str)
{
    int r=0,g=0,b=0;
    sscanf(_str.c_str(), "%d,%d,%d", &r, &g, &b);
    cv::Scalar ret(b, g, r);
    return ret;
}

FaceDetection::FaceDetection()
{
    QString qs = QDir::currentPath();
    qs += "/release";
    QDir::setCurrent(qs);

    try {
    mINI::INIFile file("../../../inputdata/configStrongAI.ini");
    mINI::INIStructure ini;
    file.read(ini);

    //read [PARAM_DETECT_FACES]
    iCOMPUTE_DNN_CUDA_FACES = std::stoi(ini["PARAM_DETECT_FACES"]["COMPUTE_DNN_CUDA"]);
    iNUM_CLASSES_FACES = std::stoi(ini["PARAM_DETECT_FACES"]["NUM_CLASSES"]);
    sPATH_CFG_FACES = ini["PARAM_DETECT_FACES"]["PATH_CFG"];
    sPATH_WEIGHTS_FACES = ini["PARAM_DETECT_FACES"]["PATH_WEIGHTS"];
    sPATH_NAMES_FACES = ini["PARAM_DETECT_FACES"]["PATH_NAMES"];
    fCONFIDENCES_FACES = std::stof(ini["PARAM_DETECT_FACES"]["CONFIDENCES"]);
    iMIN_SIZE_FACES = std::stoi(ini["PARAM_DETECT_FACES"]["MIN_SIZE"]);
    iMAX_SIZE_FACES = std::stoi(ini["PARAM_DETECT_FACES"]["MAX_SIZE"]);
    iGREEDY_RECTS_FACES = std::stoi(ini["PARAM_DETECT_FACES"]["GREEDY_RECTS"]);
    iDRAW_TEXT_FACES = std::stoi(ini["PARAM_DETECT_FACES"]["DRAW_TEXT"]);
    //vColors_FACES
    for(int i=0; i<iNUM_CLASSES_FACES; i++)
    {
        char buf_class_name[10];
        sprintf(buf_class_name, "COLOR_CLASS%d", i+1);
        string sCOLOR = ini["PARAM_DETECT_FACES"][buf_class_name];
        vColors_FACES.push_back(GetScalarCol(sCOLOR));
    }

    }
    catch(...)
    {
    printf("Err read ini!\n");
    exit(0);
    }
}

FaceDetection::~FaceDetection()
{
}

void FaceDetection::OneFace()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FaceDetection/OneFace.jpg");

    if(!frame.empty())
    {
        YoloDetector* detectorFaces = new YoloDetector(iCOMPUTE_DNN_CUDA_FACES, iNUM_CLASSES_FACES, sPATH_CFG_FACES, sPATH_WEIGHTS_FACES, sPATH_NAMES_FACES, fCONFIDENCES_FACES, iMIN_SIZE_FACES, iMAX_SIZE_FACES, iGREEDY_RECTS_FACES, iDRAW_TEXT_FACES, vColors_FACES);

        //Обработка кадра
        detectorFaces->detect(frame);

        vector<Rect> faces_rect;
        detectorFaces->getRects(faces_rect);

        if(!faces_rect.empty())
        {
            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с выделением лица
        detectorFaces->drawBoxes(frame);
        imshow("OneFace", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete detectorFaces;
    }

    QVERIFY(bOK);
}

void FaceDetection::ManyFace()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FaceDetection/ManyFace.jpg");

    if(!frame.empty())
    {
        YoloDetector* detectorFaces = new YoloDetector(iCOMPUTE_DNN_CUDA_FACES, iNUM_CLASSES_FACES, sPATH_CFG_FACES, sPATH_WEIGHTS_FACES, sPATH_NAMES_FACES, fCONFIDENCES_FACES, iMIN_SIZE_FACES, iMAX_SIZE_FACES, iGREEDY_RECTS_FACES, iDRAW_TEXT_FACES, vColors_FACES);

        //Обработка кадра
        detectorFaces->detect(frame);

        vector<Rect> faces_rect;
        detectorFaces->getRects(faces_rect);

        if(faces_rect.size() > 1)
        {
            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с выделением лица
        detectorFaces->drawBoxes(frame);
        imshow("ManyFace", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete detectorFaces;
    }

    QVERIFY(bOK);
}

void FaceDetection::CloseFace()
{
    bool bOK = false;

    //Кадр для тестирования
    Mat frame = imread("../../../inputdata/FaceDetection/CloseFace.jpg");

    if(!frame.empty())
    {
        YoloDetector* detectorFaces = new YoloDetector(iCOMPUTE_DNN_CUDA_FACES, iNUM_CLASSES_FACES, sPATH_CFG_FACES, sPATH_WEIGHTS_FACES, sPATH_NAMES_FACES, fCONFIDENCES_FACES, iMIN_SIZE_FACES, iMAX_SIZE_FACES, iGREEDY_RECTS_FACES, iDRAW_TEXT_FACES, vColors_FACES);

        //Обработка кадра
        detectorFaces->detect(frame);

        vector<Rect> faces_rect;
        detectorFaces->getRects(faces_rect);

        if(!faces_rect.empty())
        {
            bOK = true;
        }

        if(bOK)
        {
        //Вывод входного кадра с выделением лица
        detectorFaces->drawBoxes(frame);
        imshow("CloseFace", frame);
        waitKey(TIME_SLEEP_TEST_MS);
        }

        delete detectorFaces;
    }

    QVERIFY(bOK);
}

QTEST_APPLESS_MAIN(FaceDetection)

#include "tst_facedetection.moc"
