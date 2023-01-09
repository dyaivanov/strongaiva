#include "faceprocessor.h"

FaceProcessor::FaceProcessor()
{
    m_iTOTAL_BLINK = 0;
    m_bEYE_CLOSE = false;

    m_bBlinked = false;
    m_bMouthOpen = false;
    m_bFaceFound = false;

    m_iPerFaceVisible = 0;

    m_iFaceTilt = 0;

    m_bFaceDown = false;
    m_bFaceLeft = false;
    m_bFaceRight = false;
    m_bLipsClosed = false;
    m_bEyebrowsRaised = false;
    m_bEyebrowsLowered = false;
}

//25.10.2022
bool FaceProcessor::isEyeClose()
{
    return m_bEYE_CLOSE;
}

void FaceProcessor::checkEyesBlinking()
{
    bool b_ok_points = true;
    for(int i=36; i<47; i++)
        if(!isPointPresent(i))
        {
            b_ok_points = false;
            break;
        }

    if(b_ok_points)
    {

    //       37   38         43   44
    //    36         39   42         45
    //       41   40         47   46
    float distA = fabs(faceDetails.part(37).y() - faceDetails.part(41).y());
    float distB = fabs(faceDetails.part(38).y() - faceDetails.part(40).y());
    float distC = fabs(faceDetails.part(36).x() - faceDetails.part(39).x());

    bool tmpBlinked = (distA + distB) / 2.0 < distC / 4.5; //4 5my

    float distA1 = fabs(faceDetails.part(43).y() - faceDetails.part(47).y());
    float distB1 = fabs(faceDetails.part(44).y() - faceDetails.part(46).y());
    float distC1 = fabs(faceDetails.part(42).x() - faceDetails.part(45).x());

    bool tmpBlinked1 = (distA1 + distB1) / 2.0 < distC1 / 4.5; //4 5my

    if (tmpBlinked && tmpBlinked1)
    {
        //printf("close\n");
        m_bEYE_CLOSE = true;
    }
    else
    {
        //printf("open\n");

        if(m_bEYE_CLOSE == true)
        {
            m_bEYE_CLOSE = false;
            m_iTOTAL_BLINK++;
            m_bBlinked = true;
        }
    }

    //printf("%d\n", TOTAL_BLINK);

    }
}

void FaceProcessor::checkMouthOpen()
{
    if(isPointPresent(62) && isPointPresent(66))
    {

    float distA = fabs(faceDetails.part(62).y() - faceDetails.part(66).y());

    if(distA > 5.)
        m_bMouthOpen = true;
    else
        m_bMouthOpen = false;
    }
}

void FaceProcessor::checkPerFaceVisible()
{
        int cnt_ok_points = 0;

        for(int fp = 0; fp < 68; fp++) //70
            if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE) //!!! score 70per
            {
            cnt_ok_points++;
            }

        //printf("per = %d\n", (100*cnt_ok_points) / 68);
        m_iPerFaceVisible = (100*cnt_ok_points) / 68;
}

void FaceProcessor::checkFaceDown() //02.08.2022
{
    if(isPointPresent(27) && isPointPresent(30) && isPointPresent(8))
    {
        double dist1 = GetDist(27, 30);
        double dist2 = GetDist(30, 8);

        //printf("%.1f %.1f\n", dist1, dist2);

        if(dist2 < dist1*1.3)
            m_bFaceDown = true;
        else
            m_bFaceDown = false;
    }
    else
        m_bFaceDown = false;
}

void FaceProcessor::checkFaceLeftRigth() //02.08.2022
{
    m_bFaceLeft = false;
    m_bFaceRight = false;

    if(isPointPresent(30) && isPointPresent(36) && isPointPresent(45))
    {
        //double dist1 = GetDist(30, 36);
        //double dist2 = GetDist(30, 45);
//        if(dist1*1.4 < dist2)
//            m_bFaceRight = true;
//        if(dist1 > dist2*1.4)
//            m_bFaceLeft = true;

        //03.08.2022
        double dist1 = GetDistX(30, 36);
        double dist2 = GetDistX(30, 45);

        //printf("%.1f %.1f\n", dist1, dist2);

        if(dist1*1.6 < dist2)
            m_bFaceRight = true;

        if(dist1 > dist2*1.6)
            m_bFaceLeft = true;
    }

    //03.08.2022 доп условие если не видно уголки глаз
    //printf("%d\n", isPointPresent(36));
}

void FaceProcessor::checkLipsClosed() //02.08.2022
{
    if(isPointPresent(48) && isPointPresent(54) && isPointPresent(50) && isPointPresent(57))
    {
        double dist1 = GetDist(48, 54);
        double dist2 = GetDist(50, 57);

        //printf("checkLipsClosed %.1f\n", dist1/dist2);

        if(dist1/dist2 > 3.7)
            m_bLipsClosed = true;
        else
            m_bLipsClosed = false;
    }
}

void FaceProcessor::checkEyebrowsUpDown()
{
    if(isPointPresent(19) && isPointPresent(68) && isPointPresent(24) && isPointPresent(69) && isPointPresent(36) && isPointPresent(39) && isPointPresent(42) && isPointPresent(45))
    {
        double dist1 = GetDist(19, 68);
        double dist2 = GetDist(24, 69);
        double dist_sr = (dist1 + dist2) / 2.;

        double dist11 = GetDist(36, 39);
        double dist22 = GetDist(42, 45);
        double dist_sr1 = (dist11 + dist22) / 2.;



        //printf("checkEyebrowsUpDown %.1f\n", dist_sr/dist_sr1);

        if(dist_sr/dist_sr1 < 0.65)
            m_bEyebrowsLowered = true;

        if(dist_sr/dist_sr1 > 1.17)
            m_bEyebrowsRaised = true;
    }
}

//25.07.2022 растяжка гистограммы
void FaceProcessor::applyCLAHE(cv::Mat &srcArry, cv::Mat &dstArry)
{
    //Function that applies the CLAHE algorithm to "dstArry".

    if (srcArry.channels() >= 3)
    {
        // READ RGB color image and convert it to Lab
        cv::Mat channel;// = new cv::Mat();
        cvtColor(srcArry, dstArry, cv::COLOR_BGR2Lab);

        // Extract the L channel
        extractChannel(dstArry, channel, 0);

        // apply the CLAHE algorithm to the L channel
        //cv::CLAHE clahe();// = cv::createCLAHE();
        cv::Ptr<cv::CLAHE> clahe;
        clahe = cv::createCLAHE();
        clahe->setClipLimit(2); //4
        clahe->setTilesGridSize(cv::Size(8,8)); //8
        clahe->apply(channel, channel);

        // Merge the the color planes back into an Lab image
        insertChannel(channel, dstArry, 0);

        // convert back to RGB
        cvtColor(dstArry, dstArry, cv::COLOR_Lab2BGR);

        // Temporary Mat not reused, so release from memory.
        channel.release();
    }

}

void FaceProcessor::process(cv::Mat &frame, cFaceKeyPoint &_faceDetails, bool _face_found, double _face_tilt) //29.07.2022
{
    m_bBlinked = false;
    m_bMouthOpen = false;
    m_bFaceFound = _face_found;
    m_iPerFaceVisible = 0;
    m_iFaceTilt = fabs(_face_tilt);
    m_bFaceDown = false;
    m_bFaceLeft = false;
    m_bFaceRight = false;
    m_bLipsClosed = false;
    m_bEyebrowsRaised = false;
    m_bEyebrowsLowered = false;

    frame.copyTo(currentFace); //31.07.2022

    if(m_bFaceFound == true)
        {
        //frame.copyTo(currentFace);

        //imshow("FaceP", currentFace); //ok tut

        //25.07.2022 !!!
        //applyCLAHE(currentFace, currentFace);
        //applyCLAHE(currentFace, currentFace); //!!!!!!!!!!!!!!!!!!!! +
        //cv::blur(currentFace, currentFace, cv::Size(3,3));


        faceDetails = _faceDetails; //29.07.2022
        //printf("1\n");
        eyeDetector.processing(currentFace, faceDetails); //17.10.2022 padaet big face
        //printf("2\n");


        checkEyesBlinking();
        checkMouthOpen();
        checkPerFaceVisible();
        checkFaceDown();
        checkFaceLeftRigth();
        checkLipsClosed();
        checkEyebrowsUpDown();
        }
}

bool FaceProcessor::GetImage(cv::Mat &_frame, bool showPoints) //26.05.2022
{

    if (showPoints && m_bFaceFound)
    {

    for(int fp = 0; fp < 68; fp++) //70
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
        int x = faceDetails.part(fp).x();
        int y = faceDetails.part(fp).y();

        cv::circle(currentFace, cv::Point(x, y), 1, cv::Scalar(255, 255, 255, 255), 1);
        }






    //отрисовка линий
    for(int fp = 0; fp < 16; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }

    for(int fp = 17; fp < 21; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }

    for(int fp = 22; fp < 26; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }

    for(int fp = 27; fp < 30; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }

    for(int fp = 31; fp < 35; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }

    for(int fp = 36; fp < 41; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }
    //
    //for(int fp = 36; fp < 41; fp++)
        if(faceDetails.part(36).prec() > OK_PER_POINT_FACE && faceDetails.part(41).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(36).x();
            int y1 = faceDetails.part(36).y();
            //
            int x1_ = faceDetails.part(41).x();
            int y1_ = faceDetails.part(41).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }


    for(int fp = 42; fp < 47; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }
    //
    if(faceDetails.part(42).prec() > OK_PER_POINT_FACE && faceDetails.part(47).prec() > OK_PER_POINT_FACE) //!!! score 70per
    {
        int x1 = faceDetails.part(42).x();
        int y1 = faceDetails.part(42).y();
        //
        int x1_ = faceDetails.part(47).x();
        int y1_ = faceDetails.part(47).y();

        cv::Point p1(x1, y1);
        cv::Point p2(x1_, y1_);
        cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
    }

    for(int fp = 48; fp < 59; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }
    //
    if(faceDetails.part(48).prec() > OK_PER_POINT_FACE && faceDetails.part(59).prec() > OK_PER_POINT_FACE) //!!! score 70per
    {
        int x1 = faceDetails.part(48).x();
        int y1 = faceDetails.part(48).y();
        //
        int x1_ = faceDetails.part(59).x();
        int y1_ = faceDetails.part(59).y();

        cv::Point p1(x1, y1);
        cv::Point p2(x1_, y1_);
        cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
    }

    for(int fp = 60; fp < 67; fp++)
        if(faceDetails.part(fp).prec() > OK_PER_POINT_FACE && faceDetails.part(fp + 1).prec() > OK_PER_POINT_FACE) //!!! score 70per
        {
            int x1 = faceDetails.part(fp).x();
            int y1 = faceDetails.part(fp).y();
            //
            int x1_ = faceDetails.part(fp+1).x();
            int y1_ = faceDetails.part(fp+1).y();

            cv::Point p1(x1, y1);
            cv::Point p2(x1_, y1_);
            cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
        }
    //
    //
    if(faceDetails.part(60).prec() > OK_PER_POINT_FACE && faceDetails.part(67).prec() > OK_PER_POINT_FACE) //!!! score 70per
    {
        int x1 = faceDetails.part(60).x();
        int y1 = faceDetails.part(60).y();
        //
        int x1_ = faceDetails.part(67).x();
        int y1_ = faceDetails.part(67).y();

        cv::Point p1(x1, y1);
        cv::Point p2(x1_, y1_);
        cv::line(currentFace, p1, p2, cv::Scalar(255, 255, 255, 255), 1);
    }

    } //show points face


    if(m_bFaceFound) //31.07.2022
    {

    //29.07.2022
    int im_w = currentFace.cols;
    int im_h = currentFace.rows;
    if(eyeDetector.getGazeDirection() == eyeDetector.DIR_CENTER) {
        cv::rectangle(currentFace, cv::Point(im_w/2-20, im_h/2-20), cv::Point(im_w/2+20, im_h/2+20), cv::Scalar(255, 255, 255), -1);
    }
    if(eyeDetector.getGazeDirection() == eyeDetector.DIR_LEFT) {
        cv::rectangle(currentFace, cv::Point(0, im_h/2-20), cv::Point(40, im_h/2+20), cv::Scalar(255, 255, 255), -1);
    }
    if(eyeDetector.getGazeDirection() == eyeDetector.DIR_RIGHT) {
        cv::rectangle(currentFace, cv::Point(im_w-40, im_h/2-20), cv::Point(im_w, im_h/2+20), cv::Scalar(255, 255, 255), -1);
    }
    if(eyeDetector.getGazeDirection() == eyeDetector.DIR_UP) {
        cv::rectangle(currentFace, cv::Point(im_w/2-20, 0), cv::Point(im_w/2+20, 40), cv::Scalar(255, 255, 255), -1);
    }
    if(eyeDetector.getGazeDirection() == eyeDetector.DIR_DOWN) {
        cv::rectangle(currentFace, cv::Point(im_w/2-20, im_h-40), cv::Point(im_w/2+20, im_h), cv::Scalar(255, 255, 255), -1);
    }


    cv::circle(currentFace, eyeDetector.leftPupil, 1, cv::Scalar(0, 255, 0), 4);
    cv::circle(currentFace, eyeDetector.rightPupil, 1, cv::Scalar(0, 255, 0), 4);

    }

    //Вывод процента видимости лица 31.07.2022
    char buf_text[50];
    sprintf(buf_text, "Видимость лица: %03d%%", m_iPerFaceVisible);
    cv::putText(currentFace, buf_text, cv::Point(20, currentFace.rows - 30), 3, 1, cv::Scalar(255, 255, 255, 255), 2); // bilo (255, 0, 0, 255);


    //26.05.2022
    _frame = currentFace.clone();

    return true;
}

bool FaceProcessor::isEyesDown()
{
    return eyeDetector.getGazeDirection() == eyeDetector.DIR_DOWN;
}

bool FaceProcessor::isEyesCenter()
{
    return eyeDetector.getGazeDirection() == eyeDetector.DIR_CENTER;
}

bool FaceProcessor::isEyesLeft()
{
    return eyeDetector.getGazeDirection() == eyeDetector.DIR_RIGHT;
}

bool FaceProcessor::isEyesRight()
{
    return eyeDetector.getGazeDirection() == eyeDetector.DIR_LEFT;
}

bool FaceProcessor::isBlinked()
{
    return m_bBlinked;
}

bool FaceProcessor::isMouthOpen()
{
    return m_bMouthOpen;
}

bool FaceProcessor::isFaceVisible()
{
    return m_bFaceFound;
}

int FaceProcessor::perFaceVisible()
{
    return m_iPerFaceVisible;
}

int FaceProcessor::GetFaceTilt()
{
    return m_iFaceTilt;
}

bool FaceProcessor::isFaceDown()
{
    return m_bFaceDown;
}

bool FaceProcessor::isFaceLeft()
{
    return m_bFaceLeft;
}

bool FaceProcessor::isFaceRight()
{
    return m_bFaceRight;
}

bool FaceProcessor::isLipsClosed()
{
    return m_bLipsClosed;
}

bool FaceProcessor::isEyebrowsRaised()
{
    return m_bEyebrowsRaised;
}

bool FaceProcessor::isEyebrowsLowered()
{
    return m_bEyebrowsLowered;
}
