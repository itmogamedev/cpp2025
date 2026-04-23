#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const float game_time = 10;  
const float mistake_time = 2;

char getRandomChar() { return char(33 + rand() % (126 - 33 + 1)); }

void game() {
  
  sf::RenderWindow window(sf::VideoMode(800, 600), "SKOROPECHATALKA");
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) {
    std::cerr << "Ошибка: не найден файл шрифта arial.ttf.\n";
    return;
  }

  int score = 0;
  float time_left = game_time;
  char current_char = getRandomChar();
  bool game_over = false;

  sf::Clock clock;

  sf::Text character_text;
  character_text.setFont(font);
  character_text.setCharacterSize(120);
  character_text.setFillColor(sf::Color::White);
  character_text.setString(std::string(1, current_char));

  sf::FloatRect bounds = character_text.getLocalBounds();
  character_text.setOrigin(bounds.left + bounds.width / 2,
                     bounds.top + bounds.height / 2);
  character_text.setPosition(window.getSize().x / 2., window.getSize().y / 2.);

  sf::Text score_text;
  score_text.setFont(font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::Green);
  score_text.setPosition(20, 20);

  sf::Text timer_text;
  timer_text.setFont(font);
  timer_text.setCharacterSize(30);
  timer_text.setFillColor(sf::Color::White);
  timer_text.setPosition(window.getSize().x - 150, 20);

  sf::Text gamover_text;
  gamover_text.setFont(font);
  gamover_text.setCharacterSize(50);
  gamover_text.setFillColor(sf::Color::Red);
  gamover_text.setString("   GAME OVER\nPress R to restart");
  sf::FloatRect go_text_bounds = gamover_text.getLocalBounds();
  gamover_text.setOrigin(go_text_bounds.left + go_text_bounds.width / 2,
                         go_text_bounds.top + go_text_bounds.height / 2);
  gamover_text.setPosition(window.getSize().x / 2.,
                           window.getSize().y / 2. - 40);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::TextEntered && !game_over) {
        sf::Uint32 unicode = event.text.unicode;

        if (unicode < 32 || unicode == 127) continue; //до 32 и 127 это короче не особо символы

        if (unicode < 128) { //это чтобы только ascii
          char player_input_char = char(unicode);

          if (player_input_char == current_char) {
            score++;
            current_char = getRandomChar();
            character_text.setString(std::string(1, current_char));

            sf::FloatRect char_text_bounds = character_text.getLocalBounds();
            character_text.setOrigin(char_text_bounds.left + char_text_bounds.width / 2,
                               char_text_bounds.top + char_text_bounds.height / 2);
            character_text.setPosition(window.getSize().x / 2.,
                                 window.getSize().y / 2.);
          } else {
            time_left -= mistake_time;
            if (time_left < 0.0f) time_left = 0.0f;
          }
        }
      }

      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::R && game_over) {
        game_over = false;
        score = 0;
        time_left = game_time;
        current_char = getRandomChar();
        character_text.setString(std::string(1, current_char));

        sf::FloatRect char_text_bounds = character_text.getLocalBounds();
        character_text.setOrigin(char_text_bounds.left + char_text_bounds.width / 2,
                           char_text_bounds.top + char_text_bounds.height / 2);
        character_text.setPosition(window.getSize().x / 2.,
                             window.getSize().y / 2.);

        clock.restart();
      }
    }

    if (!game_over) {
      float dt = clock.restart().asSeconds();
      time_left -= dt;
      if (time_left <= 0) {
        time_left = 0;
        game_over = true;
      }
    }

    score_text.setString("Score: " + std::to_string(score));

    int sec = int(time_left);
    int ms = int((time_left - sec) * 100);
    timer_text.setString("Time: " + std::to_string(sec) + "." +
                        (ms < 10 ? "0" : "") + std::to_string(ms));

    window.clear(sf::Color::Black);

    if (!game_over) {
      window.draw(character_text);
    } else {
      window.draw(gamover_text);
      sf::Text final_score;
      final_score.setFont(font);
      final_score.setCharacterSize(40);
      final_score.setFillColor(sf::Color::Green);
      final_score.setString("Final Score: " + std::to_string(score));
      sf::FloatRect final_score_text_bounds = final_score.getLocalBounds();
      final_score.setOrigin(final_score_text_bounds.left + final_score_text_bounds.width / 2,
                           final_score_text_bounds.top + final_score_text_bounds.height / 2);
      final_score.setPosition(window.getSize().x / 2.,
                             window.getSize().y / 2. + 40);
      window.draw(final_score);
    }

    window.draw(score_text);
    window.draw(timer_text);
    window.display();
  }
}

int main() {
  std::srand(time(NULL));
  game();
}