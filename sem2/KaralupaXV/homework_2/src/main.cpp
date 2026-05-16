#include <SFML/Graphics.hpp>
#include <vector>

#include "circle.h"
#include "game.h"

const int number_of_circles = 5;

Circle* newCircle() {
  Game* game = Game::getInstance();

  return new Circle(
      game->randrange(0, game->screen_width),
      game->randrange(0, game->screen_height), game->randrange(20, 50),
      Color::Blue, game->randrange(200, 300),
      Vec2<int>(game->randrange(0, 1) * 2 - 1, game->randrange(0, 1) * 2 - 1));
}

int main() {
  Game* game = Game::getInstance();

  const sf::Font font("C:/windows/fonts/arial.ttf");

  sf::Text timer_text(font, "");
  timer_text.setCharacterSize(30);
  timer_text.setPosition(sf::Vector2f(0, 0));

  sf::Text score_text(font, "");
  score_text.setCharacterSize(30);
  score_text.setPosition(sf::Vector2f(0, 30));

  std::vector<Object*> objects;

  for (int i = 0; i < number_of_circles; i++) {
    objects.push_back(newCircle());
  }

  sf::Clock clock;
  sf::Time delta = sf::Time::Zero;
  const sf::Time fps = sf::seconds(1.f / 60.f);

  while (game->window.isOpen()) {
    delta += clock.restart();
    while (delta > fps) {
      delta -= fps;

      // events
      while (const std::optional event = game->window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          game->window.close();
        }
        if (event->is<sf::Event::MouseButtonPressed>()) {
          if (event->getIf<sf::Event::MouseButtonPressed>()->button ==
              sf::Mouse::Button::Left) {
            Vec2<int> position =
                event->getIf<sf::Event::MouseButtonPressed>()->position;

            bool clicked_on_circle = false;
            for (int i = 0; i < objects.size(); i++) {
              Circle* object = static_cast<Circle*>(objects[i]);
              Vec2<int> object_position(object->x, object->y);
              if ((position - object_position).lengthSquared() <=
                  object->radius * object->radius) {
                clicked_on_circle = true;

                delete (static_cast<Circle*>(objects[i]));
                objects[i] = newCircle();

                game->score += 1;

                break;
              }
            }

            if (!clicked_on_circle) {
              game->timer -= 5;
            }
          }
        }
      }
      // events

      // update
      game->timer -= fps.asSeconds();

      if (game->timer > 0) {
        for (auto& it : objects) {
          it->update(fps.asSeconds());
        }
      }
      // update
    }

    // render
    game->window.clear();

    timer_text.setString(std::to_string(game->timer));
    score_text.setString(std::to_string(game->score));

    if (game->timer > 0) {
      for (auto& it : objects) {
        it->draw();
      }

      game->window.draw(timer_text);
      game->window.draw(score_text);
    } else {
      score_text.setPosition(
          sf::Vector2f(game->screen_width / 2, game->screen_height / 2));
      game->window.draw(score_text);
    }

    game->window.display();
    // render
  }
}
