/**
 * @file EventManager.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief
 *
 * @version 0.1
 * @date 2023-11-24
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef EVENT_EVENT_MANAGER_HPP
#define EVENT_EVENT_MANAGER_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include "plug/event.hpp"
#include "plug/math.hpp"
#include "plug/widget.hpp"

/**
 * @brief Converter from SFML events to universal events
 */
class EventManager
{
public:
    EventManager(sf::Window &window, plug::TransformStack &stack) :
        m_window(window), m_stack(stack), m_shiftPressed(false),
        m_ctrlPressed(false), m_altPressed(false) {}

    EventManager(const EventManager &)            = delete;
    EventManager &operator=(const EventManager &) = delete;

    ~EventManager(void) = default;

    /**
     * @brief Send all available events to widget
     *
     * @param[in] widget	Receiver of events
     */
    void sendEvents(plug::Widget *widget);

private:
    plug::MouseMoveEvent        convertMove          (const sf::Event &sf_event) const;
    plug::MousePressedEvent     convertMousePressed  (const sf::Event &sf_event) const;
    plug::MouseReleasedEvent    convertMouseReleased (const sf::Event &sf_event) const;
    plug::KeyboardPressedEvent  convertKeyPressed    (const sf::Event &sf_event) const;
    plug::KeyboardReleasedEvent convertKeyReleased   (const sf::Event &sf_event) const;
    plug::TickEvent             makeTickEvent        (void);

    sf::Window &m_window;
    plug::TransformStack &m_stack;
    sf::Clock m_clock;

    bool m_shiftPressed;
    bool m_ctrlPressed;
    bool m_altPressed;
};

#endif  // EVENT_EVENT_MANAGER_HPP

