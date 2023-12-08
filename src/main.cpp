#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>

// #include "window.hpp"
// #include "universal_layout_box.hpp"
// #include "frame.hpp"

// #include "button.hpp"
// #include "scrollbar.hpp"
// #include "menu.hpp"
 
// #include "ver_btn_list.hpp"
// #include "text_btn.hpp"
 
// #include "line_tool.hpp"
// #include "brush.hpp"
// #include "square_tool.hpp"
// #include "polyline_tool.hpp"
// #include "polygon_tool.hpp"
// #include "line_edit_tool.hpp"
 
// #include "filter_plugins/brightness_filter.hpp"
// #include "blackwhite_filter.hpp"
// #include "onecolor_filter.hpp"
// #include "negative_filter.hpp"

#include "shopofot.hpp"

// #include "line_edit.hpp"

// #include "canvas_manager.hpp"
// #include "toolbar.hpp"

#include "event/event_manager.hpp"
#include "ui/button.hpp"
#include "universal_layoutbox.hpp"
#include "util/sfml.hpp"
#include "math/transform_stack.hpp"
#include "graphics/render_window.hpp"
#include "ui/frame.hpp"
#include "ui/canvas_view.hpp"
#include "ui/scrollbar.hpp"
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
    
    // LineTool line_tool;
    // SquareTool square_tool;
    // BrushTool brush_tool;
    // PolyLineTool polyline_tool;
    // PolygonTool polygon_tool;
    // LineEditTool line_edit_tool(font, 0.05);

    ToolPalette tool_palette;
    tool_palette.loadPlugin("Plugins/CircleTool/CircleTool.so");

    // ToolBar toolbar(30_px, 30_px, tool_palette, 2);

    // // tool_palette.addTool(&line_tool);
    // sf::Texture line_tool_btn_texture;
    // line_tool_btn_texture.loadFromFile("line_tool_btn_texture.png");
    // ButtonTexture line_tool_btn_texture_config
    // {
    //     &line_tool_btn_texture,
    //     {57,  0,  57, 52},
    //     {57, 52,  57, 52},
    //     {57, 104, 57, 52}
    // };
    // toolbar.addButton(line_tool_btn_texture_config, tool_palette.addTool(&line_tool));

    // // tool_palette.addTool(&square_tool);
    // sf::Texture square_tool_btn_texture;
    // square_tool_btn_texture.loadFromFile("square_tool_btn_texture.png");
    // ButtonTexture square_tool_btn_texture_config
    // {
    //     &square_tool_btn_texture,
    //     {57,  0,  57, 52},
    //     {57, 52,  57, 52},
    //     {57, 104, 57, 52}
    // };
    // toolbar.addButton(square_tool_btn_texture_config, tool_palette.addTool(&square_tool));

    // // tool_palette.addTool(&brush_tool);
    // sf::Texture brush_tool_btn_texture;
    // brush_tool_btn_texture.loadFromFile("brush_tool_btn_texture.png");
    // ButtonTexture brush_tool_btn_texture_config
    // {
    //     &brush_tool_btn_texture,
    //     {57,  0,  57, 52},
    //     {57, 52,  57, 52},
    //     {57, 104, 57, 52}
    // };
    // toolbar.addButton(brush_tool_btn_texture_config, tool_palette.addTool(&brush_tool));
    // 
    // // tool_palette.addTool(&polyline_tool);
    // sf::Texture polyline_tool_btn_texture;
    // polyline_tool_btn_texture.loadFromFile("polyline_tool_btn_texture.png");
    // ButtonTexture polyline_tool_btn_texture_config
    // {
    //     &polyline_tool_btn_texture,
    //     {57,  0,  57, 52},
    //     {57, 52,  57, 52},
    //     {57, 104, 57, 52}
    // };
    // toolbar.addButton(polyline_tool_btn_texture_config, tool_palette.addTool(&polyline_tool));

    // // tool_palette.addTool(&polygon_tool);
    // sf::Texture polygon_tool_btn_texture;
    // polygon_tool_btn_texture.loadFromFile("polygon_tool_btn_texture.png");
    // ButtonTexture polygon_tool_btn_texture_config
    // {
    //     &polygon_tool_btn_texture,
    //     {57,  0,  57, 52},
    //     {57, 52,  57, 52},
    //     {57, 104, 57, 52}
    // };
    // toolbar.addButton(polygon_tool_btn_texture_config, tool_palette.addTool(&polygon_tool));

    // sf::Texture line_edit_tool_btn_texture;
    // line_edit_tool_btn_texture.loadFromFile("line_edit_tool_btn_texture.png");
    // ButtonTexture line_edit_tool_btn_texture_config
    // {
    //     &line_edit_tool_btn_texture,
    //     {57,  0,  57, 52},
    //     {57, 52,  57, 52},
    //     {57, 104, 57, 52}
    // };
    // toolbar.addButton(line_edit_tool_btn_texture_config, tool_palette.addTool(&line_edit_tool));

    // Frame toolbar_frame(toolbar, "toolbar", 10_px, frame_texture_config);

    // BrightnessFilter brightness_filter_pos;
    // brightness_filter_pos.setBrightnessDelta(0.05);
    // BrightnessFilter brightness_filter_neg;
    // brightness_filter_neg.setBrightnessDelta(-0.05);

    // BlackWhiteFilter blackwhite_filter;
    // OneColorFilter red_filter(OneColorFilter::RED);
    // OneColorFilter green_blue_filter(OneColorFilter::GREEN | OneColorFilter::BLUE);

    // NegativeFilter negative_filter;

    FilterPalette filter_palette;
    int32_t plugin_negative_filter_pos_id = filter_palette.loadPlugin("Plugins/ContrastFilter/ContrastFilter.so");
    // int32_t brightness_filter_pos_id = filter_palette.loadplugin("filter_plugins/brightness_filter.so");

    // filter_palette.addFilter(brightness_filter_pos);
    // int32_t brightness_filter_neg_id = filter_palette.addFilter(brightness_filter_neg);
    // int32_t blackwhite_filter_id     = filter_palette.addFilter(blackwhite_filter);
    // int32_t red_filter_id            = filter_palette.addFilter(red_filter);
    // int32_t green_blue_filter_id     = filter_palette.addFilter(green_blue_filter);
    // int32_t negative_filter_id       = filter_palette.addFilter(negative_filter);

    ColorPalette color_palette;

    UniversalLayoutBox sample_box(640_px, 480_px);
    sample_box.setPosition(Vec2d(0_px, 0_px));

    CanvasViewManager canv_manager(sample_box, tool_palette, filter_palette, color_palette, canv_manager_texture_config);
    canv_manager.addCanvas(1024, 640);
    canv_manager.addCanvas(1024, 640);

    FileVerticalButtonList file_ver_btn_lst(UniversalLayoutBox(50_px, 30_px), canv_manager, text_btn_texture_config);

    FilterVerticalButtonList filt_ver_btn_lst(UniversalLayoutBox(50_px, 30_px), canv_manager, text_btn_texture_config);
    filt_ver_btn_lst.addFilter("Contrast",     plugin_negative_filter_pos_id);
    // filt_ver_btn_lst.addFilter("Light+",     brightness_filter_pos_id);
    // filt_ver_btn_lst.addFilter("Light-",     brightness_filter_neg_id);
    // filt_ver_btn_lst.addFilter("B/W",        blackwhite_filter_id);
    // filt_ver_btn_lst.addFilter("Red",        red_filter_id);
    // filt_ver_btn_lst.addFilter("Green&Blue", green_blue_filter_id);
    // filt_ver_btn_lst.addFilter("Negative",   negative_filter_id);
    
    Menu menu(canv_manager);
    menu.addButton(file_ver_btn_lst);
    menu.addButton(filt_ver_btn_lst);

    EventManager event_manager(sf_window, stack);

    // Canvas canvas(sample_box, 1024, 640, tool_palette, filter_palette);
    // ScrollBar scrollbar(canvas, 20_px, 200_px, 200_px, static_cast<ScrollBar::scrollable_t>(ScrollBar::SCROLLABLE_VERTICAL | ScrollBar::SCROLLABLE_HORIZONTAL), scrollbar_texture_config);

    // Menu menu(canv_manager);

    // Button testButton1(UniversalLayoutBox(30_px, 30_px), btn_texture_config);
    // Button testButton2(UniversalLayoutBox(30_px, 30_px), btn_texture_config);
    // Button testButton3(UniversalLayoutBox(30_px, 30_px), btn_texture_config);

    // menu.addButton(testButton1);
    // menu.addButton(testButton2);
    // menu.addButton(testButton3);

    // Frame frame(menu, "lol", 10_px, frame_texture_config);
    // frame.setClosable(true);

    // sf::Image cat_img;
    // cat_img.loadFromFile("cat.jpg");
    // canvas.loadFromImage(cat_img);

    // TextButton sample_button(UniversalLayoutBox(10_cm, 2_cm), "ded hui n nn n n n n lol", text_btn_texture_config);

    // CanvasView canvas_view(UniversalLayoutBox(20_cm, 20_cm), 1024, 640, tool_palette, filter_palette);
    // ScrollBar scrollbar(canvas_view, 1_cm, 10_cm, 10_cm, static_cast<ScrollBar::scrollable_t>(ScrollBar::SCROLLABLE_VERTICAL | ScrollBar::SCROLLABLE_HORIZONTAL), scrollbar_texture_config);
    // Menu menu(scrollbar);

    // Button testButton1(UniversalLayoutBox(30_px, 30_px), btn_texture_config);
    // Button testButton2(UniversalLayoutBox(30_px, 30_px), btn_texture_config);
    // Button testButton3(UniversalLayoutBox(30_px, 30_px), btn_texture_config);

    // menu.addButton(testButton1);
    // menu.addButton(testButton2);
    // menu.addButton(testButton3);

    // Frame frame(menu, "loh", 1_cm, frame_texture_config);
    // frame.setClosable(true);

    while (sf_window.isOpen())
    {
        event_manager.sendEvents((plug::Widget*) &menu);

        sf_window.clear(sf::Color::Black);
        menu.draw(stack, window);

        sf_window.display();
    }
    
    return 0;
}

