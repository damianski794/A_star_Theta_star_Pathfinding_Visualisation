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
float euclidean_distance1(Node& current_node, Node& destination) {
	return sqrt((current_node.x - destination.x)*(current_node.x - destination.x) + (current_node.y - destination.y)*(current_node.y - destination.y));
}

void draw_path(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node destination, sf::RenderWindow& window) {
	float dlugosc_sciezki = 0;
	//z innego algorytmu:
	//for (int i = 0; i < 12; i++) {
	//	for (int j = 0; j < 12; j++) {
	//		std::cout << "" << i << "," << j << " --> parent " << mapka[i][j].parentX << "," << mapka[i][j].parentY << std::endl;
	//	}
	//}
	std::cout << std::endl << std::endl;

	//sf::VertexArray lines(sf::LinesStrip, 2);
	int X = destination.x;
	int Y = destination.y;
	
	//std::cout << "test" << std::endl;
	//std::cout << "rysuje droge z: (" << mapka[X][Y].x << "," << mapka[X][Y].y << ") do (" << mapka[X][Y].parentX << "," << mapka[X][Y].parentY << ")" << std::endl;
	while (mapka[X][Y].y != -1  && !(mapka[X][Y].x == mapka[X][Y].parentX && mapka[X][Y].y == mapka[X][Y].parentY) && mapka[X][Y].x != -1) { //zmienione
		//lines[0].position = sf::Vector2f(pixel_x(mapka[X][Y].x), pixel_y(mapka[X][Y].y));
		//lines[0].color = sf::Color::Black;
		//lines[1].position = sf::Vector2f(pixel_x(mapka[X][Y].parentX), pixel_y(mapka[X][Y].parentY));
		//lines[1].color = sf::Color::Black;

		mapka[X][Y].shape.setFillColor(sf::Color::Green);
		//window.draw(mapka[X][Y]);
		mapka[mapka[X][Y].parentX][mapka[X][Y].parentY].shape.setFillColor(sf::Color::Green);
		//window.draw(mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]);


		//sf::RectangleShape line(sf::Vector2f(euclidean_distance1(mapka[X][Y], mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]), 50));
		//line.rotate(90);
		//line.setFillColor(sf::Color::Green);
		//line.setOrigin
		//window.draw(line);

		float single_line_dist = X_STEP * euclidean_distance1(mapka[X][Y], mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]);
		sf::RectangleShape line2(sf::Vector2f(single_line_dist, 5));

		float line_y = (Y - mapka[X][Y].parentY); // - bo w sfml y zwieksza sie w dol ekranu
		float line_x = (X - mapka[X][Y].parentX);

		line2.rotate(atan2(line_y,line_x)*180/3.14);
		line2.setPosition(pixel_x(mapka[X][Y].parentX),pixel_y(mapka[X][Y].parentY));

		line2.setFillColor(sf::Color::Green);
		window.draw(line2);

		
		std::cout << "X,Y: " << mapka[X][Y].x << "," << mapka[X][Y].y << " --> " << mapka[X][Y].parentX << "," << mapka[X][Y].parentY << "\t";
		std::cout << "zostanie_dodane: " << euclidean_distance1(mapka[X][Y], mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]) << std::endl;
		dlugosc_sciezki += euclidean_distance1(mapka[X][Y], mapka[mapka[X][Y].parentX][mapka[X][Y].parentY]);

		int tempX = mapka[X][Y].parentX;
		Y = mapka[X][Y].parentY;
		X = tempX;

		std::cout << "nowe X,Y: " <<X<<","<<Y<< std::endl;
	//	window.draw(line, 2, sf::Lines);
	

		//window.draw(lines); 
		
	}
	window.display();

	std::cout<<"DLUGOSC SCIEZKI TO: "<<dlugosc_sciezki<<std::endl;
	std::cout << "sleeping" << std::endl;
	Sleep(4000);
	std::cout << "end of sleeping" << std::endl;

}

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
		std::cout << "wywalilo blad" << std::endl;
		std::cout << e.what() << std::endl;
	}
}

static void a_star(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

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

		//std::cout << "rozmiar openset" << openset.size() << std::endl;
		//Node node = *openset.back(); //bylo wczesniej rbegin()
		Node* node = openset.back();
		std::cout << "NAJMNIEJSZY FCOST: " << node->fCost << std::endl;
		/*for (auto it = openset.begin(); it != openset.end();it++) {
			std::cout << "Rozmiar opeset:"<<openset.size() << std::endl;
			std::cout << "G: " << it->gCost << std::endl;
		}*/


		node->shape.setFillColor(sf::Color::Red);// 7.09.2019
		window.draw(node->shape);
		window.display();



		if (isDestination(node->x, node->y, destination_Node)) {
			std::cout << "this is the destination" << std::endl;
			return;
		}
		openset.pop_back(); //drop the last element
		//std::cout << "rozmiar openset" << openset.size() << std::endl;
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
					//std::cout << "Checking Node: (" << i_new << "," << j_new<<")" << std::endl;

					//std::cout << "wartosc closeset: " << closeSet[i_new][j_new] << std::endl;
					if (my_isDestination(mapka[i_new][j_new], destination_Node) == true) {
						mapka[i_new][j_new].parentX = mapka[i][j].x;
						mapka[i_new][j_new].parentY = mapka[i][j].y;
						std::cout << "you are at the destination, a_star found path" << std::endl;

						//check_predecessor(mapka, destination_Node);
						std::cout << "poprzednik: " << mapka[i_new][j_new].parentX << "," << mapka[i_new][j_new].parentY << std::endl;

						draw_path(mapka, mapka[i_new][j_new], window);
						//wyswietl_sciezke(mapka, destination_Node);
						//reczne_sprawdzanie_rodzica(mapka, destination_Node);
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
						float tentative_g_score = node->gCost + dist_beetween_node_and_adjastend;

						Fnew = tentative_g_score + mapka[i_new][j_new].hCost;
						//std::cout << "tentative_g_score: " << tentative_g_score << std::endl;
						bool tentative_is_better = false;
						bool is_in_openset = false;

						for (auto it = openset.rbegin(); it != openset.rend(); ++it) { //sprawdzam czy sprawdzany node nie jest w openSet
							if (**it == mapka[i_new][j_new]) {
								is_in_openset = true;
								break;
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
							mapka[i_new][j_new].parentX = mapka[i][j].x;
							mapka[i_new][j_new].parentY = mapka[i][j].y;

							tentative_is_better = true;
							openset.push_back(&mapka[i_new][j_new]); //bylo emplace 
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