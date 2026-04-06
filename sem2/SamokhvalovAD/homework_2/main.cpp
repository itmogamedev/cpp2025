#include "main.h"
#include "circle.h"
// #include <thread>


void loop(sf::RenderWindow& window) {
    window.setFramerateLimit(60);
    std::vector<Circle*> circles;
    for (int i = 0; i < CIRCLE_COUNT; i++) {
        circles.push_back(new Circle());
    }
    while (window.isOpen())
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        for (Circle* circle : circles) {
            circle->move();
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        for (Circle* circle : circles) {
            window.draw(circle->getCircle());
        }
        window.display();
    }
}


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "OSU");
    loop(window);
    return 0;
}