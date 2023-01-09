#include <QCoreApplication>

#include "platform.h"

#include "mini.h"
#include "Stopwatch.h"
#include "SpeedReg.h"
#include "PoseProcessor.h"
#include "faceprocessor.h" //26.05.2022
FaceProcessor faceProcessor; //26.05.2022

#include "BehaviorProcessor.h" //29.05.2022
BehaviorProcessor behProcessor;

#include <opencv2/opencv.hpp>
using namespace cv;

//25.10.2022
#define NAME_CONFIG "../../../inputdata/configStrongAI.ini" //20.12.2022
#define NAME_DUMP "../../../inputdata/dumpBehAI.bin"
#define NAME_EXPERTS_DB "../../../inputdata/expertsTaskMachine.dat"

#include "MachineControlAI.h"
#include "interactionsppr.h"
cInteractionSPPR interSPPR;
cMachineControl *MC = NULL;

//25.10.2022
sParamsBEH paramsBEHprev;
sParamsBEH paramsBEH;

//[PARAM_VIDEO]
int iTYPE_INPUT = 0;
//
string sVIDEO_FILE_PATH;
int iVIDEO_START_POS = 0;
int iCAM_NUM = 0;
int iCAM_WIDTH = 0;
int iCAM_HEIGHT = 0;
int iCAM_FPS = 0;
double fCAM_GAIN = 0;
double fCAM_EXPOSURE = 0;

//[PARAM_DETECT_POSE]
int iUSE_DETECT_POSE = 0;
double fMIN_QUANT_SKELETON = 0.;
int iMIN_SIZE_SKELETON = 0;
int iMAX_SIZE_SKELETON = 0;
int iDRAW_SKELETONS = 0;

int iUSE_ANALIZE_HANDS_UP = 0;
cv::Scalar scCOLOR_HANDS_UP;

int iUSE_ANALIZE_HEAD_NOT_VISIBLE = 0;
cv::Scalar scCOLOR_HEAD_NOT_VISIBLE;

int iUSE_ANALIZE_BODY_LYING = 0;
cv::Scalar scCOLOR_BODY_LYING;

int iUSE_ANALIZE_FIGHT = 0;
int iFIGHT_HIT_HAND_TO_FACE = 0;
int iFIGHT_HIT_FOOT_TO_FACE = 0;
int iFIGHT_HIT_FOOT2_TO_FACE = 0;
int iFIGHT_HIT_FOOT_TO_PELVIS = 0;
cv::Scalar scCOLOR_FIGHT;

//21.09.2022
//[PARAM_DETECT_BEHAVIOR]
int iUSE_DETECT_BEHAVIOR = 0;
int iUSE_SEND_KEYPOINT = 0; //03.10.2022
int iUSE_TUNE_PARAMS_BEH = 0; //25.10.2022

//[PARAM_OUTPUT]
int iUSE_DRAW_FPS = 0;
int iUSE_DRAW_VIDEO_POS = 0;
int iUSE_WAIT_KEY = 0;
int iUSE_IMSHOW = 0; //25.09.2022
//02.12.2022
int iUSE_REC = 0;
int iREC_FPS = 0;
string sREC_FILE_PATH;
//02.12.2022
VideoWriter writer;

VideoCapture capture;
CMedVar med_fps;

PoseProcessor* poseProcessor = NULL; //04.05.2022

//цвет из 255,0,0 в cv::Scalar 06.05.2022
cv::Scalar GetScalarCol(string _str)
{
    int r=0,g=0,b=0;
    sscanf(_str.c_str(), "%d,%d,%d", &r, &g, &b);
    cv::Scalar ret(b, g, r);
    return ret;
}


//Чтение конфигурационного файла
bool ReadConfigINI()
{
    try {
    mINI::INIFile file(NAME_CONFIG); //25.10.2022
    mINI::INIStructure ini;
    file.read(ini);

    //read [PARAM_VIDEO]
    iTYPE_INPUT = std::stoi(ini["PARAM_VIDEO"]["TYPE_INPUT"]);
    //19.12.2022
    //
    sVIDEO_FILE_PATH = ini["PARAM_VIDEO"]["VIDEO_FILE_PATH"];
    iVIDEO_START_POS = std::stoi(ini["PARAM_VIDEO"]["VIDEO_START_POS"]);

    iCAM_NUM = std::stoi(ini["PARAM_VIDEO"]["CAM_NUM"]);
    iCAM_WIDTH = std::stoi(ini["PARAM_VIDEO"]["CAM_WIDTH"]);
    iCAM_HEIGHT = std::stoi(ini["PARAM_VIDEO"]["CAM_HEIGHT"]);
    iCAM_FPS = std::stoi(ini["PARAM_VIDEO"]["CAM_FPS"]);
    fCAM_GAIN = std::stof(ini["PARAM_VIDEO"]["CAM_GAIN"]);
    fCAM_EXPOSURE = std::stof(ini["PARAM_VIDEO"]["CAM_EXPOSURE"]);

    //read [PARAM_DETECT_POSE]
    iUSE_DETECT_POSE = std::stoi(ini["PARAM_DETECT_POSE"]["USE_DETECT_POSE"]);
    //
    fMIN_QUANT_SKELETON = std::stof(ini["PARAM_DETECT_POSE"]["MIN_QUANT_SKELETON"]);
    iMIN_SIZE_SKELETON = std::stoi(ini["PARAM_DETECT_POSE"]["MIN_SIZE_SKELETON"]);
    iMAX_SIZE_SKELETON = std::stoi(ini["PARAM_DETECT_POSE"]["MAX_SIZE_SKELETON"]);
    iDRAW_SKELETONS = std::stoi(ini["PARAM_DETECT_POSE"]["DRAW_SKELETONS"]);

    iUSE_ANALIZE_HANDS_UP = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_HANDS_UP"]);
    scCOLOR_HANDS_UP = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_HANDS_UP"]);

    iUSE_ANALIZE_HEAD_NOT_VISIBLE = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_HEAD_NOT_VISIBLE"]);
    scCOLOR_HEAD_NOT_VISIBLE = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_HEAD_NOT_VISIBLE"]);

    iUSE_ANALIZE_BODY_LYING = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_BODY_LYING"]);
    scCOLOR_BODY_LYING = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_BODY_LYING"]);

    iUSE_ANALIZE_FIGHT = std::stoi(ini["PARAM_DETECT_POSE"]["USE_ANALIZE_FIGHT"]);
    iFIGHT_HIT_HAND_TO_FACE = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_HAND_TO_FACE"]);
    iFIGHT_HIT_FOOT_TO_FACE = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_FOOT_TO_FACE"]);
    iFIGHT_HIT_FOOT2_TO_FACE = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_FOOT2_TO_FACE"]);
    iFIGHT_HIT_FOOT_TO_PELVIS = std::stoi(ini["PARAM_DETECT_POSE"]["FIGHT_HIT_FOOT_TO_PELVIS"]);
    scCOLOR_FIGHT = GetScalarCol(ini["PARAM_DETECT_POSE"]["COLOR_FIGHT"]);

    //25.09.2022
    //read [PARAM_DETECT_BEHAVIOR]
    iUSE_DETECT_BEHAVIOR = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["USE_DETECT_BEHAVIOR"]);
    iUSE_SEND_KEYPOINT = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["USE_SEND_KEYPOINT"]); //03.10.2022
    iUSE_TUNE_PARAMS_BEH = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["USE_TUNE_PARAMS_BEH"]); //25.10.2022
    //25.10.2022 BEH params
    //=====================
    //Гнев
    paramsBEH.iAnger_MouthOpen = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_Anger_MouthOpen"]);
    paramsBEH.iAnger_LipsClosed = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_Anger_LipsClosed"]);
    paramsBEH.iAngerisEyebrowsLowered = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_AngerisEyebrowsLowered"]);
    //Страх
    paramsBEH.iFearEyebrowsRaised = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_FearEyebrowsRaised"]);
    paramsBEH.iFearMouthOpen = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_FearMouthOpen"]);
    paramsBEH.iFearHeadDown = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_FearHeadDown"]);
    paramsBEH.iFearFaceDown = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_FearFaceDown"]);
    paramsBEH.iFearFrequentLookingAround = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_FearFrequentLookingAround"]);
    //Сильное волнение
    paramsBEH.iExcitementFacepalm = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_ExcitementFacepalm"]);
    paramsBEH.iExcitementHeadDown = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_ExcitementHeadDown"]);
    paramsBEH.iExcitementShiftyLook = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_ExcitementShiftyLook"]);
    paramsBEH.iExcitementFrequentBlinking = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_ExcitementFrequentBlinking"]);
    paramsBEH.iExcitementFrequentLookingAround = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_ExcitementFrequentLookingAround"]);
    //Priznak
    //=======
    //Ухудшение состояния ССС
    paramsBEH.iSSSFear = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_SSSFear"]);
    paramsBEH.iSSSExcitement = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_SSSExcitement"]);
    paramsBEH.iSSSHandsChest = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_SSSHandsChest"]);
    //Ухудшение состояния ЦНС
    paramsBEH.iCNSFear = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_CNSFear"]);
    paramsBEH.iCNSExcitement = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_CNSExcitement"]);
    paramsBEH.iCNSTorsoTilt = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_CNSTorsoTilt"]);
    //Сонливость
    paramsBEH.iSleepingTorsoTilt = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_SleepingTorsoTilt"]);
    paramsBEH.iSleepingFaceTilt = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_SleepingFaceTilt"]);
    paramsBEH.iSleepingYawning = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_SleepingYawning"]);
    //Панические атаки
    paramsBEH.iPanicAttacksShiftyLook = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_PanicAttacksShiftyLook"]);
    paramsBEH.iPanicAttacksExcitement = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_PanicAttacksExcitement"]);
    paramsBEH.iPanicAttacksMouthOpen = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_PanicAttacksMouthOpen"]);
    //Алкогольное опьянение
    paramsBEH.iAlcoholPoisoningFaceTilt = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_AlcoholPoisoningFaceTilt"]);
    paramsBEH.iAlcoholPoisoningSleeping = std::stoi(ini["PARAM_DETECT_BEHAVIOR"]["BEH_AlcoholPoisoningSleeping"]);
    //25.10.2022
    paramsBEHprev = paramsBEH;
    //25.10.2022
    behProcessor.updateParams(paramsBEH);


    //read [PARAM_OUTPUT]
    iUSE_DRAW_FPS = std::stoi(ini["PARAM_OUTPUT"]["USE_DRAW_FPS"]);
    iUSE_DRAW_VIDEO_POS = std::stoi(ini["PARAM_OUTPUT"]["USE_DRAW_VIDEO_POS"]);
    iUSE_WAIT_KEY = std::stoi(ini["PARAM_OUTPUT"]["USE_WAIT_KEY"]);
    iUSE_IMSHOW = std::stoi(ini["PARAM_OUTPUT"]["USE_IMSHOW"]); //25.09.2022
    //02.12.2022
    iUSE_REC = std::stoi(ini["PARAM_OUTPUT"]["USE_REC"]);
    iREC_FPS = std::stoi(ini["PARAM_OUTPUT"]["REC_FPS"]);
    sREC_FILE_PATH = ini["PARAM_OUTPUT"]["REC_FILE_PATH"];
    }
    catch(...)
    {
    printf("Err read ini!\n");
    return false;
    }

    return true;
}

bool InitALL()
{
    setlocale(LC_NUMERIC, "POSIX"); //06.05.2022 float point (.)


    if(!ReadConfigINI())
        return false;

    //09.01.2022
    interSPPR.ReadExpertsFromDB(NAME_EXPERTS_DB);
    MC = new cMachineControl("COM3");
    //if(!MC->IsOpenDevice())
    //    return false;

    //25.09.2022
    if(iUSE_IMSHOW)
    {

    cv::namedWindow("SKELETON", WINDOW_FULLSCREEN);
    cv::moveWindow("SKELETON", 710, 0);

    //31.07.2022
    cv::namedWindow("FACE_FEATURES");
    cv::moveWindow("FACE_FEATURES", 710, 0);

    cv::namedWindow("SKELETON_FEATURES");
    cv::moveWindow("SKELETON_FEATURES", 0, 0);

    cv::namedWindow("FACE");
    cv::moveWindow("FACE", 1420, 0);

    }

    med_fps.SetLenMas(10);

    if(iUSE_DETECT_POSE) //29.09.2022
        poseProcessor = new PoseProcessor(iUSE_DETECT_BEHAVIOR, fMIN_QUANT_SKELETON, iMIN_SIZE_SKELETON, iMAX_SIZE_SKELETON, iDRAW_SKELETONS, iUSE_ANALIZE_HANDS_UP, scCOLOR_HANDS_UP, iUSE_ANALIZE_HEAD_NOT_VISIBLE, scCOLOR_HEAD_NOT_VISIBLE, iUSE_ANALIZE_BODY_LYING, scCOLOR_BODY_LYING, iUSE_ANALIZE_FIGHT, iFIGHT_HIT_HAND_TO_FACE, iFIGHT_HIT_FOOT_TO_FACE, iFIGHT_HIT_FOOT2_TO_FACE, iFIGHT_HIT_FOOT_TO_PELVIS, scCOLOR_FIGHT);


    if(iTYPE_INPUT == 0) //CAM
    {
        //InitCAM
#ifdef _WIN32
        if(!capture.open(iCAM_NUM))
#else
        if(!capture.open(iCAM_NUM, CAP_V4L2)) //04.05.2022 lin
#endif
        {
            printf("Cannot open cam = %d\n", iCAM_NUM);
            return false;
        }
        else
        {
#ifndef _WIN32
            capture.set(CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G')); //04.05.2022 lin
#endif
            capture.set(CAP_PROP_FRAME_WIDTH, iCAM_WIDTH);
            capture.set(CAP_PROP_FRAME_HEIGHT, iCAM_HEIGHT);
            capture.set(CAP_PROP_FPS, iCAM_FPS);
            capture.set(CAP_PROP_GAIN, fCAM_GAIN);
            capture.set(CAP_PROP_AUTO_EXPOSURE, 1); //1 - off, 3 - on //v4l2-ctl -l
            capture.set(CAP_PROP_EXPOSURE, fCAM_EXPOSURE);//1-5000
            capture.set(CAP_PROP_AUTOFOCUS, 0); //0 - off
            capture.set(CAP_PROP_FOCUS, 10); //25.10.2022


            //fCAM_EXPOSURE = capture.get(CAP_PROP_EXPOSURE);
            //printf("%.3f\n", fCAM_EXPOSURE);
        }
    }
    else
    if(iTYPE_INPUT == 1) //FILE
    {
        if(!capture.open(sVIDEO_FILE_PATH, CAP_GSTREAMER)) //01.12.2022 add
        {
            printf("Cannot open input file = %s\n", sVIDEO_FILE_PATH.c_str());
            return false;
        }
        else
        {
            capture.set(cv::CAP_PROP_POS_FRAMES, iVIDEO_START_POS);
            //capture.set(cv::CAP_PROP_BUFFERSIZE, 1); //07.10.2022
        }
    }
    else
        return false;

    return true;
}

void ClearALL()
{
    if(poseProcessor != NULL)
        delete poseProcessor;

    capture.release();

    printf("ClearALL OK!\n");
}

void DrawFPS(Mat &_frame, long long _time)
{
        if(_time == 0)
            _time = 1000;
        _time = 1000/_time;
        med_fps.PushNewZn((int)_time);

        char str[50];
        sprintf(str, "fps=%ld", med_fps.GetSr());
        putText(_frame, str, Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1); //40 0.75 //15.05.2020
}

void DrawVideoPos(Mat &_frame)
{
    if(iTYPE_INPUT == 1)
        {
        int vid_pos = capture.get(cv::CAP_PROP_POS_FRAMES);

        char str[50];
        sprintf(str, "video_pos=%ld", vid_pos);
        putText(_frame, str, Point(20, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1); //40 0.75 //15.05.2020
        }
}

//27.07.2022
cv::Mat translateImg(const cv::Mat& img, double offsetx, double offsety) {
  cv::Mat trans_mat = (cv::Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
  cv::Mat ret;
  warpAffine(img, ret, trans_mat, img.size());
  return ret;
}

//27.07.2022
cv::Mat rotateImg(const cv::Mat& img, double angle_grad) {
  cv::Mat ret;

  cv::Point2f pc(img.cols/2., img.rows/2.);
  cv::Mat r = cv::getRotationMatrix2D(pc, angle_grad, 1.0);

  cv::warpAffine(img, ret, r, img.size());
  return ret;
}

//Копирование фрагмента с лицом с образкой каря кадра и заполнением черным
void CopyFaceLimitation(cv::Mat &_in, cv::Mat &_out, int x0, int y0, int _ROI_SZ)
{
    //cv::Mat FaceROI(cv::Size(_ROI_SZ, _ROI_SZ), CV_8UC3, cv::Scalar(0, 0, 0)); //01.08.2022

    int x0_roi = x0 - _ROI_SZ / 2;
    int y0_roi = y0 - _ROI_SZ / 2;
    //int x1_roi = x0 + _ROI_SZ / 2;
    //int y1_roi = y0 + _ROI_SZ / 2;


      int sz_elem = (int)_in.elemSize(); //24.11.2020
      int im_width = _out.cols;
      int im_height = _out.rows;

      //printf("%d\n", sz_elem);

      int i, j;
      for(i=0;i<im_width;i++)
      for(j=0;j<im_height;j++)
            {
            int ii = i + y0_roi;
            int jj = j + x0_roi;

            if(ii > 0 && jj > 0 && ii < _in.rows && jj < _in.cols)
                {
                //unsigned char us = image->imageData[i*image->width + j]; //24.03.2020
                unsigned short us1 = _in.data[ii*_in.cols * sz_elem + jj * sz_elem];
                unsigned short us2 = _in.data[ii*_in.cols * sz_elem + jj * sz_elem + 1];
                unsigned short us3 = _in.data[ii*_in.cols * sz_elem + jj * sz_elem + 2];

                //unsigned short us1 = 50;
                //unsigned short us2 = 0;
                //unsigned short us3 = 0;

                _out.data[i*_out.cols * sz_elem + j * sz_elem] = us1;
                _out.data[i*_out.cols * sz_elem + j * sz_elem + 1] = us2;
                _out.data[i*_out.cols * sz_elem + j * sz_elem + 2] = us3;
                }
            }


      /*
      for(int row = 0; row < img.rows; ++row)
      {
          uchar* p = img.ptr(row);
          for(int col = 0; col < img.cols; ++col) {
               *p++  //points to each pixel value in turn assuming a CV_8UC1 greyscale image
          }
          or
          for(int col = 0; col < img.cols*3; ++col) {
               *p++  //points to each pixel B,G,R value in turn assuming a CV_8UC3 color image
          }
      }
      */


    //_out = FaceROI.clone();
}


//11.09.2022
CMedVar med_fps1;
void DrawFPS1(Mat &_frame, long long _time)
{
        if(_time == 0)
            _time = 1000;
        _time = 1000/_time;
        med_fps1.PushNewZn((int)_time);

        char str[50];
        sprintf(str, "fps=%ld", med_fps1.GetSr());
        putText(_frame, str, Point(380, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1); //40 0.75 //15.05.2020
}

//=============
void MainProc()
{
    Mat frame;
    long long time_fps = 0;

    bool b_init_rec = true; //02.12.2022

    while(1)
    {
        CStopwatch st;

        //07.10.2022
        bool b_read_frame = false;
        if(1)
        {
            b_read_frame = capture.read(frame);

            if(iTYPE_INPUT == 1) //file close 01.12.2022
            {
                if(!b_read_frame)
                {
                    printf("EOF!\n");
                    break;
                }
            }
        }

        if(b_read_frame) //07.10.2022
        //if(capture.read(frame)) //comm 07.10.2022
        if(frame.cols > 0 && frame.rows > 0)
        {

        //02.12.2022
        if(iUSE_REC)
        {
        if(b_init_rec)
            {
                b_init_rec = false;
                writer = VideoWriter(sREC_FILE_PATH.c_str(), VideoWriter::fourcc('M','J','P','G'), (double)iREC_FPS, Size(frame.cols, frame.rows));
            }
        }

        //add 20.12.2022
        //02.12.2022
        if(iUSE_REC && !b_init_rec)
        {
            writer.write(frame);
        }


        if(iUSE_DETECT_POSE)
            {
            //Openpose
            poseProcessor->process(frame);
            }

        bool b_isPerson_visible = false; //03.08.2022
        if(iUSE_DETECT_BEHAVIOR && iUSE_DETECT_POSE == 1) //анализ поведения 29.05.2022 //26.07.2022 0 !!! //25.09.2022 //1 BEH 27.09.2022
            {

            bool _face_found = false;
            Rect r_face;

            int iROI_SZ = 500; //500x500
            cv::Mat FaceROI(cv::Size(iROI_SZ, iROI_SZ), CV_8UC3, cv::Scalar(0, 0, 0)); //01.08.2022


            Skeleton s;
            //poseProcessor->GetBigestSkeleton(s);
            if(!poseProcessor->GetCenterNoseSkeleton(s))
            {
                s.SetEmptySkeleton();
                //printf("fack skeleton!!!\n");
            }

            //one face proc //29.07.2022
            ////////////////////////////
            if(s.isVisible()) //26.07.2022 draw faces !!!
            {
                b_isPerson_visible = true; //03.08.2022

                //print angle
                double x1 = s.face[36].pixelX;
                double y1 = s.face[36].pixelY;
                double x2 = s.face[45].pixelX;
                double y2 = s.face[45].pixelY;
                double angle_rot = atan2(y2 - y1, x2 - x1);

                bool b_fack_eye = false;
                if(s.face[36].pixelZ < OK_PER_POINT_FACE || s.face[45].pixelZ < OK_PER_POINT_FACE) //плохие углы глаз
                {
                    angle_rot = 0.;
                    b_fack_eye = true;
                }

                //printf("angle_rot = %.0f\n", angle_rot * 57.296); //comm

                angle_rot *= -1;

                double x0 = s.face[30].pixelX;
                double y0 = s.face[30].pixelY;

                bool b_fack_nose = false;
                if(s.face[30].pixelZ < OK_PER_POINT_FACE) //плохой нос
                {
                    x0 = s.nose.pixelX;
                    y0 = s.nose.pixelY;
                    b_fack_nose = true;
                }


                //ROI image
                CopyFaceLimitation(frame, FaceROI, (int)x0, (int)y0, iROI_SZ); //01.08.2022

                cv::Mat rot_FaceROI = rotateImg(FaceROI, -angle_rot * 57.296);

                //29.07.2022
                _face_found = true;

                if(b_fack_eye && b_fack_nose) //нет носа и уголков глаз значит лицо не видно и не надо анализировать
                    _face_found = false;

                vector<cPointFace> v_keypoints_face;
                for(int fp = 0; fp < s.face.size(); fp++)
                    //if(s.face[fp].pixelZ > ok_per_point) //!!! score 70per
                    {
                    double x = s.face[fp].pixelX - x0;
                    double y = s.face[fp].pixelY - y0;

                    double x1 = x*cos(angle_rot) - y*sin(angle_rot);
                    double y1 = x*sin(angle_rot) + y*cos(angle_rot);

                    x1 += iROI_SZ/2;
                    y1 += iROI_SZ/2;

                    //cv::circle(rot_FaceROI, cv::Point(x1, y1), 1, cv::Scalar(255, 255, 255, 255), 1);
                    cPointFace point_face(x1, y1, s.face[fp].pixelZ);
                    v_keypoints_face.push_back(point_face);
                    }

                cFaceKeyPoint faceDet(v_keypoints_face);

                faceProcessor.process(rot_FaceROI, faceDet, _face_found, angle_rot * 57.296); //padaet 17.10.2022 big face

                Mat out_face;
                if(faceProcessor.GetImage(out_face, true))
                    {
                    if(iUSE_IMSHOW) //25.09.2022
                        imshow("FACE", out_face);
                    }

            }
            else //no skeleton
            {
                cFaceKeyPoint faceDet;
                faceProcessor.process(FaceROI, faceDet, _face_found, 0.);

                Mat out_face;
                if(faceProcessor.GetImage(out_face, true))
                    {
                    if(iUSE_IMSHOW) //25.09.2022
                        imshow("FACE", out_face);
                    }
            }


            //Mat graphs;
            behProcessor.update(s, faceProcessor);
            //behProcessor.draw(frame);

            //09.01.2022
            interSPPR.process(behProcessor);
            if(interSPPR.isAgentsVotingOK())
                {
                //printf("TRIGGED!\n");
                if(MC->IsOpenDevice())
                    MC->SendEmergencyStop();
                }
            }


        //Отображение фпс
        if(iUSE_DRAW_FPS)
            DrawFPS(frame, time_fps);

        //Отображегние номера кадра видео
        if(iUSE_DRAW_VIDEO_POS)
        {
            DrawVideoPos(frame);
        }


        //Отображение скелетов
        if(iUSE_DETECT_POSE)
            poseProcessor->drawL(frame);


        //Отображение поведения чел
        if(iUSE_DETECT_BEHAVIOR) //29.05.2022
        {
            Mat frame_face;
            Mat frame_skeleton;
            behProcessor.DrawFeaturesWindows(frame_face, frame_skeleton);

        if(iUSE_IMSHOW) //25.09.2022 !!!
            {
            imshow("FACE_FEATURES", frame_face);
            imshow("SKELETON_FEATURES", frame_skeleton);
            }

        }


        //Вывод фрейма
        if(iUSE_IMSHOW) //25.09.2022
            imshow("SKELETON", frame);

        //comm 20.12.2022
        /*
        //02.12.2022
        if(iUSE_REC && !b_init_rec)
        {
            writer.write(frame);
        }
        */

        if(iUSE_IMSHOW) //25.09.2022
        {
            //25.10.2022
            if(iUSE_TUNE_PARAMS_BEH)
            {
                if(!paramsBEHprev.IsIdentically(paramsBEH))
                {
                    paramsBEHprev = paramsBEH;
                    behProcessor.updateParams(paramsBEH);
                    //printf("change beh!\n"); //25.10.2022
                }
            }

            char key = 0;
            if(iUSE_WAIT_KEY == 0)
                key = waitKey(1);
            else
                key = waitKey(iUSE_WAIT_KEY); //-1); //02.12.2022

            if(key == 27)
            {
                //printf("esc\n");
                break;
            }

            //05.01.2022
            if(key == 'd' || key == 'D')
                behProcessor.SaveDumpData(NAME_DUMP);
            if(key == 'l' || key == 'L')
                behProcessor.LoadDumpData(NAME_DUMP);

        }

        time_fps = st.Now();
        }
        else
            Sleep(1);
    }

    //02.12.2022
    if(iUSE_REC && !b_init_rec)
    {
        writer.release();
    }
}

#include "qdir.h"
int main(int argc, char *argv[])
{
    QString qs = QDir::currentPath();
    printf("%s\n", qs.toStdString().c_str()); //03.01.2022
    qs += "/release";
    QDir::setCurrent(qs);

    if(InitALL())
    {
        MainProc();
        ClearALL();
    }

    exit(0);
    return 0;
}
