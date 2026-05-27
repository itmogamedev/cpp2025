#pragma once
#include <string>

class Audio
{
  public:
    Audio(std::string name, std::string path);
    static void Play(std::string name);
    static bool IsPlaying(std::string name);
    static void Stop(std::string name);
    static void SetVolume(std::string name, int v);
    static int GetVolume(std::string name);
};