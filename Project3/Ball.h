#pragma once
#include "Paddle.h"

class Ball
{
private:
	// variable
	sf::CircleShape shape;
	bool isAttach;
	bool isIngame;
	sf::Vector2f speed;
	float positionOnPaddle;
	float speedOnPaddle;


	//private funtion
	void initShape();
	void initPos(sf::Vector2f pos);
	void initVar(bool condition);

public:
	//constructor / destructor
	Ball(sf::Vector2f pos, bool condtion);
	virtual ~Ball();

	//accessor
	bool inGame();
	sf::CircleShape getShape();
	bool isShooted();

	//function
	void modifySpeed(float x, float y);
	void changeSpeed(int x,int y);
	void BouncePaddle(Paddle paddle);
	void rollOnPaddle(Paddle paddle);
	void updateCollision();
	void shoot(Paddle paddle);
	void update(sf::Vector2f pos, bool isShoot,Paddle paddle);
	void render(sf::RenderTarget *window);
};

