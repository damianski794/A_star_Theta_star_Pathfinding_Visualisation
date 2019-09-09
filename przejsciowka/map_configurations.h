#pragma once
#include <array>
#include "window_dimensions.h"
#include "Node.h"

void config0(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) { //clear all
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;
		}
	}
}

void config1_2collumns(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) {
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;
			
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

//config4 godny uwagi
void config4(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) {
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;
		}
	}

	for (int i = 0; i < 31; i++) {
		mapka[i][6].isObstacle = true;
	}
	for (int i = 25; i < 35; i++) {
		mapka[i][11].isObstacle = true;
	}
	for (int j=0; j < 12; j++) {
		mapka[35][j].isObstacle = true;
	}
	for (int j = 11; j < 16; j++) {
		mapka[25][j].isObstacle = true;
	}
}

//config 5 //jak sie uda odtworzyc to bedzie supcio
void config5(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, sf::RenderWindow& window) {
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].isObstacle = false;
		}
	}

	//pionowe linie od lewej:
	for (int j = 0; j < 21; j++) {
		mapka[7][j].isObstacle = true;
	}
	for (int j = 9; j < 18; j++) {
		mapka[12][j].isObstacle = true;
	}
	for (int j = 1; j <= 9; j++) {
		mapka[13][j].isObstacle = true;
	}
	for (int j = 17; j <= 22; j++) {
		mapka[13][j].isObstacle = true;
	}
	for (int j = 9; j <= 14; j++) {
		mapka[16][j].isObstacle = true;
	}
	for (int j = 20; j <= 22; j++) {
		mapka[19][j].isObstacle = true;
	}
	for (int j = 0; j <= 11; j++) {
		if(j==6 || j==7)
			mapka[24][j].isObstacle = false;
		else
			mapka[24][j].isObstacle = true;
	}
	for (int j = 5; j <= 12; j++) {
		if (j == 9 || j == 10)
			mapka[25][j].isObstacle = false;
		else 
			mapka[25][j].isObstacle = true;
	}
	for (int j = 12; j <= 20; j++) {
		mapka[29][j].isObstacle = true;
	}
	for (int j = 0; j <= 17; j++) {
		mapka[34][j].isObstacle = true;
	}
	for (int j = 21; j <= 23; j++) {
		mapka[42][j].isObstacle = true;
	}

	//poziomo od gory

	for (int i = 13; i <= 21; i++) {
		mapka[i][1].isObstacle = true;
	}
	for (int i = 17; i <= 25; i++) {
		mapka[i][8].isObstacle = true;
	}
	for (int i = 25; i <= 30; i++) {
		mapka[i][12].isObstacle = true;
	}
	for (int i = 16; i <= 20; i++) {
		mapka[i][14].isObstacle = true;
	}
	for (int i = 12; i <= 27; i++) {
		mapka[i][17].isObstacle = true;
	}
	for (int i = 34; i <= 43; i++) {
		mapka[i][17].isObstacle = true;
	}
	for (int i = 19; i <= 30; i++) {
		mapka[i][20].isObstacle = true;
	}
	for (int i = 0; i <= 13; i++) {
		mapka[i][22].isObstacle = true;
	}
	for (int i = 29; i <= 42; i++) {
		mapka[i][23].isObstacle = true;
	}

	//pozostale punkty
	mapka[17][9].isObstacle = true;
	mapka[29][24].isObstacle = true;
}