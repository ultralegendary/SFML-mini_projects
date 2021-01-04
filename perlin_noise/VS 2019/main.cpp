 //http://freespace.virgin.net/hugo.elias/models/m_perlin.htm

#include"PerlinNoise.h"
#include<iostream>
#include<cmath>
#include<sstream>
#include<SFML/Graphics.hpp>
#define Pi 3.14159265
using namespace std;

int main(int argc, char** args) {
    
    srand(time(0));
    PerlinNoise p(time(0));
    stringstream s;
    int one_D = 0;
    sf::CircleShape circle;
    circle.setRadius(10.f);
    circle.setOrigin(5.f, 5.f);
    
    sf::Texture t_arrow;
    sf::Sprite s_arrow;
    s_arrow.setOrigin(25, 25);
    s_arrow.setPosition(275, 25);
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    t_arrow.loadFromFile("direction_key.png");
    s_arrow.setTexture(t_arrow);
    sf::RenderWindow w(sf::VideoMode(300, 300), "prelin tests");
    w.setFramerateLimit(60);
    std::cout << "\nkey codes:\nUse arrow keys to move\n'z' - zoom in\n'x' - zoom out\n'Q' - to increase color muiltipliyer\n'W'- to decrease color muiltipliyer";
    double m,xoff=0,yoff=0,m1,incy=0.01,zoff=0,xspeed=0,yspeed=0,zoom=0.01,color_multiplier=255,xref=0,yref=0;
    sf::Vector2u w_size = w.getSize();
    sf::VertexArray vertices(sf::Points, 200 * 200),line(sf::LinesStrip,300);
    sf::Color pixel_color=sf::Color::Red;
    s << "Color multiplier : " << abs(color_multiplier) << "\nZoom : " << abs(zoom)<<"\nRepresentation of 2D PRELIN NOISE\n in 3D graph";
    text.setString(s.str());

    for (int i = 0; i < 200; i++)
    {
        yoff += 0.01;
        xoff = 0;
        for (int j = 0; j < 200; j++)
        {
            xoff += 0.01;
            float a = p.noise(xoff,yoff,0);
            vertices[i * 200 + j].position = sf::Vector2f(i+100 ,100+ j); 
            pixel_color.b = a*255;
            pixel_color.g = a*255;
            pixel_color.r = a*255;
            vertices[i * 200 + j].color = pixel_color;
        }
    }
    
    


    while (w.isOpen())
    {
        sf::Event e;
        while (w.pollEvent(e))
        {
            switch (e.type)
            {
            case 0:
                w.close();
                break;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Space)
                {
                    one_D++; one_D %= 3;
                    xoff = rand() % 100;
                    yoff = rand() % 100;
                    yspeed = xspeed = zoom = 0.01f;
                    incy = 1;
                }
                s.str("");
                if (!one_D)
                {
                    if (e.key.code == sf::Keyboard::Up)
                        xspeed -= 0.01;

                    else if (sf::Keyboard::Down == e.key.code)
                        xspeed += 0.01;

                    if (sf::Keyboard::Right == e.key.code)
                        yspeed += 0.01;

                    else if (sf::Keyboard::Left == e.key.code)
                        yspeed -= 0.01;
                    if (xspeed == 0)
                        xspeed = 0.000000000000001;
                    if (yspeed == 0)
                        yspeed = 0.000000000000001;
                    if (yspeed > 0 && xspeed < 0)
                        s_arrow.setRotation(180 / Pi * asin(yspeed / sqrt(yspeed * yspeed + xspeed * xspeed)) + 0);
                    else if (yspeed > 0 && xspeed > 0)
                        s_arrow.setRotation(-180 / Pi * asin(yspeed / sqrt(yspeed * yspeed + xspeed * xspeed)) - 180);
                    else if (yspeed < 0 && xspeed > 0)
                        s_arrow.setRotation(-180 / Pi * asin(yspeed / sqrt(yspeed * yspeed + xspeed * xspeed)) + 180);
                    else if (yspeed < 0 && xspeed < 0)
                        s_arrow.setRotation(180 / Pi * asin(yspeed / sqrt(yspeed * yspeed + xspeed * xspeed)) + 0);

                    if (sf::Keyboard::Z == e.key.code)
                    {
                        if (abs(zoom) < 1)
                            zoom -= 0.001;
                        else
                            zoom -= 0.01;
                    }


                    else if (sf::Keyboard::X == e.key.code)
                    {
                        if (abs(zoom) < 1)
                            zoom += 0.001;
                        else
                            zoom += 0.01;
                    }
                    if (sf::Keyboard::Q == e.key.code)
                    {
                        color_multiplier += 10;
                    }
                    else if (sf::Keyboard::W == e.key.code)
                    {
                        color_multiplier -= 10;
                    }
                    
                    s << "Color multiplier : " << abs(color_multiplier) << "\nZoom : " << abs(zoom)<<"\nRepresentation of 2D PRELIN NOISE\n in 3D graph";
                    
                }
                else if (one_D == 1)
                {
                    s << "Representation of 2D perlin with time";
                }
                else if (one_D == 2) {
                    if (sf::Keyboard::Z == e.key.code)
                    {
                        if (abs(xspeed) < 0.01)
                            xspeed += 0.001;
                        else
                            xspeed += 0.01;
                        incy+=0.1;
                    }
                    else if (sf::Keyboard::X == e.key.code)
                    {
                        if (abs(xspeed) < 0.01)
                            xspeed -= 0.001;
                        else
                            xspeed -= 0.01;
                        incy-=0.1;
                    }

                    if (sf::Keyboard::Right == e.key.code)
                        yspeed += 0.01;

                    else if (sf::Keyboard::Left == e.key.code)
                        yspeed -= 0.01;
                    
                    s << "Zoom : " << abs(xspeed)<<"\nRepresentation of 1D PERLIN NOISE\n with time";
                    
                }
                text.setString(s.str());
                break;
            }
        }

        if (!one_D)
        {
            yref += yspeed;
            yoff = yref;

            xref += xspeed;
            for (int i = 0; i < 200; i++)
            {

                xoff = xref;
                yoff += zoom;
                for (int j = 0; j < 200; j++)
                {
                    xoff += zoom;
                    float a = p.noise(xoff, yoff, 0) * color_multiplier;
                    pixel_color.b = a;
                    pixel_color.g = a;
                    pixel_color.r = a;
                    vertices[i * 200 + j].color = pixel_color;
                }
            }

        }
        else if(one_D==1)
        {
            xoff += 0.05; yoff += 0.05;
            float t1 = p.noise(xoff, 0, 0)*300, t2 = p.noise(0, yoff, 0)*300;
            circle.setPosition(sf::Vector2f(t1, t2));

        }
        else
        {
            yoff += yspeed;
            xoff = yoff;
            for (int i = 0; i < 300; i++)
            {
                xoff += xspeed;
                line[i].position = sf::Vector2f(i,p.noise(xoff,0,0)*300);
            }

        }
        
        w.clear();
        if (!one_D)
        {
            w.draw(vertices);
            w.draw(s_arrow);
            
        }
        else if (one_D == 1)
        {
            w.draw(circle);
        }
        else
            w.draw(line);
        w.draw(text);
        w.display();
            
    }




    
    return 0;
}