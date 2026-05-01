
#ifndef SCORE_H

#define SCORE_H

class Score {
 public:
  Score();

  void increment();

  void reset();

  int getValue() const;

 private:
  int m_value;
};

#endif
