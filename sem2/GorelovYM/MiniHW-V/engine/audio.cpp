#include "audio.h"
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <filesystem>

// global stuff
static std::unordered_map<std::string, sf::Music*> sounds;
static float volume = 50;

// constructor
Audio::Audio(std::string name, std::string path)
{
  // load the sound
  sf::Music* music = new sf::Music();
  music->openFromFile(path);
  sounds[name] = music;
  sounds[name]->setVolume(volume);
}

void Audio::Play(std::string name)
{
  // play the sound
  sounds[name]->play();
}

void Audio::Stop(std::string name)
{
  // stop the sound
  sounds[name]->stop();
}

// set volume
void Audio::SetVolume(std::string name, int v) {
  sounds[name]->setVolume(v);
}

// get volume
int Audio::GetVolume(std::string name) {
  return sounds[name]->getVolume();
}

// check if the sound is playing
bool Audio::IsPlaying(std::string name)
{
  // check if the sound is playing
  return sounds[name]->getStatus() == sf::Music::Playing;
}