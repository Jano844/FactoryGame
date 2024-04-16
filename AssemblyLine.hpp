
#pragma once

#include "Game.hpp"
#include <limits>

#define FACTORY "textures/Factory_new.png"

class Player;

class AssemblyLine
{
private:
	// init
	void initBase();
	sf::Texture factory_texture;
	sf::Sprite factory;
	sf::RectangleShape part1;
	sf::RectangleShape part2;

	void initParts();
	sf::CircleShape triangle;
	sf::CircleShape square_rotated;
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
	sf::RectangleShape square;

	// part Flags
	bool first_spwan_ractangle;
	bool first_spwan_circle;
	bool first_spwan_triangle;
	bool first_spwan_square_rotated;
	bool pickedUp;
	bool leverState;
	std::string partName;

	// pick up part / lay back
	void pickUpPart(Player &player);
	void layBack(Player &player);

	void initDestionation();
	void resetDestination();
	void drawDestination(sf::RenderWindow *window);
	void dropPart(Player &player);
	bool newDestination;
	std::string destinationName;
	sf::RectangleShape destination;
	sf::CircleShape drop_triangle;
	sf::CircleShape drop_square_rotated;
	sf::CircleShape drop_circle;
	sf::RectangleShape drop_rectangle;
	sf::RectangleShape drop_square;

public:
	AssemblyLine();
	~AssemblyLine();

	void	updateAsseblyLine(bool leverOn, bool pickup, Player &player);
	void	drawAsseblyLine(sf::RenderWindow *window, Player *player, int frames);

	std::string getPartName();
};
