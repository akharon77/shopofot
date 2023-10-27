#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "window.hpp"
#include "canvas.hpp"
#include "frame.hpp"

#include "button.hpp"
#include "scrollbar.hpp"
#include "menu.hpp"

#include "ver_btn_list.hpp"
#include "text_btn.hpp"

#include "line_tool.hpp"
#include "brush.hpp"
#include "square_tool.hpp"
#include "polyline_tool.hpp"
#include "polygon_tool.hpp"

#include "brightness_filter.hpp"

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
    
    LineTool line_tool;
    SquareTool square_tool;
    BrushTool brush_tool;
    PolyLineTool polyline_tool;
    PolygonTool polygon_tool;

    ToolPalette tool_palette;
    tool_palette.addTool(&line_tool);
    tool_palette.addTool(&square_tool);
    tool_palette.addTool(&brush_tool);
    tool_palette.addTool(&polyline_tool);
    tool_palette.addTool(&polygon_tool);

    BrightnessFilter brightness_filter;
    brightness_filter.setBrightnessDelta(0.1);

    FilterPalette filter_palette;
    int32_t brightness_filter_id = filter_palette.addFilter(brightness_filter);
    filter_palette.setLastFilter(brightness_filter_id);

    Button sample_button
    {
        {0, 0},
        0.05, 0.02,
        btn_texture_config
    };
    Button sample_button1
    {
        {0, 0.5},
        0.03, 0.01,
        btn_texture_config
    };
    Button sample_button2
    {
        {0.5, 0},
        0.07, 0.04,
        btn_texture_config
    };

    sf::Font font;
    font.loadFromFile("arial.ttf");

    VerticalButtonList ver_btn_list({0, 0}, 0.05, 0.02, "File", font, 16, btn_texture_config);
    ver_btn_list.addButton(sample_button1);
    ver_btn_list.addButton(sample_button2);

    sf::Image cat_img;
    cat_img.loadFromFile("cat.jpg");

    Canvas my_window({0.2f, 0.1f}, 1, 1, 640, 480, tool_palette, filter_palette);
    my_window.loadFromImage(cat_img);

    ScrollBar my_window_with_scrollbar{my_window, 0.01, 0.3, true, 0.3, true, scrollbar_texture_config};
    Menu my_window_with_scrollbar_menu{my_window_with_scrollbar};
    my_window_with_scrollbar_menu.addButton(sample_button);
    Frame my_window_with_scrollbar_menu_frame{my_window_with_scrollbar_menu, "hello", 0.01, btn_texture_config};

    Canvas my_window1({0.6f, 0.8f}, 1, 1, 1000, 1000, tool_palette, filter_palette);
    ScrollBar my_window_with_scrollbar1{my_window1, 0.03, 0.3, true, 0.3, true, scrollbar_texture_config};
    Frame my_window_with_scrollbal_frame1{my_window_with_scrollbar1, "hello", 0.02, btn_texture_config};

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            adaptSfEvent(event, &my_window_with_scrollbar_menu_frame,  transf_list);
            adaptSfEvent(event, &ver_btn_list,  transf_list);
            //adaptSfEvent(event, &my_window_with_scrollbal_frame1, transf_list);
        }

        window.clear(sf::Color::Black);

        my_window_with_scrollbar_menu_frame.draw(window, transf_list);
        ver_btn_list.draw(window, transf_list);
        //my_window_with_scrollbal_frame1.draw(window, transf_list);

        window.display();
    }
    return 0;
}

