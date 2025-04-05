//
// Created by Andrew Graser on 3/22/2025.
//


#pragma once

#include "Event.h"

namespace Voxify {
    class KeyPressEvent : public Event {
    public:
        KeyPressEvent(int keycode) : KeyCode(keycode) {}

        const std::string GetEventType() const override {return "Key Down Event";}
        static const std::string GetStaticEventType() {return "Key Down Event";}

        int KeyCode {0};
    };

    class KeyReleaseEvent : public Event {
    public:
        KeyReleaseEvent(int keycode) : KeyCode(keycode) {}

        const std::string GetEventType() const override {return "Key Release Event";}
        static const std::string GetStaticEventType() {return "Key Release Event";}

        int KeyCode {0};
    };
}