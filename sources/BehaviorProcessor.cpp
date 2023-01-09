#include "BehaviorProcessor.h"

BehaviorProcessor::BehaviorProcessor()
{
    std::string *featuresSkeleton;
    std::string* featuresFace;
    std::string* featuresPES;
    std::string* featuresPriznak;

    //SKELETON
    //========
    int n_featuresSkeleton = 6;
    featuresSkeleton = new string[n_featuresSkeleton];
    featuresSkeleton[0] = "Наклон туловища"; //+
    featuresSkeleton[1] = "Плечи подняты"; //+
    featuresSkeleton[2] = "Руки тремор"; //-
    featuresSkeleton[3] = "Руки к груди"; //+
    featuresSkeleton[4] = "Подняты руки"; //+
    featuresSkeleton[5] = "Рука к лицу"; //+
    //
    int *types_graphSkeleton = new int[n_featuresSkeleton];
    types_graphSkeleton[0] = 90;
    types_graphSkeleton[1] = 1;
    types_graphSkeleton[2] = 1;
    types_graphSkeleton[3] = 1;
    types_graphSkeleton[4] = 2;
    types_graphSkeleton[5] = 1;
    //
    m_graph_Skeleton = new cDrawGraph(n_featuresSkeleton, featuresSkeleton, types_graphSkeleton, FRAMES);
    //
    delete[] featuresSkeleton;
    delete[] types_graphSkeleton;


    //FACE
    //========
    int n_featuresFace = 18;
    featuresFace = new std::string[n_featuresFace];
    featuresFace[0] = "Наклон головы"; //+
    featuresFace[1] = "Голова опущена"; //+
    featuresFace[2] = "Голова влево"; //+
    featuresFace[3] = "Голова вправо"; //+
    featuresFace[4] = "Частое оглядывание"; //+
    featuresFace[5] = "Брови приподняты"; //+
    featuresFace[6] = "Сужена глазная щель"; //-<2
    featuresFace[7] = "Взгляд в камеру"; //+
    featuresFace[8] = "Взгляд в пол"; //+
    featuresFace[9] = "Взгляд влево"; //+
    featuresFace[10] = "Взгляд вправо"; //+
    featuresFace[11] = "Бегающий взгляд"; //+
    featuresFace[12] = "Однократное моргание"; //+
    featuresFace[13] = "Учащенное моргание"; //+
    featuresFace[14] = "Рот раскрыт"; //+
    featuresFace[15] = "Зевание"; //+
    featuresFace[16] = "Губы сомкнуты"; //+
    featuresFace[17] = "Распахнуты глаза"; //-
    //
    //
    int *types_graphFace = new int[n_featuresFace];
    types_graphFace[0] = 90;
    types_graphFace[1] = 1;
    types_graphFace[2] = 1;
    types_graphFace[3] = 1;
    types_graphFace[4] = 1;
    types_graphFace[5] = 1;
    types_graphFace[6] = 1;
    types_graphFace[7] = 1;
    types_graphFace[8] = 1;
    types_graphFace[9] = 1;
    types_graphFace[10] = 1;
    types_graphFace[11] = 1;
    types_graphFace[12] = 1;
    types_graphFace[13] = 1;
    types_graphFace[14] = 1;
    types_graphFace[15] = 1;
    types_graphFace[16] = 1;
    types_graphFace[17] = 1;
    //
    m_graph_Face = new cDrawGraph(n_featuresFace, featuresFace, types_graphFace, FRAMES);
    //
    delete[] featuresFace;
    delete[] types_graphFace;


    //PES
    //===
    int n_featuresPES = 3;
    featuresPES = new std::string[n_featuresPES];
    featuresPES[0] = "Гнев";
    featuresPES[1] = "Страх";
    featuresPES[2] = "Сильное волнение";
    //
    int *types_featuresPES = new int[n_featuresPES];
    types_featuresPES[0] = 100;
    types_featuresPES[1] = 100;
    types_featuresPES[2] = 100;
    //
    m_graph_PES = new cDrawGraph(n_featuresPES, featuresPES, types_featuresPES, FRAMES);
    //
    delete[] featuresPES;
    delete[] types_featuresPES;


    //Priznak
    //=======
    int n_featuresPriznak = 6;
    featuresPriznak = new std::string[n_featuresPriznak];
    featuresPriznak[0] = "1. Внезапная смерть/потеря сознания";
    featuresPriznak[1] = "2. Ухудшеине состояния ССС";
    featuresPriznak[2] = "3. Ухудшение состояния ЦНС";
    featuresPriznak[3] = "4. Сонливость";
    featuresPriznak[4] = "5. Панические атаки";
    featuresPriznak[5] = "6. Последствия алкогольного отравления";
    //
    int *types_featuresPriznak = new int[n_featuresPriznak];
    types_featuresPriznak[0] = 1;
    types_featuresPriznak[1] = 100;
    types_featuresPriznak[2] = 100;
    types_featuresPriznak[3] = 100;
    types_featuresPriznak[4] = 100;
    types_featuresPriznak[5] = 100;
    //
    m_graph_Priznak = new cDrawGraph(n_featuresPriznak, featuresPriznak, types_featuresPriznak, FRAMES);
    //
    delete[] featuresPriznak;
    delete[] types_featuresPriznak;

}

BehaviorProcessor::~BehaviorProcessor()
{
    delete m_graph_Skeleton;
    delete m_graph_Face;
    delete m_graph_PES;
    delete m_graph_Priznak;
}

void BehaviorProcessor::clearAllQueues()
{
    m_graph_Skeleton->ClearQueues();
    m_graph_Face->ClearQueues();
    m_graph_PES->ClearQueues();
    m_graph_Priznak->ClearQueues();
}

//Оглядывание по сторонам
bool BehaviorProcessor::isFrequentLookingAround() //02.08.2022
{
    int cnt_reverse = 0;
    int prev_state = 0; //0 1 2
    int dlit_prev = 0;

    int n = m_graph_Face->m_v_Queues[2].length();
    for(int i=0; i<n; i++)
    {
        bool b_left = m_graph_Face->m_v_Queues[2][i];
        bool b_right = m_graph_Face->m_v_Queues[3][i];

        int state = 0;

        if(b_left)
            state = 1;
        if(b_right)
            state = 2;

        if(state != prev_state)
        {
            if(dlit_prev > 3) //фильтр шума
                cnt_reverse++;

            dlit_prev = 0;

            prev_state = state;
        }
        else
        {
            dlit_prev++;
        }
    }

    //printf("cnt_reverse = %d\n", cnt_reverse);

    if(cnt_reverse > 5)
        return true;

    return false;
}

//Бегающий взгляд
bool BehaviorProcessor::isShiftyLook() //02.08.2022
{
    int cnt_reverse = 0;
    int prev_state = 0; //0 1 2
    int dlit_prev = 0;

    int n = m_graph_Face->m_v_Queues[2].length();
    for(int i=0; i<n; i++)
    {
        bool b_left = m_graph_Face->m_v_Queues[9][i];
        bool b_right = m_graph_Face->m_v_Queues[10][i];

        int state = 0;

        if(b_left)
            state = 1;
        if(b_right)
            state = 2;

        if(state != prev_state)
        {
            if(dlit_prev > 2) //фильтр шума
                cnt_reverse++;

            dlit_prev = 0;

            prev_state = state;
        }
        else
        {
            dlit_prev++;
        }
    }

    //printf("cnt_reverse = %d\n", cnt_reverse);

    if(cnt_reverse > 7)
        return true;

    return false;
}


bool BehaviorProcessor::isFrequentBlinking()
{
    int cnt_blinks = 0;
    int prev_state = 0;
    int dlit_prev = 0;

    int n = m_graph_Face->m_v_Queues[12].length();
    for(int i=0; i<n; i++)
    {
        bool b_blink = m_graph_Face->m_v_Queues[12][i];

        int state = 0;

        if(b_blink)
            state = 1;

        if(state != prev_state)
        {
            if(prev_state == 1)
            if(dlit_prev >= 0) //фильтр шума
                cnt_blinks++;

            dlit_prev = 0;

            prev_state = state;
        }
        else
        {
            dlit_prev++;
        }
    }

    double freq_blinks = (double)cnt_blinks / 20; //20sec длительность наблюдения
    //printf("cnt_blinks = %d, freq=%.1f\n", cnt_blinks, freq_blinks);

    if(freq_blinks > 0.5) //0.5Hz
        return true;

    return false;
}


bool BehaviorProcessor::isYawning()
{
    int cnt_opens = 0;
    int prev_state = 0;
    int dlit_prev = 0;

    int n = m_graph_Face->m_v_Queues[14].length();
    for(int i=0; i<n; i++)
    {
        bool b_open = m_graph_Face->m_v_Queues[14][i];

        int state = 0;

        if(b_open)
            state = 1;

        if(state != prev_state)
        {
            if(prev_state == 1)
            if(dlit_prev > 6) //фильтр шума
                cnt_opens++;

            dlit_prev = 0;

            prev_state = state;
        }
        else
        {
            dlit_prev++;
        }
    }

    //printf("cnt_reverse = %d\n", cnt_reverse);

    if(cnt_opens > 2)
        return true;

    return false;
}

//03.08.2022
bool BehaviorProcessor::isDeath()
{
    int cnt_face_tilt = 0;
    int cnt_body_tilt = 0;

    int n = m_graph_Face->m_v_Queues[0].length();
    for(int i=0; i<n; i++)
    {
        if(m_graph_Face->m_v_Queues[0][i] > 35) //35deg
            cnt_face_tilt++;

        if(m_graph_Skeleton->m_v_Queues[0][i] > 25) //25deg_
            cnt_body_tilt++;
    }

    double tilt_time_face = (double)cnt_face_tilt / n;
    double tilt_time_body = (double)cnt_body_tilt / n;

    //printf("tilt_time_face=%.1f, tilt_time_body=%.1f\n", tilt_time_face, tilt_time_body);

    if(tilt_time_face > 0.4 || tilt_time_body > 0.4) //40% time analize
        return true;

    return false;
}

//25.10.2022
void BehaviorProcessor::updateParams(const sParamsBEH &_params)
{
    m_params = _params;
}

void BehaviorProcessor::update(Skeleton& skeleton, FaceProcessor& faceProcessor)
{
    //comm 29.05.2022
    if (skeleton.isVisible()) {
        skeletonInvisibilityTime = 0;
    } else {
        skeletonInvisibilityTime++;
        if (skeletonInvisibilityTime > 5) {
            clearAllQueues();
        }
        return;
    }


    //SKELETON
    //--------------------------------------------
    int iTorsoTilt = skeleton.TorsoTiltDeg();
    m_graph_Skeleton->addAction(0, iTorsoTilt);

    int iHeadDown = skeleton.isShouldersRaised();
    m_graph_Skeleton->addAction(1, iHeadDown);

    //..
    //m_graph_Skeleton->addAction(2, 0); //comm 25.10.2022

    int iHandsChest = skeleton.isHandsChest();
    m_graph_Skeleton->addAction(3, iHandsChest);

    int iHandsUp = 0;
    if (skeleton.isHandsUp())
        iHandsUp = 1;
    else
    if(skeleton.isHandsUpFull())
        iHandsUp = 2;
    else
        iHandsUp = 0;
    m_graph_Skeleton->addAction(4, iHandsUp);

    int iFacepalm = skeleton.isFacepalm();
    //24.10.2022 comm
    //if(faceProcessor.perFaceVisible() < 60) //60per
    //    iFacepalm = 1;
    m_graph_Skeleton->addAction(5, iFacepalm);



    //FACE
    //--------------------------------------------
    int iFaceTilt = faceProcessor.GetFaceTilt();
    m_graph_Face->addAction(0, iFaceTilt);

    int iFaceDown = faceProcessor.isFaceDown();
    m_graph_Face->addAction(1, iFaceDown);

    int iFaceLeft = faceProcessor.isFaceLeft();
    m_graph_Face->addAction(2, iFaceLeft);
    m_graph_Face->NoiseFilter(2); //03.08.2022

    int iFaceRight = faceProcessor.isFaceRight();
    m_graph_Face->addAction(3, iFaceRight);
    m_graph_Face->NoiseFilter(3); //03.08.2022

    int iFrequentLookingAround = isFrequentLookingAround();
    m_graph_Face->addAction(4, iFrequentLookingAround);

    int iEyebrowsRaised = faceProcessor.isEyebrowsRaised();
    m_graph_Face->addAction(5, iEyebrowsRaised);

    //25.10.2022 add
    int iEyeClose = faceProcessor.isEyeClose();
    m_graph_Face->addAction(6, iEyeClose);

    int iEyeCenter = faceProcessor.isEyesCenter();
    m_graph_Face->addAction(7, iEyeCenter);

    int iEyeDown = faceProcessor.isEyesDown();
    m_graph_Face->addAction(8, iEyeDown);

    int iEyeLeft = faceProcessor.isEyesLeft();
    m_graph_Face->addAction(9, iEyeLeft);

    int iEyeRight = faceProcessor.isEyesRight();
    m_graph_Face->addAction(10, iEyeRight);

    int iShiftyLook = isShiftyLook();
    m_graph_Face->addAction(11, iShiftyLook);

    int iBlinked = faceProcessor.isBlinked();
    m_graph_Face->addAction(12, iBlinked);

    int iFrequentBlinking = isFrequentBlinking();
    m_graph_Face->addAction(13, iFrequentBlinking);


    int iMouthOpen = faceProcessor.isMouthOpen();
    m_graph_Face->addAction(14, iMouthOpen);

    int iYawning = isYawning();
    m_graph_Face->addAction(15, iYawning);

    int iLipsClosed = faceProcessor.isLipsClosed();
    m_graph_Face->addAction(16, iLipsClosed);

    m_graph_Face->addAction(17, 0);



    //PES
    //--------------------------------------------
    //Гнев
    int iAnger = 0;
    if(iMouthOpen)
        iAnger += m_params.iAnger_MouthOpen; //25;
    if(iLipsClosed)
        iAnger += m_params.iAnger_LipsClosed; //35;
    if(faceProcessor.isEyebrowsLowered())
        iAnger += m_params.iAngerisEyebrowsLowered; //35;
    if(iAnger > 100)
        iAnger = 100;
    m_graph_PES->addAction(0, iAnger);

    //Страх
    int iFear = 0;
    if(iEyebrowsRaised)
        iFear += m_params.iFearEyebrowsRaised; //20;
    if(iMouthOpen)
        iFear += m_params.iFearMouthOpen; //20;
    if(iHeadDown)
        iFear += m_params.iFearHeadDown; //20;
    if(iFaceDown)
        iFear += m_params.iFearFaceDown; //20;
    if(iFrequentLookingAround)
        iFear += m_params.iFearFrequentLookingAround; //20;
    if(iFear > 100)
        iFear = 100;
    m_graph_PES->addAction(1, iFear);

    //Сильное волнение
    int iExcitement = 0;
    if(iFacepalm)
        iExcitement += m_params.iExcitementFacepalm; //20;
    if(iHeadDown)
        iExcitement += m_params.iExcitementHeadDown; //20;
    if(iShiftyLook)
        iExcitement += m_params.iExcitementShiftyLook; //20;
    if(iFrequentBlinking)
        iExcitement += m_params.iExcitementFrequentBlinking; //20;
    if(iFrequentLookingAround)
        iExcitement += m_params.iExcitementFrequentLookingAround; //20;
    if(iExcitement > 100)
        iExcitement = 100;
    m_graph_PES->addAction(2, iExcitement);


    //Priznak
    //--------------------------------------------
    //Смерть потеря сознания
    int iDeath = isDeath();
    m_graph_Priznak->addAction(0, iDeath);

    //Ухудшение состояния ССС
    int iSSS = 0;
    if(iFear > 30)
        iSSS += m_params.iSSSFear; //20;
    if(iExcitement > 30)
        iSSS += m_params.iSSSExcitement; //20;
    if(iHandsChest)
        iSSS += m_params.iSSSHandsChest; //40;
    if(iSSS> 100)
        iSSS = 100;
    m_graph_Priznak->addAction(1, iSSS);

    //Ухудшение состояния ЦНС
    int iCNS = 0;
    if(iFear > 30)
        iCNS += m_params.iCNSFear; //20;
    if(iExcitement > 30)
        iCNS += m_params.iCNSExcitement; //20;
    if(iTorsoTilt > 20)
        iCNS += m_params.iCNSTorsoTilt; //30;
    if(iCNS> 100)
        iCNS = 100;
    m_graph_Priznak->addAction(2, iCNS);

    //Сонливость
    int iSleeping = 0;
    if(iTorsoTilt > 20)
        iSleeping += m_params.iSleepingTorsoTilt; //20;
    if(iFaceTilt > 20)
        iSleeping += m_params.iSleepingFaceTilt; //20;
    if(iYawning)
        iSleeping += m_params.iSleepingYawning; //50;
    if(iSleeping > 100)
        iSleeping = 100;
    m_graph_Priznak->addAction(3, iSleeping);

    //Панические атаки
    int iPanicAttacks = 0;
    if(iShiftyLook)
        iPanicAttacks += m_params.iPanicAttacksShiftyLook; //40;
    if(iExcitement > 25)
        iPanicAttacks += m_params.iPanicAttacksExcitement; //25;
    if(iMouthOpen)
        iPanicAttacks += m_params.iPanicAttacksMouthOpen; //20;
    if(iPanicAttacks > 100)
        iPanicAttacks = 100;
    m_graph_Priznak->addAction(4, iPanicAttacks);

    //Алкогольное опьянение
    int iAlcoholPoisoning = 0;
    if(iFaceTilt > 25)
        iAlcoholPoisoning = m_params.iAlcoholPoisoningFaceTilt; //25;
    if(iSleeping > 25)
        iAlcoholPoisoning = m_params.iAlcoholPoisoningSleeping; //35;
    if(iAlcoholPoisoning > 100)
        iAlcoholPoisoning = 100;
    m_graph_Priznak->addAction(5, iAlcoholPoisoning);
}

//вывод всего
void BehaviorProcessor::DrawFeaturesWindows(cv::Mat &_frame_face, cv::Mat &_frame_skeleton) //26.09.2022
{
    cv::Mat frame_face_features(cv::Size(710, 1080), CV_8UC3, cv::Scalar(70, 0, 0));
    cv::Mat frame_skeleton_features(cv::Size(710, 1080), CV_8UC3, cv::Scalar(70, 0, 0));

    m_graph_Face->Draw(frame_face_features, cv::Point(0, 0), cv::Scalar(40, 40, 40));
    m_graph_Skeleton->Draw(frame_skeleton_features, cv::Point(0, 0), cv::Scalar(40, 40, 40));
    m_graph_PES->Draw(frame_skeleton_features, cv::Point(0, 360), cv::Scalar(0, 90, 90));
    m_graph_Priznak->Draw(frame_skeleton_features, cv::Point(0, 540), cv::Scalar(0, 0, 90));

    //НИИ МВС ЮФУ
    //cv::putText(frame_skeleton_features, "НИИ МВС ЮФУ", cv::Point(90, 970), 3, 2,  cv::Scalar(255, 255, 255, 255), 3); //27.09.2022

    //26.09.2022
    /*
    imshow("FACE_FEATURES", frame_face_features);
    imshow("SKELETON_FEATURES", frame_skeleton_features);

    cv::waitKey(1);
    */
    //26.09.2022
    _frame_face = frame_face_features.clone();
    _frame_skeleton = frame_skeleton_features.clone();
}

//04.01.2023
bool BehaviorProcessor::SaveDumpData(const char *_f_name)
{
    FILE *f_out = fopen(_f_name, "wb");

    m_graph_Skeleton->WriteToFile(f_out);
    m_graph_Face->WriteToFile(f_out);
    m_graph_PES->WriteToFile(f_out);
    m_graph_Priznak->WriteToFile(f_out);

    fclose(f_out);

    return true;
}
//
bool BehaviorProcessor::LoadDumpData(const char *_f_name)
{
    FILE *f_in = fopen(_f_name, "rb");

    m_graph_Skeleton->ReadFromFile(f_in);
    m_graph_Face->ReadFromFile(f_in);
    m_graph_PES->ReadFromFile(f_in);
    m_graph_Priznak->ReadFromFile(f_in);

    fclose(f_in);

    return true;
}
