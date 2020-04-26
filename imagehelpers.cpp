/*
  Author: Jason Comisi
  Description:
    The program reads a PGM image from the file "inImage.pgm",
    and outputs a modified image to "outImage.pgm"

  Used namespace std since it was used in the sample code
  Also used row and col in sample main for tasks
*/

//ALREADY HERE
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
  char c;
  int x;
  ifstream instr;
  instr.open("inImage.pgm");

  // read the header P2
  instr >> c;
  assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;
}

// Writes a PGM file
// Need to provide the array data and the image dimensions

void writeImage(int image[MAX_H][MAX_W], int height, int width, string file) {
  ofstream ostr;
  ostr.open(file);
  if (ostr.fail()) {
    cout << "Unable to write file\n";
    exit(1);
  };

  // print the header
  ostr << "P2" << endl;
  // width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' ';
			ostr << endl;
		}
	}
	ostr.close();
	return;
}

void invert(int image[MAX_H][MAX_W], int &h, int &w){
	int MaximumD[MAX_H][MAX_W];
	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
			MaximumD[row][col] = 255 - image[row][col];
		}
	}
	writeImage(MaximumD, h, w, "TASKA.pgm");
}


void invert_half(int image[MAX_H][MAX_W], int &h, int &w){
	int MaximumD[MAX_H][MAX_W];
	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
			if(col > w/2){
				MaximumD[row][col] = 255 - image[row][col];
			}
			else{
				MaximumD[row][col] = image[row][col];
			}
		}
	}
	writeImage(MaximumD, h, w, "TASKB.pgm");
}


void pixelate(int image[MAX_H][MAX_W], int &h, int &w){
	int MaximumD[MAX_H][MAX_W];
	for(int row = 0; row < h; row+=2) {
		for(int col = 0; col < w; col+=2) {
			int sum = 0;
			sum += image[row][col];
			sum += image[row+1][col];
			sum += image[row][col+1];
			sum += image[row+1][col+1];
			int avg = sum/4;
			MaximumD[row][col] = avg;
			MaximumD[row+1][col] = avg;
			MaximumD[row][col+1] = avg;
			MaximumD[row+1][col+1] = avg;
		}
	}
	writeImage(MaximumD, h, w, "TASKF.pgm");
}

void frame(int image[MAX_H][MAX_W], int &h, int &w){
	int MaximumD[MAX_H][MAX_W];
	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
			MaximumD[row][col] = image[row][col];
		}
	}
	for(int col = w/4; col < w-w/4; col++){
		MaximumD[h/4][col] = 255;
	}
	for(int col = w/4; col < w-w/4; col++){
		MaximumD[h-h/4][col] = 255;
	}
	for(int row = h/4; row < h-h/4; row++){
		MaximumD[row][w/4] = 255;
	}
	for(int row = h/4; row < h-h/4; row++){
		MaximumD[row][w-w/4] = 255;
	}
	writeImage(MaximumD, h, w, "TASKD.pgm");
}


void scale(int image[MAX_H][MAX_W], int &h, int &w){
	int MaximumD[MAX_H][MAX_W];
	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
			MaximumD[row*2][col*2] = image[row][col];
			MaximumD[row*2+1][col*2] = image[row][col];
			MaximumD[row*2][col*2+1] = image[row][col];
			MaximumD[row*2+1][col*2+1] = image[row][col];
		}
	}
	writeImage(MaximumD, h*2, w*2, "TASKE.pgm");
}
//-------------Enhancement----------------------------//
// I created a framed white canvas. A drawing or picture canvas
// be inserted to drawn in it.
void box(int image[MAX_H][MAX_W], int &h, int &w){
	int MaximumD[MAX_H][MAX_W];
	for(int row = 0; row < h; row++)
  {
		for(int col = 0; col < w; col++)
    {
			if(col > w/22 && col < w - w/22  && row > h/22 && row < h - h/22)
      {
				MaximumD[row][col] = 255;
			}
			else
      {
				MaximumD[row][col] = image[row][col];
			}
		}
	}
	writeImage(MaximumD, h, w, "TASKC.pgm");
}
//----------------------------------------------------//
