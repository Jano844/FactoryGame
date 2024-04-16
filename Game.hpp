

#pragma once


#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // For usleep()


#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#include "Player.hpp"
#include "AssemblyLine.hpp"

#define BACKGROUND "textures/Background.png"
#define PLAYER "textures/Done.png"
#define LEVER_ON "textures/Lever1.png"
#define LEVER_OFF "textures/Lever2.png"
#define PORTAL "textures/Portal.png"
#define PORTALDIFFX 80
#define PORTALDIFFY 64

#define OFFSETX 64
#define OFFSETY 64

class Player;
class AssemblyLine;

class Game
{
private:
	sf::RenderWindow *window;
	sf::VideoMode vMode;
	sf::Event ev;


	// frames counter
	int frames;

	// Textures
	void	initTextures();
	sf::Texture	texture;
	sf::Sprite	sBackground;
	//lever
	void	initLever();
	void	triggerLever();
	sf::Texture	lever1_texture;
	sf::Texture	lever2_texture;
	sf::Sprite	lever1;
	sf::Sprite	lever2;
	int			leverPosX;
	int			leverPosY;
	bool		leverOn;

	// Player
	Player *player;
	std::string partName;

	//AssemblyLine
	AssemblyLine *assemblyLine;
	bool		pickUp;

	// Mouse
	void	initMouse();
	void	updateMousePos();
	void	drawMouse();
	int		animation;
	bool	pressed;
	std::vector<sf::CircleShape> mouse;
	int mousePosX;
	int mousePosY;
	int lastPressedX;
	int lastPressedY;


	void initWindow();
public:
	Game();
	~Game();

	// functions
	bool	isRunning();
	void	pollEvents();
	void	update();
	void	render();
};
