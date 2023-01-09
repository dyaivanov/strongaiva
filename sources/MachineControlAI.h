#ifndef MCONTROL_H
#define MCONTROL_H

#include <QSerialPort>
#include <QThread>
using namespace std;


//Класс работы с переф через виртуальный COM порт
class cMachineControl
{
private:
    string m_COM_NAME;
    QSerialPort serial;
    bool m_bOpen;

public:
    cMachineControl(const char *_COM_NAME);
    ~cMachineControl();

    bool IsOpenDevice();
    void SendEmergencyStop();
    void SendMachineOn();
    void SendCopterGoHome();
};

#endif // MCONTROL_H
