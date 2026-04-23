#include "input.h"

#include "constants.h"

char InputHandler::getPressedChar(sf::Keyboard::Key key) const {
  int code = static_cast<int>(key);
  int aCode = static_cast<int>(sf::Keyboard::Key::A);

  if (code >= aCode && code < aCode + Constants::SYMBOL_COUNT) {
    return 'a' + (code - aCode);
  }
  return '\0';
}
