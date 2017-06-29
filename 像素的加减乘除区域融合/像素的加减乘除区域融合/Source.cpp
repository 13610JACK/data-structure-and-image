//#include <opencv2/opencv.hpp>  
//using namespace std;
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
////图片归一化
//IplImage* EqualizeHistColorImage1111(IplImage *pImage)
//{
//	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);
//
//	// 原图像分成各通道后再均衡化,最后合并即彩色图像的直方图均衡化  
//	const int MAX_CHANNEL = 4;
//	IplImage *pImageChannel[MAX_CHANNEL] = { NULL };
//
//	int i;
//	for (i = 0; i < pImage->nChannels; i++)
//		pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);
//
//	cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);
//
//	for (i = 0; i < pImage->nChannels; i++)
//		cvNormalize(pImageChannel[i], pImageChannel[i], 100, 50, 4, 0);
//
//	cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);
//
//	for (i = 0; i < pImage->nChannels; i++)
//		cvReleaseImage(&pImageChannel[i]);
//
//	return pEquaImage;
//}
//
//
//
////去除高光
//int highlight_remove_Chi(IplImage* src, IplImage* dst)//, double Re)
//{
//	int height = src->height;
//	int width = src->width;
//	int step = src->widthStep;
//	int i = 0, j = 0;
//	unsigned char R, G, B, MaxC;
//	double alpha, beta, alpha_r, alpha_g, alpha_b, beta_r, beta_g, beta_b, temp = 0, realbeta = 0, minalpha = 0;
//	double gama, gama_r, gama_g, gama_b;
//	unsigned char* srcData;
//	unsigned char* dstData;
//	for (i = 0; i<height; i++)
//	{
//		srcData = (unsigned char*)src->imageData + i*step;
//		dstData = (unsigned char*)dst->imageData + i*step;
//		for (j = 0; j<width; j++)
//		{
//			R = srcData[j * 3];
//			G = srcData[j * 3 + 1];
//			B = srcData[j * 3 + 2];
//
//			alpha_r = (double)R / (double)(R + G + B);
//			alpha_g = (double)G / (double)(R + G + B);
//			alpha_b = (double)B / (double)(R + G + B);
//			alpha = max(max(alpha_r, alpha_g), alpha_b);
//			MaxC = max(max(R, G), B);// compute the maximum of the rgb channels
//			minalpha = min(min(alpha_r, alpha_g), alpha_b);
//			beta_r = 1 - (alpha - alpha_r) / (3 * alpha - 1);
//			beta_g = 1 - (alpha - alpha_g) / (3 * alpha - 1);
//			beta_b = 1 - (alpha - alpha_b) / (3 * alpha - 1);
//			beta = max(max(beta_r, beta_g), beta_b);
//			//将beta当做漫反射系数，则有               
//
//			// gama is used to approximiate the beta
//			gama_r = (alpha_r - minalpha) / (1 - 3 * minalpha);
//			gama_g = (alpha_g - minalpha) / (1 - 3 * minalpha);
//			gama_b = (alpha_b - minalpha) / (1 - 3 * minalpha);
//			gama = max(max(gama_r, gama_g), gama_b);
//
//			temp = (gama*(R + G + B) - MaxC) / (3 * gama - 1);
//			//beta=(alpha-minalpha)/(1-3*minalpha)+0.08;
//			//temp=(gama*(R+G+B)-MaxC)/(3*gama-1);
//			dstData[j * 3] = R - (unsigned char)(temp + 0.5);
//			dstData[j * 3 + 1] = G - (unsigned char)(temp + 0.5);
//			dstData[j * 3 + 2] = B - (unsigned char)(temp + 0.5);
//		}
//	}
//	return 1;
//}
////彩色图像的直方图均衡化  
//IplImage* EqualizeHistColorImage(IplImage *pImage)
//{
//	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);
//
//	// 原图像分成各通道后再均衡化,最后合并即彩色图像的直方图均衡化  
//	const int MAX_CHANNEL = 4;
//	IplImage *pImageChannel[MAX_CHANNEL] = { NULL };
//
//	int i;
//	for (i = 0; i < pImage->nChannels; i++)
//		pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);
//
//	cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);
//
//	for (i = 0; i < pImage->nChannels; i++)
//		cvEqualizeHist(pImageChannel[i], pImageChannel[i]);
//
//	cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);
//
//	for (i = 0; i < pImage->nChannels; i++)
//		cvReleaseImage(&pImageChannel[i]);
//
//	return pEquaImage;
//}
//int main(int argc, char** argv)
//{
//	const char *pstrWindowsSrcTitle = "原图";
//	const char *pstrWindowsHisEquaTitle = "直方图均衡化后";
//
//	// 从文件中加载原图  
//	IplImage *pSrcImage = cvLoadImage("C:\\Users\\zhh\\Desktop\\72.jpg");
//	//IplImage *pHisEquaImag = EqualizeHistColorImage(pSrcImage);
//	IplImage *pHisEquaImage = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 3);
//	cvSetImageROI(pSrcImage, cvRect(120,30,360,80));
//	pHisEquaImage = EqualizeHistColorImage(pSrcImage);
//	cvResetImageROI(pSrcImage);
//	//highlight_remove_Chi(pSrcImage, pHisEquaImage);
//	//IplImage *pHisEquaImag = EqualizeHistColorImage(pHisEquaImage);
//	/*IplImage *pHisEquaImag = EqualizeHistColorImage(pSrcImage);
//	IplImage * img_sum = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_32F, 3);
//	cvZero(img_sum);
//	cvAcc(pSrcImage, img_sum);
//	cvAcc(pHisEquaImag, img_sum);
//	IplImage * img_sum_gray = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 3);
//	cvConvertScale( img_sum , img_sum_gray, 1.0 / 2);
//	cvAddWeighted(pSrcImage, 0.5, pHisEquaImag, 0.5, 0, pSrcImage);*/
//	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
//	cvNamedWindow(pstrWindowsHisEquaTitle, CV_WINDOW_AUTOSIZE);
//	cvShowImage(pstrWindowsSrcTitle, pSrcImage);
//	cvShowImage(pstrWindowsHisEquaTitle, pHisEquaImage);
//
//	cvWaitKey(0);
//	cvDestroyWindow(pstrWindowsSrcTitle);
//	cvDestroyWindow(pstrWindowsHisEquaTitle);
//	cvReleaseImage(&pSrcImage);
//	cvReleaseImage(&pHisEquaImage);
//	// cvReleaseImage(&pHisEquaImag);
//	return 0;
//}
////CvScalar 
//纹理提取
//#include <iostream>
//#include <math.h>
////#include "cv.h"
//#include<opencv2/opencv.hpp>
////#include <hig>
//#include<opencv2/highgui/highgui.hpp>
////#include<cxcore.h>
//#include<opencv2/core/core.hpp>
//using namespace std;
//int main1(int argc, char* argv[])
//{
//	int tmp[8] = { 0 };
//	int sum = 0; int k = 0;
//	IplImage* img, *dst;
//	img = cvLoadImage("C:\\Users\\zhh\\Desktop\\30.jpg", 0);
//	CvScalar s;
//	cvNamedWindow("img", NULL);
//	cvNamedWindow("dst", NULL);
//	cvShowImage("img", img);
//
//	uchar* data = (uchar*)img->imageData;
//	int step = img->widthStep;
//	dst = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
//	dst->widthStep = img->widthStep;
//	for (int i = 1; i < img->height - 1; i++)
//		for (int j = 1; j < img->width - 1; j++)
//		{
//			if (data[(i - 1)*step + j - 1] > data[i*step + j]) tmp[0] = 1;
//			else tmp[0] = 0;
//			if (data[i*step + (j - 1)] > data[i*step + j]) tmp[1] = 1;
//			else tmp[1] = 0;
//			if (data[(i + 1)*step + (j - 1)] > data[i*step + j]) tmp[2] = 1;
//			else tmp[2] = 0;
//			if (data[(i + 1)*step + j] > data[i*step + j]) tmp[3] = 1;
//			else tmp[3] = 0;
//			if (data[(i + 1)*step + (j + 1)] > data[i*step + j]) tmp[4] = 1;
//			else tmp[4] = 0;
//			if (data[i*step + (j + 1)] > data[i*step + j]) tmp[5] = 1;
//			else tmp[5] = 0;
//			if (data[(i - 1)*step + (j + 1)] > data[i*step + j]) tmp[6] = 1;
//			else tmp[6] = 0;
//			if (data[(i - 1)*step + j] > data[i*step + j]) tmp[7] = 1;
//			else tmp[7] = 0;
//			for (k = 0; k <= 7; k++)
//				sum += abs(tmp[k] - tmp[k + 1]);
//			sum = sum + abs(tmp[7] - tmp[0]);
//			if (sum <= 2)
//				s.val[0] = (tmp[0] * 128 + tmp[1] * 64 + tmp[2] * 32 + tmp[3] * 16 + tmp[4] * 8 + tmp[5] * 4 + tmp[6] * 2 + tmp[7]);
//			else s.val[0] = 59;
//			cvSet2D(dst, i, j, s);
//		}
//
//	cvShowImage("dst", dst);
//	cvWaitKey(0);
//
//	return 0;
//}
//
////形状边缘提取
//int main(int argc, char** argv)
//{
//	//声明IplImage指针
//	IplImage* pImg = NULL;
//	IplImage* pCannyImg = NULL;
//	//载入图像，强制转化为Gray
//	pImg = cvLoadImage("C:\\Users\\zhh\\Desktop\\72.jpg", 1);
//	//为canny边缘图像申请空间
//	pCannyImg = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
//	//canny边缘检测
//	cvCanny(pImg, pCannyImg, 50, 100, 3);
//	//创建窗口
//	cvSetImageROI(pCannyImg, cvRect(1, 1, 1, 1));
//	CvScalar a = cvAvg(pCannyImg, NULL);
//	cout << a.val[0] << endl;
//	cvResetImageROI(pCannyImg);
//	//	//cvErode(src1, src1, NULL, 1);
//	//	//cvMorphologyEx(src1, src1, src3, p, CV_MOP_OPEN);
//	//	CvScalar a1 = cvAvg(src1, NULL);
//	//	//cout << a1.val[0] << "  " << a1.val[1] << "  " << a1.val[2] << " " << a1.val[3] << endl;
//
//	cvNamedWindow("src", 1);
//	cvNamedWindow("canny", 1);
//	//显示图像
//	cvShowImage("src", pImg);
//	cvShowImage("canny", pCannyImg);
//	//等待按键
//	cvWaitKey(0);
//	//销毁窗口
//	cvDestroyWindow("src");
//	cvDestroyWindow("canny");
//	//释放图像
//	cvReleaseImage(&pImg);
//	cvReleaseImage(&pCannyImg);
//	return 0;
//
//}





//最后结果
//#include<iostream>
//#include<opencv\highgui.h>
//#include<core.hpp>
//#include <opencv/cv.hpp>
//# define _CRT_SECURE_NO_DEPRECATE
//#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<iostream>
#include<opencv/highgui.h>
#include<opencv2/core/core.hpp>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
typedef struct Coordinate {
	int x;
	int y;
};
typedef struct Heigth_Width {
	int lengthx;
	int lengthy;
};
void  winkleImage(IplImage ** s1,IplImage **s2,IplImage **s3, Coordinate cd1, Coordinate cd2, Heigth_Width length,double alpha,double beta) 
{   
	int x1, y1, x2, y2;
	double lengthx, lengthy;
	x1 = cd1.x;
	y1 = cd1.y;
	x2 = cd2.x;
	y2 = cd2.y;
	lengthx = length.lengthx;
	lengthy = length.lengthy;
	IplImage *src1, *src2,*src3;
	src1 = *s1;
	src2 = *s2;
	src3 = *s3;
	cvSetImageROI(src1, cvRect(x1, y1, lengthx, lengthy));
	//cvErode(src1, src1, NULL, 1);
	//cvMorphologyEx(src1, src1, src3, p, CV_MOP_OPEN);
	CvScalar a1 = cvAvg(src1, NULL);
	//cout << a1.val[0] << "  " << a1.val[1] << "  " << a1.val[2] << " " << a1.val[3] << endl;
	cvResetImageROI(src1);
	cvSetImageROI(src2, cvRect(x2, y2, lengthx, lengthy));
	//double a21, a22, a23;
	CvScalar a2 = cvAvg(src2, NULL);
	/*for (int m = 0; m < lengthy; m++)
	{
		for (int n = 0; n < lengthx; n++)
		{
			a21 = (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3];
			if ((double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3]<0)
			{
				a21= 256 + (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3];
			}
			a22 = (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 1];
			if ((double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3+1]<0)
			{
				 a22 = 256 + (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3+1];
			}
			a23 = (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 2];
			if ((double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3+2]<0)
			{
				a23 = 256 + (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3+2];
			}
			if (
				a22>a2.val[1]
				||a21>a2.val[0]
				||a23>a2.val[2]
				)
			{
				(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3] = 255;
				(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 1]=255;
				(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 2]= 255;
			}
		}
	}*/
	//cout << a2.val[0] << "  " << a2.val[1] << "  " << a2.val[2] << " " << a2.val[3] << endl;
	cvResetImageROI(src2);
	/*cvNamedWindow("合成图片1", CV_WINDOW_NORMAL);
	cvShowImage("合成图片1", src2);
	cvWaitKey(0);*/
	double bgr[3];
	int t[3];
	for (int m = 0; m < 3; m++) {
		t[m] = a1.val[m] - a2.val[m];
		bgr[m] = beta * t[m];
	}
	uchar b1, g1, r1;
	uchar b2, g2, r2;
	for (int i = 0; i < lengthy; i++)
	{
		for (int k = 0; k < lengthx; k++)
		{
			b1 = (src1->imageData + (y1 + i)*src2->widthStep)[(k + x1) * 3];
			g1 = (src1->imageData + (y1 + i)*src2->widthStep)[(k + x1) * 3 + 1];
			r1 = (src1->imageData + (y1 + i)*src2->widthStep)[(k + x1) * 3 + 2];
			b2 = (src2->imageData + (y2 + i)*src2->widthStep)[(k + x2) * 3];
			g2 = (src2->imageData + (y2 + i)*src2->widthStep)[(k + x2) * 3 + 1];
			r2 = (src2->imageData + (y2 + i)*src2->widthStep)[(k + x2) * 3 + 2];
			/*if (alpha * b1 + beta *b2 + bgr[0] < 200)
			{
				(src1->imageData + (y1 + i)*src1->widthStep)[(k + x1) * 3] = alpha * b1 + beta *b2 + bgr[0];
			}
			if (alpha * g1 + beta *g2 + bgr[1]<250)
			{
				(src1->imageData + (y1 + i)*src1->widthStep)[(k + x1) * 3 + 1] = alpha * g1 + beta *g2 + bgr[1];
			}
			if (alpha * r1 + beta *r2 + bgr[2] < 250)
			{
				(src1->imageData + (y1 + i)*src1->widthStep)[(k + x1) * 3 + 2] = alpha * r1 + beta *r2 + bgr[2];
			}*/
            if ((src3->imageData + (y2 + i)*src3->widthStep)[(k+ x2) * 3] ==0)
			{
				(src1->imageData + (y1 + i)*src1->widthStep)[(k + x1) * 3] = b2; //+ bgr[0];
				(src1->imageData + (y1 + i)*src1->widthStep)[(k + x1) * 3 + 1] = g2;// + bgr[1];
				(src1->imageData + (y1 + i)*src1->widthStep)[(k + x1) * 3 + 2] =r2; //+ bgr[2];

			}
																																													//if (t[0] <0)
																																													//{
																																													//	t[0] = -t[0];
																																													//}
																																													//if (t[1] <0)
																																													//{
																																													//	t[1] = -t[1];
																																													//}
																																													//if (t[2] <0)
																																													//{
																																													//	t[2] = -t[2];
																																													//}
																																													//		if (
																																													//			beta * b2 + bgr[0] + 30 < alpha * b1 + beta *b2 + bgr[0]
																																													//			&& alpha * b1 + beta *b2 + bgr[0] < (a1.val[0] + t[0]) 
																																													//			&& alpha * g1 + beta *g2 + bgr[1] < (a1.val[1] + t[1]) 
																																													//			&& alpha * r1 + beta *r2 + bgr[2] < (a1.val[2] + t[2])
																																													//			&& alpha * b1 + beta *b2 + bgr[0]<255
																																													//			&& alpha * g1 + beta *g2 + bgr[1]<255
																																													//			&& alpha * r1 + beta *r2 + bgr[2]<255

				
			}			
	}
	return ;
}
void  winkleImage1(IplImage **s2,  Coordinate cd2, Heigth_Width length)
{
	int  x2, y2;
	double lengthx, lengthy;
	x2 = cd2.x;
	y2 = cd2.y;
	lengthx = length.lengthx;
	lengthy = length.lengthy;
	IplImage  *src2;
	src2 = *s2;
	cvSetImageROI(src2, cvRect(x2, y2, lengthx, lengthy));
	double a21, a22, a23;
	CvScalar a2 = cvAvg(src2, NULL);
	for (int m = 0; m < lengthy; m++)
	{
		for (int n = 0; n < lengthx; n++)
		{
			a21 = (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3];
			if ((double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3] < 0)
			{
				a21 = 256 + (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3];
			}
			a22 = (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 1];
			if ((double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 1] < 0)
			{
				a22 = 256 + (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 1];
			}
			a23 = (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 2];
			if ((double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 2] < 0)
			{
				a23 = 256 + (double)(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 2];
			}
			if (
				a22 > a2.val[1]
				|| a21 > a2.val[0]
				|| a23 > a2.val[2]
				)
			{
				(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3] = 255;
				(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 1] = 255;
				(src2->imageData + (y2 + m)*src2->widthStep)[(n + x2) * 3 + 2] = 255;
			}
		}
	}
	//cout << a2.val[0] << "  " << a2.val[1] << "  " << a2.val[2] << " " << a2.val[3] << endl;
	//cvDilate(src2, src2, NULL, 1);
	cvResetImageROI(src2);
	/*cvNamedWindow("合成图片1", CV_WINDOW_NORMAL);
	cvShowImage("合成图片1", src2);
	cvWaitKey(0);*/
}
int main(int argc, char** argv) {
	argc = 2;
	IplImage* src1, *src2;
	//IplImage *p1,*p2;
	src1 = cvLoadImage("C:\\Users\\zhh\\Desktop\\30.jpg");
    src2 = cvLoadImage("C:\\Users\\zhh\\Desktop\\72.jpg");
	IplImage *src3 = cvCreateImage(cvSize(600, 600), 8, 3);
	IplImage* pCannyImg = NULL, *p1 = NULL, *p2 = NULL, *p3 = NULL;
	//载入图像，强制转化为Gray
	//为canny边缘图像申请空间
	pCannyImg = cvCreateImage(cvGetSize(src1), IPL_DEPTH_8U, 1);

	//canny边缘检测
	cvCanny(src2, pCannyImg, 50, 100, 3);
	/*p1 = pCannyImg;
	p2 = pCannyImg;
	p3 = pCannyImg;
	p4 = pCannyImg;*/
	/*cvSplit(src3, p1, p2, p3,p4);*/
	cvResize(pCannyImg, src3);
	cvSaveImage("pCannyImg.jpg", src3);
	cvNamedWindow("边缘提取图片");
	cvShowImage("C:\\Users\\zhh\\Desktop\\边缘提取图片.img", pCannyImg);
	//src3 = cvLoadImage("C:\\Users\\zhh\\Desktop\\1.jpg");
	//IplConvKernel *p = cvCreateStructuringElementEx(3, 3, 2, 2, CV_SHAPE_RECT, NULL);
	if (argc == 2 )
	{
	  double al = 0.718;
	  double be = 0.282;
//提取纹理失败
	  int j =1;
	 /* for (int m = 0; m < 36; m++)
	  {
		  for (int n = 0; n <1; n++)
		  {
			  Coordinate src1_cde = { 100, 45 }, src2_cde = { 120 + m * 10, 30 + n * 80 };
			  Heigth_Width sr12_Hwe = { 10,80 };
			  winkleImage1(&src2, src2_cde, sr12_Hwe);
		  }
	  }
	  cvNamedWindow("合成图片1", CV_WINDOW_NORMAL);
	  cvShowImage("合成图片1", src2);
	  cvWaitKey(0);*/
	  for (int i = 0; i < j; i++)
	  {

		/*  for (int m = 0; m < 380;m++)
		  {
			  Coordinate src1_cde = { 100, 45 }, src2_cde = { 120+m*1, 30 };
			  Heigth_Width sr12_Hwe = { 1,90 };
			  winkleImage1(&src2, src2_cde, sr12_Hwe);
		  }*/
		 /* cvNamedWindow("合成图片1", CV_WINDOW_NORMAL);
		  cvShowImage("合成图片1", src2);
		  cvWaitKey(0);
		  system("pause");
		  return 0;*/
		  int k, l;
		  k = 16;
		  l = 4;
		  for (int m = 0; m < 24; m++)
		 {
			  for (int n = 0; n <22; n++)
		    {
			  Coordinate src1_cde = { 120+m * k, 22 + n * l }, src2_cde = { 120 + m * k, 20 + n * l };
			  Heigth_Width sr12_Hwe = { k,l };
			  winkleImage(&src1, &src2, &pCannyImg,src1_cde, src2_cde, sr12_Hwe, al, be);
			}
		  }
		  cvSetImageROI(src1, cvRect(120,96,388,20));
		  //cvDilate(src1, src1, NULL, 1);
		  cvResetImageROI(src1);
		  //cvDilate(src1, src1, NULL, 1);
		  //cvDilate(src1, src1, NULL, 1); 
		  //cvDilate(src1, src1, NULL, 1);
		  //额头
		  /*Coordinate src1_cde = { 120, 40 }, src2_cde = { 120, 30 };
		  Heigth_Width sr12_Hwe = { 380,80};
		  winkleImage(&src1, &src2, src1_cde, src2_cde, sr12_Hwe, al, be);*/
		  /*system("pause");
		  return 0;*/
		  ////左眼角
		  //Coordinate src1_cdyl1 = { 20,185 }, src2_cdyl1 = { 70,180 };
		  //Heigth_Width sr12_Hwly1 = { 60,160 };
		  //winkleImage(&src1, &src2, src1_cdyl1, src2_cdyl1, sr12_Hwly1, al, be);
		  //Coordinate src1_cdyl2 = { 80,260 }, src2_cdyl2 = { 130,255 };
		  //Heigth_Width sr12_Hwly2 = { 150,80 };
		  //winkleImage(&src1, &src2, src1_cdyl2, src2_cdyl2, sr12_Hwly2, al, be);
		  ////右眼角
		  //Coordinate src1_cdyr1 = { 400,265 }, src2_cdyr1 = { 350,245 };
		  //Heigth_Width sr12_Hwry1 = { 130,75 };
		  //winkleImage(&src1, &src2, src1_cdyr1, src2_cdyr1, sr12_Hwry1, al, be);
		  //Coordinate src1_cdyr2 = { 530,200 }, src2_cdyr2 = { 480,180 };
		  //Heigth_Width sr12_Hwry2 = { 60,180 };
		  //winkleImage(&src1, &src2, src1_cdyr2, src2_cdyr2, sr12_Hwry2, al, be);
		  //cvErode(src1, src1, NULL, 1);
		  //cvErode(src1, src1, NULL, 1);
		  ////左嘴角
		  //Coordinate src1_cdzl1 = { 105,470 }, src2_cdzl1 = { 150,430 };
		  //Heigth_Width sr12_Hwzl1 = { 60,120 };
		  //winkleImage(&src1, &src2, src1_cdzl1, src2_cdzl1, sr12_Hwzl1, al, be);
		  ////右嘴角
		  //Coordinate src1_cdzr2 = { 450,470 }, src2_cdzr2 = { 410,430 };
		  //Heigth_Width sr12_Hwzr2 = { 70,120 };
		  //winkleImage(&src1, &src2, src1_cdzr2, src2_cdzr2, sr12_Hwzr2, al, be);
		 // cvMorphologyEx(src1, src1, src3,p,CV_MOP_OPEN);
		  
	  }
	  //cvMorphologyEx(src1, src1, src3, p, CV_MOP_OPEN);
	  //cvMorphologyEx(src1, src1, src3, p, CV_MOP_OPEN);
	  //cvDilate(src1, src1, NULL, 1);
	  //cvDilate(src1, src1, NULL, 1);
	 //cvErode(src1, src1, NULL, 1);
		//cvSaveImage("hecheng.jpg",src1);
		//cvSmooth(src1, src1, CV_GAUSSIAN, 11, 11);
	  cvNamedWindow("合成图片");// CV_WINDOW_NORMAL);
		cvShowImage("合成图片",src1);
		cvWaitKey(0);
	}
	//system("pause");
	cvDestroyWindow("合成图片");
	//cvReleaseStructuringElement(&p);
	cvReleaseImage(&src1);
	//cvReleaseImage(&p1); 
	//cvReleaseImage(&p2);
	cvReleaseImage(&src2);
	cvReleaseImage(&pCannyImg);
	cvReleaseImage(&src3);
	return 0;
}




//IplImage* EqualizeHistColorImage(IplImage *pImage)
//{
//	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);
//	// 原图像分成各通道后再均衡化,最后合并即彩色图像的直方图均衡化  
//	const int MAX_CHANNEL = 4;
//	IplImage *pImageChannel[MAX_CHANNEL] = { NULL };
//
//	int i;
//	for (i = 0; i < pImage->nChannels; i++)
//		pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);
//
//	cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);
//
//	for (i = 0; i < pImage->nChannels; i++)
//		cvEqualizeHist(pImageChannel[i], pImageChannel[i]);
//
//	cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);
//
//	for (i = 0; i < pImage->nChannels; i++)
//		cvReleaseImage(&pImageChannel[i]);
//
//	return pEquaImage;
//}


// 切图片
//IplImage* cutImage(IplImage* src, CvRect rect) {
//	cvSetImageROI(src, rect);
//	IplImage* dst = cvCreateImage(cvSize(rect.width, rect.height),
//		src->depth,
//		src->nChannels);
//	cvCopy(src, dst, 0);
//	cvResetImageROI(src);
//	return dst;
//}

/*if (b1 < 0) { b1 = b1 + 256; }
if (g1 < 0) { g1 = g1 + 256; }
if (r1 < 0) { r1 = r1 + 256; }
if (b2 < 0) { b2 = b2 + 256; }
if (g2 < 0) { b2 = b1 + 256; }
if (r2 < 0) { r2 = r2 + 256; }*/
//cvSetImageROI(src2, CvRect(k+x2, y2+i, 1, 1));
//CvScalar a = cvAvg(src1, NULL);
//cout << a.val[0] << "  "<<a.val[1] <<"  "<< a.val[2] <<" "<<a.val[3]<< endl;
// if (a.val[0] < 140&&a.val[1]< 170 &&a.val[2]< 170)
// {
/* cvSetImageROI(src1, CvRect(k + x1, y1 + i, 1, 1));
cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
cvResetImageROI(src1);*/
//p1 = EqualizeHistColorImage(src2);
//src1 = EqualizeHistColorImage(p1);
/*cvSetImageROI(src1, cvRect(60, 190, 40, 180));
cvSetImageROI(src2, cvRect(65, 175, 40, 180));
CvScalar a = cvAvg(src1, NULL);
cout << a.val[0] << "  " << a.val[1] << "  " << a.val[2] << " " << a.val[3] << endl;
cvAddWeighted(src1, alpha, src2, beta, -5, src1);
cvResetImageROI(src2);
cvResetImageROI(src1);
cvSetImageROI(src1, cvRect(100, 245, 80, 120));
cvSetImageROI(src2, cvRect(105, 230, 80, 120));
CvScalar b = cvAvg(src1, NULL);
cout << b.val[0] << "  " << b.val[1] << "  " << b.val[2] << " " << b.val[3] << endl;
cvAddWeighted(src1, alpha, src2, beta,35, src1);
cvResetImageROI(src2);
cvResetImageROI(src1);
cvSetImageROI(src1, cvRect(60, 190, 40, 180));
CvScalar a1 = cvAvg(src1, NULL);
cout << a1.val[0] << "  " << a1.val[1] << "  " << a1.val[2] << " " << a1.val[3] << endl;
cvResetImageROI(src1);
cvSetImageROI(src1, cvRect(100, 245, 80, 120));
CvScalar b1 = cvAvg(src1, NULL);
cout << b1.val[0] << "  " << b1.val[1] << "  " << b1.val[2] << " " << b1.val[3] << endl;
cvResetImageROI(src1);*/
//p1 = EqualizeHistColorImage(src1)


//搞事平滑
/*cvSetImageROI(p1, cvRect(94, 196, 24, 200));
cvSmooth(p1, p1, CV_BILATERAL, 5, 5);
cvResetImageROI(p1);*/
//cvResetImageROI(src1);
//cvSetImageROI(src2, CvRect(192,240, 1, 1));
//cvResetImageROI(src2);
//CvScalar a = cvAvg(src2, NULL);
//cout << a.val[0] << "  "<<a.val[1] <<"  "<< a.val[2] <<" "<<a.val[3]<< endl;
//cvResetImageROI(src2);
/*cvResetImageROI(src1);
cvResetImageROI(src2);
cvSetImageROI(src1, cvRect(413,218, 50, 80));
cvSetImageROI(src2, cvRect(410,203, 50, 80));
cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
cvResetImageROI(src1);
cvResetImageROI(src2);
cvSetImageROI(src1, cvRect(308, 243, 105, 47));
cvSetImageROI(src2, cvRect(305, 228, 105, 47));
cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
cvResetImageROI(src1);
cvResetImageROI(src2);*/
/*cvSetImageROI(src1, cvRect(94, 196, 12, 200));
cvSmooth(src1, src1, CV_GAUSSIAN, 11, 1);
cvResetImageROI(src1);*/
//IplConvKernel * b = cvCreateStructuringElementEx(4, 4, 2, 2, CV_SHAPE_ELLIPSE);
//cvDilate(src2, src2,NULL,1);
//cvResetImageROI(src1);
/*int y = 110;
for (int i = 139; i <400; i++)
{
if (i % 2)
{
(src2->imageData + y*src2->widthStep)[i * 3] = 46;
(src2->imageData + y*src2->widthStep)[i * 3 + 1] = 86;
(src2->imageData + y*src2->widthStep)[i * 3 + 2] = 145;
}
else {
(src2->imageData + y*src2->widthStep)[i * 3] = 111;
(src2->imageData + y*src2->widthStep)[i * 3 + 1] = 140;
(src2->imageData + y*src2->widthStep)[i * 3 + 2] = 184;
}
}*/
//cvReleaseStructuringElement(&b);
/*cvSetImageROI(p1, cvRect(94, 241, 100, 12));
cvSmooth(p1, p2, CV_GAUSSIAN, 1, 11);
cvResetImageROI(p2);*/
//pHisEquaImage = EqualizeHistColorImage(src1);



//#include "opencv2/core/core.hpp"
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
   //IplImage* cutImage(IplImage* src, CvRect rect) {
	//	cvSetImageROI(src, rect);
	//	IplImage* dst = cvCreateImage(cvSize(rect.width, rect.height),
	//		src->depth,
	//		src->nChannels);
	//	cvCopy(src, dst, 0);
	//	cvResetImageROI(src);
	//	return dst;
	//}
	//string face_cascade_name = "H:\\opencv3.1.0\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml";
	//CascadeClassifier face_cascade;
	//string eye_cascade_name = "H:\\opencv3.1.0\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_eye.xml";
	//CascadeClassifier eye_cascade;
	//string window_name = "人脸识别";
	//IplImage* detectAndDisplay1(Mat frame) {
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
	//	IplImage* temp = cutImage(&(IplImage(frame)), cvRect(faces.begin()->x, faces.begin()->y, 500, 500));
	//	return temp;
	//};
	//IplImage* detectAndDisplay(Mat frame) {
	//	std::vector<Rect> faces;
	//	Mat frame_gray;
	//	string face_cascade_name = "H:\\opencv3.1.0\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml";
	//	CascadeClassifier face_cascade;
	//	if (!(face_cascade).load(face_cascade_name)) {
	//		printf("[error] 无法加载级联分类器文件！\n");
	//		return NULL;
	//	}
	//	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	//	equalizeHist(frame_gray, frame_gray);
	//
	//	(face_cascade).detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	//
	//	for (int i = 0; i < faces.size(); i++) {
	//		//Mat smallImgROI;
	//		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
	//		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	//	 
	//		//smallImgROI =frame_gray(*faces.begin());
	////人眼部分检测
	//		//free( &face_cascade);
	//		string eye_cascade_name = "H:\\opencv3.1.0\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_eye.xml";
	//		CascadeClassifier eye_cascade;
	//		if(!eye_cascade.load(eye_cascade_name)) {
	//			printf("[error] 无法加载级联分类器文件！\n");
	//			return NULL;
	//		}
	//	    std:vector<Rect> eyes;
	//		eye_cascade.detectMultiScale(frame, eyes, 1.1, 10, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	//		for (int j = 0; j < eyes.size(); j++) {
	//			Point cente(eyes[j].x + eyes[j].width*0.5, eyes[j].y + eyes[j].height*0.5);
	//			ellipse(frame, cente, Size(eyes[j].width*0.1, eyes[j].height*0.2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	//			cout << "眼睛在图片中的位置x:" << eyes[j].x << eyes[j].width<<"位置y:" << eyes[j].y <<eyes[j].height<< endl;
	//		}
	//	namedWindow("眼睛", WINDOW_NORMAL);
	//	imshow("眼睛", frame);
	//	waitKey(0);
	//
	//	//剪切出图片
	//	//IplImage* temp = cutImage(&(IplImage(frame)), cvRect(faces.begin()->x, faces.begin()->y, 400, 400));
	//	//namedWindow("谭景凤", WINDOW_NORMAL);
	//	//cvShowImage("谭景凤", temp);												//CvMat *faceImg =c();
	//	//cvNamedWindow((const char *)&window_name, WINDOW_NORMAL);
	//	//namedWindow("人脸检测", WINDOW_NORMAL)								imshow("人脸检测", frame);*/
	//	//Rect a = cvRect(faces.begin()->x, faces.begin()->y, 750, 750);
	//	//return temp;
	//	return NULL;
	//};
	//CV_IS_SUBDIV2D * a;
	//cv::(Subdiv2D.point)
