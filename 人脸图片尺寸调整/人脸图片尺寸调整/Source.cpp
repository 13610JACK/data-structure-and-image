#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui_c.h>
#include<opencv2\imgproc\imgproc_c.h>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{   
	IplImage *p = cvLoadImage("C:\\Users\\zhh\\Desktop\\����ͼƬ��ͷ\\����Ů\\9.jpg");
	IplImage *xin = cvCreateImage(cvSize(600, 600), 8, 3);
	cvResize(p, xin, 1);
	cout << xin->height << endl;
	cvSaveImage("C:\\Users\\zhh\\Desktop\\����ͼƬ��ͷ\\����Ů\\19.jpg", xin);
	cvNamedWindow("��ð�", CV_WINDOW_NORMAL);
	cvShowImage("��ð�", xin);
	cvWaitKey(0);
	cvDestroyWindow("��ð�");
	cvReleaseImage(&p);
	//cvReleaseImage(&xin);
	return 0;

}