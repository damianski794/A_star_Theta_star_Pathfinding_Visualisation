#pragma once
#include"window_dimensions.h"
#include "Square.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <array>

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
	bool isCheckedByA_Star = false;

	Node(int x_square, int y_square);

};
Node::Node(int x_square=0, int y_square=0) :Square(x_square, y_square){}//=0 (jako parametry domyslne) dodalem zeby sie program nie wywalal

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
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

 static bool isDestination(int x, int y, Node dest) {
	 if (x == dest.x && y == dest.y) {
		 return true;
	 }
	 return false;
 }

 static double calculateH(int x, int y, Node dest) { //heurystyka jako odleglosc typu pitagorasa: (sqrt(x^2=y^2))
	 double H = (sqrt((x - dest.x)*(x - dest.x)
		 + (y - dest.y)*(y - dest.y)));
	 return H;
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
