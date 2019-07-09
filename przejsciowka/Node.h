#pragma once
#include"window_dimensions.h"
#include "Square.h"
#include <cmath>

class Node:public Square
{
public:
	int y = y_square;
	int x = x_square;
	int parentX;
	int parentY;
	float gCost;
	float hCost;
	float fCost;

	bool isObstacle = false;

	Node(int x_square, int y_square);

};
Node::Node(int x_square=0, int y_square=0) :Square(x_square, y_square){}//=0 (jako parametry domyslne) dodalem zeby sie program nie wywalal

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

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

 static bool isDestination(int x, int y, Node dest) {
	 if (x == dest.x && y == dest.y) {
		 return true;
	 }
	 return false;
 }

 static double calculateH(int x, int y, Node dest) {
	 double H = (sqrt((x - dest.x)*(x - dest.x)
		 + (y - dest.y)*(y - dest.y)));
	 return H;
 }

 static float pixel_x(int x) {
	 return float(x*X_STEP)+X_STEP/2.f;
 }
 static float pixel_y(int y) {
	 return float(y*Y_STEP)+Y_STEP/2.f;
 }

