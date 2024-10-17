#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "exprtk.hpp"  // Include exprtk header

namespace exprtk {
    template <typename T>
    class expression;

    template <typename T>
    class parser;

    template <typename T>
    class symbol_table;
}

class Calculator {
public:
    Calculator();
    void run();

private:
    void processEvents();
    void render();
    void initializeButtons();
    void updateDisplayText();
    void handleMousePress(const sf::Event& event);
    void handleMouseRelease(const sf::Event& event);
    void handleMouseMove(const sf::Event& event);
    void handleButtonPress(const std::string& buttonText);
    void calculateResult();
    void setButtonColor(sf::RectangleShape& button, const std::string& label);
    sf::Color getDefaultButtonColor(const std::string& label) const;
    void updateCursorBlink(float deltaTime);

    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape textBoxBackground;
    sf::Text displayText;
    sf::RectangleShape cursor; // Added for cursor
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::string inputExpression;

    // Added for cursor blinking
    float cursorBlinkTimer;
    bool cursorVisible;
    float cursorBlinkInterval;
};

#endif // CALCULATOR_HPP
