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

void draw_path(vector<Node>& path,sf::RenderWindow& window) { //UWAGA na REFERENCJE
	if (path.size() == 0) {
		cout << "sciezka ma dlugosc 0 - brak sciezki" << endl;
		return;
	}

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
			if (i*j % (j+10) == 0 && i>5)
				mapka[i][j].isObstacle = true; //dodawanie przeszkod
			//if ((i + j) % 10 == 0)
				//mapka[i][j].isCheckedByA_Star = true; //dodawanie sprawdzenia czy a* iterowal po danym node
		}
	}


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
	//koniec przykladowej sciezki

	sf::RenderWindow window( sf::VideoMode(X_MAX,Y_MAX),"A star visualisation" );
	window.setFramerateLimit(25);
	sf::Event event;

	int current_mouse_pos_x=1;
	int current_mouse_pos_y=1;


	while (window.isOpen())
	{
		window.pollEvent(event);
				
		if (event.type == sf::Event::Closed)
			window.close();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			//tutaj cos dodac o dodawaniu/usuwaniu przeszkod
			//if (x_from_pixel(sf::Mouse::getPosition(window).x) != current_mouse_pos_x && y_from_pixel(sf::Mouse::getPosition(window).y) != current_mouse_pos_y) {
			//	sf::Mouse::getPosition(window);

				mapka[x_from_pixel(sf::Mouse::getPosition(window).x)][y_from_pixel(sf::Mouse::getPosition(window).y)].isObstacle
					= !mapka[x_from_pixel(sf::Mouse::getPosition(window).x)][y_from_pixel(sf::Mouse::getPosition(window).y)].isObstacle;
			//}
			//current_mouse_pos_x = x_from_pixel(sf::Mouse::getPosition(window).x);
			//current_mouse_pos_y = y_from_pixel(sf::Mouse::getPosition(window).y);
		}
		
		draw_map(mapka, window);
		//window.draw(lines);
		draw_path(test_path,window);
		window.display();
		
	}
}

