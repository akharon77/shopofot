#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "list.hpp"
#include "transform.hpp"

enum MouseKey
{
    Left,
    Right
};

enum KeyboardKey
{};

class Widget
{
protected:
    Transform m_transf;
    Vector2f m_size;

public:
    Widget(Transform transf, Vector2f size);

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list)  = 0;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)  = 0;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)  = 0;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) = 0;

    virtual bool onKeyboardPressed  (KeyboardKey key) = 0;
    virtual bool onKeyboardReleased (KeyboardKey key) = 0;

    virtual bool onTime (float d_seconds) = 0;

    virtual Transform getTransform() const;
    virtual Transform setTransform(const Transform &transf);
};

void adaptSfEvent(sf::Event event, Widget *widget, List<Transform> &transf_list);

#endif  // WIDGET_HPP

