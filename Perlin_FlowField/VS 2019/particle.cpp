#include "particle.h"

void particle::resetparts()
{
	for (int i = 0; i < 200; i++)
	{
		particles[i].position.x = (rand() % 600 );
		particles[i].position.y = (rand() % 600 );
		circles[i].setPosition(rand() % 600 ,rand()%600);
		
		if (particles[i].position.x < 0)
		{
			particles[i].position.x = 599;
		}
		else if (particles[i].position.x > 599)
		{
			particles[i].position.x = 0;
		}
		if (particles[i].position.y < 0)
		{
			particles[i].position.y = 599; 
		}
		else if (particles[i].position.y > 599)
		{
			particles[i].position.y = 0;
		}
		if (circles[i].getPosition().x < 0)
		{
			circles[i].setPosition(599, circles[i].getPosition().y);
		}
		else if (circles[i].getPosition().x > 599)
		{
			circles[i].setPosition(0, circles[i].getPosition().y);
		}
		if (circles[i].getPosition().y < 0)
		{
			circles[i].setPosition(circles[i].getPosition().x, 599);
		}
		else if (circles[i].getPosition().y > 599)
		{
			circles[i].setPosition(circles[i].getPosition().x, 0);
		}
	}
}

particle::particle() :particles(sf::Points, 200), circles(200), lines(sf::Lines, 400)
{


	speed = 1.f;
	for (int i = 0; i < 200; i++)
	{
		circles[i].setPosition(sf::Vector2f(rand() % 600, rand() % 600));
		circles[i].setFillColor(sf::Color(255, 255, 255, 1));
		circles[i].setRadius(3.f);
		direction.push_back(sf::Vector2f(cos(rand() % 360 * 2 * Pi / 180), sin(rand() % 360 * 2 * Pi / 180)));
		particles[i].position = sf::Vector2f(rand() % 600, rand() % 600);
		particles[i].color = sf::Color(255, 255, 255, 10);
		lines[2 * i].color = lines[2 * i + 1].color = sf::Color(255, 255, 255, 5);
		/*if (i < 200 / 6)
			particles[i].color = sf::Color(255, 0, 0, 10);
		else if (i < 200 / 6 * 2)
			particles[i].color = sf::Color(0, 255, 0, 10);
		else if (i < 200 / 6 * 3)
			particles[i].color = sf::Color(0, 0, 255, 10);
		else if (i < 200 / 6 * 4)
			particles[i].color = sf::Color(255, 255, 0, 10);
		else if (i < 200 / 6 * 5)
			particles[i].color = sf::Color(255, 0, 255, 10);
		else if (i < 200 / 6 * 6)
			particles[i].color = sf::Color(0, 255, 255, 10);
		else
			particles[i].color = sf::Color(255, 255, 255, 10);
			*/
	}
}

void particle::update(vector<float> angles)
{
	for (int i = 0; i < 200; i++)
	{
		
		direction[i] = sf::Vector2f(cos(angles[int((int(circles[i].getPosition().x) / 10) * 60 + circles[i].getPosition().y / 10)]), sin(angles[int((int(circles[i].getPosition().x) / 10) * 60 + circles[i].getPosition().y / 10)]));
		//direction[i] = sf::Vector2f(cos(angles[int((int(particles[i].position.x) / 10) * 60 + particles[i].position.y / 10)]), sin(angles[int((int(particles[i].position.x) / 10) * 60 + particles[i].position.y / 10)]));
		
		
		circles[i].move(direction[i] * speed);
		lines[2 * i].position = particles[i].position;
		lines[2 * i + 1].position = particles[i].position + direction[i] * speed;
		particles[i].position += direction[i]*speed;
		if (circles[i].getPosition().x < 0)
		{
			circles[i].setPosition(599, circles[i].getPosition().y);
		}
		else if (circles[i].getPosition().x > 599)
		{
			circles[i].setPosition(0, circles[i].getPosition().y);
		}
		if (circles[i].getPosition().y < 0)
		{
			circles[i].setPosition( circles[i].getPosition().x,599);
		}
		else if (circles[i].getPosition().y > 599)
		{
			circles[i].setPosition(circles[i].getPosition().x, 0);
		}
		if (particles[i].position.x < 0)
		{
			particles[i].position.x = 599;
		}
		else if (particles[i].position.x > 599)
		{
			particles[i].position.x = 0;
		}
		if (particles[i].position.y < 0)
		{
			particles[i].position.y = 599;
		}
		else if (particles[i].position.y > 599)
		{
			particles[i].position.y = 0;
		}
	}
	
}

sf::Vector2f particle::getposition(int i)
{
	return circles[i].getPosition();
}

void particle::setdirection(sf::Vector2f d,int i)
{
	direction[i] = d;
}

void particle::draw(sf::RenderTarget&t,sf::RenderStates s) const
{
	for (int i = 0; i < 200; i++)
		t.draw(circles[i]);
	//t.draw(particles);
	//t.draw(lines);
}
