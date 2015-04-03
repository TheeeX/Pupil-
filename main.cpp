#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"

using namespace cv;
using namespace std;

Mat negative(Mat);

int main()
{
	VideoCapture cap(0);
	cap.open(0);
	
	Mat neg;
	Mat edges;

	/*-- Windows --*/
	namedWindow("edges", 1);
	namedWindow("neg", 1);

	for (;;)
	{
		Mat frame;
		cap >> frame; 

		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(3, 3), 1.5, 1.5);

		neg = negative(frame);
		
		imshow("edges", edges);
		imshow("neg", neg);
		
		int c = waitKey(10);
		if ((char)c == 'c') { break; }
	}
	
	return 0;
}

Mat negative(Mat image){

	// initialize the output matrix with zeros
	Mat new_image = Mat::zeros(image.size(), image.type());

	// create a matrix with all elements equal to 255 for subtraction
	Mat sub_mat = Mat::ones(image.size(), image.type()) * 255;

	//subtract the original matrix by sub_mat to give the negative output new_image
	subtract(sub_mat, image, new_image);

	return new_image;
}
