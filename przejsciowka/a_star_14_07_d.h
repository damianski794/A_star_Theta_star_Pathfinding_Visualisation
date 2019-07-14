#pragma once

#include "A_star.h"
#include "window_dimensions.h"
#include "Node.h"
#include <vector>
#include <array>

static void a_star_rzezba(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

	if (current_Node.x == destination_Node.x && current_Node.y == destination_Node.y) {
		std::cout << "you are at the destination" << std::endl;
		return;
	}
	if (destination_Node.isObstacle == true) {
		std::cout << "destination is an obstacle" << std::endl;
	}
	
	bool closeSet[X_MAX / X_STEP][Y_MAX / Y_STEP];
	
	for (int i = 0; i < (X_MAX / X_STEP); i++) {
		for (int j = 0; j < (Y_MAX / Y_STEP); j++) {
			mapka[i][j].fCost = FLT_MAX;
			mapka[i][j].gCost = FLT_MAX;
			mapka[i][j].hCost = my_calcutateH(mapka[i][j], destination_Node); //zmienilem z FLT_MAX
			mapka[i][j].parentX = -1;
			mapka[i][j].parentY = -1;

			mapka[i][j].x = i;
			mapka[i][j].y = j;

			closeSet[i][j] = false;
			
		}
	}
	std::vector<Node> openset;
	mapka[current_Node.x][current_Node.y].gCost = 0;
	mapka[current_Node.x][current_Node.y].fCost = 0; //uwaga, moze byc bez sensu
	openset.emplace_back(mapka[current_Node.x][current_Node.y]);

	//current_Node.gCost = 0;
	mapka[current_Node.x][current_Node.y].gCost = 0;
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; //pamietaj zeby zmienic na to co wyzzej
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;
	
	//bool found_path = false;
	
	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger); //usuwam r wszedzie
		std::cout << "rozmiar openset" << openset.size() << std::endl;
		Node node = *openset.rbegin(); //bylo wczesniej rbegin()

		/*for (auto it = openset.begin(); it != openset.end();it++) {
			std::cout << "Rozmiar opeset:"<<openset.size() << std::endl;
			std::cout << "G: " << it->gCost << std::endl;
		}*/
		

		if (isDestination(node.x, node.y, destination_Node)) {
			std::cout << "this is the destination" << std::endl;
			return;
		}
		openset.pop_back(); //drop the last element
		//std::cout << "rozmiar openset" << openset.size() << std::endl;
		closeSet[node.x][node.y] = true;
		
		int i = node.x;
		int j = node.y;
		
		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				
				if (my_isValid_xy(i + newX, j + newY, mapka) == true) {
					mapka[i + newX][j + newY].shape.setFillColor(sf::Color::Magenta);
					window.draw(mapka[i + newX][j + newY].shape);
					window.display();
					int i_new = i + newX;
					int j_new = j + newY;
					//std::cout << "Checking Node: (" << i_new << "," << j_new<<")" << std::endl;

					//std::cout << "wartosc closeset: " << closeSet[i_new][j_new] << std::endl;
					if (my_isDestination(mapka[i_new][j_new], destination_Node) == true) {
						std::cout << "you are at the destination, a_star found path" << std::endl;
						return;
					}
					else if (closeSet[i_new][j_new] == false) {
						float Fnew;

						float dist_beetween_node_and_adjastend;
						if ((newX == -1 && newY == -1) || (newX == -1 && newY == 1) || (newX == 1 && newY == -1) || (newX == 1 && newY == 1)) {
							dist_beetween_node_and_adjastend = 1.4f;
						}
						else {
							dist_beetween_node_and_adjastend = 1.0f;
						}
						float tentative_g_score = node.gCost + dist_beetween_node_and_adjastend;
						std::cout << "tentative_g_score: " << tentative_g_score << std::endl;
						bool tentative_is_better = false;
						bool is_in_openset = false;

						for (auto it = openset.rbegin(); it != openset.rend(); ++it) { //sprawdzam czy sprawdzany node nie jest w openSet
							if (*it == mapka[i_new][j_new]) {
								is_in_openset = true;
								//break;
							}
						}
						//std::cout << "is_in_openset: 1=tak, 0=nie: " << is_in_openset << std::endl;
						//if (is_in_openset == true) {
							//std::cout << "node jest juz   w openset" << std::endl;
						//}
						if (is_in_openset == false) {
							openset.emplace_back(mapka[i_new][j_new]);
							//std::cout << "dodano element" << std::endl;
							mapka[i_new][j_new].hCost = my_calcutateH(mapka[i_new][j_new], destination_Node);
							tentative_is_better = true;
						}
						else if(tentative_g_score < mapka[i_new][j_new].gCost){
							tentative_is_better = true;
						}

						if (tentative_is_better) {
							mapka[i_new][j_new].parentX = node.x;
							mapka[i_new][j_new].parentY = node.y;
							mapka[i_new][j_new].gCost = tentative_g_score;
							mapka[i_new][j_new].fCost = mapka[i_new][j_new].gCost + mapka[i_new][j_new].hCost;
						}
						
					}

				}
			}
		}
		std::cout << "ROZMIAR openset na koniec petli: " << openset.size() << std::endl;

	}

	std::cout << "BRAK SCIEZKI" << std::endl;
	return;
}



static void a_star_rzezba_bede_kombinowal_z_heurystyka(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

	if (current_Node.x == destination_Node.x && current_Node.y == destination_Node.y) {
		std::cout << "you are at the destination" << std::endl;
		return;
	}
	if (destination_Node.isObstacle == true) {
		std::cout << "destination is an obstacle" << std::endl;
	}

	bool closeSet[X_MAX / X_STEP][Y_MAX / Y_STEP];

	for (int i = 0; i < (X_MAX / X_STEP); i++) {
		for (int j = 0; j < (Y_MAX / Y_STEP); j++) {
			//mapka[i][j].fCost = FLT_MAX; f cost ustawiam jako nieznane
			mapka[i][j].gCost = FLT_MAX;
			mapka[i][j].hCost = my_calcutateH(mapka[i][j], destination_Node); //zmienilem z FLT_MAX
			mapka[i][j].parentX = -1;
			mapka[i][j].parentY = -1;

			mapka[i][j].x = i;
			mapka[i][j].y = j;

			closeSet[i][j] = false;

		}
	}
	std::vector<Node> openset;
	mapka[current_Node.x][current_Node.y].gCost = 0;
	//mapka[current_Node.x][current_Node.y].fCost = 0; //uwaga, moze byc bez sensu
	openset.emplace_back(mapka[current_Node.x][current_Node.y]);

	//current_Node.gCost = 0;
	mapka[current_Node.x][current_Node.y].gCost = 0;
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; //pamietaj zeby zmienic na to co wyzzej
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;

	//bool found_path = false;

	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger); //usuwam r wszedzie
		std::cout << "rozmiar openset" << openset.size() << std::endl;
		Node node = openset.back(); //bylo wczesniej rbegin()

		/*for (auto it = openset.begin(); it != openset.end();it++) {
			std::cout << "Rozmiar opeset:"<<openset.size() << std::endl;
			std::cout << "G: " << it->gCost << std::endl;
		}*/


		if (isDestination(node.x, node.y, destination_Node)) {
			std::cout << "this is the destination" << std::endl;
			return;
		}
		openset.pop_back(); //drop the last element
		//std::cout << "rozmiar openset" << openset.size() << std::endl;
		closeSet[node.x][node.y] = true;

		int i = node.x;
		int j = node.y;

		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {

				if (my_isValid_xy(i + newX, j + newY, mapka) == true) {
					mapka[i + newX][j + newY].shape.setFillColor(sf::Color::Magenta);
					window.draw(mapka[i + newX][j + newY].shape);
					window.display();
					int i_new = i + newX;
					int j_new = j + newY;
					//std::cout << "Checking Node: (" << i_new << "," << j_new<<")" << std::endl;

					//std::cout << "wartosc closeset: " << closeSet[i_new][j_new] << std::endl;
					if (my_isDestination(mapka[i_new][j_new], destination_Node) == true) {
						std::cout << "you are at the destination, a_star found path" << std::endl;
						return;
					}
					else if (closeSet[i_new][j_new] == false) {
						float Fnew; //dodane

						float dist_beetween_node_and_adjastend;
						if ((newX == -1 && newY == -1) || (newX == -1 && newY == 1) || (newX == 1 && newY == -1) || (newX == 1 && newY == 1)) {
							dist_beetween_node_and_adjastend = 1.4f;
						}
						else {
							dist_beetween_node_and_adjastend = 1.0f;
						}
						float tentative_g_score = node.gCost + dist_beetween_node_and_adjastend;

						Fnew = tentative_g_score + mapka[i_new][j_new].hCost;
						std::cout << "tentative_g_score: " << tentative_g_score << std::endl;
						bool tentative_is_better = false;
						bool is_in_openset = false;

						for (auto it = openset.rbegin(); it != openset.rend(); ++it) { //sprawdzam czy sprawdzany node nie jest w openSet
							if (*it == mapka[i_new][j_new]) {
								is_in_openset = true;
								//break;
							}
						}
						//std::cout << "is_in_openset: 1=tak, 0=nie: " << is_in_openset << std::endl;
						//if (is_in_openset == true) {
							//std::cout << "node jest juz   w openset" << std::endl;
						//}
						if (is_in_openset == false) {
							//std::cout << "dodano element" << std::endl;
							mapka[i_new][j_new].hCost = my_calcutateH(mapka[i_new][j_new], destination_Node);
							mapka[i_new][j_new].fCost = Fnew;
							mapka[i_new][j_new].gCost = tentative_g_score;
							tentative_is_better = true;
							openset.emplace_back(mapka[i_new][j_new]);
						}
						else if (tentative_g_score < mapka[i_new][j_new].gCost) {
							tentative_is_better = true;
						}

						if (tentative_is_better) {
							mapka[i_new][j_new].parentX = node.x;
							mapka[i_new][j_new].parentY = node.y;
							mapka[i_new][j_new].gCost = tentative_g_score;
							mapka[i_new][j_new].fCost = mapka[i_new][j_new].gCost + mapka[i_new][j_new].hCost;
						}

					}

				}
			}
		}
		std::cout << "ROZMIAR openset na koniec petli: " << openset.size() << std::endl;

	}

	std::cout << "BRAK SCIEZKI" << std::endl;
	return;
}