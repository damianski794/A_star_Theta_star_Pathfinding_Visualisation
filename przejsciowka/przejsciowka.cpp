// przejsciowka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "window_dimensions.h"
#include "Node.h"
#include <iostream>
#include <array>
#include "Square.h"
#include <vector>

using namespace std;

const int columns = Y_MAX / Y_STEP; // ew. na odwrot powinny byc kolumny i wiersze
const int rows = X_MAX / X_STEP;

void draw_map(array<array<Node, columns>, rows> &mapka,sf::RenderWindow& window){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			window.draw(mapka[i][j].shape);
		}
	}
}

void draw_path(vector<Node>& path,sf::RenderWindow& window) { //UWAGA na REFERENCJE
	sf::VertexArray lines(sf::LinesStrip, 2);
	
	for (auto t = path.begin(); t != path.end() && path.size() > 0; ++t) {
		lines[0].position = sf::Vector2f(pixel_x(t->x), pixel_y(t->y));
		lines[0].color = sf::Color::Red;
		lines[1].position = sf::Vector2f(pixel_x(t->parentX), pixel_y(t->parentY));
		lines[1].color = sf::Color::Red;

		window.draw(lines);
		cout << "rysuje linie z " << t->x << "," << t->y << "  do " << t->parentX << "," << t->parentY << endl;
	}
}
//
//UWAGA
//usunalem jpeg.lib z dodatykowych bibliotek
int main()
{

	array<array<Node, columns>, rows> mapka;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mapka[i][j] = Node(i, j);
		}
	}

	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = sf::Vector2f(pixel_x(mapka[5][5].x), pixel_y(mapka[5][5].y));
	lines[0].color = sf::Color::Red;
	lines[1].position= sf::Vector2f(pixel_x(mapka[10][10].x), pixel_y(mapka[10][10].y));
	lines[1].color = sf::Color::Red;
	
	
	//test przykladowej sciezki:
	mapka[12][10].parentX = 5;
	mapka[12][10].parentY = 8;

	mapka[5][8].parentX = 2;
	mapka[5][8].parentY = 2;

	mapka[2][2].parentX = 2;
	mapka[2][2].parentY = 10;
	vector<Node> test_path;
	test_path.push_back(mapka[12][10]);
	test_path.push_back(mapka[5][8]);
	test_path.push_back(mapka[2][2]);


	sf::RenderWindow window( sf::VideoMode(X_MAX,Y_MAX),"A star visualisation" );
	sf::Event event;



	while (window.isOpen())
	{
		window.pollEvent(event);
				
		if (event.type == sf::Event::Closed)
			window.close();
		//std::cout << "test" << std::endl;
		
		window.clear(sf::Color::Black);
		
		draw_map(mapka, window);
		//window.draw(lines);
		draw_path(test_path,window);
		
		window.display();
	}
}

