#pragma once
#include <memory>
#include "image.h"
#include "define.h"

// forward declaration
class Scene;
int main(void);

// namespace for all classes of objects
namespace Object
{
  // basic object class, must be renderable
  class Base
  {
    // owww we have a little friend
    friend class ::Scene;

    // properties
    protected:

      // tag for identification
      std::string tag = "";

      // center position and size
      float x = 0, y = 0;
      float width = 0, height = 0;

      // angle layer and image
      float angle = 0;
      int layer = 0;
      std::shared_ptr<Image> image = nullptr;

      // if false, camera will not affect on the position of this object
      bool relative = true;

    // public
    public:

      // constructor
      Base(float x, float y, std::string tag = "");
      
      // copy constructor
      Base(const Base& object) = default;

      // no args
      Base(void) = default;

      // to be inheritable
      virtual ~Base(void) { };

      // getters
      getter(X, x);
      getter(Y, y);
      getter(Width, width);
      getter(Height, height);
      getter(Tag, tag);
      getter(Angle, angle);
      getter(Layer, layer);
      getter(Relative, relative);
      getter(Image, image);

      // setters
      setter(X, x, value);
      setter(Y, y, value);
      setter(Width, width, value);
      setter(Height, height, value);
      setter(Tag, tag, value);
      setter(Angle, angle, value);
      setter(Layer, layer, value);
      setter(Relative, relative, value);
      setter(Image, image, value);
  };

  // sprite class
  class Sprite : public Base
  {
    // public
    public:

      // constructors
      Sprite(std::shared_ptr<Resources::Image> image,
             float x, float y, float w, float h,
             std::string tag = "");
      Sprite(const Sprite& sprite) = default;
      Sprite(void) = default;
  };
};

// namespace for uis
namespace UI
{
  // base class
  class Base : public Object::Base
  {
    // friends
    friend class ::Scene;

    // properties
    protected:
      void (*interact)(UI::Base* self) = nullptr;
      void (*renderer)(UI::Base* self) = nullptr;

    // public
    public:

      // constructors
      Base(int x, int y, int w, int h, std::string tag = "");
      Base(const Base& ui) = default;
      Base(void) : Base(0, 0, 0, 0) { };
  };

  // label class
  class Label : public Base
  {
    // properties
    private:
      std::string text;

    // public
    public:

      // constructor
      Label(std::string text,
            int x, int y, int w = -1, int h = -1,
            std::string tag = "");
      Label(const Label& label) = default;
      Label(void) : Label("", 0, 0, 0, 0) { };

      // setters and getters
      setter(Text, text, value);
      getter(Text, text);
  };

  // button class
  class Button : public Base
  {
    // properties
    private:

      // interstate
      bool hovered = false;
      
      // callback
      void (*callback)(UI::Button* self) = nullptr;

      // text on the button
      std::string text;
     
    // public
    public:

      // constructors
      Button(std::string text,
             int x, int y, int w, int h,
             void (*callback)(UI::Button* self) = nullptr,
             std::string tag = "");
      Button(const Button& button) = default;
      Button(void) : Button("", 0, 0, 0, 0, nullptr) { };

      // setters
      setter(Text, text, value);
      setter(Callback, callback, value);
      
      // getters
      getter(Text, text);
      getter(Callback, callback);
      getter(Hovered, hovered);

      // other
      bool clicked = false;
      bool released = false;
  };
};