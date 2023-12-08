#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Utility.h"
#include "Entity.h"
#include "Map.h"

struct GameState
{
    Map* map;
    Entity* player;
    Entity* enemies;
    Entity* keys;

    Mix_Music* bgm;
    Mix_Chunk* jump_sfx;

    int next_scene_id;
};

class Scene {
public:
    int m_number_of_enemies = 1;
    int m_number_of_keys = 1;

    GameState m_state;

    
    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram* program) = 0;
    void update_lives(int previous_lives) {
        m_state.player->num_lives = previous_lives;
    }

    GameState const get_state() const { return m_state; }

    //ADDED
    void const set_number_of_enemies(int num_enemies) { m_number_of_enemies = num_enemies; }
    void const set_number_of_keys(int num_keys) { m_number_of_keys = num_keys; }
    int const get_number_of_enemies() const { return m_number_of_enemies; }
    int const get_number_of_keys() const { return m_number_of_keys; }
};