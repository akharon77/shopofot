#include "shopofot.hpp"
#include "universal_layoutbox.hpp"

ButtonFilterApply::ButtonFilterApply(const plug::LayoutBox &box, const char *str, TextButtonTexture &btn_texture, CanvasViewManager &canv_manager, int32_t filt_id) :
    TextButton(box, str, btn_texture),
    m_canv_manager(&canv_manager),
    m_filt_id(filt_id)
{}

void ButtonFilterApply::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    TextButton::onMousePressed(key, x, y, context);
    if (context.stopped)
    {
        CanvasView *canvas = m_canv_manager->getActive();

        plug::Filter *filter = canvas->m_filter_palette->getFilter(m_filt_id);
        filter->applyFilter(*canvas->m_canvas);
        canvas->m_filter_palette->setLastFilter(m_filt_id);
    }
}

FilterVerticalButtonList::FilterVerticalButtonList(const plug::LayoutBox &box, CanvasViewManager &canv_manager, TextButtonTexture &btn_texture) :
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

ButtonNewCanvasWindow::ButtonNewCanvasWindow(const plug::LayoutBox &box, TextButtonTexture &btn_texture, CanvasViewManager &canv_manager) :
    TextButton(box, "New canvas", btn_texture),
    m_canv_manager(&canv_manager)
{}

void ButtonNewCanvasWindow::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    TextButton::onMousePressed(key, x, y, context);
    if (context.stopped)
        m_canv_manager->addCanvas(1024, 640);
}

FileVerticalButtonList::FileVerticalButtonList(const plug::LayoutBox &box, CanvasViewManager &canv_manager, TextButtonTexture &btn_texture) :
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

