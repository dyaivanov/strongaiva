#include "EyeDetector.h"

/** Нумерация особых точек, отвечающих за глаза и переносицу
*     37   38                43   44
* 36     *     39   27   42     *     45
*     41   40                47   46
*/

cv::Point EyeDetector::unscalePoint(int target_width, cv::Point p, cv::Rect origSize) {
	float ratio = (float)target_width / origSize.width;
	int x = round(p.x / ratio);
	int y = round(p.y / ratio);
	return cv::Point(x, y);
}

void EyeDetector::scaleToFastSize(int target_width, const cv::Mat &src, cv::Mat &dst) {
	cv::resize(src, dst, cv::Size(target_width, (((float)target_width) / src.cols) * src.rows));
}

bool EyeDetector::inMat(cv::Point p, int rows, int cols) {
	return p.x >= 0 && p.x < cols && p.y >= 0 && p.y < rows;
}

cv::Rect EyeDetector::findBoundingBoxFromShapes(/*dlib::full_object_detection*/cFaceKeyPoint &points, int index1, int index2, int paddingX, int paddingY) { //29.07.2022
	int left = 10000;
	int top = 10000;
	int right = -10000;
	int bottom = -10000;
	int width = 0;
	int height = 0;
	for (int i = index1; i <= index2; i++) {
		if (points.part(i).x() < left) {
			left = points.part(i).x();
		}
		if (points.part(i).x() > right) {
			right = points.part(i).x();
		}
        if (points.part(i).y() < top) {
			top = points.part(i).y();
		}
        if (points.part(i).y() > bottom) {
			bottom = points.part(i).y();
		}
	}
	left = left - paddingX;
	top = top - paddingY;
	width = right - left + paddingX;
	height = bottom - top + paddingY;
	return cv::Rect(left, top, width, height);
}

cv::Mat EyeDetector::computeMatXGradient(const cv::Mat &mat) {
	cv::Mat out(mat.rows, mat.cols, CV_64F);
	for (int y = 0; y < mat.rows; ++y) {
		const uchar *Mr = mat.ptr<uchar>(y);
		double *Or = out.ptr<double>(y);
		Or[0] = Mr[1] - Mr[0];
		for (int x = 1; x < mat.cols - 1; ++x) {
			Or[x] = (Mr[x + 1] - Mr[x - 1]) / 2.0;
		}
		Or[mat.cols - 1] = Mr[mat.cols - 1] - Mr[mat.cols - 2];
	}
	return out;
}

double EyeDetector::computeDynamicThreshold(const cv::Mat &mat, double stdDevFactor) {
	cv::Scalar stdMagnGrad, meanMagnGrad;
	cv::meanStdDev(mat, meanMagnGrad, stdMagnGrad);
	double stdDev = stdMagnGrad[0] / sqrt(mat.rows * mat.cols);
	return stdDevFactor * stdDev + meanMagnGrad[0];
}

cv::Mat EyeDetector::matrixMagnitude(const cv::Mat &matX, const cv::Mat &matY) {
	cv::Mat mags(matX.rows, matX.cols, CV_64F);
	for (int y = 0; y < matX.rows; ++y) {
		const double *Xr = matX.ptr<double>(y), *Yr = matY.ptr<double>(y);
		double *Mr = mags.ptr<double>(y);
		for (int x = 0; x < matX.cols; ++x) {
			double gX = Xr[x], gY = Yr[x];
			double magnitude = sqrt(gX * gX + gY * gY);
			Mr[x] = magnitude;
		}
	}
	return mags;
}

cv::Mat EyeDetector::floodKillEdges(cv::Mat &mat) {
	rectangle(mat, cv::Rect(0, 0, mat.cols, mat.rows), 255);
	cv::Mat mask(mat.rows, mat.cols, CV_8U, 255);
	std::queue<cv::Point> toDo;
	toDo.push(cv::Point(0, 0));
	while (!toDo.empty()) {
		cv::Point p = toDo.front();
		toDo.pop();
		if (mat.at<float>(p) == 0.0f) {
			continue;
		}
		cv::Point np(p.x + 1, p.y);
		if (inMat(np, mat.rows, mat.cols)) toDo.push(np);
		np.x = p.x - 1; np.y = p.y;
		if (inMat(np, mat.rows, mat.cols)) toDo.push(np);
		np.x = p.x; np.y = p.y + 1;
		if (inMat(np, mat.rows, mat.cols)) toDo.push(np);
		np.x = p.x; np.y = p.y - 1;
		if (inMat(np, mat.rows, mat.cols)) toDo.push(np);
		mat.at<float>(p) = 0.0f;
		mask.at<uchar>(p) = 0;
	}
	return mask;
}


//16.07.2021!!!
//27.06.2021 FF centroid
#define _USE_MATH_DEFINES
#include <math.h> // число pi
bool GetCentroidFF16(const cv::Mat& shot, const int tresh, double& x_cent, double& y_cent)
{
    //unsigned short* Data_shot = (unsigned short*)shot.data; //8(char) or 16(short)bit
    unsigned char* Data_shot = (unsigned char*)shot.data; //8(char) or 16(short)bit //29.06.2021

    int cbnd = shot.cols;
    int rbnd = shot.rows;

    cv::Mat vec = cv::Mat::zeros(rbnd, cbnd, CV_64FC1);
    double* Data_vec = (double*)vec.data;

    for (int i = 0; i < cbnd * rbnd; i++)
    {
        Data_shot[i] = 255 - Data_shot[i]; //inv 30.07.2022

        if (Data_shot[i] > tresh) //porog filter!?!!!!!!!!!!!!!<<<
            Data_vec[i] = Data_shot[i];
        else
        {
            Data_vec[i] = 0;
            Data_shot[i] = 0;
        }
    }

    //printf("\n");
    cv::Mat SIN_A = cv::Mat::zeros(1, rbnd, CV_64FC1);
    double* DataSA = (double*)SIN_A.data;
    for (int i = 1; i < rbnd + 1; i++)
    {
        DataSA[i - 1] = sin((i - 1.) * 2. * M_PI / (rbnd - 1));
        //printf("%.3lf\n", DataSA[i - 1]);
    }

    //printf("\n");
    cv::Mat COS_A = cv::Mat::zeros(1, rbnd, CV_64FC1);
    double* DataCA = (double*)COS_A.data;
    for (int i = 1; i < rbnd + 1; i++)
    {
        DataCA[i - 1] = cos((i - 1.) * 2. * M_PI / (rbnd - 1));
        //printf("%.3lf\n", DataCA[i - 1]);
    }

    ///

    //printf("\n");
    cv::Mat SIN_B = cv::Mat::zeros(cbnd, 1, CV_64FC1);
    double* DataSB = (double*)SIN_B.data;
    for (int i = 1; i < cbnd + 1; i++)
    {
        DataSB[i - 1] = sin((i - 1.) * 2. * M_PI / (cbnd - 1));
        //printf("%.3lf\n", DataSB[i - 1]);
    }

    //printf("\n");
    cv::Mat COS_B = cv::Mat::zeros(cbnd, 1, CV_64FC1);
    double* DataCB = (double*)COS_B.data;
    for (int i = 1; i < cbnd + 1; i++)
    {
        DataCB[i - 1] = cos((i - 1.) * 2. * M_PI / (cbnd - 1));
        //printf("%.3lf\n", DataCB[i - 1]);
    }




    double a = sum(COS_A * vec)[0];
    double b = sum(SIN_A * vec)[0];
    double c = sum(vec * COS_B)[0];
    double d = sum(vec * SIN_B)[0];

    //printf("\n\n %.5lf\n", a);
    //printf("\n\n %.5lf\n", b);
    //printf("\n\n %.5lf\n", c);
    //printf("\n\n %.5lf\n", d);


    ///
    double rphi = 0.;
    double cphi = 0.;

    if (a > 0.)
    {
        if (b > 0.)
            rphi = 0.;
        else
            rphi = 2. * M_PI;
    }
    else
        rphi = M_PI;

    if (c > 0.)
    {
        if (d > 0.)
            cphi = 0.;
        else
            cphi = 2. * M_PI;
    }
    else
        cphi = M_PI;



    double y = (atan(b / a) + rphi) * (rbnd - 1.) / 2. / M_PI + 1.;
    double x = (atan(d / c) + cphi) * (cbnd - 1.) / 2. / M_PI + 1.;


    if (isnan(x) == 0 && isnan(y) == 0)
    {
        x_cent = x;
        y_cent = y;
        return true;
    }

    return false;

    //printf("x = %.3lf, y = %.3lf\n", x, y);
    //DrawCross(shot, x, y, "bit8");
    //imshow("shot", shot);
    //waitKey(1);
}


bool EyeDetector::findEyes(cv::Mat faceROI) {
    leftEyeRegion = findBoundingBoxFromShapes(faceDetails, 36, 41, 0, 0);
    rightEyeRegion = findBoundingBoxFromShapes(faceDetails, 42, 47, 0, 0);

    //printf("4\n"); //17.10.2022
    //printf("%d %d %d %d\n", leftEyeRegion.x, leftEyeRegion.y, leftEyeRegion.x + leftEyeRegion.width, leftEyeRegion.y + leftEyeRegion.height);
    //printf("%d %d %d %d\n", rightEyeRegion.x, rightEyeRegion.y, rightEyeRegion.x + rightEyeRegion.width, rightEyeRegion.y + rightEyeRegion.height); //!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Области глаз выходят за пределы ROI лица 18.10.2022
    cv::Point p_test1(leftEyeRegion.x, leftEyeRegion.y);
    cv::Point p_test2(leftEyeRegion.x + leftEyeRegion.width, leftEyeRegion.y + leftEyeRegion.height);
    cv::Point p_test3(rightEyeRegion.x, rightEyeRegion.y);
    cv::Point p_test4(rightEyeRegion.x + rightEyeRegion.width, rightEyeRegion.y + rightEyeRegion.height);
    int rows_test = faceROI.rows;
    int cols_test = faceROI.cols;
    if(!inMat(p_test1, rows_test, cols_test) || !inMat(p_test2, rows_test, cols_test) || !inMat(p_test3, rows_test, cols_test) || !inMat(p_test4, rows_test, cols_test))
    {
        printf("EyeRegion out of face!\n");
        return false;
    }

    //02.08.2022 проверка чтобы сильно узкие не были
    if(leftEyeRegion.width <=2 || leftEyeRegion.height <=2 || rightEyeRegion.width <=2 || rightEyeRegion.height <=2) //падало на нулевом размере !!!
    {
        //printf("leftEyeRegion.width <=0\n");
        return false;
    }

    calculateEye(leftPupil, faceROI, leftEyeRegion, 1);
    calculateEye(rightPupil, faceROI, rightEyeRegion, 0);

    //printf("5\n"); //17.10.2022

    //30.07.2022 comm
    /*
    rightPupil.x += rightEyeRegion.x;
	rightPupil.y += rightEyeRegion.y;
	leftPupil.x += leftEyeRegion.x;
	leftPupil.y += leftEyeRegion.y;
    */

    //debug
    //30.07.2022 //!!!!!!!!!!!!!!!!!!!!
    //printf("123 %d %d\n", leftPupil.x - leftEyeRegion.x, leftPupil.y - leftEyeRegion.y);
    cv::Point lp_debug(leftPupil.x - leftEyeRegion.x, leftPupil.y - leftEyeRegion.y);
    cv::Point rp_debug(rightPupil.x - rightEyeRegion.x, rightPupil.y - rightEyeRegion.y);


    //centriod L
    double x_centL = 0.;
    double y_centL = 0.;
    if(GetCentroidFF16(l_eye_debug, 200, x_centL, y_centL)) //200 - porog
    {
        //printf("%.1f %.1f\n", x_centL, y_centL);
        cv::circle(l_eye_debug, cv::Point(x_centL, y_centL), 3, cv::Scalar(0, 0, 0, 255), 1);
        leftPupil.x = x_centL;
        leftPupil.y = y_centL;
        leftPupil = unscalePoint(EYE_PROCESSING_FRAME_WIDTH, leftPupil, leftEyeRegion);
    }

    //
    leftPupil.x += leftEyeRegion.x;
    leftPupil.y += leftEyeRegion.y;

    //centriod R
    double x_centR = 0.;
    double y_centR = 0.;
    if(GetCentroidFF16(r_eye_debug, 200, x_centR, y_centR)) //200 - porog
    {
        //printf("%.1f %.1f\n", x_centL, y_centL);
        //cv::circle(r_eye_debug, cv::Point(x_centR, y_centR), 3, cv::Scalar(0, 0, 0, 255), 1);
        rightPupil.x = x_centR;
        rightPupil.y = y_centR;
        rightPupil = unscalePoint(EYE_PROCESSING_FRAME_WIDTH, rightPupil, rightEyeRegion);
    }
    //

    //
    rightPupil.x += rightEyeRegion.x;
    rightPupil.y += rightEyeRegion.y;

    //test poly
    //vector<cv::Point> pts = {cv::Point(0,0), cv::Point(20,0), cv::Point(20,20)};//, cv::Point(), cv::Point(), cv::Point()};
    //cv::fillConvexPoly(l_eye_debug, pts, cv::Scalar(0,0,0));
    //
    //cv::circle(l_eye_debug, lp_debug, 2, cv::Scalar(255, 255, 255, 255), 1);
    //cv::circle(r_eye_debug, rp_debug, 2, cv::Scalar(255, 255, 255, 255), 1);

    //print debug !!!
    //imshow("eyeL", l_eye_debug);
    //cv::waitKey(1);

    return true;
}

void EyeDetector::FillEyeAround(cv::Mat &_eyeROIUnscaled, cv::Rect &eye, bool left_eye)
{
    cv::Mat mask_bin = _eyeROIUnscaled.clone();

    //занулить все пиксели маски черным
    for (int y = 0; y < mask_bin.rows; ++y)
        {
        unsigned char *row = mask_bin.ptr<unsigned char>(y);
        for (int x = 0; x < mask_bin.cols; ++x)
            {
            row[x] = 0;
            }
        }

    //нарисовать белым на маске область глаза
    vector<cv::Point> pts;
    //
    if(left_eye)
    {
        for(int i=36; i<=41; i++)
        {
            cv::Point ppp(faceDetails.part(i).x() - eye.x, faceDetails.part(i).y() - eye.y);
            pts.push_back(ppp);
        }
    }
    else
    {
        for(int i=42; i<=47; i++)
        {
            cv::Point ppp(faceDetails.part(i).x() - eye.x, faceDetails.part(i).y() - eye.y);
            pts.push_back(ppp);
        }
    }
    //
    cv::fillConvexPoly(mask_bin, pts, cv::Scalar(255,255,255));

    //морфологическое расширение области глаза !!!!!!!!!!!!!!!!!!!!!
    //..

    //удалять потом мелкие связные области, оставить одну самую большую !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //..

    //применить маску для затенения всего вне глаза
    for (int y = 0; y < mask_bin.rows; ++y)
        {
        unsigned char *row = mask_bin.ptr<unsigned char>(y);
        unsigned char *row_res = _eyeROIUnscaled.ptr<unsigned char>(y);
        for (int x = 0; x < mask_bin.cols; ++x)
            {
            if(row[x] != 255)
                row_res[x] = 255;
            }
        }


    //imshow("blackwww", mask_bin);
    //cv::waitKey(1);//
}


void EyeDetector::calculateEye(cv::Point &dstPoint, cv::Mat &face, cv::Rect &eye, bool left_eye) {
	cv::Mat gradientX;
	cv::Mat gradientY;
	cv::Mat mags;
	cv::Mat weight;
    cv::Mat copy_face = face.clone(); //30.07.2022
    cv::Mat eyeROIUnscaled = copy_face(eye); //clone 30.07.2022 !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	cv::Mat eyeROI;

    //imshow("FaceP", face); //ok tut


    //зарисовать все кроме яблока 30.07.2022
    FillEyeAround(eyeROIUnscaled, eye, left_eye);



    scaleToFastSize(EYE_PROCESSING_FRAME_WIDTH, eyeROIUnscaled, eyeROI);

    //30.07.2022 debug !!!
    /*
    if(left_eye)
        l_eye_debug = eyeROI.clone();
    else
        r_eye_debug = eyeROI.clone();
    */


	float avg = 0.0f;
	for (int y = 0; y < eyeROI.rows; ++y) {
		unsigned char *row = eyeROI.ptr<unsigned char>(y);
		for (int x = 0; x < eyeROI.cols; ++x) {
			avg += (float)row[x] / 256.0f;
		}
	}
	avg /= ((float)eyeROI.rows * (float)eyeROI.cols);

    /*float sum = 0.0f;
	for (int y = 0; y < eyeROI.rows; ++y) {
		unsigned char *row = eyeROI.ptr<unsigned char>(y);
		for (int x = 0; x < eyeROI.cols; ++x) {
			float current = (float)row[x] / 256.0f;
			sum += (current - avg) * (current - avg);
		}
	}
	sum = std::sqrt(sum / ((float)eyeROI.rows * (float)eyeROI.cols));
	if (sum < 0.04f) {
		if (eyesDirection == -3) {
			eyesDirection = DIR_BRIGHTNESS_PROBLEM;
		}
		if (eyesDirection == -1) {
			eyesDirection = -3;
		}
    }*/

    //30.07.2022 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!---
    //imshow("eye", eyeROI);
    /*
    if(left_eye)
    {
        l_eye_debug = eyeROI;
    }
    else
    {
        r_eye_debug = eyeROI;
    }
    */


    // disabled by default
     cv::equalizeHist(eyeROI, eyeROI); //uncomm 25.07.2022 !!!
     cv::erode(eyeROI, eyeROI, erodeKernel3); //uncomm 25.07.2022 !!!

	calculateGradientsAndMagnitudes(eyeROI, gradientX, gradientY, mags);
	eyeROI.copyTo(weight);
    GaussianBlur(eyeROI, weight, cv::Size(5, 5), 0, 0);

    //30.07.2022 debug !!!
    if(left_eye)
        l_eye_debug = eyeROI.clone();
    else
        r_eye_debug = eyeROI.clone();


	for (int y = 0; y < weight.rows; ++y) {
		unsigned char *row = weight.ptr<unsigned char>(y);
		for (int x = 0; x < weight.cols; ++x) {
			row[x] = (255 - row[x]);
		}
	}
	cv::Mat outSum = cv::Mat::zeros(eyeROI.rows, eyeROI.cols, CV_64F);
	for (int y = 0; y < weight.rows; ++y) {
		const double *Xr = gradientX.ptr<double>(y), *Yr = gradientY.ptr<double>(y);
		for (int x = 0; x < weight.cols; ++x) {
			double gX = Xr[x], gY = Yr[x];
			if (gX <= 0.1 && gY <= 0.1) {
				continue;
			}
			testPossibleCentersFormula(x, y, weight, gX, gY, outSum);
		}
	}
	double numGradients = (weight.rows * weight.cols);
	cv::Mat out;
	outSum.convertTo(out, CV_32F, 1.0 / numGradients);
	cv::Point maxP;
	double maxVal;
	cv::minMaxLoc(out, NULL, &maxVal, NULL, &maxP);
	cv::Mat floodClone;
	double floodThresh = maxVal * 0.97;
	cv::threshold(out, floodClone, floodThresh, 0.0f, cv::THRESH_TOZERO);
	cv::Mat mask = floodKillEdges(floodClone);
	cv::minMaxLoc(out, NULL, &maxVal, NULL, &maxP, mask);
	dstPoint = unscalePoint(EYE_PROCESSING_FRAME_WIDTH, maxP, eye);
}

void EyeDetector::detectIris(cv::Mat &face, cv::Rect &eyeRegion, cv::Point &pupilCenter, int &outRadius) {
	cv::Mat eyeROI = face(eyeRegion);
	float oldSizeX = eyeROI.cols;
	float oldSizeY = eyeROI.rows;
	scaleToFastSize(PUPIL_IRIS_PROCESSING_FRAME_WIDTH, eyeROI, eyeROI);
	float kiX = oldSizeX / (float)eyeROI.cols;
	float kiY = oldSizeY / (float)eyeROI.rows;

	cv::equalizeHist(eyeROI, eyeROI);
	for (int y = 0; y < eyeROI.rows; ++y) {
		unsigned char *row = eyeROI.ptr<unsigned char>(y);
		for (int x = 0; x < eyeROI.cols; ++x) {
			if (row[x] > 160 || x < 25 || x > eyeROI.cols - 25) {
				row[x] = 255;
			}
		}
	}

	cv::Point p = cv::Point(pupilCenter.x - eyeRegion.x, pupilCenter.y - eyeRegion.y);
	p.x /= kiX;
	p.y /= kiY;
	float zx = p.x;
	// float zy = p.y;
	float zy = eyeROI.rows / 2;
	int lg = zx;
	int rg = zx;
	for (int i = 9; i < EYE_PROCESSING_FRAME_WIDTH; i++) {
		lg = i;
		if (lg < 0) break;
		unsigned char *row = eyeROI.ptr<unsigned char>(zy);
		if (row[lg] != 255) {
			lg--;
			break;
		}
	}
	for (int i = 9; i < EYE_PROCESSING_FRAME_WIDTH; i++) {
		rg = eyeROI.cols - i;
		if (rg > eyeROI.cols) break;
		unsigned char *row = eyeROI.ptr<unsigned char>(zy);
		if (row[rg] != 255) {
			rg++;
			break;
		}
	}
	cv::line(eyeROI, cv::Point(lg, zy), cv::Point(rg, zy), 0, 2);
	cv::line(eyeROI, cv::Point(p.x, 0), cv::Point(p.x, eyeROI.rows), 0, 2);



	if (std::abs((p.x - lg) - (rg - p.x)) < 20) {
		outRadius = (rg - lg) / 2 + 1;
		outRadius *= kiX;
	}
}

void EyeDetector::detectPupil(cv::Mat &face, cv::Rect &eyeRegion, cv::Point &pupilCenter, int &irisRadius, int &outRadius) {
	cv::Mat eyeROI = face(eyeRegion);
	float oldSizeX = eyeROI.cols;
	float oldSizeY = eyeROI.rows;
	scaleToFastSize(PUPIL_IRIS_PROCESSING_FRAME_WIDTH, eyeROI, eyeROI);
	float kiX = (float)oldSizeX / (float)eyeROI.cols;
	float kiY = (float)oldSizeY / (float)eyeROI.rows;
	cv::Point p = cv::Point(pupilCenter.x - eyeRegion.x, pupilCenter.y - eyeRegion.y);
	p.x /= kiX;
	p.y /= kiY;
	cv::equalizeHist(eyeROI, eyeROI);
	for (int y = 0; y < eyeROI.rows; ++y) {
		unsigned char *row = eyeROI.ptr<unsigned char>(y);
		for (int x = 0; x < eyeROI.cols; ++x) {
			if (x > p.x - irisRadius / kiX / 2 && x < p.x + irisRadius / kiX / 2 && y > eyeROI.rows / 4 && y < eyeROI.rows / 4 * 3) {
				if (row[x] > 120) {
					row[x] = 0;
				}
			}					
		}
	}
	cv::erode(eyeROI, eyeROI, erodeKernel3);

	for (int y = 0; y < eyeROI.rows; ++y) {
		unsigned char *row = eyeROI.ptr<unsigned char>(y);
		for (int x = 0; x < eyeROI.cols; ++x) {
			if (row[x] < 20) {
				row[x] = 0;
            } else {
				row[x] = 255;
			}			
		}
	}

	float zx = p.x;
	float zy = p.y;
	int lg = zx;
	int rg = zx;
	while (true) {
		lg--;
		if (lg < 6) break;
		unsigned char *row = eyeROI.ptr<unsigned char>(zy);
		bool founded = true;
		for (int j = 0; j < 6; j++) {
			if (row[lg - j] != 255) {
				founded = false;
				break;
			}
		}
		if (founded) break;
	}
	while (true) {
		rg++;
		if (rg > eyeROI.cols - 6) break;
		unsigned char *row = eyeROI.ptr<unsigned char>(zy);
		bool founded = true;
		for (int j = 0; j < 6; j++) {
			if (row[rg + j] != 255) {
				founded = false;
				break;
			}
		}
		if (founded) break;
	}
	outRadius = -1;
	if (std::abs((p.x - lg) - (rg - p.x)) < 15) {
		outRadius = (rg - lg) / 2 + 1;
		outRadius *= kiX;
	}
}

void EyeDetector::calculateGradientsAndMagnitudes(cv::Mat &im, cv::Mat &gmX, cv::Mat &gmY, cv::Mat &mags) {
	gmX = computeMatXGradient(im);
	gmY = computeMatXGradient(im.t()).t();
	mags = matrixMagnitude(gmX, gmY);
	double gradientThresh = computeDynamicThreshold(mags, 50.0);
	for (int y = 0; y < im.rows; ++y) {
		double *Xr = gmX.ptr<double>(y), *Yr = gmY.ptr<double>(y);
		const double *Mr = mags.ptr<double>(y);
		for (int x = 0; x < im.cols; ++x) {
			double gX = Xr[x], gY = Yr[x];
			double magnitude = Mr[x];
			if (magnitude > gradientThresh) {
				Xr[x] = gX / magnitude;
				Yr[x] = gY / magnitude;
			}
			else {
				Xr[x] = 0.0;
				Yr[x] = 0.0;
			}
		}
	}
}

void EyeDetector::testPossibleCentersFormula(int x, int y, const cv::Mat &weight, double gx, double gy, cv::Mat &out) {
	if (gx <= 0.1 && gy <= 0.1) return;
	for (int cy = 0; cy < out.rows; ++cy) {
		double *Or = out.ptr<double>(cy);
		const unsigned char *Wr = weight.ptr<unsigned char>(cy);
		for (int cx = 0; cx < out.cols; ++cx) {
			if (x == cx && y == cy) {
				continue;
			}
			float dx = mdArr[0][x - cx + EYE_PROCESSING_FRAME_WIDTH][y - cy + EYE_PROCESSING_FRAME_WIDTH];
			float dy = mdArr[1][x - cx + EYE_PROCESSING_FRAME_WIDTH][y - cy + EYE_PROCESSING_FRAME_WIDTH];
			float dotProduct = dx * gx + dy * gy;
			dotProduct = std::max(0.0f, dotProduct);
			Or[cx] += dotProduct * dotProduct * Wr[cx];
		}
	}
}

void EyeDetector::checkEyesDirection() {
    float avgEyeLength = (faceDetails.part(39).x() - faceDetails.part(36).x() + faceDetails.part(45).x() - faceDetails.part(42).x()) / 2.0f;
	int heightPoints[] = { 41, 37, 40, 38, 47, 43, 46, 44 };
	float avgEyeHeight = 0.0f;
	for (int i = 0; i < 8; i += 2) {
        avgEyeHeight += std::abs(faceDetails.part(heightPoints[i]).y() - faceDetails.part(heightPoints[i + 1]).y());
	}
	avgEyeHeight /= 4.0f;
    float leftEyeDL = leftPupil.x - faceDetails.part(36).x();
    float leftEyeDR = faceDetails.part(39).x() - leftPupil.x;

    bool lookBottom = true;
    bool lookUp = false;
    /** Нумерация особых точек, отвечающих за глаза и переносицу
    *     37   38                43   44
    * 36     *     39   27   42     *     45
    *     41   40                47   46
    */
    for (int i = 36; i <= 47; i++) {
        if (faceDetails.part(i).y() < faceDetails.part(27).y() + avgEyeHeight / 1.5f) {
			lookBottom = false;
		}
    }
    if (!lookBottom && avgEyeHeight > avgEyeLength * 0.35f && std::abs(leftPupil.y - faceDetails.part(37).y()) < 3 && std::abs(rightPupil.y - faceDetails.part(43).y()) < 3) {
		lookUp = true;
	}

	float look_koef = LEFT_RIGHT_SIGHT_KOEF;
	if (lookBottom || lookUp) {
		look_koef -= 0.5f;
	}

	if (leftEyeDR > leftEyeDL * look_koef) {
		eyesDirection = DIR_LEFT;
	} else if (leftEyeDL > leftEyeDR * look_koef) {
		eyesDirection = DIR_RIGHT;
	} else {
		eyesDirection = DIR_CENTER;
	}

	if (lookBottom) {
//		if (eyesDirection == DIR_LEFT) {
//			eyesDirection = DIR_DOWN_LEFT;
//		}
//		if (eyesDirection == DIR_RIGHT) {
//			eyesDirection = DIR_DOWN_RIGHT;
//		}
//        if (eyesDirection == DIR_CENTER) {
			eyesDirection = DIR_DOWN;
//        }
	} 
	if (lookUp) {
//		if (eyesDirection == DIR_LEFT) {
//			eyesDirection = DIR_UP_LEFT;
//		}
//		if (eyesDirection == DIR_RIGHT) {
//			eyesDirection = DIR_UP_RIGHT;
//		}
//        if (eyesDirection == DIR_CENTER) {
			eyesDirection = DIR_UP;
//        }
	}	
}

void EyeDetector::processing(cv::Mat &inputFace, /*dlib::full_object_detection*/cFaceKeyPoint &inputFaceDeatils) { //29.07.2022

    //imshow("FaceP", inputFace); //ok tut

    faceDetails = inputFaceDeatils;
    cv::Mat face;
    cv::cvtColor(inputFace, face, cv::COLOR_RGB2GRAY);
	eyesDirection = DIR_UNKNOWN;
    //printf("3\n"); //17.10.2022
    if(findEyes(face)) //02.08.2022 if
    {
        float dx = std::abs((rightPupil.x - rightEyeRegion.x) - (leftPupil.x - leftEyeRegion.x));
        float dy = std::abs((rightPupil.y - rightEyeRegion.y) - (leftPupil.y - leftEyeRegion.y));
        if (eyesDirection == DIR_UNKNOWN && dx < 14 && dy < 14) { //dx dy otn nada !!!
            checkEyesDirection();
        }
    }


    //comm 30.07.2022 //!!!!!!!!!!!!!!!!!!!!!!!!
    /*
	pupilIrisRatio = -1;
	leftEyeIrisRadius = -1;
	rightEyeIrisRadius = -1;
	leftEyePupilRadius = -1;
	rightEyePupilRadius = -1;
	if (eyesDirection == DIR_CENTER) {
        cv::Point lp = cv::Point(leftPupil.x, faceDetails.part(36).y());
        cv::Point rp = cv::Point(rightPupil.x, faceDetails.part(45).y());
        detectIris(face, leftEyeRegion, leftPupil, leftEyeIrisRadius);
        detectIris(face, rightEyeRegion, rightPupil, rightEyeIrisRadius);
		detectPupil(face, leftEyeRegion, leftPupil, leftEyeIrisRadius, leftEyePupilRadius);
        detectPupil(face, rightEyeRegion, rightPupil, rightEyeIrisRadius, rightEyePupilRadius);




		if (IRIS_THRUST_ONLY_TWO_EYES) {
			if (leftEyeIrisRadius < 1 || rightEyeIrisRadius < 1 || std::abs(leftEyeIrisRadius - rightEyeIrisRadius) > IRIS_PUPIL_RATIO_POSSIBLE_ERROR) {
				leftEyeIrisRadius = -1;
				rightEyeIrisRadius = -1;
			}
		}
		if (PUPIL_THRUST_ONLY_TWO_EYES) {
			if (!(leftEyePupilRadius > -1 && rightEyePupilRadius > -1 && std::abs(leftEyePupilRadius - rightEyePupilRadius) < IRIS_PUPIL_RATIO_POSSIBLE_ERROR)) {
				leftEyePupilRadius = -1;
				rightEyePupilRadius = -1;
			}
		}

		if (leftEyeIrisRadius > -1 && rightEyeIrisRadius > -1 && leftEyePupilRadius > -1 && rightEyePupilRadius > -1) {
			if (std::abs(leftEyeIrisRadius - rightEyeIrisRadius) < IRIS_PUPIL_RATIO_POSSIBLE_ERROR && std::abs(leftEyePupilRadius - rightEyePupilRadius) < IRIS_PUPIL_RATIO_POSSIBLE_ERROR) {
				pupilIrisRatio = (int)(((float)leftEyePupilRadius + (float)rightEyePupilRadius) / ((float)leftEyeIrisRadius + (float)rightEyeIrisRadius) * 100);
				if (pupilIrisRatio < 10 || pupilIrisRatio > 99) {
					pupilIrisRatio = -1;
				}
			}
		}
    }
    */
}

int EyeDetector::getGazeDirection() {
	return eyesDirection;
}

int EyeDetector::getPupilIrisRatio() {
	return pupilIrisRatio;
}

EyeDetector::EyeDetector() {
    erodeKernel3 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2 * 3 + 1, 2 * 3 + 1));
    for (float i = -EYE_PROCESSING_FRAME_WIDTH; i <= EYE_PROCESSING_FRAME_WIDTH; i++) {
        for (float j = -EYE_PROCESSING_FRAME_WIDTH; j <= EYE_PROCESSING_FRAME_WIDTH; j++) {
            float magnitude = sqrt(i * i + j * j);
            mdArr[0][(int)(i + EYE_PROCESSING_FRAME_WIDTH)][(int)(j + EYE_PROCESSING_FRAME_WIDTH)] = i / magnitude;
            mdArr[1][(int)(i + EYE_PROCESSING_FRAME_WIDTH)][(int)(j + EYE_PROCESSING_FRAME_WIDTH)] = j / magnitude;
        }
    }
}

EyeDetector::~EyeDetector() {
}
