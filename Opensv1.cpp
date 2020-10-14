#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/core/core.hpp"



using namespace std;
using namespace cv;


void transform(Point2f* src_vertices, Point2f* dst_vertices, Mat& src, Mat &dst) {
	Mat M = getPerspectiveTransform(src_vertices, dst_vertices);
	warpPerspective(src, dst, M, dst.size(), INTER_LINEAR, BORDER_CONSTANT);
}


int frameWidth = 1280;
int frameHeight = 720;

int main(int argc, char const *argv[]) {

	

	// capture object
	VideoCapture capture("challenge.mp4");

	int vverh__ = 100, niz__ = 340, visota__ = 100;

	namedWindow("src", 1);

	createTrackbar("Topline", "src", &vverh__, 1280);
	createTrackbar("Baselane", "src", &niz__, 720);
	createTrackbar("Hight", "src", &visota__, 2000);


	// mat container to receive images
	Mat src, destination;

	while (true) {

		capture >> src;

		resize(src, src, Size(frameWidth, frameHeight));

		Point p1(660 - vverh__, 600 - visota__), p2(660 + vverh__, 600 - visota__), p3(660 - niz__, 600), p4(660 + niz__, 600);
		Scalar colorLine(0, 0, 255);
		int thicknessLine = 1;
		line(src, p1, p2, colorLine, thicknessLine);
		line(src, p3, p4, colorLine, thicknessLine);

		line(src, p1, p3, colorLine, thicknessLine);
		line(src, p2, p4, colorLine, thicknessLine);
		

		Point2f src_vertices[4];
		
		src_vertices[0] = Point(660 - vverh__, 600 - visota__);
		src_vertices[1] = Point(660 + vverh__, 600 - visota__);
		src_vertices[3] = Point(660 - niz__, 600);
		src_vertices[2] = Point(660 + niz__, 600);

		Point2f dst_vertices[4];
		dst_vertices[0] = Point(0, 0);
		dst_vertices[1] = Point(640, 0);
		dst_vertices[2] = Point(640, 480);
		dst_vertices[3] = Point(0, 480);


		Mat video = src.clone();
					
		
		Mat M = getPerspectiveTransform(src_vertices, dst_vertices);		
		Mat dst(480, 640, CV_8UC3);
		warpPerspective(video, dst, M, dst.size());

		
		imshow("src", video);
		imshow("dst", dst);
		
		waitKey(25);
	}


	return 0;
}