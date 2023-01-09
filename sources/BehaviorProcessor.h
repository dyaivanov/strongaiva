#ifndef BEHAVIORPROCESSOR_H
#define BEHAVIORPROCESSOR_H

#include <deque>
#include "Skeleton.h"
#include "faceprocessor.h"

//05.01.2022
#include <fstream>

using namespace std;

#define MAX_QUEUES 50
class cDrawGraph
{
private:
    int m_n_size;
    string m_names[MAX_QUEUES];
    int m_types_graph[MAX_QUEUES];
    int m_frames_sz;

public:
    int getNsize()
    {
        return m_n_size;
    }
    QList<int> m_v_Queues[MAX_QUEUES];

public:
    //05.01.2023
    void WriteToFile(FILE *_f_out)
    {
        /*
        fwrite((char*)&m_n_size, sizeof(m_n_size), 1, _f_out);
        //strings
        for(int i=0; i<MAX_QUEUES; i++)
        {
            int len = m_names[i].size();
            fwrite((char*)&len, sizeof(len), 1, _f_out);
            char buf[100];
            memcpy(buf, m_names[i].c_str(), len);
            fwrite((char*)&buf, len, 1, _f_out);
        }
        fwrite((char*)&m_types_graph, sizeof(m_types_graph), 1, _f_out);
        fwrite((char*)&m_frames_sz, sizeof(m_frames_sz), 1, _f_out);
        */
        //list
        for(int i=0; i<MAX_QUEUES; i++)
        {
            int len = m_v_Queues[i].size();
            fwrite((char*)&len, sizeof(len), 1, _f_out);
            for(int j=0; j<len; j++)
            {
                int el = m_v_Queues[i].at(j);
                fwrite((char*)&el, sizeof(el), 1, _f_out);
            }
        }
    }
    //
    void ReadFromFile(FILE *_f_in)
    {
        for(int i=0; i<MAX_QUEUES; i++)
        {
            int len = 0; //m_v_Queues[i].size();
            m_v_Queues[i].clear();
            fread((char*)&len, sizeof(len), 1, _f_in);
            for(int j=0; j<len; j++)
            {
                int el = 0; //m_v_Queues[i].at(j);
                fread((char*)&el, sizeof(el), 1, _f_in);
                m_v_Queues[i].push_back(el);
            }
        }
    }

public:   
    cDrawGraph(int _n_size, const string *_names, const int *_types_graph, int _frames_sz)
    {
        m_n_size = _n_size;
        for(int i=0; i<m_n_size; i++)
        {
            m_names[i] = _names[i];
            m_types_graph[i] = _types_graph[i];
        }

        m_frames_sz = _frames_sz;
    }

    ~cDrawGraph()
    {
        ClearQueues();
    }

    void ClearQueues()
    {
        for(int i=0; i<m_n_size; i++)
            m_v_Queues[i].clear();
    }

    //удалить одиночные всплески в временных рядах
    void NoiseFilter(int _num_features)
    {
        if(_num_features >= 0 && _num_features < m_n_size)
        {
            int n = m_v_Queues[_num_features].size();
            for(int i=1; i<n-1; i++)
                if(m_v_Queues[_num_features][i] == m_types_graph[_num_features] && m_v_Queues[_num_features][i-1] == 0 && m_v_Queues[_num_features][i+1] == 0)
                    m_v_Queues[_num_features][i] = 0;
        }
    }

    void addAction(int _num_features, int _value)
    {
        if(_num_features >= 0 && _num_features < m_n_size)
        {
            m_v_Queues[_num_features].push_front(_value);
            if (m_v_Queues[_num_features].size() > m_frames_sz)
                {
                m_v_Queues[_num_features].pop_back();
                }
        }
    }

    void Draw(cv::Mat &input, cv::Point start_pos, cv::Scalar color_back)
    {
        /*
        if (skeletonInvisibilityTime > 5)
        {
            cv::putText(input, "Человек за пределами области обработки", cv::Point(20, 60), 3, 2, cv::Scalar(255, 0, 0, 255), 3);
            return;
        }
        */

        int sx = 300;
        int sy = 50;
        int stepY = 60;
        int height = 30;
        int step_pix = 2; //02.08.2022

        for (int i = 0; i < m_n_size; i++)
        {
            cv::rectangle(input, cv::Point(start_pos.x + 10, start_pos.y + sy + i * stepY - height - 6), cv::Point(start_pos.x + sx, start_pos.y + sy + i * stepY + 6), color_back, cv::FILLED);
            cv::line(input, cv::Point(start_pos.x + 10, start_pos.y + sy + i * stepY - height - 6), cv::Point(start_pos.x + sx + m_frames_sz * 5, start_pos.y + sy + i * stepY - height - 6), cv::Scalar(255, 255, 255), 1);
            cv::putText(input, m_names[i], cv::Point(start_pos.x + 20, start_pos.y + sy + i * stepY), 3, 1,  cv::Scalar(255, 255, 255, 255), 2);
            cv::line(input, cv::Point(start_pos.x + 10, start_pos.y + sy + i * stepY + 6), cv::Point(start_pos.x + sx + m_frames_sz * 5, start_pos.y + sy + i * stepY + 6), cv::Scalar(255, 255, 255), 1);
        }


        for(int f=0; f<m_n_size; f++)
        {

        for (int i = 0; i < (int)m_v_Queues[f].size() - 1; i++)
            {
                float v1 = (float)m_v_Queues[f][i] / m_types_graph[f];
                float v2 = (float)m_v_Queues[f][i + 1] / m_types_graph[f];
                cv::Scalar color(0, 255, 0);
                if (v2 > 0.3f) {
                    color[0] = 0;
                    color[1] = 255;
                    color[2] = 255;
                }
                if (v2 > 0.7f) {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 255;
                }
                cv::line(input, cv::Point(start_pos.x + sx + i * step_pix, start_pos.y + sy + f * stepY - v1 * height), cv::Point(start_pos.x + sx + (i + 1) * step_pix, start_pos.y + sy + f * stepY - v2 * height), color, 2);
            }

        }
    }


};

//25.10.2022
struct sParamsBEH
{
    //Гнев
    int iAnger_MouthOpen;
    int iAnger_LipsClosed;
    int iAngerisEyebrowsLowered;

    //Страх
    int iFearEyebrowsRaised;
    int iFearMouthOpen;
    int iFearHeadDown;
    int iFearFaceDown;
    int iFearFrequentLookingAround;

    //Сильное волнение
    int iExcitementFacepalm;
    int iExcitementHeadDown;
    int iExcitementShiftyLook;
    int iExcitementFrequentBlinking;
    int iExcitementFrequentLookingAround;

    //Priznak
    ////////////////////////////

    //Ухудшение состояния ССС
    int iSSSFear;
    int iSSSExcitement;
    int iSSSHandsChest;

    //Ухудшение состояния ЦНС
    int iCNSFear;
    int iCNSExcitement;
    int iCNSTorsoTilt;

    //Сонливость
    int iSleepingTorsoTilt;
    int iSleepingFaceTilt;
    int iSleepingYawning;

    //Панические атаки
    int iPanicAttacksShiftyLook;
    int iPanicAttacksExcitement;
    int iPanicAttacksMouthOpen;

    //Алкогольное опьянение
    int iAlcoholPoisoningFaceTilt;
    int iAlcoholPoisoningSleeping;

    bool IsIdentically(const sParamsBEH &_param)
    {
        return
                //Гнев
                iAnger_MouthOpen == _param.iAnger_MouthOpen &&
                iAnger_LipsClosed == _param.iAnger_LipsClosed &&
                iAngerisEyebrowsLowered == _param.iAngerisEyebrowsLowered &&

                //Страх
                iFearEyebrowsRaised == _param.iFearEyebrowsRaised &&
                iFearMouthOpen == _param.iFearMouthOpen &&
                iFearHeadDown == _param.iFearHeadDown &&
                iFearFaceDown == _param.iFearFaceDown &&
                iFearFrequentLookingAround == _param.iFearFrequentLookingAround &&

                //Сильное волнение
                iExcitementFacepalm == _param.iExcitementFacepalm &&
                iExcitementHeadDown == _param.iExcitementHeadDown &&
                iExcitementShiftyLook == _param.iExcitementShiftyLook &&
                iExcitementFrequentBlinking == _param.iExcitementFrequentBlinking &&
                iExcitementFrequentLookingAround == _param.iExcitementFrequentLookingAround &&

                //Priznak
                ////////////////////////////

                //Ухудшение состояния ССС
                iSSSFear == _param.iSSSFear &&
                iSSSExcitement == _param.iSSSExcitement &&
                iSSSHandsChest == _param.iSSSHandsChest &&

                //Ухудшение состояния ЦНС
                iCNSFear == _param.iCNSFear &&
                iCNSExcitement == _param.iCNSExcitement &&
                iCNSTorsoTilt == _param.iCNSTorsoTilt &&

                //Сонливость
                iSleepingTorsoTilt == _param.iSleepingTorsoTilt &&
                iSleepingFaceTilt == _param.iSleepingFaceTilt &&
                iSleepingYawning == _param.iSleepingYawning &&

                //Панические атаки
                iPanicAttacksShiftyLook == _param.iPanicAttacksShiftyLook &&
                iPanicAttacksExcitement == _param.iPanicAttacksExcitement &&
                iPanicAttacksMouthOpen == _param.iPanicAttacksMouthOpen &&

                //Алкогольное опьянение
                iAlcoholPoisoningFaceTilt == _param.iAlcoholPoisoningFaceTilt &&
                iAlcoholPoisoningSleeping == _param.iAlcoholPoisoningSleeping;
    }
};

#define FRAMES 20 * 10 // 20 sec * 10 fps
//
class BehaviorProcessor
{
private:
    sParamsBEH m_params; //25.10.2022

    bool isSkeletonVisible;
    int skeletonInvisibilityTime;

    cDrawGraph *m_graph_Skeleton;
    cDrawGraph *m_graph_Face;
    cDrawGraph *m_graph_PES;
    cDrawGraph *m_graph_Priznak;

    void clearAllQueues();
    //
    bool isFrequentLookingAround();
    bool isShiftyLook();
    bool isFrequentBlinking();
    bool isYawning();
    //
    bool isDeath();

public:
    BehaviorProcessor();
    ~BehaviorProcessor();

    int GetAlert()
    {
        return 0;
    }

    //04.01.2023
    bool SaveDumpData(const char *_f_name);
    bool LoadDumpData(const char *_f_name);

    cDrawGraph *GetGraphPES()
    {
        return m_graph_PES;
    }

    cDrawGraph *GetGraphPriznak()
    {
        return m_graph_Priznak;
    }

    //25.10.2022
    void updateParams(const sParamsBEH &_params);

    void update(Skeleton& skeleton, FaceProcessor& faceProcessor);
    void DrawFeaturesWindows(cv::Mat &_frame_face, cv::Mat &_frame_skeleton); //26.09.2022
};

#endif // BEHAVIORPROCESSOR_H
