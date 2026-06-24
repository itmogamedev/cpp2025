#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "define.h"
#include "object.h"
#include "body.h"

// macros for shorten declaration
#define DeclScene(name) \
  static void Init(void); \
  static void Update(void); \
  static void Destroy(void); \
  static Scene scene(#name, Init, Update, Destroy)

// class for managing scenes
class Scene
{
  // friends
  friend int main();

  // properties
  private:
    
    // scene members and current scene (initialization order)
    using SceneMap = std::unordered_map<std::string, Scene*>;
    singleton(SceneMap, Members);
    singleton(Scene*, Current);

    // callbacks
    void (*init)(void);
    void (*update)(void);
    void (*destroy)(void);

    // postprocess function
    void (*postproc)(void);

    // physics unrealistic :) bodies
    std::vector<Body*> bodies;

    // a lot of black objects
    std::vector<Object::Base*> objects;
    
    // around one white camera on sofa
    struct Camera
    {
      // parameters
      float x;
      float y;
      float scale;
      float angle;

      // coord converters
      int ToCameraX(int x);
      int ToCameraY(int y);
    } camera;

  // public
  public:

    // constructor
    Scene(std::string name,
          void (*init)(void),
          void (*update)(void),
          void (*destroy)(void));

    // destructor
    ~Scene(void);

    // getters and refers
    refer(Camera, camera);

    // physics binders
    void Bind(Body* body);
    void Unbind(Body* body);

    // ugly function for creating objects
    template <class T, typename... Args>
    T* Create(Args&&... args) {
      T* object = new T(std::forward<Args>(args)...);
      objects.push_back(object);
      return object;
    }

    // function to add a object to the scene
    void Add(Object::Base* object);

    // remove object by pointer or by tag
    void Remove(Object::Base* object);
    void Remove(std::string tag);

    // find object by tag
    std::vector<Object::Base*> Find(std::string tag);

    // change the scene
    static void Switch(std::string name);

    // set postprocess function
    setter(Postproc, postproc, value);

  // private stuff
  private:
    static void InitAll(void);
    static void UpdateCurrent(void);
    static void DrawCurrent(void);
};