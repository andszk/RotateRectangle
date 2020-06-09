#include <iostream>
#include <SFML/Graphics.hpp>
#include <boost/random.hpp>
#include <boost/random/beta_distribution.hpp>

typedef boost::random::mt19937 gen_type;
typedef boost::random::beta_distribution<> beta_dist_type;
typedef boost::random::variate_generator<gen_type&, beta_dist_type> variate_gen_type;

double get_random()
{
    // values for median = 0.33 for beta dist
    float alpha = 1.71347194248032f;
    float beta = 5.f;
    int max = 100;
    int min = 10;

    gen_type random_generator(time(NULL));
    beta_dist_type beta_dist(alpha, beta);
    variate_gen_type random_beta_generator(random_generator, beta_dist);
    return (random_beta_generator() * (max - min)) + min;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "");
    sf::RectangleShape shape(sf::Vector2f(50, 100));
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(25, 50);
    shape.setPosition(150, 150);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.rotate(1);
        window.draw(shape);
        window.display();
        get_random();
    }

    return 0;
}

