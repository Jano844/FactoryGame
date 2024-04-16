
#include "Player.hpp"

Player::Player() : player(48)
{
	initPlayer();
	initParts();
	this->speed = 1;
	this->playerSprite = 0;
	this->playerDir = 'n';
	this->playerX = OFFSETX;
	this->playerY = OFFSETY;
	this->offsetX = 100;
	this->offsetY = 100;
}

Player::~Player()
{

}

void	Player::initPlayer()
{
	if (!this->portal_texture.loadFromFile(PORTAL))
	{
		std::cout << "Error loading Portal\n";
		exit(1);
	}
	this->portal.setTexture(this->portal_texture);
	if (!this->player_texture.loadFromFile(PLAYER))
	{
		std::cout << "Error loading Player\n";
		exit(1);
	}

	sf::IntRect textureRects[48] = {
		sf::IntRect(000, 0, 128, 128),
		sf::IntRect(128, 0, 128, 128),
		sf::IntRect(256, 0, 128, 128),
		sf::IntRect(384, 0, 128, 128),

		sf::IntRect(000, 128, 128, 128),
		sf::IntRect(128, 128, 128, 128),
		sf::IntRect(256, 128, 128, 128),
		sf::IntRect(384, 128, 128, 128),

		sf::IntRect(000, 256, 128, 128),
		sf::IntRect(128, 256, 128, 128),
		sf::IntRect(256, 256, 128, 128),
		sf::IntRect(384, 256, 128, 128),

		sf::IntRect(000, 384, 128, 128),
		sf::IntRect(128, 384, 128, 128),
		sf::IntRect(256, 384, 128, 128),
		sf::IntRect(384, 384, 128, 128),

		sf::IntRect(000, 512, 128, 128),
		sf::IntRect(128, 512, 128, 128),
		sf::IntRect(256, 512, 128, 128),
		sf::IntRect(384, 512, 128, 128),

		sf::IntRect(000, 640, 128, 128),
		sf::IntRect(128, 640, 128, 128),
		sf::IntRect(256, 640, 128, 128),
		sf::IntRect(384, 640, 128, 128),

		sf::IntRect(000, 768, 128, 128),
		sf::IntRect(128, 768, 128, 128),
		sf::IntRect(256, 768, 128, 128),
		sf::IntRect(384, 768, 128, 128),

		sf::IntRect(000, 896, 128, 128),
		sf::IntRect(128, 896, 128, 128),
		sf::IntRect(256, 896, 128, 128),
		sf::IntRect(384, 896, 128, 128),

		sf::IntRect(000, 1024, 128, 128),
		sf::IntRect(128, 1024, 128, 128),
		sf::IntRect(256, 1024, 128, 128),
		sf::IntRect(384, 1024, 128, 128),

		sf::IntRect(000, 1152, 128, 128),
		sf::IntRect(128, 1152, 128, 128),
		sf::IntRect(256, 1152, 128, 128),
		sf::IntRect(384, 1152, 128, 128),

		sf::IntRect(000, 1280, 128, 128),
		sf::IntRect(128, 1280, 128, 128),
		sf::IntRect(256, 1280, 128, 128),
		sf::IntRect(384, 1280, 128, 128),

		sf::IntRect(000, 1408, 128, 128),
		sf::IntRect(128, 1408, 128, 128),
		sf::IntRect(256, 1408, 128, 128),
		sf::IntRect(384, 1408, 128, 128)
	};
	for (int i = 0; i < 48; ++i) {
		player[i] = sf::Sprite(this->player_texture, textureRects[i]);
		player[i].setPosition(playerX, playerY);
	}
	this->portal.setPosition(playerX + PORTALDIFFX, playerY + PORTALDIFFX);
}

void Player::initParts()
{
	// Triangle
	triangle = sf::CircleShape(25, 3);
	triangle.setFillColor(sf::Color::Cyan);
	triangle.setPosition(playerX, playerY);

	// Square rotated
	square_rotated = sf::CircleShape(25, 4);
	square_rotated.setFillColor(sf::Color::Red);
	square_rotated.setPosition(playerX, playerY);

	// Circle
	circle = sf::CircleShape(22);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(playerX, playerY);

	// Rectangle
	rectangle = sf::RectangleShape(sf::Vector2f(50, 30));
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(playerX, playerY);

	// Square
	square = sf::RectangleShape(sf::Vector2f(40, 40));
	square.setFillColor(sf::Color::Magenta);
	square.setPosition(playerX, playerY);
}

void	Player::updatePlayer(int lastPressedX, int lastPressedY)
{
	float vecx = playerX - lastPressedX;
	float vecy = playerY - lastPressedY;

	if (std::fabs(vecx) < 4 && std::fabs(vecy) < 4) {
		playerDir = '0';
		return ;
	}
	char temp = playerDir;
	if (std::fabs(vecx) > std::fabs(vecy)) {
		// walk one in x dir
		if (vecx < 0) { // rechts
			playerX += (1 * speed);
			playerDir = 'r';
		}
		else { // links
			playerX -= (1 * speed);
			playerDir = 'l';
		}
		if (vecy < 0)
			playerY += std::fabs(vecy / vecx) * speed;
		else
			playerY -= std::fabs(vecy / vecx) * speed;
	}
	else {
		// walk one in y dir
		if (vecy < 0) {// unten
			playerY += (1 * speed);
			playerDir = 'u';
		}
		else { // oben
			playerY -= (1 * speed);
			playerDir = 'o';
		}
		if (vecx < 0)
			playerX += std::fabs(vecx / vecy) * speed;
		else
			playerX -= std::fabs(vecx / vecy) * speed;
	}
	for (int i = 0; i < 12 * 4; i++) {
		player[i].setPosition((playerX), playerY);
	}
	portal.setPosition(playerX + PORTALDIFFX, playerY + PORTALDIFFY);
	if (temp != playerDir)
		dirChange = true;
}


void	Player::setPartPos()
{
	triangle.setPosition(playerX + 5 + offsetX, playerY + offsetY - 10);
	square_rotated.setPosition(playerX + offsetX + 15, playerY + offsetY - 5);
	circle.setPosition(playerX + offsetX + 15, playerY + offsetY);
	rectangle.setPosition(playerX + offsetX + 12, playerY + offsetY + 5);
	square.setPosition(playerX + offsetX + 12, playerY + offsetY + 5);
}

void	Player::drawParts(sf::RenderWindow *window, std::string partName)
{
	// std::cout << partName << std::endl;
	triangle.setFillColor(sf::Color::Transparent);
	square_rotated.setFillColor(sf::Color::Transparent);
	circle.setFillColor(sf::Color::Transparent);
	rectangle.setFillColor(sf::Color::Transparent);
	square.setFillColor(sf::Color::Transparent);

	std::transform(partName.begin(), partName.end(), partName.begin(), ::tolower);
	if (partName == "triangle")
		triangle.setFillColor(sf::Color::Cyan);
	if (partName == "square_rotated")
		square_rotated.setFillColor(sf::Color::Red);
	if (partName == "circle")
		circle.setFillColor(sf::Color::Green);
	if (partName == "rectangle")
		rectangle.setFillColor(sf::Color::Yellow);
	if (partName == "square")
		square.setFillColor(sf::Color::Magenta);

	window->draw(triangle);
	window->draw(square_rotated);
	window->draw(circle);
	window->draw(rectangle);
	window->draw(square);
}

void	Player::drawPlayer(int frames, sf::RenderWindow *window, std::string partName)
{
	int first;
	int last;
	if (dirChange == true) {
		if (playerDir == 'r') {
			playerSprite = 15;
		}
		else if (playerDir == 'u') {
			playerSprite = 11;
		}
		else if (playerDir == 'o') {
			playerSprite = 19;
		}
		else {
			playerSprite = 0;
		}
	}

	if (playerDir == 'r') {
		first = 16;
		last = 20;
		this->offsetX = 124;
		this->offsetY = 50;
		this->portal.setRotation(0);
	}
	else if (playerDir == 'u') {
		first = 12;
		last = 16;
		this->offsetX = 100;
		this->offsetY = 100;
		this->portal.setRotation(35);
	}
	else if (playerDir == 'o') {
		first = 20;
		last = 24;
		this->offsetX = 120;
		this->offsetY = 0;
		this->portal.setRotation(-35);
	}
	else {
		first = 0;
		last = 4;
		this->offsetX = 100;
		this->offsetY = 100;
		this->portal.setRotation(35);
	}

	setPartPos();

	if (frames % 20 == 0)
		playerSprite++;
	if (playerSprite >= last)
		playerSprite = first;
	if (playerDir == 'o') {
		window->draw(portal);
		window->draw(player[playerSprite]);
	}
	else {
		window->draw(player[playerSprite]);
		window->draw(portal);
	}
	drawParts(window, partName);
	dirChange = false;
}

void	Player::setSpeed(int value) {
	this->speed = value;
}

int		Player::getSpeed() {
	return this->speed;
}

int		Player::getplayerX() {
	return this->playerX;
}

int		Player::getplayerY() {
	return this->playerY;
}
