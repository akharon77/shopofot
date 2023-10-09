#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "window.hpp"
#include "frame.hpp"
#include "button.hpp"

const uint32_t SCREEN_WIDTH  = 1024; 
const uint32_t SCREEN_HEIGHT = 720;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "shopofot");

    List<Transform> transf_list;
    transf_list.PushBack({{0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}});

    sf::Texture button_texture;
    button_texture.loadFromFile("mols_ctrl_texture.png");

    ButtonTexture btn_texture_config
    {
        button_texture,
        {0,  0,  57, 52},
        {0, 52,  57, 52},
        {0, 104, 57, 52}
    };
    
    sf::Texture window_texture;
    window_texture.loadFromFile("mols_ctrl_texture.png");

    // Button my_button1({0.25f, 0.25f}, 0.05, 0.05, 
    //                      button_texture,
    //                   {0,  0,  57, 52},
    //                   {0, 52,  57, 52},
    //                   {0, 104, 57, 52});

    // Button my_button2({0.75f, 0.67f}, 0.05, 0.05, button_texture,
    //                   {57,  0,  57, 52},
    //                   {57, 52,  57, 52},
    //                   {57, 104, 57, 52});

    Window my_window({0.2f, 0.1f}, 0.2, 0.2, window_texture, {0, 0, 50, 70});
    Window my_window2({0.1f, 0.5f}, 0.2, 0.05, window_texture, {0, 0, 50, 70});

    Frame my_window_with_frame{my_window, "hello", 0.02, btn_texture_config};
    Frame my_window_with_frame2{my_window2, "hello", 0.02, btn_texture_config};

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // adaptSfEvent(event, &my_button1, transf_list);
            // adaptSfEvent(event, &my_button2, transf_list);

            adaptSfEvent(event, &my_window_with_frame, transf_list);
            adaptSfEvent(event, &my_window_with_frame2, transf_list);
        }

        window.clear(sf::Color::Black);

        // my_button1.draw(window, transf_list);
        // my_button2.draw(window, transf_list);
        my_window_with_frame.draw(window, transf_list);
        my_window_with_frame2.draw(window, transf_list);

        window.display();
    }
    return 0;
}

