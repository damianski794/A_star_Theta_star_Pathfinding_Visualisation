#include "pch.h"
#include "Ball.h"

Ball::Ball(float x, float y)
{
	shape.setPosition(x, y);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(this->ballRadius, this->ballRadius);
}

float Ball::right()
{
	return shape.getPosition().x + shape.getRadius();
}
float Ball::left()
{
	return shape.getPosition().x - shape.getRadius();
}
float Ball::top()
{
	return shape.getPosition().y - shape.getRadius();
}
float Ball::bottom()
{
	return shape.getPosition().y + shape.getRadius();
}
void Ball::update()
{
	shape.move(this->velocity);

	if (top() < 0)
		velocity.y = ballVelocity;
	if (bottom() > 600)
		velocity.y = -ballVelocity;
	if (left() < 0)
		velocity.x = ballVelocity;
	if (right() > 800)
		velocity.x = -ballVelocity;
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}
