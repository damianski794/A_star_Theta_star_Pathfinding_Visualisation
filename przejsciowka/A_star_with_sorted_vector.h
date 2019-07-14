#pragma once
#include "A_star.h"
#include "Node.h"
#include <iostream>



static void my_A_Star_with_sorted_vector(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

	//std::cout << "test" << std::endl;
	std::vector<Node> empty;// return empty;
	if (my_isValid(destination_Node) == false) {
		std::cout << "destination is an obstacle, returning empty path" << std::endl;
		//return empty; zmienilem
		return;
	}
	if (my_isDestination(current_Node, destination_Node)) {
		std::cout << "you are at the destination, returning empty path" << std::endl;
		return;
		//return empty; //zmienilem
	}


	bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];
	//std::cout << "coping all" << std::endl;
	//std::array<std::array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap = mapka; //zmienic
	//std::cout << "all copied" << std::endl;
	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].fCost = FLT_MAX;
			mapka[i][j].gCost = FLT_MAX;
			mapka[i][j].hCost = my_calcutateH(mapka[i][j], destination_Node); //zmienilem z FLT_MAX
			mapka[i][j].parentX = i;
			mapka[i][j].parentY = j;

			closedList[i][j] = false;
		}
	}

	int i = current_Node.x;
	int j = current_Node.y;

	mapka[i][j].fCost = 0;
	mapka[i][j].gCost = 0;
	mapka[i][j].hCost = 0;
	mapka[i][j].parentX = i;
	mapka[i][j].parentY = j;

	std::vector<Node> openList;
	std::cout << "rozmiar openList przed emplace = " << openList.size() << std::endl;
	openList.emplace_back(mapka[i][j]);
	std::cout << "rozmiar openList po emplace = " << openList.size() << std::endl;
	bool destination_found = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
		std::cout << "wewnatrz glownej petli !openList.empty() && openList.size()" << std::endl;
		std::sort(openList.rbegin(), openList.rend(),compareNode);
		Node node;
		//do {
		//	float temp = FLT_MAX;
		//	std::cout << "za temp = flt_max" << std::endl;
		//	std::vector<Node>::iterator itNode;
		//	for (std::vector<Node>::iterator it = openList.begin();
		//		it != openList.end(); ++it) { //zamiast next(it) biore ++it
		//		std::cout << "wewnatrz iteratora" << std::endl;
		//		Node n = *it;
		//		if (n.fCost < temp) {
		//			temp = n.fCost;
		//			itNode = it;
		//		}
		//	}
		//	node = *itNode;
		//	openList.erase(itNode);
		//	std::cout << "wewnatrz do while(my_isValid(node) == false) " << std::endl;
		//} while (my_isValid(node) == false);
		node = *openList.rbegin();
		openList.pop_back();

		i = node.x;
		j = node.y;
		closedList[i][j] = true;
		std::cout << "przed sasiednimi nodami" << std::endl;
		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				std::cout << "sprawdzam sasiadow" << std::endl;
				if (my_isValid_xy(i + newX, j + newY, mapka)) {
					// BY ZOBACZYC SPRAWDZANE NODY ODKOMENTUJ PONI
					//pokazujemy, ktore nody sa sprawdzane
					mapka[i + newX][j + newY].shape.setFillColor(sf::Color::Magenta);
					window.draw(mapka[i + newX][j + newY].shape);
					window.display();

					if (my_isDestination(mapka[i + newX][j + newY], destination_Node)) {
						mapka[i + newX][j + newY].parentX = i;
						mapka[i + newX][j + newY].parentY = j;
						destination_found = true;
						std::cout << "znaleziono droge!!!" << std::endl << "a jest ona taka:" << std::endl;

						draw_path(mapka, mapka[i + newX][j + newY], window);

						//return makePath(mapka, destination_Node); zmienilem
						return;
					}

					else if (closedList[i + newX][j + newY] == false) {
						if ((newX == -1 && newY == -1) || (newX == -1 && newY == 1) || (newX == 1 && newY == -1) || (newX == 1 && newY == 1))
							gNew = node.gCost + 1.4;
						else
							gNew = node.gCost + 1;
						hNew = my_calcutateH(mapka[i + newX][j + newY], destination_Node);
						fNew = gNew + hNew;

						if (mapka[i + newX][j + newY].fCost == FLT_MAX || mapka[i + newX][j + newY].fCost > fNew) {
							mapka[i + newX][j + newY].fCost = fNew;
							mapka[i + newX][j + newY].gCost = gNew;
							mapka[i + newX][j + newY].hCost = hNew;
							mapka[i + newX][j + newY].parentX = i;
							mapka[i + newX][j + newY].parentY = j;

							openList.emplace_back(mapka[i + newX][j + newY]);
						}
					}
				}
			}
		}
	}
	if (destination_found == false) {
		std::cout << "destination not found :/" << std::endl;
		//return empty; zmienilem
		return;
	}
}