// arithmetic_coding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Encode.h"
#include "Decode.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int get_size_file(string file_path);

struct compress_size{
	int input_file_size;
	int encode_file_size;
	int decode_file_size;
	float compress_ratio;
};

int main( )
{
	string input_dir = "input/";
	string encode_dir = "encode/";
	string decode_dir = "decode/";
	vector<compress_size> info_compression;
	for (int i = 1; i <= 30; i++) {
		cout << "===== MAKE ENCODE AND DECODE FILE FOR SAMPLE " << i << " =====\n";
		string input_path, encode_path, decode_path;
		if (i < 10) {
			input_path = input_dir + "sample0" + to_string(i) + ".txt";
			encode_path = encode_dir + "sample0" + to_string(i) + ".txt";
			decode_path = decode_dir + +"sample0" + to_string(i) + ".txt";
		}
		else {
			input_path = input_dir + "sample" + to_string(i) + ".txt";
			encode_path = encode_dir + "sample" + to_string(i) + ".txt";
			decode_path = decode_dir + +"sample" + to_string(i) + ".txt";
		}	
		Encode encode_text;
		encode_text.encode(input_path, encode_path);
		Decode decode_text;
		decode_text.decode(encode_path, decode_path);
		compress_size info;
		info.input_file_size = get_size_file(input_path);
		info.encode_file_size = get_size_file(encode_path);
		info.decode_file_size = get_size_file(decode_path);
		info.compress_ratio = (float)info.input_file_size / (float)info.encode_file_size;
		info_compression.push_back(info);
	}
	cout << "\n[INFO] END ENCODE AND DECODE PROCESS\n\n";
	cout << "\t\t\t================================ COMPRESSION INFORMATION ==================================\n";
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "|	Sample		|	Input file size (bytes)	|	Encode file size (bytes)	|	Decode file size (bytes) | Compress Ratio|\n";
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < info_compression.size(); i++)
		if (i < 9) {
			cout << "|	sample0" << i + 1 << "	|		" << info_compression[i].input_file_size << "		|		" << info_compression[i].encode_file_size << "			|		" << info_compression[i].decode_file_size << "	          |      " << setprecision(5) << info_compression[i].compress_ratio << "   |\n";
		}
		else {
			cout << "|	sample" << i + 1 << "	|		" << info_compression[i].input_file_size << "		|		" << info_compression[i].encode_file_size << "			|		" << info_compression[i].decode_file_size << "	          |      " << setprecision(5) << info_compression[i].compress_ratio << "   |\n";
		}
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------\n";
	return 0;
}

int get_size_file(string file_path) {
	ifstream file(file_path, ios::binary);
	file.seekg(0, ios::end);
	int file_size = file.tellg();
	return file_size;
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
