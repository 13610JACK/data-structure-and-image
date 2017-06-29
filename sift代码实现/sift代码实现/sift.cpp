#include "stdafx.h"
#include "highgui.h"
//#include "features2d/features2d.hpp"
#include <iostream>
#include<opencv2\opencv.hpp>
//#include<opencv2\xfeatures2d.hpp>
#include<opencv2\xfeatures2d\nonfree.hpp>
using namespace std;
using namespace cv;
void main(int argc, char* argv[])
{
	Mat input1 = imread("image1.jpg", 1);
	Mat input2 = imread("image2.jpg", 1);
	SiftFeatureDetector  detector; 
	vector<KeyPoint> keypoint1, keypoint2;
	detector.detect(input1, keypoint1);

	Mat output1;
	drawKeypoints(input1, keypoint1, output1);
	imshow("sift_result1.jpg", output1);
	imwrite("sift_result1.jpg", output1);

	Mat output2;
	SiftDescriptorExtractor * extractor;
	Mat descriptor1, descriptor2;
	BruteForceMatcher<L2<float>> matcher;

	vector<DMatch> matches;
	Mat img_matches;
	detector.detect(input2, keypoint2);
	drawKeypoints(input2, keypoint2, output2);

	imshow("sift_result2.jpg", output2);
	imwrite("sift_result2.jpg", output2);

	extractor.compute(input1, keypoint1, descriptor1);
	extractor.compute(input2, keypoint2, descriptor2);

	matcher.match(descriptor1, descriptor2, matches);

	drawMatches(input1, keypoint1, input2, keypoint2, matches, img_matches);
	imshow("matches", img_matches);
	imwrite("matches.jpg", img_matches);

	waitKey();


}
