#include <iostream>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv/cv.hpp>

using namespace std;
using namespace cv;

float Coordinates[50] = { 2.5,0.5,2.2,1.9,3.1,2.3,2.0,1.0,1.5,1.1,
2.4,0.7,2.9,2.2,3.0,2.7,1.6,1.1,1.6,0.9,
2.1,0.4,2.7,2.2,3.4,2.5,1.3,1.2,1.5,0.8,
2.0,0.2,2.4,2.3,3.1,2.3,1.4,1.9,1.1,1.8,
1.9,0.3,2.8,2.2,1.1,2.7,4.4,1.5,1.8,1.8
};
CvMat p= imread("C:\\Users\\zhh\\Desktop\\张欢欢\\jingfeng\\老谭园博园\\1.JPG");
void PrintMatrix(CvMat *Matrix, int Rows, int Cols);
#include <cv.h>  
#include <highgui.h>
int main1()
{
	int *a;
	int b = 1;
	a = &b;
	CvMat *Vector1;
	CvMat *AvgVector;
	CvMat *EigenValue_Row;
	CvMat *EigenVector;
	//double c = CV_MAT_ELEM(Coordinates, 1, 1, double);
	Vector1 = cvCreateMat(p.height,p.width, CV_32FC1);
	cvSetData(Vector1, &p, Vector1->step);  //给vector1赋值（样本矩阵）
	AvgVector = cvCreateMat(1, p.width, CV_32FC1);  //这个用处还不知道
	EigenValue_Row = cvCreateMat(1, p.height, CV_32FC1);  //每个数表示一个特征值，5是选取的样本数和维度中较小的数
	EigenVector = cvCreateMat(p.height, p.width, CV_32FC1);  //每一行表示一个特征向量，5是选取的样本数和维度中较小的数

												 //PCA的实现函数
	cvCalcPCA(Vector1, AvgVector, EigenValue_Row, EigenVector, CV_PCA_DATA_AS_ROW);
	cvNamedWindow("特征向量图", CV_WINDOW_NORMAL);
	cvShowImage("特征向量图", EigenVector);
	//*((float*)cvPtr2D(EigenVector, 4, 3)+1) = 3;
	//CvMat *Vector2 = cvCreateMat(5, 5, CV_32FC1);
	////cvProjectPCA(Vector1,AvgVector,EigenVector,Vector2);  //选择前面的特征向量（主成分）
	////cout << cvGetDims(Vector2, a) << endl;
	//printf("原始样本矩阵:\n");
	//PrintMatrix(Vector1, Vector1->rows, Vector1->cols);
	//printf("----------------------\n");
	//printf("----------------------\n");
	//printf("特征值:\n");
	//PrintMatrix(EigenValue_Row, EigenValue_Row->rows, EigenValue_Row->cols);
	//printf("----------------------\n");
	//printf("特征向量:\n");
	//PrintMatrix(EigenVector, EigenVector->rows, EigenVector->cols);
	system("pause");
	return 0;
}
void PrintMatrix(CvMat *Matrix, int Rows, int Cols)
{
	for (int i = 0; i<Rows; i++)
	{
		for (int j = 0; j<Cols; j++)
		{
			printf("%.4f ", cvGet2D(Matrix, i, j).val[0]);
		}
		printf("\n");
	}
}
// ch3_ex3_12 image_name x y width height add#   
int main(int argc, char ** argv) {
	IplImage * src;
	IplImage * src2;
	argc = 10;
	cvNamedWindow("Example3_12_pre", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example3_12_post", CV_WINDOW_AUTOSIZE);
	if (argc == 10 && ((src = cvLoadImage("C:\\Users\\zhh\\Desktop\\张欢欢\\jingfeng\\老谭园博园\\1.JPG", 1)) != 0))
	{
		src2 = cvLoadImage("C:\\Users\\zhh\\Desktop\\张欢欢\\jingfeng\\老谭园博园\\1.JPG");
		IplImage * interestimg = cvCreateImageHeader(
			cvSize(250, 300),
			src->depth,
			src->nChannels
		);
		IplImage * interestimg2 = cvCreateImageHeader(
			cvSize(250, 300), src->depth, src->nChannels
		);
		interestimg2->origin = src2->origin;
		interestimg2->widthStep = src2->widthStep;
		interestimg2->imageData = src2->imageData + 12 * src2->widthStep + 12 * src2->nChannels;
		interestimg->origin = src->origin;
		interestimg->widthStep = src->widthStep;
		interestimg->imageData = src->imageData + 120 * src->widthStep + 120 * src->nChannels;
		int add = 50;
		cvShowImage("Example3_12_pre", src);
		cvAddS(interestimg, cvScalar(add), interestimg);
		cvResetImageROI(src);
		cvShowImage("Example3_12_post", src);
		cvWaitKey();
	}
	cvReleaseImage(&src);
	cvDestroyWindow("Example3_12_pre");
	cvDestroyWindow("Example3_12_post");
	return 0;
}
int main2(int argc, char** argv)
{
	argc = 7;
	IplImage* src;
	cvNamedWindow("Example3_12_pre", CV_WINDOW_NORMAL);
	cvNamedWindow("Example3_12_post", CV_WINDOW_NORMAL);
	if (argc == 7 && ((src = cvLoadImage("C:\\Users\\zhh\\Desktop\\张欢欢\\jingfeng\\老谭园博园\\1.JPG", -1)) != 0))
	{
		int x = atoi("200");
		int y = atoi("200");
		int width = atoi("1100");
		int height = atoi("1100");
		int add = atoi("-50");
		cvShowImage("Example3_12_pre", src);
		cvSetImageROI(src, cvRect(x, y, width, height));
		cvAddS(src, cvScalar(add), src);
		cvResetImageROI(src);
		cvShowImage("Example3_12_post", src);
		cvWaitKey();
	}
	cvReleaseImage(&src);
	cvDestroyWindow("Example3_12_pre");
	cvDestroyWindow("Example3_12_post");
	return 0;
}

