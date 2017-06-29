#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui_c.h>
#include<opencv2\imgproc\imgproc_c.h>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{   
	IplImage *p = cvLoadImage("C:\\Users\\zhh\\Desktop\\剪切图片人头\\老年女\\9.jpg");
	IplImage *xin = cvCreateImage(cvSize(600, 600), 8, 3);
	cvResize(p, xin, 1);
	cout << xin->height << endl;
	cvSaveImage("C:\\Users\\zhh\\Desktop\\剪切图片人头\\老年女\\19.jpg", xin);
	cvNamedWindow("你好啊", CV_WINDOW_NORMAL);
	cvShowImage("你好啊", xin);
	cvWaitKey(0);
	cvDestroyWindow("你好啊");
	cvReleaseImage(&p);
	//cvReleaseImage(&xin);
	return 0;

}