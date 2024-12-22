//
// Created by troll on 12/8/2024.
//
#pragma once

#include <functional>
#include <SDL.h>

//for now i am not sure exactly how to design the input handler properly.

///an analogy if you may... this is my child. I WILL NOT MARRY MY CHILD!! Therefore, I must leave it to die and rot... AMONG US VIDEO GAME!!!!!!

//I'm not going to lie... I kind of got an erection.
struct SDL_EventData
{
    SDL_EventData() = default;

    explicit SDL_EventData(const SDL_Event& event): eventType(static_cast<SDL_EventType>(event.type)), keycode(event.key.keysym.sym) {};
    explicit SDL_EventData(const SDL_EventType& eventType, const SDL_Keycode& keycode = 0): eventType(eventType), keycode(keycode)  {};
    ~SDL_EventData() = default;

    bool operator==(const SDL_EventData& rhs) const
    {
        return this->eventType == rhs.eventType && keycode == rhs.keycode;
    }



    SDL_EventType eventType = SDL_EventType();
    SDL_Keycode keycode = 0;
};

//to make SDL_EventData compatible with maps we need to overload the parenthesis operator so the generic code in the map
//can hash using my struct (sexy?)
struct SDL_EventDataHasher {
    size_t operator()(const SDL_EventData& eventData) const
    {
        return std::hash<SDL_EventType>()(eventData.eventType) ^ std::hash<SDL_Keycode>()(eventData.keycode) << 1;
    }
};


struct InputCallback
{
    InputCallback() = default;
    explicit InputCallback(const std::function<void(const SDL_Event&)>& callback)
    {
        callbacks.push_back(callback);
    }

    ~InputCallback() = default;

    using CallbackType = std::function<void(const SDL_Event&)>;

    std::vector<CallbackType> callbacks;

    //variables to tell in what way we want to call the callbacks
    bool onlyOnFirstInput = true;
    bool callbackWhilePressed = false;

    //variables to tell the current input state
    bool inputStarted = false;
};

using InputEventMapType = std::unordered_map<SDL_EventData, InputCallback, SDL_EventDataHasher>;

class InputHandler
{
public:

    static void PollInputEvents();
    static void BindEvent(const SDL_EventData& event, const std::function<void(const SDL_Event&)>& callback);
    static void UnBindEvent(const SDL_EventData& event, const std::function<void(const SDL_Event&)>& callback);
    static void ConfigureEvent(const SDL_EventData& event, bool onlyOnFirstInput = true, bool callbackWhilePressed = false);

protected:

    static void BroadCast(const std::vector<std::function<void(const SDL_Event&)>>& inputCallback, const SDL_Event& event);

    static InputEventMapType inputEventMap;
};
