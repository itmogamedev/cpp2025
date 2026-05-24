#include "resource_manager.h"

#include <iostream>

ResourceManager& ResourceManager::getInstance() {
  static ResourceManager instance;
  return instance;
}

sf::Texture& ResourceManager::getTexture(const std::string& path) {
  auto it = texture_cache.find(path);
  if (it != texture_cache.end()) {
    return it->second;
  }
  sf::Texture& texture = texture_cache[path];
  if (!texture.loadFromFile(path)) {
    std::cerr << "[ResourceManager] Failed to load texture: " << path
              << std::endl;
  } else {
    texture.setSmooth(true);
  }
  return texture;
}

sf::Font& ResourceManager::getFont() {
  if (font_loaded) {
    return font;
  }
  // Пробуем несколько мест: пользовательский шрифт в assets,
  // потом системные шрифты Windows.
  const std::string candidates[] = {
      "assets/font.ttf",
      "C:/Windows/Fonts/arial.ttf",
      "C:/Windows/Fonts/segoeui.ttf",
      "C:/Windows/Fonts/tahoma.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
  };
  for (const std::string& path : candidates) {
    if (font.loadFromFile(path)) {
      font_loaded = true;
      break;
    }
  }
  if (!font_loaded) {
    std::cerr << "[ResourceManager] No font could be loaded. UI text will be"
                 " invisible. Place a .ttf file at assets/font.ttf."
              << std::endl;
  }
  return font;
}
