#include "game.h"

#include <chrono>
#include <random>
#include <string>

game::game() {
  firstCardIndex = -1;
  secondCardIndex = -1;
  isWaitingDelay = false;
  consecutiveMistakes = 0;
  totalMoves = 0;
  pairsFound = 0;
  isGameWon = false;

  gameFont.loadFromFile("font.ttf");

  statusText.setFont(gameFont);
  statusText.setCharacterSize(24);
  statusText.setFillColor(sf::Color::White);
  statusText.setPosition(20.f, 480.f);

  std::vector<char> initialSymbols = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D',
                                      'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H'};

  for (int cardCounter = 0; cardCounter < 16; ++cardCounter) {
    int randomIndex = randNum(0, static_cast<int>(initialSymbols.size()) - 1);

    char chosenSymbol = initialSymbols[randomIndex];

    initialSymbols.erase(initialSymbols.begin() + randomIndex);

    float positionX = 15.f + (cardCounter % 4) * 115.f;
    float positionY = 15.f + (cardCounter / 4) * 115.f;
    gameCards.emplace_back(chosenSymbol, 100.f,
                           sf::Vector2f(positionX, positionY));
  }
}

  int game::randNum(int minVal, int maxVal) {
    std::random_device randomDevice;
    std::mt19937 generatorEngine(randomDevice());
    std::uniform_int_distribution<int> integerDistribution(minVal, maxVal);

    int generatedResult = integerDistribution(generatorEngine);
    return generatedResult;
  }

void game::shuffleHiddenCards() {
    std::vector<char> hiddenSymbols;

    for (const auto& currentCard : gameCards) {
      if (!currentCard.isOpened and !currentCard.isSolved) {
        hiddenSymbols.push_back(currentCard.cardSymbol);
      }
    }

    for (auto& currentCard : gameCards) {
      if (!currentCard.isOpened and !currentCard.isSolved) {
        int randomIndex = randNum(0, static_cast<int>(hiddenSymbols.size()) - 1);
        currentCard.cardSymbol = hiddenSymbols[randomIndex];
        hiddenSymbols.erase(hiddenSymbols.begin() + randomIndex);
      }
    }
  }

void game::handleMouseClick(sf::Vector2i mousePosition) {
  if (isWaitingDelay or isGameWon) return;

  for (int cardIndex = 0; cardIndex < 16; ++cardIndex) {
    if (!gameCards[cardIndex].isOpened and !gameCards[cardIndex].isSolved and
        gameCards[cardIndex].checkClick(mousePosition)) {
      if (firstCardIndex == -1) {
        firstCardIndex = cardIndex;
        gameCards[firstCardIndex].isOpened = true;
      } else if (secondCardIndex == -1 and cardIndex != firstCardIndex) {
        secondCardIndex = cardIndex;
        gameCards[secondCardIndex].isOpened = true;
        isWaitingDelay = true;
        delayClock.restart();
        totalMoves++;
      }
      break;
    }
  }
}

void game::updateLogic() {
  if (isWaitingDelay and delayClock.getElapsedTime().asSeconds() >= 1.0f) {
    if (gameCards[firstCardIndex].cardSymbol ==
        gameCards[secondCardIndex].cardSymbol) {
      gameCards[firstCardIndex].isSolved = true;
      gameCards[secondCardIndex].isSolved = true;
      consecutiveMistakes = 0;
      pairsFound++;
      if (pairsFound == 8) {
        isGameWon = true;
      }
    } else {
      gameCards[firstCardIndex].isOpened = false;
      gameCards[secondCardIndex].isOpened = false;
      consecutiveMistakes++;

      if (consecutiveMistakes == 2) {
        shuffleHiddenCards();
        consecutiveMistakes = 0;
      }
    }
    firstCardIndex = -1;
    secondCardIndex = -1;
    isWaitingDelay = false;
  }

  if (isGameWon) {
    statusText.setString("Win! Total moves: " + std::to_string(totalMoves));
  } else {
    statusText.setString("Moves: " + std::to_string(totalMoves) +
                         " | Mistakes: " + std::to_string(consecutiveMistakes));
  }
}

void game::renderGame(sf::RenderWindow& appWindow) {
  for (auto& currentCard : gameCards) {
    if (currentCard.isSolved) continue;

    if (currentCard.isOpened) {
      currentCard.cardShape.setFillColor(sf::Color(200, 200, 200));
      appWindow.draw(currentCard.cardShape);

      sf::Text textElement;
      textElement.setFont(gameFont);
      textElement.setString(currentCard.cardSymbol);
      textElement.setCharacterSize(40);
      textElement.setFillColor(sf::Color::Black);

      sf::FloatRect textRectangle = textElement.getLocalBounds();
      textElement.setOrigin(textRectangle.left + textRectangle.width / 2.0f,
                            textRectangle.top + textRectangle.height / 2.0f);
      sf::Vector2f cardPosition = currentCard.cardShape.getPosition();
      textElement.setPosition(cardPosition.x + 50.f, cardPosition.y + 50.f);

      appWindow.draw(textElement);
    } else {
      currentCard.cardShape.setFillColor(sf::Color(70, 130, 180));
      appWindow.draw(currentCard.cardShape);
    }
  }
  appWindow.draw(statusText);
}
