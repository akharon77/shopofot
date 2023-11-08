#include "line_edit.hpp"

LineEdit::LineEdit(Vector2f pos, float width, float height, sf::Font &font, int32_t char_size) :
    Widget({pos, {1, 1}}, {width, height}),
    m_buf(""),
    m_len(0),
    m_text("", font, char_size),
    m_shift_flag(false),
    m_last_char('\0')
{
    m_text.setColor(sf::Color::White);
}

void LineEdit::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.rollbackTransform({0, 0});

    sf::RectangleShape rect;
    rect.setPosition(pos);
    rect.setSize({20, 20});
    // rect.setScale(top_transf.m_scale);
    rect.setFillColor(sf::Color::Blue);
    target.draw(rect);

    m_text.setPosition(pos);
    // m_text.setScale(top_transf.m_scale);
    target.draw(m_text);

    transf_list.PopBack();
}

bool LineEdit::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    return false;
}

bool LineEdit::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    return false;
}

bool LineEdit::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    return false;
}

bool LineEdit::onKeyboardPressed(KeyboardKey key)
{
    bool flag = false;

    if (key == KeyboardKey::LShift || key == KeyboardKey::RShift)
    {
        m_shift_flag = true;
    }
    else if (KeyboardKey::A <= key && key <= KeyboardKey::Z)
    {
        m_last_char = (uint32_t) key - (uint32_t) KeyboardKey::A + (m_shift_flag ? 'A' : 'a');
        flag = true;
    }
    else if (KeyboardKey::Num0 <= key && key <= KeyboardKey::Num9)
    {
        m_last_char = (uint32_t) key - (uint32_t) KeyboardKey::Num0 + '0';
        flag = true;
    }
    else
    {
        flag = true;
        switch (key)
        {
            case KeyboardKey::Space:
                m_last_char = ' ';
                break;
            case KeyboardKey::Enter:
                m_last_char = '\n';
                break;
            case KeyboardKey::Backspace:
                --m_len;
                m_buf[m_len] = '\0';
            default:
                flag = false;
        }
    }

    if (flag)
    {
        m_buf[m_len] = m_last_char;
        m_buf[m_len + 1] = '\0';
        ++m_len;
    }

    m_text.setString(m_buf);
    return true;
}

bool LineEdit::onKeyboardReleased(KeyboardKey key)
{
    if (key == KeyboardKey::LShift || key == KeyboardKey::RShift)
    {
        m_shift_flag = false;
    }
}

bool LineEdit::onTime (float d_seconds)
{
    return true;
}

bool LineEdit::onResize(float width, float height)
{
    return false;
}

