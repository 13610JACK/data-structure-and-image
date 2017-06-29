#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
string face_cascade_name = "I:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
void  cutImage(IplImage* src, CvRect rect) {
	cvSetImageROI(src, rect);
	IplImage* dst = cvCreateImage(cvSize(rect.width, rect.height),
		src->depth,
		src->nChannels);
	cvCopy(src, dst, 0);
	cvResetImageROI(src);
	cvNamedWindow("����ͷ", CV_WINDOW_NORMAL);
	cvShowImage("����ͷ", dst);
	cvWaitKey(0);
	cvSaveImage("C:\\Users\\zhh\\Desktop\\����ͼƬ��ͷ\\����Ů\\1.jpg", dst);
	cvReleaseImage(&dst);
	cvDestroyWindow("����ͷ");
	//cvReleaseImage(&src);
	return ;
}
void  detectAndDisplay1(Mat frame) {
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	/*for (int i = 0; i < faces.size(); i++) {
	Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
	ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}*/
	cvNamedWindow("����ͷ1", CV_WINDOW_NORMAL);
	imshow("����ͷ1", frame);
	cvWaitKey(0);
	cvDestroyWindow("����ͷ1");
	int j = 0;
	cutImage(&(IplImage(frame)), cvRect((faces.begin() + j)->x, (faces.begin() + j)->y, (faces.begin() + j)->width, (faces.begin() + j)->height));
    //cutImage(&(IplImage(frame)), cvRect(faces.begin()->x, faces.begin()->y, faces.begin()->width,faces.begin()->height));
	return;
}

int main()
{
	int argc = 2;
	Mat p= imread("C:\\Users\\zhh\\Desktop\\ģ��ͼ����\\����Ů\\1.jpg");
	//cout << p.data << endl;
	//system("pause");
	if ( !p.data) {
		printf("[error] û��ͼƬ\n");
		return -1;
	}

	if (!face_cascade.load(face_cascade_name)) {
		printf("[error] �޷����ؼ����������ļ���\n");
		return -1;
	}
    detectAndDisplay1(p);
	///*cvSaveImage("C:\\Users\\zhh\\Desktop\\����ͼƬ\\������\\1.jpg", p1);
	//cvNamedWindow("����ͷ��", CV_WINDOW_NORMAL);
	//cvShowImage("����ͷ��", p1);
	//cvWaitKey(0);*/
	//cvReleaseImage(&p1);
	//cvReleaseMat((CvMat **)&p);
	//cvReleaseImage(&p);
	return 0;
}
//#include "opencv2/core/core.hpp"
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//
//#include <iostream>
//#include <stdio.h>
//
//using namespace std;
//using namespace cv;
//
//string face_cascade_name = "I:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
//CascadeClassifier face_cascade;
//string window_name = "����ʶ��";
//
//void detectAndDisplay(Mat frame);
//
//int main(int argc, char** argv) {
//	IplImage *image =cvLoadImage("C:/Users/zhh/Desktop/ģ��ͼ����/������/1.jpg");
//	int a = 1;
//	/*if (image->imageData == NULL) {
//		printf("[error] û��ͼƬ\n");
//		return -1;
//	}
//*/
//	if (!face_cascade.load(face_cascade_name)) {
//		printf("[error] �޷����ؼ����������ļ���\n");
//		return -1;
//	}
//
//	detectAndDisplay(image);
//
//	waitKey(0);
//}
//
//void detectAndDisplay(Mat frame) {
//	std::vector<Rect> faces;
//	Mat frame_gray;
//
//	cvtColor(frame, frame_gray, CV_BGR2GRAY);
//	equalizeHist(frame_gray, frame_gray);
//
//	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
//
//	for (int i = 0; i < faces.size(); i++) {
//		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
//		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
//	}
//
//	imshow(window_name, frame);
//}