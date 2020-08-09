#include "image_lossless_compression.h"

int prediction(int predictor, int a, int b, int c) {
	switch (predictor)
	{
	case 1:
		return a;					// Predictor P1
	case 2:
		return b;					// Predictor P2
	case 3:
		return c;					// Predictor P3
	case 4:
		return a + b - c;			// Predictor P4
	case 5:
		return (a + b) - c / 2;		// Predictor P5
	case 6:
		return b + (a - c) / 2;		// Predictor P6
	case 7:
		return (a + b) / 2;			// Predictor P7
	default:
		return 0;					// Not Calculate
	}
}

image_lossless_compression::image_lossless_compression()
{
}

image_lossless_compression::image_lossless_compression(Mat intensity_value_matrix)
{
	image::image(intensity_value_matrix);
	// Make red intensity matrix
	intensity_of_red_color.resize(this->rows);
	for (int i = 0; i < intensity_of_red_color.size(); i++) {
		intensity_of_red_color[i].resize(this->cols);
		for (int j = 0; j < intensity_of_red_color.size(); j++) {
			Vec3b intensity = this->intensity_value_matrix.at<Vec3b>(i, j);
			intensity_of_red_color[i][j] = intensity[2];
		}
	}
	// Make green intensity matrix
	intensity_of_green_color.resize(this->rows);
	for (int i = 0; i < intensity_of_green_color.size(); i++) {
		intensity_of_red_color[i].resize(this->cols);
		for (int j = 0; j < intensity_of_green_color[i].size(); j++) {
			Vec3b intensity = this->intensity_value_matrix.at<Vec3b>(i, j);
			intensity_of_green_color[i][j] = intensity[1];
		}
	}
	// Make blue intensity matrix
	intensity_of_blue_color.resize(this->rows);
	for (int i = 0; i < intensity_of_blue_color.size(); i++) {
		intensity_of_blue_color[i].resize(this->cols);
		for (int j = 0; j < intensity_of_blue_color.size(); j++) {
			Vec3b intensity = this->intensity_value_matrix.at<Vec3b>(i, j);
			intensity_of_blue_color[i][j] = intensity[0];
		}
	}
}

void image_lossless_compression::load_image(string file_path)
{
	image::load_image(file_path);

	// Make red intensity matrix
	intensity_of_red_color.resize(this->rows);
	for (int i = 0; i < intensity_of_red_color.size(); i++) {
		intensity_of_red_color[i].resize(this->cols);
		for (int j = 0; j < intensity_of_red_color.size(); j++) {
			Vec3b intensity = this->intensity_value_matrix.at<Vec3b>(i, j);
			intensity_of_red_color[i][j] = intensity[2];
		}
	}

	// Make green intensity matrix
	intensity_of_green_color.resize(this->rows);
	for (int i = 0; i < intensity_of_green_color.size(); i++) {
		intensity_of_green_color[i].resize(this->cols);
		for (int j = 0; j < intensity_of_green_color[i].size(); j++) {
			Vec3b intensity = this->intensity_value_matrix.at<Vec3b>(i, j);
			intensity_of_green_color[i][j] = intensity[1];
		}
	}

	// Make blue intensity matrix
	intensity_of_blue_color.resize(this->rows);
	for (int i = 0; i < intensity_of_blue_color.size(); i++) {
		intensity_of_blue_color[i].resize(this->cols);
		for (int j = 0; j < intensity_of_blue_color.size(); j++) {
			Vec3b intensity = this->intensity_value_matrix.at<Vec3b>(i, j);
			intensity_of_blue_color[i][j] = intensity[0];
		}
	}
}

vector<vector<uint8_t>> image_lossless_compression::get_intensity_of_red_color()
{
	return intensity_of_red_color;
}

vector<vector<uint8_t>> image_lossless_compression::get_intensity_of_green_color()
{
	return intensity_of_green_color;
}

vector<vector<uint8_t>> image_lossless_compression::get_intensity_of_blue_color()
{
	return intensity_of_blue_color;
}

vector<vector<int>> image_lossless_compression::get_red_diff_matrix()
{
	return red_difference_matrix;
}

vector<vector<int>> image_lossless_compression::get_green_diff_matrix()
{
	return green_difference_matrix;
}

vector<vector<int>> image_lossless_compression::get_blue_diff_matrix()
{
	return blue_difference_matrix;
}

void image_lossless_compression::cal_diff_matrix(int predictor)
{
	// cal red difference matrix
		// Init difference matrix
	red_difference_matrix.resize(intensity_of_red_color.size());
	for (int i = 0; i < red_difference_matrix.size(); i++)
		red_difference_matrix[i].resize(intensity_of_red_color[i].size());

	red_difference_matrix[0][0] = (int)intensity_of_red_color[0][0];
		// Use P2 predictor for column 0
	for (int i = 1; i < red_difference_matrix.size(); i++)
		red_difference_matrix[i][0] = (int)intensity_of_red_color[i - 1][0] - (int)intensity_of_red_color[i][0];

		// Use P1 predictor for row 0
	for (int i = 1; i < red_difference_matrix[0].size(); i++)
		red_difference_matrix[0][i] = (int)intensity_of_red_color[0][i - 1] - (int)intensity_of_red_color[0][i];

	for (int i = 1; i < red_difference_matrix.size(); i++) {
		for (int j = 1; j < red_difference_matrix[i].size(); j++)
			red_difference_matrix[i][j] = prediction(predictor, intensity_of_red_color[i][j-1], intensity_of_red_color[i-1][j], intensity_of_red_color[i-1][j-1]) 
										  - (int)intensity_of_red_color[i][j] ;
	}

	// cal green difference matrix
		// Init difference matrix
	green_difference_matrix.resize(intensity_of_green_color.size());
	for (int i = 0; i < green_difference_matrix.size(); i++)
		green_difference_matrix[i].resize(intensity_of_green_color[i].size());

	green_difference_matrix[0][0] = (int)intensity_of_green_color[0][0];
		// Use P2 predictor for column 0
	for (int i = 1; i < green_difference_matrix.size(); i++)
		green_difference_matrix[i][0] = (int)intensity_of_green_color[i - 1][0] - (int)intensity_of_green_color[i][0];
		// Use P1 predictor for row 0
	for (int i = 1; i < green_difference_matrix[0].size(); i++)
		green_difference_matrix[0][i] = (int)intensity_of_green_color[0][i - 1] - (int)intensity_of_green_color[0][i];

	for (int i = 1; i < green_difference_matrix.size(); i++) {
		for (int j = 1; j < green_difference_matrix[i].size(); j++)
			green_difference_matrix[i][j] = prediction(predictor, intensity_of_green_color[i][j-1], intensity_of_green_color[i-1][j], intensity_of_green_color[i - 1][j - 1])
											- (int)intensity_of_green_color[i][j];
	}

	// cal blue difference matrix
		// Init blue difference matrix
	blue_difference_matrix.resize(intensity_of_blue_color.size());
	for (int i = 0; i < blue_difference_matrix.size(); i++)
		blue_difference_matrix[i].resize(intensity_of_blue_color[i].size());

	blue_difference_matrix[0][0] = (int)intensity_of_blue_color[0][0];
		// Use P2 predictor for column 0
	for (int i = 1; i < blue_difference_matrix.size(); i++)
		blue_difference_matrix[i][0] = (int)intensity_of_blue_color[i - 1][0] - (int)intensity_of_blue_color[i][0];
		
		// Use P1 predictor for row 0
	for (int i = 1; i < blue_difference_matrix[0].size(); i++)
		blue_difference_matrix[0][i] = (int)intensity_of_blue_color[0][i - 1] - (int)intensity_of_blue_color[0][i];

	for (int i = 1; i < blue_difference_matrix.size(); i++) {
		blue_difference_matrix[i].resize(intensity_of_blue_color[i].size());
		for (int j = 1; j < blue_difference_matrix[i].size(); j++)
			blue_difference_matrix[i][j] = prediction(predictor, intensity_of_blue_color[i][j-1], intensity_of_blue_color[i-1][j], intensity_of_blue_color[i - 1][j - 1])
											- (int)intensity_of_blue_color[i][j];
	}
}