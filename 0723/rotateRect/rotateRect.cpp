#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image(300, 500, CV_8UC3, Scalar(255, 255, 255)); // 행렬 선언
	Point2f center(250, 150), pts[4];
	Size2f size(300, 100);
	RotatedRect rot_rect(center, size, 50); // 회전 사각형 선언

	// 바깥 네모: 회전된 사각형을 감싸는 축에 맞춘 사각형
	Rect bound_rect = rot_rect.boundingRect();
	// 1) 바깥 네모 그리기
	rectangle(image, bound_rect, Scalar(0), 1);		 // 사각형 그리기
	circle(image, rot_rect.center, 1, Scalar(0), 2); // 원 그리기

	// 2) 안쪽 네모 그리기
	rot_rect.points(pts);
	for (int i = 0; i < 4; i++)
	{
		circle(image, pts[i], 4, Scalar(0), 1); // 꼭짓점 표시
		cout << pts[i] << endl;
		line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2); // 꼭짓점 잇는 직선
	}

	line(image, (pts[0] + pts[1]) * 0.5,
		 (pts[2] + pts[3]) * 0.5, Scalar(0, 255, 0), 2); // 초록 가로 중심선
	// line(image, pts[0], pts[2], Scalar(0, 0, 255), 2);	 // 빨간 대각선
	line(image,
		 Point(bound_rect.x, bound_rect.y + bound_rect.height / 2),
		 Point(bound_rect.x + bound_rect.width, bound_rect.y + bound_rect.height / 2),
		 Scalar(0, 0, 255), 2); // 바깥 네모 가로 빨간선

	cout << "bound_rect: " << bound_rect << endl;
	cout << "center: " << rot_rect.center << endl;
	cout << "size: " << rot_rect.size << endl;
	cout << "angle: " << rot_rect.angle << endl;

	imshow("회전사각형", image);
	waitKey(0);
	return 0;
}