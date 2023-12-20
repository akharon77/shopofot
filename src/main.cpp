#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>

#include "shopofot.hpp"
#include "plugin_loader.hpp"
#include "event/event_manager.hpp"
#include "ui/button.hpp"
#include "universal_layoutbox.hpp"
#include "util/sfml.hpp"
#include "math/transform_stack.hpp"
#include "graphics/render_window.hpp"
#include "ui/menu.hpp"
#include "ui/canvas_view_manager.hpp"
#include "color_palette.hpp"

int main()
{
    sf::RenderWindow sf_window(sf::VideoMode(1024, 720), "shopofot");
    RenderWindow window(sf_window);

    TransformStack stack;

    plug::Texture button_texture = getPlugTexture("assets/img/mols_ctrl_texture.png");

    ButtonTexture btn_texture_config
    {
        &button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    plug::Texture close_button_texture = getPlugTexture("assets/img/mols_ctrl_texture (copy).png");

    ButtonTexture close_btn_texture_config
    {
        &close_button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    plug::Texture scroll_button_texture = getPlugTexture("assets/img/scrollbar.png");

    ButtonTexture scroll_btn_texture_config
    {
        &scroll_button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    // up, down, left, right

    plug::Texture scroll_up_button_texture = getPlugTexture("assets/img/scrollbar_up.png");
    ButtonTexture scroll_up_btn_texture_config
    {
        &scroll_up_button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    plug::Texture scroll_down_button_texture = getPlugTexture("assets/img/scrollbar_down.png");
    ButtonTexture scroll_down_btn_texture_config
    {
        &scroll_down_button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    plug::Texture scroll_left_button_texture = getPlugTexture("assets/img/scrollbar_left.png");
    ButtonTexture scroll_left_btn_texture_config
    {
        &scroll_left_button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    plug::Texture scroll_right_button_texture = getPlugTexture("assets/img/scrollbar_right.png");
    ButtonTexture scroll_right_btn_texture_config
    {
        &scroll_right_button_texture,
        {57,  0,  57, 52},
        {57, 52,  57, 52},
        {57, 104, 57, 52}
    };

    // //

    ScrollBarTexture scrollbar_texture_config
    {
        &button_texture,
        &scroll_up_btn_texture_config,
        &scroll_down_btn_texture_config,
        &scroll_left_btn_texture_config,
        &scroll_right_btn_texture_config,
        &scroll_btn_texture_config
    };

    sf::Font font;
    font.loadFromFile("assets/fonts/anon_pro.ttf");
    TextButtonTexture text_btn_texture_config
    {
        getPlugColor(sf::Color::White),
        &btn_texture_config,
        font
    };

    FrameTexture frame_texture_config
    {
        &close_btn_texture_config,
        &close_btn_texture_config,
        font
    };

    CanvasViewManagerTexture canv_manager_texture_config
    {
        &scrollbar_texture_config,
        &frame_texture_config
    };

    ToolPalette tool_palette;
    FilterPalette filter_palette;
    ColorPalette color_palette;

    UniversalLayoutBox sample_box(1024_px, 720_px);
    sample_box.setPosition(Vec2d(0_px, 0_px));

    CanvasViewManager canv_manager(sample_box, tool_palette, filter_palette, color_palette, canv_manager_texture_config);
    canv_manager.addCanvas(1024, 640);

    FileVerticalButtonList file_ver_btn_lst(UniversalLayoutBox(100_px, 30_px), canv_manager, 20, text_btn_texture_config);
    FilterVerticalButtonList filt_ver_btn_lst(UniversalLayoutBox(130_px, 30_px), canv_manager, 20, text_btn_texture_config);
    ToolVerticalButtonList tool_ver_btn_lst(UniversalLayoutBox(100_px, 30_px), canv_manager, 20, text_btn_texture_config);

    loadPlugins("Plugins", filt_ver_btn_lst, tool_ver_btn_lst);
    
    Menu menu(canv_manager);
    menu.addButton(file_ver_btn_lst);
    menu.addButton(filt_ver_btn_lst);
    menu.addButton(tool_ver_btn_lst);

    EventManager event_manager(sf_window, stack);

    while (sf_window.isOpen())
    {
        event_manager.sendEvents((plug::Widget*) &menu);

        sf_window.clear(sf::Color::Black);
        menu.draw(stack, window);

        sf_window.display();
    }
    
    return 0;
}

