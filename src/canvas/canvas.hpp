#ifndef CANVAS_CANVAS_HPP
#define CANVAS_CANVAS_HPP

#include "plug/canvas/canvas.hpp"

#include "graphics/render_texture.hpp"
#include "canvas/selection_mask.hpp"

class Canvas : public plug::Canvas
{
public:
    Canvas(const size_t width, const size_t height, const plug::Color color);
    Canvas(const char *filename);

    ~Canvas()
    {
        delete m_sf_render_texture;
        delete m_render_texture;
        delete m_selection_mask;
        delete m_texture;
    }

    virtual void draw(const plug::VertexArray &vertex_array) override;

    virtual void draw(const plug::VertexArray &vertex_array, const plug::Texture &texture) override;

    virtual plug::Vec2d getSize(void) const override;

    virtual void setSize(const plug::Vec2d &size) override;

    virtual plug::SelectionMask &getSelectionMask(void) override;

    virtual plug::Color getPixel(size_t x, size_t y) const override;

    virtual void setPixel(size_t x, size_t y, const plug::Color &color) override;

    virtual const plug::Texture& getTexture(void) const override;

    Canvas(const Canvas &other) = delete;
    Canvas &operator= (const Canvas &other) = delete;

private:
    sf::RenderTexture *m_sf_render_texture;
    RenderTexture *m_render_texture;

    SelectionMask *m_selection_mask;
    plug::Texture *m_texture;
};

#endif  // CANVAS_CANVAS_HPP

