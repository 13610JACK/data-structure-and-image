#include<opencv2\highgui\highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;
int main()
{
	IplImage *p = cvLoadImage("C:\\Users\\zhh\\Desktop\\剪切图片人头\\中年女\\5.jpg");
	IplImage *xin = cvCreateImage(cvSize(500, 600), 8, 3);
	cvResize(p, xin, 1);
	cout << "jieguo" << xin->height << xin->width << endl;
	cvSaveImage("C:\\Users\\zhh\\Desktop\\剪切图片人头\\中年女\\5.jpg", xin);
	cvNamedWindow("你好啊", CV_WINDOW_NORMAL);
	cvShowImage("你好啊", xin);
	cvWaitKey(0);
	cvDestroyWindow("你好啊");
	cvReleaseImage(&p);
	cvReleaseImage(&xin);
	return 0;

}