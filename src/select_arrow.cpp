/**
 * @file select_arrow.cpp
 * @brief Purpose: Contains the methods for SelectArrow class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "select_arrow.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "../engine/include/audio.hpp"
#include "level_factory.hpp"

using namespace mindscape;
const int adition_time = 200;

const int level_1_y_position = 175;
const int level_2_y_position = 227;
const int level_credits_y_position = 280;
const int level_exit_y_position = 335;

const std::string arrow_font_path = "../assets/fonts/FFF_Tusj.ttf";
const std::string arrow_font_name = "selector";
const int arrow_font_priority = 5;
const int arrow_font_size = 35;

/**
 * @brief Constructor for SelectArrow
 *
 * @param name Name of the object.
 * @param position Pair of integers representing x and y position.
 * @param priority Priority on rendering.
 *
 * @return void
 */
SelectArrow::SelectArrow(
		std::string name,
		std::pair<int, int> position,
		int priority)
		: engine::GameObject(
		name,
		position,
		priority,
		{
				{engine::KeyboardEvent::UP,     "UP"},
				{engine::KeyboardEvent::DOWN,   "DOWN"},
				{engine::KeyboardEvent::RETURN, "ENTER"}
		}
) {
	initialize_arrow();
};

/**
 * @brief Initializes the arrow
 *
 * @return void
 */
void SelectArrow::initialize_arrow() {
	engine::Game game = engine::Game::get_instance();

	engine::Text *selector = new engine::Text(game.get_renderer(),
										 arrow_font_name, std::make_pair(0, 0), arrow_font_priority, ">",
										 arrow_font_path, arrow_font_size
	);

	selector->activate();
	add_component(selector);
	timer->init();

	action = new Action(Action::Command::CHANGE_SCENE);
}

/**
 * @brief Process received Game Events
 *
 * Process received game events according to the override of the method
 *
 * @param game_event The Game Event to be processed.
 *
 * @return void
 */
void SelectArrow::on_event(GameEvent game_event) {
	std::string event_name = game_event.game_event_name;

	time += timer->time_elapsed() - time_aux;
	time_aux = timer->time_elapsed();

	if (enable) {
		if (event_name == "DOWN") {
			enable = false;
			next_time = time + adition_time;

			if (arrow_seletor >= 0 && arrow_seletor < 3) {
				arrow_seletor += 1;
			} else {
				arrow_seletor = 0;
			}
		}

		if (event_name == "UP") {
			enable = false;
			next_time = time + adition_time;

			if (arrow_seletor <= 3 && arrow_seletor > 0) {
				arrow_seletor -= 1;
			} else {
				arrow_seletor = 3;
			}
		}
	}

	if (enable == false) {
		if (time > next_time) {
			enable = true;
			time = 0;
		}
	}


	switch (arrow_seletor) {

		//Initialize
		case (0):
			set_position(std::make_pair(get_position().first, level_1_y_position));

			if (event_name == "ENTER") {
				action->execute("../data/1.level.dat");
			}
			break;

			//Instructions
		case (1):
			set_position(std::make_pair(get_position().first, level_2_y_position));

			if (event_name == "ENTER") {
				action->execute("../data/2.level.dat");
			}
			break;

			//Credits
		case (2):
			set_position(std::make_pair(get_position().first, level_credits_y_position));

			if (event_name == "ENTER") {
				action->execute("../data/credits_scene.dat");
			}
			break;

			//Exit
		case (3):
			set_position(std::make_pair(get_position().first, level_exit_y_position));

			if (event_name == "ENTER") {
			}
			break;

		default:
			break;
	}
}

/**
 * @brief Updates the object state
 *
 * @return void
 */
void SelectArrow::update_state() {
}