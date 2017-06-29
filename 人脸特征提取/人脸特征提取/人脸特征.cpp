
//纹理提取
#include <iostream>
#include <math.h>
#include "cv.h"
#include "highgui.h"
#include<cxcore.h>
int main(int argc, char* argv[])
{
	int tmp[8] = { 0 };
	int sum = 0; int k = 0;
	IplImage* img, *dst;
	img = cvLoadImage("C:\\Users\\zhh\\Desktop\\30.jpg", 0);
	CvScalar s;
	cvNamedWindow("img", NULL);
	cvNamedWindow("dst", NULL);
	cvShowImage("img", img);

	uchar* data = (uchar*)img->imageData;
	int step = img->widthStep;
	dst = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
	dst->widthStep = img->widthStep;
	for (int i = 1; i < img->height - 1; i++)
		for (int j = 1; j < img->width - 1; j++)
		{
			if (data[(i - 1)*step + j - 1] > data[i*step + j]) tmp[0] = 1;
			else tmp[0] = 0;
			if (data[i*step + (j - 1)] > data[i*step + j]) tmp[1] = 1;
			else tmp[1] = 0;
			if (data[(i + 1)*step + (j - 1)] > data[i*step + j]) tmp[2] = 1;
			else tmp[2] = 0;
			if (data[(i + 1)*step + j] > data[i*step + j]) tmp[3] = 1;
			else tmp[3] = 0;
			if (data[(i + 1)*step + (j + 1)] > data[i*step + j]) tmp[4] = 1;
			else tmp[4] = 0;
			if (data[i*step + (j + 1)] > data[i*step + j]) tmp[5] = 1;
			else tmp[5] = 0;
			if (data[(i - 1)*step + (j + 1)] > data[i*step + j]) tmp[6] = 1;
			else tmp[6] = 0;
			if (data[(i - 1)*step + j] > data[i*step + j]) tmp[7] = 1;
			else tmp[7] = 0;
			for (k = 0; k <= 7; k++)
				sum += abs(tmp[k] - tmp[k + 1]);
			sum = sum + abs(tmp[7] - tmp[0]);
			if (sum <= 2)
				s.val[0] = (tmp[0] * 128 + tmp[1] * 64 + tmp[2] * 32 + tmp[3] * 16 + tmp[4] * 8 + tmp[5] * 4 + tmp[6] * 2 + tmp[7]);
			else s.val[0] = 59;
			cvSet2D(dst, i, j, s);
		}

	cvShowImage("dst", dst);
	cvWaitKey(0);

	return 0;
}

//形状边缘提取
int main1(int argc, char** argv)
{
	//声明IplImage指针
	IplImage* pImg = NULL;
	IplImage* pCannyImg = NULL;
	//载入图像，强制转化为Gray
	pImg = cvLoadImage("C:\\Users\\zhh\\Desktop\\5.jpg", 1);
	//为canny边缘图像申请空间
	pCannyImg = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
	//canny边缘检测
	cvCanny(pImg, pCannyImg, 75,125, 3);
	//创建窗口
	cvNamedWindow("src", 1);
	cvNamedWindow("canny", 1);
	//显示图像
	cvShowImage("src", pImg);
	cvShowImage("canny", pCannyImg);
	//等待按键
	cvWaitKey(0);
	//销毁窗口
	cvDestroyWindow("src");
	cvDestroyWindow("canny");
	//释放图像
	cvReleaseImage(&pImg);
	cvReleaseImage(&pCannyImg);
	return 0;

}
