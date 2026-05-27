#include "body.h"
#include <cmath>

// body creation
Body::Body(
  float x, float y, float w, float h, char tag,
  void (*callback)(Body* self, Body* other))
  : x(x), y(y), w(w), h(h), tag(tag), callback(callback) { }

// collision check
bool Body::Collides(Body* other, float ax, float ay) {
  return (std::abs(x - other->x + ax) < w + other->w)
      && (std::abs(y - other->y + ay) < h + other->h);
}

// apply force
void Body::ApplyForce(float ax, float ay)
  { vx += ax, vy += ay; }

// apply vector
void Body::ApplyVector(float angle, float length) {
  vx += length * std::cos(angle);
  vy += length * std::sin(angle);
}