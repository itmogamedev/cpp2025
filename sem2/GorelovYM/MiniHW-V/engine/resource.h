#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "define.h"

// global definition
int main(void);

// namespace for resources
namespace Resources
{  
  // inheritable base class
  class Base
  {
    // friends
    friend int ::main(void);

    // weird templates
    template <class T> friend T* Get(std::string);
    template <class T> friend void Load(std::string, std::string);

    // all the resources
    private:
      static std::unordered_map<std::string,
                                std::unique_ptr<Base>> members;

    // to make it inheritable
    public:
      virtual ~Base() {};
  };

  // image resource class
  class Image;
  
  // font resource class
  class Font : public Base
  {
    // friends
    friend class Image;

    // properties
    private:

      // sizing of the font
      int width;
      int height;
      int spacingx;
      int spacingy;

      // data of the font
      std::unordered_map<char, std::string> chars;

    // constructor
    public:
      Font(std::string path);

      // getters
      getter(Width, width);
      getter(Height, height);
      getter(SpacingX, spacingx);
      getter(SpacingY, spacingy);
      refer(Chars, chars);
  };

  // plain dumb text resource class split by newlines
  class Text : public Base
  {
    // properties
    private:
      std::vector<std::string> lines;
      std::vector<uchar> bytes;

    // public stuff
    public:

      // constructor
      Text(std::string path);

      // getters
      getter(Lines, lines);
      getter(Bytes, bytes)
  };

  // palettes resource
  class Palettes : public Base
  {
    // properties
    private:
      std::vector<std::vector<uint>> list;

    // public
    public:

      // constructor
      Palettes(std::string path);

      // getters
      refer(List, list);
  };

  // gets resource by name
  template <class T>
  static T* Get(std::string name) {
    return dynamic_cast<T*>(Base::members[name].get());
  };

  // templated load
  template <class T>
  static void Load(std::string name, std::string path) {
    Base::members[name].reset(
      static_cast<Resources::Base*>(new T(path)));;
  };
};