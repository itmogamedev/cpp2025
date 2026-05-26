#include "GameBoard.h"

#include <algorithm>
#include <random>

#include "Constants.h"

GameBoard::GameBoard() : pairsFound(0), consecutiveErrors(0) {
  for (int i = 0; i < TOTAL_PAIRS; ++i) {
    symbols.push_back(i);
    symbols.push_back(i);
  }

  bool fontOk = font.openFromFile("C:/Windows/Fonts/arial.ttf");
  if (!fontOk) {
    fontOk = font.openFromFile("arial.ttf");
  }

  loadTextures();
  initCards();
}

bool GameBoard::loadTextures() {
  std::string iconFiles[] = {"assets/icon_0.png", "assets/icon_1.png",
                             "assets/icon_2.png", "assets/icon_3.png",
                             "assets/icon_4.png", "assets/icon_5.png",
                             "assets/icon_6.png", "assets/icon_7.png"};

  for (int i = 0; i < TOTAL_PAIRS; ++i) {
    auto tex = std::make_shared<sf::Texture>();
    bool iconLoaded = tex->loadFromFile(iconFiles[i]);
    if (iconLoaded) {
      iconTextures[i] = tex;
    } else {
      sf::Image image;
      image.resize(sf::Vector2u(TEXTURE_SIZE, TEXTURE_SIZE));
      sf::Color color(50 + i * 25, 100, 200);
      for (unsigned int y = 0; y < TEXTURE_SIZE; ++y)
        for (unsigned int x = 0; x < TEXTURE_SIZE; ++x)
          image.setPixel(sf::Vector2u(x, y), color);
      bool imgLoaded = tex->loadFromImage(image);
      iconTextures[i] = tex;
    }
  }

  auto coverTex = std::make_shared<sf::Texture>();
  bool coverLoaded = coverTex->loadFromFile("assets/cover.png");
  if (!coverLoaded) {
    sf::Image coverImage;
    coverImage.resize(sf::Vector2u(TEXTURE_SIZE, TEXTURE_SIZE));
    for (unsigned int y = 0; y < TEXTURE_SIZE; ++y)
      for (unsigned int x = 0; x < TEXTURE_SIZE; ++x)
        coverImage.setPixel(
            sf::Vector2u(x, y),
            sf::Color(COLOR_COVER_R, COLOR_COVER_G, COLOR_COVER_B));
    bool imgLoaded = coverTex->loadFromImage(coverImage);
  }
  coverTexture = coverTex;

  return true;
}

void GameBoard::initCards() {
  std::shuffle(symbols.begin(), symbols.end(),
               std::mt19937(std::random_device()()));
  cards.clear();

  int totalWidth = GRID_SIZE * CARD_SIZE + (GRID_SIZE - 1) * GAP;
  int totalHeight = GRID_SIZE * CARD_SIZE + (GRID_SIZE - 1) * GAP;
  float offsetX = static_cast<float>(WINDOW_WIDTH - totalWidth) / 2.0f;
  float offsetY = static_cast<float>(WINDOW_HEIGHT - totalHeight) / 2.0f +
                  static_cast<float>(GRID_Y_OFFSET);

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      sf::Vector2f position(
          offsetX + static_cast<float>(j * (CARD_SIZE + GAP)),
          offsetY + static_cast<float>(i * (CARD_SIZE + GAP)));
      int symbol = symbols[i * GRID_SIZE + j];
      cards.emplace_back(position, symbol, *coverTexture,
                         *iconTextures[symbol]);
    }
  }
}

int GameBoard::handleClick(sf::Vector2i mousePos) {
  for (int i = 0; i < TOTAL_CARDS; ++i) {
    if (cards[i].getState() == CardState::Hidden &&
        cards[i].contains(mousePos)) {
      cards[i].reveal();
      return i;
    }
  }
  return -1;
}

bool GameBoard::checkMatch(int firstCard, int secondCard) {
  if (cards[firstCard].getSymbolIndex() == cards[secondCard].getSymbolIndex()) {
    cards[firstCard].match();
    cards[secondCard].match();
    pairsFound++;
    consecutiveErrors = 0;
    return true;
  }
  consecutiveErrors++;
  cards[firstCard].hide();
  cards[secondCard].hide();
  if (consecutiveErrors >= MAX_ERRORS_BEFORE_SHUFFLE) {
    shuffleHiddenCards();
    consecutiveErrors = 0;
  }
  return false;
}

void GameBoard::shuffleHiddenCards() {
  std::vector<int> hiddenIndices;
  std::vector<int> currentSymbols;

  for (int i = 0; i < TOTAL_CARDS; ++i) {
    if (cards[i].getState() == CardState::Hidden && !cards[i].getWasSeen()) {
      hiddenIndices.push_back(i);
      currentSymbols.push_back(cards[i].getSymbolIndex());
    }
  }

  if (hiddenIndices.size() < 2) return;

  std::shuffle(currentSymbols.begin(), currentSymbols.end(),
               std::mt19937(std::random_device()()));

  for (size_t k = 0; k < hiddenIndices.size(); ++k) {
    int cardIndex = hiddenIndices[k];
    int newSymbol = currentSymbols[k];
    cards[cardIndex].setSymbol(newSymbol, *iconTextures[newSymbol]);
  }
}

int GameBoard::getPairsFound() const { return pairsFound; }
bool GameBoard::isGameWon() const { return pairsFound == TOTAL_PAIRS; }

void GameBoard::drawBackground(sf::RenderWindow& window) const {
  sf::RectangleShape star(sf::Vector2f(STAR_SIZE, STAR_SIZE));
  star.setFillColor(sf::Color(COLOR_STAR, COLOR_STAR, COLOR_STAR));
  std::mt19937 rng(42);
  std::uniform_real_distribution<float> xDist(0.0f, WINDOW_WIDTH);
  std::uniform_real_distribution<float> yDist(0.0f, WINDOW_HEIGHT);
  for (int i = 0; i < STAR_COUNT; ++i) {
    star.setPosition({xDist(rng), yDist(rng)});
    window.draw(star);
  }
  sf::Text title(font, "Memory", TITLE_SIZE);
  title.setFillColor(sf::Color(COLOR_GOLD_R, COLOR_GOLD_G, COLOR_GOLD_B));
  sf::FloatRect titleBounds = title.getLocalBounds();
  title.setPosition({(WINDOW_WIDTH - titleBounds.size.x) / 2.0f, TITLE_Y});
  window.draw(title);
  sf::RectangleShape line(sf::Vector2f(LINE_WIDTH, LINE_THICKNESS));
  line.setPosition({LINE_X, LINE_Y});
  line.setFillColor(sf::Color(COLOR_GOLD_R, COLOR_GOLD_G, COLOR_GOLD_B));
  window.draw(line);
}

void GameBoard::draw(sf::RenderWindow& window) const {
  for (const auto& card : cards) card.draw(window);
}
