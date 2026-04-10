#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

const float INITIAL_TIME = 30.0f;
const float PENALTY_TIME = 2.0f;
const int SCORE_PER_HIT = 1;
const int MIN_PRINTABLE = 97;
const int MAX_PRINTABLE = 122;

// Forward declarations
void centerText(sf::Text& text);
void updateTargetChar(sf::Text& targetCharText, char& currentChar);
void updateScoreText(sf::Text& scoreText, int score);
void updateTimerText(sf::Text& timerText, float remainingTime);
void handleTextInput(const sf::Event& event, bool isGameActive, char& currentChar, 
                     int& score, float& remainingTime, sf::Text& scoreText, 
                     sf::Text& timerText, sf::Text& targetCharText, 
                     std::mt19937& gen, std::uniform_int_distribution<int>& dist);
void updateGameTimer(float deltaTime, float& remainingTime, bool& isGameActive, 
                     int score, sf::Text& finalScoreText, sf::Text& gameOverText);

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Typing Monkey");
    window.setFramerateLimit(60u);

    // Load font
    sf::Font font;
    if(!font.openFromFile("Cascadia_Mono.ttc")) {
        std::cout << "failed to open font\n";
        return -1;
    }

    // Initialize UI elements
    sf::Text targetCharText(font), scoreText(font), timerText(font);
    sf::Text gameOverText(font), finalScoreText(font);
    
    targetCharText.setCharacterSize(200u);
    targetCharText.setFillColor(sf::Color::White);
    targetCharText.setStyle(sf::Text::Bold);
    
    scoreText.setCharacterSize(36u);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({20.0f, 20.0f});
    
    timerText.setCharacterSize(36u);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({window.getSize().x - 150.0f, 20.0f});
    
    gameOverText.setCharacterSize(48u);
    gameOverText.setStyle(sf::Text::Bold);
    
    finalScoreText.setCharacterSize(36u);
    finalScoreText.setFillColor(sf::Color::White);

    // Center text elements
    centerText(targetCharText);
    centerText(gameOverText);
    centerText(finalScoreText);
    
    gameOverText.setPosition({window.getSize().x / 2.0f - 130.0f, window.getSize().y / 2.0f - 100.0f});
    finalScoreText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f + 20.0f});
    targetCharText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

    // Initialize random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(MIN_PRINTABLE, MAX_PRINTABLE);

    // Game state variables
    int score = 0;
    float remainingTime = INITIAL_TIME;
    bool isGameActive = true;
    char currentChar = static_cast<char>(dist(gen));

    // Initial UI updates
    updateTargetChar(targetCharText, currentChar);
    updateScoreText(scoreText, score);
    updateTimerText(timerText, remainingTime);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    // Main game loop
    while (window.isOpen()) {
        // Event handling
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            handleTextInput(*event, isGameActive, currentChar, score, remainingTime,
                           scoreText, timerText, targetCharText, gen, dist);
        }

        // Time update
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (isGameActive) {
            updateGameTimer(deltaTime, remainingTime, isGameActive, score, 
                           finalScoreText, gameOverText);
            updateTimerText(timerText, remainingTime);
        }

        // Rendering
        window.clear(sf::Color::Black);
        if (isGameActive) {
            window.draw(targetCharText);
            window.draw(scoreText);
            window.draw(timerText);
        } else {
            window.draw(gameOverText);
            window.draw(finalScoreText);
        }
        window.display();
    }

    return 0;
}

// Helper function implementations
void centerText(sf::Text& text) {
    sf::FloatRect bounds = text.getGlobalBounds();
    text.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
}

void updateTargetChar(sf::Text& targetCharText, char& currentChar) {
    targetCharText.setString(std::string(1, currentChar));
    centerText(targetCharText);
}

void updateScoreText(sf::Text& scoreText, int score) {
    scoreText.setString("Score: " + std::to_string(score));
}

void updateTimerText(sf::Text& timerText, float remainingTime) {
    std::ostringstream ss;
    ss << "Time: " << std::fixed << std::setprecision(1) << remainingTime;
    timerText.setString(ss.str());
}

void handleTextInput(const sf::Event& event, bool isGameActive, char& currentChar, 
                     int& score, float& remainingTime, sf::Text& scoreText, 
                     sf::Text& timerText, sf::Text& targetCharText, 
                     std::mt19937& gen, std::uniform_int_distribution<int>& dist) {
    if (!isGameActive) return;
    
    if (const auto* textEvent = event.getIf<sf::Event::TextEntered>()) {
        uint32_t codepoint = textEvent->unicode;
        if (codepoint >= MIN_PRINTABLE && codepoint <= MAX_PRINTABLE) {
            char enteredChar = static_cast<char>(codepoint);
            if (enteredChar == currentChar) {
                score += SCORE_PER_HIT;
                updateScoreText(scoreText, score);
                currentChar = static_cast<char>(dist(gen));
                updateTargetChar(targetCharText, currentChar);
            } else {
                remainingTime -= PENALTY_TIME;
                if (remainingTime < 0) remainingTime = 0;
                updateTimerText(timerText, remainingTime);
            }
        }
    }
}

void updateGameTimer(float deltaTime, float& remainingTime, bool& isGameActive, 
                     int score, sf::Text& finalScoreText, sf::Text& gameOverText) {
    remainingTime -= deltaTime;
    if (remainingTime <= 0) {
        remainingTime = 0;
        isGameActive = false;
        finalScoreText.setString("Final score: " + std::to_string(score));
        centerText(finalScoreText);
        
        if (score > 20) {
            gameOverText.setString("GREAT JOB!");
            gameOverText.setFillColor(sf::Color::Green);
        } else {
            gameOverText.setString("TRY AGAIN");
            gameOverText.setFillColor(sf::Color::Red);
        }
    }
}
