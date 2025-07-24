#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "트랙바 이벤트";
Mat image;

void onChange(int value, void *userdata) // 트랙바 콜백 함수 구현
{
	int add_value = value - 130; // -126 ~ 129
	cout << "추가 화소값 " << add_value << endl;

	Mat tmp = image + add_value; // 원본 행렬에 -126 ~ 129 사이값 더하기
	imshow(title, tmp);
}

int main()
{
	int value = 130;
	image = Mat(300, 400, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);
	// 트랙바 이름, 등록할 창 이름, 변경값, 최대값, 콜백함수 이름
	createTrackbar("밝기값", title, &value, 255, onChange);

	imshow(title, image);
	waitKey(0);
	return 0;
}