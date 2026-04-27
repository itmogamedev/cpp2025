//
// Created by Admin on 06.04.2026.
//
#include "circle.h"

sf::CircleShape addCircle() {
  //ограничение для рандома
  int windowWidth = win_w_stop;
  int windowHeight = win_h_stop;

  // создаём круг радиусом 100
  sf::CircleShape circle(static_cast<float>(radius));
  circle.setOutlineThickness(static_cast<float>(circle_count));
  circle.setOutlineColor(sf::Color::Red);
  //позиция центра круга
  circle.setOrigin(circle.getRadius(), circle.getRadius());
  float x = radius + (std::rand() % (windowWidth - 2 * radius));
  float y = radius + (std::rand() % (windowHeight - 2 * radius));
  circle.setPosition(x, y);

  return circle;
}

float getTimer(sf::Clock &clock, float totalTime) {
  float elapsed = clock.getElapsedTime().asSeconds();
  float remaining = totalTime - elapsed;
  if (remaining < time_over) remaining = time_over;

  return remaining;
}

void respawnCircle(std::vector<sf::CircleShape> &circles, int n, float &live) {
  circles[n] = addCircle();
  live = lives_new;
}

void circleAnimation(std::vector<sf::Clock> &c_l, std::vector<sf::CircleShape> &c, int n, float &live) {
  float dt = c_l[n].restart().asSeconds();
  live += dt;
  float factor = normal_size - live / lifeTime;
  if (factor < time_over) factor = time_over;
  c[n].setScale(factor, factor);
  if (factor == 0) { respawnCircle(c, n, live); }
}

bool circleClick(sf::Vector2f mousePos, std::vector<sf::CircleShape> &c, int n, float &live) {
  sf::Vector2f center = c[n].getPosition();
  float dx = mousePos.x - center.x;
  float dy = mousePos.y - center.y;

  if (dx * dx + dy * dy <= c[n].getRadius() * c[n].getRadius()) {
    std::cout << "click\n";
    c[n].setScale(0, 0);
    respawnCircle(c, n, live);
    counter++;
    return true;
  }
  return false;
}

int notMain()
{
  sf::Clock clock;
  std::vector<sf::CircleShape> circles;
  std::vector<sf::Clock> clock_live(circle_count);
  std::vector<float> lives(circle_count, 0.f);
  std::srand(static_cast<unsigned int>(std::time(nullptr)));


  //спавн кругов в начале
  for (int i = 0; i < circle_count; i++) {
    circles.push_back(addCircle());
  }


  //создание окошка
  sf::RenderWindow win(
    sf::VideoMode(sf::VideoMode(win_w, win_h)),
    L"Домашний осу");


  //загрузка иконки
  sf::Image icon;
  if (!icon.loadFromFile("C:/Users/Admin/Desktop/meow/cpp2sem/miniHw2/image/water.png")) {
    return 1;
  }
  win.setIcon(icon_size, icon_size, icon.getPixelsPtr());


  //загрузка шрифта
  sf::Font font;
  if (!font.loadFromFile("C:/Users/Admin/Desktop/meow/cpp2sem/miniHw2/image/Strogo-Regular.ttf")) {
    return 2;
  }


  //стиль таймера
  sf::Text text_time;
  text_time.setFont(font);
  text_time.setCharacterSize(text_size);
  text_time.setPosition(sf::Vector2f(text_x, text_timer_y));

  //стиль очков
  sf::Text text_point;
  text_point.setFont(font);
  text_point.setCharacterSize(text_size);
  text_point.setPosition(sf::Vector2f(text_x, text_points_y));

  //стиль конца игры
  sf::Text over;
  over.setFont(font);
  over.setCharacterSize(text_size_over);
  over.setPosition(sf::Vector2f(text_over_x, text_over_y));


  //lfml ивенты
  while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      //закрытие окошка при нажатии на крестик
      if (event.type == sf::Event::Closed) win.close();

      //реакция на клик мыши
      if (event.type == sf::Event::MouseButtonPressed && game) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        bool hit = false;

        //проверка, что клик попал в круг
        for (int i = 0; i < circles.size(); i++) {
          if (circleClick(mousePos, circles, i, lives[i])) {
            hit = true;
            break;
          }
        }

        if (!hit) {
          timer -= circle_count;
        }
      }
    }

    //анимация кругов
    if (game) {
      for (int i = 0; i < circles.size(); i++) {
        circleAnimation(clock_live, circles, i, lives[i]);
      }
    }


    // Обновляем таймер
    float remaining = getTimer(clock, timer);
    text_time.setString("Time left: " + std::to_string(static_cast<int>(remaining)));
    text_point.setString("Points: " + std::to_string(counter));
    over.setString("Time is up \n your points: " + std::to_string(counter));


    if (remaining <= 0) {
      game = false;
    }

    //рендер
    win.clear();
    if (game) {
      for (int j = 0; j < circle_count; j++) {
        win.draw(circles[j]);
      }

      win.draw(text_time);
      win.draw(text_point);
    } else { win.draw(over); }
    win.display();
  }

  return 0;
}