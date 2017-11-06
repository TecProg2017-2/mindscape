/**
 * @file translator.cpp
 * @brief Purpose: Contain a method to make the communication between
 * the user and the keyboard, checking the keys defined early.
 *
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/ master/LICENSE.md
 */

#include "translator.hpp"

using namespace engine;

bool Translator::is_a_valid_event;
const std::string game_object_default_name = "";
const std::string game_object_name = "little_girl";
const int game_object_key = 50;

/**
 * @brief Create a list of GameEvent.
 *
 * Creates a list of events for each key listed, checking if each key has
 * already been listed before, defining a key with an action.
 *
 * @ param keyboard_events Events for each key configured.
 * @return list<GameEvent> List of keys that has an event associated.
 */
std::list<GameEvent> Translator::keyboard_events_to_game_events(
    std::list<KeyboardEvent> keyboard_events) {

    std::list<GameEvent> game_events;
    std::map<KeyboardEvent::Key, bool> used_keys;

    for (auto keyboard_event : keyboard_events) {
        KeyboardEvent::Key key = keyboard_event.key();
        //bool key_repeated = keyboard_event.repeated();
        bool key_released = keyboard_event.state();

        auto used_key = used_keys.find(key);

        if (used_key == used_keys.end()) {
            used_keys[key] = false;
        }
        else {
            used_keys[key] = true;
        }

        for (auto game_object : EventHandler::listeners) {
            if ((game_object->name == game_object_name && key == game_object_key) 

                && (key_released)) {
                continue;
            }
            else {
          		/* Do  nothing*/
          	}

            if (game_object->translations[key] != game_object_default_name && !used_keys[key]) {
                auto game_event = GameEvent(
                    game_object->name,
                    game_object->translations[key],
                    keyboard_event.state()
                );

                game_events.push_back(game_event);
            }
            else {
          		/* Do  nothing*/
          	}
        }
    }

    auto default_game_event = GameEvent(
        "All",
        "Update",
        engine::KeyboardEvent::State::PRESSED
    );

    game_events.push_back(default_game_event);

    return game_events;
}
