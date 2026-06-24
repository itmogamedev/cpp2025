#pragma once
#include <vector>
#include <memory>
#include <string>
#include "define.h"
#include "resource.h"

#define TRANSPARENT 0xff00ff

// the graphics class
class Resources::Image : public Resources::Base
{
  // friends
  friend int ::main(void);
  friend void Load<Image>(std::string, std::string);

  // properties
  private:
    int width;
    int height;
    std::vector<uint> pixels;

    // private constructor for resource loading
    Image(std::string path);
  
  // public
  public:

    // constructor for manual creation
    Image(int width, int height);

    // getters and refers
    getter(Width,  width)
    getter(Height, height)
    refer(Pixels, pixels)

    // resize the image (possibly breaks it)
    void Resize(int width, int height);

    // image cutter that returns a shared image
    std::shared_ptr<Image> Cut(int x, int y, int width, int height);

    // get and set a pixel (with bounds checking)
    uint Get(int x, int y);
    void Set(int x, int y, uint color);

    // fill the rectangle
    void Fill(int x, int y, int width, int height, uint color);
    void Fill(uint color);

    // image drawing algorithms, second is less efficient
    void Draw(Image* source, int dx, int dy, int dw = 0, int dh = 0);
    void DrawEx(Image* source, int dx, int dy,
      int dw, int dh, float angle);

    // write some text
    void Write(Resources::Font* font, std::string text,
      int x, int y, uint color);

    // color to some color
    void Tint(uint color);
};

// alias
using Image = Resources::Image;