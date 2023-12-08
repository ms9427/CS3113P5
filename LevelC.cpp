#include "LevelC.h"
#include "Utility.h"

#define LEVELC_HEIGHT 8
#define LEVELC_WIDTH 20

#define LEVELC_ENEMY_COUNT 3
#define LEVELC_KEY_COUNT 1

unsigned int LEVELC_DATA[] =
{

    5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
    5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 5,
    5, 0, 5, 5, 0, 0, 0, 5, 5, 5, 0, 0, 5, 5, 0, 0, 0, 5, 5, 5,
    5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

LevelC::~LevelC()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelC::initialise()
{
    m_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture("tileset.png");
    m_state.map = new Map(LEVELC_WIDTH, LEVELC_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 16, 7);

    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
     // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(2.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("george_0.png");

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

    // Jumping
    m_state.player->m_jumping_power = 6.0f;

    /**
      Enemies' stuff */
    GLuint enemy_texture_id1 = Utility::load_texture("enemy.png");
    GLuint enemy_texture_id2= Utility::load_texture("enemy.png");
    GLuint enemy_texture_id3 = Utility::load_texture("enemy.png");
    m_state.enemies = new Entity[LEVELC_ENEMY_COUNT];

    for (int i = 0; i < LEVELC_ENEMY_COUNT; i++)
    {
        if (i == 0)
        {
            m_state.enemies[i].set_entity_type(ENEMY);
            m_state.enemies[i].set_ai_type(GUARD);
            m_state.enemies[i].set_ai_state(IDLE);
            m_state.enemies[i].m_texture_id = enemy_texture_id1;
            m_state.enemies[i].set_movement(glm::vec3(0.0f));
            m_state.enemies[i].set_speed(0.9f);
            m_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
            m_state.enemies[i].set_width(0.7f);
            m_state.enemies[i].set_height(0.7f);
            m_state.enemies[i].set_position(glm::vec3(4.0f, -3.0f, 0.0f));
        }
        else if (i == 1)
        {
            m_state.enemies[i].set_entity_type(ENEMY);
            m_state.enemies[i].set_ai_type(GUARD);
            m_state.enemies[i].set_ai_state(IDLE);
            m_state.enemies[i].m_texture_id = enemy_texture_id2;
            m_state.enemies[i].set_movement(glm::vec3(0.0f));
            m_state.enemies[i].set_speed(0.9f);
            m_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
            m_state.enemies[i].set_width(0.7f);
            m_state.enemies[i].set_height(0.7f);
            m_state.enemies[i].set_position(glm::vec3(13.0f, -4.0f, 0.0f));

        }
        else 
        {
            m_state.enemies[i].set_entity_type(ENEMY);
            m_state.enemies[i].set_ai_type(GUARD);
            m_state.enemies[i].set_ai_state(IDLE);
            m_state.enemies[i].m_texture_id = enemy_texture_id3;
            m_state.enemies[i].set_movement(glm::vec3(0.0f));
            m_state.enemies[i].set_speed(0.9f);
            m_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
            m_state.enemies[i].set_width(0.7f);
            m_state.enemies[i].set_height(0.7f);
            m_state.enemies[i].set_position(glm::vec3(17.0f, -5.0f, 0.0f));

        }
    }

    //Initlaizing Keys
    m_state.keys = new Entity[LEVELC_KEY_COUNT];

    for (int i = 0; i < LEVELC_KEY_COUNT; i++)
    {
        m_state.keys[i].set_entity_type(KEY);
        m_state.keys[i].m_texture_id = Utility::load_texture("key.png");
        m_state.keys[i].set_width(0.5f);
        m_state.keys[i].set_height(0.5f);
        m_state.keys[i].set_position(glm::vec3(18, -3, 0));
    }

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_state.bgm = Mix_LoadMUS("beauty_flow.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(10.0f);

    m_state.jump_sfx = Mix_LoadWAV("jump.wav");
}

void LevelC::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.keys, LEVELC_KEY_COUNT, m_state.map);

    for (int i = 0; i < LEVELC_ENEMY_COUNT; i++)
    {
        m_state.enemies[i].update(delta_time, m_state.player, m_state.player, 1, m_state.map);
    }

    for (int i = 0; i < LEVELC_KEY_COUNT; i++)
    {
        m_state.keys[i].update(delta_time, m_state.player, m_state.player, 1, m_state.map);
    }

    if (m_state.player->num_keys_collected == LEVELC_KEY_COUNT)
    {
        m_state.next_scene_id = -2;
    }

    if (m_state.player->reset_level == true) {
        m_state.next_scene_id = 3;
    }
}

void LevelC::render(ShaderProgram* program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < LEVELC_ENEMY_COUNT; i++) {
        m_state.enemies[i].render(program);
    }
    m_state.keys->render(program);

    if (m_state.player->num_keys_collected == LEVELC_KEY_COUNT)

    {
        for (int i = 0; i < LEVELC_ENEMY_COUNT; i++) {
            m_state.enemies[i].m_is_active = false;
        }
        Utility::draw_text(program, Utility::load_texture("font1.png"), "You Win!", 0.5f, -0.25f, glm::vec3(14.0f, -2.0f, 0.0f));
    }

    if (m_state.player->m_is_active == false) {
        Utility::draw_text(program, Utility::load_texture("font1.png"), "You Lose!", 0.5f, -0.25f, glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y - 2.0f, 0.0f));
    }
}