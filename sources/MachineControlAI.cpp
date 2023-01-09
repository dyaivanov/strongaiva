#include "MachineControlAI.h"

//MCONTROL
cMachineControl::cMachineControl(const char *_COM_NAME)
{
    m_COM_NAME = _COM_NAME;
    m_bOpen = true;

    serial.setPortName(m_COM_NAME.c_str());

    serial.setBaudRate(9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if (!serial.open(QIODevice::ReadWrite))
    {
        //printf("err open COM!\n");
        m_bOpen = false;
    }

    serial.setDataTerminalReady(true);

    QThread::msleep(2000);

    if(!serial.isWritable())
    {
       //printf("err init COM!\n");
       m_bOpen = false;
    }
    else
    {
        //printf("ok!\n");
        m_bOpen = true;
    }
}

cMachineControl::~cMachineControl()
{
    serial.close();
}

bool cMachineControl::IsOpenDevice()
{
    if(m_bOpen)
        return true;
    return false;
}

void cMachineControl::SendEmergencyStop()
{
    char command_off[4] = "A1S";
    serial.write(command_off, 3);
    serial.waitForBytesWritten();
    QThread::msleep(100);
}

void cMachineControl::SendMachineOn()
{
    char command_on[4] = "A0S";
    serial.write(command_on, 3);
    serial.waitForBytesWritten();
    QThread::msleep(100);
}

void cMachineControl::SendCopterGoHome()
{
    char command_on[5] = "C01#";
    serial.write(command_on, 4);
    serial.waitForBytesWritten();
    QThread::msleep(100);
}
