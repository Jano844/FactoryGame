
#include "Player.hpp"

Player::Player() : player(48)
{
	initPlayer();
	this->speed = 1;
	this->playerSprite = 0;
	this->playerDir = 'n';
	this->playerX = OFFSETX;
	this->playerY = OFFSETY;
}

Player::~Player()
{

}

void	Player::initPlayer()
{
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
}


void	Player::updatePlayer(int lastPressedX, int lastPressedY)
{
	float vecx = playerX - lastPressedX;
	float vecy = playerY - lastPressedY;

	if (std::fabs(vecx) < 1 && std::fabs(vecy) < 1) {
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
	if (temp != playerDir)
		dirChange = true;
}


void	Player::drawPlayer(int frames, sf::RenderWindow *window)
{
	int first;
	int last;
	if (dirChange == true) {
		if (playerDir == 'r')
			playerSprite = 15;
		else if (playerDir == 'u')
			playerSprite = 11;
		else if (playerDir == 'o')
			playerSprite = 19;
		else
			playerSprite = 0;
	}

	if (playerDir == 'r') {
		first = 16;
		last = 20;
	}
	else if (playerDir == 'u') {
		first = 12;
		last = 16;
	}
	else if (playerDir == 'o') {
		first = 20;
		last = 24;
	}
	else {
		first = 0;
		last = 4;
	}



	if (frames % 20 == 0)
		playerSprite++;
	if (playerSprite >= last)
		playerSprite = first;
	window->draw(player[playerSprite]);
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
