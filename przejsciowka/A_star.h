#pragma once

#include "window_dimensions.h"
#include "Node.h"

#include <vector>
#include <array>
#include <stack>

#include <iostream>

//using namespace std;
static std::vector<Node> makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
	try {
		std::cout << "Found a path" << std::endl;
		int x = dest.x;
		int y = dest.y;
		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

static std::vector<Node> aStar(Node player, Node dest) {
	std::vector<Node> empty;
	if (isValid(dest.x, dest.y) == false) {
		std::cout << "Destination is an obstacle" << std::endl;
		return empty;
		//Destination is invalid
	}
	if (isDestination(player.x, player.y, dest)) {
		std::cout << "You are the destination" << std::endl;
		return empty;
		//You clicked on yourself
	}
	bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

	//Initialize whole map
	//Node allMap[50][25];
	std::array<std::array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
	for (int x = 0; x < (X_MAX / X_STEP); x++) {
		for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	//Initialize our starting list
	int x = player.x;
	int y = player.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
		Node node;
		do {
			//This do-while loop could be replaced with extracting the first
			//element from a set, but you'd have to make the openList a set.
			//To be completely honest, I don't remember the reason why I do
			//it with a vector, but for now it's still an option, although
			//not as good as a set performance wise.
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); it = next(it)) {
				Node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (isValid(node.x, node.y) == false);

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		//For each neighbour starting from North-West to South-East
		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (isValid(x + newX, y + newY)) {
					if (isDestination(x + newX, y + newY, dest))
					{
						//Destination found - make path
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;
						return makePath(allMap, dest);
					}
					else if (closedList[x + newX][y + newY] == false)
					{
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						// Check if this path is better than the one already present
						if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
							allMap[x + newX][y + newY].fCost > fNew)
						{
							// Update the details of this neighbour node
							allMap[x + newX][y + newY].fCost = fNew;
							allMap[x + newX][y + newY].gCost = gNew;
							allMap[x + newX][y + newY].hCost = hNew;
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false) {
		std::cout << "Destination not found" << std::endl;
		return empty;
	}
}


//zmienilem std::vector<Node> na void na czas testowania
static void my_A_Star(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

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
			mapka[i][j].hCost = my_calcutateH(mapka[i][j],destination_Node); //zmienilem z FLT_MAX
			mapka[i][j].parentX = -1;
			mapka[i][j].parentY = -1; 

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
	std::cout << "rozmiar openList przed emplace = " <<openList.size()<< std::endl;
	openList.emplace_back(mapka[i][j]);
	std::cout << "rozmiar openList po emplace = " << openList.size() << std::endl;
	bool destination_found = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
		std::cout << "wewnatrz glownej petli !openList.empty() && openList.size()" << std::endl;
		Node node;
		do {
			float temp = FLT_MAX;
			std::cout << "za temp = flt_max" << std::endl;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); ++it) { //zamiast next(it) biore ++it
				std::cout << "wewnatrz iteratora" << std::endl;
				Node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
			std::cout << "wewnatrz do while(my_isValid(node) == false) " << std::endl;
		} while (my_isValid(node) == false);

		i = node.x;
		j = node.y;
		closedList[i][j] = true;
		std::cout << "przed sasiednimi nodami" << std::endl;
		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				std::cout << "sprawdzam sasiadow"<< std::endl;
				if (my_isValid_xy(i + newX, j + newY, mapka)) {

					//pokazujemy, ktore nody sa sprawdzane
					mapka[i + newX][j + newY].shape.setFillColor(sf::Color::Magenta);
					window.draw(mapka[i + newX][j + newY].shape);
					window.display();

					if (my_isDestination(mapka[i + newX][j + newY], destination_Node)) {
						mapka[i + newX][j + newY].parentX = i;
						mapka[i + newX][j + newY].parentY = j;
						destination_found = true;
						std::cout << "znaleziono droge!!!" << std::endl << std::endl;

						//return makePath(mapka, destination_Node); zmienilem
						return;
					}

					else if (closedList[i + newX][j + newY] == false) {
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

void testowane(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node) {
	std::cout <<" mapka[5][5].isObstacle: "<< mapka[5][5].isObstacle << std::endl;
	std::cout << "current_Node.x: " << current_Node.x << std::endl;
	std::cout << "current_Node.y: " << current_Node.y << std::endl;
	std::cout << "destination_Node.x: " << destination_Node.x << std::endl;
	std::cout << "destination_Node.y: " << destination_Node.y << std::endl;
	std::cout << std::endl;
}