#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int w = 400;

void MyEllipse(Mat img, Point p, int r, Scalar color, int angle = 0)
{
	int thickness = -1;
	int lineType = 8;
	ellipse(img,
		p,
		Size(r, r),
		angle,
		0,
		360,
		color,
		thickness,
		lineType);
}

void RotateMat(Mat img, Mat &dst, double angle)
{
	Point center(img.cols / 2, img.rows / 2);
	double scale = 1;
	Mat rotateMat = getRotationMatrix2D(center, angle, scale);
	warpAffine(img, dst, rotateMat, img.size());
}

void DrawTaiji(Mat &img, int angle)
{
	img = Mat::zeros(400, 400, CV_8UC3);
	ellipse(img, Point(w / 2, w / 2), Size(w / 4 + 2, w / 4 + 2), angle, 0, 360, Scalar(0, 68, 255), 2, 8);

	ellipse(img, Point(w / 2, w / 2), Size(w / 4, w / 4), angle, 0, 180, Scalar(0, 0, 0), -1, 8);

	MyEllipse(img, Point(3 * w / 8, w / 2), w / 8, Scalar(255, 255, 255));

	ellipse(img, Point(w / 2, w / 2), Size(w / 4, w / 4), angle, 180, 360, Scalar(255, 255, 255), -1, 8);

	MyEllipse(img, Point(5 * w / 8, w / 2), w / 8, Scalar(0, 0, 0));

	MyEllipse(img, Point(3 * w / 8, w / 2), w / 16, Scalar(0, 0, 0));
	MyEllipse(img, Point(5 * w / 8, w / 2), w / 16, Scalar(255, 255, 255));
}

int main()
{
	Mat img;

	DrawTaiji(img, 0);		//画一个初始的太极图
	imshow("haxi", img);

	Mat dst;

	int angle = 0;
	while (true)			//无舍入误差的旋转
	{
		RotateMat(img, dst, angle);
		imshow("excited", dst);

		angle++;
		angle %= 360;

		char c = waitKey(10);	//esc结束旋转
		if (c == 27)
			break;
	}

	while (true)			//旋转带来的累计的舍入误差效果
	{
		RotateMat(img, img, 1);
		imshow("excited2", img);
		char c = waitKey(10);	//esc结束旋转
		if (c == 27)
			break;
	}

	waitKey(0);
	return 0;
}