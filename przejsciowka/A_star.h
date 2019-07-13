#pragma once

#include "Node.h"
#include "window_dimensions.h"
#include <vector>
#include <array>
#include <stack>
#include <iostream>

using namespace std;

static vector<Node> aStar(Node player, Node dest) {
	vector<Node> empty;
	if (isValid(dest.x, dest.y) == false) {
		cout << "Destination is an obstacle" << endl;
		return empty;
		//Destination is invalid
	}
	if (isDestination(player.x, player.y, dest)) {
		cout << "You are the destination" << endl;
		return empty;
		//You clicked on yourself
	}
	bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

	//Initialize whole map
	//Node allMap[50][25];
	array<array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
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

	vector<Node> openList;
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
			vector<Node>::iterator itNode;
			for (vector<Node>::iterator it = openList.begin();
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
		cout << "Destination not found" << endl;
		return empty;
	}
}

static vector<Node> makePath(array<array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
	try {
		cout << "Found a path" << endl;
		int x = dest.x;
		int y = dest.y;
		stack<Node> path;
		vector<Node> usablePath;

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
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}

static vector<Node> my_A_Star(array<array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka, Node& current_Node, Node& destination_Node) {

	vector<Node> empty;
	if (my_isValid(destination_Node) == false) {
		cout << "destination is an obstacle, returning empty path" << endl;
		return empty;
	}
	if (my_isDestination(current_Node, destination_Node)) {
		cout << "your at the destination, returning empty path" << endl;
		return empty;
	}

	bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

	for (int i = 0; i < X_MAX / X_STEP; i++) {
		for (int j = 0; j < Y_MAX / Y_STEP; j++) {
			mapka[i][j].fCost = FLT_MAX;
			mapka[i][j].gCost = FLT_MAX;
			mapka[i][j].hCost = FLT_MAX;
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

	vector<Node> openList;
	openList.emplace_back(mapka[i][j]);

	bool destination_found = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
		Node node;
		do {
			float temp = FLT_MAX;
			vector<Node>::iterator itNode;
			for (vector<Node>::iterator it = openList.begin();
				it != openList.end(); next(it)) {
				Node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (my_isValid(node) == false);

		i = node.x;
		j = node.y;
		closedList[i][j] = true;

		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (my_isValid_xy(i + newX, j + newY, mapka)) {
					if (my_isDestination(mapka[i + newX][j + newY], destination_Node)) {
						mapka[i + newX][j + newY].parentX = i;
						mapka[i + newX][j + newY].parentY = j;
						destination_found = true;
						cout << "znaleziono droge!!!" << endl << endl;

						return makePath(mapka, destination_Node);
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
						}
					}
				}
			}
		}
	}
	if (destination_found == false) {
		cout << "destination not found :/" << endl;
		return empty;
	}
}
