
#ifndef TIMER_H

#define TIMER_H

class Timer {
 public:
  Timer(float initialTime = 30.f);

  void update(float deltaTime);

  void reduce(float amount);

  void reset();

  void setZero();

  float getRemainingTime() const;

  bool isFinished() const;

 private:
  float m_remainingTime;
  float m_initialTime;
};

// Закрываем защиту от повторного включения
#endif
