#pragma once
#include "Compress.h"
#include <string>

using namespace std;

class Decode : public Compress
{
	int low, high;
	int value;

	int buffer;
	int	bits_in_buf;
	bool end_decoding;

	ifstream in;
	ofstream out;
public:
	Decode(void);
	~Decode(void);

	void load_first_value(void);
	void decode(string infile, string outfile);
	int decode_symbol(void);
	int get_bit(void);
};

