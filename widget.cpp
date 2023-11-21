#include "widget.hpp"

Widget::Widget(const LayoutBox &box) :
    m_layout_box(box.clone())
{}

void Widget::onParentUpdate(const LayoutBox &parent_box)
{
    m_layout_box->onParentUpdate(parent_box);
}

LayoutBox& Widget::getLayoutBox()
{
    return *m_layout_box;
}

const LayoutBox& Widget::getLayoutBox() const
{
    return *m_layout_box;
}

void Widget::setLayoutBox(const LayoutBox &box)
{
    delete m_layout_box;
    m_layout_box = box.clone();
}

void adaptSfEvent(sf::Event event, Widget *widget, List<Transform> &transf_list)
{
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
    {
        MouseKey key = MouseKey::Left;
        switch (event.mouseButton.button)
        {
            case sf::Mouse::Right:
                key = MouseKey::Right;
                break;
            default:
                key = MouseKey::Left;
        }

        switch (event.type)
        {
            case sf::Event::MouseButtonPressed:
                widget->onMousePressed(key, 
                        event.mouseButton.x, event.mouseButton.y, transf_list);
                break;

            case sf::Event::MouseButtonReleased:
                widget->onMouseReleased(key, 
                        event.mouseButton.x, event.mouseButton.y, transf_list);
                break;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        widget->onMouseMoved(event.mouseMove.x, event.mouseMove.y, transf_list);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        widget->onKeyboardPressed((KeyboardKey) event.key.code);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        widget->onKeyboardReleased((KeyboardKey) event.key.code);
    }
}

