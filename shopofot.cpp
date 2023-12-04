#include "shopofot.hpp"
#include "universal_layout_box.hpp"

ButtonFilterApply::ButtonFilterApply(const LayoutBox &box, const char *str, TextButtonTexture &btn_texture, CanvasManager &canv_manager, int32_t filt_id) :
    TextButton(box, str, btn_texture),
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

FilterVerticalButtonList::FilterVerticalButtonList(const LayoutBox &box, CanvasManager &canv_manager, TextButtonTexture &btn_texture) :
    VerticalButtonList(box, "Filter", btn_texture),
    m_canv_manager(&canv_manager),
    m_btn_texture(&btn_texture)
{}

void FilterVerticalButtonList::addFilter(const char *str, int32_t filt_id)
{
    UniversalLayoutBox box(0_px, 0_px);
    box.setSize(getLayoutBox().getSize());
    Button *btn = new ButtonFilterApply(box, str, *m_btn_texture, *m_canv_manager, filt_id);
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

ButtonNewCanvasWindow::ButtonNewCanvasWindow(const LayoutBox &box, TextButtonTexture &btn_texture, CanvasManager &canv_manager) :
    TextButton(box, "New canvas", btn_texture),
    m_canv_manager(&canv_manager)
{}

bool ButtonNewCanvasWindow::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = TextButton::onMousePressed(key, x, y, transf_list);
    if (res)
        m_canv_manager->addCanvas(1024, 640);

    return res;
}

FileVerticalButtonList::FileVerticalButtonList(const LayoutBox &box, CanvasManager &canv_manager, TextButtonTexture &btn_texture) :
    VerticalButtonList(box, "File", btn_texture),
    m_canv_manager(&canv_manager),
    m_btn_texture(&btn_texture)
{
    UniversalLayoutBox sample_box(0_px, 0_px);
    sample_box.setSize(getLayoutBox().getSize());
    Button *btn = new ButtonNewCanvasWindow(sample_box, *m_btn_texture, *m_canv_manager);
    addButton(*btn);
}

FileVerticalButtonList::~FileVerticalButtonList()
{
    Button *pop_btn = nullptr;
    do
    {
        pop_btn = popButton();
        delete pop_btn;
    }
    while (pop_btn != nullptr);
}

