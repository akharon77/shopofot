#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "window.hpp"

const uint32_t SCREEN_WIDTH  = 770; 
const uint32_t SCREEN_HEIGHT = 620;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "chamber");

    List<Transform> transf_list;
    transf_list.PushBack({{0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}});

    sf::Texture window_texture;
    window_texture.loadFromFile("mols_ctrl_texture.png");

    Window my_window({0.5f, 0.5f}, 0.5, 0.5, window_texture, {0, 0, 50, 70});

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            adaptSfEvent(event, &my_window, transf_list);
        }

        window.clear(sf::Color::Black);
        my_window.draw(window, transf_list);
        window.display();
    }

    return 0;
}
