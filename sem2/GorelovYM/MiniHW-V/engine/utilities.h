#pragma once
#include <string>
#include <vector>
#include "define.h"

#define PI 3.1415926f

// all just usefull functions
namespace Utilities
{
  // read and write whole file
  std::vector<uchar> ReadFile(std::string path);
  void WriteFile(std::string path, std::vector<uchar> data);

  // some math
  float Lerp(float a, float b, float t);
  bool Inside(float px, float py, float bx, float by, float bw, float bh);
  int Sign(float x); 
  float Dist(float x1, float y1, float x2, float y2);

  // bmp format parser
  struct BMP
  {
    // properties
    int width;
    int height;
    std::vector<uint> data;

    // parser
    BMP(std::vector<uchar> data);
  };

  // color's intensity
  float ColorIntensity(uint color);

  // color multiply
  uint ColorShade(uint color, float factor);

  // set random seed
  void RandSeed(uint seed = 0);

  // random in int range
  int RandRange(int min, int max);

  // random betweem 0 and 1
  float Randzo();

  // random from vector
  template<typename T>
  T RandVec(std::vector<T> vec) {
    return vec[RandRange(0, vec.size())];
  }
}