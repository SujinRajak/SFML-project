#include "ball.h"
#include"SFML/Graphics.hpp"
#include<cmath>
#include<iostream>
#define pi 3.1415926
#include "paddle.h"

//since we need the velocity of the ball to move and deflect it we passed two parameter for speed of the ball in x and y asis
sf::Vector2f ballSpeed(0.6, 0.6);

//ball
ball::ball(int ballrad, sf::Color Color)
{
	Pball.setRadius(ballrad);
	Pball.setFillColor(Color);
	Pball.setOutlineColor(sf::Color::Yellow);
	Pball.setOutlineThickness(ballrad / 2);
	initialspeed = ballSpeed;
}

//setting the ball position
void ball::ballPosition(sf::Vector2f(postion))
{

	Pball.setPosition(sf::Vector2f(postion));

}



//deflecting the ball if the ball touches the paddle which is the x axix
void ball::deflectX() {

	initialspeed.x = -initialspeed.x;


}

//deflecting the ball if the ball touches the botscreen
void  ball::deflectY()
{
	/*1-20, deflect at a -60 degree angle
	21-35, deflect at -45
	36-50, deflect at -30
	51-65, deflect at 30
	66-80, deflect at 45
	81-100, deflect at 60 */
	initialspeed.y = -initialspeed.y;
}

/*this is for the ball  accelerating when collides with the paddle */
void ball::accelerate(paddle pla) {

	//from getglobalbounds()
	/*The returned rectangle is in global coordinates, which means that it takes in account the transformations (translation, rotation, scale, ...) that are applied
	to the entity. In other words, this function returns the bounds of the sprite in the global 2D world's coordinate system.*/

	double ballPos = Pball.getGlobalBounds().top + Pball.getGlobalBounds().height / 2;
	std::cout << "ballposition:" << ballPos << std::endl;
	double playerPos = pla.getGlobal().top - pla.getGlobal().height / 2;
	std::cout << "playerpostion:" << playerPos << std::endl;
	initialspeed.y = (ballPos - playerPos) / 100;
	std::cout << "initialspeed of y:" << initialspeed.y << std::endl;
}

//reset the speed of the ball
/*void ball::Speedup(float sign)
{
initialspeed=ballSpeed;
std::cout<<"x:"<<initialspeed.x;
std::cout<<"y:"<<initialspeed.y;

ballSpeed.y = ballSpeed.y +sign;
ballSpeed.x = ballSpeed.x +sign;
std::cout<<"x:"<<ballSpeed.x;
std::cout<<"y:"<<ballSpeed.y;

}*/


/*void ball::resetSpeed(){

sf::Vector2f ballSpeed(0.3,0.3);
initialspeed=ballSpeed;
initialspeed.x=ballSpeed.x;
initialspeed.y=ballSpeed.y;
std::cout<<initialspeed.x<<std::endl;
std::cout<<initialspeed.y<<std::endl;
}*/


/*//this fucntion is for deflection of the ball when  ball touches the paddle
void ball::bpCollision(paddle pla){

//reffer angular velocity
double   ballPos = Pball.getPosition().y - pla.getPaddlePosition().y;
double relativePos = ( pla.getPaddleSize().y - ballPos );
double angle = relativePos * ( pi / pla.getPaddleSize().y );

double newVel = cos( angle ) * initialspeed.y;

} */

//condition for ball colliding in the screen
bool ball::isballColliding(sf::RectangleShape RECTANGLE)
{

	//interesct returns tur or flase Check the intersection between two rectangles
	if (Pball.getGlobalBounds().intersects(RECTANGLE.getGlobalBounds())) {

		std::cout << "is colliding with the screen" << std::endl;

		return true;
	}
	else
		return false;

}

bool ball::isballPlacollision(sf::FloatRect pRec)
{
	if (Pball.getGlobalBounds().intersects(pRec)) {
		std::cout << "is colliding with the paddle" << std::endl;
		return true;
	}
	else
		return false;

}

//moving the ball
void ball::ballMove(float ballAngle) {

	/*since the sin and cos doesnt tkae angle as it works in radian so conveting angle int radian 1 radian=57.6 degree and 2 pi r in a circle*/
	double moveMent = ballAngle * pi / 180.0;
	// Move the ball and it changes the position of the ball
	Pball.move(cos(moveMent) * initialspeed.x, sin(moveMent) * initialspeed.y);
}

//returns the Ball postion
sf::Vector2f ball::getBallPosition()
{
	return Pball.getPosition();
}

//returns the ball radius
int ball::retRad()
{
	return Pball.getRadius();
}

sf::FloatRect ball::globalCircle()
{
	return Pball.getGlobalBounds();
}

//for making a ball
void ball::update(sf::RenderWindow& app)
{
	app.draw(Pball);
}


