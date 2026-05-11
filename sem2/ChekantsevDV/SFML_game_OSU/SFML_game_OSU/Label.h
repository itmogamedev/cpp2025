#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Label : public Transformable, public Drawable {
 private:
  Font font;
  Text text;
  void draw(RenderTarget& target, RenderStates states) const;

 public:
  Label(string text, string font = "PressStart2P-Regular.ttf");
  void setString(string text);
  void centerString(Vector2u window);
  Vector2f getSize();
};
