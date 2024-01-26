#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

float leftSpeed = 0.5f;
float rightSpeed = 0.5f;
float bulletSpeed = 1.0f;
bool leftBullFired = false;
bool rightBullFired = false;
bool gotHit = false;

sf::String winner = "";

sf::Clock bulletClock;
sf::Clock hitClock;

int main()
{
    sf::Font font;
    font.loadFromFile("arial.ttf");

    string gameOverText = "GAME OVER " + winner + " WINS";
    sf::Text gameOver;
    gameOver.setFont(font);
    gameOver.setFillColor(sf::Color::Yellow);
    gameOver.setPosition(140, 550);
    gameOver.setCharacterSize(60);
    gameOver.setString(gameOverText);
    gameOver.setLetterSpacing(2);
    gameOver.setOutlineThickness(5);

    sf::RenderWindow window(sf::VideoMode(1400, 1200), "Game title");

    sf::Texture spaceBg;
    spaceBg.loadFromFile("space.jpg");

    sf::Sprite background;
    background.setTexture(spaceBg);

    // Shooter rectangles
    sf::RectangleShape leftRectangle(sf::Vector2f(20.0f, 200.0f));
    leftRectangle.setPosition(0, 600);
    leftRectangle.setFillColor(sf::Color::Cyan);

    sf::RectangleShape rightRectangle(sf::Vector2f(20.0f, 200.0f));
    rightRectangle.setPosition(1380, 600);
    rightRectangle.setFillColor(sf::Color::Cyan);

    sf::CircleShape leftBullet(20.0f);
    leftBullet.setFillColor(sf::Color::Red);

    sf::CircleShape rightBullet(20.0f);
    rightBullet.setFillColor(sf::Color::Red);

    background.setScale(
        static_cast<float>(window.getSize().x) / background.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / background.getLocalBounds().height
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Fire bullet for left rectangle
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!leftBullFired && bulletClock.getElapsedTime().asMilliseconds() > 100) {
                    leftBullet.setPosition(leftRectangle.getPosition().x + leftRectangle.getSize().x, leftRectangle.getPosition().y);
                    leftBullFired = true;
                    bulletClock.restart();
                }
            }
            // Fire bullet for right rectangle
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::RAlt) {
                if (!rightBullFired && bulletClock.getElapsedTime().asMilliseconds() > 100) {
                    rightBullet.setPosition(rightRectangle.getPosition().x - rightBullet.getRadius() * 2, rightRectangle.getPosition().y);
                    rightBullFired = true;
                    bulletClock.restart();
                }
            }
        }

        // Movement logic
        if (leftRectangle.getPosition().y > 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                leftRectangle.move(0.0f, -leftSpeed);
        }

        if (leftRectangle.getPosition().y + leftRectangle.getSize().y < window.getSize().y) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                leftRectangle.move(0.0f, leftSpeed);
        }

        if (rightRectangle.getPosition().y > 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                rightRectangle.move(0.0f, -rightSpeed);
        }

        if (rightRectangle.getPosition().y + rightRectangle.getSize().y < window.getSize().y) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                rightRectangle.move(0.0f, rightSpeed);
        }

        // Bullet movement and disappearance logic
        if (leftBullFired) {
            leftBullet.move(bulletSpeed, 0.0f);
            if (leftBullet.getPosition().x > window.getSize().x -5) {
                leftBullFired = false;
            }
        }

        if (rightBullFired) {
            rightBullet.move(-bulletSpeed, 0.0f);
            if (rightBullet.getPosition().x < 0 - 5) {
                rightBullFired = false;
            }
        }

        // Game ending logic
        sf::FloatRect leftBulletBounds = leftBullet.getGlobalBounds();
        sf::FloatRect rightRectangleBounds = rightRectangle.getGlobalBounds();
        if (leftBulletBounds.intersects(rightRectangleBounds))
        {
            winner = "LEFT SHOOTER";
            gotHit = true;
        }
        else
        {
            sf::FloatRect rightBulletBounds = rightBullet.getGlobalBounds();
            sf::FloatRect leftRectangleBounds = leftRectangle.getGlobalBounds();
            if (rightBulletBounds.intersects(leftRectangleBounds))
            {
                winner = "RIGHT SHOOTER";
                gotHit = true;
            }
        }

        window.clear();
        window.draw(background);
        window.draw(leftRectangle);
        window.draw(rightRectangle);

        if (leftBullFired) {
            window.draw(leftBullet);
        }

        if (rightBullFired) {
            window.draw(rightBullet);
        }

        if (gotHit) {
            gameOver.setString("GAME OVER " + winner + " WINS");
            window.draw(gameOver);
        }

        if (gotHit && hitClock.getElapsedTime().asSeconds() > 5) {
            window.close();
        }

        window.display();
    }

    return 0;
}
