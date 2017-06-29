#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
IplImage* cutImage(IplImage* src, CvRect rect) {
	   cvSetImageROI(src, rect);
	   IplImage* dst = cvCreateImage(cvSize(rect.width, rect.height),
		        src->depth,
		        src->nChannels);
	   cvCopy(src, dst, 0);
	   cvResetImageROI(src);
	   return dst;
}
string face_cascade_name = "I:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
//string window_name = "人脸识别";
IplImage* detectAndDisplay1(Mat frame) {
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (int i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}
	IplImage* temp = cutImage(&(IplImage(frame)), cvRect(faces.begin()->x, faces.begin()->y, 500, 500));
	return temp;
};
IplImage* detectAndDisplay(Mat frame) {
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (int i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}
	IplImage* temp = cutImage(&(IplImage(frame)), cvRect(faces.begin()->x, faces.begin()->y, 400, 400));
	//namedWindow("谭景凤", WINDOW_NORMAL);
	//cvShowImage("谭景凤", temp);																									//CvMat *faceImg =c();
	//cvNamedWindow((const char *)&window_name, WINDOW_NORMAL);
	//namedWindow("人脸检测", WINDOW_NORMAL)																								imshow("人脸检测", frame);*/
	//Rect a = cvRect(faces.begin()->x, faces.begin()->y, 750, 750);
	return temp;
};
//CV_IS_SUBDIV2D * a;
//cv::(Subdiv2D.point)
int main(int argc, char** argv) {
	/*Mat image;
	argc = 2;
	image = imread("C:\\Users\\zhh\\Desktop\\图片\\中年图片\\8.jpg");*/
	argc = 2;
	Mat src1, src2;
	IplImage *src3, *src4;
	src1 = imread("C:\\Users\\zhh\\Desktop\\1.jpg");
	src2 = imread("C:\\Users\\zhh\\Desktop\\2.jpg");
	if (argc != 2 || !src1.data) {
		printf("[error] 没有图片\n");
		return -1;
	}
	if (!face_cascade.load(face_cascade_name)) {
		printf("[error] 无法加载级联分类器文件！\n");
		return -1;
	}
	if (argc == 2 && src1.data&& src2.data)
	{
		/*int x = 1;
		int y = 1;
		int width = 1;
		int height = 1;*/
		double alpha = 0.35;
		double beta = 0.65;
		src3 = detectAndDisplay(src1);
		src4 = detectAndDisplay(src2);
		//cvSetImageROI(src1, cvRect(x, y, width, height));
		//cvSetImageROI(src2, cvRect(0, 0, width, height));
		cvAddWeighted(src3, alpha, src4, beta, 0.0, src3);
		cvResetImageROI(src3);
		cvNamedWindow("合成图片", CV_WINDOW_NORMAL);
		cvShowImage("合成图片", src3);
		cvWaitKey();
	}
	return 0;
}
