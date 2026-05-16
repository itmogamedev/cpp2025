#include "typing_trainer.h"
#include <ctime>
#include <iostream>

TypingTrainer::TypingTrainer(int total_time)
    : window(sf::VideoMode({800, 600}), "Typing Trainer"),
    target_text(nullptr),
    info_text(nullptr),
    target_char(' '),
    score(0),
    time_limit(static_cast<float>(total_time)),
    remaining_time(static_cast<float>(total_time)),
    is_game_over(false) {

  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  initResouces();
  generateNewTarget();
}

//Очищаем память
TypingTrainer::~TypingTrainer() {
  delete target_text;
  delete info_text;
}

void TypingTrainer::initResouces() {
    //Загрузка шрифта
  if (!font.openFromFile("arial.ttf")) {
    std::cerr << "Could not load 'arial.ttf' " << std::endl;
  }
  // Создаем объекты ТЕПЕРЬ, когда шрифт точно загружен
  target_text = new sf::Text(font);
  target_text->setCharacterSize(150);
  target_text->setFillColor(sf::Color::Yellow);
  target_text->setPosition({350.f, 180.f});

  info_text = new sf::Text(font);
  info_text->setCharacterSize(25);
  info_text->setFillColor(sf::Color::White);
  info_text->setPosition({20.f, 20.f});
}

void TypingTrainer::generateNewTarget() {
  // Диапазон печатных символов в ASCII: от 33 ( без пробела) до 126 (~)
  target_char = static_cast<char>(std::rand() % 95 + 33);
  
  if (target_text) {
    target_text->setString(std::string(1, target_char));
  }
}

void TypingTrainer::handleInput(uint32_t unicode_symbol) {
  if (unicode_symbol <= 32 || unicode_symbol > 126) return; // Отсекаем служебные клафиши типа пробела
  char pressed = static_cast<char>(unicode_symbol);
  if (pressed == target_char) {
    score ++;
    generateNewTarget();
  }
  else {
    time_limit -= 1.0f; //Штраф времени за ошибку
  }
}

void TypingTrainer::update() {
  if (is_game_over) return;

  float elapsed = clock.getElapsedTime().asSeconds();
  //Отчитываем отсавшееся время
  remaining_time = time_limit - elapsed;

  if (remaining_time <= 0.f) {
    remaining_time = 0.f;
    is_game_over = true;
  }

  std::string info = "Score: " + std::to_string(score) + 
                     "\nTime: " + std::to_string(static_cast<int>(remaining_time)) + "s";
  
  if (is_game_over) {
    info += "\n\nGAME OVER!\nFinal Score: " + std::to_string(score);
  }

  if (info_text) {
    info_text->setString(info);
  }
}

void TypingTrainer::render() {
  window.clear(sf::Color(30, 30, 40));

  if (!is_game_over && target_text) {
    window.draw(*target_text); // Рисуем то, на что указывает указатель
  }
  
  if (info_text) {
    window.draw(*info_text);
  }

  window.display();
}

void TypingTrainer::run() {
  while (window.isOpen()) {
    while ( const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // Ловим ввод текста (символов)
      else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
        handleInput(textEntered->unicode);
      }
    }
    update();
    render();
  }
}