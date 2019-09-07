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

void config2(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) {
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;
			
		}
	}

	for (int i = 0; i < 23; i++) {
		mapka[i][3].isObstacle = true;
	}

	for (int i = 12; i < 30; i++) {
		mapka[i][13].isObstacle = true;
	}

	for (int j = 0; j < 13; j++) {
		mapka[29][j].isObstacle = true;
	}
	std::cout << "wczytano config nr 2" << std::endl;
}
void config3(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) {
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;

		}
	}

	for (int i = 0; i < 23; i++) {
		mapka[i][4].isObstacle = true;
	}

	for (int i = 12; i < 30; i++) {
		mapka[i][11].isObstacle = true;
	}

	for (int j = 0; j < 13; j++) {
		mapka[29][j].isObstacle = true;
	}

	for (int j = 12; j < 19; j++) {
		mapka[12][j].isObstacle = true;
		mapka[5][j].isObstacle = true;
	}
	
	for (int i = 5; i < 13; i++) {
		mapka[i][18].isObstacle = true;
	}

	std::cout << "wczytano config nr 3" << std::endl;

	std::cout << "na tym configu theta nie ogarnia" << std::endl;
}