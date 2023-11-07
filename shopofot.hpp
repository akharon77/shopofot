#ifndef SHOPOFOT_HPP
#define SHOPOFOT_HPP

#include "canvas_manager.hpp"
#include "text_btn.hpp"
#include "ver_btn_list.hpp"

class ButtonFilterApply : public TextButton
{
    CanvasManager *m_canv_manager;
    int32_t m_filt_id;

public:
    ButtonFilterApply(Vector2f pos, float width, float height, const char *str, TextButtonTexture &btn_texture, CanvasManager &canv_manager, int32_t filt_id);  //sf::Font &font, int32_t char_size, const ButtonTexture &btn_texture, Canvas &canvas, int32_t filt_id) :

    virtual bool onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
};

class ButtonNewCanvasWindow : public TextButton
{
    CanvasManager *m_canv_manager;

public:
    ButtonNewCanvasWindow(Vector2f pos, float width, float height, TextButtonTexture &btn_texture, CanvasManager &canv_manager);

    virtual bool onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
};

class FilterVerticalButtonList : public VerticalButtonList
{
    float m_width;
    float m_height;

    CanvasManager *m_canv_manager;
    TextButtonTexture *m_btn_texture;

public:
    FilterVerticalButtonList(Vector2f pos, float width, float height, CanvasManager &canv_manager, TextButtonTexture &btn_texture);

    void addFilter(const char *str, int32_t filt_id);

    ~FilterVerticalButtonList();

    FilterVerticalButtonList& operator = (FilterVerticalButtonList &rhs) = delete;
    FilterVerticalButtonList(const FilterVerticalButtonList &rhs) = delete;
};

class FileVerticalButtonList : public VerticalButtonList
{
    float m_width;
    float m_height;

    CanvasManager *m_canv_manager;
    TextButtonTexture *m_btn_texture;

public:
    FileVerticalButtonList(Vector2f pos, float width, float height, CanvasManager &canv_manager, TextButtonTexture &btn_texture);
    ~FileVerticalButtonList();

    FileVerticalButtonList& operator = (FileVerticalButtonList &rhs) = delete;
    FileVerticalButtonList(const FileVerticalButtonList &rhs) = delete;
};

#endif  // SHOPOFOT_HPP

