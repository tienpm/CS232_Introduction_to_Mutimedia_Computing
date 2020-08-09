#include "image.h"

using namespace std;
using namespace cv;

image::image()
{
}

image::image(Mat intensity_value_matrix)
{
	this->intensity_value_matrix = intensity_value_matrix;
	this->rows = this->intensity_value_matrix.rows;
	this->cols = this->intensity_value_matrix.cols;
}

void image::load_image(string file_path)
{
	this->intensity_value_matrix = imread(file_path, IMREAD_COLOR);
	if (this->intensity_value_matrix.empty()) {
		cout << "Couldn't read the image" << endl;
		return;
	}
	this->rows = this->intensity_value_matrix.rows;
	this->cols = this->intensity_value_matrix.cols;
}
