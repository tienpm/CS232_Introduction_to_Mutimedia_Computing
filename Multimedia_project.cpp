// Multimedia_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <iostream>
#include "image.h"
#include "image_lossless_compression.h"
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
	string image_path = samples::findFile("sample_01.png");
	image_lossless_compression img;
	img.load_image(image_path);
	vector<vector<uint8_t>> red_color = img.get_intensity_of_red_color();
	vector<vector<uint8_t>> green_color = img.get_intensity_of_green_color();
	vector<vector<uint8_t>> blue_color = img.get_intensity_of_blue_color();
	// Copmute difference matrix of RGB color with predictor p1 -> 1 ... p7 -> 7
	img.cal_diff_matrix(4);
	vector<vector<int>> dif_red_color = img.get_red_diff_matrix();
	vector<vector<int>> dif_green_color = img.get_green_diff_matrix();
	vector<vector<int>> dif_blue_color = img.get_blue_diff_matrix();
	ofstream file;
	file.open("intensity_of_red.txt");
	for (int i = 0; i < red_color.size(); i++) {
		for (int j = 0; j < red_color[i].size(); j++)
			file << (int)red_color[i][j] << " ";
		file << "\n";
	}
	file.close();
	file.open("intensity_of_green.txt");
	for (int i = 0; i < green_color.size(); i++) {
		for (int j = 0; j < green_color[i].size(); j++)
			file << (int)green_color[i][j] << " ";
		file << "\n";
	}
	file.close();
	file.open("intensity_of_blue.txt");
	for (int i = 0; i < blue_color.size(); i++) {
		for (int j = 0; j < blue_color[i].size(); j++)
			file << (int)blue_color[i][j] << " ";
		file << "\n";
	}
	file.close();
	file.open("diff_red.txt");
	for (int i = 0; i < dif_red_color.size(); i++) {
		for (int j = 0; j < dif_red_color[i].size(); j++)
			file << dif_red_color[i][j] << " ";
		file << "\n";
	}
	file.close();
	file.open("diff_green.txt");
	for (int i = 0; i < dif_green_color.size(); i++) {
		for (int j = 0; j < dif_green_color[i].size(); j++)
			file << (int)dif_green_color[i][j] << " ";
		file << "\n";
	}
	file.close();
	file.open("diff_blue.txt");
	for (int i = 0; i < dif_blue_color.size(); i++) {
		for (int j = 0; j < dif_blue_color[i].size(); j++)
			file << (int)dif_blue_color[i][j] << " ";
		file << "\n";
	}
	file.close();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

