#include <opencv2/opencv.hpp>  
using namespace std;
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//图片归一化
IplImage* EqualizeHistColorImage1111(IplImage *pImage)
{
	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);

	// 原图像分成各通道后再均衡化,最后合并即彩色图像的直方图均衡化  
	const int MAX_CHANNEL = 4;
	IplImage *pImageChannel[MAX_CHANNEL] = { NULL };

	int i;
	for (i = 0; i < pImage->nChannels; i++)
		pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);

	cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);

	for (i = 0; i < pImage->nChannels; i++)
		cvNormalize(pImageChannel[i], pImageChannel[i],100,50,4,0);

	cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);

	for (i = 0; i < pImage->nChannels; i++)
		cvReleaseImage(&pImageChannel[i]);

	return pEquaImage;
}



//去除高光
int highlight_remove_Chi(IplImage* src, IplImage* dst)//, double Re)
{
	int height = src->height;
	int width = src->width;
	int step = src->widthStep;
	int i = 0, j = 0;
	unsigned char R, G, B, MaxC;
	double alpha, beta, alpha_r, alpha_g, alpha_b, beta_r, beta_g, beta_b, temp = 0, realbeta = 0, minalpha = 0;
	double gama, gama_r, gama_g, gama_b;
	unsigned char* srcData;
	unsigned char* dstData;
	for (i = 0; i<height; i++)
	{
		srcData = (unsigned char*)src->imageData + i*step;
		dstData = (unsigned char*)dst->imageData + i*step;
		for (j = 0; j<width; j++)
		{
			R = srcData[j * 3];
			G = srcData[j * 3 + 1];
			B = srcData[j * 3 + 2];

			alpha_r = (double)R / (double)(R + G + B);
			alpha_g = (double)G / (double)(R + G + B);
			alpha_b = (double)B / (double)(R + G + B);
			alpha = max(max(alpha_r, alpha_g), alpha_b);
			MaxC = max(max(R, G), B);// compute the maximum of the rgb channels
			minalpha = min(min(alpha_r, alpha_g), alpha_b);               
			beta_r = 1 - (alpha - alpha_r) / (3 * alpha - 1);
			beta_g = 1 - (alpha - alpha_g) / (3 * alpha - 1);
			beta_b = 1 - (alpha - alpha_b) / (3 * alpha - 1);
			beta = max(max(beta_r, beta_g), beta_b);
			//将beta当做漫反射系数，则有               
												
			// gama is used to approximiate the beta
			gama_r = (alpha_r - minalpha) / (1 - 3 * minalpha);
			gama_g = (alpha_g - minalpha) / (1 - 3 * minalpha);
			gama_b = (alpha_b - minalpha) / (1 - 3 * minalpha);
			gama = max(max(gama_r, gama_g), gama_b);

			temp = (gama*(R + G + B) - MaxC) / (3 * gama - 1);
			//beta=(alpha-minalpha)/(1-3*minalpha)+0.08;
			//temp=(gama*(R+G+B)-MaxC)/(3*gama-1);
			dstData[j * 3] = R - (unsigned char)(temp + 0.5);
			dstData[j * 3 + 1] = G - (unsigned char)(temp + 0.5);
			dstData[j * 3 + 2] = B - (unsigned char)(temp + 0.5);
		}
	}
	return 1;
}
//彩色图像的直方图均衡化  
IplImage* EqualizeHistColorImage(IplImage *pImage)
{
	   IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);
	
	    // 原图像分成各通道后再均衡化,最后合并即彩色图像的直方图均衡化  
	    const int MAX_CHANNEL = 4;
	   IplImage *pImageChannel[MAX_CHANNEL] = { NULL };

	    int i;
       for (i = 0; i < pImage->nChannels; i++)
	        pImageChannel[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);
	
		   cvSplit(pImage, pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3]);

	   for (i = 0; i < pImage->nChannels; i++)
	        cvEqualizeHist(pImageChannel[i], pImageChannel[i]);

		    cvMerge(pImageChannel[0], pImageChannel[1], pImageChannel[2], pImageChannel[3], pEquaImage);
	
	   for (i = 0; i < pImage->nChannels; i++)
		        cvReleaseImage(&pImageChannel[i]);
	
		    return pEquaImage;
	}
int main(int argc, char** argv)
{
	    const char *pstrWindowsSrcTitle = "原图";
	    const char *pstrWindowsHisEquaTitle = "直方图均衡化后";
	
	    // 从文件中加载原图  
	    IplImage *pSrcImage = cvLoadImage("C:\\Users\\zhh\\Desktop\\30.jpg");
	    //IplImage *pHisEquaImag = EqualizeHistColorImage(pSrcImage);
		IplImage *pHisEquaImage= cvCreateImage(cvGetSize(pSrcImage),pSrcImage->depth,3);
		//IplImage *pHisEquaImage = EqualizeHistColorImage(pHisEquaImag);
	    highlight_remove_Chi(pSrcImage, pHisEquaImage);
		//IplImage *pHisEquaImag = EqualizeHistColorImage(pHisEquaImage);
		/*IplImage *pHisEquaImag = EqualizeHistColorImage(pSrcImage);
		IplImage * img_sum = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_32F, 3);
		cvZero(img_sum);
		cvAcc(pSrcImage, img_sum);
		cvAcc(pHisEquaImag, img_sum);
		IplImage * img_sum_gray = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 3);
		cvConvertScale( img_sum , img_sum_gray, 1.0 / 2);
		cvAddWeighted(pSrcImage, 0.5, pHisEquaImag, 0.5, 0, pSrcImage);*/
	    cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	    cvNamedWindow(pstrWindowsHisEquaTitle, CV_WINDOW_AUTOSIZE);
	    cvShowImage(pstrWindowsSrcTitle, pSrcImage);
	    cvShowImage(pstrWindowsHisEquaTitle, pHisEquaImage);
	
	    cvWaitKey(0);
		cvDestroyWindow(pstrWindowsSrcTitle);
        cvDestroyWindow(pstrWindowsHisEquaTitle);
	    cvReleaseImage(&pSrcImage);
	    cvReleaseImage(&pHisEquaImage);
	   // cvReleaseImage(&pHisEquaImag);
        return 0;
	}
//CvScalar 

