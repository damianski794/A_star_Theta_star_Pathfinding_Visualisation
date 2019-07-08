#pragma once
#include "SFML/Graphics.hpp"
#include "window_dimensions.h"
#include <array>
class Map:public sf::Drawable
{
private:
	int width_;
	int height_;
	int square_size_;
public:
	Map(int width, int height,int square_size);




};

