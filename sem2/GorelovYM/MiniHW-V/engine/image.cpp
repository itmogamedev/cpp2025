#include <cmath>
#include <algorithm>
#include "utilities.h"
#include "image.h"

// image constructor via loading
Image::Image(std::string path)
{
  // read the file
  std::vector<uchar> data = Utilities::ReadFile(path);

  // parse the bmp
  Utilities::BMP bmp(data);
  this->width  = bmp.width;
  this->height = bmp.height;
  this->pixels = bmp.data;
}

// image constructor via size and creation
Image::Image(int width, int height) {
  this->width  = width;
  this->height = height;
  this->pixels.resize(width * height);
}

// resize the image
void Image::Resize(int width, int height) {
  this->width  = width;
  this->height = height;
  this->pixels.resize(width * height);
  pixels.assign(width * height, TRANSPARENT);
}

// cut a part from the image
std::shared_ptr<Image> Image::Cut(int x, int y, int width, int height)
{
  // create a new image
  auto image = std::make_shared<Image>(width, height);
  
  // copy the required pixels
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      image->pixels[j * width + i] =
        pixels[(y + j) * this->width + x + i];
  
  // return the image
  return image;
}

// get a pixel
uint Image::Get(int x, int y) {
  if (x < 0 || x >= width ||
      y < 0 || y >= height)
    return 0;
  return pixels[y * width + x];
}

// set a pixel
void Image::Set(int x, int y, uint color) {
  if (x < 0 || x >= width ||
      y < 0 || y >= height)
    return;
  pixels[y * width + x] = color;
}

// fill the rectangle
void Image::Fill(int x, int y, int width, int height, uint color) {
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      Set(x + i, y + j, color);
}

// clear the image
void Image::Fill(uint color) {
  std::fill(pixels.begin(), pixels.end(), color);
}

// draw scaled image
void Image::Draw(Image* source, int dx, int dy, int dw, int dh)
{
  // caching
  int iw = source->width;
  int ih = source->height;
  uint* id = source->pixels.data();

  // full image
  if (!dw || !dh)
    dw = iw, dh = ih;

  // source step (horizontal and vertical)
  float ssh = static_cast<float>(iw) / dw;
  float ssv = static_cast<float>(ih) / dh;

  // drawing loop
  for (int x = 0; x < dw; x++) {
    for (int y = 0; y < dh; y++) {
      uint color = id[static_cast<int>(y * ssv) * iw
        + static_cast<int>(x * ssh)];
      if (color != TRANSPARENT)
      Set(dx + x, dy + y, color);
    }
  }
}

// draw with rotation
void Image::DrawEx(Image* image, int dx, int dy, int dw, int dh, float angle)
{
  // caching
  int iw = image->width;
  int ih = image->height;
  uint* id = image->pixels.data();

  // full image
  if (!dw || !dh)
    dw = iw,
    dh = ih;

  // cos and sin of the angle
  float ca = std::cos(angle);
  float sa = std::sin(angle);

  // inverse scale x and y
  float isx = static_cast<float>(iw) / dw;
  float isy = static_cast<float>(ih) / dh;

  // true destination size (hypot)
  int hw = (std::abs(dw * ca) + std::abs(dh * sa)) / 2;
  int hh = (std::abs(dw * sa) + std::abs(dh * ca)) / 2;

  // clamp the size
  int cx1 = -hw + std::max(0, hw - dx);
  int cx2 =  hw - std::max(0, dx + hw - (width - 1));
  int cy1 = -hh + std::max(0, hh - dy);
  int cy2 =  hh - std::max(0, dy + hh - (height - 1));

  // drawing loop
  for (int x = cx1; x <= cx2; x++) {
    for (int y = cy1; y <= cy2; y++)
    {
      // inverse rotation
      int sx = (( x * ca + y * sa) + dw / 2.0f) * isx;
      int sy = ((-x * sa + y * ca) + dh / 2.0f) * isy;
      
      // check if inside and set
      if (sx >= 0 && sx < iw && sy >= 0 && sy < ih
          && id[sy * iw + sx] != TRANSPARENT)
        Set(dx + x, dy + y, id[sy * iw + sx]);
    }
  }
}

// write text
void Image::Write(Resources::Font* font, std::string text,
  int x, int y, uint color)
{
  // get an initial x for newlines
  int ix = x;

  // write each character
  for (char c : text)
  {
    // check for newline
    if (c == '\n') {
      x = ix;
      y += font->height + font->spacingy;
      continue;
    }

    // draw the character
    if (c != ' ') {
      std::string data = font->chars[c];
      for (int j = 0; j < font->height; j++)
        for (int i = 0; i < font->width; i++)
          if (data[j * font->width + i] == '#')
            Set(x + i, y + j, color);
    }

    // move the x
    x += font->width + font->spacingx;
  }
}

// tint the image
void Image::Tint(uint color) {
  for (int i = 0; i < width * height; i++)
    pixels[i] = Utilities::ColorShade(color, 
      Utilities::ColorIntensity(pixels[i]));
}