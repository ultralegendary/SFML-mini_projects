 //http://freespace.virgin.net/hugo.elias/models/m_perlin.htm

#include"particle.h"
//remove command lines to veiw more
int main(int argc, char** args) {

    srand(time(0));
    PerlinNoise p(time(0));
    sf::CircleShape circle;
    circle.setRadius(10.f);
    circle.setOrigin(5.f, 5.f);
    sf::Clock clock;
    particle parts;
    int scale = 10, reset = 0;
    int rows = 600 / scale, cols = 600 / scale;
    vector<sf::VertexArray> rectangle;
    vector<vector<float>> dirx(rows), diry(cols);
    float angle;
    
    vector<float> angles(rows * cols);

    for (int i = 0; i < rows; i++)
    {

        vector<float> dx, dy;
        sf::VertexArray r(sf::Lines, 2 * rows + 1);

        for (int j = 0; j < cols; j++)
        {
            angle = rand() % int(2 * Pi);
            r[j * 2].position = sf::Vector2f(i * scale, j * scale);
            r[j * 2 + 1].position = sf::Vector2f(i * scale + cos(angle) * scale, j * scale + sin(angle) * scale);
            r[j * 2].color = sf::Color(255, 255, 255, 255);
            r[j * 2 + 1].color = sf::Color(255, 255, 255, 10);
            dx.push_back(cos(angle));
            dy.push_back(sin(angle));
        }
        dirx.push_back(dx);
        diry.push_back(dx);



        rectangle.push_back(r);
        sf::Color c(255, 255, 255, rand() % 255);

    }



    sf::RenderWindow w(sf::VideoMode(600, 600), "Flow field");
    
    w.setFramerateLimit(60);
    std::cout << "\nkey codes:";
    double m, xoff = 0, yoff = 0, m1, incy = 0.01, zoff = 0, xspeed = 0, yspeed = 0, zoom = 0.01, color_multiplier = 255, xref = 10, yref = 10;
    sf::Vector2u w_size = w.getSize();
    xoff = rand() % 100;
    yoff = rand() % 100;
    yspeed = 0.02f;
    xspeed = 0.02f;

    
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
                if(e.key.code==sf::Keyboard::Space)
                {
                    parts.resetparts();
                }
                if (e.key.code == sf::Keyboard::Z)
                    parts.resetparts();
                break;
            }
        }




        yref += yspeed; xref += xspeed;//command this

        yoff = yref;



        for (int i = 0; i < rows; i++)
        {
            xoff = xref;

            yoff += 0.1;
             
            for (int j = 0; j < cols; j++)
            {
                angle = p.noise(xoff, yoff, 0) * 2 * Pi;
                rectangle[i][2 * j].color = sf::Color(p.noise(0,yoff,0)*1000, p.noise(xoff, 0, 0)*1000,0,255);
                rectangle[i][2 * j + 1].position = sf::Vector2f(i * scale + cos(angle) * scale, j * scale  + sin(angle) * scale);
                angles[i * cols + j] = angle;
                xoff += 0.1;

            }
        }

        if (clock.getElapsedTime().asSeconds() > 3.f)
        {
            parts.resetparts();
            clock.restart();
        }
        parts.update(angles);



        w.clear();//uncommand this
        for (int i = 0; i < rows; i++)
        {

              w.draw(rectangle[i]);//uncomand this

        }
        //w.draw(parts);//comment this 
        w.display();




    }




    return 0;
}