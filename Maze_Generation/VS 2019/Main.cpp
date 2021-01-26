#include"boxes.h"


int main()
{
	srand(static_cast<unsigned int>(time(0)));
	sf::RenderWindow w(sf::VideoMode(800, 800), "MAZE Generation");
	float frames = 10;
	w.setPosition(sf::Vector2i(450, 15));
	w.setFramerateLimit(frames);
	
	sf::Clock framerate;
	boxes grid;
	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{
			switch (e.type)
			{
			case 0:
				w.close();
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Space)
				{
					w.setFramerateLimit(60);
				}

			}
		}
		grid.update_();
		w.clear();
		grid.render(w);
		w.display();
	}
	return 0;
}