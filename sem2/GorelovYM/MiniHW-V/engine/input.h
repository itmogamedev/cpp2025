#pragma once
#include "define.h"

// class for managing input
class Input
{
  // friends
  friend int main();

  // properties
  private:
    
    // all the properties
    static bool keys[];
    static bool buttons[];
    static int mouseX;
    static int mouseY;

  // enums
  public:

    // getters
    static getter(MouseX, mouseX);
    static getter(MouseY, mouseY);

    // keyboard and mouse buttons getters
    static bool Key(int key);
    static bool Mouse(int button);

    // all the keys
    enum {
      // alphabet
      A, B, C, D, E, F, G, H, I, J, K, L, M,
      N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

      // digits
      D0, D1, D2, D3, D4, D5, D6, D7, D8, D9,
      
      // special
      Escape, LCtrl, LShift, LAlt, LSystem,
      RCtrl, RShift, RAlt, RSystem,
      Space = 57, Enter, Backspace, Tab,
      Delete = 66,
      
      // punctuation
      LBracket = 46, RBracket, Semicolon, Comma, Period,
      Apostrophe, Slash, Backslash, Grave, Equal, Hyphen,
      
      // arrows
      Left = 71, Right, Up, Down,
      
      // function keys
      F1 = 85, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
      KeyCount = 100
    };

    // all the mouse buttons
    enum { Primary, Secondary, Middle, ButtonCount = 5 };
};