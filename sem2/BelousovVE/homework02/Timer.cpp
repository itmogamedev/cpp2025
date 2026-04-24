#include "Timer.h"

#include "Constants.h"

Timer::Timer(sf::Time tm) : Time(tm) { start(); }

int32_t Timer::getRemainingTimeAsMilliseconds() {
  int32_t tm = this->asMilliseconds() - cl.getElapsedTime().asMilliseconds();
  return tm > 0 ? tm : 0;
}

void Timer::start() { cl.restart(); }

void Timer::stop() { cl.stop(); }

void Timer::draw(sf::RenderWindow& wn) {
  const sf::Font font(Constants::TEXT::font);
  sf::Text tmText(font, Constants::TIMER::timerText);

  int32_t t = this->getRemainingTimeAsMilliseconds();

  if (t > 0.f) {
    int sec = t / Constants::TIMER::intPrecision;
    int fracPart = t % Constants::TIMER::floatPrecision;

    std::string s = std::to_string(sec) + "." + std::to_string(fracPart);

    tmText.setString(Constants::TIMER::timerText + sf::String(s));
  } else {
    this->stop();
    tmText.setString(Constants::TIMER::timerText);
  }

  tmText.setPosition(Constants::TIMER::pos);
  tmText.setFillColor(sf::Color::Black);

  wn.draw(tmText);
}
