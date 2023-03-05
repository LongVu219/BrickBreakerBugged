#include "pch.h"
#include "Ball.h"


//private function
void Ball::initShape()
{
	this->shape.setRadius(5.f);
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1);
}

void Ball::initPos(sf::Vector2f pos)
{
	float rad = this->shape.getRadius();
	this->shape.setOrigin(rad, rad);
	this->shape.setPosition(pos);
}

void Ball::initVar(bool condition)
{
	this->isAttach = condition;
	this->speed = sf::Vector2f(0.f, 0.f);
	this->isIngame = 1;
	this->positionOnPaddle = 0;
	this->speedOnPaddle = 1;
}

//constructor / destructoe
Ball::Ball(sf::Vector2f pos, bool condition)
{
	this->initShape();
	this->initPos(pos);
	this->initVar(condition);
}

Ball::~Ball()
{

}

bool Ball::inGame()
{
	return this->isIngame;
}

sf::CircleShape Ball::getShape()
{
	return this->shape;
}

bool Ball::isShooted()
{
	return !this->isAttach;
}

//function
void Ball::shoot(Paddle paddle)
{
	this->isAttach = 0;
	sf::Vector2f pos = this->shape.getPosition();
	float x = pos.x - paddle.getShape().getPosition().x; x /= 10.0;
	//cout << "? " << x * x<< "\n";
	float y = sqrt(50 - x * x);
	this->speed = sf::Vector2f(x,-y);
}

void Ball::modifySpeed(float x, float y)
{
	this->speed.x = x;
	this->speed.y = y;
}

void Ball::changeSpeed(int x, int y)
{
	this->speed.x *= x;
	this->speed.y *= y;
}

void Ball::BouncePaddle(Paddle paddle)
{
	sf::Vector2f posPaddle = paddle.getShape().getPosition();
	sf::Vector2f posBall = this->shape.getPosition();
	if (abs(posBall.y + this->shape.getRadius() - posPaddle.y) <= 5.0 && posPaddle.x - 50 <= posBall.x
		&& posBall.x <= posPaddle.x + 50) this->shoot(paddle);
}

void Ball::rollOnPaddle(Paddle paddle)
{
	float paddleLeft = paddle.getShape().getPosition().x - 50;
	float paddleRight = paddle.getShape().getPosition().x + 50;
	float ballLeft = this->shape.getPosition().x - this->shape.getRadius();
	float ballRight = this->shape.getPosition().x + this->shape.getRadius();
	//cout << ballLeft << " " << ballRight << " "<< this->positionOnPaddle<<"\n";
	if (ballLeft <= paddleLeft || ballRight >= paddleRight) this->speedOnPaddle *= -1;
	this->positionOnPaddle += this->speedOnPaddle;
	
}

void Ball::updateCollision()
{
	sf::Vector2f pos = this->shape.getPosition();
	//std::cout << pos.x << " " << pos.y << "\n";
	float upperX = pos.x - this->shape.getRadius(), upperY = pos.y - this->shape.getRadius();
	float lowerX = pos.x + this->shape.getRadius(), lowerY = pos.y + this->shape.getRadius();
	//std::cout << upperX << " " << upperY << " " << lowerX << " " << lowerY << "\n";
	if (upperX <= 0) this->speed.x *= -1;
	else if (upperY <= 0) this->speed.y *= -1;
	else if (lowerX >= 800) this->speed.x *= -1;
	else if (lowerY >= 600) this->isIngame = 0;
}

void Ball::update(sf::Vector2f pos, bool isShoot,Paddle paddle)
{
	//cout << this->shape.getPosition().x << " " << this->shape.getPosition().y << "\n";
	if (isShoot && this->isAttach) this->shoot(paddle);
	if (this->isAttach)
	{
		this->rollOnPaddle(paddle);
		this->shape.setPosition(pos.x + this->positionOnPaddle, pos.y - this->shape.getRadius());
	}
	else 
	{
		this->shape.move(this->speed);
		this->updateCollision();
		this->BouncePaddle(paddle);
	}
}



void Ball::render(sf::RenderTarget* window)
{
	window->draw(this->shape);
}

