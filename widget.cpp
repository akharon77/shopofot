#include "widget.hpp"

Widget::Widget(Transform transf, Vector2f size) :
    m_transf(transf),
    m_size(size)
{}

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

Transform Widget::getTransform() const
{
    return m_transf;
}

Transform Widget::setTransform(const Transform &transf)
{
    m_transf = transf;
}

