#pragma once
#include <array>
#include <iostream>
#include "Node.h"
#include <memory>
#include "window_dimensions.h"

void reczne_sprawdzanie_rodzica(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& cel) {

	//for (int i = 0; i < 8; i++) {
		//std::cout << "" << i << "," << i << " --> parent " << mapka[i][i].parentX << "," << mapka[i][i].parentY << std::endl;
	//}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			std::cout << "" << i << "," << j << " --> parent " << mapka[i][j].parentX << "," << mapka[i][j].parentY << std::endl;
		}
	}


}

void wyswietl_sciezke(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& cel) {

	int i = cel.x;
	int j = cel.y;
	std::cout << "x,y = "<<i <<","<<j << std::endl;
	while (true) { //(y != -1 && x != -1) && mapka[x][y].x != mapka[x][y].parentX && mapka[x][y].y != mapka[x][y].parentY
		std::cout << "droga: (" << mapka[i][j].x << "," << mapka[i][j].y << ") --> (" << mapka[i][j].parentX << "," << mapka[i][j].parentY << ")" << std::endl;

		
		i = mapka[i][j].parentX;
		j = mapka[i][j].parentY;

		std::cout << " wewnatrz petli: x,y = " << i << "," << j << std::endl;
		if (mapka[i][j].parentX == -1 || mapka[i][j].parentY == -1) {
			std::cout << "mam lipe" << std::endl;
			break;
		}
	}
	std::cout << "na koncu rysowania sciezki" << std::endl;

}

static void a_star_vector_of_pointers(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

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
			mapka[i][j].gCost = FLT_MAX;
			mapka[i][j].hCost = my_calcutateH(mapka[i][j], destination_Node); //zmienilem z FLT_MAX
			mapka[i][j].parentX = -1;
			mapka[i][j].parentY = -1;

			mapka[i][j].x = i;
			mapka[i][j].y = j;

			closeSet[i][j] = false;

		}
	}
	std::vector<Node*> openset; //DODA£EM std::unique<Node> #unique
	mapka[current_Node.x][current_Node.y].gCost = 0;
	//mapka[current_Node.x][current_Node.y].fCost = 0; //uwaga, moze byc bez sensu
	openset.emplace_back(&mapka[current_Node.x][current_Node.y]); //DODA£EM & przed mapka #unique //push_back() moze ew. byc

	//current_Node.gCost = 0;
	mapka[current_Node.x][current_Node.y].gCost = 0;
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; //pamietaj zeby zmienic na to co wyzzej
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;

	//bool found_path = false;

	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger_pointer); //usuwam r wszedzie
		
		std::cout << "rozmiar openset" << openset.size() << std::endl;
		//Node node = *openset.back(); //bylo wczesniej rbegin()
		Node node = *openset.back();
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
						mapka[i_new][j_new].parentX = mapka[i][j].x;
						mapka[i_new][j_new].parentY = mapka[i][j].y;
						std::cout << "you are at the destination, a_star found path" << std::endl;

						//check_predecessor(mapka, destination_Node);
						std::cout << "poprzednik: " << mapka[i_new][j_new].parentX << "," << mapka[i_new][j_new].parentY << std::endl;

						draw_path(mapka, mapka[i_new][j_new], window);
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
							openset.emplace_back(&mapka[i_new][j_new]);
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



static void a_star_vector_of_pointers_node_as_pointer(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node, sf::RenderWindow& window) {

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
	mapka[current_Node.x][current_Node.y].parentX = current_Node.parentX; //pamietaj zeby zmienic na to co wyzzej
	mapka[current_Node.x][current_Node.y].parentY = current_Node.parentY;

	//bool found_path = false;

	while (!openset.empty()) {
		std::sort(openset.begin(), openset.end(), compareNode_first_bigger_pointer); //usuwam r wszedzie

		//std::cout << "rozmiar openset" << openset.size() << std::endl;
		//Node node = *openset.back(); //bylo wczesniej rbegin()
		Node* node = openset.back();
		/*for (auto it = openset.begin(); it != openset.end();it++) {
			std::cout << "Rozmiar opeset:"<<openset.size() << std::endl;
			std::cout << "G: " << it->gCost << std::endl;
		}*/


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

					//if (mapka[i + newX][j + newY].isObstacle == true)
					//	std::cout << "sprawdzam przeszkode" << std::endl;

					mapka[i + newX][j + newY].shape.setFillColor(sf::Color::Magenta);
					window.draw(mapka[i + newX][j + newY].shape);
					window.display();
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

					}

				}
			}
		}
		//std::cout << "ROZMIAR openset na koniec petli: " << openset.size() << std::endl;

	}

	std::cout << "BRAK SCIEZKI" << std::endl;
	return;
}

//0, 0 -- > parent 0, 0
//0, 1 -- > parent 0, 0
//0, 2 -- > parent - 1, -1
//0, 3 -- > parent - 1, -1
//0, 4 -- > parent - 1, -1
//0, 5 -- > parent - 1, -1
//0, 6 -- > parent - 1, -1
//0, 7 -- > parent - 1, -1
//0, 8 -- > parent - 1, -1
//0, 9 -- > parent - 1, -1
//0, 10 -- > parent - 1, -1
//0, 11 -- > parent - 1, -1
//1, 0 -- > parent 0, 0
//1, 1 -- > parent - 1, -1
//1, 2 -- > parent - 1, -1
//1, 3 -- > parent - 1, -1
//1, 4 -- > parent - 1, -1
//1, 5 -- > parent - 1, -1
//1, 6 -- > parent - 1, -1
//1, 7 -- > parent - 1, -1
//1, 8 -- > parent - 1, -1
//1, 9 -- > parent - 1, -1
//1, 10 -- > parent - 1, -1
//1, 11 -- > parent - 1, -1
//2, 0 -- > parent 1, 0
//2, 1 -- > parent - 1, -1
//2, 2 -- > parent - 1, -1
//2, 3 -- > parent - 1, -1
//2, 4 -- > parent - 1, -1
//2, 5 -- > parent - 1, -1
//2, 6 -- > parent - 1, -1
//2, 7 -- > parent - 1, -1
//2, 8 -- > parent - 1, -1
//2, 9 -- > parent - 1, -1
//2, 10 -- > parent - 1, -1
//2, 11 -- > parent - 1, -1
//3, 0 -- > parent 2, 0
//3, 1 -- > parent 2, 0
//3, 2 -- > parent 3, 1
//3, 3 -- > parent 4, 2
//3, 4 -- > parent - 1, -1
//3, 5 -- > parent - 1, -1
//3, 6 -- > parent - 1, -1
//3, 7 -- > parent - 1, -1
//3, 8 -- > parent - 1, -1
//3, 9 -- > parent - 1, -1
//3, 10 -- > parent - 1, -1
//3, 11 -- > parent - 1, -1
//4, 0 -- > parent - 1, -1
//4, 1 -- > parent - 1, -1
//4, 2 -- > parent 3, 1
//4, 3 -- > parent - 1, -1
//4, 4 -- > parent - 1, -1
//4, 5 -- > parent - 1, -1
//4, 6 -- > parent - 1, -1
//4, 7 -- > parent - 1, -1
//4, 8 -- > parent - 1, -1
//4, 9 -- > parent - 1, -1
//4, 10 -- > parent - 1, -1
//4, 11 -- > parent - 1, -1
//5, 0 -- > parent - 1, -1
//5, 1 -- > parent 4, 2
//5, 2 -- > parent 4, 2
//5, 3 -- > parent 4, 2
//5, 4 -- > parent 5, 3
//5, 5 -- > parent - 1, -1
//5, 6 -- > parent - 1, -1
//5, 7 -- > parent - 1, -1
//5, 8 -- > parent - 1, -1
//5, 9 -- > parent - 1, -1
//5, 10 -- > parent - 1, -1
//5, 11 -- > parent - 1, -1
//6, 0 -- > parent - 1, -1
//6, 1 -- > parent - 1, -1
//6, 2 -- > parent 5, 3
//6, 3 -- > parent 5, 3
//6, 4 -- > parent 5, 3
//6, 5 -- > parent 6, 4
//6, 6 -- > parent 7, 5
//6, 7 -- > parent - 1, -1
//6, 8 -- > parent - 1, -1
//6, 9 -- > parent - 1, -1
//6, 10 -- > parent - 1, -1
//6, 11 -- > parent - 1, -1
//7, 0 -- > parent - 1, -1
//7, 1 -- > parent - 1, -1
//7, 2 -- > parent - 1, -1
//7, 3 -- > parent 6, 4
//7, 4 -- > parent 6, 4
//7, 5 -- > parent 6, 4
//7, 6 -- > parent 7, 5
//7, 7 -- > parent 8, 6
//7, 8 -- > parent 8, 7
//7, 9 -- > parent 8, 8
//7, 10 -- > parent 8, 9
//7, 11 -- > parent - 1, -1
//8, 0 -- > parent - 1, -1
//8, 1 -- > parent - 1, -1
//8, 2 -- > parent - 1, -1
//8, 3 -- > parent - 1, -1
//8, 4 -- > parent 7, 5
//8, 5 -- > parent 7, 5
//8, 6 -- > parent 7, 5
//8, 7 -- > parent 8, 6
//8, 8 -- > parent 8, 7
//8, 9 -- > parent 8, 8
//8, 10 -- > parent 8, 9
//8, 11 -- > parent - 1, -1
//9, 0 -- > parent - 1, -1
//9, 1 -- > parent - 1, -1
//9, 2 -- > parent - 1, -1
//9, 3 -- > parent - 1, -1
//9, 4 -- > parent - 1, -1
//9, 5 -- > parent 8, 6
//9, 6 -- > parent 8, 6
//9, 7 -- > parent 8, 6
//9, 8 -- > parent 8, 7
//9, 9 -- > parent 8, 8
//9, 10 -- > parent - 1, -1
//9, 11 -- > parent - 1, -1
//10, 0 -- > parent - 1, -1
//10, 1 -- > parent - 1, -1
//10, 2 -- > parent - 1, -1
//10, 3 -- > parent - 1, -1
//10, 4 -- > parent - 1, -1
//10, 5 -- > parent - 1, -1
//10, 6 -- > parent - 1, -1
//10, 7 -- > parent - 1, -1
//10, 8 -- > parent - 1, -1
//10, 9 -- > parent - 1, -1
//10, 10 -- > parent - 1, -1
//10, 11 -- > parent - 1, -1
//11, 0 -- > parent - 1, -1
//11, 1 -- > parent - 1, -1
//11, 2 -- > parent - 1, -1
//11, 3 -- > parent - 1, -1
//11, 4 -- > parent - 1, -1
//11, 5 -- > parent - 1, -1
//11, 6 -- > parent - 1, -1
//11, 7 -- > parent - 1, -1
//11, 8 -- > parent - 1, -1
//11, 9 -- > parent - 1, -1
//11, 10 -- > parent - 1, -1
//11, 11 -- > parent - 1, -1


