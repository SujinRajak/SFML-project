#include "paddle.h"
#include<iostream>
#include "SFML/Graphics.hpp"

const int playerSpeed=40;

paddle::paddle(sf::Color COLOR)
{
    playerObject.setFillColor(COLOR);
}

//this is to set the postion of the paddle
void paddle::playerPositon(sf::Vector2f coordinate)
{
   playerObject.setPosition(coordinate);
}


//this is to set the size of the paddle which in includes height and width
void paddle::playerSize(sf::Vector2f sizee)
{
    playerObject.setSize(sizee);
}

/*why is ddint use deltatime ??
it allows you to alter timescale (e.g. slow motion).
Actually, you don't want to use deltaTime with rigidbody.velocity. Due to the fact that it already moves your character at a speed that is framerate independent, using Time.deltaTime actually breaks things. It basically becomes framerate dependent again due to your velocity essentially being speed * Time.deltaTime * Time.deltaTime.
So, just set rigidbody.velocity equal to Vector3(0,0,speed). It should work just fine.*/

//this is for the movement of paddle as since moving up the y coordinate value decreases
void paddle::moveUp(){
    playerObject.move(0,-playerSpeed);
}

//this is for the movemont of paddle since moving down the value of y coordinate increases
void paddle::moveDown(){
        playerObject.move(0, playerSpeed);
}

sf::FloatRect paddle::getGlobal(){
       return playerObject.getGlobalBounds();

}
//condition for the paddle collidind with the background rectangles
bool paddle::isColliding(sf::RectangleShape RECTANGLE)
{
    /*
Get the global bounding rectangle of the entity.
The returned rectangle is in global coordinates, which means that it takes in account the transformations (translation, rotation, scale, ...) that are applied to the entity. In other words, this function returns the bounds of the sprite in the global 2D world's coordinate system.
Returns
    Global bounding rectangle of the entity */
if(playerObject.getGlobalBounds().intersects(RECTANGLE.getGlobalBounds())){
        std::cout<<"is colling with the rectangle"<<std::endl;
        return true;
    }
    else
    return false;
/*getGlobalBounds returns the coordinates of the bounding rectangular box of the sprite we loaded in. Intersection is
determined when any of these return coordinates first return the same value, just like two intersecting functions.*/
}

//this is to return the paddle position
sf::Vector2f paddle::getPaddlePosition()
{
    return playerObject.getPosition();
}

//this is to return the paddle size
sf::Vector2f paddle::getPaddleSize()
{
    return playerObject.getSize();
}

//this is used becoz aftr the ball is out then again the paddle will be reset to the initial position
void paddle::update(sf::RenderWindow &app)
{
    app.draw(playerObject);
}
