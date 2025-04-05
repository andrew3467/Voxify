//
// Created by Andrew Graser on 3/19/2025.
//


#pragma once


namespace Voxify {
    class Event {
    public:
        virtual const std::string GetEventType() const = 0;
        static const std::string GetStaticEventType() {return "Base Event: Should not used";}

    public:
        bool Handled { false };
    };


    template<typename EventType>
    using EventHandler = std::function<void(const EventType& e)>;

    class EventHandlerWrapperInterface {
    public:
        virtual ~EventHandlerWrapperInterface() = default;

        void Exec(const Event& e) {
            Call(e);
        }

        virtual const std::string& GetType() const = 0;

    private:
        virtual void Call(const Event& e) = 0;
    };

    template<typename EventType>
    class EventHandlerWrapper : public EventHandlerWrapperInterface {
    public:
        explicit EventHandlerWrapper(const EventHandler<EventType>& handler)
            : mHandler(handler), mHandlerType(mHandler.target_type().name()) {};

        ~EventHandlerWrapper() override = default;

    private:
        void Call(const Event& e) override {
            if(e.GetEventType() == EventType::GetStaticEventType()) {
                mHandler(static_cast<const EventType&>(e));
                VOXIFY_INFO(e.Handled);
            }
        }

        const std::string& GetType() const override {return mHandlerType;}

        EventHandler<EventType> mHandler;
        const std::string mHandlerType;
    };

    class EventManager {
    public:
        void Shutdown() {
            mSubscribers.clear();
        }

        void Subscribe(const std::string& eventId, std::unique_ptr<EventHandlerWrapperInterface>&& handler) {
            auto subscribers = mSubscribers.find(eventId);
            if(subscribers != mSubscribers.end()) {
                auto &handlers = subscribers->second;
                for (auto &it: handlers) {
                    if (it->GetType() == handler->GetType()) {
                        VOXIFY_ASSERT(false, "Attempting to double register callback");
                        return;
                    }
                }
                handlers.push_back(std::move(handler));
            }
            else {
                mSubscribers[eventId].push_back(std::move(handler));
            }
        }

        void Unsubscribe(const std::string& eventID, const std::string& handlerName) {
            auto& handlers = mSubscribers[eventID];
            for(auto it = handlers.begin(); it != handlers.end(); ++it) {
                if(it->get()->GetType() == handlerName) {
                    it = handlers.erase(it);
                    return;
                }
            }
        }

        void TriggerEvent(const Event& event) {
            for(auto& handler : mSubscribers[event.GetEventType()]) {
                handler->Exec(event);
            }
        }

        void QueueEvent(std::unique_ptr<Event>&& event) {
            mEventQueue.push_back(std::move(event));
        }

        void DispatchEvents() {
            for(auto it = mEventQueue.begin(); it != mEventQueue.end();) {
                if(!it->get()->Handled) {
                    TriggerEvent(*it->get());
                    it = mEventQueue.erase(it);
                }else{
                    ++it;
                }
            }
        }


    private:
        std::vector<std::unique_ptr<Event>> mEventQueue;
        std::unordered_map<std::string, std::vector<std::unique_ptr<EventHandlerWrapperInterface>>> mSubscribers;

    };







    namespace EventSystem {
        extern EventManager sEventManager;

        template<typename EventType>
        inline void Subscribe(const EventHandler<EventType> &callback) {
            std::unique_ptr<EventHandlerWrapperInterface> handler = std::make_unique<EventHandlerWrapper<EventType>>(callback);
            sEventManager.Subscribe(EventType::GetStaticEventType(), std::move(handler));
        }

        template<typename EventType>
        inline void Unsubscribe(const EventHandler<EventType> &callback) {
            const std::string handlerName = callback.target_type().name();
            sEventManager.Unsubscribe(EventType::GetStaticEventType(), handlerName);
        }

        inline void TriggerEvent(const Event &event) {
            sEventManager.TriggerEvent(event);
        }

        inline void QueueEvent(std::unique_ptr<Event>&& event) {
            sEventManager.QueueEvent(std::forward<std::unique_ptr<Event>>(event));
        }

        inline void DispatchEvents() {
            sEventManager.DispatchEvents();
        }
    }
}