#include "resource.h"
#include "object.h"
#include "engine.h"
#include "utilities.h"
#include "input.h"

// base constructor
Object::Base::Base(float x, float y, std::string tag)
  : x(x), y(y), tag(tag) { }

// sprite constructor
Object::Sprite::Sprite(std::shared_ptr<Resources::Image> img,
  float x, float y, float w, float h, std::string tag) 
    : Base(x, y, tag) {
  this->width = w;
  this->height = h;
  this->image = img;
  this->relative = true;
}

// base constructor
UI::Base::Base(int x, int y, int w, int h, std::string tag) {
  this->relative = false;
  this->x = x;
  this->y = y;
  this->width = w;
  this->height = h;
  this->image = std::make_shared<Resources::Image>(w, h);
  this->tag = tag;
  this->layer = 1000;
}

// label constructor
UI::Label::Label(
  std::string text, int x, int y,
  int w, int h, std::string tag)
    : Base(x, y, w, h, tag) 
{
  // default width and height
  if (w == -1 || h == -1) {
    this->width = (Engine::DefaultFont()->Width()
      + Engine::DefaultFont()->SpacingX()) * text.size();
    this->height = Engine::DefaultFont()->Height();
    this->image->Resize(this->width, this->height);
  }

  // set the params
  this->text = text;
  
  // set the render function
  this->renderer = [](UI::Base* self) {
    auto label = dynamic_cast<UI::Label*>(self);
    label->image->Fill(TRANSPARENT);
    label->image->Write(
      Engine::DefaultFont(), label->text, 0, 0, 0xffffff);
  };
}

// button constructor
UI::Button::Button(std::string text,
  int x, int y, int w, int h,
  void (*callback)(UI::Button* self),
  std::string tag)
    : Base(x, y, w, h, tag)
{
  // set the params
  this->text = text;
  this->callback = callback;

  // set the render function
  this->renderer = [](UI::Base* self) {
    auto button = dynamic_cast<UI::Button*>(self);
    button->image->Fill(
      0, 0, button->width, button->height,
      button->hovered ? 0x666666 : 0x444444);
    button->image->Write(
      Engine::DefaultFont(), button->text, 2, 2, 0xffffff);
  };

  // set the interact function
  this->interact = [](UI::Base* self)
  {
    // get the button
    auto button = dynamic_cast<UI::Button*>(self);
    
    // check mouse
    bool wasClicked = button->clicked;
    button->clicked = Input::Mouse(Input::Primary);
    button->released = wasClicked && !button->clicked;
    
    // check if mouse is inside
    button->hovered = Utilities::Inside(
      Input::MouseX(), Input::MouseY(),
      button->x, button->y, button->width, button->height);

    // check if mouse 
    if (button->released && button->hovered)
      button->callback(button);
  };
}