#pragma once
#include <string>
#include "define.h"
#include "image.h"

// class that drives the whole game
class Engine
{
  // friends
  friend int main();

  // properties
  private:
    
    // can produce static initialization
    // order fiasco without singleton
    singleton(std::string, Title);
    
    // window size
    static int   width;
    static int   height;
    static float scale;

    // render target
    static Image screen;

    // default font
    static Resources::Font* font;

    // callback in the beginning of main
    static void (*start)(void);

    // ticker stuff
    static double ticks;
    static double tickspeed;

  // public
  public:
    
    // constructor
    Engine(std::string title,
           int width,
           int height,
           int scale,
           void (*onstart)(void));

    // function to quit the game
    static void Quit(void);
    static void Delay(int time);

    // getters and refers
    static getter(Width,  width);
    static getter(Height, height);
    static getter(DefaultFont, font);
    static getter(Ticks, ticks);
    static getter(TickSpeed, tickspeed);
    static refer(Screen, screen);

    // setter to set the default font
    static setter(DefaultFont, font, value);
    static setter(TickSpeed, tickspeed, value);
};