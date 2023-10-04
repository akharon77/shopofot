// #ifndef BUTTON_HPP
// #define BUTTON_HPP
// 
// #include "widget.hpp"
// #include "vector2.hpp"
// 
// class Button : public Widget
// {
//     Vector2f m_pos;
//     Vector2f m_size;
// 
//     sf::Texture *m_texture;
// 
//     sf::IntRect  m_default_rect;
//     sf::IntRect  m_pressed_rect;
//     sf::IntRect  m_focused_rect;
// 
//     virtual bool checkMousePos(int32_t x, int32_t y);
// 
// public:
//     Button(Vector2f pos, Vector2f size, sf::Texture &texture, sf::IntRect default_rect, sf::IntRect pressed_rect, sf::IntRect focused_rect);
//     ~Button();
// 
//     virtual void draw(sf::RenderTarget &target) override;
// 
//     virtual bool onMousePressed  (MouseKey key) override;
//     virtual bool onMouseReleased (MouseKey key) override;
// 
//     virtual bool onMouseMoved (int32_t x, int32_t y) override;
// 
//     virtual bool onKeyboardPressed  (KeyboardKey key) {};
//     virtual bool onKeyboardReleased (KeyboardKey key) {};
// 
//     virtual bool onTime (float d_seconds) override;
// };
// 
// #endif  // BUTTON_HPP
// 
