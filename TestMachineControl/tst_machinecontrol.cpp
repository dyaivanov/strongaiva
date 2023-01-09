#include <QtTest>

#include "MachineControlAI.h"
#include <QThread>

#define TIME_SLEEP_TEST_MS 2000

class MachineControl : public QObject
{
    Q_OBJECT

public:
    MachineControl();
    ~MachineControl();

private:
    cMachineControl *MC;

//ТЕСТЫ
private slots:
    void EmergencyStop();
    void OnMachine();
    void CopterGoHome();

};

MachineControl::MachineControl()
{
    MC = new cMachineControl("COM3");
}

MachineControl::~MachineControl()
{
    delete MC;
}

void MachineControl::EmergencyStop()
{
    if(MC->IsOpenDevice())
        {
        MC->SendEmergencyStop();
        //QThread::msleep(TIME_SLEEP_TEST_MS);
        QTest::qSleep(TIME_SLEEP_TEST_MS);
        }
    else
        QVERIFY(0);
}

void MachineControl::OnMachine()
{
    if(MC->IsOpenDevice())
        {
        MC->SendMachineOn();
        }
    else
        QVERIFY(0);
}

void MachineControl::CopterGoHome()
{
    if(MC->IsOpenDevice())
        {
        MC->SendCopterGoHome();
        }
    else
        QVERIFY(0);
}

QTEST_APPLESS_MAIN(MachineControl)

#include "tst_machinecontrol.moc"
