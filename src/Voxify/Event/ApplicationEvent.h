//
// Created by Andrew Graser on 3/19/2025.
//


#pragma once

#include "Event.h"

namespace Voxify {
    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) : Width(width), Height(height) {}

        const std::string GetEventType() const override {return "Window Resize Event";}
        static const std::string GetStaticEventType() {return "Window Resize Event";}

    public:
        uint32_t Width {0};
        uint32_t Height {0};
    };
}