// przejsciowka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "window_dimensions.h"
#include <iostream>
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



//UWAGA
//usunalem jpeg.lib z dodatykowych bibliotek
int main()
{
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
		window.display();
	}
}