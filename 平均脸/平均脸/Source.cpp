#include "cv.h"  
#include<cv.hpp>
#include<opencv2/highgui.hpp>
#include "highgui.hpp"
#include<cxcore.h>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	 IplImage * img1 = cvLoadImage("C:\\Users\\zhh\\Desktop\\1.jpg");
	 IplImage * img2 = cvLoadImage("C:\\Users\\zhh\\Desktop\\2.jpg");
	 IplImage * img3 = cvLoadImage("C:\\Users\\zhh\\Desktop\\3.jpg");
	 IplImage * img4 = cvLoadImage("C:\\Users\\zhh\\Desktop\\4.jpg");
	 IplImage * img5 = cvLoadImage("C:\\Users\\zhh\\Desktop\\5.jpg");
	 IplImage * img6 = cvLoadImage("C:\\Users\\zhh\\Desktop\\6.jpg");
	 IplImage * img7 = cvLoadImage("C:\\Users\\zhh\\Desktop\\7.jpg");
	 IplImage * img8 = cvLoadImage("C:\\Users\\zhh\\Desktop\\8.jpg");
	 IplImage * img9 = cvLoadImage("C:\\Users\\zhh\\Desktop\\9.jpg");
	 IplImage * img10 = cvLoadImage("C:\\Users\\zhh\\Desktop\\10.jpg");
	 IplImage * img11 = cvLoadImage("C:\\Users\\zhh\\Desktop\\11.jpg");
	// IplImage * img12 = cvLoadImage("C:\\Users\\zhh\\Desktop\\12.jpg");
	 IplImage * img13 = cvLoadImage("C:\\Users\\zhh\\Desktop\\13.jpg");
	 IplImage * img14 = cvLoadImage("C:\\Users\\zhh\\Desktop\\14.jpg");
	 IplImage * img15 = cvLoadImage("C:\\Users\\zhh\\Desktop\\15.jpg");
	 IplImage * img16 = cvLoadImage("C:\\Users\\zhh\\Desktop\\16.jpg"); 
	 IplImage * img17 = cvLoadImage("C:\\Users\\zhh\\Desktop\\17.jpg");
	 IplImage * img18 = cvLoadImage("C:\\Users\\zhh\\Desktop\\18.jpg");
	 IplImage * img19 = cvLoadImage("C:\\Users\\zhh\\Desktop\\19.jpg");
	 IplImage * img20 = cvLoadImage("C:\\Users\\zhh\\Desktop\\20.jpg");
	 IplImage * img21 = cvLoadImage("C:\\Users\\zhh\\Desktop\\21.jpg");
	 IplImage * img22 = cvLoadImage("C:\\Users\\zhh\\Desktop\\22.jpg");
	/* IplImage * img12 = cvLoadImage("C:\\Users\\zhh\\Desktop\\12.jpg");
	 IplImage * img13 = cvLoadImage("C:\\Users\\zhh\\Desktop\\13.jpg");*/
	 IplImage * desc;
	 CvSize sz;
	 cout << "im1:" << img1->width << img1->height << endl;
	 double scale = 0.5;
	 if (img1)
	 {
		 sz.width = img1->width*scale;
		 sz.height = img1->height*scale;
		 desc = cvCreateImage(sz, img1->depth, img1->nChannels);
		 cvResize(img1, desc, CV_INTER_AREA);
		 cvResize(img2, desc, CV_INTER_AREA);
		 cvResize(img3, desc, CV_INTER_AREA);
		 //cvNamedWindow("nihao");
		// cvShowImage("nihao",desc);
		 cvWaitKey(0);
		 cout << "im3:" << img3->width << img3->height << endl;
		 cout << desc->width << desc->height <<endl;

	 }

	 cout << "im1:" << img1->width << img1->height << endl;
	 cout << "im2:" << img2->width << img2->height << endl;
	 cout << "im3:" << img3->width << img3->height << endl;
	 cout << "im1:" << img4->width << img4->height << endl;
	 cout << "im2:" << img5->width << img5->height << endl;
	 cout << "im3:" << img6->width << img6->height << endl;
	 cout << "im1:" << img7->width << img7->height << endl;
	 cout << "im2:" << img8->width << img8->height << endl;
	 cout << "im3:" << img9->width << img9->height << endl;
	 cout << "im3:" << img10->width << img10->height << endl;
	 cout << "im3:" << img11->width << img11->height << endl;

	 IplImage * img_sum = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, 3);
	 IplImage * img_sum_gray = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 3);
	 cvZero(img_sum);
	 //cvAcc(img1, img_sum);
    // cvAcc(img2, img_sum);
	// cvAcc(img3, img_sum);
       cvAcc(img4, img_sum);
	 //cvAcc(img5, img_sum);
	// cvAcc(img6, img_sum);
	 cvAcc(img7, img_sum);
	 cvAcc(img8, img_sum);
	// cvAcc(img9, img_sum); 
	cvAcc(img10, img_sum);
	// cvAcc(img11, img_sum);
	 cout << "im1:" << img1->width << img1->height << endl;
	 cvConvertScale(img_sum, img_sum_gray, 1.0 / 4);
	 cvNamedWindow("img_sum_gray");
	 cvShowImage("img_sum_gray", img_sum_gray);
	 cvWaitKey(0);
	
	 cvSaveImage("img_sum_gray.png", img_sum_gray);
	
	 cvDestroyAllWindows();
	
	 cvReleaseImage(&img1);
	 cvReleaseImage(&img2);
	 cvReleaseImage(&img3);
	 cvReleaseImage(&img_sum);
	 cvReleaseImage(&img_sum_gray);
	
	 return 0;
}
