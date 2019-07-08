#pragma once
#include <SFML/Graphics.hpp>
class Ball:public sf::Drawable
{
public:
	Ball(float x, float y);
	Ball() = delete;
	~Ball() = default;

	float right();
	float left();
	float top();
	float bottom();

	void update();
private:
	sf::CircleShape shape;
	const float ballRadius{ 10.0f };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	const float ballVelocity{ 4.0f };
	sf::Vector2f velocity{ this->ballVelocity,this->ballVelocity };
};

