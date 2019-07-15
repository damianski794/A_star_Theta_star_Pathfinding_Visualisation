#pragma once
#include"window_dimensions.h"
#include "Square.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <array>
#include <memory>

class Node:public Square
{
public:
	int y = y_square;
	int x = x_square;
	int parentX = 0; //dla testu czy sie sciezka bedzie odpalala
	int parentY = 0; //
	float gCost;
	float hCost;
	float fCost;

	bool isObstacle = false;
	bool isCheckedByA_Star = false;

	bool isInCloseList = false;

	Node(int x_square, int y_square);

	bool operator==(const Node& right) {
		if (this->x == right.x && this->y == right.y) {
			return true;
		}
		return false;
	}

};
Node::Node(int x_square=0, int y_square=0) :Square(x_square, y_square){}//=0 (jako parametry domyslne) dodalem zeby sie program nie wywalal

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

bool compareNode(const Node& lhs, const Node& rhs) {
	return lhs.fCost < rhs.fCost;
}

bool compareNode_first_bigger(const Node& lhs, const Node& rhs) {
	return lhs.fCost > rhs.fCost;
}

bool compareNode_first_bigger_pointer(std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs) {
	return lhs->fCost > rhs->fCost;
}

//dodaj zmiane obstacle/non obstacle przez klikniecie w mape


//uwaga usuniete
 static bool isValid(int x, int y) { //If our Node is an obstacle it is not valid
	int id = x + y * (X_MAX / X_STEP);
	if (true){//world.obstacles.count(id) == 0) {
		if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP)) {
			return false;
		}
		return true;
	}
	return false;
}
 static bool my_isValid(Node& node) {
	 if (node.isObstacle)
		 return false;
	 if (node.x < 0 || node.x >= X_MAX / X_STEP || node.y < 0 || node.y >= Y_MAX / Y_STEP)
		 return false;
	 return true;
 }
 static bool my_isValid_xy(int x, int y, std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& mapka) { 
	 if (x < 0 || x >= X_MAX / X_STEP || y < 0 || y >= Y_MAX / Y_STEP)
		 return false;
	 if (mapka[x][y].isObstacle == true)
		 return false;
	 return true;
 }

 static bool isDestination(int x, int y, Node dest) {
	 if (x == dest.x && y == dest.y) {
		 return true;
	 }
	 return false;
 }
 static bool my_isDestination(Node& current_node, Node& destination)
 {
	 if (current_node.x == destination.x && current_node.y == destination.y)
		 return true;
	 return false;
 }

 static double calculateH(int x, int y, Node dest) { //heurystyka jako odleglosc typu pitagorasa: (sqrt(x^2+y^2))
	 double H = (sqrt((x - dest.x)*(x - dest.x)
		 + (y - dest.y)*(y - dest.y)));
	 return H;
 }
 static double my_calcutateH(Node& current_node, Node& destination) {
	 return fabs(current_node.x - destination.x) + fabs(current_node.y - destination.y);
	 // return sqrt((current_node.x - destination.x)*(current_node.x - destination.x) - (current_node.y - destination.y)*(current_node.y - destination.y));
 }

 static float pixel_x(int x) { //zwraca numer pixela x gdy dane jest polozenie Node.x
	 return float(x*X_STEP)+X_STEP/2.f;
 }
 static float pixel_y(int y) { //zwraca numer pixela y gdy dane jest polozenie Node.y
	 return float(y*Y_STEP)+Y_STEP/2.f;
 }

 static int x_from_pixel(float px) {
	 float f = px / X_STEP;
	 int g = px / X_STEP;
	 if (f > g)
		 return g;
	 else
		 return g - 1;
 }

 static int y_from_pixel(float py) {
	 float f = py / Y_STEP;
	 int g = py / Y_STEP;
	 if (f > g)
		 return g;
	 else
		 return g - 1;
 }
