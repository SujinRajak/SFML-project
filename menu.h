#ifndef MENU_H
#define MENU_H

#include"SFML/Graphics.hpp"
#include<iostream>
#define maxTimes 3
class menu
{

    int selectedIndex;
    sf::Font font;
    sf::Text title[maxTimes];
    public:

    menu(float width,float height)
    {
        if(!font.loadFromFile("tomb.ttf")){
            std::cout<<"error loading font!!";
        }

        title[0].setFont(font);
        title[0].setColor(sf::Color::Red);
        title[0].setString("PONG");
        title[0].setPosition(sf::Vector2f(100,20));
        title[0].setCharacterSize(200);

        title[1].setFont(font);
        title[1].setColor(sf::Color::White);
        title[1].setString("Play");
        title[1].setPosition(sf::Vector2f(width/2,height/(maxTimes+1)*2));
        title[1].setCharacterSize(30);

        title[2].setFont(font);
        title[2].setColor(sf::Color::White);
        title[2].setString("Quit");
        title[2].setPosition(sf::Vector2f(width/2,height/(maxTimes+1)*3));
        title[2].setCharacterSize(30);//ctor

        selectedIndex=1;
    }

    void draw(sf::RenderWindow& window){
        window.draw(title[0]);
        window.draw(title[1]);
        window.draw(title[2]);
    }

    void moveUp()
    {
        if (selectedIndex >maxTimes-2)
        {
            title[selectedIndex].setColor(sf::Color::White);
            selectedIndex--;
            title[selectedIndex].setColor(sf::Color::Cyan);
        }
    }

    void moveDown()
    {
        if (selectedIndex<maxTimes)
        {
            title[selectedIndex].setColor(sf::Color::White);
            selectedIndex++;
            title[selectedIndex].setColor(sf::Color::Cyan);
        }
    }

    int getselectedIndex(){
        return selectedIndex;
    }
};

bool LoadMenu(sf::RenderWindow&);

#endif // MENU_H
