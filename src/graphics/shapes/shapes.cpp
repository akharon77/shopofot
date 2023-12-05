#include "graphics/shapes.hpp"

static void getSymbolTexture(plug::Color *data, 
        const char symbol,
        const plug::Color color);

void drawLine(plug::RenderTarget &target, 
        const plug::Vec2d &begin, const plug::Vec2d &end,
        const plug::Color color)
{
    plug::VertexArray line(plug::PrimitiveType::Lines, 2);

    line[0] = plug::Vertex(begin, plug::Vec2d(0, 0), color);
    line[1] = plug::Vertex(end,   plug::Vec2d(0, 0), color);

    target.draw(line);
}

void drawCircle(plug::RenderTarget &target,
        const plug::Vec2d &pos, const double radius,
        const plug::Color color)
{
    plug::VertexArray circle(plug::PrimitiveType::LineStrip, 0);

    const size_t cnt = 360;
    double step = 2.0 * M_PI / static_cast<double>(cnt);

    double alpha = 0;
    for (size_t it = 0; it <= cnt; it++)
    {
        plug::Vertex next_vertex(plug::Vec2d(cos(alpha) * radius + pos.x, 
                sin(alpha) * radius + pos.y), 
                Vec2d(0, 0), color);
        circle.appendVertex(next_vertex);
        alpha += step;
    }

    target.draw(circle);  
}


void drawRectangle(plug::RenderTarget &target, 
        const plug::Vec2d &left_up, const plug::Vec2d &right_down,
        const plug::Color color)
{
    plug::VertexArray rectangle(plug::PrimitiveType::LineStrip, 5);

    rectangle[0] = rectangle[4] = Vertex(left_up, plug::Vec2d(0, 0), color);
    rectangle[1] = Vertex(plug::Vec2d(right_down.x, left_up.y), plug::Vec2d(0, 0), color);
    rectangle[2] = Vertex(right_down, plug::Vec2d(0, 0), color);
    rectangle[3] = Vertex(plug::Vec2d(left_up.x, right_down.y), plug::Vec2d(0, 0), color);

    target.draw(rectangle);
}

void writeText(plug::RenderTarget &target,
        const plug::Vec2d &pos, 
        const char *text, const double thickness,
        const plug::Color color)
{
    size_t len = strlen(text);

    if (len == 0) return;

    plug::VertexArray vertex_array(plug::Quads, 4);
    vertex_array[0].tex_coords = plug::Vec2d(0, 0);
    vertex_array[1].tex_coords = plug::Vec2d(SYMBOL_WIDTH, 0);
    vertex_array[2].tex_coords = plug::Vec2d(SYMBOL_WIDTH, SYMBOL_HEIGHT);
    vertex_array[3].tex_coords = plug::Vec2d(0, SYMBOL_HEIGHT);

    plug::Color *data = new plug::Color[SYMBOL_WIDTH * SYMBOL_HEIGHT];

    double offset = SYMBOL_WIDTH * thickness;

    for (size_t it = 0; it < len; it++)
    {
        getSymbolTexture(data, text[it], color);

        plug::Texture texture(SYMBOL_WIDTH, SYMBOL_HEIGHT, data);

        plug::Vec2d size(thickness * SYMBOL_WIDTH, thickness * SYMBOL_HEIGHT);

        vertex_array[0].position = plug::Vec2d(pos.x + it * offset, pos.y);
        vertex_array[1].position = plug::Vec2d(pos.x + it * offset + size.x, pos.y);
        vertex_array[2].position = plug::Vec2d(pos.x + it * offset + size.x, pos.y + size.y);
        vertex_array[3].position = plug::Vec2d(pos.x + it * offset, pos.y + size.y);

        target.draw(vertex_array, texture);
    }

    delete[] data;
}

void getSymbolTexture(plug::Color *data, const char symbol, const plug::Color color)
{
    const bool *mask = plug::Unknown;

    switch (symbol)
    {
        case '.':
            mask = plug::Dot;
            break;

        case '!':
            mask = plug::Exclamation_mark;
            break;

        case '?':
            mask = plug::Question_mark;
            break;

        case '/':
            mask = plug::Slash;
            break;

        case ' ': case '\0':
            mask = plug::Space;
            break;

        default:
            {
                if (symbol >= '0' && symbol <= '9')
                {
                    mask = plug::Numbers[symbol - '0'];
                }

                if (symbol >= 'a' && symbol <= 'z')
                {
                    mask = plug::Letters[symbol - 'a'];
                }

                if (symbol >= 'A' && symbol <= 'Z')
                {
                    mask = plug::Letters[symbol - 'A'];
                }
            }
            break;
    }

    for (size_t it = 0; it < SYMBOL_WIDTH * SYMBOL_HEIGHT; it++)
    {
        if (mask[it])
        {
            data[it] = color;
        }
        else
        {
            data[it] = plug::Transparent;
        }
    }
}

