

#pragma once

#include "Game.hpp"

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
public:
	Player();
	~Player();

	void	initPlayer();
	void	updatePlayer(int lastPressedX, int lastPressedY);
	void	drawPlayer(int frames, sf::RenderWindow *window);

	// accessors
	void	setSpeed(int value);
	int		getSpeed();
	int		getplayerX();
	int		getplayerY();

};
