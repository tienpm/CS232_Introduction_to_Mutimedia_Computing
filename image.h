#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

class image
{
protected:
	Mat intensity_value_matrix;
	int rows, cols;
public:
	image();
	image(Mat intensity_value_matrix);
	void load_image(string file_path);
};

