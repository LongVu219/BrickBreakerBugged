#include "pch.h"
#include "Paddle.h"

//private function
void Paddle::initShape()
{
	this->shape.setSize(sf::Vector2f(100.f, 10.f));
	this->shape.setFillColor(sf::Color::Red);
}

void Paddle::initPos()
{
	this->shape.setOrigin(sf::Vector2f(this->shape.getSize().x / 2, 0.f));
	this->shape.setPosition(sf::Vector2f(400.f, 500.f));
}

void Paddle::initVar()
{
	this->speed = 5.f;
}


//constructor / destructor
Paddle::Paddle()
{
	this->initShape();
	this->initPos();
	this->initVar();
}

Paddle::~Paddle()
{

}

sf::RectangleShape Paddle::getShape()
{
	return this->shape;
}

bool Paddle::checkBound(sf::RenderWindow *window)
{
	float x = this->shape.getPosition().x;
	if (x + this->shape.getSize().x / 2 > window->getSize().x) 
		return 1;
	if (x - this->shape.getSize().x / 2 < 0.f)
		return 1;
	return 0;
}

//function
void Paddle::movement(sf::RenderWindow *window)
{	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->speed, 0.f);
		if (this->checkBound(window))
			this->shape.move(this->speed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->speed, 0.f);
		if (this->checkBound(window))
			this->shape.move(-this->speed, 0.f);
	}


}

void Paddle::update(sf::RenderWindow *window)
{
	this->movement(window);
}

void Paddle::render(sf::RenderTarget *window)
{
	window->draw(this->shape);
}


