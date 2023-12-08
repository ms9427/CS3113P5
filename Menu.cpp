
#include "Menu.h"
#include "Utility.h"

#define MENU_WIDTH 20
#define MENU_HEIGHT 8

unsigned int menu_data[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

void Menu::initialise()
{
	m_state.next_scene_id = -1;

	//Intializing Map
	GLuint map_texture_id = Utility::load_texture("tileset.png");
	m_state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, map_texture_id, 1.0f, 14, 8);

	//Initalizing Player 
	m_state.player = new Entity();
	m_state.player->set_entity_type(PLAYER);
	m_state.player->set_position(glm::vec3(10.5, -7, 0));
	m_state.player->set_movement(glm::vec3(0));
	m_state.player->set_acceleration(glm::vec3(0, -9.81, 0));
	m_state.player->set_speed(2.5);
	m_state.player->m_texture_id = Utility::load_texture("george_0.png");
	m_state.player->set_width(0.9f);
	m_state.player->set_height(0.9f);
	m_state.player->set_jumping_power(5.0f);
	// Walking
	m_state.player->m_walking[m_state.player->LEFT] = new int[4] { 4, 5, 6, 7 };
	m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 8, 9, 10, 11 };
	m_state.player->m_walking[m_state.player->UP] = new int[4] { 12, 13, 14, 15 };
	m_state.player->m_walking[m_state.player->DOWN] = new int[4] { 0, 1, 2, 3 };

	m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
	m_state.player->m_animation_frames = 4;
	m_state.player->m_animation_index = 0;
	m_state.player->m_animation_time = 0.0f;
	m_state.player->m_animation_cols = 4;
	m_state.player->m_animation_rows = 4;
	m_state.player->set_height(0.8f);
	m_state.player->set_width(0.8f);
}

void Menu::update(float delta_time)
{
	m_state.player->update(delta_time, m_state.player, NULL, 0, m_state.map);
}

void Menu::render(ShaderProgram* program)
{
	m_state.player->render(program);
	m_state.map->render(program);

	GLuint font_texture_id = Utility::load_texture("font1.png");
	Utility::draw_text(program, font_texture_id, "Collecting Chris", 0.5f, 0.001f, glm::vec3(7, 0, 0));
	Utility::draw_text(program, font_texture_id, "Collect the Key!", 0.4f, 0.001f, glm::vec3(7.5, -1, 0));
	Utility::draw_text(program, font_texture_id, "USE SPACE & ARROW KEYS", 0.4f, 0.001f, glm::vec3(6.5, -2, 0));
	Utility::draw_text(program, font_texture_id, "Press ENTER to Start", 0.4f, 0.001f, glm::vec3(6.5, -3, 0));
}