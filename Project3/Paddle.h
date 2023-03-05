#pragma once
class Paddle
{
private:
	//variable
	sf::RectangleShape shape;
	float speed;

	//private funtion
	void initShape();
	void initPos();
	void initVar();

public:
	//constructor / destructor
	Paddle();
	virtual ~Paddle();
	
	//accessor
	sf::RectangleShape getShape();

	//function
	bool checkBound(sf::RenderWindow *window);
	void movement(sf::RenderWindow *window);
	void update(sf::RenderWindow *window);
	void render(sf::RenderTarget *window);
	
};

