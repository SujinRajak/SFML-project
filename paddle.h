
#ifndef PADDLE_H
#define PADDLE_H


#include"SFML/Graphics.hpp"

class paddle
{
	sf::RectangleShape playerObject;

public:
	paddle(sf::Color COLOR);
	// virtual ~paddle();
	//this is to set the postion of the paddle
	void playerPositon(sf::Vector2f(coordinate));
	//this is to set the size of the paddle which in cludes height and width
	void playerSize(sf::Vector2f(sizee));

	//this will hep in the movement of the paddle
	void moveUp();//float d);

	void moveDown();//float d);

	sf::FloatRect getGlobal();
	// detect collision
	bool isColliding(sf::RectangleShape RECTANGLE);

	//this is to return the paddle postion
	sf::Vector2f getPaddlePosition();

	//this is to return the paddle size
	sf::Vector2f getPaddleSize();

	/*this is done so that we can draw an object with the use of class
	sf::RenderWindow is marked as 'non-copyable'. This means you can't copy it.
	You don't want to copy it anyway - you don't accidentally want two windows. If you do want two seperate windows, you
	can manually create a second window, instead of accidentally duplicating one. */
	void update(sf::RenderWindow &app);

protected:

private:
};

#endif // PADDLE_H


#pragma once
