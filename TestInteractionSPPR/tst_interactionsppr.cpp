#include <QtTest>

#include "BehaviorProcessor.h"
#include "interactionsppr.h"
using namespace cv;

#define TIME_SLEEP_TEST_MS 2500
#define NAME_DUMP "../../../inputdata/dumpBehAI.bin"

class InteractionSPPR : public QObject
{
    Q_OBJECT

public:
    InteractionSPPR();
    ~InteractionSPPR();

//ТЕСТЫ
private slots:
    void test_InteractionSPPR();

};

InteractionSPPR::InteractionSPPR()
{
    QString qs = QDir::currentPath();
    qs += "/release";
    QDir::setCurrent(qs);

    //cv::namedWindow("FACE_FEATURES");
    //cv::moveWindow("FACE_FEATURES", 710, 0);
    //cv::namedWindow("SKELETON_FEATURES");
    //cv::moveWindow("SKELETON_FEATURES", 0, 0);
}

InteractionSPPR::~InteractionSPPR()
{
}

void InteractionSPPR::test_InteractionSPPR()
{
    //Считывание и обработка данных
    BehaviorProcessor beh;
    if(beh.LoadDumpData(NAME_DUMP))
        QVERIFY(true);

    //Обработка агентами по мнению экспертов временных рядов особенностей поведения
    cInteractionSPPR interSPPR;

    //Заугрузка мнений экспертов
    interSPPR.ReadExpertsFromDB("../../../inputdata/expertsTaskMachine.dat");

    //Запуск процесса обработки
    interSPPR.process(beh);

    //если агенты договорились
    if(interSPPR.isAgentsVotingOK())
        QVERIFY(true);
    else
        QVERIFY(false);

    //Визуализация
    //Mat frame_face, frame_skeleton;
    //beh.DrawFeaturesWindows(frame_face, frame_skeleton);
    //imshow("FACE_FEATURES", frame_face);
    //imshow("SKELETON_FEATURES", frame_skeleton);
    //waitKey(TIME_SLEEP_TEST_MS);
}

QTEST_APPLESS_MAIN(InteractionSPPR)

#include "tst_interactionsppr.moc"
