#include "event_dispatcher.h"

EventDispatcher* EventDispatcher::mInstance = nullptr;

void EventDispatcher::subscribe(EventHandler* handler, Uint32 type) {
    if (!mInstance)
        mInstance = new EventDispatcher;

    EventSubscription subscription(handler, type);
    mInstance->subscribePrivate(subscription);
}

void EventDispatcher::pollEvents() {
    if (!mInstance)
        mInstance = new EventDispatcher;

    SDL_Event event;
    EventSubscriptions subs = mInstance->mSubscriptions;
    while (SDL_PollEvent(&event)) {
        for (EventSubscriptions::iterator it = subs.begin(); it != subs.end();
             ++it) {
            EventHandler* handler = it->first;
            Uint32 eventType = it->second;
            if (event.type == eventType)
                handler->handleEvent(event);
        }
    }
}

void EventDispatcher::subscribePrivate(const EventSubscription& subscription) {
    mSubscriptions.insert(subscription);
}