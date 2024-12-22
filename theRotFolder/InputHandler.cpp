//
// Created by troll on 12/8/2024.
//

#include "InputHandler.h"

#include <cstdio>

InputEventMapType InputHandler::inputEventMap;

void InputHandler::PollInputEvents()
{
     SDL_Event event;

     const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
     const uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);

     if (keyboardState == nullptr) return;

     for (const auto& pair : inputEventMap)
     {
          if (keyboardState[pair.first.keycode])
          {
               BroadCast(pair.second.callbacks, SDL_Event());
          }

          if (mouseState & SDL_BUTTON(1) && pair.first.eventType == SDL_MOUSEBUTTONDOWN)
          {
               BroadCast(pair.second.callbacks, SDL_Event());
          }

     }
}

void InputHandler::BindEvent(const SDL_EventData& event, const std::function<void(const SDL_Event&)>& callback)
{
     auto& callbacksObject = inputEventMap[event];

     const auto callbackItr = std::ranges::find_if(callbacksObject.callbacks.begin(), callbacksObject.callbacks.end(),
          [callback](const InputCallback::CallbackType& currentCallback)
          {
               return currentCallback.target<InputCallback::CallbackType>() == callback.target<InputCallback::CallbackType>();
          });

     if (callbackItr != callbacksObject.callbacks.end()) return;

     callbacksObject.callbacks.push_back(callback);
}

void InputHandler::UnBindEvent(const SDL_EventData& event, const std::function<void(const SDL_Event&)>& callback)
{
     const auto itr = inputEventMap.find(event);
     if (itr == inputEventMap.end()) return;

     const auto callbackItr = std::ranges::find_if(itr->second.callbacks.begin(), itr->second.callbacks.end(),
          [&callback](const InputCallback::CallbackType& currentCallback)
          {
               return currentCallback.target<InputCallback::CallbackType>() == callback.target<InputCallback::CallbackType>();
          });

     if (callbackItr == itr->second.callbacks.end()) return;

     itr->second.callbacks.erase(callbackItr);
}

void InputHandler::ConfigureEvent(const SDL_EventData &event, bool onlyOnFirstInput, bool callbackWhilePressed)
{
     auto& callback = inputEventMap[event];

     callback.callbackWhilePressed = callbackWhilePressed;
     callback.onlyOnFirstInput = onlyOnFirstInput;
}

void InputHandler::BroadCast(const std::vector<std::function<void(const SDL_Event&)>>& callbacks, const SDL_Event& event)
{
     for (const auto& callback : callbacks)
     {
          if (callback != nullptr) callback(event);
     }
}
