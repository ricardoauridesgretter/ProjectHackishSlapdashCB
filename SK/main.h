#pragma once

/*

ESSE APLICATIVO FOI DESENVOLVIDO POR "RICARDO AURIDES GRETTER", DE 2016 À 2017.
PROJETADO E PROGRAMADO POR "RICARDO AURIDES GRETTER".
(C) COPYRIGHT 2016-2017 RICARDO AURIDES GRETTER - TODOS OS DIREITOS RESERVADOS.
ESSE APLICATIVO USA A LINGUAGEM DE PROGRAMAÇÃO "C" E O FRAMEWORK DE JOGOS "ALLEGRO 5".

THIS APPLICATION WAS DEVELOPED BY "RICARDO AURIDES GRETTER", FROM 2016 TO 2017.
DESIGNED AND PROGRAMMED BY "RICARDO AURIDES GRETTER".
(C) COPYRIGHT 2016-2017 RICARDO AURIDES GRETTER - ALL RIGHTS RESERVED.
THIS APPLICATION USES THE "C" PROGRAMMING LANGUAGE AND THE "ALLEGRO 5" GAME FRAMEWORK.

*/

#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_memfile.h"
//#include "allegro5/allegro_physfs.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"
//#include "time64.h"
//#include "SFML\System.hpp"
//#include "SFML\Audio.hpp"

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdarg>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <limits>
#include <cerrno>

// 
// DEFINES, CONSTANTES
//

#define SUCCESS 1
#define FAILURE 0
#define PROBLEM -1
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define START_X_POS 35
#define START_Y_POS 35
#define PLAYER_INITIAL_X ( SCREEN_WIDTH / 5 )
#define PLAYER_INITIAL_Y ( SCREEN_HEIGHT / 2 )
#define FRAME_RATE 60
#define PLAYER_LIVES 5
#define PLAYER_MAX_LIVES 9
#define PLAYER_MIN_LIVES 0
#define PLAYER_SHIP_SPEED 7
#define PLAYER_BOUNDX 40
#define PLAYER_BOUNDY 24
#define PLAYER_NUM_KEYS 18
#define PLAYER_NUM_WEAPONS 10
#define PLAYER_NUM_BULLETS 25
#define PLAYER_BULLET_SPEED 9
#define PLAYER_BULLET_RADIUS 3
#define PLAYER_BITMAP "assets/ship.png"
#define BULLET_START_X 50
#define BULLET_START_Y 7
#define MAX_NUM_COMETS 10
#define PLANE_FIRING_COOLDOWN 45
#define COMET_SPAWN_RATE 500
#define COMET_NUM_BULLETS 10
#define COMET_BULLET_SPEED 10
#define COMET_BULLET_RADIUS 2
#define COMET_MOVE_SPEED 6
#define COMET_BOUNDX 18
#define COMET_BOUNDY 18
#define COMET_BODY_RADIUS 20
#define COMET_POSITION_BUFFER 25
#define PLAYER_FIRING_COOLDOWN 18
#define COMET_FIRING_COOLDOWN 9999
#define COMET_FIRING_TRIGGER 120
#define ANGLE 45
#define BLOCK_SIZE 64
#define MAP_COLUMNS 10
#define MAP_ROWS 10
#define CAMERA_SCROLLING_SPEED 5
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define GRAVITY 0.5
#define ACCELERATION 0.25
#define PLAYER_JUMP_SPEED 12
#define PLAYER_HORIZONTAL_SPEED 0
#define PLAYER_VERTICAL_SPEED 5
#define PI 3.14159265359
#define GAME_TITLE "UNTITLED"
#define TITLE_MENU_SPACING 40
#define GAME_DEVELOPER "RICARDOMINATOR"
#define GAME_DEVELOPER2 "Ricardominator"
#define GAME_AUTHORSHIP "ALL RIGHTS RESERVED "
#define GAME_YEAR "2016 "
#define GAME_INFO "(C) " GAME_YEAR GAME_DEVELOPER GAME_AUTHORSHIP	
#define NUM_BUTTONS 10
#define OTHER_MENU_SPACING 36
#define FONT_SIZE_MENU 36
#define FONT_SIZE_TITLE 48
#define PLAYER_NUM_ACTIONS 10
#define KEY_NAME 15
#define OPTIONS_MENU_SPACING 36
#define CREDITS_MENU_SPACING 80
#define PASSWORD_MENU_SPACING 45
#define PLAYER_CONTINUES 10
#define PLAYER_CREDITS 10
#define NUM_SOUNDS 25
#define MOUSE_BUTTONS 3
#define BGM_MAX_VOLUME 1.0
#define SFX_MAX_VOLUME 1.0
#define JINGLE_MAX_VOLUME 100
#define EASING_AMOUNT 0.35
#define MINIMUM_DISTANCE 1.0
#define BULLET_NUM_DIRECTIONS 8
#define NUM_ENEMIES 15
#define NUM_POWERUPS 5
#define NUM_HEARTS 5
#define NUM_ITEMS 10
#define NUM_COLLECTIBLES 35
#define NUM_BACKGROUNDS 3
#define ENEMY_POSITION_BUFFER 20
#define ENEMY_SPAWN_RATE 750
#define PLANE_OFFSCREEN_X 250
#define PLANE_OFFSCREEN_Y 50
#define PLANE_SPAWN_INTERVAL 120
#define PLANE_BOUNDX 100
#define PLANE_BOUNDY 18
#define PLANE_AREAX PLANE_BOUNDX * 3
#define PLANE_AREAY PLANE_BOUNDY * 3
#define PLANE_OFFSETX 100
#define PLANE_OFFSETY 100
#define ENEMY_NUM_BULLETS 7
#define SPACEMINE_BOUNDX 72
#define SPACEMINE_BOUNDY 72
#define CHEMTRAIL_BOUNDX 2
#define CHEMTRAIL_BOUNDY 2
#define CHEMTRAILS_SPEEDX 3
#define CHEMTRAILS_SPEEDY 3
#define PLANE_WHITE_SPEED PLAYER_SHIP_SPEED * 0.50
#define COLLECTIBLE_SPEED PLANE_WHITE_SPEED
#define PLANE_RED_SPEED PLANE_WHITE_SPEED + 1.50
#define COLLECTIBLE_BOUNDX 42
#define COLLECTIBLE_BOUNDY 42
#define COLLECTIBLE_SPAWN_INTERVAL 120
#define COLLECTIBLE_HORIZONTAL_BUFFER 15
#define COLLECTIBLE_VERTICAL_BUFFER 15
#define VOICE_SAMPLE_RATE 48000
#define MASTER_MIXER_SAMPLE_RATE 48000
#define MUSIC_MIXER_SAMPLE_RATE 44100
#define SOUND_MIXER_SAMPLE_RATE 22050
#define SPEECH_MIXER_SAMPLE_RATE 22050
#define MODULE_MIXER_SAMPLE_RATE 32000
#define STREAM_MIXER_SAMPLE_RATE 44100
#define MAX_RGB_VALUE 255
#define MIN_RGB_VALUE 0
#define LEVEL01_BACKGROUND_IMAGE "assets/skyBG.png"
#define LEVEL01_MIDDLEGROUND_IMAGE "assets/skyMG.png"
#define LEVEL01_BACKGROUND_SCROLLING_SPEED 0
#define LEVEL01_MIDDLEGROUND_SCROLLING_SPEED -.5
#define LEVEL03_BACKGROUND_SCROLLING_SPEED 2
#define LEVEL04_BACKGROUND_SCROLLING_SPEED 2
#define COIN_SFX "assets/pickup.wav"
#define PLANE_WHITE_BITMAP "assets/plane2.png"
//#define STRING "270304__littlerobotsoundfactory__collect-point-00.wav"
#define COIN_SFX_VOLUME 0.5
#define HEART_SFX_VOLUME COIN_SFX_VOLUME
#define HEART_SFX "assets/heart.wav"
#define SHOT_SFX "assets/pew.wav"
#define HURT_SFX "assets/hurt.wav"
#define PLANE_OTHER_BITMAP "assets/warplane.png"
#define HEALTH_BITMAP "assets/health.png"
#define SHIELD_BITMAP "assets/shield.png"
#define MACHINE_GUN_BITMAP "assets/machinegun.png"
#define PLANE_RED_BITMAP "assets/redplane.png"
#define EXPLOSION_BITMAP "assets/boom.png"
#define PLANE_SHOT_SAMPLE_PATH "assets/enemyPew.wav"
#define PLANE_RADIUS 222
#define EXPLOSION_SAMPLE_PATH "assets/bossExplode.wav"
#define ENEMY_EXPLOSION_SAMPLE "assets/boom.wav"
#define EXPLOSION_TIMER 100
#define ENEMY_PLANE_RED_COLOR 234
#define NUM_SHIELDS 3
#define BOSS01_BITMAP_PATH "assets/spaceship.png"
#define BOSS01_LIVES 18
#define BOSS01_SPEED 4
#define BOSS01_POSITIONX SCREEN_WIDTH * -0.70
#define BOSS01_POSITIONY SCREEN_HEIGHT * 0.50
#define BOSS01_STARTX SCREEN_WIDTH * -0.70
#define BOSS01_STARTY SCREEN_HEIGHT * 0.50
#define BOSS01_BULLET_RADIUS 3
#define BOSS01_COLLISION_OFFSET 0.18
#define BOSS01_BULLET_SPEED 5
#define BOSS_CUTSCENE 120
#define NUM_BOSSES 3
#define NUM_MID_BOSSES 0
#define BOSS01_BORDERX 332
#define BOSS01_BORDERY 72
#define BOSS01_ATTACK_COOLDOWN 180
#define BOSS_WSCALE 1
#define BOSS_HSCALE 1
#define PLAYER_INVULNERABILITY 280
#define BOSS01_INVULNERABILITY_COOLDOWN 100
#define BOSS_NUM_BULLETS 18
// BOSSES' VERTICAL MOVEMENT
#define BOSS_VMOV 360
// BOSSES' HORIZONTAL MOVEMENT
#define BOSS_HMOV 360
#define BOSS01_SHOT_SAMPLE_PATH "assets/bossPew.FLAC"
#define BOSS01_HURT_SAMPLE_PATH "assets/bossHurt.wav"
#define BOSS01_NUM_PHASES 3
#define NUM_FINAL_BOSS 1
#define FPS_MINUTE 3600
#define FPS_LIMIT FPS_MINUTE * 3
#define BOSS01_FINALX SCREEN_WIDTH * 2.55
#define BOSS01_FINALY SCREEN_HEIGHT * 2.50
#define LEVEL01_BACKGROUND_ALPHA 0.5
#define LEVEL01_BACKGROUND_TINT 0.5
#define LEVEL01_BACKGROUND_RED 0.5
#define LEVEL01_BACKGROUND_GREEN 0.5
#define LEVEL01_BACKGROUND_BLUE 0.5
#define PLAYER_RGB_RED 1
#define PLAYER_RGB_BLUE 1
#define PLAYER_RGB_GREEN 1
#define PLAYER_RGB_ALPHA 1
#define NUM_EXPLOSIONS 18
#define EXPLOSION_SPEED 2
#define SMOKE_BITMAP_PATH "..."
#define SMOKE_SAMPLE "..."
#define BOSS_DEATH_TIMER 360
#define NUM_LEVELS 3
#define LOST_BITMAP "assets/lost.png"
#define LOST_SAMPLE "assets/lostSample.wav"
#define LOST_SONG "assets/lostSong.ogg"
#define TITLE_BITMAP "assets/title.png"
#define PAUSE_SAMPLE "assets/pause.wav"
#define LEVEL02_BACKGROUND "assets/level02_bkg.png"
#define LEVEL02_BACKGROUND2 "assets/level02_bkg2.png"
#define LEVEL02_BACKGROUND_SCROLLING_SPEED -2
#define LEVEL02_BACKGROUND2_SCROLLING_SPEED -1
#define COPTER_BITMAP "assets/copter2.png"
#define COPTER_BULLET_BITMAP "assets/copterBulletBitmap.png"
#define COPTER_BULLET_SAMPLE "assets/copterBulletSample.wav"
#define COPTER_OFFSCREEN_X 140
#define COPTER_OFFSCREEN_Y 60
#define COPTER_FLYING_SAMPLE "assets/copterFlyingSample.wav"
#define NUM_COPTERS 10
#define COPTER_COOLDOWN 85
#define COPTER_SPEED 5
#define COPTER_NUM_BULLETS 20
#define COPTER_BULLET_SPEED 6
#define COPTER_BULLET_RADIUS 3
#define COPTER_VISION_RADIUS 500
#define PLAYER_THRESHOLD 127
#define COPTER_BOUNDX 40
#define COPTER_BOUNDY 26
#define COPTER_HELIX_BITMAP "assets/helix.png"
#define COPTER_LEFT_BOUNDX -22
#define COPTER_RIGHT_BOUNDX -44
#define COPTER_UP_BOUNDY 0
#define COPTER_DOWN_BOUNDY 0
#define COPTER_BULLET_INIT_X -92
#define COPTER_BULLET_INIT_Y 16
#define ANGLE_90 90
#define ANGLE_45 45
#define ANGLE_180 180
#define TITLE_SCREEN_BUTTONS "assets/title_logo.png"
#define TITLE_SCREEN_LOGO "assets/title_full.png"
#define TITLE_NUM_COMMANDS 3
#define MENU_TITLES "assets/menus.png"
#define MENU_FONTS "assets/title_font.png"
#define NUM_ACTIONS 10
#define OPTIONS_NUM_COMMANDS 5
#define CONTROLS_NUM_COMMANDS 11
#define BGM_VOLUME_CONTROL 0.01
#define SFX_VOLUME_CONTROL 0.01
#define NUM_TUNES 10
#define MENU_SELECT_SAMPLE "assets/menuSelect.wav"
#define MENU_CHANGE_SAMPLE "assets/menuSelect2.wav"
#define MENU_CONFIGURE_SAMPLE "assets/menuSelect3.wav"
#define MENU_CANCEL_SAMPLE "assets/menuSelect4.wav"
#define MENU_CONFIRM_SAMPLE "assets/menuConfirm.wav"
#define SOUND_PAN_LEFT -1.0
#define SOUND_PAN_RIGHT +1.0
#define SOUND_PAN_VALUE 0.1
#define COLLECTIBLE_BUFFER_X 30
#define COLLECTIBLE_BUFFER_Y 30
#define PLAYBACK_SPEED 1.0
#define FADE 0
#define FADING 360
#define FADE_BITMAP "assets/fade_effect.png"
#define COLLECTIBLE_BITMAP "assets/gold.png"
#define FADE_LIMIT 255
#define FADE_INCREASE 5
#define FADE_DECREASE -2.575
#define DIV_BY 2
#define DIV_REMAINER 0
#define LOADING_NUM_COMMANDS 3
#define SAVING_NUM_COMMANDS 5
#define SAVEFILE_NAME "savefile"
#define NUM_SAVEFILES 4
#define PAUSING_NUM_COMMANDS 4
#define CONFIRMATION_NUM_COMMANDS 2
#define CONST_ZERO 0
#define CONST_ONE 1
#define CONST_TWO 2
#define CONST_THREE 3
#define CONST_FOUR 4
#define CONST_FIVE 5
#define CONST_SIX 6
#define CONST_SEVEN 7
#define CONST_EIGHT 8
#define CONST_NINE 9
#define CONST_TEN 10
#define CONST_100 100
#define CONST_1000 1000
#define CONST_360 360
#define SETUP_FONT_SIZE 0.35
#define PAUSE_FONT_SIZE 0.35
#define SETUP_START_X 0.0025
#define SETUP_START_Y 0.035
#define SETUP_LETTER_SPACING 72
#define EXIT_REST 1.25
#define SPACESHIP_CANNON_X 0.65
#define SPACESHIP_CANNON_Y 10
#define LOAD_START_X 0.10
#define LOAD_START_Y 0.05
#define LOAD_LETTER_SPACING 72
#define NUM_SKYSCRAPERS 3
#define BOSS02_LIVES 14
#define BOSS02_BOUNDX 156
#define BOSS02_BOUNDY 328
#define BOSS02_BITMAP_PATH "assets/building.png"
#define BOSS02_INVULNERABILITY_COOLDOWN 180
#define BOSS02_NUM_PHASES 3
#define BOSS02_RADIUS 100
#define BOSS02_BULLET_RADIUS 3
#define BOSS02_SPEED 5
#define BOSS02_BULLET_SPEED 6
#define LEVEL_ENDING FPS_MINUTE * 2 + FRAME_RATE * 2
#define BOSS02_STARTX SCREEN_WIDTH * 0.78;
#define BOSS02_STARTY SCREEN_HEIGHT * 1.62;
#define BOSS_LEFT_BOUNDX 0
#define BOSS_RIGHT_BOUNDX 0
#define BOSS_UP_BOUNDY 0
#define BOSS_DOWN_BOUNDY 0
#define BOSS02_CUTSCENE 80
#define BOSS02_ATTACK_COOLDOWN 100
#define BOSS02_FIREX 85
#define BOSS02_FIREY -220
#define CURRENT_LEVEL LEVEL01
#define NEXT_LEVEL LEVEL02
#define HUD_SPACING 25
#define LOST_SCREEN_SPACING 78
#define LOST_SCREEN_PLACEMENT 0.05
#define HUD_PLACEMENT 0.015
#define HUD_FONT_SIZE 0.35
#define HUD_NUMBERS 0.0000125
#define LOST_SCREEN_FONT_SIZE 0.40
#define LOST_SCREEN_LETTERS 35
#define LOST_NUM_COMMANDS 3
#define SFX_START_VOLUME 0.45
#define BGM_START_VOLUME 0.45
#define STAGE_01_BGM "assets/stage1.ogg"
#define STAGE_02_BGM "assets/stage2.ogg"
#define LEVEL03_BGM " "
#define LEVEL04_BGM " "
#define LEVEL05_BGM " "
#define TITLE_BGM "assets/title.ogg"
#define ENDING_BGM "assets/ending2.ogg"
#define BOSS_BGM "assets/boss.ogg"
#define ENDING_LETTER_SPACING 75
#define ENDING_FONT_SIZE 1
#define CREDITS_LETTER_SPACING 40
#define CREDITS_FONT_SIZE 0.50
#define ENDING_FRAMES 360
#define CREDITS_FRAMES 720
#define CREDITS_MARGIN 3
#define CREDITS_THIRD_LINE 0.575
#define FINALE_FRAMES 1080

//
// ENUMERAÇÕES
//

enum EXPLOSION_TYPE
{
	EXP_IMAGE,
	EXP_PRIMITIVE,
	EXP_OTHER
};

enum SCROLLING
{
	UPWARDS,
	DOWNWARDS,
	LEFTWARDS,
	RIGHTWARDS,
	STILL,
	NORTHEAST_45,
	NORTHWEST_45, 
	SOUTHEAST_45, 
	SOUTHWEST_45
};

enum KEYS
{
	UP,
	DOWN, 
	LEFT,
	RIGHT,
	SHOOT, 
	PAUSE, 
	ENTER, 
	ESCAPE, 
	BOMB, 
	SELECT, 
	ZOOM_IN, 
	ZOOM_OUT, 
	ROTATE_LEFT, 
	ROTATE_RIGHT, 
	RESET_ZOOMING_SCALE,
	SHOW_COLLISION
};

enum INPUT_DEVICE
{
	INPUT_DEVICE_KEYBOARD, 
	INPUT_DEVICE_MOUSE, 
	INPUT_DEVICE_JOYSTICK, 
	INPUT_DEVICE_UNKNOWN, 
	INPUT_DEVICE_DEFAULT, 
	INPUT_DEVICE_NONE
};

enum ASSETS
{
	ASSET_LVL01_PIC_PLAYER_LOAD_FAIL, 
	ASSET_LVL01_PIC_BACKGROUND_LOAD_FAIL
};

enum LEVEL
{
	LEVEL00, 
	LEVEL01,
	LEVEL02,
	LEVEL03,
	LEVEL04,
	LEVEL05,
	LEVEL06,
	LEVEL07,
	LEVEL08,
	LEVEL09,
	LEVEL10, 
	TEST
};

enum GAME_LANGUAGE
{
	LANGUAGE_ENGLISH,
	LANGUAGE_SPANISH, 
	LANGUAGE_PORTUGUESE
};

enum PLAYER_STATE
{
	PLAYER_INVULNERABLE,
	PLAYER_VULNERABLE
};

enum STATE
{
	TITLE, 
	CREDITS, 
	GAMEPLAY, 
	LOST, 
	WON, 
	PLAYING, 
	VICTORY, 
	GAMEOVER, 
	PAUSING, 
	SELECTING, 
	FILES, 
	SAVING, 
	LOADING, 
	OPTIONS, 
	PASSWORD, 
	CONTROLS, 
	BOSS_BATTLE, 
	FINAL_BOSS_BATTLE,
	MAPS, 
	ENDING, 
	SOUNDTEST,
	ENDING_A,
	ENDING_B,
	GAME_EXIT,
	LEVEL_SELECT, 
	BOSS_RUSH, 
	TRANSITION, 
	QUITTING_EVERYTHING, 
	QUITTING_GAMEPLAY, 
	SETTING_AUDIO, 
	SAVE_AND_QUIT,
	RESTART, 
	SAVE_AND_CONTINUE,
	QUIT_EVERYTHING,
	QUIT_GAMEPLAY
};

enum SYSTEM_FAILURES
{
	AL_INIT_FAIL, 
	AL_INIT_PRIMITIVES_ADDON_FAIL, 
	AL_INIT_FONT_ADDON_FAIL, 
	AL_INIT_TTF_ADDON_FAIL, 
	AL_INIT_IMAGE_ADDON_FAIL,
	AL_INSTALL_AUDIO_FAIL, 
	AL_INIT_ACODEC_ADDON_FAIL, 
	AL_INSTALL_KEYBOARD_ADDON_FAIL, 
	AL_INSTALL_MOUSE_ADDON_FAIL, 
	AL_INSTALL_JOYSTICK_ADDON_FAIL, 
	AL_INIT_DIALOG_ADDON_FAIL,
	AL_INIT_GAME_SYSTEM

};

enum ACTIONS
{
	FIRE_BULLET, 
	SCREEN_BOMB, 
	USE_POWERUP, 
	MOVE_UP,
	MOVE_DOWN, 
	MOVE_LEFT, 
	MOVE_RIGHT, 
	CONFIRM,
	CANCEL
};

enum COLLECTIBLES
{
	COLLECTIBLE_COIN, 
	COLLECTIBLE_HEALTH, 
	COLLECTIBLE_POINT_MULTIPLIER,
	COLLECTIBLE_WEAPON_UPGRADE, 
	COLLECTIBLE_WEAPON_DOWNGRADE, 
	COLLECTIBLE_NONE,
	COLLECTIBLE_SHIELD,
	COLLECTIBLE_GOAL
};

enum DEVICE_FAILURES
{
	CANNOT_CREATE_DISPLAY, 
	CANNOT_CREATE_EVENT_QUEUE, 
	CANNOT_CREATE_TIMER, 
	CANNOT_GET_KEYBOARD_EVENT_SOURCE, 
	CANNOT_GET_MOUSE_EVENT_SOURCE, 
	CANNOT_GET_JOYSTICK1_EVENT_SOURCE, 
	CANNOT_GET_DISPLAY_EVENT_SOURCE, 
	CANNOT_REGISTER_KEYBOARD_EVENT_SOURCE, 
	CANNOT_REGISTER_MOUSE_EVENT_SOURCE, 
	CANNOT_REGISTER_JOYSTICK1_EVENT_SOURCE, 
	CANNOT_REGISTER_JOYSTICK2_EVENT_SOURCE,
	CANNOT_REGISTER_TIMER_EVENT_SOURCE, 
	CANNOT_REGISTER_DISPLAY_EVENT_SOURCE,
	CANNOT_GET_JOYSTICK2_EVENT_SOURCE,
	CANNOT_GET_TIMER_EVENT_SOURCE, 
	GAME_SYSTEM_INITIALIZED, 
	GAME_SYSTEM_FINALIZED
};

enum AUDIO_PROBLEMS
{
	CANNOT_CREATE_VOICE, 
	CANNOT_CREATE_MASTER_MIXER, 
	CANNOT_CREATE_BGM_MIXER, 
	CANNOT_CREATE_SFX_MIXER, 
	CANNOT_CREATE_MOD_MIXER, 
	CANNOT_CREATE_SPEECH_MIXER, 
	CANNOT_GET_DEFAULT_MIXER, 
	CANNOT_ATTACH_SAMPLE_TO_MIXER,
	CANNOT_ATTACH_SAMPLE_INSTANCE_TO_MIXER,
	CANNOT_SET_SAMPLE_INSTANCE_PLAYMODE,
	CANNOT_ATTACH_MIXER_TO_VOICE,
	CANNOT_ATTACH_MIXER_TO_MIXER,
	CANNOT_CREATE_STREAM_MIXER,
	CANNOT_ATTACH_BGM_MIXER_TO_MASTER_MIXER, 
	CANNOT_ATTACH_SFX_MIXER_TO_MASTER_MIXER,
	CANNOT_ATTACH_MODULE_MIXER_TO_MASTER_MIXER,
	CANNOT_ATTACH_STREAM_MIXER_TO_MASTER_MIXER, 
	CANNOT_PLAY_SAMPLE,
	CANNOT_PLAY_SAMPLE_INSTANCE, 
	CANNOT_LOAD_SAMPLE, 
	CANNOT_LOAD_SAMPLE_INSTANCE,
	CANNOT_RESERVE_SAMPLES
};

enum OBJECT_LOADING
{
	OBJ_SHIP_LOADED, 
	OBJ_BULLET_LOADED,
	OBJ_COMET_LOADED, 
	OBJ_FONT_LOADED, 
	ALL_OBJECTS_INITIALIZED, 
	ALL_OBJECTS_DESTROYED
};

enum FADING_TRANSTIONS
{
	FADE_IN_WHITE,
	FADE_OUT_WHITE, 
	FADE_IN_BLACK, 
	FADE_OUT_BLACK, 
	CROSS_FADE,
	FADE_IN_COLOR,
	FADE_OUT_COLOR
};

enum ID
{
	PLAYER,
	BULLET,
	ENEMY, 
	ITEM, 
	NPC, 
	WARP, 
	COLLECTIBLE, 
	BOSS,
	MID_BOSS,
	FINAL_BOSS,
	GOAL, 
	ANIMATION
};

enum COMET_TYPE
{
	COMET_STANDARD_TYPE, 
	COMET_SINGLE_SHOT,
	COMET_BULLET_WAVE, 
	COMET_FOLLOW_SHIP
};

enum OBJECT_STATE
{
	IDLING, 
	SHOOTING, 
	CHARGING, 
	BOMBING, 
	DYING, 
	FLYING, 
	FOLLOWING,
	DODGING, 
	UNKNOWN
};

enum WEAPON
{
	SINGLE_SHOT,
	DOUBLE_SHOT,
	TRIPLE_SHOT,
	BACK_SHOT,
	FULL_SHOT,
	MACHINE_GUN_SHOT,
	TEST_WEAPON
};

enum ENEMY_STATE
{
	ENEMY_IDLE, 
	ENEMY_SHOOT, 
	ENEMY_MOVE_UP, 
	ENEMY_MOVE_DOWN, 
	ENEMY_MOVE_LEFT, 
	ENEMY_MOVE_RIGHT, 
	ENEMY_DIE, 
	ENEMY_BURST
};


enum FACING_DIRECTION
{
	NORTH, 
	SOUTH, 
	EAST, 
	WEST, 
	NORTHEAST, 
	NORTHWEST, 
	SOUTHEAST, 
	SOUTHWEST, 
	NO_DIRECTION, 
	IDLE
};

enum BOSS_BEHAVIOR
{
	BOSS_IDLING,
	BOSS_ATTACKING,
	BOSS_DYING, 
	BOSS_INVULNERABLE,
	BOSS_GETTING_HIT,
	BOSS_GETTING_HURT,
	BOSS_MOVING_UP,
	BOSS_MOVING_STRAIGHT,
	BOSS_MOVING_DOWN,
	BOSS_MOVING_LEFT,
	BOSS_MOVING_RIGHT,
	BOSS_WAITING,
	BOSS_ANIMATING,
	BOSS_GETTING_READY
};

enum LoadState
{
	TILESET, MAP
};

enum ENEMY_TYPES
{
	ENEMY_PLANE_WHITE, 
	ENEMY_PLANE_RED,
	ENEMY_WARPLANE_GREEN, 
	ENEMY_WARPLANE_RED,
	ENEMY_COPTER_BLACK, 
	ENEMY_COPTER_RED, 
	ENEMY_COPTER_WHITE, 
	ENEMY_COPTER_YELLOW, 
	ENEMY_COPTER_BLUE, 
	ENEMY_COPTER_GREEN, 
	ENEMY_COPTER_PINK,
	ENEMY_SPACE_MINE_GRAY, 
	ENEMY_SPACE_MINE_RED, 
	ENEMY_UFO_GRAY, 
	ENEMY_UFO_RED, 
	ENEMY_SKYSCRAPER
};

// 
// OBJETOS DO APLICATIVO
//

typedef struct Save
{
	int currLevel;
	int numLives;
	int playerState;
	int weaponUpgrade;
	int totalScore;

	int seconds;
	int minutes;
	int hours;
	int days;
	int months;
	int years;
	
	int playingTime;

	std::string savefileTitle;
	char* savefileTitle2;

	int saveFileNumber;

} Save;

struct Background{
	double posX, posY;;
	double speedX, speedY;
	int dirX, dirY;

	int width, height;

	ALLEGRO_BITMAP *image;

};

struct Collectible
{
	double x, y;
	int ID;
	int type;
	bool alive;
	bool collected;
	int width, height;
	int direction;
	double borderX, borderY;
	double speedX, speedY;
	int currFrame;

	ALLEGRO_BITMAP *image;
};

struct Audio
{
	float musicGain, soundGain;
	float musicPan, soundPan;
	bool isMusicOn, isSoundOn;

};

struct Explosion
{
	int ID;
	double x, y;
	double boundx, boundy;
	int numFrames;
	int speed;
	int direction;
	bool alive;
	float red, green, blue, alpha;
	unsigned char r, g, b, a;
	int width, height;
	int explosionType;

	ALLEGRO_BITMAP *image;

};

struct SpaceShip
{
	int ID;
	double x;
	double y;
	double radius;
	double speed;
	int direction;
	int boundX;
	int boundY;
	int invulnerability;
	unsigned int collectibles;
	int score;
	int lives;
	int width, height;

	bool isFiringBullets;
	bool isFiringDoubleShot;
	int firingType;
	int currentFrame;
	int DScurrFrame;
	int waitingFrame;
	int walkingDelta;
	bool isWalking;

	int playerDirection;
	int attackDirection;
	double angle;
	double sine, cosine;
	
	double horizontalSpeed, verticalSpeed;

	int currTileX, currTileY, destTileX, destTileY;
	double currPosX, currPosY, destPosX, destPosY;

	double targetPosX, targetPosY;

	int currWeapon;
	int nextWeapon;
	int quantWeapons;
	int state;

	ALLEGRO_BITMAP *image;
};

struct Bullet
{
	int ID;
	double x;
	double y;
	bool alive;
	double speed;

	double originX;
	double originY;
	double shipX;
	double shipY;
	double angle;

	int bulletDirection;

	int currFrame;
	int coolDown;

	bool isFiringBullets;
	double r;
	int width, height;

	ALLEGRO_BITMAP *image;

	double dx, dy, distance, smoothing;
};

struct Missile
{
	int objID;
	double posX, posY;
	int currLayer;
	int currFrame;
	int objDirection;
	double objAngle;
	double targetX, targetY;
	bool alive;

	ALLEGRO_BITMAP *missileImage;
};

struct Comet
{
	int ID;
	double x;
	double y;
	double speed;
	bool alive;
	double boundX;
	double boundY;
	int lives;

	struct Bullet shots[COMET_NUM_BULLETS];
	int currentFrame;
	int waitingFrame;

	bool isFiringBullets;
	bool hasFiredBullets;

	int bulletFiringCycle;

	ALLEGRO_BITMAP *image;
};

struct Map
{
	int mapfile[MAP_COLUMNS][MAP_ROWS];
	int loadCounterX;
	int loadCounterY;
	char *filename;
	int mapSizeX;
	int mapSizeY;
	int mapID;
	int mapTileID;
	int tileWidth;
	int tileHeight;
	int numColumns;
	int numRows;

	std::vector< std::vector <int> > maplevel;
};

struct Camera
{
	double x, y, scale, angle, fade;
	ALLEGRO_TRANSFORM transform;
};

struct TileMap
{
	int loadCounterX, loadCounterY, mapSizeX, mapSizeY;
	int map[15][15];
	char *filename;
	int blockSize;
	int mapColumns, mapRows, mapSize, tileSize;
	int room[100];
};

struct Weapon
{
	int weaponID;
	int shotBullets;
	double bulletSpeed;
	int maxNumBullets;
	int currNumBullets;
	int bulletLifetime;
	bool isFiringBullets;
	bool isWeaponActivated;
	bool isDamageActivated;
	int effectID;

	ALLEGRO_BITMAP *image;
};

struct Menu
{
	int ID;
	int selected;
	bool on;
	int sound;
	int volume;
	int controller;
	int password;
	int entered;
	int language;
	int input;
	int options;

	int fireProjectile;
	int pauseGame;
	int bombAttack;
	int selectWeapon;
	int chargeWeapon;
	int useWeapon;
	int escapeKey;

};

struct Game
{
	double screenX, screenY;
	int windowWidth, windowHeight;
	int maximumResolutionWidth, maximumResolutionHeight;
	int minimumResolutionWidth, minimumResolutionHeight;
	int currentResolutionWidth, currentResolutionHeight;
	int colorDepth, numberColors;
	int aspectRatio[2];
	int idealResolutionWidth, idealResolutionHeight;
	double scalingRatio;
	double zoomingFactor;
	bool gameStarted, gameLoading;
};

struct Mouse
{
	int shoot;
	int pause;
	int moveUp;
	int moveDown;
	int moveLeft;
	int moveRight;

	int backgroundMusicVolume;
	int soundEffectVolume;

	double posX, posY;
	double axisX, axisY;
	int wheelPos;

};

struct Controls
{
	int shoot;
	int bomb;
	int powerup;
	int moveUp;
	int moveDown;
	int moveLeft;
	int moveRight;
	int pause;
	int confirm;
	int executeSpecialMove;
	int inputDevice;
	int newSetup;
	int oldSetup;

	double backgroundMusicVolume;
	double soundEffectVolume;
	double jingleVolume;
	int gameTune;
	int playerContinues;
	int playerCredits;
	int playerLives;
	double soundPan;
	double playbackSpeed;
};

struct SoundTrack
{
	bool isAudioInstalled;
	int backgroundMusicVolume;
	int soundEffectVolume;
	float playbackSpeed;
	bool isBGMplaying;
	bool isSFXplaying;
	int numberOfAllocatedSamples;
	int numberOfPlayingSamples;
	bool hasBGMplayedOnce;
	bool hasSFXplayedOnce;
	int BGMplayingMode;
	int SFXplayingMode;
	//ALLEGRO_SAMPLE *sample[SOUND_EFFECT_QUANTITY];
	ALLEGRO_SAMPLE_INSTANCE *instance;

};

struct Gameplay{
	int currentFrame, currentFrame2, bossFrame;
	unsigned int *triggerFrame;
	unsigned int *triggerFrame2;
	unsigned int *bossTrigger;
	int eventType;
	int timeCounter;
	int *levelMaxFrame;
	int currentLevel;
};

struct Enemy{
	int ID;
	int type;
	int currFrame;
	int spawnFrame;
	double areaX, areaY;

	int lives;
	int phase;
	int syncFrame;
	double speed;

	double posX, posY;
	double velX, velY;
	
	int direction;
	bool alive;

	ALLEGRO_BITMAP *image;

	int state;
	bool isAttacking;
	double angle;

	double borderX, borderY;
	int width, height;
	int cooldown;
	double offsetX, offsetY;
	double threshold;
	double radius;
};


struct Level
{
	struct Background backgrounds[NUM_BACKGROUNDS];
	struct Background repeated[NUM_BACKGROUNDS];
	struct Background BG, MG, FG;

	ALLEGRO_SAMPLE_INSTANCE *music;
	int levelNumber;
	int nextLevel;
	int levelTimer;
	int error;

	int enemyTypes;

	//ALLEGRO_BITMAP *e[3];
};

struct Boss
{
	int ID;
	double x, y, speed, velX, velY;
	double borderX, borderY;

	double radius, angle;
	int spriteDir, attackDir;
	int currFrame, waitFrame, currFrame2, currFrame3;
	ALLEGRO_BITMAP *image;

	int currState, transPhase, numTrans;
	int numLives;
	bool isAlive, isInvulnerable, gotHit;
	int hitFrames;
	int imageWidth, imageHeight;

	ALLEGRO_SAMPLE *shoot, *move, *die, *hurt;
	ALLEGRO_BITMAP *shooting, *moving, *dying, *hurting;
};

struct Action
{
	int hotKey[NUM_ACTIONS];
	bool isPressed[NUM_ACTIONS];
	int actionDone[NUM_ACTIONS];
};

//
// VARIÁVEIS GLOBAIS
//

//struct Action input;
ALLEGRO_MONITOR_INFO monitorInfo;
int screenWidth, screenHeight;

ALLEGRO_DISPLAY *display;
bool result;
bool successfulShutdown;
bool frozen;

ALLEGRO_EVENT ev;
ALLEGRO_EVENT_QUEUE *eq;
ALLEGRO_EVENT_SOURCE *keyboardEventSource;
ALLEGRO_EVENT_SOURCE *mouseEventSource;
ALLEGRO_EVENT_SOURCE *displayEventSource;
ALLEGRO_EVENT_SOURCE *timerEventSource;
ALLEGRO_EVENT_SOURCE *joystick1EventSource;
ALLEGRO_EVENT_SOURCE *joystick2EventSource;
ALLEGRO_TIMER *timer;
ALLEGRO_JOYSTICK *joystick1;
ALLEGRO_JOYSTICK *joystick2;

bool isGameLoopDone;
bool isTimeToDraw;
bool isTimeToRedraw;
int currFrame;
int maximumNumberOfFrames;
int mapLoad;

int state;
double currFPS;

int bitmapSize;
int startX, startY;
bool keys[PLAYER_NUM_KEYS];
bool weapons[PLAYER_NUM_WEAPONS];
bool mouse[MOUSE_BUTTONS], isSongPlaying;

int generatedNumber, generatedNumber2;
int generated, generated2;

ALLEGRO_FONT *font18;
ALLEGRO_FONT *fontSelected;
ALLEGRO_COLOR color_white;
ALLEGRO_COLOR color_red;
ALLEGRO_COLOR color_blue;
ALLEGRO_COLOR color_green;
ALLEGRO_COLOR color_transparent;
ALLEGRO_COLOR color_black;
ALLEGRO_COLOR color_pink;
ALLEGRO_COLOR color_magenta;
ALLEGRO_COLOR color_grey;
ALLEGRO_FONT *fontTitle;
ALLEGRO_FONT *fontMenu;

double cameraPosition[2];
ALLEGRO_TRANSFORM camera;
double rotation;
double scale;
int offsetX, offsetY;
ALLEGRO_TRANSFORM rotTransf;
ALLEGRO_BITMAP *tileset;
ALLEGRO_BITMAP *image;
double mousePosX, mousePosY;
int mouseWheel, mouseButton, mouseWheelW, mouseWheelZ;

unsigned int songPosition;
unsigned int songLength;
float songSpeed;
float songTime;
ALLEGRO_SAMPLE *sample, *sample2, *bossSample, *titleSample, *endingSample;
ALLEGRO_SAMPLE_INSTANCE *stage1, *stage2, *bossInstance, *titleInstance, *endingInstance;
ALLEGRO_SAMPLE *bongos;
ALLEGRO_SAMPLE_INSTANCE *bongosTrack;
unsigned int bongosLength;
ALLEGRO_VOICE *voice;
ALLEGRO_MIXER *mixerBGM, *mixerSFX, *mixerSpeech, *mixerModule, *masterMixer, *mixerStream;
unsigned int problems;
bool success;
struct Controls PC;
char mapped[KEY_NAME];
//int source;
struct Mouse gameMouse;
double distX, distY, distance, easingAmount;
int nextWeapon, quantWeapons;
bool levels[NUM_LEVELS];
bool buttons[NUM_BUTTONS];
struct Level stage;
struct Enemy e[NUM_ENEMIES];
bool showCollision;
//bool gameLevel[NUM_LEVELS];
int endingFrames;

int fadingType;
unsigned char red, green, blue, alpha;

ALLEGRO_BITMAP *fader;
float fade;
int fading;
bool isFading;

ALLEGRO_SAMPLE *shot;
ALLEGRO_SAMPLE *coin;
ALLEGRO_SAMPLE *heart;
ALLEGRO_SAMPLE *shield;
ALLEGRO_SAMPLE *hurt;
ALLEGRO_SAMPLE *death;
ALLEGRO_SAMPLE *defend;
ALLEGRO_BITMAP *boom;
double threshold;
float angle;

ALLEGRO_SAMPLE *enemyShot[NUM_ENEMIES];
ALLEGRO_SAMPLE *explode[NUM_ENEMIES];
ALLEGRO_SAMPLE *explosion[NUM_EXPLOSIONS];
ALLEGRO_BITMAP *titleImage;
ALLEGRO_BITMAP *lost;
ALLEGRO_SAMPLE *lostSample;
ALLEGRO_SAMPLE_INSTANCE *lostSong;
ALLEGRO_SAMPLE *menuSelect, *menuCancel, *menuConfigure, *menuChange, *menuOK, *pauseSample;

ALLEGRO_BITMAP *level02_bgImage;
ALLEGRO_BITMAP *level02_bgImage2;
struct Background level02_bkg;
struct Background level02_bkg2;
struct Background level02_bkg_loop;
struct Background level02_bkg2_loop;
int enemyType;
struct Enemy copter[NUM_COPTERS];
struct Bullet projs[NUM_COPTERS][COPTER_NUM_BULLETS];
struct Bullet pr[NUM_COPTERS][COPTER_NUM_BULLETS];

ALLEGRO_BITMAP *helix[NUM_COPTERS];

ALLEGRO_BITMAP *titleStart, *titleLoad, *titleSetup, *titleInput, *titleQuit, *titleButtons, *menuFont, *menuTitles, *titleLogo;
double BGMVolume, SFXVolume;
int soundType, musicType;
int currFrame2;

ALLEGRO_SAMPLE_ID *configureSampleId;
Save save;

//
// OBJETOS E VARIÁVEIS DA BIBLIOTECA SFML
//

//sf::Music music;
//sf::Music music2;
float volume;
//sf::Time audioTime;
//sf::Time current;
//sf::Clock gameClock;

//
// STRINGS DOS MENUS DO JOGO
//

static const char* titleMenuItems[]
{
	"NEW GAME START",
	"SAVED GAME",
	"CONTROLS",
	"OPTIONS",
	"PASSWORD",
	"QUIT"
};

static const char* setupMenuItems[]
{
	"PLAYER 1 CONTROLS", 
	"PLAYER 2 CONTROLS", 
	"PASSWORD", 
	"BACKGROUND MUSIC VOLUME",
	"SOUND EFFECT VOLUME",
	"SOUNDTRACK TEST",
	"SOUND PAN",
	"LIVES", 
	"SET DEFAULT VALUES", 
	"CREDITS", 
	"<- RETURN TO THE TITLE SCREEN", 
	"INPUT DEVICE"
};

static const char* playerControls[]
{
	"FIRE BULLET ", 
	"SCREEN BOMB ", 
	"USE POWER-UP ", 
	"MOVE UP ", 
	"MOVE DOWN ", 
	"MOVE LEFT ",
	"MOVE RIGHT ",
	"CONFIRM / ACCEPT ", 
	"PAUSE / CANCEL ",
	"SET DEFAULT VALUES", 
	"RETURN TO THE TITLE SCREEN", 
	"INPUT DEVICE = "
};

static const char* mouseControls[]
{
	"SET DEFAULT CONFIGURATIONS", 
	"<- RETURN TO THE TITLE SCREEN", 
	"SHOOT / CONFIRM",
	"PAUSE / CANCEL", 
	"MOVE CHARACTER UP", 
	"MOVE CHARACTER DOWN",
	"MOVE CHARACTER LEFT", 
	"MOVE CHARACTER RIGHT"
};

static const char* passwordMenu[]
{
	"DELETE", 
	"ERASE ALL", 
	"CONFIRM", 
	"<- RETURN TO THE TITLE SCREEN"
};

static const char* characterSelectMenu[]
{
	"SELECT YOUR CHARACTER", 
	"<- RETURN TO THE PREVIOUS SCREEN", 
	"LOAD GAME", 
	"ERASE GAME DATA", 
	"COPY AND PASTE DATA", 
	"CUT GAME DATA",
	"GAME LANGUAGE", 
	"SKILLS: ",
	"<- RETURN TO THE PREVIOUS MENU"
};

static const char* optionsMenu[]
{
	"ON", "OFF"
};


//
// OBJETOS DOS PERSONAGENS
//

struct SpaceShip ship;
struct Bullet bullets[PLAYER_NUM_BULLETS]; // EAST
struct Bullet bulletsWest[2]; 
struct Bullet bulletsNorth[2];
struct Bullet bulletsSouth[2];
struct Bullet bulletsNE[2];	// NORTHEAST
struct Bullet bulletsSE[2];	// SOUTHEAST
struct Bullet bulletsSW[2];	// SOUTHWEST
struct Bullet bulletsNW[2];	// NORTHWEST
struct Bullet b[PLAYER_NUM_WEAPONS][PLAYER_NUM_WEAPONS];
struct Comet comets[MAX_NUM_COMETS];
struct Map level;
struct TileMap ptrMap;
//struct TileMap ptr;
//struct Map map;
struct TileMap room;
struct Menu menu;
struct Gameplay gameplay;
struct Collectible collect[NUM_COLLECTIBLES];
struct Bullet ct[ENEMY_NUM_BULLETS][NUM_ENEMIES];
struct Collectible powerup[NUM_POWERUPS];
struct Collectible shields[NUM_SHIELDS];
struct Enemy boss[NUM_BOSSES];
struct Boss badGuy[NUM_BOSSES];
struct Bullet proj[BOSS_NUM_BULLETS];
struct Explosion explosions[NUM_EXPLOSIONS];
struct Bullet projectiles[BOSS_NUM_BULLETS];
//struct Audio soundtrack;
//struct Enemy skyscraper[NUM_SKYSCRAPERS];

//
// INSTÂNCIAS DE CLASSE
//



//
// PROTÓTIPOS DE FUNÇÕES DO MAIN
//

int systemReturn, gameReturn;

void initializeModules();
void deinitializeModules();

void initializeGameSystem();
void deinitializeGameSystem();

int changeGameState(int *state, int newState);

void createDisplay();
void destroyDisplay();
void setDisplayOptions();
void createEventQueue();
void destroyEventQueue();
void getKeyboardEventSource();
void getMouseEventSource();
void getJoystick1EventSource();
void getJoystick2EventSource();
void getDisplayEventSource();
void createTimer();
void destroyTimer();
void startTimer();
void stopTimer();
void registerKeyboardEventSource();
void unregisterKeyboardEventSource();
void registerMouseEventSource();
void unregisterMouseEventSource();
void registerDisplayEventSource();
void unregisterDisplayEventSource();
void registerJoystick1EventSource();
void unregisterJoystick1EventSource();
void registerJoystick2EventSource();
void unregisterJoystick2EventSource();
void getTimerEventSource();
void registerTimerEventSource();
void unregisterTimerEventSource();

void createGameResources();
void destroyGameResources();

void setFrameRate();

void GameLoop();
void GameDraw();
void GameUpdate();
void GameRedraw();

void getNextEvent();
void waitForEvent();
void ifEventIsTimer();
void ifEventIsKeyDown();
void ifEventIsKeyUp();
void ifEventIsJoystickAxes();
void ifEventIsJoystickButtonDown();
void ifEventIsJoystickButtonUp();
void ifEventIsMouseButtonDown();
void ifEventIsMouseButtonUp();
void ifEventIsMouseAxes();
void ifEventIsDisplayClose();
void ifEventIsMouseEnterDisplay();
void ifEventIsMouseLeaveDisplay();
void ifEventIsDisplayLoseFocus();
void ifEventIsDisplayGainFocus();
void ifEventIsDisplayResize();
void ifEventIsMouseWheelNorth();
void ifEventIsMouseWheelSouth();
void ifEventIsMouseWheelPressed();
void ifEventIsMouseWheelReleased();

void InitializeGameObjects();
void DestroyGameObjects();

void InitShip();
void DrawShip();
void UpdateShip();
void MoveShipUp();
void MoveShipDown();
void MoveShipLeft();
void MoveShipRight();
void MoveShipUpLeft();
void MoveShipDownLeft();
void MoveShipUpRight();
void MoveShipDownRight();
void CenterCharacterPosition(int ID, double x, double y, int width, int height);
void MoveShipWithMouse();

void InitBullet();
void DrawBullet();
void UpdateBullet();
void FireBullet();
void CollideBullet();

void InitBullet2();
void DrawBullet2();
void UpdateBullet2();
void FireBullet2();
void CollideBullet2();

void InitHUD();
void DrawHUD();
void UpdateHUD();

void InitComet();
void DrawComet();
void StartComet();
void UpdateComet();
void SpawnComet();
void CollideComet();

void Comet_InitBullet();
void Comet_DrawBullet();
void Comet_UpdateBullet();
void Comet_FireBullet();
void Comet_CollideBullet();

void randomizeNumberOfComets();
void randomizeCometPosition();

double AngleToTarget(double x1, double y1, double x2, double y2);
double CheckDistance(double x1, double y1, double x2, double y2);

void CameraUpdate(int width, int height);

void ZoomIn();
void ZoomOut();
void ResetZoomingScale();

void LoadMap();
void DrawMap();
void InitMap();
void UpdateMap();

void InitMap2();
void LoadMap2();
void DrawMap2();
void UpdateMap2();

void LoadMapFromTextFile();

void LoadMapFromMemory();

bool LoadTileMap_Easy(const char *filename);
void DrawTileMap_Easy();

void LoadTileMap_Advanced(const char*filename, std::vector< std::vector<int> > &map);
void DrawTileMap_Advanced();

bool LoadMatrix();
bool DrawMatrix();
bool UpdateMatrix();

void RotateShip(int rotDir, double rotDeg);

//int ChangeWeapon(int currWeapon, int keyPress, int buttonPress, int mouseButton, int selectedWeapon);
int GetItem(int itemID, int charID);
int GetPowerUp(int itemID, int charID);
int GetPowerDown(int itemID, int charID);

void SetStartingWeapon();
void ChangeState(int newState);
void PreProcessingTheState();
void PostProcessingTheState();
void CurrentState();
void ChangeCharacterState(int newCharacterState);

void TitleScreen();
void OptionsScreen();
void PasswordScreen();
void CreditsScreen();
void SoundTestScreen();
void PlayerSelectionScreen();
void ChapterScreen();
void GameOverScreen();
void VictoryScreen();
void LoseScreen();
void ControllerScreen();
void LevelSelectScreen();
void LoadGameScreen();
void SaveGameScreen();
void PauseScreen();
void QuitToTitleScreen();
void QuitToOperatingSystem();

void InitCheckpoint();
void DrawCheckpoint();
void UpdateCheckpoint();
void GetCheckpoint();

void SetupControls();
void ChangeControls();
void SetupAudio();
void ChangeAudio();
char* InputMapping(int source);
char* DeviceMapping(int device);
void setupMouse();

void InitWeapon();
void DrawWeapon();
void UpdateWeapon();
void ChangeWeapon();
void UpgradeWeapon();
void DowngradeWeapon();

void InitBDoubleShot();
void DrawBDoubleShot();
void FireBDoubleShot();
void UpdateBDoubleShot();

double fromDegreesToRadians(double degrees);
double fromRadiansToDegrees(double radians);

void CollideProjectile(int obj1, int obj2);

void InitLevel();
void DrawLevel();
void StartLevel();
void UpdateLevel();

void LoadAssets();
void DestroyAssets();


void InitBackground(double x, double y, double vx, double vy, int width, int height, int dx, int dy, ALLEGRO_BITMAP *image);
void DrawBackground();
void UpdateBackground();
void InitParallaxScrolling();

void InitEnemy();
void DrawEnemy();
void StartEnemy(double y, int enemyType, int enemyDirection);
void StopEnemy();
void UpdateEnemy();
void CollideEnemy(int obj1, int obj2, int obj1num, int obj2num);
void ChangeEnemy();

int randomizeEnemyType();
double randomizeEnemyPosition();
int SpawnEnemy();
void SpawnBaddie();

void InitCollectible();
void DrawCollectible();
void SpawnCollectible(int dir, double newPos, int type);
void UpdateCollectible();
void GetCollectible();

double randomizeCollectiblePosition(int dir);
void randomizeNumberOfCollectibles();

void ShowCollision();

void AudioSetup();
void AudioFinalization();

void PreparationScreen();

void FadingTransition();

void InitFading();
void DrawFading();
void UpdateFading();

void InitAudio();
void PlayAudio();
void StopAudio();
void UpdateAudio();

void InitChemicalTrails();
void DrawChemicalTrails();
void ShootChemicalTrails(int j, int bullet);
void FireCT(int enemy, int bullet);
void UpdateChemicalTrails();

void InitBoss(int level);
void DrawBoss(int level, int phase);
void StartBoss(int level);
void UpdateBoss(int level, int phase);

void InitShot(int level);
void DrawShot(int level);
void FireShot(int level);
void UpdateShot(int level);
void RechargeShot(int level, int phase);

void InitExplosion();
void DrawExplosion();
void StartExplosion(double x, double y, double speed);
void UpdateExplosion();

void InitSprite();
void DrawSprite();
void UpdateSprite();

void InitProjectile(int enemy);
void DrawProjectile(int enemy);
void FireProjectile(int enemy);
void UpdateProjectile(int enemy);

void EventKeyboardKeyDown(int value);
void EventKeyboardKeyUp(int value);
void EventJoystickButtonDown(int value);
void EventJoystickButtonUp(int value);
void EventMouseButtonDown(int value);
void EventMouseButtonUp(int value);

int MapInput(int inputDevice, int oldValue, int newValue);

void SetDefaultValues();

void MenuSelectCommand();
void MenuChangeCommand();
void MenuConfirmCommand();
void MenuConfigureCommand();
void MenuCancelCommand();
void MenuPauseCommand();
void MenuUnpauseCommand();
void MenuEscapeCommand();

void FadingIncrease();
void FadingDecrease();

void StopAllSamples();

void DrawFontNumber(double number, double x, double y, double scaleX, double scaleY, double sizeX, double sizeY);
void InitEverything();
void QuitEverything();
void QuitGameplay();

void HandleBinaryFile();
void EndingScreen(int endingType);