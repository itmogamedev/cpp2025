#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <cmath>
#include "utilities.h"
#include <iostream>


// read whole file
std::vector<uchar> Utilities::ReadFile(std::string path)
{
  // open file
  std::ifstream file(path,
    std::ios::in | std::ios::binary | std::ios::ate);
  
  // create buffer
  std::vector<uchar> buffer;
  buffer.resize(file.tellg());

  // read the file and return
  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
  file.close();
  return buffer;
}

// write whole file
void Utilities::WriteFile(std::string path, std::vector<uchar> data)
{
  // open file
  std::ofstream file(path,
    std::ios::out | std::ios::binary);
  
  // write the file
  file.write(reinterpret_cast<char*>(data.data()), data.size());
  file.close();
}

// parse bmp
Utilities::BMP::BMP(std::vector<uchar> data)
{
  // get the data from the header
  int offset = data[0x0a] + data[0x0b] * 256;
  int width  = this->width = data[0x12] + data[0x13] * 256;
  int height = this->height = data[0x16] + data[0x17] * 256;

  // allocate uint vectors
  std::vector<uchar> vuchars(width * height * sizeof(uint));
  this->data.resize(width * height);

  // mirror vertically
  for (int x = 0; x < width * sizeof(uint); x++)
    for (int y = 0; y < height; y++)
      vuchars[y * width * sizeof(uint) + x] =
        data[offset + (height - y - 1) * (width * sizeof(uint)) + x];

  // reverse the byte order
  for (int i = 0; i < this->data.size(); i++)
    this->data[i] = vuchars[i * 4 + 2] << 16
                  | vuchars[i * 4 + 1] << 8
                  | vuchars[i * 4];
}

// linear interpolation
float Utilities::Lerp(float a, float b, float t) {
  return (b - a) * t + a;
}

// point inside rectangle
bool Utilities::Inside(
  float px, float py, float bx, float by, float bw, float bh) {
  return px >= bx && px < bx + bw && py >= by && py < by + bh;
}

// sign function
int Utilities::Sign(float x) {
  return (x >= 0) * 2 - 1;
}

// seed for random
static uint seed = 0;

// internal random number generator (OMG MAGIC NUMBERS!!!)
static int Rand() {
  return (seed = seed * 214013 + 2531011) & 0xffff;
}

// set random seed
void Utilities::RandSeed(uint s) {
  seed = s ? s : std::time(NULL);
}

// generate random number in range
int Utilities::RandRange(int min, int max) {
  return min + Rand() % (max - min);
}

// generate random number between 0 and 1
float Utilities::Randzo() {
  return Rand() / static_cast<float>(0xffff);
}

// get intensity of color
float Utilities::ColorIntensity(uint color) {
  return (((color & 0xff0000) >> 16)
    + ((color & 0x00ff00) >> 8) + (color & 0x0000ff)) / 768.0f;
}

// get shaded color
uint Utilities::ColorShade(uint color, float factor) {
  return (std::min(0xffu, static_cast<uint>(((color & 0xff0000) >> 16) * factor)) << 16)
       | (std::min(0xffu, static_cast<uint>(((color & 0xff00) >> 8) * factor)) << 8)
       | (std::min(0xffu, static_cast<uint>((color & 0xff) * factor)));
}

// distance between two points
float Utilities::Dist(float x1, float y1, float x2, float y2) {
  return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}