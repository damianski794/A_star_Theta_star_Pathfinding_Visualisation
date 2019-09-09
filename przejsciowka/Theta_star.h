#pragma once
#include "Node.h"
#include "A_star.h"

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

float euclidean_distance(Node& current_node, Node& destination) {
	return sqrt((current_node.x - destination.x)*(current_node.x - destination.x) + (current_node.y - destination.y)*(current_node.y - destination.y));
}

bool line_of_sight(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& parent_Node, Node& adjecent_Node, sf::RenderWindow& window) {
	int x1 = parent_Node.x, y1 = parent_Node.y;
	int x2 = adjecent_Node.x, y2 = adjecent_Node.y;
	int max = std::max(abs(x1 - x2), abs(y1 - y2));
	max = 3 * max; //chyba nie potrzeba wiekszej dokladnosci
	float t;
	float x, y;
	for (int i = 0; i <= max; i++) {
		t = float(i) / max;
		x = (x1 * (1.0 - t) + x2 * t);
		y = (y1 * (1.0 - t) + y2 * t);

		//std::cout << "( " << round(x) << "=" << x << " , " << round(y) << "=" << y << " ) dla t = " << t << std::endl;
		int y_new = round(y);
		int x_new = round(x);
		if (mapka[x_new][y_new].isObstacle) {
			//std::cout << "wykryto przeszkode" << std::endl;
			return false;
		}

		//mapka[x_new][y_new].shape.setFillColor(sf::Color::Magenta); //wylaczone wizualizacja sprawdzanych elementow
		//window.draw(mapka[x_new][y_new].shape);
		//window.display();
		//if (i == max - 1)
		//	std::cout << "KONIEC" << std::endl;
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
	if (adjecent.parentX == -1 && adjecent.parentY == -1) {
		//adjecent.parentX = node->x;
		//adjecent.parentY = node->y;
		//adjecent.gCost = node->gCost + euclidean_distance(*node, adjecent);
		//adjecent.fCost = adjecent.gCost + adjecent.hCost;
		//std::cout << "nowy element" << std::endl;

		//std::cout << std::endl << std::endl << std::endl << std::endl;
		//update_vertex(node, adjecent, mapka, is_in_openset, window); //????
	}
	//mozliwe, ze trzeba tu troche pogrzebac z nowym gCost i fCost
}



static void a_star_theta_star(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

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
			mapka[i][j].gCost = 10000; //FLT_COS bylo wczesniej
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
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; //pamietaj zeby zmienic na to co wyzzej
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;

	//bool found_path = false;

	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger_pointer);

		//std::cout << "rozmiar openset" << openset.size() << std::endl;
		//Node node = *openset.back(); //bylo wczesniej rbegin()
		Node* node = openset.back();
		/*for (auto it = openset.begin(); it != openset.end();it++) {
			std::cout << "Rozmiar opeset:"<<openset.size() << std::endl;
			std::cout << "G: " << it->gCost << std::endl;
		}*/
		//std::cout << "NAJMNIEJSZY FCOST: " << node->fCost <<"  a openlist zawiera: "<<openset.size()<<" elementow"<< std::endl;

		if (isDestination(node->x, node->y, destination_Node)) {
			std::cout << "this is the destination" << std::endl;
			draw_path(mapka, *node, window);
			return;
		}

		//node->shape.setFillColor(sf::Color::Red);// 7.09.2019 //odkomentuj zeby zobaczyc jakie nody sa aktualnie sprawdzane
		//window.draw(node->shape);
		//window.display();

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
					/*
					if (my_isDestination(mapka[i_new][j_new], destination_Node) == true) {
						mapka[i_new][j_new].parentX = mapka[i][j].x;
						mapka[i_new][j_new].parentY = mapka[i][j].y;
						std::cout << "you are at the destination, a_star found path" << std::endl;

						//check_predecessor(mapka, destination_Node);
						//std::cout << "poprzednik: " << mapka[i_new][j_new].parentX << "," << mapka[i_new][j_new].parentY << std::endl;

						draw_path(mapka, mapka[i_new][j_new], window);
						
						return;
					} */
					if (closeSet[i_new][j_new] == false) {
						/* from here to::
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
						*/ //too here::


						bool is_in_openset = false;

						for (auto it = openset.rbegin(); it != openset.rend(); ++it) { //sprawdzam czy sprawdzany node nie jest w openSet
							if (**it == mapka[i_new][j_new]) {
								is_in_openset = true;
								break;
							}
						}
						if (is_in_openset == false) {
							//mapka[i_new][j_new].parentX = node->x;
							//mapka[i_new][j_new].parentY = node->y;
							//mapka[i_new][j_new].gCost = node->gCost + euclidean_distance(*node, mapka[i_new][j_new]);
							//mapka[i_new][j_new].fCost = mapka[i_new][j_new].gCost + mapka[i_new][j_new].hCost;

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


static void update_vertex(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

}

/*
				function update_vertex(s, neighbor)
				// This part of the algorithm is the main difference between A* and Theta*
				if line_of_sight(parent(s), neighbor)
				// If there is line-of-sight between parent(s) and neighbor
				// then ignore s and use the path from parent(s) to neighbor 
				if gScore(parent(s)) + c(parent(s), neighbor) < gScore(neighbor)
					// c(s, neighbor) is the Euclidean distance from s to neighbor
					gScore(neighbor) := gScore(parent(s)) + c(parent(s), neighbor)
					parent(neighbor) : = parent(s)
					if neighbor in open
						open.remove(neighbor)
						open.insert(neighbor, gScore(neighbor) + heuristic(neighbor))
					else
						// If the length of the path from start to s and from s to 
						// neighbor is shorter than the shortest currently known distance
						// from start to neighbor, then update node with the new distance
						if gScore(s) + c(s, neighbor) < gScore(neighbor)
							gScore(neighbor) := gScore(s) + c(s, neighbor)
							parent(neighbor) : = s
							if neighbor in open
								open.remove(neighbor)
								open.insert(neighbor, gScore(neighbor) + heuristic(neighbor))


*/
