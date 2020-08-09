#pragma once
#include "image.h"
class image_lossless_compression : public image
{
	vector<vector<uint8_t>> intensity_of_red_color;
	vector<vector<uint8_t>> intensity_of_green_color;
	vector<vector<uint8_t>> intensity_of_blue_color;	
	vector<vector<int>> red_difference_matrix;
	vector<vector<int>> green_difference_matrix;
	vector<vector<int>> blue_difference_matrix;
public:
	image_lossless_compression();
	image_lossless_compression(Mat intensity_value_matrix);
	void load_image(string file_path);
	vector<vector<uint8_t>> get_intensity_of_red_color();
	vector<vector<uint8_t>> get_intensity_of_green_color();
	vector<vector<uint8_t>> get_intensity_of_blue_color();
	void cal_diff_matrix(int predictor);
	vector<vector<int>> get_red_diff_matrix();
	vector<vector<int>> get_green_diff_matrix();
	vector<vector<int>> get_blue_diff_matrix();
	// Compress algorithm function
};