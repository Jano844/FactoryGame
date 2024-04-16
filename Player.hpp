

#pragma once

#include "Game.hpp"

class AssemblyLine;

class Player
{
private:
	sf::Texture 			player_texture;
	std::vector<sf::Sprite>	player;

	float	playerX;
	float	playerY;
	int		playerSprite;
	int 	speed;
	char	playerDir;
	bool	dirChange;

	sf::Texture portal_texture;
	sf::Sprite portal;
	void initParts();
	void setPartPos();
	void drawParts(sf::RenderWindow *window, std::string partName);
	int offsetX;
	int offsetY;
	sf::CircleShape triangle;
	sf::CircleShape square_rotated;
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
	sf::RectangleShape square;
	int rotation;


public:
	Player();
	~Player();

	void	initPlayer();
	void	updatePlayer(int lastPressedX, int lastPressedY);
	void	drawPlayer(int frames, sf::RenderWindow *window, std::string partName);

	// accessors
	void	setSpeed(int value);
	int		getSpeed();
	int		getplayerX();
	int		getplayerY();

};
