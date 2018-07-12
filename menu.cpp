#include "menu.h"

bool LoadMenu(sf::RenderWindow &app)
{
    bool flowMenu=true;

    menu Menu_items(app.getSize().x, app.getSize().y);

    app.setKeyRepeatEnabled(false);
    while(app.isOpen())
    {
        app.clear();

        sf::Event event;
        if(flowMenu)
        {
        while(app.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                {
                    exit(0);
                };

            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Down)
                    Menu_items.moveDown();
            }

            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Up)
                    Menu_items.moveUp();
            }

            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Return)
                {
                    switch(Menu_items.getselectedIndex())
                    {

                        case 1 : return true;
                        case 2 :exit(0);

                    }
                }
            }

        }
            Menu_items.draw(app);
        }


        app.display();
    }
}

