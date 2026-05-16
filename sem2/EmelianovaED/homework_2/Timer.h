#ifndef TIMER_H
#define TEMER_H
class Timer {
  float remaining_time;

 public:
  Timer(float init_time = 30.0f);
  void resetTimer(float init_time);
  void updateTimer(float delta_time);
  void reduceTimer(float amount);  // уменьшение времени при ошибке
  float getRemainingTime() const;  // устанавливаетс€ оставшеес€ врем€
  bool isExpired() const;          // флаг истечени€ времени
};
#endif
