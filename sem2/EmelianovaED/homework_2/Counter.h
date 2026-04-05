#ifndef COUNTER_H
#define COUNTER_H
class Counter {
  int points;

 public:
  Counter();
  int getPoints() const;
  void updateCounter(int win_point = 1);
  void resetCounter();
};
#endif  // !COUNTER_H
