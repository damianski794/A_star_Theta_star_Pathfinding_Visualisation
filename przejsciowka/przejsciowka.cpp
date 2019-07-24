#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <array>
#include <vector>
#include <Windows.h>

#include "window_dimensions.h"
#include "Node.h"
#include "Square.h"
#include "A_star.h"



bool is_inside_the_window(sf::Vector2i a) {
	if (a.x < 0 || a.x > pixel_x(X_MAX / X_STEP)) {
		return false;
	}
	if (a.y < 0 || a.y >pixel_y(Y_MAX / Y_STEP)) {
		return false;
	}
	return true;
}

const int columns = Y_MAX / Y_STEP; 
const int rows = X_MAX / X_STEP;

void draw_map(std::array<std::array<Node, columns>, rows> &mapka,sf::RenderWindow& window){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (mapka[i][j].isObstacle){
				mapka[i][j].shape.setFillColor(sf::Color::Black);
			}
			else if(mapka[i][j].isCheckedByA_Star){
				mapka[i][j].shape.setFillColor(sf::Color::Magenta);
			}
			else
				mapka[i][j].shape.setFillColor(sf::Color::White);
			window.draw(mapka[i][j].shape);
		}
	}
}

void draw_path(std::vector<Node>& path,sf::RenderWindow& window) { //UWAGA na REFERENCJE
	if (path.size() == 0) {
		std::cout << "sciezka ma dlugosc 0 - brak sciezki" << std::endl;
		return;
	}

	sf::VertexArray lines(sf::LinesStrip, 2);
	
	for (auto t = path.begin(); t != path.end() && path.size() > 0; ++t) {
		lines[0].position = sf::Vector2f(pixel_x(t->x), pixel_y(t->y));
		lines[0].color = sf::Color::Red;
		lines[1].position = sf::Vector2f(pixel_x(t->parentX), pixel_y(t->parentY));
		lines[1].color = sf::Color::Red;

		window.draw(lines);
	}
}



int main()
{

	std::array<std::array<Node, columns>, rows> mapka;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mapka[i][j] = Node(i, j);
			mapka[i][j].parentX = i;
			mapka[i][j].parentY = j;
		}
	}


	sf::RenderWindow window( sf::VideoMode(X_MAX,Y_MAX),"A star visualisation" );
	window.setFramerateLimit(200);
	sf::Event event;

	int current_mouse_pos_x=1;
	int current_mouse_pos_y=1;


	bool a_star_started = false;
	std::vector<Node> path_designed_by_A_star;
	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				a_star_started = true;
				std::cout << "wcisnieto A: " << std::endl;
				a_star(mapka, mapka[0][0], mapka[49][24], window);
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_inside_the_window(sf::Mouse::getPosition(window))) {//ustawianie przeszkod
			
			mapka[x_from_pixel(sf::Mouse::getPosition(window).x)][y_from_pixel(sf::Mouse::getPosition(window).y)].isObstacle
				= true;
		}
	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && is_inside_the_window(sf::Mouse::getPosition(window))) { //usuwanie przeszkod
			mapka[x_from_pixel(sf::Mouse::getPosition(window).x)][y_from_pixel(sf::Mouse::getPosition(window).y)].isObstacle
				= false;
		}


		draw_map(mapka, window);
		if (a_star_started) {
		}
		window.display();
		if (a_star_started) {
			Sleep(1500);
			a_star_started = false;
		}
	}
}

