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
const float alpha = 0.797341459119764;
const float beta = 2;

const int max = 100;
const int min = 10;
int rotation_counter = 0;
int time_to_run = 0;
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

void print_help()
{
    std::cout << "Usage: -t [seconds to run]" << std::endl;
}

bool parse(int argc, char* argv[])
{
    if (argc == 1)
    {
        print_help();
        return false;
    }

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-t")
        {
            time_to_run = std::atoi(argv[++i]);
        }
        if (std::string(argv[i]) == "-h")
        {
            print_help();
            return false;
        }
    }

    return true;
}


int main(int argc, char* argv[])
{
    if (!parse(argc, argv))
    {
        return 1;
    }

    angular_speed = get_random_uniform() * 360;
    sf::RenderWindow window(sf::VideoMode(300, 300), "Rectangle");
    sf::RectangleShape shape(sf::Vector2f(50, 100));
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(25, 50);
    shape.setPosition(150, 150);
    sf::Clock frame_clock;
    sf::Clock program_clock;

    while (program_clock.getElapsedTime().asSeconds() < time_to_run)
    {
        float delay = get_random_beta();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        while (frame_clock.getElapsedTime().asSeconds() < delay/1000)
        {
        }
        float deg = frame_clock.getElapsedTime().asSeconds() * angular_speed;
        //std::cout << "delay: " << delay << " rotate: "<< deg << " speed: "<< deg/delay << " ang_speed: " << angular_speed << " ratio: " << (deg/delay)/angular_speed << std::endl;
        if (shape.getRotation() + deg >= 360)
        {
            rotation_counter++;
        }
        shape.rotate(deg);
        window.draw(shape);
        window.display();
        frame_clock.restart();
    }

    window.close();
    std::cout << "Rotations: " << rotation_counter << std::endl;
    return 0;
}