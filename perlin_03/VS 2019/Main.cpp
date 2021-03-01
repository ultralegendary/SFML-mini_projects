#include"perlin_points.h"
int main()
{
	srand(time(0));
	perlin_points points;
	sf::Text frametext;
	sf::Font font;
	sf::RenderWindow w(sf::VideoMode(600, 600), "perlin");
	w.setPosition(sf::Vector2i(400, 10));
	w.setFramerateLimit(60);
	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				w.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					points.change_m(10);
				}
				else if( sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					points.change_m(-10);
				}

				break;
			
				

			default:
				break;
			}
		}
		points.update();
		w.clear();
		w.draw(points);
		w.display();

	}
	return 0;
}