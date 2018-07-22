#pragma once

#ifndef BALL_H
#define BALL_H

#include"SFML/Graphics.hpp"
#include"paddle.h"


class ball
{
	sf::CircleShape Pball;
	sf::Vector2f initialspeed;
	sf::Vector2f ballrect;
public:

	//sets the ball with radius and color
	ball(int ballrad, sf::Color Color);
	//sets the ball coordinate
	void ballPosition(sf::Vector2f(postion));
	//moving the ball
	void ballMove(float ballAngle);

	//if the ball moves strikes the x coordinate it deflects the direction
	void deflectX();

	//if the ball strikes the y coordinate it deflects the direction
	void deflectY();

	//accelerate the ball if it touches the paddle
	void accelerate(paddle pla);

	// void bpCollision(paddle pla);

	//reseeting the speed of the ball
	void Speedup(float sign);

	//this function is for the bal to return its globalbounds
	sf::FloatRect globalCircle();

	//condition for ball colliding with the backgound
	bool isballColliding(sf::RectangleShape RECTANGLE);

	bool isballPlacollision(sf::FloatRect pRec);

	//returns the ball position
	sf::Vector2f getBallPosition();

	//reseetting the speed
	void resetSpeed();



	//returning the ball radius
	int retRad();


	//to make a ball
	void update(sf::RenderWindow& app);
protected:

private:
};

#endif // BALL_H
