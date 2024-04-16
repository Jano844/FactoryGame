

#include "AssemblyLine.hpp"

AssemblyLine::AssemblyLine()
{
	initBase();
	initParts();
	initDestionation();
}

AssemblyLine::~AssemblyLine()
{
}

void AssemblyLine::initBase()
{
	// Factory
	pickedUp = false;
	if (!factory_texture.loadFromFile(FACTORY))
	{
		std::cout << "Error loading factory\n";
		exit(1);
	}
	this->factory.setTexture(factory_texture);
	this->factory.setPosition(290, 270);

	// Line
	part1 = sf::RectangleShape(sf::Vector2f(410, 50));
	part1.setOutlineColor(sf::Color(255, 136, 0, 255));
	part1.setOutlineThickness(4);
	part1.setFillColor(sf::Color(81, 86, 92, 255));
	part1.setPosition(0, 430);

	part2 = sf::RectangleShape(sf::Vector2f(410, 35));
	part2.setFillColor(sf::Color(41, 49, 51, 255));
	part2.setPosition(0, 470);
}

void AssemblyLine::initParts()
{
	// Triangle
	triangle = sf::CircleShape(25, 3);
	triangle.setFillColor(sf::Color::Cyan);
	triangle.setPosition(400, 435);
	first_spwan_triangle = false;

	// Square rotated
	square_rotated = sf::CircleShape(25, 4);
	square_rotated.setFillColor(sf::Color::Red);
	square_rotated.setPosition(400, 430);
	first_spwan_square_rotated = false;

	// Circle
	circle = sf::CircleShape(22);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(400, 434);
	first_spwan_circle = false;

	// Rectangle
	rectangle = sf::RectangleShape(sf::Vector2f(50, 30));
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(400, 440);
	first_spwan_ractangle = false;

	// Square
	square = sf::RectangleShape(sf::Vector2f(40, 40));
	square.setFillColor(sf::Color::Magenta);
	square.setPosition(400, 435);
}

void AssemblyLine::initDestionation()
{
	// Destination
	newDestination = true;
	destination = sf::RectangleShape(sf::Vector2f(70, 70));
	destination.setFillColor(sf::Color(81, 86, 92, 255));
	destination.setPosition(795, 95);

	drop_triangle = sf::CircleShape(25, 3);
	drop_triangle.setFillColor(sf::Color::Black);
	drop_triangle.setPosition(806, 110);

	drop_square_rotated = sf::CircleShape(25, 4);
	drop_square_rotated.setFillColor(sf::Color::Black);
	drop_square_rotated.setPosition(806, 105);

	drop_circle = sf::CircleShape(22);
	drop_circle.setFillColor(sf::Color::Black);
	drop_circle.setPosition(808, 107);

	drop_rectangle = sf::RectangleShape(sf::Vector2f(50, 30));
	drop_rectangle.setFillColor(sf::Color::Black);
	drop_rectangle.setPosition(805, 114);

	drop_square = sf::RectangleShape(sf::Vector2f(40, 40));
	drop_square.setFillColor(sf::Color::Black);
	drop_square.setPosition(809, 110);
}

void	AssemblyLine::resetDestination()
{
	srand(time(NULL));
	int random = rand() % 5;
	if (random == 0)
		this->destinationName = "Triangle";
	if (random == 1)
		this->destinationName = "Square_rotated";
	if (random == 2)
		this->destinationName = "Circle";
	if (random == 3)
		this->destinationName = "Rectangle";
	if (random == 4)
		this->destinationName = "Square";
}

void	AssemblyLine::drawDestination(sf::RenderWindow *window)
{
	if (newDestination == true) {
		resetDestination();
		newDestination = false;
	}
	window->draw(destination);
	if (destinationName == "Triangle")
		window->draw(drop_triangle);
	if (destinationName == "Square_rotated")
		window->draw(drop_square_rotated);
	if (destinationName == "Circle")
		window->draw(drop_circle);
	if (destinationName == "Rectangle")
		window->draw(drop_rectangle);
	if (destinationName == "Square")
		window->draw(drop_square);

}

void AssemblyLine::dropPart(Player &player)
{
	float dist = sqrt(pow((player.getplayerX() + OFFSETX) - (destination.getPosition().x + 35), 2) + pow(player.getplayerY() - destination.getPosition().y + 35, 2));
	if (dist > 200)
		return ;
	if (destinationName == "Triangle" && partName == "Triangle") {
		this->partName = "";
		pickedUp = false;
		newDestination = true;
		pickedUp = false;
		return ;
	}
	if (destinationName == "Square_rotated" && partName == "Square_rotated") {
		this->partName = "";
		pickedUp = false;
		newDestination = true;
		pickedUp = false;
		return ;
	}
	if (destinationName == "Circle" && partName == "Circle") {
		this->partName = "";
		pickedUp = false;
		newDestination = true;
		pickedUp = false;
		return ;
	}
	if (destinationName == "Rectangle" && partName == "Rectangle") {
		this->partName = "";
		pickedUp = false;
		newDestination = true;
		pickedUp = false;
		return ;
	}
	if (destinationName == "Square" && partName == "Square") {
		this->partName = "";
		pickedUp = false;
		newDestination = true;
		pickedUp = false;
		return ;
	}
}

void AssemblyLine::pickUpPart(Player &player)
{
	// std::cout << "Picking up part\n";
	float lenRect = sqrt(pow((player.getplayerX() + OFFSETX) - (rectangle.getPosition().x + 20), 2) + pow(player.getplayerY() - rectangle.getPosition().y, 2));
	float lenCirc = sqrt(pow((player.getplayerX() + OFFSETX) - (circle.getPosition().x + 20), 2) + pow(player.getplayerY() - circle.getPosition().y, 2));
	float lenTri = sqrt(pow((player.getplayerX() + OFFSETX) - (triangle.getPosition().x + 20), 2) + pow(player.getplayerY() - triangle.getPosition().y, 2));
	float lenSqu = sqrt(pow((player.getplayerX() + OFFSETX) - (square.getPosition().x + 20), 2) + pow(player.getplayerY() - square.getPosition().y, 2));
	float lenSquRot = sqrt(pow((player.getplayerX() + OFFSETX) - (square_rotated.getPosition().x + 20), 2) + pow(player.getplayerY() - square_rotated.getPosition().y, 2));

	float min = std::numeric_limits<float>::max();

	if (lenRect < min) {
		min = lenRect;
		partName = "Rectangle";
	}
	if (lenCirc < min) {
		min = lenCirc;
		partName = "Circle";
	}
	if (lenTri < min) {
		min = lenTri;
		partName = "Triangle";
	}
	if (lenSqu < min) {
		min = lenSqu;
		partName = "Square";
	}
	if (lenSquRot < min) {
		min = lenSquRot;
		partName = "Square_rotated";
	}
	// std::cout << "Picking up " << partName << std::endl;
	// std::cout << "Min: " << min << std::endl;
	if (min > 150) {
		partName = "";
		return ;
	}
	pickedUp = true;
	if (partName == "Rectangle")
		rectangle.setFillColor(sf::Color::Transparent);
	if (partName == "Circle")
		circle.setFillColor(sf::Color::Transparent);
	if (partName == "Triangle")
		triangle.setFillColor(sf::Color::Transparent);
	if (partName == "Square")
		square.setFillColor(sf::Color::Transparent);
	if (partName == "Square_rotated")
		square_rotated.setFillColor(sf::Color::Transparent);
}

void AssemblyLine::layBack(Player &player)
{
	float lenRect = sqrt(pow((player.getplayerX() + OFFSETX) - (rectangle.getPosition().x + 20), 2) + pow(player.getplayerY() - rectangle.getPosition().y, 2));
	float lenCirc = sqrt(pow((player.getplayerX() + OFFSETX) - (circle.getPosition().x + 20), 2) + pow(player.getplayerY() - circle.getPosition().y, 2));
	float lenTri = sqrt(pow((player.getplayerX() + OFFSETX) - (triangle.getPosition().x + 20), 2) + pow(player.getplayerY() - triangle.getPosition().y, 2));
	float lenSqu = sqrt(pow((player.getplayerX() + OFFSETX) - (square.getPosition().x + 20), 2) + pow(player.getplayerY() - square.getPosition().y, 2));
	float lenSquRot = sqrt(pow((player.getplayerX() + OFFSETX) - (square_rotated.getPosition().x + 20), 2) + pow(player.getplayerY() - square_rotated.getPosition().y, 2));

	if (partName == "Rectangle" && lenRect < 150) {
		rectangle.setFillColor(sf::Color::Yellow);
		this->partName = "";
		pickedUp = false;
		return ;
	}
	if (partName == "Circle" && lenCirc < 150) {
		circle.setFillColor(sf::Color::Green);
		this->partName = "";
		pickedUp = false;
		return ;
	}
	if (partName == "Triangle" && lenTri < 150) {
		triangle.setFillColor(sf::Color::Cyan);
		this->partName = "";
		pickedUp = false;
		return ;
	}
	if (partName == "Square" && lenSqu < 150) {
		square.setFillColor(sf::Color::Magenta);
		this->partName = "";
		pickedUp = false;
		return ;
	}
	if (partName == "Square_rotated" && lenSquRot < 150) {
		square_rotated.setFillColor(sf::Color::Red);
		this->partName = "";
		pickedUp = false;
		return ;
	}
}





void AssemblyLine::updateAsseblyLine(bool leverOn, bool pickup, Player &player)
{
	if (pickup == true)
		dropPart(player);
	if (leverOn == true) {
		this->leverState = leverOn;
		if (pickup == true) {
			// std::cout << "Picking up part\n";
			if (this->pickedUp == false)
				pickUpPart(player);
			else
				layBack(player);
		}
		return ;
	}
	this->square.move(-1, 0);
	if (this->square.getPosition().x < -200) {
		this->square.setPosition(400, 435);
		this->square.setFillColor(sf::Color::Magenta);
	}

	if (first_spwan_ractangle == true) {
		this->rectangle.move(-1, 0);
		if (this->rectangle.getPosition().x < -200) {
			this->rectangle.setPosition(400, 440);
			this->rectangle.setFillColor(sf::Color::Yellow);
		}
	}

	if (first_spwan_circle == true) {
		this->circle.move(-1, 0);
		if (this->circle.getPosition().x < -200) {
			this->circle.setPosition(400, 434);
			this->circle.setFillColor(sf::Color::Green);
		}
	}

	if (first_spwan_triangle == true) {
		this->triangle.move(-1, 0);
		if (this->triangle.getPosition().x < -200) {
			this->triangle.setPosition(400, 435);
			this->triangle.setFillColor(sf::Color::Cyan);
		}
	}

	if (first_spwan_square_rotated == true) {
		this->square_rotated.move(-1, 0);
		if (this->square_rotated.getPosition().x < -200) {
			this->square_rotated.setPosition(400, 430);
			this->square_rotated.setFillColor(sf::Color::Red);
		}
	}
}

void AssemblyLine::drawAsseblyLine(sf::RenderWindow *window, Player *player, int frames)
{
	// std::cout << "Drawing AssemblyLine\n";
	static int i;
	i++;
	window->draw(this->part2);
	window->draw(this->part1);

	window->draw(this->square);

	if (first_spwan_ractangle == false && i > 80)
		first_spwan_ractangle = true;
	if (first_spwan_ractangle == true)
		window->draw(this->rectangle);

	if (first_spwan_circle == false && i > 160)
		first_spwan_circle = true;
	if (first_spwan_circle == true)
		window->draw(this->circle);

	if (first_spwan_triangle == false && i > 230)
		first_spwan_triangle = true;
	if (first_spwan_triangle == true)
		window->draw(this->triangle);

	if (first_spwan_square_rotated == false && i > 300)
		first_spwan_square_rotated = true;
	if (first_spwan_square_rotated == true)
		window->draw(this->square_rotated);

	drawDestination(window);
	player->drawPlayer(frames, window, this->partName);
	window->draw(this->factory);
}

std::string AssemblyLine::getPartName()
{
	return this->partName;
}

