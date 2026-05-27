#pragma once
#include <vector>
#include "define.h"

// physiX sexy class with all the math ;(
class Body
{
  // friend
  friend class Scene;

  // properties
  private:

    // unhandled
    bool unhandled = false;

    // position
    float x = 0, y = 0, w = 0, h = 0;
    
    // velocity and friction
    float vx = 0, vy = 0;
    float friction = 0.935f;

    // tag to determine
    char tag = '\0';

    // callback, should return true to prevent interception
    void (*callback)(Body* self, Body* other) = nullptr;

  // public
  public:

    // constructor
    Body(float x, float y, float w, float h,
          char tag = '\0',
          void (*callback)(Body* self, Body* other) = nullptr);

    // getters and setters
    getter(X, x);
    getter(Y, y);
    getter(Width, w);
    getter(Height, h);
    getter(VelocityX, vx);
    getter(VelocityY, vy);
    getter(Friction, 1 - friction);
    getter(Tag, tag)

    // setters
    setter(X, x, value);
    setter(Y, y, value);
    setter(Width, w, value);
    setter(Height, h, value);
    setter(VelocityX, vx, value);
    setter(VelocityY, vy, value);
    setter(Friction, friction, 1 - value);
    setter(Tag, tag, value);
    setter(Callback, callback, value);
    setter(Handled, unhandled, !value);

    // things to move
    void ApplyForce(float x, float y);
    void ApplyVector(float angle, float length);
    bool Collides(Body* other, float ax = 0, float ay = 0);
};