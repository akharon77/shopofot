#include "shopofot.hpp"

ButtonFilterApply::ButtonFilterApply(Vector2f pos, float width, float height, const char *str, TextButtonTexture &btn_texture, CanvasManager &canv_manager, int32_t filt_id) :  //sf::Font &font, int32_t char_size, const ButtonTexture &btn_texture, Canvas &canvas, int32_t filt_id) :
    TextButton(pos, width, height, str, btn_texture),
    m_canv_manager(&canv_manager),
    m_filt_id(filt_id)
{}

bool ButtonFilterApply::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = TextButton::onMousePressed(key, x, y, transf_list);
    if (res)
    {
        Canvas *canvas = m_canv_manager->getActive();

        Filter *filter = canvas->m_filter_palette->getFilter(m_filt_id);
        filter->applyFilter(*canvas, canvas->m_filter_mask);
        canvas->m_filter_palette->setLastFilter(m_filt_id);
    }

    return res;
}

FilterVerticalButtonList::FilterVerticalButtonList(Vector2f pos, float width, float height, CanvasManager &canv_manager, TextButtonTexture &btn_texture) :
    VerticalButtonList(pos, width, height, "Filter", btn_texture),
    m_width(width),
    m_height(height),
    m_canv_manager(&canv_manager),
    m_btn_texture(&btn_texture)
{}

void FilterVerticalButtonList::addFilter(const char *str, int32_t filt_id)
{
    Button *btn = new ButtonFilterApply({0, 0}, m_width, m_height, str, *m_btn_texture, *m_canv_manager, filt_id);
    addButton(*btn);
}

FilterVerticalButtonList::~FilterVerticalButtonList()
{
    Button *pop_btn = nullptr;
    do
    {
        pop_btn = popButton();
        delete pop_btn;
    }
    while (pop_btn != nullptr);
}

