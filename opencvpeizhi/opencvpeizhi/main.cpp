#include<opencv2\opencv.hpp>
using namespace cv;
int main()
{
	Mat picture = imread("C:\\Users\\zhh\\Desktop\\�Ż���\\2016.9.24\\����.jpg");//ͼƬ������ӵ�����Ŀ¼��
										  //Ҳ���Ǻ�test.cpp�ļ�����һ���ļ����£�����
	imshow("���Գ���", picture);
	waitKey(20150901);
}