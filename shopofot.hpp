#ifndef SHOPOFOT_HPP
#define SHOPOFOT_HPP

class ButtonFilterApply : public TextButton
{
    Canvas *m_canvas;
    int32_t m_filt_id;

public:
    ButtonFilterApply(Vector2f pos, float width, float height, const char *str, sf::Font &font, int32_t char_size, const ButtonTexture &btn_texture, Canvas &canvas, int32_t filt_id) :
        TextButton(pos, width, height, str, font, char_size, btn_texture),
        m_canvas(&canvas),
        m_filt_id(filt_id)
    {}

    virtual bool onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
    {
        bool res = TextButton::onMousePressed(key, x, y, transf_list);
        if (res)
        {
            Filter *filter = m_canvas->m_filter_palette->getFilter(m_filt_id);
            filter->applyFilter(*m_canvas, m_canvas->m_filter_mask);
            m_canvas->m_filter_palette->setLastFilter(m_filt_id);
        }

        return res;
    }
};

class FilterVerticalButtonList : public VerticalButtonList
{
    ButtonFilterApply m_btn_brightness_filt_delta_pos;
    ButtonFilterApply m_btn_brightness_filt_delta_neg;

public:
    FilterVerticalButtonList(Canvas &canvas, int32_t brightness_filter_pos_id, int32_t brightness_filter_neg_id, Vector2f pos, float width, float height, sf::Font &font, int32_t char_size, const ButtonTexture &btn_texture) :
        VerticalButtonList(pos, width, height, "Filter", font, char_size, btn_texture),
        m_btn_brightness_filt_delta_pos(pos, width, height, "brtnss+", font, char_size, btn_texture, canvas, brightness_filter_pos_id),
        m_btn_brightness_filt_delta_neg(pos, width, height, "brtnss-", font, char_size, btn_texture, canvas, brightness_filter_neg_id)
    {
        addButton(m_btn_brightness_filt_delta_pos);
        addButton(m_btn_brightness_filt_delta_neg);
    }
};

#endif  // SHOPOFOT_HPP

