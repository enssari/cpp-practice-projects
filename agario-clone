#include <SFML/Graphics.hpp>
#include <cstdlib> 

using namespace std;

float circleM = 45.0f;
float speed = 0.2f;

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Egar.io");

    sf::CircleShape circle(circleM);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(780, 500);

    sf::CircleShape food(15.0f);
    food.setFillColor(sf::Color::Blue);
    food.setPosition(500, 300);

    sf::Text massT;
    massT.setCharacterSize(80);
    massT.setFillColor(sf::Color::White);
    massT.setPosition(1400, 50);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    massT.setFont(font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        sf::Vector2f direction(static_cast<float>(mousePosition.x) - circle.getPosition().x,
            static_cast<float>(mousePosition.y) - circle.getPosition().y);

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            direction.x /= length;
            direction.y /= length;
        }

        float distance = std::sqrt(std::pow(circle.getPosition().x - food.getPosition().x, 2) +
            std::pow(circle.getPosition().y - food.getPosition().y, 2));

        if (distance < circleM + food.getRadius())
        {
            circleM += 4.0f;
            circle.setRadius(circleM);
            int massP = circleM * 9;
            massT.setString(to_string(massP));

            food.setPosition(static_cast<float>(std::rand() % (window.getSize().x - static_cast<int>(food.getRadius()) * 2)),
                static_cast<float>(std::rand() % (window.getSize().y - static_cast<int>(food.getRadius()) * 2)));
        }

        circle.move(direction.x * speed, direction.y * speed);

        window.clear();
        window.draw(circle);
        window.draw(food);
        window.draw(massT);
        window.display();
    }

    return 0;
}
