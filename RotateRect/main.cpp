#include <iostream>
#include <SFML/Graphics.hpp>
#include <boost/random.hpp>
#include <boost/random/beta_distribution.hpp>

typedef boost::random::mt19937 gen_type;
typedef boost::random::beta_distribution<> beta_dist_type;
typedef boost::random::uniform_real_distribution<> uniform_dist_type;
typedef boost::random::variate_generator<gen_type&, beta_dist_type> beta_gen_type;
typedef boost::random::variate_generator<gen_type&, uniform_dist_type> uniform_gen_type;

// values for median = 0.33 for beta dist
//const float alpha = 1.71347194248032f;
//const float beta = 5.f;

//const float alpha = 1.5f;
//const float beta = 4.29304676159030f;

const float alpha = 0.797341459119764;
const float beta = 2;

const int max = 100;
const int min = 10;
// Hz
double angular_speed;
gen_type random_generator(time(NULL));
uniform_dist_type uniform_dist(0.2, 2);
uniform_gen_type random_uniform_generator(random_generator, uniform_dist);
beta_dist_type beta_dist(alpha, beta);
beta_gen_type random_beta_generator(random_generator, beta_dist);

double get_random_beta()
{
    return (random_beta_generator() * (max - min)) + min;
}

double get_random_uniform()
{
    return random_uniform_generator();
}

int main()
{
    angular_speed = get_random_uniform() * 360;

    sf::RenderWindow window(sf::VideoMode(300, 300), "");
    sf::RectangleShape shape(sf::Vector2f(50, 100));
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(25, 50);
    shape.setPosition(150, 150);
    sf::Clock clock;

    while (window.isOpen())
    {
        float delay = get_random_beta();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        while (clock.getElapsedTime().asSeconds() < delay/1000)
        {
        }

        float deg = clock.getElapsedTime().asSeconds() * angular_speed;
        //std::cout << "delay: " << delay << " rotate: "<< deg << " speed: "<< deg/delay << " ang_speed: " << angular_speed << " ratio: " << (deg/delay)/angular_speed << std::endl;
        shape.rotate(deg);
        window.draw(shape);
        window.display();

        clock.restart();
    }

    return 0;
}