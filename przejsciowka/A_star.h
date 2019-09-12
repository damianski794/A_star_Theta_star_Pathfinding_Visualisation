#pragma once

#include "window_dimensions.h"
#include "Node.h"
#include <Windows.h>

#include <vector>
#include <array>
#include <stack>

#include <iostream>

#include <Windows.h>

#include <cmath>

#include <chrono>
float euclidean_distance1(Node& current_node, Node& destination) {
	return sqrt((current_node.x - destination.x)*(current_node.x - destination.x) + (current_node.y - destination.y)*(current_node.y - destination.y));
}

void draw_path(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node destination, sf::RenderWindow& window) {
	float dlugosc_sciezki = 0;
	
	int X = destination.x;
	int Y = destination.y;
	
	
	while (mapka[X][Y].y != -1  && !(mapka[X][Y].x == mapka[X][Y].parentX && mapka[X][Y].y == mapka[X][Y].parentY) && mapka[X][Y].x != -1) { //zmienione
	
		mapka[X][Y].shape.setFillColor(sf::Color::Green);
		
		mapka[mapka[X][Y].parentX][mapka[X][Y].parentY].shape.setFillColor(sf::Color::Green);

		float single_line_dist = X_STEP * euclidean_distance1(mapka[X][Y], mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]);
		sf::RectangleShape line2(sf::Vector2f(single_line_dist, 5));

		float line_y = (Y - mapka[X][Y].parentY); 
		float line_x = (X - mapka[X][Y].parentX);

		line2.rotate(atan2(line_y,line_x)*180/3.14);
		line2.setPosition(pixel_x(mapka[X][Y].parentX),pixel_y(mapka[X][Y].parentY));

		line2.setFillColor(sf::Color::Green);
		window.draw(line2);

		dlugosc_sciezki += euclidean_distance1(mapka[X][Y], mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]);

		int tempX = mapka[X][Y].parentX;
		Y = mapka[X][Y].parentY;
		X = tempX;	
	}
	window.display();

	std::cout<<"DLUGOSC SCIEZKI TO: "<<dlugosc_sciezki<<std::endl;
	std::cout << "sleeping" << std::endl;
	Sleep(4000);
	std::cout << "end of sleeping" << std::endl;

}



static void a_star(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

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
			//mapka[i][j].fCost = FLT_MAX; f cost ustawiam jako nieznane
			mapka[i][j].gCost = 1000; //FLT_COS bylo wczesniej
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

	std::vector<Node*> openset; //DODA£EM std::unique<Node> #unique
	mapka[current_Node.x][current_Node.y].gCost = 0;
	//mapka[current_Node.x][current_Node.y].fCost = 0; //uwaga, moze byc bez sensu
	openset.push_back(&mapka[current_Node.x][current_Node.y]); //DODA£EM & przed mapka #unique //push_back() moze ew. byc

	//current_Node.gCost = 0;
	mapka[current_Node.x][current_Node.y].gCost = 0;
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; //pamietaj zeby zmienic na to co wyzej
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;

	//bool found_path = false;

	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger_pointer);


		Node* node = openset.back();
	


		//node->shape.setFillColor(sf::Color::Red);// 7.09.2019 //odkomentuj zeby zobaczyc ktory node jest akutalnie sprawdzany
		//window.draw(node->shape);
		//window.display();



		if (isDestination(node->x, node->y, destination_Node)) {
			

			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			std::cout << "Algorithm time (in miliseconds) is: " << double(duration.count()) / 1000 << std::endl;

			draw_path(mapka, *node, window);
			return;
		}
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
						float Fnew; //dodane

						float dist_beetween_node_and_adjastend;
						if ((newX == -1 && newY == -1) || (newX == -1 && newY == 1) || (newX == 1 && newY == -1) || (newX == 1 && newY == 1)) {
							dist_beetween_node_and_adjastend = 1.4f;
						}
						else {
							dist_beetween_node_and_adjastend = 1.0f;
						}
						float tentative_g_score = node->gCost + dist_beetween_node_and_adjastend;

						Fnew = tentative_g_score + mapka[i_new][j_new].hCost;
						
						bool tentative_is_better = false;
						bool is_in_openset = false;

						for (auto it = openset.rbegin(); it != openset.rend(); ++it) { //sprawdzam czy sprawdzany node nie jest w openSet
							if (**it == mapka[i_new][j_new]) {
								is_in_openset = true;
								break;
							}
						}
						
						if (is_in_openset == false) {
							
							mapka[i_new][j_new].fCost = Fnew;
							mapka[i_new][j_new].gCost = tentative_g_score;
							mapka[i_new][j_new].parentX = mapka[i][j].x;
							mapka[i_new][j_new].parentY = mapka[i][j].y;

							tentative_is_better = true;
							openset.push_back(&mapka[i_new][j_new]); 
						}
						else if (tentative_g_score < mapka[i_new][j_new].gCost) {
							tentative_is_better = true;
						}

						if (tentative_is_better) {
							mapka[i_new][j_new].parentX = node->x;
							mapka[i_new][j_new].parentY = node->y;
							mapka[i_new][j_new].gCost = tentative_g_score;
							mapka[i_new][j_new].fCost = mapka[i_new][j_new].gCost + mapka[i_new][j_new].hCost;
						}

					}

				}
			}
		}
	}

	std::cout << "BRAK SCIEZKI" << std::endl;
	return;
}