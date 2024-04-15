

#include "Game.hpp"

void	Game::drawMouse()
{
	if (pressed == false || frames % 3 == 0)
		return ;
	window->draw(mouse[animation]);
	animation++;
	if (animation >= 3) {
		animation = 0;
		pressed = false;
	}
}

void	Game::initMouse() {
	mousePosX = 0;
	mousePosY = 0;
	lastPressedX = OFFSETX * 2;
	lastPressedY = OFFSETY * 2;
	pressed	= false;
	animation = 0;
	mouse[0] = sf::CircleShape(5.f);
	mouse[0].setFillColor(sf::Color::White);
	mouse[0].setPosition(0.f, 0.f);
	mouse[1] = sf::CircleShape(10.f);
	mouse[1].setFillColor(sf::Color::White);
	mouse[1].setPosition(0.f, 0.f);
	mouse[2] = sf::CircleShape(15.f);
	mouse[2].setFillColor(sf::Color::White);
	mouse[2].setPosition(0.f, 0.f);
}


void	Game::initLever() {
	this->leverPosX = 30;
	this->leverPosY = 350;
	this->leverOn = false;
	if (!this->lever1_texture.loadFromFile(LEVER_OFF))
	{
		std::cout << "Error loading Lever1\n";
		exit(1);
	}
	this->lever1.setTexture(this->lever1_texture);
	this->lever1.setPosition(0, 350);

	if (!this->lever2_texture.loadFromFile(LEVER_ON))
	{
		std::cout << "Error loading Lever2\n";
		exit(1);
	}
	this->lever2.setTexture(this->lever2_texture);
	this->lever2.setPosition(0, 350);
}

void	Game::triggerLever()
{
	int vecx = std::abs(player->getplayerX() - leverPosX);
	int vecy = std::abs(player->getplayerY() - leverPosY);

	float veclen = sqrt(pow(vecy, 2) + pow(vecx, 2));
	if (veclen < 80) {
		if (this->leverOn == true)
			this->leverOn = false;
		else
			this->leverOn = true;
	}
}



Game::Game() : mouse(3) {
	initWindow();
	initTextures();
	initMouse();
	initLever();
	player = new Player();
	assemblyLine = new AssemblyLine();
}


Game::~Game() {
	delete this->window;
	delete this->player;
	delete this->assemblyLine;
}


void	Game::initTextures() {
	if (!this->texture.loadFromFile(BACKGROUND))
	{
		std::cout << "Error loading Background\n";
		exit(1);
	}
	this->sBackground.setTexture(this->texture);
}


void	Game::initWindow() {
	this->frames = 0;
	this->vMode.height = 576;
	this->vMode.width = 1024;


	this->window = new sf::RenderWindow(this->vMode, "First game!", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(100);
}


bool	Game::isRunning() {
	return this->window->isOpen();
}

void	Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;


		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
				break;
			} if (ev.key.code == sf::Keyboard::Space) {
				triggerLever();
				break;
			} if (ev.key.code == sf::Keyboard::E) {
				pickUp = true;
				break;
			}
			break;
		default:
			break;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		pressed = true;
		lastPressedX = mousePosX - OFFSETX;
		lastPressedY = mousePosY - OFFSETY;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		player->setSpeed(2);
	else
		player->setSpeed(1);
}


void	Game::updateMousePos() {
	mousePosX = sf::Mouse::getPosition(*window).x;
	mousePosY = sf::Mouse::getPosition(*window).y;
	for (int i = 0; i < 3; i++) {
		mouse[i].setPosition(mousePosX - (i * 7.5f), mousePosY - (i * 7.5f));
	}
}

void	Game::update() {
	pollEvents();
	updateMousePos();
	player->updatePlayer(lastPressedX, lastPressedY);
	assemblyLine->updateAsseblyLine(this->leverOn, this->pickUp, *player);
	this->pickUp = false;
	frames++;
	if (frames > 100)
		frames = 0;
}

void	Game::render() {
	// clear old frame
	this->window->clear();

	// draw Game
	window->draw(this->sBackground);
	player->drawPlayer(frames, window);

	if (leverOn == true)
		window->draw(this->lever2);
	else
		window->draw(this->lever1);

	assemblyLine->drawAsseblyLine(window);


	drawMouse();


	this->window->display();
}
