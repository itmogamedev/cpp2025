
#include "Timer.h"

Timer::Timer(float initialTime)

    : m_initialTime(initialTime)

      ,
      m_remainingTime(initialTime) {}

void Timer::update(float deltaTime) {
  if (m_remainingTime > 0.f) {
    m_remainingTime -= deltaTime;

    if (m_remainingTime < 0.f) {
      m_remainingTime = 0.f;
    }
  }
}

void Timer::reduce(float amount) {
  m_remainingTime -= amount;

  if (m_remainingTime < 0.f) {
    m_remainingTime = 0.f;
  }
}

void Timer::reset() { m_remainingTime = m_initialTime; }

void Timer::setZero() { m_remainingTime = 0.f; }

float Timer::getRemainingTime() const { return m_remainingTime; }

bool Timer::isFinished() const { return m_remainingTime <= 0.f; }
