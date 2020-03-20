#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	
	///////////////////////////////////////////////////////////////////train 1
	Mat image;
	image = imread("coin.png");
	Mat img_gray;
	cvtColor(image, img_gray, COLOR_BGR2GRAY);
	Mat img_threshold;
	threshold(img_gray, img_threshold, 0, 255, THRESH_OTSU);
	Mat kernel;
	kernel = getStructuringElement(MORPH_RECT, Size(3,3));

	Mat img_er, img_di, img_op, img_co;
	erode(img_threshold, img_er, kernel);
	dilate(img_threshold, img_di, kernel);
	morphologyEx(img_threshold, img_op, MORPH_OPEN, kernel);
	morphologyEx(img_threshold, img_co, MORPH_CLOSE, kernel);
	//imshow("img_er", img_er);
	//imshow("img_di", img_di);
	//imshow("img_op", img_op);
	//imshow("img_co", img_co);
	//waitKey(0);
	///////////////////////////////////////////////////////////////////train 2
	int num;
	Mat labels, states, cent;
	num = connectedComponentsWithStats(img_threshold, labels, states, cent);

	cout << num - 1 << endl;
	for (int i = 0; i < num; i++)
	{
		Rect rect;
		rect.x = states.at<int>(i,0);
		rect.y = states.at<int>(i, 1);
		rect.width = states.at<int>(i, 2);
		rect.height = states.at<int>(i, 3);
		rectangle(image, rect, Scalar(255, 0, 0));
	}
	///////////////////////////////////////////////////////////////////train 3
	Mat test2 = imread("IMG_1989.JPG",0);
	Mat test_thre;
	threshold(test2, test_thre, 100, 255, THRESH_BINARY_INV);

	Mat test_ker;
	test_ker = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	Mat test_er, test_op;
	morphologyEx(test_thre, test_op, MORPH_OPEN, test_ker, Point(-1, -1), 6);
	//erode(test_thre, test_er, test_ker,Point(-1,-1),6);

	int t_num;
	Mat t_labels, t_states, t_cent;
	t_num = connectedComponentsWithStats(test_op, t_labels, t_states, t_cent);

	cout << t_num - 1 << endl;
	for (int j = 0; j < t_num; j++)
	{
		Rect t_rect;
		t_rect.x = t_states.at<int>(j, 0);
		t_rect.y = t_states.at<int>(j, 1);
		t_rect.width = t_states.at<int>(j, 2);
		t_rect.height = t_states.at<int>(j, 3);
		rectangle(test_op, t_rect, Scalar(255, 0, 0));
	}

	///////////////////////////////////////////////////////////////////train 4
	
	Mat h_test = imread("clip.png");
	Mat h_gray;
	cvtColor(h_test, h_gray, COLOR_BGR2GRAY);
	Mat h_thre;
	threshold(h_gray, h_thre, 100, 255, THRESH_BINARY_INV);
	Mat h_ker;
	h_ker = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat h_op, h_er, h_di;
	//morphologyEx(h_thre, h_op, MORPH_OPEN, h_ker, Point(-1, -1), 3);
	erode(h_thre, h_er, h_ker, Point(-1, -1), 1);
	//dilate(h_er, h_di, h_ker, Point(-1, -1), 4);

	
	int h_num;
	Mat h_labels, h_states, h_cent;
	h_num = connectedComponentsWithStats(h_er, h_labels, h_states, h_cent);

	int s=0;
	for (int m = 0; m < h_num; m++)
	{
		Rect t_rect;
		t_rect.x = h_states.at<int>(m, 0);
		t_rect.y = h_states.at<int>(m, 1);
		t_rect.width = h_states.at<int>(m, 2);
		t_rect.height = h_states.at<int>(m, 3);
		if (h_states.at<int>(m, 3) < 800)
		{
			s++;
			rectangle(h_test, t_rect, Scalar(255, 0, 0));
		}
	}
	cout << s << endl;
	
	
	return 0;
}