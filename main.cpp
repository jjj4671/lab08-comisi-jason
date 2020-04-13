#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include "imagehelpers.h"

int main() {
  int img[MAX_H][MAX_W];
  int height, width;
  readImage(img, height, width);
  invert(img, height, width);
  invert_half(img, height, width);
  box(img, height, width);
  frame(img, height, width);
  scale(img, height, width);
  pixelate(img, height, width);
}
