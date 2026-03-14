#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main(){
    bool clicked = false;
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    float screenWidth = static_cast<float>(screen.width);
    float screenHeight = static_cast<float>(screen.height);
    sf::RenderWindow window(screen,"Rato's paradise",sf::Style::Fullscreen);
    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf")) {
        cerr << "Error loading font!" << endl;
        return 1;
    }

    // Background
    sf::Texture bgPhoto;
    if(!bgPhoto.loadFromFile("assets/textures/background.png")){
        cerr << "Error loading background!" << endl;
        return 1;
    }
    sf::Sprite background(bgPhoto);
    background.setScale(screenWidth/bgPhoto.getSize().x,screenHeight/bgPhoto.getSize().y);

    // Slime
    sf::Texture slimePhoto;
    if(!slimePhoto.loadFromFile("assets/textures/slime.png")){
        cerr << "Error loading slime!" << endl;
        return 1;
    }
    sf::Sprite slime(slimePhoto);
    slime.setScale(5.f,5.f);
    slime.setPosition(2.f/5.f*screenWidth,2.f/5.f*screenHeight);

    // Spike
    sf::Texture spikePhoto;
    if(!spikePhoto.loadFromFile("assets/textures/spike.png")){
        cerr << "Error loading spike!" << endl;
        return 1;
    }
    sf::Sprite spike(spikePhoto);
    spike.setScale(2.f,2.f);
    spike.setPosition(47.f/100.f*screenWidth,11.f/20.f*screenHeight);

    // Main text
    sf::Text mainText;
    mainText.setFont(font);
    mainText.setString("Rato's paradise");
    mainText.setCharacterSize(screenWidth/16.f);
    mainText.setFillColor(sf::Color(10,80,18));
    sf::FloatRect textRect = mainText.getLocalBounds();
    mainText.setOrigin(textRect.left + textRect.width/2.f,textRect.top + textRect.height/2.f);
    mainText.setPosition(screenWidth/2.f,5.f/36.f*screenHeight);

    // Quit button
    sf::RectangleShape buttonQuit(sf::Vector2f(5.f/96.f*screenWidth,5.f/108.f*screenHeight));
    buttonQuit.setFillColor(sf::Color(18,145,33));
    buttonQuit.setOutlineThickness(screenWidth/960.f);
    buttonQuit.setOutlineColor(sf::Color(13,104,24));
    buttonQuit.setPosition(screenWidth/64.f,25.f/27.f*screenHeight);
    sf::Text quitText;
    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(screenWidth/80.f);
    quitText.setFillColor(sf::Color::White);
    sf::FloatRect quitRect = quitText.getLocalBounds();
    quitText.setOrigin(quitRect.left + quitRect.width/2.f,quitRect.top + quitRect.height/2.f);
    quitText.setPosition(buttonQuit.getPosition().x + buttonQuit.getSize().x/2.f,buttonQuit.getPosition().y + buttonQuit.getSize().y/2.f);

    // Examplary button
    sf::RectangleShape button(sf::Vector2f(5.f/30.f*screenWidth,5.f/108.f*screenHeight));
    button.setFillColor(sf::Color(18,145,33));
    button.setOutlineThickness(screenWidth/960.f);
    button.setOutlineColor(sf::Color(13,104,24));
    button.setPosition(4.f/5.f*screenWidth,3.f/10.f*screenHeight);
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Button");
    buttonText.setCharacterSize(24.f*screenWidth/1920.f);
    buttonText.setFillColor(sf::Color::White);
    sf::FloatRect rockRect = buttonText.getLocalBounds();
    buttonText.setOrigin(rockRect.left + rockRect.width/2.f,rockRect.top + rockRect.height/2.f);
    buttonText.setPosition(button.getPosition().x + button.getSize().x/2.f,button.getPosition().y + button.getSize().y/2.f);

    while(window.isOpen()){
        sf::Event event;
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(buttonQuit.getGlobalBounds().contains(mouseWorldPos)){
                        window.close();
                    }

                    if(button.getGlobalBounds().contains(mouseWorldPos)){
                        clicked = true;
                    }
                }
            }
        }

        if(buttonQuit.getGlobalBounds().contains(mouseWorldPos)){
            buttonQuit.setFillColor(sf::Color(18,125,33));
        } 
        else{
            buttonQuit.setFillColor(sf::Color(18,145,33));
        }

        if(button.getGlobalBounds().contains(mouseWorldPos)){
            button.setFillColor(sf::Color(18,125,33));
        } 
        else{
            button.setFillColor(sf::Color(18,145,33));
        }

        window.clear();
        window.draw(background);
        window.draw(buttonQuit);
        window.draw(quitText);
        window.draw(button);
        window.draw(buttonText);
        window.draw(slime);

        if(!clicked){
        }
        else if(clicked){
            window.draw(spike);
        }
        window.draw(mainText);
        window.display();
    }
}