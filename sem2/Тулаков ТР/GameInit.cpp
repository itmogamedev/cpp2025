#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
int main()
{
    bool isPositionOccupied (int x,int y);
    srand(static_cast<unsigned int>(time(nullptr)));
    const int CELL_SIZE = 50;      // Размер одной клетки в пикселях (50x50)
    const int MAP_WIDTH = 10;       // Ширина карты в клетках
    const int MAP_HEIGHT = 10;      // Высота карты в клетках
    const int WINDOW_WIDTH = MAP_WIDTH * CELL_SIZE;   // 500 пикселей
    const int WINDOW_HEIGHT = MAP_HEIGHT * CELL_SIZE; // 500 пикселей
    const int MONSTER_COUNT = 4;
    std::vector<int> monsterX(MONSTER_COUNT);
    std::vector<int> monsterY(MONSTER_COUNT);
    std::vector<bool> monsterAlive(MONSTER_COUNT, true);
    int playerX = 2, playerY = 2;       // Игрок стартует в левом верхнем углу
    int treasureX, treasureY;   // Сокровище в правом нижнем
    do{
    treasureX = rand()% MAP_WIDTH;
    treasureY = rand()% MAP_HEIGHT;
    }while(treasureX == playerX && treasureY == playerY);
    for (int i = 0; i < MONSTER_COUNT; i++) {
 do{
    monsterX[i] = rand()% MAP_WIDTH;
    monsterY[i] = rand()% MAP_HEIGHT;
    }while((monsterX[i] == playerX && monsterY[i] == playerY) ||
             (monsterX[i] == treasureX && monsterY[i] == treasureY));
    }
    bool gameRunning = true;  // Игра активна?
    bool win = false;         // Победили?
    bool lose = false;        // Проиграли?
    //sf::Texture p_Texture;
    //p_Texture.create(sf::Vector2f(CELL_SIZE,CELL_SIZE));
    sf::RectangleShape p_Shape (sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    p_Shape.setFillColor(sf::Color::Green);
    // Квадрат для сокровища (золотой)
    sf::RectangleShape treasureShape(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    treasureShape.setFillColor(sf::Color::Yellow);
    // Квадрат для монстра (красный)
    sf::RectangleShape monsterShape(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    monsterShape.setFillColor(sf::Color::Black);
    // Квадрат для стены/пола (серый)
    sf::RectangleShape wallShape(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
    wallShape.setFillColor(sf::Color(100, 100, 100)); // Темно-серый
    /*int switch_move = 1;
    int x = 1;*/
    // create the window
    sf::RenderWindow window(sf::VideoMode({WINDOW_HEIGHT, WINDOW_WIDTH}), "Timur");
    //sf::CircleShape circle(50);
    //circle.setFillColor(sf::Color::Black);
    //circle.setPosition(sf::Vector2f(400, 300));
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>() || win == true || lose == true)
                window.close();
            if (event->is<sf::Event::KeyPressed>()) {
                
            
            int newY = playerY;
            int newX = playerX;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                newY--;
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                newY++;
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                newX--;
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                newX++;
            }
             if (newX >= 0 && newX < MAP_WIDTH && newY >=0 && newY < MAP_HEIGHT) {
                 playerX = newX;
                 playerY = newY;
                 if (playerX == treasureX && playerY == treasureY) {
                     win = true;
                     gameRunning = false;
                     std::cout<<"нашел сокровище";
                 }
                 for (int i = 0; i < MONSTER_COUNT; i++) {
                   if (monsterX[i] == playerX && monsterY[i] == playerY) {
                     lose = true;
                     gameRunning = false;
                     std::cout<<"Ты проиграл";
                 }
                 }
                 
            }

            }
        }
        //x += 1*switch_move;
        //if (x + 400 == 1920 or x + 400 == 0) {
        //    switch_move *= -1;
        //}
        // clear the window with black color
        window.clear(sf::Color::Red);
            //circle.setPosition(sf::Vector2f(400+x, 300));
        // draw everything here...
        // window.draw(...);
        //window.draw(circle);
        // end the current frame
        // Рисуем сокровище (ставим на свои координаты)
        // Рисуем пол (сетку)
        for (int i = 0; i < MAP_WIDTH; ++i)
        {
            for (int j = 0; j < MAP_HEIGHT; ++j)
            {
                // Вычисляем позицию в пикселях
                float x = i * CELL_SIZE;
                float y = j * CELL_SIZE;
                wallShape.setPosition(sf::Vector2f(x, y));
                window.draw(wallShape);
            }
        }
        treasureShape.setPosition(sf::Vector2f(treasureX * CELL_SIZE, treasureY * CELL_SIZE));
        window.draw(treasureShape);
        // Рисуем монстра
        for (int i = 0; i < MONSTER_COUNT; i++) {
             monsterShape.setPosition(sf::Vector2f(monsterX[i] * CELL_SIZE, monsterY[i] * CELL_SIZE));
              window.draw(monsterShape);
        }
        p_Shape.setPosition(sf::Vector2f(playerX * CELL_SIZE, playerY * CELL_SIZE));
        window.draw(p_Shape);
        window.display();
    }
}
bool isPositionOccupied(int x, int y) {
    return (x == playerX && y == playerY) ||
             (x == treasureX && y == treasureY);
    }