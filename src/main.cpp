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

    ScrollBarTexture scrollbar_texture_config
    {
        &button_texture,
        &btn_texture_config,
        &btn_texture_config,
        &btn_texture_config,
        &btn_texture_config,
        &btn_texture_config
    };

    TextButtonTexture text_btn_texture_config
    {
        getPlugColor(sf::Color::Green),
        &btn_texture_config
    };

    FrameTexture frame_texture_config
    {
        &btn_texture_config,
        &btn_texture_config
    };

    CanvasViewManagerTexture canv_manager_texture_config
    {
        &scrollbar_texture_config,
        &frame_texture_config
    };

    ToolPalette tool_palette;
    FilterPalette filter_palette;
    ColorPalette color_palette;

    UniversalLayoutBox sample_box(640_px, 480_px);
    sample_box.setPosition(Vec2d(0_px, 0_px));

    CanvasViewManager canv_manager(sample_box, tool_palette, filter_palette, color_palette, canv_manager_texture_config);
    canv_manager.addCanvas(1024, 640);

    FileVerticalButtonList file_ver_btn_lst(UniversalLayoutBox(100_px, 50_px), canv_manager, text_btn_texture_config);
    FilterVerticalButtonList filt_ver_btn_lst(UniversalLayoutBox(100_px, 50_px), canv_manager, text_btn_texture_config);
    ToolVerticalButtonList tool_ver_btn_lst(UniversalLayoutBox(100_px, 50_px), canv_manager, text_btn_texture_config);

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

