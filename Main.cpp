#include <SFML/Graphics.hpp>
#include <iostream>

static void setOriginToCenter(auto& obj)
{
    obj.setOrigin(obj.getLocalBounds().getSize().x / 2, obj.getLocalBounds().getSize().y / 2);
}

int main()
{
    constexpr uint32_t windowWidth{640};
    constexpr uint32_t windowHeight{480};
    const sf::Vector2f screenCenter((float) windowWidth / 2, (float) windowHeight / 2);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Media Player");
    sf::RectangleShape rect(sf::Vector2f(25, 25));

    rect.setFillColor(sf::Color::Red);


    sf::Font mainFont;

    if (!mainFont.loadFromFile("Res/arialbd.ttf"))
    {
        system("pause");
        return EXIT_FAILURE;
    }

    sf::Text text_audioDuration("0:00 / 3:29", mainFont);
    sf::Text text_selectAudio("Choose A File", mainFont);

    text_audioDuration.setPosition(sf::Vector2f(25, windowHeight / 1.1f));
    //text_selectAudio.setOrigin(text_selectAudio.getLocalBounds().getSize().x / 2, text_selectAudio.getLocalBounds().getSize().y / 2);
    setOriginToCenter(text_selectAudio);
    text_selectAudio.setPosition(screenCenter);

    while (window.isOpen())
    {
        sf::Event e;

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed || e.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();

        window.draw(rect);

        window.draw(text_audioDuration);
        window.draw(text_selectAudio);

        window.display();
    }

    return 0;
}