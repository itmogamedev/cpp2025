#include <string>
#include <algorithm>
#include "scene.h"
#include "engine.h"

// lots of konchenniye funkcii here
Scene::Scene(std::string name,
             void (*init)(void),
             void (*update)(void),
             void (*destroy)(void)) {
  this->init = init;
  this->update = update;
  this->destroy = destroy;
  camera.x = camera.y = camera.angle = 0;
  camera.scale = 1;
  Members()[name] = this;
};

// destructor
Scene::~Scene(void) {
  if (destroy != nullptr)
    destroy();
}

// switch to another scene
void Scene::Switch(std::string name) {
  Current() = Members()[name];
}

// remove object's existence (omg, this causes crash for clones)
void Scene::Remove(Object::Base* object) {
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i] == object) {
      delete objects[i];
      objects.erase(objects.begin() + i);
      break;
    }
  }
}

// remove objects by tag
void Scene::Remove(std::string tag) { }

// find object by tag
std::vector<Object::Base*> Scene::Find(std::string tag) {
  auto size = objects.size();
  std::vector<Object::Base*> result;
  for (int i = 0; i < size; i++)
    if (objects[i]->tag == tag)
      result.push_back(objects[i]);
  return result;
}

// init all scenes
void Scene::InitAll(void) {
  for (auto& scene : Members())
    if (scene.second->init != nullptr)
      scene.second->init();
}

// update current scene
void Scene::UpdateCurrent()
{
  // bodies
  auto bodies = Current()->bodies;

  // make all bodies unhandled
  for (auto& body : bodies)
    body->unhandled = true;

  // do until everycollision is handled
  for (int o = 0; o < 50; o++)
  {
    // count unhandled
    int count = 0;
    for (int i = 0; i < bodies.size(); i++)
      count += bodies[i]->unhandled;

    // quit loop
    if (count == 0)
      break;

    // iterate through all bodies
    for (int i = 0; i < bodies.size(); i++)
    {
      // unhandled
      if (!bodies[i]->unhandled)
        continue;
      bodies[i]->unhandled = false;

      // no back collisioning
      for (int j = 0; j < bodies.size(); j++)
      {
        if (i == j)
          continue;

        // check for future collision
        if (bodies[i]->Collides(bodies[j],
            bodies[i]->vx - bodies[j]->vx,
            bodies[i]->vy - bodies[j]->vy))
        {
          // apply the callbacks
          if (bodies[i]->callback)
            bodies[i]->callback(bodies[i], bodies[j]);
        }
      }
    }
  }

  // apply movement
  for (int i = 0; i < bodies.size(); i++)
  {
    // apply the movement
    bodies[i]->x += bodies[i]->vx;
    bodies[i]->y += bodies[i]->vy;

    // apply the friction
    bodies[i]->vx *= bodies[i]->friction;
    bodies[i]->vy *= bodies[i]->friction;
  }

  // call the update
  if (Current()->update != nullptr)
    Current()->update();
}

// draw current scene
void Scene::DrawCurrent()
{
  // all the objects
  auto objects = Current()->objects;
  auto& camera = Current()->camera;

  // sort by layer (REDO!)
  std::sort(objects.begin(), objects.end(),
  [](Object::Base* a, Object::Base* b) {
    return a->layer < b->layer;
  });

  // draw each object
  for (Object::Base* object : objects)
  {
    // if its a ui
    if (auto ui = dynamic_cast<UI::Base*>(object)) {
      if (ui->interact)
        ui->interact(ui);
      if (ui->renderer)
        ui->renderer(ui);
    }

    // draw non-relative to camera
    if (!object->relative) {
      Engine::Screen().Draw(
        object->image.get(),
        object->x, object->y,
        object->width, object->height);
      continue;
    }

    // camera transformation
    int newx = static_cast<int>(object->x * camera.scale)
      - static_cast<int>(camera.x * camera.scale);
    int newy = static_cast<int>(object->y * camera.scale)
      - static_cast<int>(camera.y * camera.scale);

    // draw relative to camera
    Engine::Screen().DrawEx(
      object->image.get(),
      newx + Engine::Width() / 2,
      newy + Engine::Height() / 2,
      object->width * camera.scale,
      object->height * camera.scale,
      object->angle);
  }

  // call the postprocess function
  if (Current()->postproc)
    Current()->postproc();
}

// camera transformations
int Scene::Camera::ToCameraX(int px)
  { return (px - Engine::Width() / 2) / scale + static_cast<int>(x); }
int Scene::Camera::ToCameraY(int py)
  { return (py - Engine::Height() / 2) / scale + static_cast<int>(y); }

// create body
void Scene::Bind(Body* body) {
  bodies.push_back(body);
}

// remove body by pointer
void Scene::Unbind(Body* body) {
  for (int i = 0; i < bodies.size(); i++) {
    if (bodies[i] == body) {
      bodies.erase(bodies.begin() + i);
      break;
    }
  }
}

// add object to the scene
void Scene::Add(Object::Base* object) {
  objects.push_back(object);
}