#include<opencv2\highgui\highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;
int main()
{
	IplImage *p = cvLoadImage("C:\\Users\\zhh\\Desktop\\����ͼƬ��ͷ\\����Ů\\5.jpg");
	IplImage *xin = cvCreateImage(cvSize(500, 600), 8, 3);
	cvResize(p, xin, 1);
	cout << "jieguo" << xin->height << xin->width << endl;
	cvSaveImage("C:\\Users\\zhh\\Desktop\\����ͼƬ��ͷ\\����Ů\\5.jpg", xin);
	cvNamedWindow("��ð�", CV_WINDOW_NORMAL);
	cvShowImage("��ð�", xin);
	cvWaitKey(0);
	cvDestroyWindow("��ð�");
	cvReleaseImage(&p);
	cvReleaseImage(&xin);
	return 0;

}