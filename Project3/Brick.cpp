#include "pch.h"
#include "Brick.h"

void Brick::initShape(int health)
{
	this->shape.setSize(sf::Vector2f(50.f, 20.f));
	if (health == 1)
		this->shape.setFillColor(sf::Color::Blue);
	else if (health == 2)
		this->shape.setFillColor(sf::Color::Red);

}

void Brick::initVar(int health)
{
	this->health = health;
}

void Brick::initPos(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
}

Brick::Brick(sf::Vector2f pos,int health)
{
	this->initShape(health);
	this->initPos(pos);
	this->initVar(health);
}

Brick::~Brick()
{
}

sf::RectangleShape Brick::getShape()
{
	return this->shape;
}

int Brick::getHealth()
{
	return this->health;
}

void Brick::decreaseHealth()
{
	this->health--;
}

void Brick::update()
{
	//this->health--;
	if (this->health == 1)
		this->shape.setFillColor(sf::Color::Blue);
}

void Brick::render(sf::RenderTarget* window)
{
	window->draw(this->shape);
}
