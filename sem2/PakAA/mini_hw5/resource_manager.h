#ifndef SPACE_SHOOTER_RESOURCE_MANAGER_H
#define SPACE_SHOOTER_RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// Singleton-кэш текстур. Нужен по двум причинам:
// 1) sf::Sprite хранит указатель на sf::Texture. Если бы текстура была
//    членом, например, Asteroid, то при росте std::vector<Asteroid>
//    объекты копировались/перемещались бы, а sprite указывал бы на мёртвую
//    память.
// 2) Незачем грузить одну и ту же текстуру повторно.
//
// std::map гарантирует, что указатели/ссылки на уже вставленные элементы
// остаются валидными при последующих вставках — нам это и нужно.
class ResourceManager {
 public:
  static ResourceManager& getInstance();
  sf::Texture& getTexture(const std::string& path);
  sf::Font& getFont();

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

 private:
  ResourceManager() = default;

  std::map<std::string, sf::Texture> texture_cache;
  sf::Font font;
  bool font_loaded = false;
};

#endif  // SPACE_SHOOTER_RESOURCE_MANAGER_H
