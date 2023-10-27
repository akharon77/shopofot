#ifndef TOOL_HPP
#define TOOL_HPP

#include "widget.hpp"

class Canvas;

enum class MouseType
{
    PRESSED,
    RELEASED
};

class Tool
{
public:
    virtual void onMainButton(MouseType key, Vector2f pos, Canvas &canvas)      = 0;
    virtual void onSecondaryButton(MouseType key, Vector2f pos, Canvas &canvas) = 0;

    virtual void onModifier1(MouseType key, Vector2f pos, Canvas &canvas) = 0;
    virtual void onModifier2(MouseType key, Vector2f pos, Canvas &canvas) = 0;
    virtual void onModifier3(MouseType key, Vector2f pos, Canvas &canvas) = 0;

    virtual void onMove(Vector2f pos, Canvas &canvas)    = 0;
    virtual void onConfirm(Vector2f pos, Canvas &canvas) = 0;
    virtual void onCancel(Vector2f pos, Canvas &canvas)  = 0;

    virtual Widget* getWidget() = 0;
};

#endif  // TOOL_HPP

