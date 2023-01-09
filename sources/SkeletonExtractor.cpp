#include "SkeletonExtractor.h"

SkeletonExtractor::SkeletonExtractor(){

}

void SkeletonExtractor::createFromOpenpose(std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>> &datum, float wk, float hk, vector<Skeleton> &_vs)
{
    //    nose;             //0
    //    neck;             //1
    //    rightShoulder;    //2
    //    rightElbow;       //3
    //    rightWrist;       //4
    //    leftShoulder;     //5
    //    leftElbow;        //6
    //    leftWrist;        //7
    //    centerPelvis;     //8
    //    rightPelvis;      //9
    //    rightKnee;        //10
    //    rightFoot;        //11
    //    leftPelvis;       //12
    //    leftKnee;         //13
    //    leftFoot;         //14
    //    rightEye;         //15
    //    leftEye;          //16
    //    rightEar;         //17
    //    leftEar;          //18
    //    leftFoot2;          //19
    //    rightFoot2;          //22

    _vs.clear();

    if(datum==NULL || datum->empty())
        return;

    op::Array<float> poseKeypoints = datum->at(0)->poseKeypoints;

    if(poseKeypoints.empty())
        return;

    int n = poseKeypoints.getSize().at(0);
    for(int i=0; i<n; i++)
    {
    Skeleton skeleton = Skeleton();

    int numSkeleton = i;
    int start = numSkeleton * 25 * 3;

    skeleton.nose = Point3f3i((int)(poseKeypoints.at(start + (0 * 3)) * wk), (int)(poseKeypoints.at(start + (0 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (0 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.neck = Point3f3i((int)(poseKeypoints.at(start + (1 * 3)) * wk), (int)(poseKeypoints.at(start + (1 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (1 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightShoulder = Point3f3i((int)(poseKeypoints.at(start + (2 * 3)) * wk), (int)(poseKeypoints.at(start + (2 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (2 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightElbow = Point3f3i((int)(poseKeypoints.at(start + (3 * 3)) * wk), (int)(poseKeypoints.at(start + (3 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (3 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightWrist = Point3f3i((int)(poseKeypoints.at(start + (4 * 3)) * wk), (int)(poseKeypoints.at(start + (4 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (4 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftShoulder = Point3f3i((int)(poseKeypoints.at(start + (5 * 3)) * wk), (int)(poseKeypoints.at(start + (5 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (5 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftElbow = Point3f3i((int)(poseKeypoints.at(start + (6 * 3)) * wk), (int)(poseKeypoints.at(start + (6 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (6 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftWrist = Point3f3i((int)(poseKeypoints.at(start + (7 * 3)) * wk), (int)(poseKeypoints.at(start + (7 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (7 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.centerPelvis= Point3f3i((int)(poseKeypoints.at(start + (8 * 3)) * wk), (int)(poseKeypoints.at(start + (8 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (8 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightPelvis = Point3f3i((int)(poseKeypoints.at(start + (9 * 3)) * wk), (int)(poseKeypoints.at(start + (9 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (9 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightKnee = Point3f3i((int)(poseKeypoints.at(start + (10 * 3)) * wk), (int)(poseKeypoints.at(start + (10 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (10 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightFoot = Point3f3i((int)(poseKeypoints.at(start + (11 * 3)) * wk), (int)(poseKeypoints.at(start + (11 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (11 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftPelvis = Point3f3i((int)(poseKeypoints.at(start + (12 * 3)) * wk), (int)(poseKeypoints.at(start + (12 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (12 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftKnee = Point3f3i((int)(poseKeypoints.at(start + (13 * 3)) * wk), (int)(poseKeypoints.at(start + (13 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (13 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftFoot = Point3f3i((int)(poseKeypoints.at(start + (14 * 3)) * wk), (int)(poseKeypoints.at(start + (14 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (14 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightEye = Point3f3i((int)(poseKeypoints.at(start + (15 * 3)) * wk), (int)(poseKeypoints.at(start + (15 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (15 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftEye = Point3f3i((int)(poseKeypoints.at(start + (16 * 3)) * wk), (int)(poseKeypoints.at(start + (16 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (16 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightEar = Point3f3i((int)(poseKeypoints.at(start + (17 * 3)) * wk), (int)(poseKeypoints.at(start + (17 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (17 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftEar = Point3f3i((int)(poseKeypoints.at(start + (18 * 3)) * wk), (int)(poseKeypoints.at(start + (18 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (18 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.leftFoot2 = Point3f3i((int)(poseKeypoints.at(start + (19 * 3)) * wk), (int)(poseKeypoints.at(start + (19 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (19 * 3 + 2)) * 100.)); //0 03.10.2022
    skeleton.rightFoot2 = Point3f3i((int)(poseKeypoints.at(start + (22 * 3)) * wk), (int)(poseKeypoints.at(start + (22 * 3 + 1)) * hk), (int)(poseKeypoints.at(start + (22 * 3 + 2)) * 100.)); //0 03.10.2022

    _vs.push_back(skeleton);
    }

    //face 25.07.2022
    op::Array<float> faceKeypoints = datum->at(0)->faceKeypoints;

    if(faceKeypoints.empty())
        return;


    int numberPeopleDetected = faceKeypoints.getSize().at(0);
    int numberFaceParts = faceKeypoints.getSize().at(1);
    //printf("numberPeopleDetected = %d, facePoints = %d\n", numberPeopleDetected, numberFaceParts);
    //if(!_vs.empty())
    for(int person=0; person < _vs.size(); person++) //padat moget!!!
    for(int part = 0; part < numberFaceParts; part++)
    {
        // Slightly more efficient version
        //int person = 0;
           const auto baseIndex = faceKeypoints.getSize(2)*(person*numberFaceParts + part);
           const auto x = faceKeypoints[baseIndex];
           const auto y = faceKeypoints[baseIndex + 1];
           const auto score = faceKeypoints[baseIndex + 2];

           //printf("%f\n", (float)score);

        Point3f3i p_face((int)x, (int)y, (int)(score*100.));
        _vs[person].face.push_back(p_face); //!!! person
    }


    //return;
    /////////////////
    //hands 26.07.2022
    op::Array<float> handsKeypointsL = datum->at(0)->handKeypoints[0];

    if(handsKeypointsL.empty())
        return;

    // Common parameters needed
    numberPeopleDetected = handsKeypointsL.getSize().at(0);
    int numberHandPartsL = handsKeypointsL.getSize().at(1);
    //printf("numberPeopleDetected = %d, numberHandPartsL = %d\n", numberPeopleDetected, numberHandPartsL);
    for(int person=0; person < _vs.size(); person++) //padat moget!!!
    for(int part = 0; part < numberHandPartsL; part++)
    {
        // Slightly more efficient version
        //int person = 0;
           const auto baseIndex = handsKeypointsL.getSize(2)*(person*numberHandPartsL + part);
           const auto x = handsKeypointsL[baseIndex];
           const auto y = handsKeypointsL[baseIndex + 1];
           const auto score = handsKeypointsL[baseIndex + 2];

           //printf("%f\n", (float)score);

        Point3f3i p_handL((int)x, (int)y, (int)(score*100.));
        _vs[person].lhand.push_back(p_handL);
    }

    //RRR
    op::Array<float> handsKeypointsR = datum->at(0)->handKeypoints[1];

    if(handsKeypointsR.empty())
        return;

    // Common parameters needed
    numberPeopleDetected = handsKeypointsR.getSize().at(0);
    int numberHandPartsR = handsKeypointsR.getSize().at(1);
    //printf("numberPeopleDetected = %d, numberHandPartsL = %d\n", numberPeopleDetected, numberHandPartsL);
    for(int person=0; person < _vs.size(); person++) //padat moget!!!
    for(int part = 0; part < numberHandPartsR; part++)
    {
        // Slightly more efficient version
        //int person = 0;
           const auto baseIndex = handsKeypointsR.getSize(2)*(person*numberHandPartsR + part);
           const auto x = handsKeypointsR[baseIndex];
           const auto y = handsKeypointsR[baseIndex + 1];
           const auto score = handsKeypointsR[baseIndex + 2];

           //printf("%f\n", (float)score);

        Point3f3i p_handR((int)x, (int)y, (int)(score*100.));
        _vs[person].rhand.push_back(p_handR);
    }


    return;// skeleton;
}



















