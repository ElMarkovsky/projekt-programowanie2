#include <iostream>
#include <string>
#include <optional>
#include <SFML/Graphics.hpp>
using namespace std;

class Slime{
public:
    Slime(float screenWidth) : x(300.f),y(400.f),hp(100),energy(100),speed(screenWidth*0.2f),gravity(0.f){
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

    void move(float deltaTime,float screenWidth,float screenHeight){
        sf::Vector2f movement(0.f,0.f);
        gravity += 200*screenHeight*deltaTime;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && y > 0){
            movement.y -= speed;
            gravity = 0;
        }
        else if(y < screenHeight*0.9f){
            movement.y += gravity*deltaTime;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x >= 0){
            sprite.setScale(5.f,5.f);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                movement.x -= 2*speed; 
            }
            else{
                movement.x -= speed;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x <= screenWidth){
            sprite.setScale(-5.f,5.f);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                movement.x += 2*speed; 
            }
            else{
                movement.x += speed;
            }
        }

        y = sprite.getPosition().y;
        if(y >= screenHeight*0.9f){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                sprite.setPosition(sprite.getPosition().x,screenHeight*0.9f - 1);
                gravity = -100*screenHeight;
            }
            else{
                sprite.setPosition(sprite.getPosition().x,screenHeight*0.9f);
                gravity = 0;
            }
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
    float gravity;
};

class Spike{
public:
    Spike(float screenWidth,float screenHeight) : x(500),y(100){
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

    void move(float deltaTime,float screenHeight){
        sf::Vector2f movement(0.f,0.f);
        movement.y += 50*screenHeight*deltaTime;

        sprite.move(movement*deltaTime);
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
    }

    int getY(){
        return y;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    int x,y;
};

class Zombie{
public:
    Zombie(float screenWidth,float screenHeight) : x(600),y(screenHeight*0.9f),speed(10*screenWidth){
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

    void move(float deltaTime,float screenWidth){
        sf::Vector2f movement(0.f,0.f);
        if(x >= screenWidth || x <= 0){
            speed = -speed;
            sprite.setScale(-sprite.getScale().x,sprite.getScale().y);
        }
        movement.x += speed*deltaTime;

        sprite.move(movement*deltaTime);
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    int x,y;
    float speed;
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
    optional<Text> text;
    text.emplace("Rato's paradise",screenWidth/16.f,sf::Vector2f(screenWidth/2.f,5.f/36.f*screenHeight),font);

    // Quit button
    optional<Button> quit;
    quit.emplace("Quit",sf::Vector2f(5.f/96.f*screenWidth,5.f/108.f*screenHeight),sf::Vector2f(4.f/64.f*screenWidth,25.f/27.f*screenHeight),font);

    // Examplary button
    optional<Button> example;
    example.emplace("Title",sf::Vector2f(200,40),sf::Vector2f(screenWidth/2.f,screenHeight/2.f),font);

    //Slime
    optional<Slime> slime;
    slime.emplace(screenWidth);

    // Spike
    optional<Spike> spike;
    spike.emplace(screenWidth,screenHeight);

    // Zombie
    optional<Zombie> zombie;
    zombie.emplace(screenWidth,screenHeight);

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
                    if(quit->isHoveredOver(mouseWorldPos)){
                        window.close();
                    }
                }
            }
        }

        if(quit->isHoveredOver(mouseWorldPos)){
            quit->setFillColor(sf::Color(18,125,33));
        } 
        else{
            quit->setFillColor(sf::Color(18,145,33));
        }

        if(example->isHoveredOver(mouseWorldPos)){
            example->setFillColor(sf::Color(18,125,33));
        } 
        else{
            example->setFillColor(sf::Color(18,145,33));
        }

        slime->move(deltaTime,screenWidth,screenHeight);
        spike->move(deltaTime,screenHeight);
        zombie->move(deltaTime,screenWidth);

        if(spike->getY() > screenHeight){
            spike.emplace(screenWidth,screenHeight);
        }

        window.clear();
        window.draw(background);
        quit->draw(window);
        example->draw(window);
        text->draw(window);
        slime->draw(window);
        spike->draw(window);
        zombie->draw(window);

        window.display();
    }
}