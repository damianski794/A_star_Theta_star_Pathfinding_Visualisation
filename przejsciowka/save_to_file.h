#pragma once
#include "map_configurations.h"
#include <iostream>
#include <fstream>
void save_to_file(std::string file_name, std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka) {
	file_name = "../konfiguracje/" + file_name;
	std::ofstream zapis;
	zapis.open(file_name);
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			if (mapka[i][j].isObstacle == true) {
				zapis << "mapka[" << i << "][" << j << "].isObstacle = true;" << std::endl;
			}
			else {
				zapis << "mapka[" << i << "][" << j << "].isObstacle = false;" << std::endl;
			}
		}
	}
	std::cout << "tu jestem" << std::endl;
	zapis.close();
}