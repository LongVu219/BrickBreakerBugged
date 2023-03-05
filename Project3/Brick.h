#pragma once
class Brick
{
private:
	sf::RectangleShape shape;
	int health;

	void initShape(int health);
	void initVar(int health);
	void initPos(sf::Vector2f pos);

public:
	//constructor / destructor
	Brick(sf::Vector2f pos,int health);
	virtual ~Brick();
	
	//accessor
	
	sf::RectangleShape getShape();
	int getHealth();

	//function
	void decreaseHealth();
	void update();
	void render(sf::RenderTarget *window);

};

