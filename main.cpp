#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "paddle.h"
#include "ball.h"
#include <iostream>
#include "menu.h"
#include <sstream>
#include <fstream>
#include<iomanip>

#define file "HighScore.txt"


/*for videoMode coordinate*/
#define xVideomode 800
#define yVidoemode 600
#define screenName" PONG !! "

#define winner "WINNER"

/*height and width for both paddle*/
 int width=10;
 int height=80;

//player position for x and y
int player1X=40;
int player1Y=300;
int player2X=750;
int player2Y=300;

//for storing hight score of the player
int highScorePlayer=0;

//colos for different player
sf::Color player1Color=sf::Color::Magenta;
sf::Color player2Color=sf::Color::Magenta;


//for ball radius
 int ballrad=6;


// for ball coordinate
    int ballx=xVideomode/2;
    int bally=yVidoemode/2;

//for balls defualtposition
sf::Vector2f defaultPosition(ballx,bally);

//changing the ball movement angle
 double ballAngle=45;

 //color for ball
 sf::Color ballColor=sf::Color::White;

//ball randomspeed
float randomSpeed=0.1;

/** for background **/
const int topRecWidth = 800;
const int topRecHeight = 30;
sf::Color topRecColor = sf::Color::Red;

const int botRecWidth = 800;
const int botRecHeight = 30;
sf::Color botRecColor = sf::Color::Red;

const int leftRecWidth = 30;
const int leftRecHeight = 600;
sf::Color leftRecColor = sf::Color::Green;

const int rightRecWidth = 30;
const int rightRecHeight = 600;
sf::Color rightRecColor = sf::Color::Green;

const int middleRecWidth = 5;
const int middleRecHeight = 540;
sf::Color middleRecColor= sf::Color::Red;

int bigCrad=90;
const int circlePosx=xVideomode/2;
const int circlePosy=yVidoemode/2;
sf::Color bigCcolor=sf::Color::Black;

int main()
{
    //creating a window
    sf::RenderWindow window(sf::VideoMode(xVideomode, yVidoemode), screenName);

    if(LoadMenu(window)== true)
        window.close();
    else if(LoadMenu(window)==false)
        return 0;

    char name1[40],name2[40];
    std::cout<<"enter the player1name:";
    std::cin>>name1;

    std::cout<<"enter the player2name:";
    std::cin>>name2;

   sf::RenderWindow app(sf::VideoMode(xVideomode,yVidoemode),screenName);
   //creating a window

    //for loading the font
    sf::Font font;
    if(!font.loadFromFile("tomb.ttf")){
      std::cout<<"the font cant be loaded";
    }

    sf::Text player1Name,player2Name;
    player1Name.setString(name1);
    player1Name.setFont(font);
    player1Name.setCharacterSize(40);
    player1Name.setPosition(30,0);

    player2Name.setString(name2);
    player2Name.setFont(font);
    player2Name.setCharacterSize(40);
    player2Name.setPosition(650,0);




    sf::SoundBuffer buffer1;
    if(!buffer1.loadFromFile("paddlehit.wav")){
        std::cout<<"error loading the sound";
    }

    sf::SoundBuffer buffer2;
    if(!buffer2.loadFromFile("ball.wav")){
        std::cout<<"error loading the sound";
    }

    sf::Sound paddles;
    paddles.setBuffer(buffer1);

    sf::Sound balls;
    balls.setBuffer(buffer2);

//creating a rectangle for the screen/ backgound
    sf::RectangleShape backGTopRec;
    sf::RectangleShape backGBotRec;
    sf::RectangleShape backGLeftRec;
    sf::RectangleShape backGRightRec;
    sf::RectangleShape middlerec;
    sf::CircleShape middlecircle;

    /*a frame updates in less than one millisecond */
    /*the moment we make a clock its running just like a stop watch ,clock has two methods one is to check the value and another
        is to reset it,REsolution of clock is very high  */

    //seting up rectangle for backgound //top
    backGTopRec.setPosition(sf::Vector2f(0,0));
    backGTopRec.setSize(sf::Vector2f(topRecWidth,topRecHeight));
    backGTopRec.setFillColor(topRecColor);
    //bot background
    backGBotRec.setPosition(sf::Vector2f(0,570));
    backGBotRec.setSize(sf::Vector2f(botRecWidth,botRecHeight));
    backGBotRec.setFillColor(botRecColor);
    //left background
    backGLeftRec.setPosition(sf::Vector2f(0,0));
    backGLeftRec.setSize(sf::Vector2f(leftRecWidth,leftRecHeight));
    backGLeftRec.setFillColor(leftRecColor);
    //right background
    backGRightRec.setPosition(sf::Vector2f(770,0));
    backGRightRec.setSize(sf::Vector2f(rightRecWidth,rightRecHeight));
    backGRightRec.setFillColor(rightRecColor);
    //middle rec
    middlerec.setPosition(sf::Vector2f(xVideomode/2-middlerec.getSize().x,30));
    middlerec.setSize(sf::Vector2f(middleRecWidth,middleRecHeight));
    middlerec.setFillColor(middleRecColor);
    //for circle drawn in the middle
    middlecircle.setPosition(xVideomode/2-middlerec.getSize().x-80,yVidoemode/2-100);
    middlecircle.setRadius(bigCrad);
    middlecircle.setFillColor(bigCcolor);
    middlecircle.setOutlineColor(sf::Color::Red);
    middlecircle.setOutlineThickness(bigCrad/13);

    //declaring paddle class with 2 rectangles as object
    paddle player1(player1Color);
    paddle player2(player2Color);

    //declaring and making a ball class with a circle as object and ballradius and ball color with constructor
    ball cBall(ballrad,ballColor);


    //for the ball initial movement to stop the ball as at first ball wil be resting in still motion
    bool ballMove=false;
    bool ballStoped=true;

    bool winCon1=false;
    bool winCon2=false;

    //setting player1
    player1.playerPositon(sf::Vector2f(player1X,player1Y));
    player1.playerSize(sf::Vector2f(width,height));


    //setting player2
    player2.playerPositon(sf::Vector2f(player2X,player2Y));
    player2.playerSize(sf::Vector2f(width,height));

    //drawing a balls
    cBall.ballPosition(sf::Vector2f(ballx,bally));

    //for score of the player
    int player1Score=0, player2Score=0;

    //setting up score for player1
    sf::Text score1;
    score1.setString("0");
    score1.setFont(font);
    score1.setCharacterSize(70);
    score1.setPosition(250,15);
    //score1.setColor(sf::Color::White);

    //setting up score for player2
    sf::Text score2;
    score2.setString("0");
    score2.setFont(font);
    score2.setCharacterSize(70);
    score2.setPosition(500,15);
   // score2.setColor(sf::Color::White);

    //will return true or false only
    while (app.isOpen())
    {
        sf::Event event;
        //this  event will run eveytime the window is open
        while(app.pollEvent(event))
        {
        //updating the screen and handling events like mouse ,keyboard ,etc
            if(event.type==sf::Event::Closed)
                    app.close();//this wil return false

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                player1.moveUp();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    player1.moveDown();
                }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    player2.moveUp();
                }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                       player2.moveDown();
                }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

                if(ballMove==false&&ballStoped==true){
                    ballMove=true;
                    ballStoped=false;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if(LoadMenu(app))
                {
                        player1.playerPositon(sf::Vector2f(player1X,player1Y));
                        player2.playerPositon(sf::Vector2f(player2X,player2Y));
                        cBall.ballPosition(defaultPosition);
                        player1Score = 0;
                        player2Score = 0;
                        score1.setString("0");
                        score2.setString("0");
                        ballMove = false;
                        ballStoped = true;
                        winCon1=false;
                        winCon2=false;
                }
            }

        }


           //moving a ball
            if(ballMove==true && ballStoped==false){
                         cBall.ballMove(ballAngle);
                }

            //colliding concpet for ball and the background of the rectangle
            if(cBall.isballColliding(backGBotRec)){
                        balls.play();
                        cBall.deflectY();

            }

            //colliding concpet for ball and the background of the rectangle
            if(cBall.isballColliding(backGTopRec)){
                        balls.play();
                        cBall.deflectY();
            }



            app.clear();
            //if the ball is colliding with the left rectangle
            if(cBall.isballColliding(backGLeftRec))
            {

                //claculating score;
                player1Score++;
               /*Stream class to operate on strings.Objects of this class use a string buffer that contains a sequence of
               characters. This sequence of characters can be accessed directly as a string object, using member str.*/
                std::stringstream update1Score;//str returns a string object with a copy of the current contents in the stream buffer.
                update1Score << player1Score;
               // fout<<player1Score;
                score1.setString(update1Score.str());//helps for the font to update its value
                //for the ball so that the ball stays in the same coordinate
                cBall.ballPosition(sf::Vector2f(width/2-5,height/2-5));
                //resetting player position as initial if the ball goes out of boundry;
                player1.playerPositon(sf::Vector2f(player1.getPaddlePosition().x, yVidoemode / 2 - 5));
                //after the ball is not hit by a paddle and goes outsides the let and right rectangle then its position is reset to middle
                cBall.ballPosition(defaultPosition);
                ballMove=false;
                ballStoped=true;
              //  cBall.resetSpeed();
            }

            //becoz this will refresh each frame
            app.clear();
            //if ball is coliding with the right rectangle rectangle
            if(cBall.isballColliding(backGRightRec))
            {

                player2Score++;
                std::stringstream update2Score;
                update2Score << player2Score;
                score2.setString(update2Score.str());
                cBall.ballPosition(sf::Vector2f(width/2-5,height/2-5));
                //resetting the paddle postion after the ball goes out of boundry;
                player2.playerPositon(sf::Vector2f(player2.getPaddlePosition().x, yVidoemode / 2 - 5));
                cBall.ballPosition(defaultPosition);
                ballMove=false;
                ballStoped=true;
                //cBall.resetSpeed();

            }

           //for storing the high score of the player
               //
       // fstream fp;
       // fp.open("highScore.txt",std::ios::in|std::ios::out);

            app.clear();
            //clossing  between paddle and ball
            if(cBall.isballPlacollision(player1.getGlobal())){
                         paddles.play();
                         cBall.deflectX();
                       cBall.accelerate(player1);
                      // cBall.Speedup(randomSpeed*-2);

            }

            //window.clear();
            //colliding concpet for ball and the background of the rectangle
            if(cBall.isballPlacollision(player2.getGlobal())){
                         paddles.play();
                         //cBall.Speedup(randomSpeed*-2);
                        cBall.deflectX();
                        cBall.accelerate(player2);
                }


                        sf::Text win1;
                        win1.setString(winner);
                        win1.setFont(font);
                        win1.setCharacterSize(40);
                        win1.setPosition(100,300);

                        sf::Text win2;
                        win2.setString(winner);
                        win2.setFont(font);
                        win2.setCharacterSize(40);
                        win2.setPosition(530,300);

                    if( player1Score > 4 && (player1Score - player2Score >= 2))
                    {
                        std::fstream fp;
                        fp.open(file,std::ios::out);
                        if(!fp.is_open()){
                        fp<<name1<<std::setw(15)<<name2<<std::endl;
                        fp<<player1Score<<std::setw(15)<<player2Score;
                        }
                        fp.close();
                        player1.playerPositon(sf::Vector2f(player1X, player1Y));
                        player2.playerPositon(sf::Vector2f(player2X, player2Y));
                        cBall.ballPosition(defaultPosition);
                       // player1Score = 0;
                       // player2Score = 0;
                       // score1.setString("0");
                        //score2.setString("0");
                        ballMove = false;
                        ballStoped = true;
                        winCon2=true;
                    }
                    else if(player2Score > 4 && (player2Score - player1Score >= 2 ))
                    {
                        std::fstream fp;
                        fp.open(file,std::ios::out);

                        if(!fp.is_open()){
                           fp<<name1<<std::setw(20)<<name2<<std::endl;
                        fp<<player1Score<<std::setw(15)<<player2Score;
                        }
                        fp.close();
                        player1.playerPositon(sf::Vector2f(player1X,player1Y));
                        player2.playerPositon(sf::Vector2f(player2X,player2Y));
                        cBall.ballPosition(defaultPosition);
                        player1Score = 0;
                        player2Score = 0;
                        //score1.setString("0");
                        //score2.setString("0");
                        ballMove = false;
                        ballStoped = true;
                        winCon1=true;
                    }


               /*coditions for paddle movement up and down so that it will be easy for the paddle to move up and down without going
            out of bounds*/
            if(player1.isColliding(backGTopRec))
                        player1.playerPositon(sf::Vector2f(player1.getPaddlePosition().x, backGTopRec.getPosition().y + 30));

            if(player1.isColliding(backGBotRec))
                        player1.playerPositon(sf::Vector2f(player1.getPaddlePosition().x, backGBotRec.getPosition().y - 80));

            if(player2.isColliding(backGTopRec))
                        player2.playerPositon(sf::Vector2f(player2.getPaddlePosition().x, backGTopRec.getPosition().y + 30));

            if(player2.isColliding(backGBotRec))
                    player2.playerPositon(sf::Vector2f(player2.getPaddlePosition().x, backGBotRec.getPosition().y - 80));


                //defualt is balck screen if want to change use sf::Color:: color)
        app.clear();//every loop we draw in a screen is basically a frame it clears it
       app.draw(backGTopRec);
       app.draw(backGBotRec);
       app.draw(backGLeftRec);
       app.draw(backGRightRec);
       app.draw(middlecircle);
       app.draw(middlerec);
       app.draw(score1);
       app.draw(score2);
       app.draw(player1Name);
       app.draw(player2Name);
       player1.update(app);
       player2.update(app);
       cBall.update(app);
       if(winCon1==true)
       app.draw(win1);
       else if(winCon2==true)
        app.draw(win2);


        // end the current frame
        app.display();

    }




}


