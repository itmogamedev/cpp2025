#include "input.h"

// all the initializators
bool Input::keys[KeyCount];
bool Input::buttons[ButtonCount];
int Input::mouseX;
int Input::mouseY;

// get keyboard press
bool Input::Key(int key) {
  return keys[key];
}

// get mouse position
bool Input::Mouse(int button) {
  return buttons[button];
}