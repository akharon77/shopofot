#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "window.hpp"
#include "canvas.hpp"
#include "frame.hpp"
#include "button.hpp"
#include "scrollbar.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "shopofot");

    List<Transform> transf_list;
    transf_list.PushBack({{0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}});

    sf::Texture window_texture;
    window_texture.loadFromFile("mols_ctrl_texture.png");

    WindowTexture window_texture_config
    {
        &window_texture,
        {0, 0, 57, 52}
    };

    sf::Texture button_texture;
    button_texture.loadFromFile("mols_ctrl_texture.png");

    ButtonTexture btn_texture_config
    {
        &button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    ScrollBarTexture scrollbar_texture_config
    {
        &window_texture,
        &btn_texture_config,
        &btn_texture_config,
        &btn_texture_config,
        &btn_texture_config,
        &btn_texture_config
    };
    
    Canvas my_window({0.2f, 0.1f}, 0.7, 0.6, 1000, 1000);
    ScrollBar my_window_with_scrollbar{my_window, 0.03, 0.3, true, 0.3, true, scrollbar_texture_config};
    Frame my_window_with_scrollbal_frame{my_window_with_scrollbar, "hello", 0.02, btn_texture_config};

    Canvas my_window1({0.6f, 0.8f}, 0.7, 0.6, 1000, 1000);
    ScrollBar my_window_with_scrollbar1{my_window1, 0.03, 0.3, true, 0.3, true, scrollbar_texture_config};
    Frame my_window_with_scrollbal_frame1{my_window_with_scrollbar1, "hello", 0.02, btn_texture_config};

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            adaptSfEvent(event, &my_window_with_scrollbal_frame, transf_list);
            adaptSfEvent(event, &my_window_with_scrollbal_frame1, transf_list);
        }

        window.clear(sf::Color::Black);

        my_window_with_scrollbal_frame.draw(window, transf_list);
        my_window_with_scrollbal_frame1.draw(window, transf_list);

        window.display();
    }
    return 0;
}

