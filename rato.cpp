#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class Slime{
public:
    Slime() : x(300.f),y(400.f),hp(100),energy(100),speed(200.f){
        if(!texture.loadFromFile("assets/textures/slime.png")){
            throw runtime_error("Error loading slime!");
        }
        sprite.setTexture(texture);
        sprite.setScale(5.f,5.f);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2.f,bounds.height/2.f);
        sprite.setPosition((float)x,(float)y);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    }

    void move(float deltaTime){
        sf::Vector2f movement(0.f,0.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y >= 400){
            movement.y -= speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            movement.x -= speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            movement.x += speed;
        }

        sprite.move(movement*deltaTime);
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    float x,y;
    int hp,energy;
    float speed;
};

class Spike{
public:
    Spike() : x(500),y(100){
        if(!texture.loadFromFile("assets/textures/spike.png")){
            throw runtime_error("Error loading spike!");
        }
        sprite.setTexture(texture);
        sprite.setScale(8.f,8.f);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2.f,bounds.height/2.f);
        sprite.setPosition((float)x,(float)y);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    int x,y;
};

class Zombie{
public:
    Zombie() : x(600),y(400){
        if(!texture.loadFromFile("assets/textures/zombie.png")){
            throw runtime_error("Error loading zombie!");
        }
        sprite.setTexture(texture);
        sprite.setScale(4.f,4.f);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width/2.f,bounds.height/2.f);
        sprite.setPosition((float)x,(float)y);
    }

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    int x,y;
};

class Button{
public:
    Button(string title,sf::Vector2f size,sf::Vector2f pos,sf::Font& font){
        button.setSize(size);
        button.setFillColor(sf::Color(18,145,33));
        button.setOutlineThickness(2.f);
        button.setOutlineColor(sf::Color(13,104,24));
        
        button.setOrigin(size.x/2.f,size.y/2.f);
        button.setPosition(pos);

        text.setFont(font);
        text.setString(title);
        text.setCharacterSize((unsigned int)(size.y*0.5f));
        text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width/2.f,bounds.top + bounds.height/2.f);
        text.setPosition(button.getPosition());
    }

    void draw(sf::RenderWindow& window){
        window.draw(button);
        window.draw(text);
    }

    bool isHoveredOver(sf::Vector2f mouse){
        return button.getGlobalBounds().contains(mouse);
    }

    void setFillColor(sf::Color color){
        button.setFillColor(color);
    }

private:
    sf::RectangleShape button;
    sf::Text text;
};

class Text{
public:
    Text(string title,unsigned int size,sf::Vector2f pos,sf::Font& font){
        text.setFont(font);
        text.setString(title);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width/2.f,bounds.top + bounds.height/2.f);
        text.setPosition(pos);
    }

    void draw(sf::RenderWindow& window){
        window.draw(text);
    }

private:
    sf::Text text;
};

int main(){
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    float screenWidth = static_cast<float>(screen.width);
    float screenHeight = static_cast<float>(screen.height);

    sf::Clock clock;
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

    // Main text
    Text text("Rato's paradise",screenWidth/16.f,{screenWidth/2.f,5.f/36.f*screenHeight},font);

    // Quit button
    Button quit("Quit",{5.f/96.f*screenWidth,5.f/108.f*screenHeight},{4.f/64.f*screenWidth,25.f/27.f*screenHeight},font);

    // Examplary button
    Button example("Title",{200,40},{screenWidth/2.f,screenHeight/2.f},font);

    //Slime
    Slime slime;

    // Spike
    Spike spike;

    // Zombie
    Zombie zombie;

    while(window.isOpen()){
        sf::Event event;
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

        sf::Time tickTime = clock.restart();
        float deltaTime = tickTime.asSeconds();

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
                    if(quit.isHoveredOver(mouseWorldPos)){
                        window.close();
                    }
                }
            }
        }

        if(quit.isHoveredOver(mouseWorldPos)){
            quit.setFillColor(sf::Color(18,125,33));
        } 
        else{
            quit.setFillColor(sf::Color(18,145,33));
        }

        if(example.isHoveredOver(mouseWorldPos)){
            example.setFillColor(sf::Color(18,125,33));
        } 
        else{
            example.setFillColor(sf::Color(18,145,33));
        }

        slime.move(deltaTime);

        window.clear();
        window.draw(background);
        quit.draw(window);
        example.draw(window);
        text.draw(window);
        slime.draw(window);
        spike.draw(window);
        zombie.draw(window);

        window.display();
    }
}