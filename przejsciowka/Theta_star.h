#pragma once
#include "Node.h"
#include "A_star.h"

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <chrono>

float euclidean_distance(Node& current_node, Node& destination) {
	return sqrt((current_node.x - destination.x)*(current_node.x - destination.x) + (current_node.y - destination.y)*(current_node.y - destination.y));
}

bool line_of_sight(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& parent_Node, Node& adjecent_Node, sf::RenderWindow& window) {
	int x1 = parent_Node.x, y1 = parent_Node.y;
	int x2 = adjecent_Node.x, y2 = adjecent_Node.y;
	int max = std::max(abs(x1 - x2), abs(y1 - y2));
	//max = 3 * max; //chyba nie potrzeba wiekszej dokladnosci
	float t;
	float x, y;
	for (int i = 0; i <= max; i++) {
		t = float(i) / max;
		x = (x1 * (1.0 - t) + x2 * t);
		y = (y1 * (1.0 - t) + y2 * t);

		int y_new = round(y);
		int x_new = round(x);
		if (mapka[x_new][y_new].isObstacle) {
			return false;
		}

		//mapka[x_new][y_new].shape.setFillColor(sf::Color::Magenta); //wylaczone wizualizacja sprawdzanych elementow
		//window.draw(mapka[x_new][y_new].shape);
		//window.display();
		
	}
	return true;
}

void update_vertex(Node* node,Node& adjecent, std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka,bool& is_in_openset, sf::RenderWindow& window){
	if (line_of_sight(mapka, mapka[node->parentX][node->parentY], adjecent, window)) {
		
		if ((mapka[node->parentX][node->parentY].gCost + euclidean_distance(mapka[node->parentX][node->parentY], adjecent)) < adjecent.gCost) {
			adjecent.gCost = mapka[node->parentX][node->parentY].gCost + euclidean_distance(mapka[node->parentX][node->parentY], adjecent);
			adjecent.parentX = node->parentX;
			adjecent.parentY = node->parentY;

			adjecent.fCost = adjecent.gCost + adjecent.hCost;

			return;
		}
	}
	else {
		if ((node->gCost + euclidean_distance(*node, adjecent)) < adjecent.gCost) {
			adjecent.gCost = node->gCost + euclidean_distance(*node, adjecent);
			adjecent.parentX = node->x;
			adjecent.parentY = node->y;

			adjecent.fCost = adjecent.gCost + adjecent.hCost;

			return;
		}
	}
	
}



static void a_star_theta_star(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {
	auto start_time = std::chrono::high_resolution_clock::now();

	if (current_Node.x == destination_Node.x && current_Node.y == destination_Node.y) {
		std::cout << "you are at the destination" << std::endl;
		return;
	}
	if (destination_Node.isObstacle == true) {
		std::cout << "destination is an obstacle" << std::endl;
		return;
	}

	bool closeSet[X_MAX / X_STEP][Y_MAX / Y_STEP];

	for (int i = 0; i < (X_MAX / X_STEP); i++) {
		for (int j = 0; j < (Y_MAX / Y_STEP); j++) {
			mapka[i][j].fCost = 10000; //tutaj zmienilem 18.08.2019// bylo FLT_MAX
			mapka[i][j].gCost = 10000; //FLT_MAX bylo wczesniej
			mapka[i][j].hCost = my_calcutateH(mapka[i][j], destination_Node); //zmienilem z FLT_MAX
			mapka[i][j].parentX = -1;
			mapka[i][j].parentY = -1;

			mapka[i][j].x = i;
			mapka[i][j].y = j;

			closeSet[i][j] = false;

		}
	}
	current_Node.parentX = 0;
	current_Node.parentY = 0;

	std::vector<Node*> openset;
	mapka[current_Node.x][current_Node.y].gCost = 0;

	openset.push_back(&mapka[current_Node.x][current_Node.y]);

	
	mapka[current_Node.x][current_Node.y].gCost = 0;
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; 
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;

	

	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger_pointer);

		Node* node = openset.back();
		

		if (isDestination(node->x, node->y, destination_Node)) {
			
			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			std::cout << "Algorithm time (in miliseconds) is: " << double(duration.count()) / 1000 << std::endl;

			draw_path(mapka, *node, window);
			return;
		}

		//node->shape.setFillColor(sf::Color::Red);//odkomentuj zeby zobaczyc jakie nody sa aktualnie sprawdzane
		//window.draw(node->shape);
		//window.display();

		openset.pop_back();
		
		closeSet[node->x][node->y] = true;

		int i = node->x;
		int j = node->y;

		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {

				if (my_isValid_xy(i + newX, j + newY, mapka) == true) {

					if (mapka[i + newX][j + newY].isObstacle == true)
						std::cout << "sprawdzam przeszkode" << std::endl;

					//mapka[i + newX][j + newY].shape.setFillColor(sf::Color::Magenta); //wylaczone wizualizacja sprawdzanych elementow
					//window.draw(mapka[i + newX][j + newY].shape);
					//window.display();

					int i_new = i + newX;
					int j_new = j + newY;
					
					if (closeSet[i_new][j_new] == false) {
						bool is_in_openset = false;

						for (auto it = openset.rbegin(); it != openset.rend(); ++it) { //sprawdzam czy sprawdzany node nie jest w openSet
							if (**it == mapka[i_new][j_new]) {
								is_in_openset = true;
								break;
							}
						}
						if (is_in_openset == false) {
							openset.push_back(&mapka[i_new][j_new]);
						}
						update_vertex(node, mapka[i_new][j_new], mapka, is_in_openset, window);
					}

				}
			}
		}
	}

	std::cout << "BRAK SCIEZKI" << std::endl;
	return;
}





