#ifndef TOOL_TOOL_HPP
#define TOOL_TOOL_HPP

#include "widget.hpp"
#include "math.hpp"

class CanvasView;

enum class MouseType
{
    PRESSED,
    RELEASED
};

class Tool
{
public:
    virtual void onMainButton(MouseType key, Vec2d pos, CanvasView &canvas)      = 0;
    virtual void onSecondaryButton(MouseType key, Vec2d pos, CanvasView &canvas) = 0;

    virtual void onModifier1(MouseType key, Vec2d pos, CanvasView &canvas) = 0;
    virtual void onModifier2(MouseType key, Vec2d pos, CanvasView &canvas) = 0;
    virtual void onModifier3(MouseType key, Vec2d pos, CanvasView &canvas) = 0;

    virtual void onMove(Vec2d pos, CanvasView &canvas)    = 0;
    virtual void onConfirm(Vec2d pos, CanvasView &canvas) = 0;
    virtual void onCancel(Vec2d pos, CanvasView &canvas)  = 0;

    virtual Widget* getWidget() = 0;
};

#endif  // TOOL_TOOL_HPP

