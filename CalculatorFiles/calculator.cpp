#include "calculator.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>

// Define button colors
const sf::Color darkGreyDefault = sf::Color{ 51, 51, 51 };
const sf::Color darkGreyHighlighted = sf::Color{ 115, 115, 115 };
const sf::Color darkGreyPressed = sf::Color{ 80, 80, 80 };
const sf::Color lightGreyDefault = sf::Color{ 165, 165, 165 };
const sf::Color lightGreyHighlighted = sf::Color{ 217, 217, 217 };
const sf::Color lightGreyPressed = sf::Color{ 190, 190, 190 };
const sf::Color orangeDefault = sf::Color{ 240, 154, 55 };
const sf::Color orangeHighlighted = sf::Color{ 243, 201, 149 };
const sf::Color orangePressed = sf::Color{ 240, 180, 120 };
const sf::Color textBoxBackgroundColor = sf::Color(80, 80, 80);

Calculator::Calculator() : window(sf::VideoMode(1720, 969), "Scientific Calculator"), cursorBlinkTimer(0), cursorVisible(true) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    // Setup display text box background
    textBoxBackground.setSize(sf::Vector2f(1700, 200)); // Increase text box height
    textBoxBackground.setFillColor(textBoxBackgroundColor);
    textBoxBackground.setPosition(10, 10);

    displayText.setFont(font);
    displayText.setString("");
    displayText.setCharacterSize(64); // Increase font size
    displayText.setFillColor(sf::Color::White);
    displayText.setPosition(textBoxBackground.getPosition().x + 10, textBoxBackground.getPosition().y + 10);

    // Setup cursor
    cursor.setSize(sf::Vector2f(4, displayText.getCharacterSize() * 1.2f)); // Adjust size
    cursor.setFillColor(sf::Color::White);
    cursorBlinkInterval = 0.5f; // 0.5 second blink interval

    // Initialize buttons
    initializeButtons();
}

void Calculator::initializeButtons() {
    std::vector<std::string> buttonLabels = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "(", "0", ")", "+",
        "sin" , "=" , "AC", "cos", "tan",
        "log", "ln", "sqrt"
    };

    const float buttonWidth = 415; // Adjust button width to fill the gaps
    const float buttonHeight = 115; // Adjust button height
    const float spacing = 15;
    const float startX = 6; // Shift buttons to the left by reducing startX
    const float startY = 220;

    for (int i = 0; i < buttonLabels.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        float x = startX + (i % 4) * (buttonWidth + spacing); // Adjust layout to 4 columns
        float y = startY + (i / 4) * (buttonHeight + spacing);
        button.setPosition(x, y);

        setButtonColor(button, buttonLabels[i]);
        buttons.push_back(button);

        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(buttonLabels[i]);
        buttonText.setCharacterSize(32); // Keep character size
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(button.getPosition().x + (buttonWidth - buttonText.getLocalBounds().width) / 2,
            button.getPosition().y + (buttonHeight - buttonText.getLocalBounds().height) / 2 - 10);
        buttonTexts.push_back(buttonText);
    }
}

void Calculator::setButtonColor(sf::RectangleShape& button, const std::string& label) {
    if (label == "=" || label == "AC") {
        button.setFillColor(orangeDefault);
    }
    else if (label == "/" || label == "*" || label == "-" || label == "+" || label == "sin" || label == "cos" || label == "tan" || label == "log" || label == "ln" || label == "sqrt" || label == "exp" || label == "^") {
        button.setFillColor(lightGreyDefault);
    }
    else {
        button.setFillColor(darkGreyDefault);
    }
}

void Calculator::updateDisplayText() {
    displayText.setString(inputExpression);

    sf::FloatRect textBounds = displayText.getLocalBounds();
    float textWidth = textBounds.width;
    float textHeight = textBounds.height;

    float backgroundWidth = textBoxBackground.getSize().x;
    float backgroundHeight = textBoxBackground.getSize().y;

    // Center the text within the text box
    float textX = textBoxBackground.getPosition().x + (backgroundWidth - textWidth) / 2;
    float textY = textBoxBackground.getPosition().y + (backgroundHeight - textHeight) / 2;

    displayText.setPosition(textX, textY);

    // Set cursor position to the start of the text
    cursor.setPosition(textX + textWidth, textY+5);  // Adjust cursor position to align with text

    // Reset cursor blink timer to make the cursor visible immediately
    cursorBlinkTimer = 0;
}



void Calculator::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        updateCursorBlink(deltaTime.asSeconds());
        render();
    }
}

void Calculator::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            handleMousePress(event);
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            handleMouseRelease(event);
        }
        else if (event.type == sf::Event::MouseMoved) {
            handleMouseMove(event);
        }
    }
}

void Calculator::handleMousePress(const sf::Event& event) {
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            handleButtonPress(buttonTexts[i].getString());
            buttons[i].setFillColor(darkGreyPressed);
        }
    }
}

void Calculator::handleMouseRelease(const sf::Event& event) {
    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i].setFillColor(getDefaultButtonColor(buttonTexts[i].getString()));
    }
}

void Calculator::handleMouseMove(const sf::Event& event) {
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            buttons[i].setFillColor(darkGreyHighlighted);
        }
        else {
            buttons[i].setFillColor(getDefaultButtonColor(buttonTexts[i].getString()));
        }
    }
}

void Calculator::render() {
    window.clear();

    // Draw the text box background
    window.draw(textBoxBackground);

    // Draw the cursor first (so it appears behind the text)
    if (cursorVisible) {
        window.draw(cursor);
    }

    // Draw the display text
    window.draw(displayText);

    // Draw all the buttons
    for (int i = 0; i < buttons.size(); ++i) {
        window.draw(buttons[i]);
        window.draw(buttonTexts[i]);
    }

    window.display();
}

void Calculator::handleButtonPress(const std::string& buttonText) {
    if (buttonText == "AC") {
        inputExpression.clear();
    }
    else if (buttonText == "=") {
        calculateResult();
    }
    else {
        inputExpression += buttonText;
    }

    updateDisplayText(); // Ensure cursor is updated with text changes
}

void Calculator::calculateResult() {
    using namespace exprtk;

    typedef double T;

    // Define the expression type
    expression<T> expression;
    parser<T> parser;
    symbol_table<T> symbol_table;

    // Function to convert degrees to radians
    auto deg_to_rad = [](T degrees) -> T {
        return degrees * 3.14159265358979323846 / 180.0;
        };

    // Register the conversion function in the symbol table
    symbol_table.add_function("deg_to_rad", deg_to_rad);

    // Register the natural logarithm function (ln)
    symbol_table.add_function("ln", [](T x) -> T {
        return std::log(x);
        });

    // Register the base 10 logarithm function (log10)
    symbol_table.add_function("log10", [](T x) -> T {
        return std::log10(x);
        });

    // Add the symbol table to the expression
    expression.register_symbol_table(symbol_table);

    // Process the input expression to handle trig functions and logs
    std::string processedExpression = inputExpression;
    std::string trigFunctions[] = { "cos", "sin", "tan" };
    for (const auto& func : trigFunctions) {
        size_t pos = 0;
        while ((pos = processedExpression.find(func + "(", pos)) != std::string::npos) {
            processedExpression.replace(pos, func.length() + 1, func + "(deg_to_rad(");
            size_t closeParen = processedExpression.find(')', pos);
            if (closeParen != std::string::npos) {
                processedExpression.insert(closeParen + 1, ")");
            }
            pos += func.length() + 14; // Adjust position to avoid infinite loop
        }
    }

    // Ensure ln and log10 are correctly interpreted
    size_t pos = 0;
    while ((pos = processedExpression.find("ln(", pos)) != std::string::npos) {
        pos += 3; // Move past "ln("
    }

    pos = 0;
    while ((pos = processedExpression.find("log(", pos)) != std::string::npos) {
        processedExpression.replace(pos, 4, "log10(");
        pos += 6; // Move past "log10("
    }

    // Debug output to check processed expression
    std::cout << "Processed Expression: " << processedExpression << std::endl;

    // Compile the processed input expression
    if (!parser.compile(processedExpression, expression)) {
        inputExpression = "Error";
        std::cerr << "Compilation Error: " << parser.error() << std::endl;
        return;
    }

    // Evaluate the expression
    T result = expression.value();

    // Convert the result to a string and update the input expression
    std::ostringstream resultStream;
    resultStream << result;
    inputExpression = resultStream.str();
}

sf::Color Calculator::getDefaultButtonColor(const std::string& label) const {
    if (label == "=" || label == "AC") {
        return orangeDefault;
    }
    else if (label == "/" || label == "*" || label == "-" || label == "+" || label == "sin" || label == "cos" || label == "tan" || label == "log" || label == "ln" || label == "sqrt" || label == "exp" || label == "^") {
        return lightGreyDefault;
    }
    else {
        return darkGreyDefault;
    }
}

void Calculator::updateCursorBlink(float deltaTime) {
    cursorBlinkTimer += deltaTime;
    if (cursorBlinkTimer >= cursorBlinkInterval) {
        cursorBlinkTimer = 0;
        cursorVisible = !cursorVisible; // Toggle cursor visibility
    }
}
