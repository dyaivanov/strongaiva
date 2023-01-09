#include "interactionsppr.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void diff(std::vector<float> in, std::vector<float>& out)
{
    out = std::vector<float>(in.size()-1);

    for(int i=1; i<in.size(); ++i)
        out[i-1] = in[i] - in[i-1];
}

void vectorElementsProduct(std::vector<float> a, std::vector<float> b, std::vector<float>& out)
{
    out = std::vector<float>(a.size());

    for(int i=0; i<a.size(); ++i)
        out[i] = a[i] * b[i];
}

void findIndicesLessThan(std::vector<float> in, float threshold, std::vector<int>& indices)
{
    for(int i=0; i<in.size(); ++i)
        if(in[i]<threshold)
            indices.push_back(i+1);
}

void selectElementsFromIndices(std::vector<float> in, std::vector<int> indices, std::vector<float>& out)
{
    for(int i=0; i<indices.size(); ++i)
        out.push_back(in[indices[i]]);
}

void selectElementsFromIndices(std::vector<int> in, std::vector<int> indices, std::vector<int>& out)
{
    for(int i=0; i<indices.size(); ++i)
        out.push_back(in[indices[i]]);
}

void signVector(std::vector<float> in, std::vector<int>& out)
{
    out = std::vector<int>(in.size());

    for(int i=0; i<in.size(); ++i)
    {
        if(in[i]>0)
            out[i]=1;
        else if(in[i]<0)
            out[i]=-1;
        else
            out[i]=0;
    }
}

void scalarProduct(float scalar, std::vector<float> in, std::vector<float>& out)
{
    out = std::vector<float>(in.size());

    for(int i=0; i<in.size(); ++i)
        out[i] = scalar * in[i];
}

void PeakFinder::findPeaks(std::vector<float> x0, std::vector<int>& peakInds, bool includeEndpoints, float extrema)
{
    int minIdx = distance(x0.begin(), min_element(x0.begin(), x0.end()));
    int maxIdx = distance(x0.begin(), max_element(x0.begin(), x0.end()));

    float sel = (x0[maxIdx]-x0[minIdx])/4.0;
    int len0 = x0.size();

    scalarProduct(extrema, x0, x0);

    std::vector<float> dx;
    diff(x0, dx);
    replace(dx.begin(), dx.end(), 0.0f, -PeakFinder::EPS);
    std::vector<float> dx0(dx.begin(), dx.end()-1);
    std::vector<float> dx0_1(dx.begin()+1, dx.end());
    std::vector<float> dx0_2;

    vectorElementsProduct(dx0, dx0_1, dx0_2);

    std::vector<int> ind;
    findIndicesLessThan(dx0_2, 0, ind); // Find where the derivative changes sign
    std::vector<float> x;
    float leftMin;
    int minMagIdx;
    float minMag;

    if(includeEndpoints)
    {
        //x = [x0(1);x0(ind);x0(end)];
        selectElementsFromIndices(x0, ind, x);
        x.insert(x.begin(), x0[0]);
        x.insert(x.end(), x0[x0.size()-1]);
        //ind = [1;ind;len0];
        ind.insert(ind.begin(), 1);
        ind.insert(ind.end(), len0);
        minMagIdx = distance(x.begin(), std::min_element(x.begin(), x.end()));
        minMag = x[minMagIdx];
        //std::cout<<"Hola"<<std::endl;
        leftMin = minMag;
    }
    else
    {
        selectElementsFromIndices(x0, ind, x);
        if(x.size()>2)
        {
            minMagIdx = distance(x.begin(), std::min_element(x.begin(), x.end()));
            minMag = x[minMagIdx];
            leftMin = x[0]<x0[0]?x[0]:x0[0];
        }
    }

    int len = x.size();

    if(len>2)
    {
        float tempMag = minMag;
        bool foundPeak = false;
        int ii;

        if(includeEndpoints)
        {
            // Deal with first point a little differently since tacked it on
            // Calculate the sign of the derivative since we tacked the first
            //  point on it does not neccessarily alternate like the rest.
            std::vector<float> xSub0(x.begin(), x.begin()+3);//tener cuidado subvector
            std::vector<float> xDiff;//tener cuidado subvector
            diff(xSub0, xDiff);

            std::vector<int> signDx;
            signVector(xDiff, signDx);

            if (signDx[0] <= 0) // The first point is larger or equal to the second
            {
                if (signDx[0] == signDx[1]) // Want alternating signs
                {
                    x.erase(x.begin()+1);
                    ind.erase(ind.begin()+1);
                    len = len-1;
                }
            }
            else // First point is smaller than the second
            {
                if (signDx[0] == signDx[1]) // Want alternating signs
                {
                    x.erase(x.begin());
                    ind.erase(ind.begin());
                    len = len-1;
                }
            }
        }

        //Skip the first point if it is smaller so we always start on maxima
        if ( x[0] >= x[1] )
            ii = 0;
        else
            ii = 1;

        //Preallocate max number of maxima
        float maxPeaks = ceil((float)len/2.0);
        std::vector<int> peakLoc(maxPeaks,0);
        std::vector<float> peakMag(maxPeaks,0.0);
        int cInd = 1;
        int tempLoc;

        while(ii < len)
        {
            ii = ii+1;//This is a peak
            //Reset peak finding if we had a peak and the next peak is bigger
            //than the last or the left min was small enough to reset.
            if(foundPeak)
            {
                tempMag = minMag;
                foundPeak = false;
            }

            //Found new peak that was lager than temp mag and selectivity larger
            //than the minimum to its left.

            if( x[ii-1] > tempMag && x[ii-1] > leftMin + sel )
            {
                tempLoc = ii-1;
                tempMag = x[ii-1];
            }

            //Make sure we don't iterate past the length of our vector
            if(ii == len)
                break; //We assign the last point differently out of the loop

            ii = ii+1; // Move onto the valley

            //Come down at least sel from peak
            if(!foundPeak && tempMag > sel + x[ii-1])
            {
                foundPeak = true; //We have found a peak
                leftMin = x[ii-1];
                peakLoc[cInd-1] = tempLoc; // Add peak to index
                peakMag[cInd-1] = tempMag;
                cInd = cInd+1;
            }
            else if(x[ii-1] < leftMin) // New left minima
                leftMin = x[ii-1];

        }

        // Check end point
        if(includeEndpoints)
        {
            if ( x[x.size()-1] > tempMag && x[x.size()-1] > leftMin + sel )
            {
                peakLoc[cInd-1] = len-1;
                peakMag[cInd-1] = x[x.size()-1];
                cInd = cInd + 1;
            }
            else if( !foundPeak && tempMag > minMag )// Check if we still need to add the last point
            {
                peakLoc[cInd-1] = tempLoc;
                peakMag[cInd-1] = tempMag;
                cInd = cInd + 1;
            }
        }
        else if(!foundPeak)
        {
            float minAux = x0[x0.size()-1]<x[x.size()-1]?x0[x0.size()-1]:x[x.size()-1];
            if ( x[x.size()-1] > tempMag && x[x.size()-1] > leftMin + sel )
            {
                peakLoc[cInd-1] = len-1;
                peakMag[cInd-1] = x[x.size()-1];
                cInd = cInd + 1;
            }
            else if( !tempMag >  minAux + sel)// Check if we still need to add the last point
            {
                peakLoc[cInd-1] = tempLoc;
                peakMag[cInd-1] = tempMag;
                cInd = cInd + 1;
            }
        }

        //Create output
        if( cInd > 0 )
        {
            std::vector<int> peakLocTmp(peakLoc.begin(), peakLoc.begin()+cInd-1);
            selectElementsFromIndices(ind, peakLocTmp, peakInds);
        }

    }
    //else
    //{
        //input signal length <= 2
    //}
}


/*
cFiltratorAM::cFiltratorAM(int _X_CNT, int _Y_SEC, int _start_posAM, int _szAM)
{
    m_X_CNT = _X_CNT;
    m_Y_SEC = _Y_SEC;
    m_start_posAM = _start_posAM;
    m_szAM = _szAM;

    m_b_need_send = false;

    memset(m_mas, 0, sizeof (m_mas));
    memset(m_times, 0, sizeof (m_times));
}
*/

cFiltratorExperts::cFiltratorExperts()
{
    m_X_CNT = 0;
    m_Y_SEC = 0;
    m_start_posFM = 10;
    m_szFM = 9;

    m_b_need_send = false;

    memset(m_mas, 0, sizeof (m_mas));
    memset(m_times, 0, sizeof (m_times));
}

void cFiltratorExperts::InitFiltrator(int _X_CNT, int _Y_SEC, int _start_posFM, int _szFM)
{
    m_X_CNT = _X_CNT;
    m_Y_SEC = _Y_SEC;
    m_start_posFM = _start_posFM;
    m_szFM = _szFM;

    m_b_need_send = false;

    memset(m_mas, 0, sizeof (m_mas));
    memset(m_times, 0, sizeof (m_times));
}

void cFiltratorExperts::SbrosNeedSend()
{
    m_b_need_send = false;
}

void cFiltratorExperts::AddNewFM(const sFiltrMessage &_FM)
{
    char mas[MAX_CNT_EVENTS];
    //копировать побайтово нужные пункты из FM
    memcpy(mas, (char*)&_FM + m_start_posFM, m_szFM);

    //printf("test\n");
    //for(int i=0; i<5; i++)
    //    //printf("%d ", _FM.bAGENTS[i]);
    //    printf("%d ", mas[i]);
    //printf("\ntest_end\n");

    //Взять текущее время (сек с 1900..)
    time_t tek_time;
    time(&tek_time);

    m_b_need_send = false;

    for(int i=0; i<m_szFM; i++)
    {
        if(mas[i]==0)
        {
            m_mas[i] = 0;
        }
        else //1
        {
            m_mas[i]++;
            if(m_mas[i] >= m_X_CNT && tek_time - m_times[i] >= m_Y_SEC)
            {
                m_times[i] = tek_time;
                m_b_need_send = true;
            }
        }
    }

    //printf("1\n");

    //test
    if(m_b_need_send)
    {
        //printf("2\n");

        char mas_res[MAX_CNT_EVENTS];
        memset(mas_res, 0, sizeof (mas_res));


        for(int i=0; i<m_szFM; i++)
        {
            if(m_mas[i] >= m_X_CNT)
            {
#ifdef DEBUG_FILTR_FM
                printf("1 ");
#endif
                mas_res[i] = 1;
            }
            else
            {
#ifdef DEBUG_FILTR_FM
                printf("0 ");
#endif
                mas_res[i] = 0;
            }
        }

#ifdef DEBUG_FILTR_FM
        printf("\n");
#endif

        m_FM = _FM;
        memcpy((char*)&m_FM + m_start_posFM, mas_res, m_szFM);
    }
}

bool cFiltratorExperts::IsNeedSend(sFiltrMessage &_FM)
{
    if(m_b_need_send)
    {
        //m_b_need_send = false;
        _FM = m_FM;
        return true;
    }

    return false;
}

cInteractionSPPR::cInteractionSPPR()
{
    memset(m_ExpertsData, 0, sizeof(m_ExpertsData));
    memset(m_filteredFEATURES, 0, sizeof(m_filteredFEATURES));

    m_usID = 0;
}

//Считывание мнений экспертов с БД
void cInteractionSPPR::ReadExpertsFromDB(const char *_f_name)
{
    FILE *f_in = NULL;
    fopen_s(&f_in, _f_name, "r");

    fscanf_s(f_in, "%d", &m_ExpertsN);
#ifdef DEBUG_READ_EXPERTS
    printf("experts = %d\n", m_ExpertsN);
#endif
    for(int i=0; i<m_ExpertsN; i++)
    {
        for(int j=0; j<CNT_FEATURES; j++)
        {
            fscanf_s(f_in, "%d", &m_ExpertsData[i][j]);
#ifdef DEBUG_READ_EXPERTS
            printf("%d ", m_ExpertsData[i][j]);
#endif
        }

#ifdef DEBUG_READ_EXPERTS
        printf("\n");
#endif
    }

    fclose(f_in);

    //Иниц фильтрации от повторов
    m_FiltratorAgents.InitFiltrator(1, 0, 10, m_ExpertsN);
}

void cInteractionSPPR::PreFiltrator(BehaviorProcessor &_beh)
{
    //ПЭС

    cDrawGraph *gr_PES = _beh.GetGraphPES();

    int nn = gr_PES->getNsize();
#ifdef DEBUG_INT_SPPR
    printf("cnt riadov: %d\n", nn);
#endif

    int mas_res_riad[CNT_FEATURES];
    memset(mas_res_riad, -1, sizeof(mas_res_riad));

    for(int j=0; j<nn; j++)
        {
        //print riad:
        int sz = gr_PES->m_v_Queues->size();
        if(sz <= 1)
            return;
#ifdef DEBUG_INT_SPPR
        printf("sz_%d\n", sz);
        for(int i=0; i<sz; i++)
             printf("%d ", gr_PES->m_v_Queues[j][i]);
        printf("\n");
#endif

        //cpy data
        vector<float> v_f;
        for(int i=0; i<sz; i++)
        v_f.push_back(gr_PES->m_v_Queues[j][i]);

        vector<int> v_out;
        PeakFinder::findPeaks(v_f, v_out, true);
#ifdef DEBUG_INT_SPPR
        printf("peaks:\n");
#endif
        int max_zn = -1;
        for(int i=0; i<(int)v_out.size(); i++)
        {
#ifdef DEBUG_INT_SPPR
            printf("%d(zn=%.1f) ", v_out[i], v_f[v_out[i]]);
#endif
            if(v_f[v_out[i]] > max_zn)
                max_zn = v_f[v_out[i]];
        }
#ifdef DEBUG_INT_SPPR
        printf("\n");
#endif
        mas_res_riad[j] = max_zn;
        }

#ifdef DEBUG_INT_SPPR
    for(int i=0; i<nn; i++)
    {
        printf("%d ", mas_res_riad[i]);
    }
    printf("\n");
#endif

    //запись в m_filteredFEATURES
    int nPES = nn;
    for(int i=0; i<nPES; i++)
        m_filteredFEATURES[i] = mas_res_riad[i];

    //Признаки

    cDrawGraph *gr_Priznak = _beh.GetGraphPriznak();

    nn = gr_Priznak->getNsize();
#ifdef DEBUG_INT_SPPR
    printf("cnt riadov: %d\n", nn);
#endif

    //int mas_res_riad[CNT_FEATURES];
    memset(mas_res_riad, -1, sizeof(mas_res_riad));

    for(int j=0; j<nn; j++)
        {
        //print riad:
        int sz = gr_Priznak->m_v_Queues->size();
        if(sz <= 1)
            return;
#ifdef DEBUG_INT_SPPR
        printf("sz_%d\n", sz);
        for(int i=0; i<sz; i++)
             printf("%d ", gr_Priznak->m_v_Queues[j][i]);
        printf("\n");
#endif

        //cpy data
        vector<float> v_f;
        for(int i=0; i<sz; i++)
        v_f.push_back(gr_Priznak->m_v_Queues[j][i]);

        vector<int> v_out;
        PeakFinder::findPeaks(v_f, v_out, true);
#ifdef DEBUG_INT_SPPR
        printf("peaks:\n");
#endif
        int max_zn = -1;
        for(int i=0; i<(int)v_out.size(); i++)
        {
#ifdef DEBUG_INT_SPPR
            printf("%d(zn=%.1f) ", v_out[i], v_f[v_out[i]]);
#endif
            if(v_f[v_out[i]] > max_zn)
                max_zn = v_f[v_out[i]];
        }
#ifdef DEBUG_INT_SPPR
        printf("\n");
#endif
        mas_res_riad[j] = max_zn;
        }

#ifdef DEBUG_INT_SPPR
    for(int i=0; i<nn; i++)
    {
        printf("%d ", mas_res_riad[i]);
    }
    printf("\n");
#endif

    for(int i=0; i<nn; i++)
        m_filteredFEATURES[i+nPES] = mas_res_riad[i];

#ifdef DEBUG_F_FEATURES
    //итоговый вывод m_filteredFEATURES
    printf("filteredFEATURES:\n");
    for(int i=0; i<CNT_FEATURES; i++)
        printf("%d ", m_filteredFEATURES[i]);
    printf("\n");
#endif
}

//Процедура голосования агентов
void cInteractionSPPR::AgentsVoting()
{
    bool bAgents[MAX_EXPERTS];

    memset(bAgents, 0, sizeof(bAgents));

    for(int i=0; i<m_ExpertsN; i++)
    {
        //Проверка мнения i-го агента
        bool bAgentTrigger = false;
        for(int j=0; j<CNT_FEATURES && !bAgentTrigger; j++)
            if(m_ExpertsData[i][j] != -1 && m_filteredFEATURES[j] != -1)
            {
                if(m_filteredFEATURES[j] > m_ExpertsData[i][j])
                {
                    bAgentTrigger = true;
                    bAgents[i] = 1;
                }
            }
    }

#ifdef DEBUG_AGENTS_VOTING
    printf("agents trigger:\n");
#endif
    for(int i=0; i<m_ExpertsN; i++)
    {
#ifdef DEBUG_AGENTS_VOTING
        printf("%d ", bAgents[i]);
#endif
    }
#ifdef DEBUG_AGENTS_VOTING
    printf("\n");
#endif

    //Фильтрация агентов от ложных сработок
    vector<bool> _agents;
    for(int i=0; i<m_ExpertsN; i++)
        _agents.push_back(bAgents[i]);
    sFiltrMessage FM(m_usID++, _agents);
    m_FiltratorAgents.AddNewFM(FM);
}

void cInteractionSPPR::process(BehaviorProcessor &_beh)
{
    //Предварительная фильтрация временных рядов ПЭС
    PreFiltrator(_beh);

    //Голосование агентов
    AgentsVoting();
}

bool cInteractionSPPR::isAgentsVotingOK()
{
    sFiltrMessage FM;
    if(m_FiltratorAgents.IsNeedSend(FM))
    {
#ifdef DEBUG_AGENTS_VOTING_FILTR
        printf("agents trigger filtr:\n");
        for(int i=0; i<m_ExpertsN; i++)
            printf("%d ", FM.bAGENTS[i]);
        printf("\n");
#endif
        bool bTrigged = true;
        for(int i=0; i<m_ExpertsN; i++)
            if(FM.bAGENTS[i] == 0)
                bTrigged = false;

        if(bTrigged)
            return true;
    }

    return false;
}
