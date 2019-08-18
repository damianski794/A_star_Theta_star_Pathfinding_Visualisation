#pragma once
#include <array>
#include "window_dimensions.h"
#include "Node.h"
void config1_2collumns(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) {
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;
			//mapka[i][j].shape.setFillColor(sf::Color::Blue);
		}
	}
	if (Y_MAX / Y_STEP > 10 &&  X_MAX/X_STEP > 15) {
		for (int i = 0; i < X_MAX / X_STEP; i++) {
			for (int j = 0; j < (Y_MAX / Y_STEP); j++) {
				if ((i == 5 || i == 6 || i == 10 || i == 11) && j < 10)
					mapka[i][j].isObstacle = true;
			}
		}
	}
	//draw(mapka, window);
	std::cout << "wczytano config nr 1" << std::endl;
}