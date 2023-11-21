#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "list.hpp"
#include "transform.hpp"

enum class MouseKey
{
    Left,
    Right
};

enum class KeyboardKey : uint32_t
{
    A = 0,
    B, C,
    D, E, F, G,
    H, I, J, K,
    L, M, N, O,
    P, Q, R, S,
    T, U, V, W,
    X, Y, Z,

    Num0,
    Num1, Num2, Num3, 
    Num4, Num5, Num6, 
    Num7, Num8, Num9, 

    Escape, LControl, LShift,
    LAlt, LSystem, RControl, RShift,
    RAlt, RSystem, Menu, LBracket,
    RBracket, Semicolon, Comma, Period,
    Apostrophe, Slash, Backslash, Grave,
    Equal, Hyphen, Space, Enter,
    Backspace, Tab, PageUp, PageDown,
    End, Home, Insert, Delete,
    Add, Subtract, Multiply, Divide,
    Left, Right, Up, Down,
    Numpad0, Numpad1, Numpad2, Numpad3,
    Numpad4, Numpad5, Numpad6, Numpad7,
    Numpad8, Numpad9, F1, F2,
    F3, F4, F5, F6,
    F7, F8, F9, F10,
    F11, F12, F13, F14,
    F15, Pause
};

class Container
{
public:
    virtual bool close(int32_t id) = 0;
};

class Widget
{
    LayoutBox *m_layout_box;

public:
    Transform m_transf;
    Vector2f  m_size;

    Widget(const LayoutBox &box);

    virtual void onParentUpdate(const LayoutBox &parent_box);

    virtual       LayoutBox& getLayoutBox ();
    virtual const LayoutBox& getLayoutBox () const;

    virtual void setLayoutBox(const LayoutBox &box);

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list)  = 0;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)  = 0;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)  = 0;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) = 0;

    virtual bool onKeyboardPressed  (KeyboardKey key) = 0;
    virtual bool onKeyboardReleased (KeyboardKey key) = 0;

    virtual bool onTime (float d_seconds) = 0;

    virtual bool onResize(float width, float height) = 0;

    virtual Transform getTransform() const;
    virtual Transform setTransform(const Transform &transf);
};

void adaptSfEvent(sf::Event event, Widget *widget, List<Transform> &transf_list);

#endif  // WIDGET_HPP

