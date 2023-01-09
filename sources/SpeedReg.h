//---------------------------------------------------------------------------

#ifndef SpeedRegH
#define SpeedRegH

//#include <stdio>
#include <vector>
using namespace std;
#include <math.h>


//Класс ПИД регулятора для управления приводами
class CPidRegul //06.07.2016
{
private:
    long double Kp, Ki, Kd, dt_s;
    long double prevInput, integral, output;
    int spd_lim; //18.03.2020

public:
    long double GetIntegral(); //19.04.2020
    void SetIntegral(long double _integral); //19.04.2020

    void SetLimSpd(int _spd_lim); //18.03.2020
    void SbrosPID();
    void SetPIDParam(double _Kp, double _Ki, double _Kd);
    CPidRegul(double _Kp0, double _Ki0, double _Kd0, double _dt_s);
    double PIDregulating(double _E);
};


//Класс усреднения переменной 25.04.2016
class CMedVar
{
private:
    //vector<int> mas;
	int len_mas;
    int time_inert; //20.01.2018

public:
    vector<int> mas;

	int FullMas()
	{
		return mas.size();
	}

	void SetLenMas(int len)
	{
		len_mas = len;
	}

    int GetSr()
	{
		int sz = mas.size();
		if (sz >= 1)
		{
			int res = 0;
			for (int i = 0; i < sz; i++)
				res += mas[i];
			return res / sz;
		}

		return 0;
	}

    //19.01.2018
    int GetMNKNext()
    {
        int n = mas.size();

        if(n > 50) //хотяб 1сек ведем (50гц)
            {

            double sumx = 0;
            double sumy = 0;
            double sumx2 = 0;
            double sumxy = 0;
            for(int i=0; i<n; i++)
            {
                sumx += i;
                sumy += mas[i];
                sumx2 += i * i;
                sumxy += i * mas[i];
           //     printf("%d ", mas[i]);
            }
           // printf("___");
            double a = 0;
            double b = 0;

            if(n*sumx2 == sumx*sumx)
                return 0;

            a = (n*sumxy - (sumx*sumy)) / (n*sumx2 - sumx*sumx);
            b = (sumy - a*sumx) / n;

            double ret = a*(n /*+ time_inert*/) + b; //20.09.2018
           // time_inert++; //20.01.2018
           // printf("ret=%.1f\n", ret);
            return ret;
            }


        return 0; //а тут снимаем скорость! если нет данных для построения траектории 20.01.2018
    }

	void PushNewZn(int zn)
	{
        time_inert = 0; //20.01.2018

		mas.push_back(zn);
		if (mas.size() > len_mas)
			mas.erase(mas.begin());
	}

    int GetBeginZn()
    {
        return mas[0];
    }

	void Clear() //16.06.2016
	{
        time_inert = 0; //20.01.2018
		mas.clear();
	}

};


class CMedVarFloat
{
private:
    //vector<double> mas;
    int len_mas;
    int time_inert; //20.01.2018

public:
    vector<double> mas; //12.03.2019

    int FullMas()
    {
        return mas.size();
    }

    void SetLenMas(int len)
    {
        len_mas = len;
    }

    double GetSr()
    {
        int sz = mas.size();
        if (sz >= 1)
        {
            double res = 0;
            for (int i = 0; i < sz; i++)
                res += mas[i];
            return res / (double)sz;
        }

        return 0;
    }

    //04.03.2020
    bool GetMNKNextN(const int cnt_frame, double &_zn)
    {
        int n = mas.size();

        if(n < len_mas)
            return false;

        double sumx = 0;
        double sumy = 0;
        double sumx2 = 0;
        double sumxy = 0;
        for(int i=0; i<n; i++)
        {
            sumx += i;
            sumy += mas[i];
            sumx2 += i * i;
            sumxy += i * mas[i];
            //printf("%d ", mas[i]);
        }
        //printf("___");
        double a = 0;
        double b = 0;

        if(n*sumx2 == sumx*sumx)
            return false;

        a = (n*sumxy - (sumx*sumy)) / (n*sumx2 - sumx*sumx);
        b = (sumy - a*sumx) / n;

        _zn = a*(n + cnt_frame) + b; //20.09.2018
        //time_inert++; //20.01.2018
        //printf("ret=%.1f\n", ret);

        return true;
    }

    //19.01.2018
    double GetMNKNext() //12.03.2019 !!!! bilo int
    {
        int n = mas.size();

        if(n > 50) //хотяб 1сек ведем (50гц)
            {

            double sumx = 0;
            double sumy = 0;
            double sumx2 = 0;
            double sumxy = 0;
            for(int i=0; i<n; i++)
            {
                sumx += i;
                sumy += mas[i];
                sumx2 += i * i;
                sumxy += i * mas[i];
           //     printf("%d ", mas[i]);
            }
           // printf("___");
            double a = 0;
            double b = 0;

            if(n*sumx2 == sumx*sumx)
                return 0;

            a = (n*sumxy - (sumx*sumy)) / (n*sumx2 - sumx*sumx);
            b = (sumy - a*sumx) / n;

            double ret = a*(n /*+ time_inert*/) + b; //20.09.2018
           // time_inert++; //20.01.2018
           // printf("ret=%.1f\n", ret);
            return ret;
            }


        return 0; //а тут снимаем скорость! если нет данных для построения траектории 20.01.2018
    }

    void PushNewZn(double zn)
    {
        time_inert = 0; //20.01.2018

        mas.push_back(zn);
        if (mas.size() > len_mas)
            mas.erase(mas.begin());
    }

    void Clear() //16.06.2016
    {
        time_inert = 0; //20.01.2018
        mas.clear();
    }

};
//---------------------------------------------------------------------------
#endif
