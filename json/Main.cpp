#include <SFML/Graphics.hpp>
#include "json.h"

char jsonStr[1000];
char result[50];

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sprintf_s(jsonStr, "{\"root\":{\"Info\":{\"Total sales\":[\"Daily sales\",\"Monthly sales\",\"Yearly sales\"],\"Time Runs\":[\"Cooling\",\"Heater\"]},\"Dispense\":[\"STACK\",\"REJECT\"]}}");

	jsonInit(jsonStr);

	get((char *)&result);
	//iSetMenuStr(result);
	//iMenuUpdate();
	select(0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}