#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Card.h"

class Game {
public:
	Game();
	void run();

private:
	void initGame(); //сброс параметров и начальная раскладка 
	void handleInput(); //обработка нажатия
	void update();
	void render(); //отрисовка графики
	void shuffleRemaining(); //перемешивание карт

	sf::RenderWindow window;
	std::vector<Card> cards; //массив из карт
	sf::Font font;

	int first_selected_idx; //первая выбранная карта
	int second_selected_idx; //вторая выбранная карта
	int moves_count;
	int consecutive_mistakes;
	int matched_pairs;

	bool is_waiting_for_delay;
	sf::Clock delay_clock; //время задержки
	bool is_game_over;

	bool is_showing_shuffle_msg;
	sf::Clock shuffle_msg_clock;
};