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

#include "shopofot.hpp"

#include "canvas_manager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_WIDTH), "shopofot");

    List<Transform> transf_list;
    transf_list.PushBack({{0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}});

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
        &button_texture,
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

    BrightnessFilter brightness_filter_pos;
    brightness_filter_pos.setBrightnessDelta(0.05);
    BrightnessFilter brightness_filter_neg;
    brightness_filter_neg.setBrightnessDelta(-0.05);

    FilterPalette filter_palette;
    int32_t brightness_filter_pos_id = filter_palette.addFilter(brightness_filter_pos);
    int32_t brightness_filter_neg_id = filter_palette.addFilter(brightness_filter_neg);

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

    TextButtonTexture text_btn_texture_config
    {
        &font,
        16,
        &btn_texture_config
    };

    FrameTexture frame_texture_config
    {
        &btn_texture_config,
        &btn_texture_config
    };

    CanvasManagerTexture canv_manager_texture_config
    {
        &scrollbar_texture_config,
        &frame_texture_config
    };

    CanvasManager canv_manager({0, 0}, {1, 1}, tool_palette, filter_palette, canv_manager_texture_config);
    canv_manager.addCanvas(1024, 640);
    canv_manager.addCanvas(1024, 640);
    canv_manager.addCanvas(1024, 640);

    FileVerticalButtonList file_ver_btn_lst({0, 0}, 0.05, 0.02, canv_manager, text_btn_texture_config);

    // VerticalButtonList file_btn_list({0, 0}, 0.05, 0.02, "File", text_btn_texture_config);
    // ButtonNewCanvasWindow btn_new_canvas({0, 0}, 0.05, 0.02, text_btn_texture_config, canv_manager);
    // file_btn_list.addButton(sample_button1);
    // file_btn_list.addButton(btn_new_canvas);
    // file_btn_list.addButton(sample_button2);

    FilterVerticalButtonList filt_ver_btn_lst({0, 0}, 0.05, 0.02, canv_manager, text_btn_texture_config);
    filt_ver_btn_lst.addFilter("Light+", brightness_filter_pos_id);
    filt_ver_btn_lst.addFilter("Light-", brightness_filter_neg_id);
    
    Menu menu(canv_manager);
    menu.addButton(file_ver_btn_lst);
    menu.addButton(filt_ver_btn_lst);

    // sf::Image cat_img;
    // cat_img.loadFromFile("cat.jpg");

    // Canvas my_window({0.2f, 0.1f}, 1, 1, 640, 480, tool_palette, filter_palette);
    // FilterVerticalButtonList filt_ver_btn_lst(my_window, brightness_filter_pos_id, brightness_filter_neg_id,
    //                                         {0, 0}, 0.05, 0.02, font, 16, btn_texture_config);
    // my_window.loadFromImage(cat_img);

    // ScrollBar my_window_with_scrollbar{my_window, 0.01, 0.3, true, 0.3, true, scrollbar_texture_config};

    // Frame my_window_with_scrollbar_menu_frame{my_window_with_scrollbar_menu, "hello", 0.01, btn_texture_config};

    // Canvas my_window1({0.6f, 0.8f}, 1, 1, 1000, 1000, tool_palette, filter_palette);
    // ScrollBar my_window_with_scrollbar1{my_window1, 0.03, 0.3, true, 0.3, true, scrollbar_texture_config};
    // Frame my_window_with_scrollbal_frame1{my_window_with_scrollbar1, "hello", 0.02, btn_texture_config};

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            adaptSfEvent(event, &menu, transf_list);
            // adaptSfEvent(event, &my_window_with_scrollbar_menu_frame,  transf_list);
        }

        window.clear(sf::Color::Black);

        menu.draw(window, transf_list);
        // my_window_with_scrollbar_menu_frame.draw(window, transf_list);

        window.display();
    }
    return 0;
}

