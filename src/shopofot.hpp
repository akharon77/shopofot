#ifndef SHOPOFOT_HPP
#define SHOPOFOT_HPP

#include "ui/canvas_view_manager.hpp"
#include "ui/button.hpp"

class ButtonFilterApply : public TextButton
{
    CanvasViewManager *m_canv_manager;
    int32_t m_filt_id;

public:
    ButtonFilterApply(const plug::LayoutBox &box, const char *str, TextButtonTexture &btn_texture, CanvasViewManager &canv_manager, int32_t filt_id);

    virtual void onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context) override;
};

class ButtonNewCanvasWindow : public TextButton
{
    CanvasViewManager *m_canv_manager;

public:
    ButtonNewCanvasWindow(const plug::LayoutBox &box, TextButtonTexture &btn_texture, CanvasViewManager &canv_manager);

    virtual void onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context) override;
};

class FilterVerticalButtonList : public VerticalButtonList
{
    CanvasViewManager *m_canv_manager;
    TextButtonTexture *m_btn_texture;

public:
    FilterVerticalButtonList(const plug::LayoutBox &box, CanvasViewManager &canv_manager, TextButtonTexture &btn_texture);

    void addFilter(const char *str, int32_t filt_id);

    ~FilterVerticalButtonList();

    FilterVerticalButtonList& operator = (FilterVerticalButtonList &rhs) = delete;
    FilterVerticalButtonList(const FilterVerticalButtonList &rhs) = delete;
};

class FileVerticalButtonList : public VerticalButtonList
{
    CanvasViewManager *m_canv_manager;
    TextButtonTexture *m_btn_texture;

public:
    FileVerticalButtonList(const plug::LayoutBox &box, CanvasViewManager &canv_manager, TextButtonTexture &btn_texture);
    ~FileVerticalButtonList();

    FileVerticalButtonList& operator = (FileVerticalButtonList &rhs) = delete;
    FileVerticalButtonList(const FileVerticalButtonList &rhs) = delete;
};

#endif  // SHOPOFOT_HPP

