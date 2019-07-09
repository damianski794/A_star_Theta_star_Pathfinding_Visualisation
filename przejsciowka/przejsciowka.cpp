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
#include <iostream>

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
	lines[0].position = sf::Vector2f(float(mapka[5][5].x), float(mapka[5][5].y));
	lines[0].position= sf::Vector2f(float(mapka[10][10].x), float(mapka[10][10].y));
	//lines.color TU DODAJ KOLOR

	sf::RenderWindow window( sf::VideoMode(X_MAX,Y_MAX),"A star visualisation" );
	sf::Event event;



	while (window.isOpen())
	{
		window.pollEvent(event);
				
		if (event.type == sf::Event::Closed)
			window.close();
		std::cout << "test" << std::endl;
		
		window.clear(sf::Color::Black);
		
		draw_map(mapka, window);
		window.draw(lines);
		
		window.display();
	}
}

