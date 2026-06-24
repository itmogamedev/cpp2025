#pragma once

#include <SFML/Graphics.hpp>

// Состояние карточки на игровом поле.
enum class CardState {
  kHidden,   // рубашкой вверх, символ не виден
  kRevealed,  // открыта, символ виден
  kMatched   // пара найдена, карточка исчезла
};

// Одна прямоугольная карточка поля 4x4.
class Card {
 public:
  Card();

  void setSymbol(int symbol);
  int getSymbol() const;

  void setState(CardState state);
  CardState getState() const;

  // Задаёт прямоугольную область карточки на экране.
  void setBounds(float x, float y, float size);

  // Проверяет, попадает ли точка (по клику мыши) в карточку.
  bool contains(float x, float y) const;

  // Рисует карточку: рубашку, лицевую сторону или ничего (если найдена пара).
  void draw(sf::RenderWindow& window, const sf::Texture& back_texture,
            const sf::Texture& face_texture) const;

 private:
  int symbol;
  CardState state;
  sf::FloatRect bounds;
};
