#include "pch.h"
#include "Game.h"
using namespace std;

void Game::initVar()
{
	this->window = nullptr;
	
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "gaming", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//constructor
Game::Game()
{
	this->initVar();
	this->initWindow();
}

//destructor
Game:: ~Game()
{
	delete this->window;
}

//acessor
const bool Game::running() const
{
	return this->window->isOpen();
}

//function
void Game::pollevent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

Ball RandABall(Ball sourceBall) {
	Ball cur1 = sourceBall;
	float y = rand() % 6 + 1; y *= -1;
	float x = sqrt(50 - y * y);
	cur1.modifySpeed(x, y);
	return cur1;
}

void Game::spawmBall()
{
	if (this->ligma.size() >= 2) return;
	if (this->ligma.empty())
	{
		Ball ball(this->paddle.getShape().getPosition(), 1);
		this->ligma.push_back(ball);
	}
	else 
	{
		cout << "?";
		Ball cur = this->ligma[0];
		if (cur.isShooted()) {
			this->ligma.push_back(RandABall(cur));
			//this->ligma.push_back(RandABall(cur));
		}
		
	}

}

void Game::updateBall()
{
	this->spawmBall();
	vector<Ball> tmp;
	for (auto& i : this->ligma)
	{
		i.update(this->paddle.getShape().getPosition(), sf::Keyboard::isKeyPressed(sf::Keyboard::Space),this->paddle);
		if (i.inGame()) tmp.push_back(i);
	}
	this->ligma = tmp;
}

void Game::renderBall()
{
	for (auto& i : this->ligma)
		i.render(this->window);
}

void Game::spawnBrick()
{
	if (this->brick.size()) return;
	int redBrick = 10;
	for (int i = 0; i < 10; i++)
	{
		int health = 1;
		int rd = rand() % 2;
		if (redBrick && rd) health = 2, redBrick--;
		Brick tmp(sf::Vector2f(100.f + 55*i, 100.f),health);
		this->brick.push_back(tmp);

		health = 1;
		rd = rand() % 2;
		if (redBrick && rd) health = 2, redBrick--;
		Brick tmp2(sf::Vector2f(100.f + 55 * i, 130.f),health);
		this->brick.push_back(tmp2);

		health = 2;
		Brick tmp3(sf::Vector2f(100.f + 55 * i, 250.f), health);
		this->brick.push_back(tmp3);
	}
	
}

void Game::updateBrick()
{
	vector<Brick> tmp;
	for (auto& i : this->brick)
	{
		i.update();
		if (i.getHealth()) tmp.push_back(i);
	}
	this->brick = tmp;
}

void Game::renderBrick()
{
	this->spawnBrick();
	for (auto i : this->brick)
	{
		if (i.getHealth() > 0) i.render(this->window);
	}
}

bool LineIntersect(float lf1, float rg1, float lf2, float rg2)
{
	return ((lf1 <= lf2 && lf2 <= rg1) || (lf2 <= lf1 && lf1 <= rg2));
}

void Game::CheckBallBrickCollision()
{
	for (auto& i : this->ligma) 
	{
		for (auto& j : this->brick)
		{
			if (!j.getHealth()) continue;
			sf::Vector2f posBall = i.getShape().getPosition();
			sf::Vector2f UpperBrick = j.getShape().getPosition();
			sf::Vector2f LowerBrick = 
				sf::Vector2f (UpperBrick.x + j.getShape().getSize().x, UpperBrick.y + j.getShape().getSize().y);
			float upperBall = posBall.y - i.getShape().getRadius();
			float lowerBall = posBall.y + i.getShape().getRadius();
			float leftBall = posBall.x - i.getShape().getRadius();
			float rightBall = posBall.x + i.getShape().getRadius();



			bool changed = 0;

			if (LineIntersect(UpperBrick.x,LowerBrick.x,leftBall,rightBall))
			{
				//cout << "1 " << upperBall << " " << LowerBrick.y << " x " << lowerBall << " " << UpperBrick.y << "\n";
				if (abs(upperBall - LowerBrick.y) <= 8.0 || abs(lowerBall - UpperBrick.y) <= 8.0) 
				{
					//exit(0);
					changed = 1;
					i.changeSpeed(1, -1), j.decreaseHealth();
				}
					
			}

			if (LineIntersect(UpperBrick.y,LowerBrick.y,upperBall,lowerBall))
			{
				//cout << "2 " << rightBall << " " << UpperBrick.x << " x " << leftBall << " " << LowerBrick.x << "\n";
				if (abs(rightBall - UpperBrick.x) <= 8.0 || abs(leftBall - LowerBrick.x) <= 8.0)
				{
					//cout << "?\n";
					i.changeSpeed(-1, 1), j.decreaseHealth();
				}
					
			}

		}
	}
}


void Game::update()
{
	
	this->pollevent();
	this->CheckBallBrickCollision();
	this->paddle.update(this->window);
	this->updateBall();
	this->updateBrick();
}


void Game::render()
{
	this->window->clear();

	//Draw game object
	this->paddle.render(this->window);
	this->renderBall();
	this->renderBrick();

	this->window->display();
}

