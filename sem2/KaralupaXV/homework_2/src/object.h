#ifndef __OBJECT_H
#define __OBJECT_H

class Object {
 public:
  virtual void update(float delta) = 0;
  virtual void draw() = 0;
};

#endif