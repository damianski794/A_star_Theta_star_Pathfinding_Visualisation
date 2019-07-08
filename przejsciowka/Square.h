#pragma once
#include "SFML/Graphics.hpp"
#include "window_dimensions.h"
class Square:public sf::Drawable {
private:
	int square_size = X_STEP;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const	override;
protected:
	int x_square, y_square;
public:
	Square(int x,int y);
	sf::RectangleShape shape;
	
};

inline void Square::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->shape, states);
}

Square::Square(int x,int y) {
	x_square = x;
	y_square = y;

	shape.setOrigin(square_size / 2.f, square_size / 2.f);
	shape.setSize(sf::Vector2f{ float(square_size),float(square_size) });
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5.f);
	shape.setPosition(sf::Vector2f{ float(0.5*square_size + x * square_size),float(0.5*square_size + y * square_size) });
}