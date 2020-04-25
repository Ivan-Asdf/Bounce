#pragma once
#include <set>
#include <utility> // std::pair

#include <SDL2/SDL.h>

class EventDispatcher;

class EventHandler {
    friend class EventDispatcher;

private:
    virtual void handleEvent(SDL_Event event) = 0;
};

typedef std::pair<EventHandler*, Uint32> EventSubscription;
typedef std::set<EventSubscription> EventSubscriptions;

class EventDispatcher {
public:
    static void subscribe(EventHandler* handler, Uint32 type);
    static void pollEvents();

private:
    void subscribePrivate(const EventSubscription& handler);
    void pollEventsPrivate();

    EventSubscriptions mSubscriptions;

    static EventDispatcher* mInstance;
};