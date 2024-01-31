#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Hunt");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../../resources/R-Touhou/graphics/Background.jpg"))
        return -1;
    sf::Sprite background(backgroundTexture);

    sf::Texture duckTexture;
    if (!duckTexture.loadFromFile("../../resources/R-Touhou/graphics/Fish.png"))
        return -1;
    sf::Sprite duck(duckTexture);
    duck.setPosition(rand() % 700, rand() % 500);

    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("../../resources/R-Touhou/font/arial.ttf"))
        return -1;
    sf::Text scoreText("Score: 0", font, 24);
    scoreText.setPosition(10, 10);

    float speed = 0.07f;
    int direction = rand() % 4;

    while (window.isOpen()) {
        srand(static_cast<unsigned>(time(0)));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (duck.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    score++;
                    duck.setPosition(rand() % 700, rand() % 500);
                    scoreText.setString("Score: " + std::to_string(score));
                }
            }
        }

        // Move the duck based on the current direction
        if (direction == 0) {
            duck.move(speed, 0); // Horizontal
        } else if (direction == 1) {
            duck.move(0, speed); // Vertical
        } else if (direction == 2) {
            duck.move(speed, speed); // Diagonal
        } else {
            duck.move(-speed, -speed); // Diagonal
        }

        // If the duck goes off the window, reset its position and change direction
        if (duck.getPosition().x > window.getSize().x || duck.getPosition().x < 0 ||
            duck.getPosition().y > window.getSize().y || duck.getPosition().y < 0) {
            duck.setPosition(rand() % 790, rand() % 590);
            direction = rand() % 3;
        }

        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(duck);
        window.draw(scoreText);
        window.display();
    }
    return 0;
}
