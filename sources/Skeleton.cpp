#include "Skeleton.h"

Skeleton::Skeleton()
{
    m_bVisible = true; //31.07.2022
}

bool Skeleton::isLefter(Point3f3i what, Point3f3i than) {
    return what.pixelX < than.pixelX;
}

bool Skeleton::isUpper(Point3f3i what, Point3f3i than) {
//    return what.worldY < than.worldY;
    return what.pixelY < than.pixelY;
}

bool Skeleton::isLower(Point3f3i what, Point3f3i than) {
//    return what.worldY > than.worldY;
    return what.pixelY > than.pixelY;
}

bool Skeleton::isPartPresent(Point3f3i p) {
    return p.pixelX > 1 && p.pixelY > 1 && p.pixelZ > 30; //03.10.2022 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Z 30per
}

//тела одного размера
bool Skeleton::isBodyEqval(Skeleton &_s, float min_body_otn)
{
    if(!isPartPresent(neck) || !isPartPresent(centerPelvis))
        return false;

    if(!_s.isPartPresent(_s.neck) || !_s.isPartPresent(_s.centerPelvis))
        return false;

    float body1 = getPixelDictance(neck, centerPelvis);
    float body2 = getPixelDictance(_s.neck, _s.centerPelvis);

    //printf("body1=%.1f body2=%.1f\n", body1, body2);

    if(body1 < 1. || body2 < 1.)
        return false;

    float otn = 0.;
    if(body1 > body2)
        otn = body2/body1;
    else
        otn = body1/body2;

    //printf("otn = %.1f\n", otn);

    if(otn > min_body_otn)
        return true;

    return false;
}

bool Skeleton::isHitHandToFace(Skeleton &_s)
{
    //нет носа и шеи кого бьют
    if(!_s.isPartPresent(_s.nose) || !_s.isPartPresent(_s.neck))
        return false;

    //нет кулаков у скелета чем бить
    if(!isPartPresent(leftWrist) && !isPartPresent(rightWrist))
        return false;

    //радиус удара по носу (от носа до шеи больше далеко)
    float dist_hit = _s.getPixelDictance(_s.nose, _s.neck);

    //printf("dist_hit = %.1f\n", dist_hit);

    //удар левой
    if(isPartPresent(leftWrist))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(leftWrist, _s.nose) < dist_hit)
            return true;
    }

    //удар правой
    if(isPartPresent(rightWrist))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(rightWrist, _s.nose) < dist_hit)
            return true;
    }

    return false;
}

bool Skeleton::isHitFootToFace(Skeleton &_s) //01.05.2022
{
    //нет носа и шеи кого бьют
    if(!_s.isPartPresent(_s.nose) || !_s.isPartPresent(_s.neck))
        return false;

    //нет ног у скелета чем бить
    if(!isPartPresent(leftFoot) && !isPartPresent(rightFoot))
        return false;

    //радиус удара по носу (от носа до шеи больше далеко)
    float dist_hit = _s.getPixelDictance(_s.nose, _s.neck) * 2.; //????

    //printf("dist_hit = %.1f\n", dist_hit);

    //удар левой
    if(isPartPresent(leftFoot))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(leftFoot, _s.nose) < dist_hit)
            return true;
    }

    //удар правой
    if(isPartPresent(rightFoot))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(rightFoot, _s.nose) < dist_hit)
            return true;
    }

    return false;
}

bool Skeleton::isHitFoot2ToFace(Skeleton &_s) //01.05.2022
{
    //нет носа и шеи кого бьют
    if(!_s.isPartPresent(_s.nose) || !_s.isPartPresent(_s.neck))
        return false;

    //нет ног у скелета чем бить
    if(!isPartPresent(leftFoot2) && !isPartPresent(rightFoot2))
        return false;

    //радиус удара по носу (от носа до шеи больше далеко)
    float dist_hit = _s.getPixelDictance(_s.nose, _s.neck);

    //printf("dist_hit = %.1f\n", dist_hit);

    //удар левой
    if(isPartPresent(leftFoot2))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(leftFoot2, _s.nose) < dist_hit)
            return true;
    }

    //удар правой
    if(isPartPresent(rightFoot2))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(rightFoot2, _s.nose) < dist_hit)
            return true;
    }

    return false;
}

//Удар ногой в таз скелету _s
bool Skeleton::isHitFootToPelvis(Skeleton &_s)
{
    //нет таза кого бьют
    if(!_s.isPartPresent(_s.centerPelvis) || !_s.isPartPresent(_s.leftPelvis) || !_s.isPartPresent(_s.rightPelvis))
        return false;

    //нет ног у скелета чем бить
    if(!isPartPresent(leftFoot) && !isPartPresent(rightFoot))
        return false;

    //радиус удара по тазу ()
    float dist_hit = _s.getPixelDictance(_s.leftPelvis, _s.rightPelvis) * 2.; //????

    //printf("dist_hit = %.1f\n", dist_hit);

    //удар левой
    if(isPartPresent(leftFoot))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(leftFoot, _s.centerPelvis) < dist_hit)
            return true;
    }

    //удар правой
    if(isPartPresent(rightFoot))
    {
        //float ff = getPixelDictance(leftWrist, _s.nose);
        //printf("left = %.1f\n", ff);

        if(getPixelDictance(rightFoot, _s.centerPelvis) < dist_hit)
            return true;
    }

    return false;
}

cv::Rect Skeleton::getRectSum(Skeleton &_s)
{
    int x_min = 10000;
    int y_min = 10000;
    int x_max = 0;
    int y_max = 0;

    cv::Rect r1 = getBoundingBox();
    x_min = r1.x;
    y_min = r1.y;
    x_max = r1.x + r1.width;
    y_max = r1.y + r1.height;

    cv::Rect r2 = _s.getBoundingBox();
    if(x_min > r2.x)
        x_min = r2.x;
    if(y_min > r2.y)
        y_min = r2.y;
    if(x_max < r2.x + r2.width)
        x_max = r2.x + r2.width;
    if(y_max < r2.y + r2.height)
        y_max = r2.y + r2.height;


    cv::Rect r_ret;
    r_ret.x = x_min;
    r_ret.y = y_min;
    r_ret.width = x_max - x_min;
    r_ret.height = y_max - y_min;

    return r_ret;
}

bool Skeleton::isHandsUpFull() {
    return isUpper(rightElbow, rightShoulder) && isUpper(rightWrist, rightElbow) &&
           isUpper(leftElbow, leftShoulder) && isUpper(leftWrist, leftElbow) &&
           isUpper(rightElbow, rightShoulder) && isUpper(rightWrist, rightElbow) &&
           isPartPresent(rightElbow) &&
           isPartPresent(rightShoulder) &&
           isPartPresent(leftElbow) && isPartPresent(leftWrist) && isPartPresent(leftShoulder) &&
           isPartPresent(rightWrist);
}

bool Skeleton::isBodyLying() //30.04.2022
{
    if(isPartPresent(neck) && isPartPresent(centerPelvis))
    {
        //шея ниже центра таза
        if(isLower(neck, centerPelvis))
            return true;
    }

    if(isPartPresent(neck) && isPartPresent(leftPelvis))
    {
        //шея ниже лева таза
        if(isLower(neck, leftPelvis))
            return true;
    }

    if(isPartPresent(neck) && isPartPresent(rightPelvis))
    {
        //шея ниже лева таза
        if(isLower(neck, rightPelvis))
            return true;
    }

    if(isPartPresent(nose) && isPartPresent(centerPelvis))
    {
        //нос ниже таза
        if(isLower(nose, centerPelvis))
            return true;
    }

    if(isPartPresent(nose) && isPartPresent(leftPelvis))
    {
        //нос ниже таза
        if(isLower(nose, leftPelvis))
            return true;
    }

    if(isPartPresent(nose) && isPartPresent(rightPelvis))
    {
        //нос ниже таза
        if(isLower(nose, rightPelvis))
            return true;
    }

    return false;
}

bool Skeleton::isBodyFront() //30.04.2022
{
    int cnt_true = 0;
    int cnt_false = 0;

    if(isPartPresent(rightShoulder) && isPartPresent(leftShoulder))
    {
        if(isLefter(rightShoulder, leftShoulder))
            cnt_true++;
        else
            cnt_false++;
    }

    if(isPartPresent(rightElbow) && isPartPresent(leftElbow))
    {
        if(isLefter(rightElbow, leftElbow))
            cnt_true++;
        else
            cnt_false++;
    }

    if(isPartPresent(rightWrist) && isPartPresent(leftWrist))
    {
        if(isLefter(rightWrist, leftWrist))
            cnt_true++;
        else
            cnt_false++;
    }

    if(isPartPresent(rightPelvis) && isPartPresent(leftPelvis))
    {
        if(isLefter(rightPelvis, leftPelvis))
            cnt_true++;
        else
            cnt_false++;
    }

    if(isPartPresent(rightKnee) && isPartPresent(leftKnee))
    {
        if(isLefter(rightKnee, leftKnee))
            cnt_true++;
        else
            cnt_false++;
    }

    if(isPartPresent(rightFoot) && isPartPresent(leftFoot))
    {
        if(isLefter(rightFoot, leftFoot))
            cnt_true++;
        else
            cnt_false++;
    }


    if(cnt_true > 0 && cnt_false==0)
        return true;

    if(cnt_false > 0 && cnt_true==0)
        return false;

    return false;
}

bool Skeleton::isHeadNotVisible() {

    bool ret = isPartPresent(leftEye) || isPartPresent(rightEye) || isPartPresent(nose);// && isPartPresent(leftEar) && isPartPresent(rightEar);
    return !ret;
}

bool Skeleton::isHandsUp() {
    return isUpper(leftWrist, leftShoulder) && isUpper(rightWrist, rightShoulder) &&
           isLower(leftElbow, leftShoulder) && isLower(rightElbow, rightShoulder) &&
            isPartPresent(leftElbow) && isPartPresent(leftWrist) && isPartPresent(leftShoulder) &&
            isPartPresent(rightElbow) && isPartPresent(rightWrist) && isPartPresent(rightShoulder);
}

bool Skeleton::isHandsDownFree() {
    return isUpper(leftShoulder, leftElbow) && isUpper(leftElbow, leftWrist) && isUpper(rightShoulder, rightElbow) && isUpper(rightElbow, rightWrist);
}

//30.05.2022
bool Skeleton::isShouldersRaised()
{
    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(rightShoulder) && isPartPresent(leftShoulder))
    {
        double dist_neck = getPixelDictance(nose, neck);
        double dist_sh1 = getPixelDictance(rightShoulder, neck);
        double dist_sh2 = getPixelDictance(leftShoulder, neck);

        if(dist_neck < 1.)
            dist_neck = 1.;

        if(dist_sh1 / dist_neck > 1.7 || dist_sh2 / dist_neck > 1.7) //02.08.2022 bilo 3.
            return true;
    }

    return false;
}

float Skeleton::getPixelDictance(Point3f3i p1, Point3f3i p2)
{
    return sqrt(pow(p1.pixelX - p2.pixelX, 2) + pow(p1.pixelY - p2.pixelY, 2)); //!!!!!!!!!
}

cv::Rect Skeleton::getBoundingBox() //29.04.2022
{
    vector<cv::Point> vPoints;

    vPoints.push_back(cv::Point(nose.pixelX, nose.pixelY));
    vPoints.push_back(cv::Point(neck.pixelX, neck.pixelY));
    vPoints.push_back(cv::Point(rightShoulder.pixelX, rightShoulder.pixelY));
    vPoints.push_back(cv::Point(rightElbow.pixelX, rightElbow.pixelY));
    vPoints.push_back(cv::Point(rightWrist.pixelX, rightWrist.pixelY));
    vPoints.push_back(cv::Point(leftShoulder.pixelX, leftShoulder.pixelY));
    vPoints.push_back(cv::Point(leftElbow.pixelX, leftElbow.pixelY));
    vPoints.push_back(cv::Point(leftWrist.pixelX, leftWrist.pixelY));
    vPoints.push_back(cv::Point(centerPelvis.pixelX, centerPelvis.pixelY));
    vPoints.push_back(cv::Point(rightPelvis.pixelX, rightPelvis.pixelY));
    vPoints.push_back(cv::Point(rightKnee.pixelX, rightKnee.pixelY));
    vPoints.push_back(cv::Point(rightFoot.pixelX, rightFoot.pixelY));
    vPoints.push_back(cv::Point(leftPelvis.pixelX, leftPelvis.pixelY));
    vPoints.push_back(cv::Point(leftKnee.pixelX, leftKnee.pixelY));
    vPoints.push_back(cv::Point(leftFoot.pixelX, leftFoot.pixelY));
    vPoints.push_back(cv::Point(rightEye.pixelX, rightEye.pixelY));
    vPoints.push_back(cv::Point(leftEye.pixelX, leftEye.pixelY));
    vPoints.push_back(cv::Point(rightEar.pixelX, rightEar.pixelY));
    vPoints.push_back(cv::Point(leftEar.pixelX, leftEar.pixelY));
    vPoints.push_back(cv::Point(leftFoot2.pixelX, leftFoot2.pixelY));
    vPoints.push_back(cv::Point(rightFoot2.pixelX, rightFoot2.pixelY));

    int x_min = 10000;
    int y_min = 10000;
    int x_max = 0;
    int y_max = 0;

    int n = vPoints.size();
    for(int i=0; i<n; i++)
    if(vPoints[i].x > 0 && vPoints[i].y > 0)
    {
        //printf("%d %d\n", vPoints[i].x, vPoints[i].y);

        if(vPoints[i].x < x_min)
            x_min = vPoints[i].x;

        if(vPoints[i].y < y_min)
            y_min = vPoints[i].y;

        if(vPoints[i].x > x_max)
            x_max = vPoints[i].x;

        if(vPoints[i].y > y_max)
            y_max = vPoints[i].y;
    }

    cv::Rect r_ret;
    r_ret.x = x_min;
    r_ret.y = y_min;
    r_ret.width = x_max - x_min;
    r_ret.height = y_max - y_min;

    vPoints.clear();

    return r_ret;
}


double Skeleton::GetQuantSkeleton() //06.05.2022
{
    vector<cv::Point> vPoints;

    vPoints.push_back(cv::Point(nose.pixelX, nose.pixelY));
    vPoints.push_back(cv::Point(neck.pixelX, neck.pixelY));
    vPoints.push_back(cv::Point(rightShoulder.pixelX, rightShoulder.pixelY));
    vPoints.push_back(cv::Point(rightElbow.pixelX, rightElbow.pixelY));
    vPoints.push_back(cv::Point(rightWrist.pixelX, rightWrist.pixelY));
    vPoints.push_back(cv::Point(leftShoulder.pixelX, leftShoulder.pixelY));
    vPoints.push_back(cv::Point(leftElbow.pixelX, leftElbow.pixelY));
    vPoints.push_back(cv::Point(leftWrist.pixelX, leftWrist.pixelY));
    vPoints.push_back(cv::Point(centerPelvis.pixelX, centerPelvis.pixelY));
    vPoints.push_back(cv::Point(rightPelvis.pixelX, rightPelvis.pixelY));
    vPoints.push_back(cv::Point(rightKnee.pixelX, rightKnee.pixelY));
    vPoints.push_back(cv::Point(rightFoot.pixelX, rightFoot.pixelY));
    vPoints.push_back(cv::Point(leftPelvis.pixelX, leftPelvis.pixelY));
    vPoints.push_back(cv::Point(leftKnee.pixelX, leftKnee.pixelY));
    vPoints.push_back(cv::Point(leftFoot.pixelX, leftFoot.pixelY));
    vPoints.push_back(cv::Point(rightEye.pixelX, rightEye.pixelY));
    vPoints.push_back(cv::Point(leftEye.pixelX, leftEye.pixelY));
    vPoints.push_back(cv::Point(rightEar.pixelX, rightEar.pixelY));
    vPoints.push_back(cv::Point(leftEar.pixelX, leftEar.pixelY));
    vPoints.push_back(cv::Point(leftFoot2.pixelX, leftFoot2.pixelY));
    vPoints.push_back(cv::Point(rightFoot2.pixelX, rightFoot2.pixelY));

    int n = vPoints.size();
    int pnt_ok = 0;
    for(int i=0; i<n; i++)
    if(vPoints[i].x > 0 && vPoints[i].y > 0)
    {
        pnt_ok++;
    }

    double res = (double)pnt_ok/n;
    //printf("%.1f\n", res);
    return res;
}

bool Skeleton::isSkeletonRectOkSize(int _iMin, int _iMax)
{
    cv::Rect bBox = getBoundingBox();
    //printf("getBoundingBox() = %d %d\n", bBox.width, bBox.height);

    if((bBox.width >= _iMin && bBox.width <= _iMax) || (bBox.height >= _iMin && bBox.height <= _iMax))
        return true;

    return false;
}

//02.08.2022 наклон туловища в градусах [0 - 90]
int Skeleton::TorsoTiltDeg()
{
    if(isPartPresent(neck) && isPartPresent(centerPelvis))
    {
        //print angle
        double x1 = neck.pixelX;
        double y1 = neck.pixelY;
        double x2 = centerPelvis.pixelX;
        double y2 = centerPelvis.pixelY;
        double angle_rot = fabs(90. - atan2(y2 - y1, x2 - x1) * 57.296);
        //printf("%.1f\n", angle_rot);
        return (int)angle_rot;
    }

    return 0;
}

//руки к груди
bool Skeleton::isHandsChest()
{
    //24.10.2022 comm
    /*
    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(rightWrist))
    {
        if(isLower(rightWrist, neck))
        {
        double dist_neck = getPixelDictance(nose, neck);
        double dist_wr1 = getPixelDictance(rightWrist, neck);
        if(dist_wr1 > dist_neck*0.9 && dist_wr1 < dist_neck*2.2)
            return true;
        }
    }

    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(leftWrist))
    {
        if(isLower(leftWrist, neck))
        {
        double dist_neck = getPixelDictance(nose, neck);
        double dist_wr1 = getPixelDictance(leftWrist, neck);
        if(dist_wr1 > dist_neck*0.9 && dist_wr1 < dist_neck*2.2)
            return true;
        }
    }
    */

    //24.10.2022
    bool bRight = false;
    if(isPartPresent(rightWrist) && isPartPresent(neck) &&
       isPartPresent(rightElbow) && isPartPresent(leftShoulder) && isPartPresent(rightShoulder))
    {
        if(isLefter(rightShoulder, rightWrist) && isLefter(rightWrist, leftShoulder))
        {
            if(isLower(rightWrist, rightShoulder) && isLower(rightWrist, leftShoulder))
            //if(isLower(rightElbow, rightWrist))
            {
                double dist_Shoulder = getPixelDictance(leftShoulder, rightShoulder) * 0.8;
                double dist_chest = getPixelDictance(rightWrist, neck);

                if(dist_chest < dist_Shoulder)
                {
                    double a1 = getPixelDictance(rightElbow, rightShoulder);
                    double a2 = getPixelDictance(rightWrist, rightElbow);
                    if(dist_Shoulder/(a1 + a2) < 0.7)
                    {
                    //printf("%.1f\n", dist_Shoulder/(a1+a2));
                    //return true;
                    bRight = true;
                    }
                }
            }
        }
    }

    //24.10.2022
    bool bLeft = false;
    if(isPartPresent(leftWrist) && isPartPresent(neck) &&
       isPartPresent(leftElbow) && isPartPresent(leftShoulder) && isPartPresent(rightShoulder))
    {
        if(isLefter(rightShoulder, leftWrist) && isLefter(leftWrist, leftShoulder))
        {
            if(isLower(leftWrist, rightShoulder) && isLower(leftWrist, leftShoulder))
            //if(isLower(leftElbow, leftWrist))
            {
                double dist_Shoulder = getPixelDictance(leftShoulder, rightShoulder) * 0.8;
                double dist_chest = getPixelDictance(leftWrist, neck);

                if(dist_chest < dist_Shoulder)
                {
                    double a1 = getPixelDictance(leftElbow, leftShoulder);
                    double a2 = getPixelDictance(leftWrist, leftElbow);
                    if(dist_Shoulder/(a1 + a2) < 0.7)
                    {
                    //printf("%.1f\n", dist_Shoulder/(a1+a2));
                    //return true;
                    bLeft = true;
                    }
                }
            }
        }
    }

    return bRight && bLeft;
}

//рука лицо
bool Skeleton::isFacepalm()
{
    //24.10.2022 comm
    /*
    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(rightWrist))
    {
        double dist_neck = getPixelDictance(nose, neck);
        double dist_wr1 = getPixelDictance(rightWrist, nose);
        if(dist_wr1 < dist_neck*1.8)
            return true;
    }

    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(leftWrist))
    {
        double dist_neck = getPixelDictance(nose, neck);
        double dist_wr1 = getPixelDictance(leftWrist, nose);
        if(dist_wr1 < dist_neck*1.8)
            return true;
    }
    */

    //24.10.2022
    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(rightWrist) &&
       isPartPresent(rightElbow) && isPartPresent(leftShoulder) && isPartPresent(rightShoulder))
    {
        double dist_Shoulder = getPixelDictance(leftShoulder, rightShoulder) * 0.6;
        double dist_facepalm = getPixelDictance(rightWrist, nose);

        if(dist_facepalm < dist_Shoulder)
        {
            double a1 = getPixelDictance(rightElbow, rightShoulder);
            double a2 = getPixelDictance(rightWrist, rightElbow);
            if(dist_Shoulder/(a1 + a2) < 0.4)
            {
            //printf("%.1f\n", dist_Shoulder/(a1+a2));
            return true;
            }
        }
    }

    if(isPartPresent(nose) && isPartPresent(neck) && isPartPresent(leftWrist) &&
       isPartPresent(leftElbow) && isPartPresent(leftShoulder) && isPartPresent(rightShoulder))
    {
        double dist_Shoulder = getPixelDictance(leftShoulder, rightShoulder) * 0.6;
        double dist_facepalm = getPixelDictance(leftWrist, nose);

        if(dist_facepalm < dist_Shoulder)
        {
            double a1 = getPixelDictance(leftElbow, leftShoulder);
            double a2 = getPixelDictance(leftWrist, leftElbow);
            if(dist_Shoulder/(a1 + a2) < 0.4)
            {
            //printf("%.1f\n", dist_Shoulder/(a1+a2));
            return true;
            }
        }
    }

    return false;
}
