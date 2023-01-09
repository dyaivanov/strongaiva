#ifndef CINTERACTIONSPPR_H
#define CINTERACTIONSPPR_H

#include <vector>
#include <time.h>

#include "BehaviorProcessor.h"

namespace PeakFinder {
    const float EPS = 2.2204e-16f;

    /*
        Inputs
        x0: input signal
        extrema: 1 if maxima are desired, -1 if minima are desired
        includeEndpoints - If true the endpoints will be included as possible extrema otherwise they will not be included
        Output
        peakInds: Indices of peaks in x0
    */
    void findPeaks(std::vector<float> x0, std::vector<int>& peakInds, bool includeEndpoints=true, float extrema=1);
}

//Максимальное количество экспертов
#define MAX_EXPERTS 10

//Структура отфильтрованного сообщения ПЭС от экспертов для агентов
#pragma pack(push, 1)
struct sFiltrMessage
{
    //19.12.2022
    unsigned short usID;

    //Время события
    time_t rawtime;

    //add 19.12.2022
    bool bAGENTS[MAX_EXPERTS];

    sFiltrMessage(int _iID, vector<bool> &_experts)
    {
        usID = _iID;

        time(&rawtime);

        memset(bAGENTS, 0, sizeof(bAGENTS));

        int n = _experts.size();
        for(int i=0; i<n; i++)
            bAGENTS[i] = _experts[i];
    }

    sFiltrMessage()
    {
        usID = 0;

        rawtime = 0;

        memset(bAGENTS, 0, sizeof(bAGENTS));
    }
};
#pragma pack(pop)


#define MAX_CNT_EVENTS 50
//#define DEBUG_FILTR_FM

//Фильтрация сообщений AM от повторов
class cFiltratorExperts
{
private:
    int m_X_CNT;
    int m_Y_SEC;
    int m_start_posFM;
    int m_szFM;
    int m_mas[MAX_CNT_EVENTS];
    time_t m_times[MAX_CNT_EVENTS];
    bool m_b_need_send;
    sFiltrMessage m_FM;

public:
    //_X_CNT - сработок
    //_Y_SEC - секунд защиты дублирования
    //_start_posAM - начальная позиция байтовой последовательности в sFiltrMessage
    //_szFM - размер байтовой последовательности в sFiltrMessage
    //cFiltratorExperts(int _X_CNT, int _Y_SEC, int _start_posFM, int _szFM);
    cFiltratorExperts();
    void InitFiltrator(int _X_CNT, int _Y_SEC, int _start_posFM, int _szFM);

    void SbrosNeedSend();

    //Добавить новое сырое сообщение
    void AddNewFM(const sFiltrMessage &_FM);

    //Вывод отфильтрованного набора для отправки
    bool IsNeedSend(sFiltrMessage &_FM);
};

//Количество признаков ПЭС
#define CNT_FEATURES 9

//Вывод отладочных данных
//#define DEBUG_INT_SPPR
//#define DEBUG_READ_EXPERTS
//#define DEBUG_F_FEATURES
//#define DEBUG_AGENTS_VOTING
//#define DEBUG_AGENTS_VOTING_FILTR

class cInteractionSPPR
{
private:
    unsigned short m_usID;
    int m_ExpertsN;
    int m_ExpertsData[MAX_EXPERTS][CNT_FEATURES];
    cFiltratorExperts m_FiltratorAgents;

    int m_filteredFEATURES[CNT_FEATURES];

    //Предварительная фильтрация временных рядов ПЭС
    //Заполняется m_filteredFEATURES, вызов в ф-ции process
    void PreFiltrator(BehaviorProcessor &_beh);

    //Процедура голосования агентов (с учетом доп фильтрации от ложных срабатываний)
    void AgentsVoting();

public:
    cInteractionSPPR();

    //Считывание мнений экспертов с БД
    void ReadExpertsFromDB(const char *_f_name);

    //Обработка
    void process(BehaviorProcessor &_beh);

    //если агенты договорились - можно производить действие
    bool isAgentsVotingOK();
};

#endif // CINTERACTIONSPPR_H
