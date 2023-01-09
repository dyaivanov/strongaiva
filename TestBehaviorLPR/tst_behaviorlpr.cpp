#include <QtTest>

#include "BehaviorProcessor.h"
using namespace cv;

#define TIME_SLEEP_TEST_MS 2500
#define NAME_DUMP "../../../inputdata/dumpBehAI.bin"

class BehaviorLPR : public QObject
{
    Q_OBJECT

public:
    BehaviorLPR();
    ~BehaviorLPR();

//ТЕСТЫ
private slots:
    void test_BehaviorLPR();

};

BehaviorLPR::BehaviorLPR()
{
    QString qs = QDir::currentPath();
    qs += "/release";
    QDir::setCurrent(qs);

    cv::namedWindow("FACE_FEATURES");
    cv::moveWindow("FACE_FEATURES", 710, 0);

    cv::namedWindow("SKELETON_FEATURES");
    cv::moveWindow("SKELETON_FEATURES", 0, 0);
}

BehaviorLPR::~BehaviorLPR()
{

}

void BehaviorLPR::test_BehaviorLPR()
{
    //Считывание и обработка данных
    BehaviorProcessor beh;
    if(beh.LoadDumpData(NAME_DUMP))
        QVERIFY(true);

    //Визуализация
    Mat frame_face, frame_skeleton;
    beh.DrawFeaturesWindows(frame_face, frame_skeleton);
    imshow("FACE_FEATURES", frame_face);
    imshow("SKELETON_FEATURES", frame_skeleton);
    waitKey(TIME_SLEEP_TEST_MS);
}

QTEST_APPLESS_MAIN(BehaviorLPR)

#include "tst_behaviorlpr.moc"
