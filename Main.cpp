#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

#include "tinyfiledialogs.h"
#include "Utils.h"

static void setOriginToCenter(auto& obj)
{
    obj.setOrigin(obj.getLocalBounds().width / 2, obj.getLocalBounds().height / 2);
}

// Static objects only
constexpr static void followStatic(auto& follower, const auto& followed)
{
    follower.setPosition(followed.getPosition());
}

static bool isMouseOver(const sf::RectangleShape& object, const sf::Vector2i& cursorPos)
{
    return object.getGlobalBounds().contains(static_cast<sf::Vector2f>(cursorPos));
}
// WARNING : It's complete chaos down there

std::string_view getStatusString(const sf::Music::Status& audio)
{
    switch (audio)
    {
        case sf::SoundSource::Stopped:
            return "Stopped";
            break;
        case sf::SoundSource::Paused:
            return "Paused";
            break;
        case sf::SoundSource::Playing:
            return "Playing";
            break;
        default:
            return "Not Loaded";
            break;
    }
}

std::string getViewTime(const sf::Time& time)
{
    return std::to_string((Utils::trunc_decs(time.asSeconds() / 120, 2))) + " \\ " + std::to_string(1);
}

void printCurrentAudioStatus(const sf::Music& audio)
{
    std::cout << '\n' << getStatusString(audio.getStatus()) << " " << getViewTime(audio.getDuration()) << '\n';
}

int main()
{
    constexpr uint32_t windowWidth{640};
    constexpr uint32_t windowHeight{480};

    const sf::Vector2f screenCenter((float) windowWidth / 2, (float) windowHeight / 2);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Cool Media Player");
    window.setKeyRepeatEnabled(true);

    // Rects Only
    sf::RectangleShape button_ChooseFile(sf::Vector2f(220, 40));

    // Rects Init Values
    button_ChooseFile.setFillColor(sf::Color::Red);
    setOriginToCenter(button_ChooseFile);


    sf::Font mainFont;
    sf::Music music;

    if (!mainFont.loadFromFile("Res/arialbd.ttf"))
    {
        system("pause");
        return EXIT_FAILURE;
    }

#pragma region Text Only

    sf::Text text_audioDuration("0:00 / 3:29", mainFont);
    sf::Text text_selectAudio("Choose A File", mainFont);

#pragma endregion

    text_audioDuration.setPosition(sf::Vector2f(25, windowHeight / 1.1f));

    setOriginToCenter(text_selectAudio);
    text_selectAudio.setPosition(screenCenter);
    followStatic(button_ChooseFile, text_selectAudio);
    button_ChooseFile.setPosition(sf::Vector2f(button_ChooseFile.getPosition().x, button_ChooseFile.getPosition().y + 8));

    bool button_ChooseFileClicked{false};

    bool isMouseOverChooseFile{false};

    bool currentLoaded{};

    while (window.isOpen())
    {
        window.clear();

        sf::Event e;
        sf::Vector2i mousePos;

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed || e.key.code == sf::Keyboard::Escape)
                window.close();

            if (music.getStatus() == sf::Music::Playing)
            {
                sf::Time currentOffset = music.getPlayingOffset();
                switch (e.type)
                {
                    case sf::Event::KeyPressed:
                        switch (e.key.code)
                        {
                            case sf::Keyboard::Right:
                                music.setPlayingOffset(currentOffset + sf::seconds(1.f));
                                std::cout << "Seaked to " << currentOffset.asSeconds() << '\n';
                                break;

                            case sf::Keyboard::Left:
                                music.setPlayingOffset(currentOffset - sf::seconds(1.f));
                                std::cout << "Seaked to " << currentOffset.asSeconds() << '\n';
                                break;

                            case sf::Keyboard::Down:
                                if (music.getVolume() > 1 && !(music.getVolume() - 5.f < 0))
                                {
                                    music.setVolume(music.getVolume() - 5.f);
                                }
                                else if (music.getVolume() - 5.f < 0)
                                {
                                    music.setVolume(0);
                                }
                                std::cout << "Volume Down : " << music.getVolume() << '\n';
                                break;

                            case sf::Keyboard::Up:
                                if (music.getVolume() < 99)
                                    music.setVolume(music.getVolume() + 5.f);
                                std::cout << "Volume Up : " << music.getVolume() << '\n';
                                break;

                            default:
                                break;

                        }
                        break;



                        break;
                    default:
                        break;
                }

            }

            switch (e.type)
            {
                case sf::Event::KeyReleased:
                    switch (e.key.code)
                    {
                        case sf::Keyboard::Space:
                            if (music.getStatus() == sf::Music::Playing)
                            {
                                std::cout << "Pause\n";
                                music.pause();
                            }

                            else if (music.getStatus() == sf::Music::Paused)
                            {
                                std::cout << "Resume\n";
                                music.play();
                            }
                            break;

                        case sf::Keyboard::O:
                            printCurrentAudioStatus(music);
                            break;

                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        mousePos = sf::Mouse::getPosition(window);

        isMouseOverChooseFile = isMouseOver(button_ChooseFile, mousePos);

        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                button_ChooseFileClicked = true;
            }
        }

        if (button_ChooseFileClicked && music.getStatus() != sf::Music::Playing && !currentLoaded)
        {
            // const char* filters[] = {"*.mp3", "*.wav", "*.flac", "*.ogg", "*.aac"};
            // std::string filePath{};
            // tinyfd_openFileDialog("Choose Audio File", "", 5, filters, "Audio Files (*.mp3;*.wav;*.flac;*.ogg;*.aac)", 0);


            if (!music.openFromFile("Frank Ocean - Self Control.mp3"))
                return -1;

            std::cout << "Played\n";
            music.play();
            currentLoaded = true;
        }

        window.draw(button_ChooseFile);

        window.draw(text_audioDuration);
        window.draw(text_selectAudio);

        if (isMouseOverChooseFile)
            button_ChooseFile.setFillColor(sf::Color::Green);
        else
            button_ChooseFile.setFillColor(sf::Color::Red);

        window.display();
    }

    return 0;
}