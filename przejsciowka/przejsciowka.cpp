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

using namespace std;

const int columns = Y_MAX / Y_STEP; // ew. na odwrot powinny byc kolumny i wiersze
const int rows = X_MAX / X_STEP;

void draw_map(array<array<Node, columns>, rows> mapka,sf::RenderWindow& window){
	for (int x = 0; x < rows; x++) {
		for (int y = 0; x < columns; y++) {
			window.draw(mapka[x][y].shape);
		}
	}
}
//
//UWAGA
//usunalem jpeg.lib z dodatykowych bibliotek
int main()
{
	Square s1(0,0);
	Square s2(2,1);
	Square s3(1, 0);

	//array<array<Node, columns>, rows> mapka;
	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mapka[i][j].x = i;
			mapka[i][j].y = j;
		}
	}*/

	sf::RenderWindow window( sf::VideoMode(X_MAX,Y_MAX),"A star visualisation" );
	sf::Event event;


	while (window.isOpen())
	{
		window.pollEvent(event);
				
		if (event.type == sf::Event::Closed)
			window.close();
		std::cout << "test" << std::endl;
		
		window.clear(sf::Color::Black);
		//window.draw(ball);
		//ball.update();
		//draw_map(mapka, window);
		window.draw(s1);
		window.draw(s2);
		window.draw(s3);
		window.display();
	}
}


//int main()
//{
//	Ball ball(400, 300);
//	sf::RenderWindow window{ sf::VideoMode{800,600},"giereczka" };
//	window.setFramerateLimit(60);
//	sf::Event event;
//	while (window.isOpen())
//	{
//		window.pollEvent(event);
//		
//		if (event.type == sf::Event::Closed)
//			window.close();
//		std::cout << "test" << std::endl;
//
//		window.clear(sf::Color::Black);
//		window.draw(ball);
//		ball.update();
//		window.display();
//	}
//}