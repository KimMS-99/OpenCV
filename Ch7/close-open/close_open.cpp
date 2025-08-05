#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 마스크 원소와 마스크 범위 입력화소 간의 일치 여부 체크
bool check_match(Mat img, Point start, Mat mask, int mode = 0)
{
	for (int u = 0; u < mask.rows; u++)
	{
		for (int v = 0; v < mask.cols; v++)
		{
			Point pt(v, u);
			int m = mask.at<uchar>(pt);		   // 마스크 계수
			int p = img.at<uchar>(start + pt); // 해당 위치 입력화소

			bool ch = (p == 255); // 일치 여부 비교
			if (m == 1 && ch == mode)
				return false;
		}
	}
	return true;
}

void erosion(Mat img, Mat &dst, Mat mask) // 침식 연산
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;
	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, 0);
			dst.at<uchar>(i, j) = (check) ? 255 : 0;
		}
	}
}

void dilation(Mat img, Mat &dst, Mat mask) // 팽창 연산
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	if (mask.empty())
		mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;
	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool check = check_match(img, start, mask, 1);
			dst.at<uchar>(i, j) = (check) ? 0 : 255;
		}
	}
}

void opening(Mat img, Mat &dst, Mat mask) // 열림 연산
{
	Mat tmp;
	erosion(img, tmp, mask);
	dilation(tmp, dst, mask);
}

void closing(Mat img, Mat &dst, Mat mask) // 닫힘 연산
{
	Mat tmp;
	dilation(img, tmp, mask);
	erosion(tmp, dst, mask);
}

int main()
{
	Mat image = imread("../image/morph_test1.jpg", 0);
	CV_Assert(image.data);
	Mat th_img, dst1, dst2, dst3, dst4;
	threshold(image, th_img, 128, 255, THRESH_BINARY);

	Matx<uchar, 3, 3> mask;
	mask << 0, 1, 0,
		1, 1, 1,
		0, 1, 0;

	opening(th_img, dst1, (Mat)mask);			   // 사용자 정의함수 열림 함수 호출
	closing(th_img, dst2, (Mat)mask);			   // 사용자 정의함수 닫힘 함수 호출
	morphologyEx(th_img, dst3, MORPH_OPEN, mask);  // OpenCV 열림 함수
	morphologyEx(th_img, dst4, MORPH_CLOSE, mask); // OpenCV 닫힘 함수

	imshow("th_img", th_img);
	// imshow("User_opening", dst1), imshow("User_closing", dst2);
	imshow("OpenCV_opening", dst3), imshow("OpenCV_closing", dst4);
	waitKey();
	return 0;
}