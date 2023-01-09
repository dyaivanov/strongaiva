//---------------------------------------------------------------------------
//#include "stdafx.h"

//#pragma hdrstop

#include "SpeedReg.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)
//---------------------------------------------------------------------------

CPidRegul::CPidRegul(double _Kp0, double _Ki0, double _Kd0, double _dt_s)
{
    Kp = _Kp0;
    Ki = _Ki0;
    Kd = _Kd0;
    dt_s = _dt_s;

    prevInput = -11111111.;
    integral = 0.;
    output = 0.;

    spd_lim = 16000; //18.03.2020
}

void CPidRegul::SbrosPID()
{
    prevInput = -11111111.;
    integral = 0.;
    output = 0.;

    //spd_lim = 16000; //18.03.2020
}

//18.03.2020
void CPidRegul::SetLimSpd(int _spd_lim)
{
    spd_lim = _spd_lim;
}

void CPidRegul::SetPIDParam(double _Kp, double _Ki, double _Kd)
{
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;

    //03.03.2020
    //prevInput = 0.; //10.03.2020
    //integral = 0.;
}

long double CPidRegul::GetIntegral() //19.04.2020
{
    return integral;
}

void CPidRegul::SetIntegral(long double _integral) //19.04.2020
{
    integral = _integral;
}

double CPidRegul::PIDregulating(double input)
{
      long double error = 0./*setpoint*/ - input;           // ошибка регулирования
      long double delta_input = prevInput - input;    // изменение входного сигнала

      if(prevInput == -11111111.)
          delta_input=0;

      prevInput = input;
      output = 0.;
      long double lin = (long double)error * Kp;                  // пропорционально ошибке регулирования
      long double dif  = (long double)delta_input * Kd / dt_s;    // дифференциальная составляющая
      integral += (long double)error * Ki * dt_s;        // расчёт интегральной составляющей
      // тут можно ограничить интегральную составляющую!
      if(integral > spd_lim) //20.04.2020
          integral = spd_lim;
      if(integral < -spd_lim)
          integral = -spd_lim;


      output =lin + dif + integral;                            // прибавляем интегральную составляющую

      //printf("integral = %.4llf\n", integral); //19.04.2020
      //printf("E = %.4llf, L = %.4llf, D = %.4llf, integral = %.4llf, output = %.4llf\n",error, lin, dif, integral, output);

      //output = constrain(output, pidMin, pidMax);   // ограничиваем выход
      if(output < -spd_lim) //14k
          output = -spd_lim;
      if(output > spd_lim)
          output = spd_lim;

      return -output;
}


