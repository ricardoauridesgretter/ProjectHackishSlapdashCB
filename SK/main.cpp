#include "main.h"
//#include "algif.h"
//#include "mappy_A5.h"

/*

ESSE APLICATIVO FOI DESENVOLVIDO POR "RICARDO AURIDES GRETTER", DE 2016 À 2017.
PROJETADO E PROGRAMADO POR "RICARDO AURIDES GRETTER".
(C) COPYRIGHT 2016-2017 RICARDO AURIDES GRETTER - TODOS OS DIREITOS RESERVADOS.
ESSE APLICATIVO USA AS LINGUAGEM DE PROGRAMAÇÃO "C" E O FRAMEWORK DE JOGOS "ALLEGRO 5".

THIS APPLICATION WAS DEVELOPED BY "RICARDO AURIDES GRETTER", FROM 2016 TO 2017.
DESIGNED AND PROGRAMMED BY "RICARDO AURIDES GRETTER".
(C) COPYRIGHT 2016-2017 RICARDO AURIDES GRETTER - ALL RIGHTS RESERVED.
THIS APPLICATION USES THE "C" PROGRAMMING LANGUAGE AND THE "ALLEGRO 5" GAME FRAMEWORK.

*/

int main(int argc, char **argv)
{
	//std::cout << "Hello world!" << std::endl;	

	systemReturn = -1;
	endingFrames = 0;

	initializeModules();
	initializeGameSystem();

	al_hide_mouse_cursor(display);

	startTimer();
	GameLoop();
	stopTimer();

	al_show_mouse_cursor(display);

	

	systemReturn = AL_INIT_GAME_SYSTEM;
	gameReturn = GAME_SYSTEM_INITIALIZED;

	deinitializeGameSystem();
	deinitializeModules();

	//std::cout << "PASSOU!" << std::endl;

	//getchar();

	return 0;
}

void initializeModules()
{
	if (al_init())
	{
		// se o sistema Allegro foi inicializado
		if (al_init_primitives_addon())
		{
			// se o módulo das formas primitivas foi inicializado
			if (al_init_image_addon())
			{
				al_init_font_addon();

				if (al_init_ttf_addon())
				{
					if (al_install_audio())
					{
						if (al_init_acodec_addon())
						{
							if (al_install_keyboard())
							{
								if (al_install_mouse())
								{
									if (al_install_joystick())
									{
										if (al_init_native_dialog_addon())
										{

											//std::cout << "Sistema do jogo!" << std::endl;
											systemReturn = AL_INIT_GAME_SYSTEM;
											return;
										}
										else
										{
											systemReturn = AL_INIT_DIALOG_ADDON_FAIL;
										}
										
									}
									else
									{
										systemReturn = AL_INSTALL_JOYSTICK_ADDON_FAIL;
									}
								}
								else
								{
									systemReturn = AL_INSTALL_MOUSE_ADDON_FAIL;
								}
							}
							else
							{
								systemReturn = AL_INSTALL_KEYBOARD_ADDON_FAIL;
							}
						}
						else
						{
							systemReturn = AL_INIT_ACODEC_ADDON_FAIL;
						}
					}
					else
					{
						systemReturn = AL_INSTALL_AUDIO_FAIL;
					}
				}
				else
				{
					systemReturn = AL_INIT_TTF_ADDON_FAIL;
				}
			}
			else
			{
				systemReturn = AL_INIT_IMAGE_ADDON_FAIL;
			}
		}
		else
		{
			// se o módulo não foi inicializado
			systemReturn = AL_INIT_PRIMITIVES_ADDON_FAIL;
		}
	}
	else
	{
		// se o sistema Allegro não foi inicializado
		systemReturn = AL_INIT_FAIL;
	}

}

void deinitializeModules()
{

	 if (systemReturn == AL_INIT_DIALOG_ADDON_FAIL)
	{
		al_uninstall_joystick();

		systemReturn = AL_INSTALL_JOYSTICK_ADDON_FAIL;

		deinitializeModules();
		
	}
	else if (systemReturn == AL_INSTALL_JOYSTICK_ADDON_FAIL)
	{
		al_uninstall_mouse();

		systemReturn = AL_INSTALL_MOUSE_ADDON_FAIL;

		deinitializeModules();
	}
	else if (systemReturn == AL_INSTALL_MOUSE_ADDON_FAIL)
	{
		al_uninstall_keyboard();

		systemReturn = AL_INSTALL_KEYBOARD_ADDON_FAIL;

		deinitializeModules();
	}
	else if (systemReturn == AL_INSTALL_KEYBOARD_ADDON_FAIL)
	{
		al_uninstall_audio();

		systemReturn = AL_INSTALL_AUDIO_FAIL;

		deinitializeModules();
	}
	else if (systemReturn == AL_INSTALL_AUDIO_FAIL)
	{
		al_shutdown_ttf_addon();
		systemReturn = AL_INIT_TTF_ADDON_FAIL;
		deinitializeModules();
	}
	else if (systemReturn == AL_INIT_TTF_ADDON_FAIL)
	{
		al_shutdown_font_addon();
		systemReturn = AL_INIT_FONT_ADDON_FAIL;
		deinitializeModules();
	}
	else if (systemReturn == AL_INIT_FONT_ADDON_FAIL)
	{
		al_shutdown_image_addon();
		systemReturn = AL_INIT_IMAGE_ADDON_FAIL;
		deinitializeModules();
	}
	else if (systemReturn == AL_INIT_IMAGE_ADDON_FAIL)
	{
		al_shutdown_primitives_addon();
		systemReturn = AL_INIT_PRIMITIVES_ADDON_FAIL;
		deinitializeModules();
	}
	else if (systemReturn == AL_INIT_PRIMITIVES_ADDON_FAIL)
	{
		//al_uninstall_system();
		systemReturn = AL_INIT_FAIL;
		deinitializeModules();
	}
	else if (systemReturn == AL_INIT_FAIL || systemReturn <= -1)
	{
		//std::cout << "Todos os modulos foram desalocados com sucesso!" << std::endl;
		
	}
	else if (systemReturn == AL_INIT_GAME_SYSTEM)
	{
		al_shutdown_native_dialog_addon();
		systemReturn = AL_INIT_DIALOG_ADDON_FAIL;
		deinitializeModules();
	}
}

void initializeGameSystem()
{
	// inicializar variáveis do sistema Allegro, janela, display, joysticks, mouse, etc...
	createDisplay();

	if (result)
	{
		setDisplayOptions();
		createEventQueue();
		if (result)
		{
			getKeyboardEventSource();
			if (result)
			{
				getMouseEventSource();
				if (result)
				{
					getJoystick1EventSource();
					if (result)
					{
						getJoystick2EventSource();
						if (result)
						{
							getDisplayEventSource();
							if (result)
							{
								createTimer();
								if (result)
								{
									registerKeyboardEventSource();
									registerMouseEventSource();
									registerDisplayEventSource();
									registerJoystick1EventSource();
									registerJoystick2EventSource();
									getTimerEventSource();
									if (result)
									{
										registerTimerEventSource();
										//getchar();

										gameReturn = GAME_SYSTEM_INITIALIZED;

										return;
									}
									else
									{
										gameReturn = CANNOT_GET_TIMER_EVENT_SOURCE;
									}
								}
								else
								{
									gameReturn = CANNOT_CREATE_TIMER;
								}
							}
							else
							{
								gameReturn = CANNOT_GET_DISPLAY_EVENT_SOURCE;
							}
						}
						else
						{
							gameReturn = CANNOT_GET_JOYSTICK2_EVENT_SOURCE;
						}
					}
					else
					{
						gameReturn = CANNOT_GET_JOYSTICK1_EVENT_SOURCE;
					}
				}
				else
				{
					gameReturn = CANNOT_GET_MOUSE_EVENT_SOURCE;
				}
			}
			else
			{
				gameReturn = CANNOT_GET_KEYBOARD_EVENT_SOURCE;
			}
		}
		else
		{
			gameReturn = CANNOT_CREATE_EVENT_QUEUE;
		}
	}
	else
	{
		gameReturn = CANNOT_CREATE_DISPLAY;
	}
}

void deinitializeGameSystem()
{

	switch (gameReturn)
	{

	case GAME_SYSTEM_INITIALIZED:
		unregisterTimerEventSource();
		gameReturn = CANNOT_GET_TIMER_EVENT_SOURCE;
		deinitializeGameSystem();
		break;

	case CANNOT_GET_TIMER_EVENT_SOURCE:
		unregisterJoystick2EventSource();
		unregisterJoystick1EventSource();
		unregisterMouseEventSource();
		unregisterKeyboardEventSource();
		unregisterDisplayEventSource();
		destroyTimer();
		gameReturn = CANNOT_CREATE_TIMER;
		deinitializeGameSystem();
		break;

	case CANNOT_CREATE_TIMER:
		gameReturn = CANNOT_GET_DISPLAY_EVENT_SOURCE;
		deinitializeGameSystem();
		break;

	case CANNOT_GET_DISPLAY_EVENT_SOURCE:
		gameReturn = CANNOT_GET_JOYSTICK2_EVENT_SOURCE;
		deinitializeGameSystem();
		break;

	case CANNOT_GET_JOYSTICK2_EVENT_SOURCE:
		gameReturn = CANNOT_GET_JOYSTICK1_EVENT_SOURCE;
		deinitializeGameSystem();
		break;

	case CANNOT_GET_JOYSTICK1_EVENT_SOURCE:
		gameReturn = CANNOT_GET_MOUSE_EVENT_SOURCE;
		deinitializeGameSystem();
		break;

	case CANNOT_GET_MOUSE_EVENT_SOURCE:
		gameReturn = CANNOT_GET_KEYBOARD_EVENT_SOURCE;
		deinitializeGameSystem();
		break;

	case CANNOT_GET_KEYBOARD_EVENT_SOURCE:
		destroyEventQueue();
		gameReturn = CANNOT_CREATE_EVENT_QUEUE;
		deinitializeGameSystem();
		break;

	case CANNOT_CREATE_EVENT_QUEUE:
		destroyDisplay();
		gameReturn = CANNOT_CREATE_DISPLAY;
		deinitializeGameSystem();
		break;

	case CANNOT_CREATE_DISPLAY:
		gameReturn = GAME_SYSTEM_FINALIZED;
		deinitializeGameSystem();
		break;

	case GAME_SYSTEM_FINALIZED:
		gameReturn = -1;
		deinitializeGameSystem();
		break;

	default:
		break;
	}
}

void createDisplay()
{
	al_get_monitor_info(0, &monitorInfo);
	screenWidth = monitorInfo.x2 - monitorInfo.x1;
	screenHeight = monitorInfo.y2 - monitorInfo.y1;
	display = NULL;

	result = ((display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT)) != NULL) ? true : false;
}

void destroyDisplay()
{
	al_destroy_display(display);	display = NULL;	successfulShutdown = true;
}

void setDisplayOptions()
{
	startX = START_X_POS;
	startY = START_Y_POS;

	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_REQUIRE);
	al_set_window_position(display, startX, startY);
	bitmapSize = al_get_display_option(display, ALLEGRO_MAX_BITMAP_SIZE);
}

void createEventQueue()
{
	result = ((eq = al_create_event_queue()) != NULL) ? true : false;
}

void destroyEventQueue()
{
	al_destroy_event_queue(eq);	eq = NULL;	successfulShutdown = true;
}

void setFrameRate()
{
	currFPS = 1.00 / FRAME_RATE;
}

void createTimer()
{
	setFrameRate();

	timer = al_create_timer(currFPS);

	if (timer == NULL)
	{
		result = false;
	}
	else
	{
		result = true;
	}
}

void destroyTimer()
{
	al_destroy_timer(timer);	timer = NULL;	successfulShutdown = true;
}

void startTimer()
{
	al_start_timer(timer);
}

void stopTimer()
{
	al_stop_timer(timer);	successfulShutdown = true;
}

void getKeyboardEventSource()
{
	result = ((keyboardEventSource = al_get_keyboard_event_source()) != NULL) ? true : false;
}

void getMouseEventSource()
{
	result = ((mouseEventSource = al_get_mouse_event_source()) != NULL) ? true : false;
}

void getJoystick1EventSource()
{
	result = ((joystick1EventSource = al_get_joystick_event_source()) != NULL) ? true : false;
}

void getJoystick2EventSource()
{
	result = ((joystick2EventSource = al_get_joystick_event_source()) != NULL) ? true : false;
}

void getDisplayEventSource()
{
	result = ((displayEventSource = al_get_display_event_source(display)) != NULL) ? true : false;
}

void getTimerEventSource()
{
	result = ((timerEventSource = al_get_timer_event_source(timer)) != NULL) ? true : false;
}

void registerKeyboardEventSource()	{ al_register_event_source(eq, keyboardEventSource); }
void registerMouseEventSource() { al_register_event_source(eq, mouseEventSource); }
void registerJoystick1EventSource() { al_register_event_source(eq, joystick1EventSource); }
void registerJoystick2EventSource() { al_register_event_source(eq, joystick2EventSource); }
void registerDisplayEventSource() { al_register_event_source(eq, displayEventSource); }
void registerTimerEventSource() { al_register_event_source(eq, timerEventSource); }

void unregisterKeyboardEventSource()	{ al_unregister_event_source(eq, keyboardEventSource); }
void unregisterMouseEventSource()	{ al_unregister_event_source(eq, mouseEventSource); }
void unregisterDisplayEventSource()	{ al_unregister_event_source(eq, displayEventSource); }
void unregisterTimerEventSource()	{ al_unregister_event_source(eq, timerEventSource); }
void unregisterJoystick1EventSource()	{ al_unregister_event_source(eq, joystick1EventSource); }
void unregisterJoystick2EventSource()	{ al_unregister_event_source(eq, joystick2EventSource); }

void createGameResources()
{

}

void destroyGameResources()
{

}

void GameLoop()
{
	state = -1;
	
	AudioSetup();

	InitializeGameObjects();

	ChangeState(TITLE);

	char mapped = NULL;
	int source = ALLEGRO_KEY_QUOTE;

	InputMapping(source);
		
	while (!isGameLoopDone)
	{
		waitForEvent();
		getNextEvent();
		GameDraw();
	}

	//delete &p;
	DestroyAssets();
	AudioFinalization();
	DestroyGameObjects();
}

void InitializeGameObjects()
{
	srand((unsigned)time(NULL));

	mapLoad = -1;
	frozen = false;

	isSongPlaying = false;
	isGameLoopDone = false;
	ship.quantWeapons = PLAYER_NUM_WEAPONS;
	ship.nextWeapon = 0;
	showCollision = false;
	currFrame = 0;

	InitShip();
	InitBullet();
	InitComet();
	Comet_InitBullet();
	InitBoss(-1);
	InitShot(-1);
	InitExplosion();
	InitProjectile(-1);
	
	//InitBDoubleShot();

	menu.selected = 0;
	menu.options = 6;

	ship.state = PLAYER_VULNERABLE;

	//InitShip();
	//InitBullet();
	//InitComet();
	//Comet_InitBullet();

	font18 = fontSelected = fontTitle = fontMenu = NULL;

	//font18 = al_load_font("assets/PTS55F.ttf", FONT_SIZE_MENU, 0);
	font18 = al_load_font("assets/Roboto-Regular.ttf", FONT_SIZE_MENU, 0);

	fontSelected = al_load_font("assets/Roboto-Regular.ttf", FONT_SIZE_MENU, 0);
	fontTitle = al_load_font("assets/PTS75F.ttf", FONT_SIZE_MENU * 2, 0);
	fontMenu = al_load_font("assets/PTS75F.ttf", FONT_SIZE_MENU * 2, 0);

	color_white = al_map_rgb(255, 255, 255);
	color_red = al_map_rgb(255, 0, 0);
	color_black = al_map_rgb(0, 0, 0);
	color_blue = al_map_rgb(0, 0, 255);
	color_green = al_map_rgb(0, 255, 0);
	color_transparent = al_map_rgb(255, 0, 255);
	color_grey = al_map_rgb(20, 20, 20);
	color_magenta = al_map_rgb(255, 1, 255);

	//al_set_app_name("ILLUMINATI GAME");

	SetupControls();

	rotation = 0.00f;
	scale = +1.0f;
	offsetX = offsetY = 0;
	
	//LoadTileMapHard("assets/map.txt");
	//LoadMap2();

	//LoadMapFromTextFile();

	bool result = LoadMatrix();
	//LoadTileMap_Easy("easyMap.txt");

	//getchar();
	stage.nextLevel = NEXT_LEVEL;
	stage.levelNumber = CURRENT_LEVEL;
	gameplay.currentLevel = stage.levelNumber;

	titleImage = al_load_bitmap(TITLE_BITMAP);

	//titleSample = al_load_sample(TITLE_SAMPLE);

	//titleSong = al_create_sample_instance(titleSample);

	// CARREGAR IMAGENS E SONS DAS FASES DO JOGO

	stage.backgrounds[0].image = al_load_bitmap(LEVEL01_BACKGROUND_IMAGE);
	stage.backgrounds[1].image = al_load_bitmap(LEVEL01_MIDDLEGROUND_IMAGE);
	//stage.backgrounds[0].image = al_load_bitmap("assets/chemtrails/chemtrails_bkg.png");

	titleButtons = al_load_bitmap(TITLE_SCREEN_BUTTONS);
	al_convert_mask_to_alpha(titleButtons, al_map_rgb(255, 0, 255));

	menuFont = al_load_bitmap(MENU_FONTS);
	al_convert_mask_to_alpha(menuFont, al_map_rgb(255, 0, 255));

	menuTitles = al_load_bitmap(MENU_TITLES);
	al_convert_mask_to_alpha(menuTitles, al_map_rgb(255, 0, 255));

	pauseSample = al_load_sample(PAUSE_SAMPLE);

	titleLogo = al_load_bitmap(TITLE_SCREEN_LOGO);
	al_convert_mask_to_alpha(titleLogo, al_map_rgb(255, 0, 255));

	lost = al_load_bitmap(LOST_BITMAP);
	al_convert_mask_to_alpha(lost, al_map_rgb(255, 0, 255));

	//
	// CARREGAR SONS E MÚSICAS DO JOGO (TITLE, LOST, VICTORY, ENDING, OPTIONS, ETC...)
	//

	lostSample = NULL;	lostSong = NULL;

	lostSample = al_load_sample(LOST_SONG);
	if (lostSample != NULL){
		lostSong = al_create_sample_instance(lostSample);

		if (lostSong != NULL){
			bool result = al_attach_sample_instance_to_mixer(lostSong, al_get_default_mixer());

			if (result == true){
				al_set_sample_instance_playmode(lostSong, ALLEGRO_PLAYMODE_ONCE);
				al_set_sample_instance_speed(lostSong, PC.playbackSpeed);
				al_set_sample_instance_gain(lostSong, PC.backgroundMusicVolume);
				al_set_sample_instance_pan(lostSong, PC.soundPan);
			}
		}
	}

	InitParallaxScrolling();

	InitEnemy();
	InitCollectible();
	//InitAudio();
	InitChemicalTrails();
	AudioSetup();
	InitFading();
}

void DestroyGameObjects()
{
	if (titleInstance != NULL)	al_stop_sample_instance(titleInstance);
	if (endingInstance != NULL)	al_stop_sample_instance(endingInstance);
	if (bossInstance != NULL)	al_stop_sample_instance(bossInstance);
	if (stage1 != NULL)	al_stop_sample_instance(stage1);
	if (stage2 != NULL)	al_stop_sample_instance(stage2);

	if (font18 != nullptr)	al_destroy_font(font18);
	if (fontSelected != nullptr)	al_destroy_font(fontSelected);
	if (fontTitle != nullptr)	al_destroy_font(fontTitle);
	if (fontMenu != nullptr)	al_destroy_font(fontMenu);

	if (fader != nullptr)
		al_destroy_bitmap(fader);

	if (ship.image != nullptr)
		al_destroy_bitmap(ship.image);

	if (coin != nullptr)
		al_destroy_sample(coin);

	if (heart != nullptr)
		al_destroy_sample(heart);

	if (shot != nullptr)
		al_destroy_sample(shot);

	if (hurt != nullptr)
		al_destroy_sample(hurt);
	//al_destroy_sample_instance(titleSong);
	//al_destroy_sample(titleSample);

	if (titleImage != nullptr)
		al_destroy_bitmap(titleImage);

	if (lostSong != nullptr)
		al_destroy_sample_instance(lostSong);

	if (lostSample != nullptr)
		al_destroy_sample(lostSample);

	if (lost != nullptr)
		al_destroy_bitmap(lost);

	if (titleButtons != nullptr)
		al_destroy_bitmap(titleButtons);

	fontSelected = nullptr;
	font18 = nullptr;
	fontTitle = nullptr;
	fontTitle = nullptr;
	fader = nullptr;
	ship.image = nullptr;
	coin = nullptr;
	shot = nullptr;
	heart = nullptr;
	hurt = nullptr;
	titleImage = nullptr;
	lostSong = nullptr;
	lostSample = nullptr;
	lost = nullptr;
	titleButtons = nullptr;

	for (int i = 0; i < NUM_COLLECTIBLES; i++)
	{
		if (collect[i].image != NULL || collect[i].image != nullptr)
		{
			al_destroy_bitmap(collect[i].image);
			collect[i].image = nullptr;
		}
		else
		{
			continue;
		}
	}

	for (int i = 0; i < NUM_HEARTS; i++)
	{
		if (powerup[i].image != NULL)
		{
			al_destroy_bitmap(powerup[i].image);
			powerup[i].image = nullptr;
		}
		else
		{
			continue;
		}
	}

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (enemyShot[i] != NULL || enemyShot != nullptr)
		{
			al_destroy_sample(enemyShot[i]);
			enemyShot[i] = nullptr;
		}
		else
		{
			continue;
		}
	}

	/*
	for (int count = 0; count < NUM_ENEMIES; count++)
	{
		if (helix[count] != NULL)
		{
			al_destroy_bitmap(helix[count]);
			helix[count] = NULL;
		}
	}
	*/

	if (stage1 != NULL)	al_destroy_sample_instance(stage1);
	if (stage2 != NULL)	al_destroy_sample_instance(stage2);
	if (endingInstance != NULL)	al_destroy_sample_instance(endingInstance);
	if (bossInstance != NULL)	al_destroy_sample_instance(bossInstance);
	if (titleInstance != NULL)	al_destroy_sample_instance(titleInstance);

	if (sample != NULL)	al_destroy_sample(sample);
	if (sample2 != NULL)	al_destroy_sample(sample2);
	if (bossSample != NULL)	al_destroy_sample(bossSample);
	if (endingSample != NULL)	al_destroy_sample(endingSample);
	if (titleSample != NULL)	al_destroy_sample(titleSample);
}

void GameDraw()
{
	if (isTimeToRedraw && al_is_event_queue_empty(eq))
	{
		GameRedraw();
	}
}

void InitShip()
{
	ship.x = PLAYER_INITIAL_X;
	ship.y = PLAYER_INITIAL_Y;
	ship.ID = PLAYER;
	ship.collectibles = 0;
	ship.invulnerability = PLAYER_INVULNERABILITY;
	ship.lives = PLAYER_LIVES;
	ship.state = -1;
	ship.speed = PLAYER_SHIP_SPEED;
	ship.boundX = PLAYER_BOUNDX;
	ship.boundY = PLAYER_BOUNDY;
	ship.score = 0;
	ship.firingType = 0;
	ship.playerDirection = EAST;
	ship.attackDirection = EAST;

	ship.horizontalSpeed = PLAYER_HORIZONTAL_SPEED;
	ship.verticalSpeed = PLAYER_VERTICAL_SPEED;

	ship.angle = 0;
	ship.sine = 0.00;
	ship.cosine = 0.00;

	ship.currWeapon = SINGLE_SHOT;
	ship.walkingDelta = BLOCK_SIZE;
	ship.isWalking = false;
	ship.isFiringBullets = false;
	ship.isFiringDoubleShot = false;
	//ship.hasFiredBullet = false;
	ship.nextWeapon = SINGLE_SHOT;
	ship.quantWeapons = PLAYER_NUM_WEAPONS;

	if (ship.firingType == 0)
	{
		ship.currentFrame = 0;
		ship.waitingFrame = PLAYER_FIRING_COOLDOWN;
		
	}

	if (ship.image == NULL || ship.image == nullptr){
		ship.image = al_load_bitmap(PLAYER_BITMAP);
		ship.width = al_get_bitmap_width(ship.image);
		ship.height = al_get_bitmap_height(ship.image);
		al_convert_mask_to_alpha(ship.image, al_map_rgb(MAX_RGB_VALUE, 0, MAX_RGB_VALUE));
	}

	red = blue = green = MAX_RGB_VALUE;
	alpha = MIN_RGB_VALUE;
}

void DrawShip()
{
	if (ship.image == NULL || ship.image == nullptr)
	{
		al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7, al_map_rgb(255, 0, 0));
		al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 255, 0));

		al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x + 12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
		al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x + 15, ship.y + 2, al_map_rgb(0, 0, 255));
	}
	else
	{
		if (ship.state != PLAYER_INVULNERABLE)
		{
			al_draw_bitmap(
				ship.image,
				ship.x - ship.width / 2,
				ship.y - ship.height / 2,
				NULL
				);
		}
		else
		{
			int result = ship.invulnerability % 2;

			if (result == 0)
			{
				al_draw_bitmap(
					ship.image,
					ship.x - ship.width / 2,
					ship.y - ship.height / 2,
					NULL
					);
			}
		}
	}
	
}

void MoveShipUp()
{
	ship.playerDirection = NORTH;

	//ship.isWalking = true;

	ship.y -= ship.speed;
	//ship.y--;
}

void MoveShipDown()
{
	ship.playerDirection = SOUTH;

	//ship.isWalking = true;

	ship.y += ship.speed;
	//ship.y++;
}

void MoveShipLeft()
{
	ship.playerDirection = WEST;

	//ship.isWalking = true;

	ship.x -= ship.speed;
	//ship.x--;
}

void MoveShipRight()
{
	ship.playerDirection = EAST;

	//ship.isWalking = true;

	ship.x += ship.speed;
	//ship.x++;
}

void MoveShipUpLeft()
{
	ship.playerDirection = NORTHWEST;

	MoveShipLeft();
	MoveShipUp();

	//ship.x -= ship.speed / 2;
	//ship.y -= ship.speed / 2;
}

void MoveShipDownLeft()
{
	ship.playerDirection = SOUTHWEST;

	MoveShipLeft();
	MoveShipDown();

	//ship.x -= ship.speed / 2;
	//ship.y += ship.speed / 2;
}

void MoveShipUpRight()
{
	ship.playerDirection = NORTHEAST;

	MoveShipRight();
	MoveShipUp();

	//ship.x += ship.speed / 2;
	//ship.y -= ship.speed / 2;
}

void MoveShipDownRight()
{
	ship.playerDirection = SOUTHEAST;

	MoveShipRight();
	MoveShipDown();

	//ship.x += ship.speed / 2;
	//ship.y += ship.speed / 2;
}

void UpdateShip()
{
	if (ship.y <= 0){
		ship.y = 0;
	}

	if (ship.y >= SCREEN_HEIGHT){
		ship.y = SCREEN_HEIGHT;
	}

	if (ship.x <= 0){
		ship.x = 0;
	}

	if (ship.x >= SCREEN_WIDTH){
		ship.x = SCREEN_WIDTH;
	}

	ship.currTileX = ship.x / TILE_WIDTH;
	ship.currTileY = ship.y / TILE_HEIGHT;
	ship.currPosX = ship.x;
	ship.currPosY = ship.y;

	// FAZER GRAVIDADE E ACELERAÇÃO DE VELOCIDADE DO PERSONAGEM

	if (ship.isWalking == true){
		ship.walkingDelta--;
		if (ship.walkingDelta < 0){
			ship.isWalking = false;
			ship.walkingDelta = BLOCK_SIZE;
		}
	}
	
	if (ship.invulnerability > 0 && ship.state == PLAYER_INVULNERABLE){
		ship.invulnerability--;
	}
	else
	{
		ship.invulnerability = PLAYER_INVULNERABILITY;
		ship.state = PLAYER_VULNERABLE;
	}

	if (ship.lives > PLAYER_MAX_LIVES)
	{
		ship.lives = PLAYER_MAX_LIVES;
	}

}

void getNextEvent()
{
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		ifEventIsTimer();
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		ifEventIsKeyDown();
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		ifEventIsKeyUp();
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		ifEventIsDisplayClose();
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		//ifEventIsMouseAxes();
		
		//MoveShipWithMouse();
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		//ifEventIsMouseButtonDown();
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		//ifEventIsMouseButtonUp();
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
	{
		//ifEventIsMouseEnterDisplay();
	}
	else if (ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
	{
		//ifEventIsMouseLeaveDisplay();
	}
	else if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
	{
		//ifEventIsJoystickButtonDown();
	}
	else if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
	{
		//ifEventIsJoystickButtonUp();
	}
	else if (ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
	{
		//ifEventIsJoystickAxes();
	}
}

void waitForEvent()
{
	al_wait_for_event(eq, &ev);
}

void ifEventIsKeyDown()
{
	switch (ev.keyboard.keycode)
	{
		case ALLEGRO_KEY_ESCAPE:

			if (state == PLAYING){	//DestroyAssets();
				menu.selected = 0;  MenuPauseCommand();		fade = MAX_RGB_VALUE / 2;	ChangeState(PAUSING);
			}
			else if (state == PAUSING){
				menu.selected = 0;  MenuPauseCommand();		fade = MIN_RGB_VALUE;		ChangeState(PLAYING);
			}
			else if (state == SETTING_AUDIO)
			{
				menu.selected = 0;  MenuPauseCommand();		fade = MAX_RGB_VALUE / 2;	ChangeState(PAUSING);
			}
			else if (state == -9999){
				//escapeGameLoop:
				//DestroyAssets();
				isGameLoopDone = true;
			}
			else if (state == CONTROLS){
				//goto escapeGameLoop;
			}
			else if (state == OPTIONS){
				//DestroyAssets();
				MenuConfirmCommand();	menu.selected = 0;
				ChangeState(TITLE);
			}
			else if (state == LOST){
				MenuConfirmCommand();	menu.selected = 0;
				ChangeState(QUIT_EVERYTHING);
			}
			else if (state == QUITTING_EVERYTHING)
			{
				escapeGame:
				MenuConfirmCommand();	menu.selected = 0;
				ChangeState(PAUSING);
			}
			else if (state == QUITTING_GAMEPLAY)
			{
				goto escapeGame;
			}
			else if (state == QUIT_GAMEPLAY)
			{
				loseGame:
				MenuConfirmCommand(); menu.selected = 0;
				ChangeState(LOST);
			}
			else if (state == QUIT_EVERYTHING)
			{
				goto loseGame;
			}
			else if (state == ENDING)
			{
				MenuConfirmCommand(); menu.selected = 0;	InitEverything();
				ChangeState(TITLE);
			}
			else if (state == TITLE)
			{
				isGameLoopDone = true;
			}
			
			break;

		case ALLEGRO_KEY_UP:
			keys[UP] = true;

			if (state == TITLE)
			{
				menu.selected--;

				if (menu.selected >= 0 && menu.selected < TITLE_NUM_COMMANDS){
					MenuSelectCommand();
				}				
			}
			else if (state == PAUSING)
			{
				menu.selected--;

				if (menu.selected >= 0 && menu.selected < PAUSING_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == OPTIONS || state == SETTING_AUDIO)
			{
				menu.selected--;

				if (menu.selected >= 0 && menu.selected < OPTIONS_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == QUITTING_GAMEPLAY ||
				state == QUITTING_EVERYTHING || 
				state == QUIT_EVERYTHING ||
				state == QUIT_GAMEPLAY)
			{
				menu.selected--;

				if (menu.selected >= 0 && menu.selected < CONFIRMATION_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == LOST)
			{
				menu.selected--;

				if (menu.selected >= 0 && menu.selected < LOST_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			break;

		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = true;

			if (state == TITLE)
			{
				menu.selected++;

				if (menu.selected >= 0 && menu.selected < TITLE_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == PAUSING)
			{
				menu.selected++;

				if (menu.selected >= 0 && menu.selected < PAUSING_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == OPTIONS || state == SETTING_AUDIO)
			{
				menu.selected++;

				if (menu.selected >= 0 && menu.selected < OPTIONS_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == QUITTING_GAMEPLAY || 
				state == QUITTING_EVERYTHING || 
				state == QUIT_EVERYTHING || 
				state == QUIT_GAMEPLAY)
			{
				menu.selected++;

				if (menu.selected >= 0 && menu.selected < CONFIRMATION_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			else if (state == LOST){
				menu.selected++;

				if (menu.selected >= 0 && menu.selected < LOST_NUM_COMMANDS){
					MenuSelectCommand();
				}
			}
			break;

		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;

			if (state == OPTIONS || state == SETTING_AUDIO){
				if (menu.selected == 0){
					PC.backgroundMusicVolume = PC.backgroundMusicVolume - BGM_VOLUME_CONTROL;
					MenuConfigureCommand();

					al_set_sample_instance_gain(titleInstance, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(bossInstance, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(endingInstance, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(lostSong, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(stage1, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(stage2, PC.backgroundMusicVolume);
				}
				else if (menu.selected == 1){
					PC.soundEffectVolume = PC.soundEffectVolume - SFX_VOLUME_CONTROL;
					MenuConfigureCommand();
				}
				else if (menu.selected == -1){
					PC.gameTune--;
					MenuConfigureCommand();
				}
				else if (menu.selected == 2){
					PC.soundPan = PC.soundPan - SOUND_PAN_VALUE;
					MenuChangeCommand();

					al_set_sample_instance_pan(titleInstance, PC.soundPan);
					al_set_sample_instance_pan(bossInstance, PC.soundPan);
					al_set_sample_instance_pan(endingInstance, PC.soundPan);
					al_set_sample_instance_pan(lostSong, PC.soundPan);
					al_set_sample_instance_pan(stage1, PC.soundPan);
					al_set_sample_instance_pan(stage2, PC.soundPan);
				}
				else if (menu.selected == 4){
					//PC.playerLives--;
				}
			}
			else if (state == TITLE){
				//fade--;
				//std::cout << "-FADE" << std::endl;
			}

			break;

		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;

			if (state == OPTIONS || state == SETTING_AUDIO)
			{
				if (menu.selected == 0){
					PC.backgroundMusicVolume = PC.backgroundMusicVolume + BGM_VOLUME_CONTROL;
					MenuConfigureCommand();

					al_set_sample_instance_gain(titleInstance, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(bossInstance, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(endingInstance, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(lostSong, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(stage1, PC.backgroundMusicVolume);
					al_set_sample_instance_gain(stage2, PC.backgroundMusicVolume);
				}
				else if (menu.selected == 1){
					PC.soundEffectVolume = PC.soundEffectVolume + SFX_VOLUME_CONTROL;
					MenuConfigureCommand();
				}
				else if (menu.selected == -1){
					PC.gameTune++;
					MenuConfigureCommand();
				}
				else if (menu.selected == 2){
					PC.soundPan = PC.soundPan + SOUND_PAN_VALUE;
					MenuChangeCommand();

					al_set_sample_instance_pan(titleInstance, PC.soundPan);
					al_set_sample_instance_pan(bossInstance, PC.soundPan);
					al_set_sample_instance_pan(endingInstance, PC.soundPan);
					al_set_sample_instance_pan(lostSong, PC.soundPan);
					al_set_sample_instance_pan(stage1, PC.soundPan);
					al_set_sample_instance_pan(stage2, PC.soundPan);
				}
				else if (menu.selected == 4){
					//PC.playerLives++;
				}
			}
			else if (state == TITLE){
				//fade++;
				//std::cout << "+FADE" << std::endl;
			}

			break;

		case ALLEGRO_KEY_Z:
			keys[SHOOT] = true;

			if (state == TITLE)
			{
				//ChangeState(PLAYING);
			}
			else if (state == LOST)
			{
				//ChangeState(PLAYING);
			}
			else if (state == PLAYING)
			{
				//gameplay.currentFrame = LEVEL_ENDING;
			}

			//FireBullet();
			break;

		case ALLEGRO_KEY_COMMA:
			keys[ZOOM_OUT] = true;
			//ZoomOut();

			break;

		case ALLEGRO_KEY_FULLSTOP:
			keys[ZOOM_IN] = true;
			//ZoomIn();

			break;

		case ALLEGRO_KEY_N:
			keys[ROTATE_LEFT] = true;
			break;

		case ALLEGRO_KEY_M:
			keys[ROTATE_RIGHT] = true;

			/*
			if (al_get_sample_instance_gain(bongosTrack) <= 0)
			{
				al_set_sample_instance_gain(bongosTrack, 0.75);
			}
			else if (al_get_sample_instance_gain(bongosTrack) > 0)
			{
				al_set_sample_instance_gain(bongosTrack, 0.0);
			}
			*/
			break;

		case ALLEGRO_KEY_X:
			keys[RESET_ZOOMING_SCALE] = true;

			if (state == PLAYING)
			{
				//ChangeWeapon();
			}

			//ResetZoomingScale();
			break;

		case ALLEGRO_KEY_ENTER:
			keys[ENTER] = true;

			//std::cout << "ENTER PRESSIONADO!" << std::endl;

			if (state == TITLE)
			{
				switch (menu.selected)
				{
					case 0:
						// 1 PLAYER GAME
						//isFading = true;
						gameplay.currentFrame = 0;	menu.selected = 0;	MenuConfirmCommand();
						ChangeState(PLAYING);

						break;

					case -9:
						// 2 PLAYER GAME
						MenuConfirmCommand();	menu.selected = 0;
						ChangeState(LOADING);

						break;

						
					case 1:
						// OPÇÕES DO APLICATIVO
						menu.selected = 0; MenuConfirmCommand();	//menu.options = OPTIONS_NUM_COMMANDS;
						ChangeState(OPTIONS);
						break;

					case -99:
						// MENU DE SENHA
						//menu.selected = 0;
						MenuConfirmCommand();	
						ChangeState(CONTROLS);
						break;

					case 2:
						// CRÉDITOS DO APLICATIVO
						//isGameLoopDone = true;
						//menu.selected = 0;
						MenuConfirmCommand();	al_rest(EXIT_REST);	ChangeState(GAME_EXIT);
						break;

					default:
						break;
				}
			}
			else if (state == PLAYING)
			{
				//al_set_sample_instance_position(song, songLength / 2);
				
			}
			else if (state == SELECT){

			}
			else if (state == PASSWORD){

			}
			else if (state == CREDITS){

			}
			else if (state == LOADING){

			}
			else if (state == OPTIONS)
			{
				switch (menu.selected)
				{
					case 3:
						
						SetDefaultValues();

						al_set_sample_instance_gain(titleInstance, PC.backgroundMusicVolume);
						al_set_sample_instance_gain(bossInstance, PC.backgroundMusicVolume);
						al_set_sample_instance_gain(endingInstance, PC.backgroundMusicVolume);
						al_set_sample_instance_gain(lostSong, PC.backgroundMusicVolume);
						al_set_sample_instance_gain(stage1, PC.backgroundMusicVolume);
						al_set_sample_instance_gain(stage2, PC.backgroundMusicVolume);

						al_set_sample_instance_pan(titleInstance, PC.soundPan);
						al_set_sample_instance_pan(bossInstance, PC.soundPan);
						al_set_sample_instance_pan(endingInstance, PC.soundPan);
						al_set_sample_instance_pan(lostSong, PC.soundPan);
						al_set_sample_instance_pan(stage1, PC.soundPan);
						al_set_sample_instance_pan(stage2, PC.soundPan);

						break;

					case 4:
						MenuConfirmCommand();	ChangeState(TITLE);
						break;

					default: break;
				}
			}
			else if (state == CONTROLS)
			{
				switch (menu.selected)
				{
					case 10:
						ChangeState(TITLE);
						break;

					default: break;
				}
			}
			else if (state == WON){

			}
			else if (state == LOST)
			{
				switch (menu.selected)
				{
					case 0:

						//InitEverything();
						MenuConfirmCommand(); menu.selected = 0;	ChangeState(PLAYING);

						break;

					case 1:
						// QUIT GAMEPLAY, QUIT TO TITLE SCREEN
						MenuConfirmCommand();	menu.selected = 0;		ChangeState(QUIT_GAMEPLAY);

						break;

					case 2:		//	QUIT EVERYTHING, SAIR DO APLICATIVO
						MenuConfirmCommand();	al_rest(EXIT_REST);		ChangeState(QUIT_EVERYTHING);
						break;

					default: break;
				}
			}
			else if (state == FILES){

			}
			else if (state == GAMEOVER){

			}
			else if (state == ENDING){

			}
			else if (state == GAME_EXIT){
				// FIM DE JOGO
			}
			else if (state == TRANSITION){
				ChangeState(PLAYING);
			}
			else if (state == PAUSING)
			{
				if (menu.selected == 0)
				{
					fade = MIN_RGB_VALUE;	MenuConfirmCommand();	menu.selected = 0;

					ChangeState(PLAYING);
				}
				else if (menu.selected == 1)
				{
					fade = MAX_RGB_VALUE / 2; MenuConfirmCommand();	 menu.selected = 0;

					ChangeState(SETTING_AUDIO);
				}
				else if (menu.selected == 2)
				{
					fade = MAX_RGB_VALUE / 2;	MenuConfirmCommand();	menu.selected = 0;

					ChangeState(QUITTING_GAMEPLAY);
				}
				else  if (menu.selected == 3)
				{
					fade = fade = MAX_RGB_VALUE / 2; MenuConfirmCommand();	menu.selected = 0;

					ChangeState(QUITTING_EVERYTHING);
				}
			}
			else if (state == QUITTING_EVERYTHING)
			{
				if (menu.selected == 0)
				{
					MenuConfirmCommand();
					ChangeState(PAUSING); 
				}
				else if (menu.selected == 1)
				{
					MenuConfirmCommand(); fade = MIN_RGB_VALUE; al_rest(EXIT_REST);
					ChangeState(GAME_EXIT);
				}
			}
			else if (state == QUITTING_GAMEPLAY)
			{
				if (menu.selected == 0)
				{
					MenuConfirmCommand();
					ChangeState(PAUSING); 
				}
				else if (menu.selected == 1)
				{
					MenuConfirmCommand();

					gameplay.currentLevel = stage.levelNumber = LEVEL01;
					stage.nextLevel = LEVEL02;
					InitEverything();

					ChangeState(TITLE);
				}
			}
			else if (state == QUIT_GAMEPLAY)
			{
				switch (menu.selected)
				{
					case 0:
						menu.selected = 0;	MenuConfirmCommand();		ChangeState(LOST);
						break;

					case 1: 
						menu.selected = 0;	MenuConfirmCommand(); 	gameplay.currentLevel = stage.levelNumber = LEVEL01;	stage.nextLevel = LEVEL02;	ChangeState(TITLE);
						break;

					default: break;
				}
			}
			else if (state == QUIT_EVERYTHING)
			{
				switch (menu.selected)
				{
					case 0:
						menu.selected = 0;	MenuConfirmCommand();		ChangeState(LOST);
						break;

					case 1:
						menu.selected = 0;	MenuConfirmCommand(); 		al_rest(EXIT_REST);		ChangeState(GAME_EXIT);
						break;

					default: break;
				}
			}
			else if (state == SETTING_AUDIO)
			{
				switch (menu.selected)
				{
					case 3:
						SetDefaultValues();
						break;

					case 4:
						MenuConfirmCommand();

						ChangeState(PAUSING);
						break;
				}
			}
			else if (state == SAVING)
			{

			}

			break;

		case ALLEGRO_KEY_0:
			keys[SHOW_COLLISION] = true;

			//showCollision = !showCollision;

			break;
		default:
			break;
	}
}

void ifEventIsKeyUp()
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_ESCAPE:
		isGameLoopDone = false;
		break;

	case ALLEGRO_KEY_UP:
		keys[UP] = false;
		break;

	case ALLEGRO_KEY_DOWN:
		keys[DOWN] = false;
		break;

	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = false;
		break;

	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = false;
		break;

	case ALLEGRO_KEY_Z:
		keys[SHOOT] = false;
		break;

	case ALLEGRO_KEY_COMMA:
		keys[ZOOM_OUT] = false;
		break;

	case ALLEGRO_KEY_FULLSTOP:
		keys[ZOOM_IN] = false;
		break;

	case ALLEGRO_KEY_X:
		keys[RESET_ZOOMING_SCALE] = false;
		break;

	case ALLEGRO_KEY_ENTER:
		keys[ENTER] = false;
		break;

	case ALLEGRO_KEY_N:
		keys[ROTATE_LEFT] = false;

		break;

	case ALLEGRO_KEY_M:
		keys[ROTATE_RIGHT] = false;

		break;

	case ALLEGRO_KEY_0:
		keys[SHOW_COLLISION] = false;
		break;

	default:
		break;
	}
}

void ifEventIsTimer()
{
	isTimeToRedraw = true;
	currFrame++;

	if (state == TITLE && isFading == true)
	{
		currFrame2++;

		if (currFrame2 % DIV_BY == DIV_REMAINER)
		{
			FadingIncrease();
		}

		if (currFrame2 > FRAME_RATE * 2)
		{
			currFrame2 = 0;
			isFading = false;
		}
	}
	else if (state == OPTIONS)
	{
		// SE O JOGADOR ESTÁ NA TELA DE CONFIGURAÇÕES (SETUP)
	}

	if (currFrame < 0)
	{
		currFrame = 0;
	}
	if (currFrame >= FRAME_RATE)
	{
		currFrame = 0;
	}

	if (state == TITLE ||
		state == OPTIONS ||
		state == PASSWORD ||
		state == SELECT ||
		state == FILES || 
		state == CONTROLS || 
		state == PAUSING || 
		state == LOADING || 
		state == SETTING_AUDIO ||
		state == QUITTING_EVERYTHING || 
		state == QUITTING_GAMEPLAY || 
		state == SAVING)
	{
		if (menu.selected < 0)
		{
			menu.selected = 0;
		}
		else if (menu.selected > menu.options - 1)
		{
			menu.selected = menu.options - 1;
		}
	}
	
	
	if (keys[UP] && !keys[LEFT] && !keys[RIGHT]){
		if (state == PLAYING){
			MoveShipUp();
		}
	}
	else if (keys[DOWN] && !keys[LEFT] && !keys[RIGHT]){
		if (state == PLAYING){
			MoveShipDown();
		}
	}
	else if (keys[LEFT] && !keys[UP] && !keys[DOWN]){
		if (state == PLAYING){
			MoveShipLeft();
		}
	}
	else if (keys[RIGHT] && !keys[UP] && !keys[DOWN]){
		if (state == PLAYING){
			MoveShipRight();
		}
	}
	else if (keys[UP] && keys[LEFT] && !keys[RIGHT]){
		if (state == PLAYING){
			MoveShipUpLeft();
		}		
	}
	else if (keys[UP] && !keys[LEFT] && keys[RIGHT]){
		if (state == PLAYING){
			MoveShipUpRight();
		}
	}
	else if (keys[DOWN] && keys[LEFT] && !keys[RIGHT]){
		if (state == PLAYING){
			MoveShipDownLeft();
		}
	}
	else if (keys[DOWN] && !keys[LEFT] && keys[RIGHT]){
		if (state == PLAYING){
			MoveShipDownRight();
		}
	}
	
	
	if (keys[LEFT])
	{
		// AUMENTAR A TRANSPARÊNCIA DA IMAGEM, CLAREIA A TELA
		//FadingIncrease();
		//std::cout << "FADE = " << fade << " " << std::endl;
	}
	else if (keys[RIGHT])
	{
		// DIMINUI A TRANSPARÊNCIA DA IMAGEM, ESCURECE A TELA
		//FadingDecrease();
		//std::cout << "FADE = " << fade << " " << std::endl;
	}

	/*
	if (keys[ESCAPE])
	{
		if (state == PLAYING)
		{
			MenuPauseCommand();
			fade = MAX_RGB_VALUE / 2;
			ChangeState(PAUSING);
		}
		else if (state == PAUSING)
		{
			MenuPauseCommand();
			fade = MIN_RGB_VALUE;
			ChangeState(PLAYING);
		}
	}
	*/
	
	/*
	if (keys[UP])
	{
		MoveShipUp();
	}
	else if (keys[DOWN])
	{
		MoveShipDown();
	}
	if (keys[LEFT])
	{
		MoveShipLeft();
	}
	else if (keys[RIGHT])
	{
		MoveShipRight();
	}
	*/
	
	if (keys[SHOOT]){
	//if ( mouse[0] && ship.isFiringBullets == false){
		if (state == PLAYING){

			if (ship.isFiringBullets == false)
			{
				FireBullet2();
				//ShootChemicalTrails();
			}
			//ship.isFiringBullets = true;
			//Comet_FireBullet();
		}
	}

	//offsetX += keys[RIGHT] * 2;
	//offsetX -= keys[LEFT] * 2;
	//offsetY += keys[DOWN] * 2;
	//offsetY -= keys[UP] * 2;

	GameUpdate();
}

void ifEventIsDisplayClose()
{
	//isGameLoopDone = true;
	if (state == PLAYING)
	{
		fade = fade = MAX_RGB_VALUE / 2; MenuConfirmCommand();	menu.selected = 0;
		ChangeState(QUITTING_EVERYTHING);
	}
	else if (state == QUITTING_EVERYTHING ||
		state == QUITTING_GAMEPLAY || 
		state == QUIT_EVERYTHING || 
		state == QUIT_GAMEPLAY)
	{
		isGameLoopDone = true;
	}
	else if (state == TITLE || 
		state == OPTIONS ||
		state == SETTING_AUDIO ||
		state == LOST || 
		state == ENDING)
	{
		isGameLoopDone = true;
	}
}

void GameRedraw()
{
	isTimeToRedraw = false;

	if (state == TITLE)
	{
		int width = 0, height = 0, widthOffset = 25, heightOffset = 25;

		TitleScreen();
		DrawFading();
	}
	else if (state == TRANSITION)
	{
		//DrawFading();
	}
	else if (state == PLAYING)
	{

		DrawLevel();
		DrawShip();
		DrawBullet();
		//DrawBDoubleShot();
		DrawComet();
		Comet_DrawBullet();
		DrawEnemy();
		DrawChemicalTrails();
		DrawBoss(-1, -1);
		DrawShot(-1);
		DrawProjectile(-1);
		DrawExplosion();
		ShowCollision();
		DrawHUD();
		/*al_draw_textf(font18, al_map_rgb(255, 255, 255), 30, 30, 0,
			"Song: Length=%u Position=%u Time=%.2f Speed=%.2f ", songLength, songPosition, songTime, songSpeed);
		*/

		//al_draw_textf(font18, al_map_rgb(255, 0, 255), 25, 25, 0, "FRAMES: %i", gameplay.currentFrame);

		if (gameplay.currentFrame >= LEVEL_ENDING)
		{
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .45, 5, NULL, "BOSS: %d", badGuy[0].numLives);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .70, 5, NULL, "FRAMES BOSS: %d", badGuy[0].currFrame);
		}
	}
	else if (state == LOST)
	{
		//drawLostScreen:
		LoseScreen();

		//al_draw_textf(font18, al_map_rgb(0, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
		//"GAME OVER. FINAL SCORE: %i", ship.score);
	}
	else if (state == QUIT_EVERYTHING)
	{
		goto drawLoseScreen;
	}
	else if (state == QUIT_GAMEPLAY)
	{
		drawLoseScreen:
		QuitToTitleScreen();
	}
	else if (state == OPTIONS)
	{
		OptionsScreen();
	}
	else if (state == CREDITS)
	{
		al_draw_textf(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTRE,
			"CREDITS");
	}
	else if (state == PASSWORD)
	{
		al_draw_textf(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTRE,
			"PASSWORD");
	}
	else if (state == CONTROLS)
	{
		ControllerScreen();
	}
	else if (state == SOUNDTEST)
	{
		al_draw_textf(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTRE,
			"SOUND TEST");
	}
	else if (state == SELECTING)
	{
		al_draw_textf(font18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTRE,
			"CHARACTER SELECTION");
	}
	else if (state == ENDING)
	{
		EndingScreen(0);
	}
	else if (state == LOADING)
	{
		LoadGameScreen();
	}
	else if (state == SAVING)
	{
		SaveGameScreen();
	}
	else if (state == PAUSING)
	{
		DrawLevel();
		DrawShip();
		DrawBullet();
		//DrawBDoubleShot();
		DrawComet();
		Comet_DrawBullet();
		DrawEnemy();
		DrawChemicalTrails();
		DrawBoss(-1, -1);
		DrawShot(-1);
		DrawExplosion();
		ShowCollision();
		DrawHUD();

		if (gameplay.currentFrame >= FPS_LIMIT){
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .45, 5, NULL, "BOSS: %d", badGuy[0].numLives);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .70, 5, NULL, "FRAMES BOSS: %d", badGuy[0].currFrame);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .4, 5, NULL, "ANGLE: %d", angle);
		}

		PauseScreen();
	}
	else if (state == QUITTING_EVERYTHING)
	{
		goto drawQuit;
	}
	else if (state == QUITTING_GAMEPLAY)
	{
		drawQuit:

		DrawLevel();
		DrawShip();
		DrawBullet();
		//DrawBDoubleShot();
		DrawComet();
		Comet_DrawBullet();
		DrawEnemy();
		DrawChemicalTrails();
		DrawBoss(-1, -1);
		DrawShot(-1);
		DrawExplosion();
		ShowCollision();
		DrawHUD();

		if (gameplay.currentFrame >= FPS_LIMIT){
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .45, 5, NULL, "BOSS: %d", badGuy[0].numLives);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .70, 5, NULL, "FRAMES BOSS: %d", badGuy[0].currFrame);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .4, 5, NULL, "ANGLE: %d", angle);
		}

		QuitToTitleScreen();
	}
	else if (state == SETTING_AUDIO)
	{
		DrawLevel();
		DrawShip();
		DrawBullet();
		//DrawBDoubleShot();
		DrawComet();
		Comet_DrawBullet();
		DrawEnemy();
		DrawChemicalTrails();
		DrawBoss(-1, -1);
		DrawShot(-1);
		DrawExplosion();
		ShowCollision();
		DrawHUD();
		/*al_draw_textf(font18, al_map_rgb(255, 255, 255), 30, 30, 0,
		"Song: Length=%u Position=%u Time=%.2f Speed=%.2f ", songLength, songPosition, songTime, songSpeed);
		*/

		//al_draw_textf(font18, al_map_rgb(255, 0, 255), 25, 25, 0, "FRAMES: %i", gameplay.currentFrame);

		if (gameplay.currentFrame >= FPS_LIMIT)
		{
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .45, 5, NULL, "BOSS: %d", badGuy[0].numLives);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .70, 5, NULL, "FRAMES BOSS: %d", badGuy[0].currFrame);
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), SCREEN_WIDTH * .4, 5, NULL, "ANGLE: %d", angle);
		}

		OptionsScreen();
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void InitBullet()
{
	for (int i = 0; i < PLAYER_NUM_BULLETS; i++)
	{
		
		bullets[i].ID = BULLET;
		bullets[i].speed = PLAYER_BULLET_SPEED;
		bullets[i].alive = false;

		bullets[i].originX = bullets[i].originY = bullets[i].shipX = bullets[i].shipY = bullets[i].angle = 0.00;

		b[0][i].ID = BULLET;
		b[0][i].speed = -PLAYER_BULLET_SPEED;
		b[0][i].alive = false;

		b[0][i].originX = b[0][i].originY = b[0][i].shipX = b[0][i].shipY = b[0][i].angle = 0.00;
	}

	for (int i = 0; i < PLAYER_NUM_WEAPONS; i++){
		for (int j = 0; j < PLAYER_NUM_BULLETS; j++){
			b[i][j].ID = BULLET;
			b[i][j].speed = PLAYER_BULLET_SPEED;
			b[i][j].alive = false;
			b[i][j].angle = 0.00;
			b[i][j].bulletDirection = -1;
			b[i][j].originX = 0;
			b[i][j].originY = 0;
			b[i][j].shipX = 0;
			b[i][j].shipY = 0;
			b[i][j].coolDown = PLAYER_FIRING_COOLDOWN;
			b[i][j].currFrame = 0;
			b[i][j].isFiringBullets = false;
		}
	}
}

void DrawBullet()
{
	int i = 0, j = 0, k = 0, m = 0;

	for (i = 0; i < PLAYER_NUM_BULLETS; i++){
		if (bullets[i].alive == true){
			al_draw_filled_circle(bullets[i].x, bullets[i].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 1, 255));
		}
	}

	if (ship.currWeapon >= DOUBLE_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[0][j].alive){
				al_draw_filled_circle(b[0][j].x, b[0][j].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 0, 255));
			}
		}
	}
	
	if (ship.currWeapon >= TRIPLE_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[1][j].alive){
				al_draw_filled_circle(b[1][j].x, b[1][j].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 0, 255));
			}
		}
	}

	if (ship.currWeapon >= BACK_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[2][j].alive){
				al_draw_filled_circle(b[2][j].x, b[2][j].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 0, 255));
			}
		}
	}

	if (ship.currWeapon >= FULL_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[3][j].alive){
				al_draw_filled_circle(b[3][j].x, b[3][j].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 0, 255));
			}
		}
	}

	if (ship.currWeapon >= TEST_WEAPON){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[4][j].alive){
				al_draw_filled_circle(b[4][j].x, b[4][j].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 255, 255));
			}
		}
	}

	if (ship.currWeapon >= MACHINE_GUN_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			al_draw_filled_circle(b[5][j].x, b[5][j].y, PLAYER_BULLET_RADIUS, al_map_rgb(255, 0, 255) );
		}
	}
}

void FireBullet()
{
	for (int i = 0; i < PLAYER_NUM_BULLETS; i++)
	{
		if (bullets[i].alive == false && ship.isFiringBullets == false)
		{
			bullets[i].x = ship.x + 17;
			bullets[i].y = ship.y;
			bullets[i].alive = true;

			bullets[i].bulletDirection = ship.playerDirection;

			ship.isFiringBullets = true;
			//ship.currentFrame = 0;

			break;
		}
		
	}
}

void UpdateBullet()
{
	if (ship.isFiringBullets == true)
	{
		ship.currentFrame++;

		if (ship.currentFrame >= ship.waitingFrame)
		{
			ship.isFiringBullets = false;
			ship.currentFrame = 0;
		}
	}

	for (int i = 0; i < PLAYER_NUM_BULLETS; i++)
	{
		if (bullets[i].alive == true)
		{
			if (bullets[i].bulletDirection == EAST)
			{
				bullets[i].x += bullets[i].speed;
			}
			else if (bullets[i].bulletDirection == WEST)
			{
				bullets[i].x -= bullets[i].speed;
			}
			else if (bullets[i].bulletDirection == NORTH)
			{
				bullets[i].y -= bullets[i].speed;
			}
			else if (bullets[i].bulletDirection == SOUTH)
			{
				bullets[i].y += bullets[i].speed;
			}	
			else if (bullets[i].bulletDirection == NORTHEAST)
			{
				bullets[i].y -= (bullets[i].speed * sin(ANGLE));
				bullets[i].x += (bullets[i].speed * cos(ANGLE));
			}
			else if (bullets[i].bulletDirection == NORTHWEST)
			{
				bullets[i].y -= (bullets[i].speed * sin(ANGLE));
				bullets[i].x -= (bullets[i].speed * cos(ANGLE));
			}
			else if (bullets[i].bulletDirection == SOUTHWEST)
			{
				bullets[i].y += (bullets[i].speed * sin(ANGLE));
				bullets[i].x -= (bullets[i].speed * cos(ANGLE));
			}
			else if (bullets[i].bulletDirection == SOUTHEAST)
			{
				bullets[i].y += (bullets[i].speed * sin(ANGLE));
				bullets[i].x += (bullets[i].speed * cos(ANGLE));
			}

			if (bullets[i].x > SCREEN_WIDTH || 
				bullets[i].y > SCREEN_HEIGHT ||
				bullets[i].x < 0 ||
				bullets[i].y < 0)
			{
				bullets[i].alive = false;
			}
		}
	}
}

void GameUpdate()
{

	if (state == TITLE)
	{
		menu.options = TITLE_NUM_COMMANDS;

		UpdateFading();
	}
	else if (state == TRANSITION)
	{
		
	}
	else if (state == ENDING)
	{
		endingFrames++;

		if (endingFrames < 0)
		{
			endingFrames = 0;
		}

		if (endingFrames > FINALE_FRAMES)
		{
			ChangeState(TITLE);
		}
	}
	else if (state == PLAYING)
	{
		//UpdateFading();
		UpdateLevel();

		//SpawnCollectible(-1);
		UpdateCollectible();
		GetCollectible();

		UpdateShip();
		UpdateBullet2();
		//StartComet();
		//UpdateComet();
		CollideBullet();
		//CollideComet();
		//UpdateBDoubleShot();
		//Comet_FireBullet();
		//Comet_UpdateBullet();
		
		UpdateEnemy();
		UpdateChemicalTrails();
		CollideEnemy(-1, -1, -1, -1);
		UpdateBoss(-1, -1);
		UpdateShot(-1);
		UpdateExplosion();
		UpdateProjectile(-1);
		CollideProjectile(-1, -1);
		/*
		CameraUpdate(ship.boundX, ship.boundY);
		al_identity_transform(&camera);
		al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
		al_scale_transform(&camera, scale, scale);
		al_use_transform(&camera);
		*/

		//al_identity_transform(&rotTransf);
		//al_translate_transform(&rotTransf, -ship.x, -ship.y);
		//al_rotate_transform(&rotTransf, rotation * PI / 180);
		//al_use_transform(&rotTransf);

		if (ship.lives <= 0)
		{
			//ChangeState(LOST);
		}

		/*
		songPosition = al_get_sample_instance_position(song);
		songLength = al_get_sample_instance_length(song);
		songSpeed = al_get_sample_instance_speed(song);
		songTime = al_get_sample_instance_time(song);
		*/

		//std::cout << "FASE NUMERO: " << stage.levelNumber << " " << std::endl;
		/*
		if (al_get_sample_instance_position(song) >= al_get_sample_instance_length(song) - 5)
		{
			al_set_sample_instance_position(song, songPosition / 2);
		}
		*/
	}
	else if (state == OPTIONS)
	{
		setupAudio:
		menu.options = OPTIONS_NUM_COMMANDS;

		if (PC.backgroundMusicVolume < 0)
		{
			PC.backgroundMusicVolume = 0;
		}

		if (PC.soundEffectVolume < 0)
		{
			PC.soundEffectVolume = 0;
		}

		if (PC.gameTune < 0)
		{
			PC.gameTune = 0;
		}

		if (PC.soundPan < SOUND_PAN_LEFT)
		{
			PC.soundPan = SOUND_PAN_LEFT;
		}

		if (PC.playerCredits < 0)
		{
			PC.playerCredits = 0;
		}

		if (PC.playerLives < 0)
		{
			PC.playerLives = 0;
		}

		if (PC.playerCredits >= PLAYER_CREDITS)
		{
			PC.playerCredits = PLAYER_CREDITS - 1;
		}

		if (PC.soundPan > SOUND_PAN_RIGHT)
		{
			PC.soundPan = SOUND_PAN_RIGHT;
		}

		if (PC.playerLives >= PLAYER_LIVES)
		{
			PC.playerLives = PLAYER_LIVES - 1;
		}

		if (PC.gameTune <= 0)
		{
			PC.gameTune = 0;
		}

		if (PC.gameTune > NUM_TUNES)
		{
			PC.gameTune = NUM_TUNES;
		}

		if (PC.backgroundMusicVolume > BGM_MAX_VOLUME)
		{
			PC.backgroundMusicVolume = BGM_MAX_VOLUME;
		}

		if (PC.soundEffectVolume > SFX_MAX_VOLUME)
		{
			PC.soundEffectVolume = SFX_MAX_VOLUME;
		}

	}
	else if (state == SELECTING)
	{

	}
	else if (state == CREDITS)
	{

	}
	else if (state == CONTROLS)
	{
		menu.options = CONTROLS_NUM_COMMANDS;
	}
	else if (state == SOUNDTEST)
	{
		
	}
	else if (state == LOST)
	{
		menu.options = LOST_NUM_COMMANDS;

		if (menu.selected < CONST_ZERO)
		{
			menu.selected = CONST_ZERO;
		}
		else if (menu.selected > LOST_NUM_COMMANDS - 1)
		{
			menu.selected = LOST_NUM_COMMANDS - 1;
		}
	}
	else if (state == PASSWORD)
	{

	}
	else if (state == GAME_EXIT)
	{
		isGameLoopDone = true;

		
	}
	else if (state == LOADING)
	{
		menu.options = LOADING_NUM_COMMANDS;
	}
	else if (state == SAVING)
	{
		menu.options = SAVING_NUM_COMMANDS;
	}
	else if (state == PAUSING)
	{
		menu.options = PAUSING_NUM_COMMANDS;
		//fade = MAX_RGB_VALUE / 2;
	}
	else if (state == QUITTING_EVERYTHING)
	{
		quitEverything:
		menu.options = CONFIRMATION_NUM_COMMANDS;
	}
	else if (state == QUITTING_GAMEPLAY)
	{
		goto quitEverything;
	}
	else if (state == SETTING_AUDIO)
	{
		//menu.options = OPTIONS_NUM_COMMANDS;
		goto setupAudio;
	}
	else if (state == QUIT_EVERYTHING)
	{
		// SAIR DE TUDO
		goto quitGameplay;
	}
	else if (state == QUIT_GAMEPLAY)
	{
		// SAIR DO GAMEPLAY
		quitGameplay:
		menu.options = CONFIRMATION_NUM_COMMANDS;

		if (menu.selected < CONST_ZERO)
		{
			menu.selected = CONST_ZERO;
		}
		else if (menu.selected > CONFIRMATION_NUM_COMMANDS - 1)
		{
			menu.selected = CONFIRMATION_NUM_COMMANDS - 1;
		}
	}
}

void InitComet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		comets[i].ID = ENEMY;
		comets[i].alive = false;
		comets[i].speed = COMET_MOVE_SPEED;
		comets[i].boundX = COMET_BOUNDX;
		comets[i].boundY = COMET_BOUNDY;

		comets[i].currentFrame = 0;
		comets[i].isFiringBullets = false;
		comets[i].waitingFrame = COMET_FIRING_COOLDOWN;
		comets[i].hasFiredBullets = false;

		comets[i].bulletFiringCycle = COMET_FIRING_TRIGGER;

		if (image == NULL)
		{
			comets[i].image = image;
		}
	}
}

void DrawComet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		if (comets[i].alive == true)
		{
			al_draw_filled_circle(comets[i].x, comets[i].y, COMET_BODY_RADIUS, al_map_rgb(255, 0, 0));
		}
	}
}

void StartComet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		if (comets[i].alive == false)
		{
			randomizeNumberOfComets();

			if (generatedNumber == 0)
			{
				randomizeCometPosition();

				comets[i].alive = true;
				comets[i].x = SCREEN_WIDTH;
				comets[i].y = generatedNumber2;

				break;
			}

		}
	}
}

void randomizeNumberOfComets()
{
	generatedNumber = rand() % COMET_SPAWN_RATE;
}

void randomizeCometPosition()
{
	generatedNumber2 = COMET_POSITION_BUFFER + rand() % (SCREEN_HEIGHT - 60);
}

void UpdateComet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		if (comets[i].alive == true)
		{
			comets[i].x -= comets[i].speed;

			if (comets[i].x < 0 || comets[i].y < 0 || 
				comets[i].x > SCREEN_WIDTH || 
				comets[i].y > SCREEN_HEIGHT )
			{
				comets[i].alive = false;
				ship.lives--;
			}

		}
	}
}

void CollideBullet()
{
	int c;
	if (ship.currWeapon >= SINGLE_SHOT){
		for (int i = 0; i < PLAYER_NUM_BULLETS; i++)
		{
			if (bullets[i].alive == true)
			{
				for (int k = 0; k < MAX_NUM_COMETS; k++)
				{
					if (comets[k].alive == true)
					{
						if (bullets[i].x >(comets[k].x - comets[k].boundX) &&
							bullets[i].x < (comets[k].x + comets[k].boundX) &&
							bullets[i].y >(comets[k].y - comets[k].boundY) &&
							bullets[i].y < (comets[k].y + comets[k].boundY))
						{
							// HÁ UMA COLISÃO ENTRE PROJÉTIL E COMETA
							bullets[i].alive = false;
							comets[k].alive = false;
							ship.score++;
						}
					}
				}

				for (c = 0; c < NUM_ENEMIES; c++)
				{
					if (e[c].alive == true)
					{
						if (bullets[i].x > e[c].posX - e[c].borderX &&
							bullets[i].x < e[c].posX + e[c].borderX &&
							bullets[i].y > e[c].posY - e[c].borderY &&
							bullets[i].y < e[c].posY + e[c].borderY )
						{
							bullets[i].alive = false;
							e[c].alive = false;
							ship.score++;
							StartExplosion(e[c].posX, e[c].posY, e[c].velX);
						}
					}

					// SE O PROJÉTIL DO JOGADOR COLIDIU COM O HELICÓPTERO ATIVADO
					if (copter[c].alive == true)
					{
						if (bullets[i].x > (copter[c].posX - copter[c].borderX) &&
							bullets[i].x < (copter[c].posX + copter[c].borderX) &&
							bullets[i].y >(copter[c].posY - copter[c].borderY) &&
							bullets[i].y < (copter[c].posY + copter[c].borderY) )
						{
							bullets[i].alive = false;
							copter[c].alive = false;
							ship.score++;
							StartExplosion(copter[c].posX, copter[c].posY, copter[c].speed);
						}
					}
				}

				for (int bSize = 0; bSize < NUM_BOSSES; bSize++)
				{
					if (
						badGuy[bSize].x - badGuy[bSize].borderX < bullets[i].x &&
						badGuy[bSize].x + badGuy[bSize].borderX > bullets[i].x &&
						badGuy[bSize].y - badGuy[bSize].borderY * BOSS01_COLLISION_OFFSET < bullets[i].y &&
						badGuy[bSize].y + badGuy[bSize].borderY > bullets[i].y
						&& bSize == CONST_ZERO)
					{
						bossGotHit:

						if (badGuy[bSize].currState == BOSS_IDLING && badGuy[bSize].gotHit == false && badGuy[bSize].numLives > 0)
						{
							bullets[i].alive = false;
							badGuy[bSize].numLives--;
							al_play_sample(badGuy[0].hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
							badGuy[bSize].gotHit = true;
							//badGuy[bSize].currState = BOSS_GETTING_HIT;
						}
						else if (badGuy[1].numLives <= 0 && badGuy[1].gotHit == false)
						{
							// SE O BOSS NÃO TEM MAIS VIDAS
							badGuy[1].currFrame = 0;
							badGuy[1].currFrame2 = 0;
							badGuy[1].currState = BOSS_DYING;
							//badGuy[1].gotHit = true;
						}
					}
					else if (badGuy[bSize].x - badGuy[bSize].borderX < bullets[i].x &&
						badGuy[bSize].x + badGuy[bSize].borderX > bullets[i].x &&
						badGuy[bSize].y - badGuy[bSize].borderY < bullets[i].y &&
						badGuy[bSize].y + badGuy[bSize].borderY > bullets[i].y &&
						bSize != CONST_ZERO)
					{
						goto bossGotHit;
					}

					
				}
			}
		}
	}

	//
	//============================================================
	//
	// COLISÃO ENTRE JOGADOR E PROJÉTEIS DO BOSS (CHEFÃO) DO JOGO
	//
	//============================================================
	//

	for (int i = 0; i < BOSS_NUM_BULLETS; i++)
	{
		if (projectiles[i].alive == true){
			if (projectiles[i].x > (ship.x - ship.boundX) 
				&& projectiles[i].x < (ship.x + ship.boundX)
				&& projectiles[i].y > (ship.y - ship.boundY)
				&& projectiles[i].y < (ship.y + ship.boundY))
			{
				if (ship.state != PLAYER_INVULNERABLE){
					projectiles[i].alive = false;
					ship.lives--;
					al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
					ship.state = PLAYER_INVULNERABLE;
				}
			}
		}
	}
	//else if (ship.currWeapon >= DOUBLE_SHOT){

	//}
}

void CollideComet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		if (comets[i].alive == true)
		{
			if ( comets[i].x - comets[i].boundX < ship.x + ship.boundX &&
				comets[i].x + comets[i].boundX > ship.x - ship.boundX &&
				comets[i].y - comets[i].boundY < ship.y + ship.boundY &&
				comets[i].y + comets[i].boundY > ship.y - ship.boundY )
			{
				// HÁ UM COLISÃO ENTRE NAVE E COMETA
				ship.lives--;
				comets[i].alive = false;
			}
		}
	}
}

void CollideProjectile(int obj1, int obj2)
{
	// COLISÃO ENTRE JOGADOR E PROJÉTIL DO HELICÓPTERO

	for (int i = 0; i < NUM_COPTERS; i++)
	{
		for (int j = 0; j < COPTER_NUM_BULLETS; j++)
		{
			if (projs[i][j].alive)
			{
				// ENTROU AQUI <-----------------------------------------
				if (ship.x - ship.boundX < projs[i][j].x
					&& ship.y - ship.boundY < projs[i][j].y
					&& ship.x + ship.boundX > projs[i][j].x
					&& ship.y + ship.boundY > projs[i][j].y)
				{
					if (ship.state != PLAYER_INVULNERABLE){
						ship.lives--;
						al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
						ship.state = PLAYER_INVULNERABLE;
						projs[i][j].alive = false;
					} 
				}
			}
		}
	}
}

void Comet_InitBullet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		for (int j = 0; j < COMET_NUM_BULLETS; j++)
		{
			comets[i].shots[j].ID = BULLET;
			comets[i].shots[j].alive = false;
			comets[i].shots[j].speed = COMET_BULLET_SPEED;
			comets[i].shots[j].x = comets[i].x;
			comets[i].shots[j].y = comets[i].y;
		}
	}
}

void Comet_DrawBullet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		//if (comets[i].alive == true)
		//{
			for (int j = 0; j < COMET_NUM_BULLETS; j++)
			{
				if (comets[i].shots[j].alive == true)
				{
					al_draw_filled_circle(comets[i].shots[j].x, comets[i].shots[j].y, COMET_BULLET_RADIUS, al_map_rgb(255, 0, 0));
				}
			}
		//}
	}
}

void Comet_FireBullet()
{
	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		if (comets[i].alive == true)
		{
			for (int j = 0; j < COMET_NUM_BULLETS; j++)
			{
				if (comets[i].shots[j].alive == false && comets[i].isFiringBullets == false)
				{
					comets[i].shots[j].x = comets[i].x;
					comets[i].shots[j].y = comets[i].y;
					

					comets[i].shots[j].originX = comets[i].shots[j].x;
					comets[i].shots[j].originY = comets[i].shots[j].y;
					comets[i].shots[j].shipX = ship.x;
					comets[i].shots[j].shipY = ship.y;

					comets[i].shots[j].angle = AngleToTarget(comets[i].shots[j].originX,
															comets[i].shots[j].originY,
															comets[i].shots[j].shipX, 
															comets[i].shots[j].shipY);

					comets[i].shots[j].alive = true;

					al_draw_line(comets[i].shots[j].originX, comets[i].shots[j].originY, 
						comets[i].shots[j].shipX, comets[i].shots[j].shipY, 
						al_map_rgb(255, 0, 0), 1);

					break;
				}
			}
		}
	}
}

void Comet_UpdateBullet()
{

	for (int i = 0; i < MAX_NUM_COMETS; i++)
	{
		if (comets[i].alive == true)
		{
			for (int j = 0; j < COMET_NUM_BULLETS; j++)
			{
				if (comets[i].shots[j].alive == true)
				{
					// APENAS ATUALIZAR PROJETEIS ATIVOS DE COMETAS ATIVOS
					comets[i].shots[j].x += COMET_BULLET_SPEED * cos(comets[i].shots[j].angle);
					comets[i].shots[j].y += COMET_BULLET_SPEED * sin(comets[i].shots[j].angle);

					if (comets[i].shots[j].x < 0 ||
						comets[i].shots[j].y < 0 ||
						comets[i].shots[j].x > SCREEN_WIDTH ||
						comets[i].shots[j].y > SCREEN_HEIGHT)
					{
						comets[i].shots[j].alive = false;

					}

					if (comets[i].isFiringBullets == true)
					{
						comets[i].currentFrame++;

						if (comets[i].currentFrame >= comets[i].waitingFrame)
						{
							//comets[i].isFiringBullets = false;
							//comets[i].currentFrame = 0;
						}
					}

				}
			}
		}
	}
}
//void Comet_CollideBullet();

double AngleToTarget(double x1, double y1, double x2, double y2)
{
	if (x1 == x2 || y1 == y2)	return -1;

	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	double result = std::atan2(deltaY, deltaX);

	return result;
}

double CheckDistance(double x1, double y1, double x2, double y2)
{
	return sqrt( pow( (double)x1 - x2, 2 ) + pow( (double)y1 - y2, 2 ) );
}

/*

double angle = AngleToTarget(badx, bady, playerx, playery);
bady += (speed * sin(angle));
badx += (speed * cos(angle));

*/

//void InitBullet2();
//void DrawBullet2();

void FireBullet2()
{
	int i, j, k, m;
	i = j = k = m = 0;

	if (ship.currWeapon >= SINGLE_SHOT){
		for (i = 0; i < PLAYER_NUM_BULLETS; i++){
			if (bullets[i].alive == false){

				if (ship.image == NULL || ship.image == nullptr)
				{
					bullets[i].x = ship.x + 20;
					bullets[i].y = ship.y;
				}
				else
				{
					bullets[i].x = ship.x + BULLET_START_X;
					bullets[i].y = ship.y + BULLET_START_Y;
				}
				bullets[i].alive = true;
				bullets[i].bulletDirection = ship.playerDirection;
				//break;

				ship.isFiringBullets = true;

				FireProjectile(0);
				
				al_play_sample(shot, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
		}
	}
	

	if (ship.currWeapon >= DOUBLE_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[0][j].alive == false){
				b[0][j].x = ship.x + 10;
				b[0][j].y = ship.y;
				b[0][j].alive = true;
				b[0][j].bulletDirection = ship.playerDirection;
				b[0][j].speed = PLAYER_BULLET_SPEED;	//break;
			//ship.isFiringBullets = true;
			j++;
			//b[0][j].isFiringBullets = true;
				if (b[0][j].alive == false){
					b[0][j].x = ship.x + 10;
					b[0][j].y = ship.y;
					b[0][j].alive = true;
					b[0][j].bulletDirection = ship.playerDirection;
					b[0][j].speed = PLAYER_BULLET_SPEED;
				}
			//ship.isFiringBullets = true;
			break;
			}
		}
	}

	if (ship.currWeapon >= TRIPLE_SHOT){
		for (k = 0; k < PLAYER_NUM_BULLETS; k++){
			if (b[1][k].alive == false){
				b[1][k].x = ship.x + 8;
				b[1][k].y = ship.y;
				b[1][k].alive = true;
				b[1][k].bulletDirection = ship.playerDirection;
				b[1][k].speed = PLAYER_BULLET_SPEED;	//break;
				//ship.isFiringBullets = true;
				k++;
				//b[0][j].isFiringBullets = true;
				if (b[1][k].alive == false){
					b[1][k].x = ship.x + 8;
					b[1][k].y = ship.y;
					b[1][k].alive = true;
					b[1][k].bulletDirection = ship.playerDirection;
					b[1][k].speed = PLAYER_BULLET_SPEED;
				}
				//ship.isFiringBullets = true;
				break;
			}
		}
	}

	if (ship.currWeapon >= BACK_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (!b[2][j].alive){
				b[2][j].bulletDirection = ship.playerDirection;
				b[2][j].speed = -PLAYER_BULLET_SPEED;
				b[2][j].x = ship.x - 5;
				b[2][j].y = ship.y;
				b[2][j].alive = true;

				break;
			}
		}
	}

	if (ship.currWeapon >= FULL_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[3][j].alive == false){
				b[3][j].x = ship.x + 5;
				b[3][j].y = ship.y;
				b[3][j].alive = true;
				b[3][j].bulletDirection = ship.playerDirection;
				b[3][j].speed = PLAYER_BULLET_SPEED;	//break;
				//ship.isFiringBullets = true;

				
				j++;
				
				if (b[3][j].alive == false){
					b[3][j].x = ship.x + 5;
					b[3][j].y = ship.y;
					b[3][j].alive = true;
					b[3][j].bulletDirection = ship.playerDirection;
					b[3][j].speed = PLAYER_BULLET_SPEED;
				}
				break;
			}
		}
	}

	if (ship.currWeapon >= TEST_WEAPON){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[4][j].alive == false){
				b[4][j].x = ship.x;
				b[4][j].y = ship.y;
				b[4][j].alive = true;
				b[4][j].bulletDirection = ship.playerDirection;
				b[4][j].speed = PLAYER_BULLET_SPEED;

				ship.isFiringBullets = true;

				break;
			}
		}
	}

	if (ship.currWeapon >= MACHINE_GUN_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS * 2; j = j + 2){
			if (b[5][j].alive == false){
				b[5][j].x = ship.x + 15;
				b[5][j].y = ship.y + 10;
				b[5][j].alive = true;
				b[5][j].bulletDirection = ship.playerDirection;
				b[5][j].speed = PLAYER_BULLET_SPEED;

				j++;

				if (b[5][j].alive == false){
					b[5][j].x = ship.x + 15;
					b[5][j].y = ship.y - 10;
					b[5][j].alive = true;
					b[5][j].bulletDirection = ship.playerDirection;
					b[5][j].speed = PLAYER_BULLET_SPEED;
				}

				ship.isFiringBullets = true;

				break;
			}
		}
	}

}

void UpdateBullet2()
{
	int i, j; i = j = 0;
	int k, l, m; k = l = m = 0;
	double radians;

	if (ship.isFiringBullets == true){
		ship.currentFrame++;

		if (ship.currentFrame >= ship.waitingFrame){
			ship.isFiringBullets = false;
			ship.currentFrame = 0;
		}
	}
	for (i = 0; i < PLAYER_NUM_BULLETS; i++){
		if (ship.currWeapon >= SINGLE_SHOT){
			if (bullets[i].alive == true){
				bullets[i].x += bullets[i].speed;
				//break;
				if (bullets[i].x > SCREEN_WIDTH ||
					bullets[i].y > SCREEN_HEIGHT ||
					bullets[i].x < 0 ||
					bullets[i].y < 0)
				{
					bullets[i].alive = false;
				}
			}
		}
	}

	if (ship.currWeapon >= DOUBLE_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[0][j].alive){
				b[0][j].y -= (std::sin(45) * b[0][j].speed);
				b[0][j].x += (std::cos(45) * b[0][j].speed);
			}
				j++;
			if (b[0][j].alive){
				b[0][j].y += (std::sin(315) * b[0][j].speed);
				b[0][j].x += (std::cos(315) * b[0][j].speed);
			}
		}
	}

	if (ship.currWeapon >= DOUBLE_SHOT){
		for (k = 0; k < PLAYER_NUM_BULLETS; k++){
			if (b[0][k].alive){
				if (b[0][k].x > SCREEN_WIDTH ||
					b[0][k].x < 0 ||
					b[0][k].y < 0 ||
					b[0][k].y > SCREEN_HEIGHT)
				{
					b[0][k].alive = false;
				}
			}
		}
	}

	if (ship.currWeapon >= TRIPLE_SHOT){
		for (k = 0; k < PLAYER_NUM_BULLETS; k++){
			if (b[1][k].alive){
				b[1][k].y -= b[1][k].speed;
			}

			k++;

			if (b[1][k].alive){
				b[1][k].y += b[1][k].speed;
			}
		}
	}

	if (ship.currWeapon >= TRIPLE_SHOT){
		for (k = 0; k < PLAYER_NUM_BULLETS; k++){
			if (b[1][k].alive){
				if (b[1][k].x > SCREEN_WIDTH ||
					b[1][k].x < 0 ||
					b[1][k].y < 0 ||
					b[1][k].y > SCREEN_HEIGHT)
				{
					b[1][k].alive = false;
				}
			}
		}
	}

	if (ship.currWeapon >= BACK_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[2][j].alive){
				b[2][j].x += b[2][j].speed;

				if (b[2][j].x > SCREEN_WIDTH ||
					b[2][j].y > SCREEN_HEIGHT ||
					b[2][j].x < 0 ||
					b[2][j].y < 0)
				{
					b[2][j].alive = false;
				}

			}
		}
	}

	radians = (double) ( (double) PI / (double) 180.00 ) * 135;

	if (ship.currWeapon >= FULL_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[3][j].alive){
				b[3][j].y -= (std::sin(30) * b[3][j].speed);
				b[3][j].x += (std::cos(30) * b[3][j].speed);
			}
			
			j++;

			radians = (double)((double)PI / (double) 180.00) * 230;

			if (b[3][j].alive){
				b[3][j].y += (std::sin(330) * b[3][j].speed);
				b[3][j].x += (std::cos(330) * b[3][j].speed);
			}
			
		}
	}

	if (ship.currWeapon >= FULL_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[3][j].alive){
				if (b[3][j].x > SCREEN_WIDTH ||
					b[3][j].y > SCREEN_HEIGHT ||
					b[3][j].x < 0 ||
					b[3][j].y < 0)
				{
					b[3][j].alive = false;
				}
			}
		}
	}

	if (ship.currWeapon >= TEST_WEAPON){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[4][j].alive){

				b[4][j].x += ( std::cos( fromDegreesToRadians(ship.cosine) ) * b[4][j].speed );
				b[4][j].y += ( std::sin( fromDegreesToRadians(ship.sine) ) * b[4][j].speed );

				if (b[4][j].x > SCREEN_WIDTH ||
					b[4][j].y > SCREEN_HEIGHT ||
					b[4][j].x < 0 ||
					b[4][j].y < 0)
				{
					b[4][j].alive = false;
				}
			}
		}
	}

	if (ship.currWeapon >= MACHINE_GUN_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (b[5][j].alive){
				b[5][j].x += b[5][j].speed;
			}

			j++;

			if (b[5][j].alive){
				b[5][j].x += b[5][j].speed;
			}
		}
	}

	if (ship.sine < 0){
		ship.sine = 0;
	}
	if (ship.sine > 360){
		ship.sine = 360;
	}
	if (ship.cosine < 0){
		ship.cosine = 0;
	}
	if (ship.cosine > 360){
		ship.cosine = 360;
	}

}
//void CollideBullet2();

void CameraUpdate(int width, int height)
{
	cameraPosition[0] = -(SCREEN_WIDTH / 2) + (ship.x + width / 2);
	cameraPosition[1] = -(SCREEN_HEIGHT / 2) + (ship.y + height / 2);

	if (cameraPosition[0] < 0)
	{
		cameraPosition[0] = 0;
	}
	if (cameraPosition[1] < 0)
	{
		cameraPosition[1] = 0;
	}
}

void ZoomOut()
{
	scale -= 0.1f;
}

void ZoomIn()
{
	scale += 0.1f;
}

void ResetZoomingScale()
{
	scale = 1.0f;
}

void DrawMap()
{
	for (unsigned int i = 0; i < level.maplevel.size(); i++)
	{
		for (unsigned int j = 0; j < level.maplevel[i].size(); j++)
		{
			if (level.maplevel[i][j] == 0)
			{
				al_draw_filled_rectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
					j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE,
					al_map_rgb(0, 0, 255));

				al_draw_textf(font18, al_map_rgb(255, 255, 255), j * BLOCK_SIZE, i * BLOCK_SIZE, 0, "%d,%d", i, j );
			}
			else 
			{
				al_draw_filled_rectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
					j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE,
					al_map_rgb(0, 255, 0));

				al_draw_textf(font18, al_map_rgb(255, 0, 255), j * BLOCK_SIZE, i * BLOCK_SIZE, 0, "%d,%d", i, j);
			}
		}
	}
}

void LoadMap()
{
	std::ifstream filename("assets/map.txt");
	
	std::string line;
	
	if (filename.is_open())
	{
		level.numColumns = level.numRows = 0;
		// LER ARQUIVO LINHA POR LINHA
		while (std::getline(filename, line))
		{
			std::vector<int> lineData;
			std::stringstream lineStream(line);
			int value;
			// LER UM INTEIRO POR VEZ
			while (lineStream >> value)
			{
				// ADICIONAR INTEIROS DO ARQUIVO PARA UMA VARIÁVEL OU ESTRUTURA DE DADOS VIRTUAL
				lineData.push_back(value);
			}
			// QUANDO ACABAR DE LER TODOS OS INTEIROS, ADICIONAR O ARRAY 1D EM UM ARRAY 2D
			level.maplevel.push_back(lineData);
		}
		for (unsigned int i = 0; i < level.maplevel.size(); i++)
		{
			for (unsigned int j = 0; j < level.maplevel[i].size(); j++)
			{
				//std::cout << map.maplevel.at(i).at(j) << " ";
				std::cout << level.maplevel[i][j] << " ";
			}
			std::cout << std::endl;
		}
		filename.close();
		//getchar();
	}
	else
	{
		//std::cout << "Arquivo fechado!" << std::endl;

		return;
	}
}

void LoadMap2()
{
	std::ifstream mapfile("assets/map.txt");
	int maptileid, mapsizex, mapsizey;

	mapsizex = mapsizey = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			level.mapfile[i][j] = -1;
		}
	}

	if (mapfile.is_open())
	{
		//std::cout << "SUCESSO AO ABRIR MAPA!" << std::endl;

		mapfile >> maptileid;

		while (mapfile.good())
		{
			level.mapfile[mapsizex][mapsizey] = maptileid;
			
			if (mapsizey >= 10)
			{
				mapsizey = 0;
				mapsizex++;
				//std::cout << std::endl;
			}
			if (mapsizex >= 10)
			{
				mapsizex = 0;
				break;
			}

			mapsizey++;
			mapfile >> maptileid;
		}
		mapfile.close();
		
	}
	else
	{
		//std::cout << "ERRO AO ABRIR MAPA!" << std::endl;
	}
}

void DrawMap2()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (level.mapfile[i][j] == 0)
			{
				al_draw_rectangle(j * BLOCK_SIZE, i * BLOCK_SIZE, 
					j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, 
					al_map_rgb(127, 127, 127), 2);

				al_draw_filled_rectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
					j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE,
					al_map_rgb(255, 0, 0));
			}
			else
			{
				al_draw_filled_rectangle(j * BLOCK_SIZE, i * BLOCK_SIZE,
					j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE,
					al_map_rgb(0, 255, 0));
			}
			al_draw_textf(font18, al_map_rgb(255, 255, 255), j * BLOCK_SIZE, i * BLOCK_SIZE, 0, "(%d,%d)", i, j);
		}
	}
}

void LoadMapFromTextFile()
{
	// TILED MAP FILE PARSING
	FILE *fptr;
	int i, j;
	i = j = 0;

	printf("ENTROU NA FUNÇÃO DE LEITURA DE ARQUIVOS!\n");

	fptr = fopen("assets\\map_ansi.txt", "r");

	if (fptr == NULL || fptr == nullptr)	return;

	char single[2];

	while ((single[0] = fgetc(fptr)) != EOF)
	{
		//printf("%c", single[0]);

		level.mapfile[i][j] = atoi(single);
		//printf("%i ", map.mapfile[i][j]);

		if (i > 10)
		{
			j++;
			i = 0;
			//printf("\n");
		}
		i++;

	}

	//printf("CARACTERE LIDO = %c\n", single);

	fclose(fptr);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%d ", level.mapfile[i][j]);
		}
		printf("\n");
	}

}

void LoadMapFromMemory()
{
	// CARREGAR O MAPA A PARTIR DE UMA ESTRUTURA DE DADOS (EX.: ARRAY, VETOR, MATRIZ, LISTA, ETC...) GUARDADA NA MEMÓRIA
	
}

bool LoadTileMap_Easy(const char *filename)
{
	std::ifstream openfile(filename);

	if (openfile.is_open())
	{

		ptrMap.loadCounterX = ptrMap.loadCounterY = 0;
		ptrMap.mapSizeX = ptrMap.mapSizeY = 0;

		openfile >> ptrMap.mapSizeX >> ptrMap.mapSizeY;

		while (!openfile.eof())
		{
			openfile >> ptrMap.map[ptrMap.loadCounterX][ptrMap.loadCounterY];

			ptrMap.loadCounterX++;

			if (ptrMap.loadCounterX >= ptrMap.mapSizeX)
			{
				ptrMap.loadCounterX = 0;
				ptrMap.loadCounterY++;
			}



		}

	}
	else
	{

	}

	return true;
}

void DrawTileMap_Easy()
{
	// DESENHA O MAPA DA ESTRUTURA DE DADOS "PTRMAP"

	for (int i = 0; i < ptrMap.mapSizeX; i++)
	{
		for (int j = 0; j < ptrMap.mapSizeY; j++)
		{
			if (ptrMap.map[i][j] == 0)
			{
				al_draw_filled_rectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, 
					i * BLOCK_SIZE + BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, 
					al_map_rgb(255, 0, 255));
			}
			else
			{
				al_draw_filled_rectangle(i * BLOCK_SIZE, j * BLOCK_SIZE,
					i * BLOCK_SIZE + BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE,
					al_map_rgb(255, 255, 255));
			}
		}
	}
}

void LoadTileMap_Advanced(const char*filename, std::vector< std::vector<int> > &map)
{
	std::ifstream openfile(filename);
	int state;
	tileset = NULL;

	if (openfile.is_open())
	{

		std::string line, value;

		//int space;

		while (!openfile.eof())
		{

			std::vector<int> tempVector;

			std::getline(openfile, line);
			std::stringstream str(line);

			if (line.find("[tileset]") != std::string::npos)
			{
				state = TILESET;
				continue;
			}
			else if (line.find("[map]") != std::string::npos)
			{
				state = MAP;
				continue;
			}

			switch (state)
			{
			case TILESET:
				if (line.length() > 0)
					tileset = al_load_bitmap(line.c_str());

				break;

			case MAP:

				while (!str.eof())
				{
					std::getline(str, value, ' ');
					if (value.length() > 0)
					{
						tempVector.push_back(atoi(value.c_str()));
					}
				}
				level.maplevel.push_back(tempVector);

				break;

			default: break;

			}

		}

	}

}

void DrawTileMap_Advanced()
{
	for (unsigned int i = 0; i < level.maplevel.size(); i++)
	{
		for (unsigned int j = 0; j < level.maplevel[i].size(); j++)
		{
			al_draw_bitmap_region(tileset,
				level.maplevel[i][j] * BLOCK_SIZE, 0, 
				BLOCK_SIZE, BLOCK_SIZE, 
				j * BLOCK_SIZE, i * BLOCK_SIZE, 0);
		}
	}
}

bool LoadMatrix()
{
	room.mapColumns = 10;
	room.mapRows = 10;
	room.tileSize = BLOCK_SIZE;
	room.blockSize = room.tileSize;
	int value = -1;

	
	for (int i = 0; i < room.mapColumns; i++)
	{
		for (int j = 0; j < room.mapRows; j++)
		{
			value = rand() % 5;
			room.map[i][j] = value;
		}
	}

	for (int i = 0; i < room.mapColumns; i++)
	{
		for (int j = 0; j < room.mapRows; j++)
		{
			//std::cout << room.map[i][j] << " ";
		}
		//std::cout << std::endl;
	}

	return true;
}
//bool DrawMatrix();
//bool UpdateMatrix();

void CenterCharacterPosition(int ID, double x, double y, int width, int height)
{

}

void ChangeState(int newState)
{
	//
	// PRÉ-PROCESSAMENTO DOS ESTADOS DE JOGO
	//

	PreProcessingTheState();

	state = newState;

	//
	// PÓS-PROCESSAMENTO DOS ESTADOS DE JOGO
	//

	PostProcessingTheState();
}

void PreProcessingTheState()
{
	if (state == TITLE)
	{
		//menu.selected = 0;
		//menu.options = 6;
		//std::cout << "SAINDO DO TITLE" << std::endl;
		endingFrames = 0;
		
	}
	else if (state == PLAYING)
	{
		//std::cout << "ENTRANDO NO JOGADOR" << std::endl;
		//InitLevel();
	}
	else if (state == LOST)
	{
		//InitEverything();
	}
	else if (state == CONTROLS)
	{
		
	}
	else if (state == OPTIONS)
	{

	}
	else if (state == GAME_EXIT){
		isGameLoopDone = true;
	}
	else if (state == TRANSITION)
	{
		//std::cout << "ENTROU NO ESTADO PREPARAÇÃO!" << std::endl;
	}
	else if (state == PAUSING)
	{
		
	}
	else if (state == QUITTING_EVERYTHING)
	{
		//std::cout << "QUITTING EVERYTHING <-----------------" << std::endl;
		//al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else if (state == QUITTING_GAMEPLAY)
	{
		//std::cout << "QUITTING GAMEPLAY ==================>" << std::endl;
		//al_play_sample(heart, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
		
		
	}
	else if (state == QUIT_EVERYTHING)
	{

	}
	else if (state == QUIT_GAMEPLAY)
	{

	}
	else if (state == ENDING)
	{
		// PRE-PROCESSING THE ENDING STATE
		//std::cout << "RIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDGE RACER!" << std::endl;
		if (endingFrames > CONST_ONE) InitEverything();
	}
}

void PostProcessingTheState()
{
	//menu.selected = 0;

	if (state == TITLE)
	{
		menu.selected = 0;
		menu.options = TITLE_NUM_COMMANDS;

		//std::cout << "POST PROCESSING TITLE" << std::endl;

		gameplay.currentFrame = 0;
		gameplay.currentFrame2 = 0;
		stage.levelNumber = CURRENT_LEVEL;
		gameplay.currentLevel = stage.levelNumber;
		stage.nextLevel = NEXT_LEVEL;
		gameplay.bossFrame = 0;

		al_stop_sample_instance(lostSong);	al_stop_sample_instance(bossInstance);	al_stop_sample_instance(endingInstance);
		al_stop_sample_instance(stage1); al_stop_sample_instance(stage2);
		if (titleInstance != NULL)	al_play_sample_instance(titleInstance);

		fade = 0;
	}
	else if (state == PLAYING)
	{
		//InitFading();
		InitLevel();
		if (stage.nextLevel == LEVEL01 && stage.levelNumber == LEVEL00)
		{

		}
		else if (stage.nextLevel == LEVEL02 && stage.levelNumber == LEVEL01)
		{
			//std::cout << "SAAKSLASMLMASKL PROCESSING TITLE" << std::endl;
			al_stop_sample_instance(lostSong);	al_stop_sample_instance(bossInstance);	al_stop_sample_instance(endingInstance);
			al_stop_sample_instance(titleInstance); al_stop_sample_instance(stage2);
			if (stage1 != NULL)	al_play_sample_instance(stage1);
		}
		else if (stage.nextLevel == LEVEL03 && stage.levelNumber == LEVEL02)
		{
			//std::cout << "SAAKSLASMLMASKL PROCESSING TITLE" << std::endl;
			al_stop_sample_instance(lostSong);	al_stop_sample_instance(bossInstance);	al_stop_sample_instance(endingInstance);
			al_stop_sample_instance(titleInstance); al_stop_sample_instance(stage1);
			if (stage1 != NULL)	al_play_sample_instance(stage2);
		}

		PC.backgroundMusicVolume = BGMVolume;
	}
	else if (state == LOST)
	{
		//StartExplosion(ship.x, ship.y, 0);
		al_stop_sample_instance(stage1);	al_stop_sample_instance(bossInstance);	al_stop_sample_instance(endingInstance);
		al_stop_sample_instance(titleInstance); al_stop_sample_instance(stage2);

		if (lostSong != NULL && isSongPlaying == false)
		{
			isSongPlaying = true;
			al_play_sample_instance(lostSong);
		}

	}
	else if (state == CONTROLS)
	{
		menu.selected = 0;
		menu.options = 10;
	}
	else if (state == OPTIONS)
	{

	}
	else if (state == GAME_EXIT){
		menu.selected = 0;
		//DestroyAssets();
		isGameLoopDone = true;
	}
	else if (state == TRANSITION)
	{
		//std::cout << "SAIU DO ESTADO PREPARAÇÃO!" << std::endl;
		InitFading();
		//InitLevel();
	}
	else if (state == PAUSING)
	{
		//printf("\tENTROU NO ESTADO PAUSE! YOU ENTERED THE PAUSE STATE!\n\n");
		menu.selected = 0;
		menu.options = PAUSING_NUM_COMMANDS;
		BGMVolume = PC.backgroundMusicVolume;
	}
	else if (state == QUITTING_EVERYTHING ||
		state == QUITTING_GAMEPLAY)
	{
		menu.selected = 0;
		menu.options = CONFIRMATION_NUM_COMMANDS;
	}
	else if (state == QUIT_EVERYTHING || state == QUIT_GAMEPLAY)
	{
		menu.selected = 0;
		menu.options = CONFIRMATION_NUM_COMMANDS;
	}
	else if (state == ENDING)
	{
		//std::cout << "post-processing the state ENDING!!!!!!!!!!!!!!!!!!!!" << std::endl;
		gameplay.currentFrame = 0;
		gameplay.currentFrame2 = 0;
		stage.levelNumber = LEVEL03;
		gameplay.currentLevel = stage.levelNumber;
		al_stop_sample_instance(lostSong);	al_stop_sample_instance(bossInstance);	al_stop_sample_instance(titleInstance);
		al_stop_sample_instance(stage1); al_stop_sample_instance(stage2);
		if (endingInstance != NULL)	al_play_sample_instance(endingInstance);

		if(endingFrames > CONST_ONE) InitEverything();
		endingFrames = 0;
		//InitEverything();
	}
}

void CurrentState()
{
	if (state == TITLE)
	{
		
	}
	else if (state == PLAYING)
	{

	}
	else if (state == PASSWORD)
	{

	}
	else if (state == CREDITS)
	{

	}
	else if (state == OPTIONS)
	{

	}
	else if (state == TRANSITION)
	{

	}
	else if (state == SETTING_AUDIO)
	{

	}
	else if (state == QUITTING_EVERYTHING)
	{

	}
	else if (state == QUITTING_GAMEPLAY)
	{

	}
}

void TitleScreen()
{

	ALLEGRO_COLOR unselected = al_map_rgb(0, 234, 0);
	ALLEGRO_COLOR selected = al_map_rgb(234, 0, 0);

	ALLEGRO_BITMAP *subBitmap = NULL;
	subBitmap = al_create_sub_bitmap(titleButtons, 96 * 4, 0, 96, 96 / 2);

	if (titleImage != NULL && titleImage != nullptr){
		al_draw_bitmap(titleImage, 0, 0, NULL);

		if (titleButtons != NULL && titleButtons != nullptr){
			// START NEW GAME
			//al_draw_tinted_bitmap_region(titleButtons, unselected, 96 * 4, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5, NULL);

			// DRAW USING BITMAP FONT FILES
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .56, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
			//al_draw_tinted_bitmap(subBitmap, unselected, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5, NULL);

			if (menu.selected == 0)
			{	//al_draw_tinted_bitmap_region(titleButtons, selected, 96 * 4, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .56, SCREEN_HEIGHT * .5, 0.35, 0.35, 0.0, NULL);
			}

			// LOAD SAVED GAME

			/*
			//al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(0, 200, 0), 96 * 5, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);

			if (menu.selected == -9)
			{ //al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(255, 0, 0), 96 * 5, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .58, 0.35, 0.35, 0.0, NULL);
			}
			*/

			// SETUP GAME OPTIONS
			//al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(0, 200, 0), 96 * 6, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48 * 2, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 7, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .56, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);

			if (menu.selected == 1)
			{ //al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(255, 0, 0), 96 * 6, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48 * 2, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 7, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .56, SCREEN_HEIGHT * .66, 0.35, 0.35, 0.0, NULL);
			}

			// INPUT GAME OPTIONS

			/*
			//al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(0, 200, 0), 96 * 2, 96 * 5, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48 * 3, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 7, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .56, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);

			if (menu.selected == -99)
			{ //al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(255, 0, 0), 96 * 2, 96 * 5, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48 * 3, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 5, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 7, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .56, SCREEN_HEIGHT * .74, 0.35, 0.35, 0.0, NULL);
			}
			*/

			// QUIT GAME OPTIONS
			//al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(0, 200, 0), 96 * 7, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48 * 4, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);

			if (menu.selected == 2)
			{ //al_draw_tinted_bitmap_region(titleButtons, al_map_rgb(255, 0, 0), 96 * 7, 0, 96, 96 / 2, SCREEN_WIDTH * .5 - 96 / 2, SCREEN_HEIGHT * .5 + 48 * 4, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					0, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .44, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .48, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
				al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
					96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .52, SCREEN_HEIGHT * .82, 0.35, 0.35, 0.0, NULL);
			}
		}

		al_draw_tinted_scaled_bitmap(
			titleLogo, 
			al_map_rgb(255, 255, 0), 
			0, 0,
			al_get_bitmap_width(titleLogo), al_get_bitmap_height(titleLogo),
			SCREEN_WIDTH * .1, SCREEN_HEIGHT * .025,
			al_get_bitmap_width(titleLogo) * .85, al_get_bitmap_height(titleLogo) * .85,
			NULL
			);
		
	}

	//al_draw_tinted_bitmap(fader, al_map_rgba(0, 0, 0, fade), 0, 0, NULL);

	if (subBitmap != NULL && subBitmap != nullptr)
	{
		al_destroy_bitmap(subBitmap);
		subBitmap = NULL;
	}

}

void OptionsScreen()
{
	ALLEGRO_COLOR unselected = al_map_rgb(0, 234, 0);
	ALLEGRO_COLOR selected = al_map_rgb(234, 0, 0);
	ALLEGRO_COLOR speakers = al_map_rgb(234, 0, 234);

	if (state == OPTIONS)
		al_draw_bitmap(titleImage, 0, 0, NULL);

	if (state == OPTIONS)
	{
		al_draw_tinted_scaled_rotated_bitmap_region(
			menuTitles,
			96 * 3, 96, 96 * 5, 96,
			al_map_rgb(MAX_RGB_VALUE, MAX_RGB_VALUE, MAX_RGB_VALUE),
			1, 1,
			SCREEN_WIDTH * 0.225, SCREEN_HEIGHT * 0.035,
			1, 1, 0, NULL
			);
	}
	else if (state == SETTING_AUDIO)
	{
		// "SETUP" WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 2, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 3, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96, 96, 96, color_white, CONST_ONE, CONST_ONE, SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING
			* 4, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);

		// "AUDIO" WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 5.75, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 6.75, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 0, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 7.75, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 96, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 8.75, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * SETUP_START_X + SETUP_LETTER_SPACING * 9.75, SCREEN_HEIGHT * SETUP_START_Y, CONST_ONE, CONST_ONE, 0, NULL);
	}

	// OPÇÃO "BACKGROUND MUSIC VOLUME" - VOLUME DA MÚSICA DE FUNDO
	if (menu.selected == 0)
	{ //al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 4, ALLEGRO_ALIGN_RIGHT, setupMenuItems[3]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 5, OPTIONS_MENU_SPACING * 3.95, ALLEGRO_ALIGN_RIGHT,
			" %.2f ", PC.backgroundMusicVolume);

		//DrawFontNumber(PC.backgroundMusicVolume, SCREEN_WIDTH * 0.50 + OPTIONS_MENU_SPACING * 4, OPTIONS_MENU_SPACING * 4.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 96, 96);

		// "B.G.M." WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 1, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.175, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.20, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.225, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.275, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		// "VOLUME" WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}
	else
	{ //al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 4, ALLEGRO_ALIGN_RIGHT, setupMenuItems[3]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 5, OPTIONS_MENU_SPACING * 3.95, ALLEGRO_ALIGN_RIGHT,
			" %.2f ", PC.backgroundMusicVolume);

		// "B.G.M." WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 1, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.175, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.20, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.225, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.275, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		// "VOLUME" WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * 0.25, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}

	if (menu.selected == 1)
	{ 
		//al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 6, ALLEGRO_ALIGN_RIGHT, setupMenuItems[4]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 5, OPTIONS_MENU_SPACING * 5.70, ALLEGRO_ALIGN_RIGHT,
			" %.2f ", PC.soundEffectVolume);

		// "S.F.X." WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.175, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.20, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.225, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.275, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		// "VOLUME" WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

	}
	else
	{ //al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 6, ALLEGRO_ALIGN_RIGHT, setupMenuItems[4]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 5, OPTIONS_MENU_SPACING * 5.70, ALLEGRO_ALIGN_RIGHT,
			" %.2f ", PC.soundEffectVolume);

		// "S.F.X." WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.175, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.20, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.225, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.275, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		// "VOLUME" WORD
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * 0.35, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

	}

	/*
	if (menu.selected == 2)
	{ //al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 8, ALLEGRO_ALIGN_RIGHT, setupMenuItems[5]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 5, OPTIONS_MENU_SPACING * 7.35, ALLEGRO_ALIGN_RIGHT,
			" %02d ", PC.gameTune);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.19, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.27, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.31, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.39, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}
	else
	{ //al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 8, ALLEGRO_ALIGN_RIGHT, setupMenuItems[5]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 5, OPTIONS_MENU_SPACING * 7.35, ALLEGRO_ALIGN_RIGHT,
			" %02d ", PC.gameTune);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.19, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.27, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.31, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.39, SCREEN_HEIGHT * 0.45, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}
	*/

	if (menu.selected == 2)
	{ //al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 10, ALLEGRO_ALIGN_RIGHT, setupMenuItems[6]);

		// "SOUND PAN" EXPRESSION
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.19, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.27, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.31, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.39, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.43, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.47, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		if (PC.soundPan < 0)
		{
			al_draw_textf(fontSelected, speakers, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 7, OPTIONS_MENU_SPACING * 8.90, ALLEGRO_ALIGN_RIGHT,
				" %.1f (LEFT)", PC.soundPan);
		}
		else if (PC.soundPan > 0)
		{
			al_draw_textf(fontSelected, speakers, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 7, OPTIONS_MENU_SPACING * 8.90, ALLEGRO_ALIGN_RIGHT,
				" %.1f (RIGHT)", PC.soundPan);
		}
		else if (PC.soundPan == 0.0)
		{
			al_draw_textf(fontSelected, speakers, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 7, OPTIONS_MENU_SPACING * 8.90, ALLEGRO_ALIGN_RIGHT,
				" %.1f (BOTH)", PC.soundPan);
		}
		
	}
	else
	{ //al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 10, ALLEGRO_ALIGN_RIGHT, setupMenuItems[6]);

		// "SOUND PAN" EXPRESSION
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.19, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.27, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.31, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.39, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.43, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.47, SCREEN_HEIGHT * 0.55, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		if (PC.soundPan < 0)
		{
			al_draw_textf(font18, speakers, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 7, OPTIONS_MENU_SPACING * 8.90, ALLEGRO_ALIGN_RIGHT,
				" %.1f (LEFT)", PC.soundPan);
		}
		else if (PC.soundPan > 0)
		{
			al_draw_textf(font18, speakers, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 7, OPTIONS_MENU_SPACING * 8.90, ALLEGRO_ALIGN_RIGHT,
				" %.1f (RIGHT)", PC.soundPan);
		}
		else if (PC.soundPan == 0)
		{
			al_draw_textf(font18, speakers, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING * 7, OPTIONS_MENU_SPACING * 8.90, ALLEGRO_ALIGN_RIGHT,
				" %.1f (BOTH)", PC.soundPan);
		}
		
	}

	if (menu.selected == 3)
	{ //al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 12, ALLEGRO_ALIGN_CENTRE, setupMenuItems[8]);

		// PHRASE "SET DEFAULTS" OU "SET DEFAULT VALUES"
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.10, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.14, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.18, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.29, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.33, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.37, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.41, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.45, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.49, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.55, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.63, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.67, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.71, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}
	else
	{ //al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OPTIONS_MENU_SPACING, OPTIONS_MENU_SPACING * 12, ALLEGRO_ALIGN_CENTRE, setupMenuItems[8]);

		// PHRASE "SET DEFAULTS" OU "SET DEFAULT VALUES"
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.10, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.14, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.18, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.29, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.33, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.37, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.41, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.45, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.49, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.55, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.63, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.67, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.71, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.65, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}

	if (menu.selected == 4)
	{ //al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OPTIONS_MENU_SPACING * 14, ALLEGRO_ALIGN_CENTRE, setupMenuItems[10]);

		// OPÇÃO "RETURN TO THE TITLE SCREEN"
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.09, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.13, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.17, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.21, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.42, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.46, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		if (state == OPTIONS)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.62, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.66, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.70, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		}
		else if (state == SETTING_AUDIO)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 7, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.62, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.66, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.70, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		}
		
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.76, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.79, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.82, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.88, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.91, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}
	else
	{ //al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OPTIONS_MENU_SPACING * 14, ALLEGRO_ALIGN_CENTRE, setupMenuItems[10]);

		// OPÇÃO "RETURN TO THE TITLE SCREEN"
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.09, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.13, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.17, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.21, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.42, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.46, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);

		if (state == OPTIONS)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.62, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.66, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.70, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		}
		else if (state == SETTING_AUDIO)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 7, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.62, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.66, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.70, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		}
		
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.76, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.79, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.82, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.88, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 5, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.91, SCREEN_HEIGHT * 0.80, SETUP_FONT_SIZE, SETUP_FONT_SIZE, 0.0, NULL);
	}
}

void ControllerScreen()
{
	int source = -1;
	char mapped[KEY_NAME] = " ";

	if (menu.selected == 0)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 3, ALLEGRO_ALIGN_RIGHT, playerControls[0]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2 , OTHER_MENU_SPACING * 3, ALLEGRO_ALIGN_CENTRE,
			InputMapping(PC.shoot));
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 3, ALLEGRO_ALIGN_RIGHT, playerControls[0]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 3, ALLEGRO_ALIGN_CENTRE,
			InputMapping(PC.shoot));
	}
		

	if (menu.selected == 1)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 4, ALLEGRO_ALIGN_RIGHT, playerControls[1]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 4, ALLEGRO_ALIGN_CENTRE, 
			InputMapping(PC.bomb));
	}
		
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 4, ALLEGRO_ALIGN_RIGHT, playerControls[1]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 4, ALLEGRO_ALIGN_CENTRE,
			InputMapping(PC.bomb));
	}
		

	if (menu.selected == 2)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 5, ALLEGRO_ALIGN_RIGHT, playerControls[2]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 5, 
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.powerup) );
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 5, ALLEGRO_ALIGN_RIGHT, playerControls[2]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 5, 
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.powerup));
	}
		

	if (menu.selected == 3)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 6, ALLEGRO_ALIGN_RIGHT, playerControls[3]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 6,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveUp));
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 6, ALLEGRO_ALIGN_RIGHT, playerControls[3]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 6,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveUp));
	}	

	if (menu.selected == 4)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 7, ALLEGRO_ALIGN_RIGHT, playerControls[4]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 7, 
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveDown));
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 7, ALLEGRO_ALIGN_RIGHT, playerControls[4]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 7, 
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveDown));
	}
		
	if (menu.selected == 5)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 8, ALLEGRO_ALIGN_RIGHT, playerControls[5]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 8, 
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveLeft));
	}
		
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 8, ALLEGRO_ALIGN_RIGHT, playerControls[5]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 8, 
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveLeft));
	}

	if (menu.selected == 6)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 9, ALLEGRO_ALIGN_RIGHT, playerControls[6]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 9,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveRight));
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 9, ALLEGRO_ALIGN_RIGHT, playerControls[6]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 9,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.moveRight));
	}

	if (menu.selected == 7)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 10, ALLEGRO_ALIGN_RIGHT, playerControls[7]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 10,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.confirm));
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 10, ALLEGRO_ALIGN_RIGHT, playerControls[7]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 10,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.confirm));
	}
		

	if (menu.selected == 8)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 11, ALLEGRO_ALIGN_RIGHT, playerControls[8]);
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 11,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.pause));
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 11, ALLEGRO_ALIGN_RIGHT, playerControls[8]);
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2 + OTHER_MENU_SPACING * 2, OTHER_MENU_SPACING * 11,
			ALLEGRO_ALIGN_CENTRE, InputMapping(PC.pause));
	}

	// SET DEFAULT VALUES
	if (menu.selected == 9)
	{
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 13, ALLEGRO_ALIGN_CENTRE, playerControls[9]);
	}
	else
	{
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 13, ALLEGRO_ALIGN_CENTRE, playerControls[9]);
	}

	// RETURN TO THE TITLE SCREEN
	if (menu.selected == 10)
		al_draw_textf(fontSelected, color_red, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 15, ALLEGRO_ALIGN_CENTRE, playerControls[10]);
	else
		al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, OTHER_MENU_SPACING * 15, ALLEGRO_ALIGN_CENTRE, playerControls[10]);

	//al_draw_bitmap(titleImage, 0, 0, NULL);

	al_draw_tinted_scaled_rotated_bitmap_region(
		menuTitles, 
		96 * 3, 
		0, 
		96 * 5, 
		96, 
		al_map_rgb(MAX_RGB_VALUE, MAX_RGB_VALUE, MAX_RGB_VALUE),
		1, 
		1, 
		SCREEN_WIDTH / 3, 
		SCREEN_HEIGHT * .025,
		.5, 
		.5, 
		0,
		NULL
		);
}

void LevelSelectScreen()
{
	al_draw_textf(font18, color_white, SCREEN_WIDTH / 2, 50, ALLEGRO_ALIGN_CENTRE, "LEVEL SELECT");
}

void ifEventIsMouseAxes()
{
	mousePosX = ev.mouse.x;
	mousePosY = ev.mouse.y;
	mouseButton = ev.mouse.button;
	//mouseWheelW = ev.mouse.w;
	//mouseWheelZ = ev.mouse.z;

	//std::cout << "Mouse X = " << mousePosX << " Mouse Y = " << mousePosY << std::endl;
}

void ifEventIsMouseButtonDown()
{
	if (ev.mouse.button & 1)
	{
		//std::cout << "BOTÃO ESQUERDO DO MOUSE" << std::endl;
		mouse[0] = true;
	}
	else if (ev.mouse.button & 2)
	{
		//std::cout << "BOTÃO DIREITO DO MOUSE" << std::endl;
		mouse[1] = true;
	}
	
}

void ifEventIsMouseButtonUp()
{
	if (ev.mouse.button & 1)
	{
		//std::cout << "SAIR ESQUERDO DO MOUSE" << std::endl;
		mouse[0] = false;
	}
	else if (ev.mouse.button & 2)
	{
		//std::cout << "SAIR DIREITO DO MOUSE" << std::endl;
		mouse[1] = false;
	}
}


void SetupControls()
{
	// DEFAULT CONTROLS

	PC.moveUp = ALLEGRO_KEY_UP;
	PC.moveDown = ALLEGRO_KEY_DOWN;
	PC.moveLeft = ALLEGRO_KEY_LEFT;
	PC.moveRight = ALLEGRO_KEY_RIGHT;
	PC.confirm = ALLEGRO_KEY_ENTER;
	PC.pause = ALLEGRO_KEY_ESCAPE;
	PC.shoot = ALLEGRO_KEY_Z;
	PC.bomb = ALLEGRO_KEY_X;
	PC.powerup = ALLEGRO_KEY_C;
	PC.executeSpecialMove = ALLEGRO_KEY_V;
	PC.inputDevice = INPUT_DEVICE_KEYBOARD;
	PC.newSetup = PC.oldSetup = -1;
	
}

void setupMouse()
{
	// SETUP DEFAULT MOUSE CONTROLS FOR THE GAME

	gameMouse.shoot = mouse[0];
	gameMouse.pause = mouse[1];
	gameMouse.backgroundMusicVolume = BGM_MAX_VOLUME;
	gameMouse.soundEffectVolume = SFX_MAX_VOLUME;
	gameMouse.moveDown = DOWN;
	gameMouse.moveLeft = LEFT;
	gameMouse.moveRight = RIGHT;
	gameMouse.moveUp = UP;
}

void ChangeControls()
{
	
}

char* InputMapping(int source)
{

	switch (source)
	{
	case ALLEGRO_KEY_A:
		strncpy(mapped, "A", sizeof(mapped));	break;

	case ALLEGRO_KEY_B:
		strncpy(mapped, "B", sizeof(mapped));	break;

	case ALLEGRO_KEY_C:
		strncpy(mapped, "C", sizeof(mapped));	break;

	case ALLEGRO_KEY_D:
		strncpy(mapped, "D", sizeof(mapped));	break;

	case ALLEGRO_KEY_E:
		strncpy(mapped, "E", sizeof(mapped));	break;

	case ALLEGRO_KEY_F:
		strncpy(mapped, "F", sizeof(mapped));	break;

	case ALLEGRO_KEY_G:
		strncpy(mapped, "G", sizeof(mapped));	break;

	case ALLEGRO_KEY_H:
		strncpy(mapped, "H", sizeof(mapped));	break;

	case ALLEGRO_KEY_I:
		strncpy(mapped, "I", sizeof(mapped));	break;

	case ALLEGRO_KEY_J:
		strncpy(mapped, "J", sizeof(mapped));	break;

	case ALLEGRO_KEY_K:
		strncpy(mapped, "K", sizeof(mapped));	break;

	case ALLEGRO_KEY_L:
		strncpy(mapped, "L", sizeof(mapped));	break;

	case ALLEGRO_KEY_M:
		strncpy(mapped, "M", sizeof(mapped));	break;

	case ALLEGRO_KEY_N:
		strncpy(mapped, "N", sizeof(mapped));	break;

	case ALLEGRO_KEY_O:
		strncpy(mapped, "O", sizeof(mapped));	break;

	case ALLEGRO_KEY_P:
		strncpy(mapped, "P", sizeof(mapped));	break;

	case ALLEGRO_KEY_Q:
		strncpy(mapped, "Q", sizeof(mapped));	break;

	case ALLEGRO_KEY_R:
		strncpy(mapped, "R", sizeof(mapped));	break;

	case ALLEGRO_KEY_S:
		strncpy(mapped, "S", sizeof(mapped));	break;

	case ALLEGRO_KEY_T:
		strncpy(mapped, "T", sizeof(mapped));	break;

	case ALLEGRO_KEY_U:
		strncpy(mapped, "U", sizeof(mapped));	break;

	case ALLEGRO_KEY_V:
		strncpy(mapped, "V", sizeof(mapped));	break;

	case ALLEGRO_KEY_W:
		strncpy(mapped, "W", sizeof(mapped));	break;

	case ALLEGRO_KEY_X:
		strncpy(mapped, "X", sizeof(mapped));	break;

	case ALLEGRO_KEY_Y:
		strncpy(mapped, "Y", sizeof(mapped));	break;

	case ALLEGRO_KEY_Z:
		strncpy(mapped, "Z", sizeof(mapped));	break;

	case ALLEGRO_KEY_0:
		strncpy(mapped, "0", sizeof(mapped));	break;

	case ALLEGRO_KEY_1:
		strncpy(mapped, "1", sizeof(mapped));	break;

	case ALLEGRO_KEY_2:
		strncpy(mapped, "2", sizeof(mapped));	break;

	case ALLEGRO_KEY_3:
		strncpy(mapped, "3", sizeof(mapped));	break;

	case ALLEGRO_KEY_4:
		strncpy(mapped, "4", sizeof(mapped));	break;

	case ALLEGRO_KEY_5:
		strncpy(mapped, "5", sizeof(mapped));	break;

	case ALLEGRO_KEY_6:
		strncpy(mapped, "6", sizeof(mapped));	break;

	case ALLEGRO_KEY_7:
		strncpy(mapped, "7", sizeof(mapped));	break;

	case ALLEGRO_KEY_8:
		strncpy(mapped, "8", sizeof(mapped));	break;

	case ALLEGRO_KEY_9:
		strncpy(mapped, "9", sizeof(mapped));	break;

	case ALLEGRO_KEY_SPACE:
		strncpy(mapped, "SPACE", sizeof(mapped));	break;

	case ALLEGRO_KEY_ENTER:
		strncpy(mapped, "ENTER", sizeof(mapped));	break;

	case ALLEGRO_KEY_BACKSPACE:
		strncpy(mapped, "BACKSPACE", sizeof(mapped));	break;

	case ALLEGRO_KEY_LSHIFT:
		strncpy(mapped, "LEFT SHIFT", sizeof(mapped));	
		break;

	case ALLEGRO_KEY_RSHIFT:
		strncpy(mapped, "RIGHT SHIFT", sizeof(mapped));	
		break;

	case ALLEGRO_KEY_LCTRL:
		strncpy(mapped, "LEFT CTRL", sizeof(mapped));	
		break;

	case ALLEGRO_KEY_RCTRL:
		strncpy(mapped, "RIGHT CTRL", sizeof(mapped));	
		break;

	case ALLEGRO_KEY_HOME:
		strncpy(mapped, "HOME", sizeof(mapped));	break;

	case ALLEGRO_KEY_ALT:
		strncpy(mapped, "ALT", sizeof(mapped));	
		break;

	case ALLEGRO_KEY_ALTGR:
		strncpy(mapped, "ALTGR", sizeof(mapped));	
		break;

	case ALLEGRO_KEY_TAB:
		strncpy(mapped, "TAB", sizeof(mapped));	break;

	case ALLEGRO_KEY_MINUS:
		strncpy(mapped, "MINUS", sizeof(mapped));	break;

	case ALLEGRO_KEY_EQUALS:
		strncpy(mapped, "EQUALS", sizeof(mapped));	break;

	case ALLEGRO_KEY_QUOTE:
		strncpy(mapped, "QUOTE", sizeof(mapped));	break;

	case ALLEGRO_KEY_TILDE:
		strncpy(mapped, "TILDE", sizeof(mapped));	break;

	case ALLEGRO_KEY_COMMA:
		strncpy(mapped, "COMMA", sizeof(mapped));	break;

	case ALLEGRO_KEY_SLASH:
		strncpy(mapped, "SLASH", sizeof(mapped));	break;

	case ALLEGRO_KEY_BACKSLASH:
		strncpy(mapped, "BACKSLASH", sizeof(mapped));	break;

	case ALLEGRO_KEY_SEMICOLON:
		strncpy(mapped, "SEMICOLON", sizeof(mapped));	break;

	case ALLEGRO_KEY_OPENBRACE:
		strncpy(mapped, "OPEN BRACE", sizeof(mapped));	break;

	case ALLEGRO_KEY_CLOSEBRACE:
		strncpy(mapped, "CLOSE BRACE", sizeof(mapped));	break;

	case ALLEGRO_KEY_F1:
		strncpy(mapped, "F1", sizeof(mapped));	break;

	case ALLEGRO_KEY_F2:
		strncpy(mapped, "F2", sizeof(mapped));	break;

	case ALLEGRO_KEY_F3:
		strncpy(mapped, "F3", sizeof(mapped));	break;

	case ALLEGRO_KEY_F4:
		strncpy(mapped, "F4", sizeof(mapped));	break;

	case ALLEGRO_KEY_F5:
		strncpy(mapped, "F5", sizeof(mapped));	break;

	case ALLEGRO_KEY_F6:
		strncpy(mapped, "F6", sizeof(mapped));	break;

	case ALLEGRO_KEY_F7:
		strncpy(mapped, "F7", sizeof(mapped));	break;

	case ALLEGRO_KEY_F8:
		strncpy(mapped, "F8", sizeof(mapped));	break;

	case ALLEGRO_KEY_F9:
		strncpy(mapped, "F9", sizeof(mapped));	break;

	case ALLEGRO_KEY_F10:
		strncpy(mapped, "F10", sizeof(mapped));	break;

	case ALLEGRO_KEY_F11:
		strncpy(mapped, "F11", sizeof(mapped));	break;

	case ALLEGRO_KEY_F12:
		strncpy(mapped, "F12", sizeof(mapped));	break;

	case ALLEGRO_KEY_ESCAPE:
		strncpy(mapped, "ESCAPE", sizeof(mapped));	break;

	case ALLEGRO_KEY_FULLSTOP:
		strncpy(mapped, "FULLSTOP", sizeof(mapped));	break;

	case ALLEGRO_KEY_DELETE:
		strncpy(mapped, "DELETE", sizeof(mapped));	break;

	case ALLEGRO_KEY_INSERT:
		strncpy(mapped, "INSERT", sizeof(mapped));	break;

	case ALLEGRO_KEY_END:
		strncpy(mapped, "END", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAUSE:
		strncpy(mapped, "PAUSE", sizeof(mapped));	break;

	case ALLEGRO_KEY_UP:
		strncpy(mapped, "UP", sizeof(mapped));	break;

	case ALLEGRO_KEY_DOWN:
		strncpy(mapped, "DOWN", sizeof(mapped));	break;

	case ALLEGRO_KEY_LEFT:
		strncpy(mapped, "LEFT", sizeof(mapped));	break;

	case ALLEGRO_KEY_RIGHT:
		strncpy(mapped, "RIGHT", sizeof(mapped));	break;

	case ALLEGRO_KEY_PGDN:
		strncpy(mapped, "PAGE DOWN", sizeof(mapped));	break;

	case ALLEGRO_KEY_PGUP:
		strncpy(mapped, "PAGE UP", sizeof(mapped));	break;

	case ALLEGRO_KEY_PRINTSCREEN:
		strncpy(mapped, "PRINT SCREEN", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_0:
		strncpy(mapped, "NUMPAD 0", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_1:
		strncpy(mapped, "NUMPAD 1", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_2:
		strncpy(mapped, "NUMPAD 2", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_3:
		strncpy(mapped, "NUMPAD 3", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_4:
		strncpy(mapped, "NUMPAD 4", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_5:
		strncpy(mapped, "NUMPAD 5", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_6:
		strncpy(mapped, "NUMPAD 6", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_7:
		strncpy(mapped, "NUMPAD 7", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_8:
		strncpy(mapped, "NUMPAD 8", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_9:
		strncpy(mapped, "NUMPAD 9", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_ASTERISK:
		strncpy(mapped, "NUMPAD *", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_DELETE:
		strncpy(mapped, "NUMPAD DELETE", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_ENTER:
		strncpy(mapped, "NUMPAD ENTER", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_EQUALS:
		strncpy(mapped, "NUMPAD EQUALS", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_MINUS:
		strncpy(mapped, "NUMPAD MINUS", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_PLUS:
		strncpy(mapped, "NUMPAD PLUS", sizeof(mapped));	break;

	case ALLEGRO_KEY_PAD_SLASH:
		strncpy(mapped, "NUMPAD SLASH", sizeof(mapped));	break;

	case ALLEGRO_KEY_UNKNOWN:
		strncpy(mapped, "UNKNOWN", sizeof(mapped));	break;

	case ALLEGRO_KEY_CIRCUMFLEX:
		strncpy(mapped, "CIRCUMFLEX", sizeof(mapped));	break;

	case ALLEGRO_KEY_SEMICOLON2:
		strncpy(mapped, "SEMICOLON 2", sizeof(mapped));	break;

	case ALLEGRO_KEY_BACKSLASH2:
		strncpy(mapped, "BACKSLASH 2", sizeof(mapped));	break;

	case ALLEGRO_KEY_COLON2:
		strncpy(mapped, "COLON 2", sizeof(mapped));	break;

	case ALLEGRO_KEY_BACKQUOTE:
		strncpy(mapped, "BACKQUOTE", sizeof(mapped));	break;

	case ALLEGRO_KEY_LWIN:
		strncpy(mapped, "LEFT WINDOWS KEY", sizeof(mapped));	break;

	case ALLEGRO_KEY_RWIN:
		strncpy(mapped, "RIGHT WINDOWS KEY", sizeof(mapped));	break;

	case ALLEGRO_KEY_SCROLLLOCK:
		strncpy(mapped, "SCROLL LOCK", sizeof(mapped));	break;

	default:
		strncpy(mapped, "?", sizeof(mapped));	break;
	}

	//std::cout << "MAPPED KEY: " << mapped << " ." << std::endl;

	return mapped;

}

char* DeviceMapping(int device)
{
	switch (device)
	{
	case INPUT_DEVICE_JOYSTICK:
		strncpy(mapped, "JOYSTICK", sizeof(mapped) );
		break;

inputDevice:	case INPUT_DEVICE_KEYBOARD:
		strncpy(mapped, "KEYBOARD", sizeof(mapped));
		break;

	case INPUT_DEVICE_MOUSE:
		strncpy(mapped, "MOUSE", sizeof(mapped));
		break;

	case INPUT_DEVICE_DEFAULT:
		goto inputDevice;
		break;

	case -1:
		goto inputDevice;
		break;

	default:
		strncpy(mapped, "?", sizeof(mapped));
		break;
	}

	return mapped;
}

void SetupAudio()
{
	// DEFAULT AUDIO SETTINGS

	PC.backgroundMusicVolume = BGM_START_VOLUME;
	PC.soundEffectVolume = SFX_START_VOLUME;
	PC.playerContinues = PLAYER_CONTINUES;
	PC.playerCredits = PLAYER_CREDITS;
	PC.jingleVolume = JINGLE_MAX_VOLUME / 2;
	PC.playbackSpeed = PLAYBACK_SPEED;
	PC.soundPan = 0;
	PC.gameTune = 0;

	configureSampleId = NULL;

	al_set_sample_instance_gain(titleInstance, PC.backgroundMusicVolume);
	al_set_sample_instance_gain(bossInstance, PC.backgroundMusicVolume);
	al_set_sample_instance_gain(endingInstance, PC.backgroundMusicVolume);
	//al_set_sample_instance_gain(lostSong, PC.backgroundMusicVolume);
	al_set_sample_instance_gain(stage2, PC.backgroundMusicVolume);
	al_set_sample_instance_gain(stage1, PC.backgroundMusicVolume);

	al_set_sample_instance_pan(titleInstance, PC.soundPan);
	al_set_sample_instance_pan(bossInstance, PC.soundPan);
	al_set_sample_instance_pan(endingInstance, PC.soundPan);
	//al_set_sample_instance_pan(lostSong, PC.soundPan);
	al_set_sample_instance_pan(stage2, PC.soundPan);
	al_set_sample_instance_pan(stage1, PC.soundPan);

	al_set_sample_instance_playmode(stage2, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(stage1, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(bossInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(endingInstance, ALLEGRO_PLAYMODE_LOOP);
	//al_set_sample_instance_playmode(lostSong, ALLEGRO_PLAYMODE_ONCE);
	al_set_sample_instance_playmode(titleInstance, ALLEGRO_PLAYMODE_LOOP);

}

void ifEventIsMouseEnterDisplay()
{
	//std::cout << "MOUSE ENTROU NO DISPLAY" << std::endl;
}

void ifEventIsMouseLeaveDisplay()
{
	//std::cout << "MOUSE SAIU DO DISPLAY" << std::endl;
}

void MoveShipWithMouse()
{
	distX = ev.mouse.x - ship.x;
	distY = ev.mouse.y - ship.y;

	easingAmount = EASING_AMOUNT;

	distance = std::sqrt(distX * distX + distY * distY);

	if (distance > MINIMUM_DISTANCE)
	{
		ship.x += distX * easingAmount;
		ship.y += distY * easingAmount;
	}
	else if (distance < 0)
	{
		//distance = 0;
	}

}

void ChangeWeapon()
{
	if (ship.currWeapon < 0)
	{
		ship.currWeapon = ship.quantWeapons - 1;
	}
	if (ship.currWeapon >= ship.quantWeapons)
	{
		ship.currWeapon = 0;
	}

	ship.currWeapon++;
}

void InitBDoubleShot(){

	for (int i = 0; i < PLAYER_NUM_BULLETS; i++)
	{
		bulletsWest[i].ID = bullets[i].ID;
		bulletsWest[i].speed = -bullets[i].speed;
		bulletsWest[i].alive = bullets[i].alive;

		bulletsWest[i].originX = bulletsWest[i].originY = bulletsWest[i].angle = bulletsWest[i].shipX = bulletsWest[i].shipY =
			bullets[i].angle;

	}
	
}
void DrawBDoubleShot(){
	for (int j = 0; j < PLAYER_NUM_BULLETS; j++){
		if (bulletsWest[j].alive == true){
			al_draw_filled_circle(bulletsWest[j].x, bulletsWest[j].y, PLAYER_BULLET_RADIUS, al_map_rgb(0, 0, 255));
		}
	}
}
void FireBDoubleShot(){
	int j = 0;

	if (ship.currWeapon >= DOUBLE_SHOT){
		for (j = 0; j < PLAYER_NUM_BULLETS; j++){
			if (!bulletsWest[j].alive){
				bulletsWest[j].x = ship.x - 17;
				bulletsWest[j].y = ship.y;
				bulletsWest[j].alive = true;
				bulletsWest[j].bulletDirection = ship.playerDirection;
				ship.isFiringDoubleShot = true;
			}
		}
	}
}
void UpdateBDoubleShot(){
	int j = 0;

	if (ship.isFiringDoubleShot == true){
		ship.DScurrFrame--;

		if (ship.DScurrFrame <= 0){
			ship.isFiringDoubleShot = false;
			ship.DScurrFrame = PLAYER_FIRING_COOLDOWN;
		}
	}

	if (ship.currWeapon >= DOUBLE_SHOT) {
		for (j = 0; j < PLAYER_NUM_BULLETS; j++)
		{
			if (bulletsWest[j].alive) {
				bulletsWest[j].x += bulletsWest[j].speed;

				if (bulletsWest[j].x > SCREEN_WIDTH ||
					bulletsWest[j].y > SCREEN_HEIGHT ||
					bulletsWest[j].x < 0 ||
					bulletsWest[j].y < 0)
				{
					bulletsWest[j].alive = false;
				}
			}
		}
	}

}

double fromDegreesToRadians(double degrees){
	double radians = 0.00;

	if (degrees <= 0){
		degrees = 0;
	}
	else if (degrees >= 360){
		degrees = 0;
	}

	radians = (double)((double) PI / (double) 180.00) * (double) degrees;

	return radians;
}

double fromRadiansToDegrees(double radians){
	double degrees = 0.00;

	if (radians <= 0){
		radians = 0;
	}
	else if (radians >= ( 2 * PI ) ){
		radians = 0;
	}

	degrees = ( (double) radians * (double) 180.00 / (double) PI );

	return degrees;
}

void InitLevel(){
	//gameplay.currentFrame = 0;
	gameplay.timeCounter = 0;
	gameplay.triggerFrame = nullptr;

	gameplay.triggerFrame = (unsigned int*) realloc(gameplay.triggerFrame, 10 * sizeof(unsigned int));

	if (gameplay.currentLevel == LEVEL01){
		stage.levelNumber = LEVEL01;
	}

	for (int i = 0; i < 10; i++){
		gameplay.triggerFrame[i] = 120 + (rand() % ( int ) ( 2048 - 60 + 1 ) );
		//std::cout << "NUMBER GENERATED FOR " << i << " = " << gameplay.triggerFrame[i] << " ." << std::endl;
	}

	for (int i = 0;i < NUM_LEVELS;i++){
		levels[i] = false;
	}
	LoadAssets();

	if (stage.levelNumber == LEVEL01 || gameplay.currentLevel == LEVEL01){
		InitBackground(0, 0, 1, 0, SCREEN_WIDTH, SCREEN_HEIGHT, -1, 1, stage.backgrounds[0].image);
		red = MAX_RGB_VALUE;
		green = MAX_RGB_VALUE;
		blue = MAX_RGB_VALUE;
		alpha = LEVEL01_BACKGROUND_ALPHA;
	}
	//AudioSetup();
	//al_play_sample_instance(song);
	//al_play_sample_instance(bongosTrack);
	//al_set_sample_instance_gain(bongosTrack, 0.0);
	//al_play_sample(bongos, 0.5, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	
}

void DrawLevel(){

	if (stage.levelNumber == LEVEL01 || gameplay.currentLevel == LEVEL01){
		//al_draw_bitmap(stage.backgrounds[0].image, 0, 0, 0);
		//al_draw_bitmap(stage.backgrounds[0].image, stage.backgrounds[0].posX, stage.backgrounds[0].posY, 0);
		DrawBackground();
		DrawCollectible();
	}
	else if (stage.levelNumber == LEVEL02 || gameplay.currentLevel == LEVEL02){
		//al_draw_bitmap(stage.backgrounds[0].image, 0, 0, 0);
		//al_draw_bitmap(stage.backgrounds[0].image, stage.backgrounds[0].posX, stage.backgrounds[0].posY, 0);
		DrawBackground();
		DrawCollectible();
	}

}

//void StartLevel();

void UpdateLevel(){

	if (gameplay.currentFrame < 0){
		gameplay.currentFrame = 0;
	}
	if (gameplay.currentFrame >= 9999){
		//gameplay.currentFrame = 9999;
	}

	UpdateBackground();

	if (stage.levelNumber == LEVEL01){
		if (badGuy[0].numLives <= 0)
		{
			//std::cout << "FRAME FINAL: " << badGuy[0].currFrame << " ." << std::endl;

			badGuy[0].currFrame++;
			
			if (badGuy[0].currFrame2 <= BOSS_DEATH_TIMER)
			{
				//std::cout << "FRAME FINAL: " << badGuy[0].currFrame << " ." << std::endl;
				// BOSS 1 EXPLOSION SEQUENCE
				if (badGuy[0].currFrame == 10 || badGuy[0].currFrame == 75 || badGuy[0].currFrame == 200 || badGuy[0].currFrame == 650)
				{
					StartExplosion(badGuy[0].x - badGuy[0].imageWidth / 4, 
						badGuy[0].y - badGuy[0].imageHeight / 4, 
						badGuy[0].speed);
				}
				else if (badGuy[0].currFrame == 40 || badGuy[0].currFrame == 350 || badGuy[0].currFrame == 500 || badGuy[0].currFrame == 625)
				{
					StartExplosion(badGuy[0].x - badGuy[0].imageWidth / 3,
						badGuy[0].y - badGuy[0].imageHeight / 4, 
						badGuy[0].speed);
				}
				else if (badGuy[0].currFrame == 100 || badGuy[0].currFrame == 225 || badGuy[0].currFrame == 450)
				{
					StartExplosion(badGuy[0].x - badGuy[0].imageWidth / 3,
						badGuy[0].y - badGuy[0].imageHeight / 2, 
						badGuy[0].speed);
				}
				else if (badGuy[0].currFrame == 150 || badGuy[0].currFrame == 550 || badGuy[0].currFrame == 250)
				{
					StartExplosion(badGuy[0].x - badGuy[0].imageHeight / 2,
						badGuy[0].y - badGuy[0].imageHeight / 2, 
						badGuy[0].speed);
				}
				else if (badGuy[0].currFrame == 300 || badGuy[0].currFrame == 400 || badGuy[0].currFrame == 275)
				{
					StartExplosion(badGuy[0].x - badGuy[0].imageWidth / 2,
						badGuy[0].y - badGuy[0].imageHeight / 2, 
						badGuy[0].speed);
				}
				else if (badGuy[0].currFrame == 180 || badGuy[0].currFrame == 375 || badGuy[0].currFrame == 600)
				{
					StartExplosion(badGuy[0].x - badGuy[0].imageWidth / badGuy[0].x,
						badGuy[0].y - badGuy[0].imageWidth / badGuy[0].y, 
						badGuy[0].speed);
				}
				else if (badGuy[0].currFrame >= 800)
				{
					ship.score++;
					ship.lives++;
					stage.nextLevel = LEVEL03;
					stage.levelNumber = LEVEL02;
					gameplay.currentLevel = stage.levelNumber;
					levels[0] = true;
					badGuy[0].isAlive = false;
					badGuy[0].isInvulnerable = false;
					badGuy[0].gotHit = false;
					badGuy[0].currFrame = 0;
					badGuy[0].currFrame2 = 0;
					badGuy[0].x = badGuy[0].y = SCREEN_HEIGHT * 2;
					gameplay.currentFrame = 0;
					badGuy[0].currState = -1;
					badGuy[0].transPhase = 0;
					enemyType = ENEMY_COPTER_BLACK;
					ChangeState(PLAYING);
					//goto lvl01;
				}
			}
		}

		if (gameplay.currentFrame == 180 
			|| gameplay.currentFrame == 220 
			|| gameplay.currentFrame == 260
			|| gameplay.currentFrame == 300)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * .10, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .30, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .50, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .70, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .90, COLLECTIBLE_COIN);
		}
		
		if (gameplay.currentFrame == 400)
		{
			StartEnemy(SCREEN_HEIGHT * .90, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 580 
			|| gameplay.currentFrame == 620 
			|| gameplay.currentFrame == 660 
			|| gameplay.currentFrame == 700
			)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * .2, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .4, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .6, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .8, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 800)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * .5, COLLECTIBLE_HEALTH);
		}

		if (gameplay.currentFrame == 900)
		{
			StartEnemy(SCREEN_HEIGHT * .80, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 1100)
		{
			StartEnemy(SCREEN_HEIGHT * .60, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 1400)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.3, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.4, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 1700)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.5, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .70, ENEMY_PLANE_WHITE, LEFTWARDS);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.9, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 2000)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.1, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.5, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.9, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 2100)
		{
			StartEnemy(SCREEN_HEIGHT * .70, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 2200)
		{
			StartEnemy(SCREEN_HEIGHT * .50, ENEMY_PLANE_WHITE, LEFTWARDS);
		}
		
		if (gameplay.currentFrame == 2400)
		{
			StartEnemy(SCREEN_HEIGHT * .10, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .50, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .90, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 2700)
		{
			StartEnemy(SCREEN_HEIGHT * .10, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .20, ENEMY_PLANE_WHITE, LEFTWARDS);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.7, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.9, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.5, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 2800){
			SpawnCollectible(-1, SCREEN_HEIGHT *.9, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 2850){
			SpawnCollectible(-1, SCREEN_HEIGHT *.8, COLLECTIBLE_COIN);
			
		}

		if (gameplay.currentFrame == 2900) {
			SpawnCollectible(-1, SCREEN_HEIGHT *.7, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .95, ENEMY_PLANE_WHITE, LEFTWARDS);
		}
		
		if (gameplay.currentFrame == 2950){
			SpawnCollectible(-1, SCREEN_HEIGHT *.6, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3000){
			SpawnCollectible(-1, SCREEN_HEIGHT *.5, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .90, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3050){
			SpawnCollectible(-1, SCREEN_HEIGHT *.45, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3100){
			SpawnCollectible(-1, SCREEN_HEIGHT *.4, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .80, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3150){
			SpawnCollectible(-1, SCREEN_HEIGHT *.35, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3200){
			SpawnCollectible(-1, SCREEN_HEIGHT *.3, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .60, ENEMY_PLANE_RED, LEFTWARDS);

		}

		if (gameplay.currentFrame == 3250){
			SpawnCollectible(-1, SCREEN_HEIGHT *.25, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3300){
			SpawnCollectible(-1, SCREEN_HEIGHT *.2, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .50, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3350){
			SpawnCollectible(-1, SCREEN_HEIGHT *.15, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3400){
			SpawnCollectible(-1, SCREEN_HEIGHT *.1, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3450){
			SpawnCollectible(-1, SCREEN_HEIGHT *.05, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .45, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3500){
			SpawnCollectible(-1, SCREEN_HEIGHT *.1, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .8, COLLECTIBLE_HEALTH);
		}

		if (gameplay.currentFrame == 3525){
			SpawnCollectible(-1, SCREEN_HEIGHT *.15, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .85, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3550){
			SpawnCollectible(-1, SCREEN_HEIGHT *.20, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3600){
			SpawnCollectible(-1, SCREEN_HEIGHT *.3, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .15, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3650){
			SpawnCollectible(-1, SCREEN_HEIGHT *.4, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 3700){
			SpawnCollectible(-1, SCREEN_HEIGHT *.5, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .20, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3800){
			SpawnCollectible(-1, SCREEN_HEIGHT *.55, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .15, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 3900){
			SpawnCollectible(-1, SCREEN_HEIGHT *.6, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 4000){
			SpawnCollectible(-1, SCREEN_HEIGHT *.65, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .35, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .50, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 4100){
			SpawnCollectible(-1, SCREEN_HEIGHT *.7, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .25, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 4200){
			SpawnCollectible(-1, SCREEN_HEIGHT *.75, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 4300){
			SpawnCollectible(-1, SCREEN_HEIGHT *.8, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 4400){
			SpawnCollectible(-1, SCREEN_HEIGHT *.85, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 4500){
			SpawnCollectible(-1, SCREEN_HEIGHT *.9, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 4600){
			SpawnCollectible(-1, SCREEN_HEIGHT *.95, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 4700){
			SpawnCollectible(-1, SCREEN_HEIGHT *.99, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .2, COLLECTIBLE_HEALTH);
			StartEnemy(SCREEN_HEIGHT * .80, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 5000)
		{
			StartEnemy(SCREEN_HEIGHT * .25, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .55, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .15, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame == 5200)
		{
			StartEnemy(SCREEN_HEIGHT * .5, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .5, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 5500)
		{
			StartEnemy(SCREEN_HEIGHT * .5, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .5, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 5600)
		{
			StartEnemy(SCREEN_HEIGHT * .5, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 5700)
		{
			StartEnemy(SCREEN_HEIGHT * .5, ENEMY_PLANE_RED, LEFTWARDS);
		}

		if (gameplay.currentFrame == 5800)
		{
			StartEnemy(SCREEN_HEIGHT * .25, ENEMY_PLANE_WHITE, LEFTWARDS);
			StartEnemy(SCREEN_HEIGHT * .85, ENEMY_PLANE_WHITE, LEFTWARDS);
		}
		if (gameplay.currentFrame == 6000){
			SpawnCollectible(-1, SCREEN_HEIGHT *.1, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .3, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .5, COLLECTIBLE_HEALTH);
			SpawnCollectible(-1, SCREEN_HEIGHT * .7, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .9, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 6250 || gameplay.currentFrame == 7000){
			SpawnCollectible(-1, SCREEN_HEIGHT *.1, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .3, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .5, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .7, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .9, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 6500 || gameplay.currentFrame == 6900){
			SpawnCollectible(-1, SCREEN_HEIGHT *.15, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .35, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .55, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .75, ENEMY_PLANE_WHITE, LEFTWARDS);
			SpawnCollectible(-1, SCREEN_HEIGHT * .95, COLLECTIBLE_COIN);
		}

		if (gameplay.currentFrame == 6700){
			SpawnCollectible(-1, SCREEN_HEIGHT *.18, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .38, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .58, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * .78, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * .98, ENEMY_PLANE_WHITE, LEFTWARDS);
		}

		if (gameplay.currentFrame >= 7100 && gameplay.currentFrame < 9050)
		{
			//green = green - 0.00025f;
			//blue = blue - 0.000025f;
		}

	}
	else if (stage.levelNumber == LEVEL02)
	{
		int frame = gameplay.currentFrame;
		int frame2 = gameplay.currentFrame2;

		if(frame == 150 || 
			frame == 200 || 
			frame == 250 ||
			frame == 300 || 
			frame == 350 || 
			frame == 400 || 
			frame == 450)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.20, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.40, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.60, COLLECTIBLE_COIN);
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.80, COLLECTIBLE_COIN);
		}

		if (frame == 540)
		{
			StartEnemy(SCREEN_HEIGHT * 0.95, ENEMY_COPTER_WHITE, LEFTWARDS);
		}

		if (frame == 580)
		{
			StartEnemy(SCREEN_HEIGHT * 0.75, ENEMY_COPTER_WHITE, LEFTWARDS);
		}

		if (frame == 620)
		{
			StartEnemy(SCREEN_HEIGHT * 0.55, ENEMY_COPTER_WHITE, LEFTWARDS);
		}

		if (frame == 660)
		{
			StartEnemy(SCREEN_HEIGHT * 0.35, ENEMY_COPTER_WHITE, LEFTWARDS);
		}

		if (frame == 700)
		{
			StartEnemy(SCREEN_HEIGHT * 0.15, ENEMY_COPTER_WHITE, LEFTWARDS);
		}

		if (frame == 850)
		{
			SpawnCollectible(-1, SCREEN_HEIGHT * 0.50, COLLECTIBLE_HEALTH);
		}

		if (frame == 1000)
		{
			StartEnemy(SCREEN_HEIGHT * 0.10, ENEMY_COPTER_BLUE, LEFTWARDS);
		}
		if (frame == 1050)
		{
			StartEnemy(SCREEN_HEIGHT * 0.30, ENEMY_COPTER_BLUE, LEFTWARDS);
		}
		if (frame == 1100)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_BLUE, LEFTWARDS);
		}
		if (frame == 1150)
		{
			StartEnemy(SCREEN_HEIGHT * 0.70, ENEMY_COPTER_BLUE, LEFTWARDS);
		}
		if (frame == 1200)
		{
			StartEnemy(SCREEN_HEIGHT * 0.90, ENEMY_COPTER_BLUE, LEFTWARDS);
		}

		if (frame == 1500)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_BLUE, LEFTWARDS);
		}

		if (frame == 1750)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_BLACK, LEFTWARDS);
		}

		if (frame == 1900)
		{
			StartEnemy(SCREEN_HEIGHT * 0.20, ENEMY_COPTER_BLACK, LEFTWARDS);
		}
	
		if (frame == 1950)
		{
			SpawnCollectible(-1, SCREEN_WIDTH / 2, COLLECTIBLE_COIN);
		}
		if (frame == 2000)
		{
			StartEnemy(SCREEN_HEIGHT * 0.80, ENEMY_COPTER_BLACK, LEFTWARDS);
		}
		if (frame == 2100)
		{
			StartEnemy(SCREEN_HEIGHT * 0.40, ENEMY_COPTER_BLACK, LEFTWARDS);
		}
		if (frame == 2200)
		{
			StartEnemy(SCREEN_HEIGHT * 0.60, ENEMY_COPTER_BLACK, LEFTWARDS);
		}
		if (frame == 2300)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_BLACK, LEFTWARDS);
		}
		if (frame == 2500)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 2650 
			|| frame == 2750 
			|| frame == 2850 
			|| frame == 2950)
		{
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.10, COLLECTIBLE_COIN);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.30, COLLECTIBLE_COIN);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.50, COLLECTIBLE_COIN);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.70, COLLECTIBLE_COIN);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.90, COLLECTIBLE_COIN);
		}
		if (frame == 3300)
		{
			StartEnemy(SCREEN_HEIGHT * 0.10, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 3400)
		{
			StartEnemy(SCREEN_HEIGHT * 0.90, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 3500)
		{
			StartEnemy(SCREEN_HEIGHT * 0.20, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 3600)
		{
			StartEnemy(SCREEN_HEIGHT * 0.80, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 3700)
		{
			StartEnemy(SCREEN_HEIGHT * 0.30, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 3800)
		{
			StartEnemy(SCREEN_HEIGHT * 0.70, ENEMY_COPTER_RED, LEFTWARDS);
		}
		if (frame == 3900)
		{
			StartEnemy(SCREEN_HEIGHT * 0.40, ENEMY_COPTER_BLACK, LEFTWARDS);
		}
		if (frame == 4000)
		{
			StartEnemy(SCREEN_HEIGHT * 0.60, ENEMY_COPTER_BLACK, LEFTWARDS);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.70, COLLECTIBLE_HEALTH);
		}

		if (frame == 4200) {
			StartEnemy(SCREEN_HEIGHT * 0.05, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4250) {
			StartEnemy(SCREEN_HEIGHT * 0.10, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4300) {
			StartEnemy(SCREEN_HEIGHT * 0.15, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4350) {
			StartEnemy(SCREEN_HEIGHT * 0.20, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4400) {
			StartEnemy(SCREEN_HEIGHT * 0.25, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4450) {
			StartEnemy(SCREEN_HEIGHT * 0.30, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4500) {
			StartEnemy(SCREEN_HEIGHT * 0.35, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4550) {
			StartEnemy(SCREEN_HEIGHT * 0.40, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4600) {
			StartEnemy(SCREEN_HEIGHT * 0.45, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4650) {
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4700) {
			StartEnemy(SCREEN_HEIGHT * 0.55, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4750) {
			StartEnemy(SCREEN_HEIGHT * 0.60, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4800) {
			StartEnemy(SCREEN_HEIGHT * 0.65, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4850) {
			StartEnemy(SCREEN_HEIGHT * 0.70, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4900) {
			StartEnemy(SCREEN_HEIGHT * 0.75, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 4950) {
			StartEnemy(SCREEN_HEIGHT * 0.80, ENEMY_COPTER_RED, LEFTWARDS);
		} if (frame == 5000) {
			StartEnemy(SCREEN_HEIGHT * 0.85, ENEMY_COPTER_RED, LEFTWARDS);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.15, COLLECTIBLE_COIN);
		} if (frame == 5050) {
			StartEnemy(SCREEN_HEIGHT * 0.90, ENEMY_COPTER_RED, LEFTWARDS);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.25, COLLECTIBLE_COIN);
		} if (frame == 5100) {
			StartEnemy(SCREEN_HEIGHT * 0.95, ENEMY_COPTER_RED, LEFTWARDS);
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.35, COLLECTIBLE_COIN);
		} if (frame == 5200)
		{
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.45, COLLECTIBLE_HEALTH);
		} if (frame == 5300)
		{
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.55, COLLECTIBLE_COIN);
		} if (frame == 5400)
		{
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.65, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * 0.10, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 5500)
		{
			SpawnCollectible(LEFTWARDS, SCREEN_HEIGHT * 0.75, COLLECTIBLE_COIN);
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 5600)
		{
			StartEnemy(SCREEN_HEIGHT * 0.90, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 5700)
		{
			StartEnemy(SCREEN_HEIGHT * 0.10, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 5800)
		{
			StartEnemy(SCREEN_HEIGHT * 0.80, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 5900)
		{
			StartEnemy(SCREEN_HEIGHT * 0.20, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 6000)
		{
			StartEnemy(SCREEN_HEIGHT * 0.70, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 6100)
		{
			StartEnemy(SCREEN_HEIGHT * 0.30, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 6200)
		{
			StartEnemy(SCREEN_HEIGHT * 0.60, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 6300)
		{
			StartEnemy(SCREEN_HEIGHT * 0.40, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 6400)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_BLACK, LEFTWARDS);
		} if (frame == 6500)
		{
			StartEnemy(SCREEN_HEIGHT * 0.55, ENEMY_COPTER_BLUE, LEFTWARDS);
		} if (frame == 6700)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 6750)
		{
			StartEnemy(SCREEN_HEIGHT * 0.40, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 6800)
		{
			StartEnemy(SCREEN_HEIGHT * 0.30, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 6850)
		{
			StartEnemy(SCREEN_HEIGHT * 0.20, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 6900)
		{
			StartEnemy(SCREEN_HEIGHT * 0.10, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 6950)
		{
			StartEnemy(SCREEN_HEIGHT * 0.90, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 7000)
		{
			StartEnemy(SCREEN_HEIGHT * 0.80, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 7050)
		{
			StartEnemy(SCREEN_HEIGHT * 0.70, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 7100)
		{
			StartEnemy(SCREEN_HEIGHT * 0.60, ENEMY_COPTER_WHITE, LEFTWARDS);
		} if (frame == 7150)
		{
			StartEnemy(SCREEN_HEIGHT * 0.50, ENEMY_COPTER_WHITE, LEFTWARDS);
		} 

		if (frame >= 7200 && frame < 9050)
		{
			green = green - 0.0005f;
			blue = blue - 0.0005f;
		}
	}

	// IF LEVEL FRAMES ARE FROZEN (NOT RUNNING) OR NOT
	if (frozen == false)
	{
		gameplay.currentFrame++;
	}

	//audioTime = music.getPlayingOffset();

}

void LoadAssets()
{
	stage.levelNumber = gameplay.currentLevel;

	if (stage.levelNumber == LEVEL01){

		// SE O JOGADOR ESTÁ NA PRIMEIRA FASE (CHEMTRAILS)

		//stage.backgrounds[0].image = al_load_bitmap("assets/chemtrails/chemtrails_bkg.png");

		if (stage.backgrounds[0].image == NULL){
			stage.error = ASSET_LVL01_PIC_BACKGROUND_LOAD_FAIL;
			return;
		}

		for (int i = 0; i < NUM_COLLECTIBLES; i++)
		{
			//collect[i].image = al_load_bitmap("assets/chemtrails/gold.png");

			if (collect[i].image == NULL)
			{
				
				return;
			}
		}
	}
}

void DestroyAssets(){

	if (stage.backgrounds[0].image != NULL && stage.backgrounds[0].image != nullptr){
		al_destroy_bitmap(stage.backgrounds[0].image);
	}

	if (stage.repeated[0].image != NULL && stage.repeated[0].image != nullptr){
		//al_destroy_bitmap(stage.repeated[0].image);
	}

	if (stage.backgrounds[1].image != NULL && stage.backgrounds[1].image != nullptr){
		al_destroy_bitmap(stage.backgrounds[1].image);
	}

	if (stage.repeated[1].image != NULL && stage.repeated[1].image != nullptr){
		//al_destroy_bitmap(stage.repeated[1].image);
	}

	if (level02_bkg.image != NULL)
	{
		al_destroy_bitmap(level02_bkg.image);
	}
	if (level02_bkg2.image != NULL)
	{
		al_destroy_bitmap(level02_bkg2.image);
	}

	for (int i = 0; i < NUM_BOSSES; i++){
		if (!badGuy[i].image){
			al_destroy_bitmap(badGuy[i].image);
		}

		if (!badGuy[i].shoot){
			al_destroy_sample(badGuy[i].shoot);
		}

		if (!badGuy[i].hurt){
			al_destroy_sample(badGuy[i].hurt);
		}
	}

	if (menuSelect != NULL)
	{
		al_destroy_sample(menuSelect);
		menuSelect = NULL;
	}
	if (menuChange != NULL)
	{
		al_destroy_sample(menuChange);
		menuChange = NULL;
	}
	if (menuConfigure != NULL)
	{
		al_destroy_sample(menuConfigure);
		menuConfigure = NULL;
	}
	if (menuCancel != NULL)
	{
		al_destroy_sample(menuCancel);
		menuCancel = NULL;
	}

	if (menuOK != NULL)
	{
		al_destroy_sample(menuOK);
		menuOK = NULL;
	}

	if (pauseSample != NULL)
	{
		al_destroy_sample(pauseSample);
		pauseSample = NULL;
	}

	if (menuFont != NULL)
		al_destroy_bitmap(menuFont);

	if (menuTitles != NULL)
		al_destroy_bitmap(menuTitles);

	if (titleLogo != NULL)
	{
		al_destroy_bitmap(titleLogo);
		titleLogo = NULL;
	}

	menuFont = nullptr;
	menuTitles = nullptr;
	level02_bkg2.image = nullptr;
	level02_bkg.image = nullptr;
}

void InitBackground(double x, double y, double vx, double vy, int width, int height, int dx, int dy, ALLEGRO_BITMAP *image){

	for (int i = 0; i < NUM_BACKGROUNDS; i++){
		stage.backgrounds[i].posX = x;
		stage.backgrounds[i].posY = y;
		stage.backgrounds[0].speedX = LEVEL01_BACKGROUND_SCROLLING_SPEED;
		stage.backgrounds[1].speedX = LEVEL01_MIDDLEGROUND_SCROLLING_SPEED;
		stage.backgrounds[i].speedY = vy;
		stage.backgrounds[i].dirX = dx;
		stage.backgrounds[i].dirY = dy;
		
	}

	for (int i = 0; i < NUM_BACKGROUNDS; i++){
		stage.repeated[i].posX = x + SCREEN_WIDTH;
		stage.repeated[i].posY = y;
		stage.repeated[i].speedX = stage.backgrounds[i].speedX;
		stage.repeated[i].speedY = stage.backgrounds[i].speedY;
		stage.repeated[i].dirX = dx;
		stage.repeated[i].dirY = dy;
		stage.repeated[i].image = stage.backgrounds[i].image;
	}

	stage.repeated[0].image = stage.backgrounds[0].image;
	stage.repeated[1].image = stage.backgrounds[1].image;

	al_convert_mask_to_alpha(stage.backgrounds[1].image, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(stage.repeated[1].image, al_map_rgb(255, 0, 255));
	
}


void DrawBackground(){

	if (stage.levelNumber == LEVEL00)
	{

	}
	else if (stage.levelNumber == LEVEL01){

		al_draw_tinted_bitmap(stage.backgrounds[0].image,
			al_map_rgb(red, green, blue), 
			stage.backgrounds[0].posX,
			stage.backgrounds[0].posY,
			NULL);

			al_draw_bitmap(stage.backgrounds[0].image,
				stage.repeated[0].posX, 
				stage.repeated[0].posY,
				NULL);

			al_draw_tinted_bitmap(stage.backgrounds[1].image,
				al_map_rgba_f(LEVEL01_BACKGROUND_RED, LEVEL01_BACKGROUND_GREEN, LEVEL01_BACKGROUND_BLUE, LEVEL01_BACKGROUND_ALPHA),
				stage.backgrounds[1].posX,
				stage.backgrounds[1].posY,
				NULL);

			al_draw_tinted_bitmap(stage.backgrounds[1].image,
				al_map_rgba_f(LEVEL01_BACKGROUND_RED, LEVEL01_BACKGROUND_GREEN, LEVEL01_BACKGROUND_BLUE, LEVEL01_BACKGROUND_ALPHA),
				stage.repeated[1].posX,
				stage.repeated[1].posY,
				NULL);
	}
	else if (stage.levelNumber == LEVEL02)
	{
		if (level02_bkg2.image != NULL && level02_bkg2_loop.image != NULL)
		{
			al_draw_bitmap(level02_bkg2.image, level02_bkg2.posX, level02_bkg2.posY, NULL);
			al_draw_bitmap(level02_bkg2_loop.image, level02_bkg2_loop.posX, level02_bkg2_loop.posY, NULL);

			//al_draw_tinted_bitmap(level02_bkg2.image, al_map_rgb(red, green, blue), level02_bkg2.posX, level02_bkg2.posY, NULL);
			//al_draw_tinted_bitmap(level02_bkg2_loop.image, al_map_rgb(red, green, blue), level02_bkg2.posX, level02_bkg2.posY, NULL);
		}

		if (level02_bkg.image != NULL && level02_bkg_loop.image != NULL)
		{
			al_draw_bitmap(level02_bkg.image, level02_bkg.posX, level02_bkg.posY, NULL);
			al_draw_bitmap(level02_bkg_loop.image, level02_bkg_loop.posX, level02_bkg_loop.posY, NULL);

			//al_draw_tinted_bitmap(level02_bkg.image, al_map_rgb(red, green, blue), level02_bkg2.posX, level02_bkg2.posY, NULL);
			//al_draw_tinted_bitmap(level02_bkg_loop.image, al_map_rgb(red, green, blue), level02_bkg2.posX, level02_bkg2.posY, NULL);
		}
	}

}

void UpdateBackground(){

	int frame = gameplay.currentFrame;

	if (stage.levelNumber == LEVEL00)
	{

	}
	else if (stage.levelNumber == LEVEL01)
	{
		for (int count = 0; count < NUM_BACKGROUNDS; count++)
		{
			stage.backgrounds[count].posX += stage.backgrounds[count].speedX;
			stage.repeated[count].posX += stage.repeated[count].speedX;
			if (stage.backgrounds[count].posX + SCREEN_WIDTH <= 0){
				stage.backgrounds[count].posX = SCREEN_WIDTH;
			}
			if (stage.backgrounds[count].posY + SCREEN_HEIGHT <= 0){
				stage.backgrounds[count].posY = SCREEN_HEIGHT;
			}
			if (stage.repeated[count].posX + SCREEN_WIDTH <= 0){
				stage.repeated[count].posX = SCREEN_WIDTH;
			}
			if (stage.repeated[count].posY + SCREEN_HEIGHT <= 0){
				stage.repeated[count].posY = SCREEN_HEIGHT;
			}
		}
	}
	else if (stage.levelNumber == LEVEL02)
	{
		//std::cout << "SASKALSKASLAS AKSLAS BKG 2 X = " << level02_bkg2.posX << " BKG 1 X =" << level02_bkg.posX << " " << std::endl;

		level02_bkg2.posX += level02_bkg2.speedX;
		level02_bkg2_loop.posX += level02_bkg2_loop.speedX;

		level02_bkg.posX += level02_bkg.speedX;
		level02_bkg_loop.posX += level02_bkg_loop.speedX;

		if (level02_bkg2.posX + SCREEN_WIDTH <= 0){
			level02_bkg2.posX = SCREEN_WIDTH;
		}
		if (level02_bkg.posX + SCREEN_WIDTH <= 0){
			level02_bkg.posX = SCREEN_WIDTH;
		}
		if (level02_bkg2_loop.posX + SCREEN_WIDTH <= 0){
			level02_bkg2_loop.posX = SCREEN_WIDTH;
		}
		if (level02_bkg_loop.posX + SCREEN_WIDTH <= 0){
			level02_bkg_loop.posX = SCREEN_WIDTH;
		}
	}


	if (red <= 0){
		red = 0;
	}
	if (red >= MAX_RGB_VALUE){
		red = MAX_RGB_VALUE;
	}

	if (green <= 0){
		green = 0;
	}
	if (green >= MAX_RGB_VALUE){
		green = MAX_RGB_VALUE;
	}

	if (blue <= 0){
		blue = 0;
	}
	if (blue >= MAX_RGB_VALUE){
		blue = MAX_RGB_VALUE;
	}
}

void InitEnemy(){

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		e[i].ID = ENEMY;
		e[i].threshold = PLANE_RADIUS;
		e[i].alive = false;
		e[i].velX = PLANE_WHITE_SPEED;
		e[i].velY = PLANE_WHITE_SPEED;
		e[i].borderX = PLANE_BOUNDX;
		e[i].borderY = PLANE_BOUNDY;
		e[i].angle = 0.00;

		e[i].currFrame = 0;
		e[i].isAttacking = false;
		e[i].cooldown = COMET_FIRING_COOLDOWN;
		e[i].spawnFrame = PLANE_SPAWN_INTERVAL;
		
		e[i].image = al_load_bitmap(PLANE_WHITE_BITMAP);

		if (e[i].image != NULL || e[i].image != nullptr)
		{
			al_convert_mask_to_alpha(e[i].image, al_map_rgb(255, 0, 255));

			e[i].height = al_get_bitmap_height(e[i].image);
			e[i].width = al_get_bitmap_width(e[i].image);

			e[i].radius = PLANE_RADIUS;
		}

		e[i].areaX = PLANE_AREAX;
		e[i].areaY = PLANE_AREAY;

		e[i].offsetX = PLANE_OFFSETX;
		e[i].offsetY = PLANE_OFFSETY;

		e[i].type = -1;

		if (enemyShot[i] == NULL || enemyShot[i] == nullptr)
		{
			enemyShot[i] = al_load_sample(PLANE_SHOT_SAMPLE_PATH);
		}
		
	}

	for (int c = 0; c < NUM_COPTERS; c++)
	{
		copter[c].alive = false;
		copter[c].angle = 0.00;
		copter[c].currFrame = 0;
		copter[c].direction = LEFTWARDS;
		copter[c].ID = ENEMY;
		copter[c].lives = -1;
		copter[c].radius = COPTER_VISION_RADIUS;
		copter[c].type = ENEMY_COPTER_BLACK;
		copter[c].image = nullptr;
		copter[c].image = al_load_bitmap(COPTER_BITMAP);

		if (copter[c].image != nullptr && copter[c].image != NULL)
		{
			copter[c].width = al_get_bitmap_width(copter[c].image);
			copter[c].height = al_get_bitmap_height(copter[c].image);
			al_convert_mask_to_alpha(copter[c].image, al_map_rgb(255, 0, 255));
		}

		copter[c].borderX = COPTER_BOUNDX;
		copter[c].borderY = COPTER_BOUNDY;
		copter[c].cooldown = COPTER_COOLDOWN;
		copter[c].state = -1;
		copter[c].posX = 0;
		copter[c].posY = 0;
		copter[c].spawnFrame = 0;
		copter[c].speed = COPTER_SPEED;
		copter[c].velX = COPTER_SPEED;
		copter[c].velY = copter[c].velX;
		copter[c].offsetX = COPTER_OFFSCREEN_X;
		copter[c].offsetY = COPTER_OFFSCREEN_Y;
		copter[c].isAttacking = false;
	}

	/*
	for (int count = 0; count < NUM_COPTERS; count++)
	{
		helix[count] = NULL;
		helix[count] = al_load_bitmap(COPTER_HELIX_BITMAP);

		if (helix[count] == NULL)
		{
			al_convert_mask_to_alpha(helix[count], color_pink);
		}
	}
	*/

}

void DrawEnemy(){

	if (stage.levelNumber == LEVEL01)
	{
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			if (e[i].alive == true)
			{
				//al_draw_filled_circle(e[i].posX, e[i].posY, COMET_BODY_RADIUS, al_map_rgb(0, 0, 255));

				if (e[i].image != NULL || e[i].image != nullptr)
				{
					if (e[i].type == ENEMY_PLANE_WHITE || e[i].type == ENEMY_COPTER_BLACK)
					{
						if (e[i].direction == LEFTWARDS)
						{
							al_draw_bitmap(e[i].image,
								e[i].posX - e[i].width / 2,
								e[i].posY - e[i].height / 2, NULL);
						}
						else if (e[i].direction == RIGHTWARDS)
						{
							al_draw_bitmap(e[i].image,
								e[i].posX - e[i].width / 2,
								e[i].posY - e[i].height / 2, ALLEGRO_FLIP_HORIZONTAL);

						}
					}
					else if (e[i].type == ENEMY_PLANE_RED)
					{
						if (e[i].direction == LEFTWARDS)
						{
							al_draw_tinted_bitmap(e[i].image,
								al_map_rgb(ENEMY_PLANE_RED_COLOR, 0, 0),
								e[i].posX - e[i].width / 2,
								e[i].posY - e[i].height / 2, NULL);
						}
						else if (e[i].direction == RIGHTWARDS)
						{
							al_draw_tinted_bitmap(e[i].image,
								al_map_rgb(ENEMY_PLANE_RED_COLOR, 0, 0),
								e[i].posX - e[i].width / 2,
								e[i].posY - e[i].height / 2, ALLEGRO_FLIP_HORIZONTAL);

						}
					}
				}
				else
				{
					al_draw_filled_rectangle(
						e[i].posX - e[i].borderX, e[i].posY - e[i].borderY,
						e[i].posX + e[i].borderX, e[i].posY + e[i].borderY,
						al_map_rgb(255, 0, 0)
						);
				}

			}
		}
	}
	else if (stage.levelNumber == LEVEL02){
		for (int i = 0; i < NUM_COPTERS; i++){
			if (copter[i].alive == true){
				if (copter[i].type == ENEMY_COPTER_BLACK){
					if (copter[i].direction == LEFTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_grey,
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							NULL
							);
					}
					else if (copter[i].direction == RIGHTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_grey, 
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							ALLEGRO_FLIP_HORIZONTAL
							);
					}
				}
				else if (copter[i].type == ENEMY_COPTER_RED){
					if (copter[i].direction == LEFTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_red, 
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							NULL
							);
					}
					else if (copter[i].direction == RIGHTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_red, 
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							ALLEGRO_FLIP_HORIZONTAL
							);
					}
				}
				else if (copter[i].type == ENEMY_COPTER_WHITE)
				{
					if (copter[i].direction == LEFTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_white,
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							NULL
							);
					}
					else if (copter[i].direction == RIGHTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_white,
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							ALLEGRO_FLIP_HORIZONTAL
							);
					}
				}
				else if (copter[i].type == ENEMY_COPTER_BLUE)
				{
					if (copter[i].direction == LEFTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_blue,
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							NULL
							);
					}
					else if (copter[i].direction == RIGHTWARDS){
						al_draw_tinted_bitmap(
							copter[i].image,
							color_blue,
							copter[i].posX - copter[i].width / 2,
							copter[i].posY - copter[i].height / 2,
							ALLEGRO_FLIP_HORIZONTAL
							);
					}
				}
			}
		}
	}
	
}

void SpawnBaddie()
{

}

void StartEnemy(double y, int enemyType, int enemyDirection){

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (e[i].alive == false)
		{
			int spawn = SpawnEnemy();

			//if (spawn == 0)
			//{
				//double pos = randomizeEnemyPosition();

				e[i].alive = true;

				if (enemyDirection == LEFTWARDS)
				{
					e[i].posX = SCREEN_WIDTH + PLANE_OFFSCREEN_X;
				}
				else if (enemyDirection == RIGHTWARDS)
				{
					e[i].posX = 0 - PLANE_OFFSCREEN_X;
				}
				
				e[i].posY = y;
				e[i].direction = enemyDirection;
				e[i].type = enemyType;

				break;
			//}

		}
	}

	for (int i = 0; i < NUM_COPTERS; i++)
	{
		if (copter[i].alive == false)
		{
			copter[i].alive = true;

			if (enemyDirection == LEFTWARDS)
			{
				copter[i].posX = SCREEN_WIDTH + COPTER_OFFSCREEN_X;
			}
			else if (enemyDirection == RIGHTWARDS)
			{
				copter[i].posX = - COPTER_OFFSCREEN_X;
			}

			copter[i].posY = y;
			copter[i].direction = enemyDirection;
			copter[i].type = enemyType;

			break;
		}
	}

}

void StopEnemy(){

}

void UpdateEnemy(){

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		threshold = e[i].threshold;

		if (e[i].alive == true && gameplay.currentLevel == LEVEL01)
		{
			if (e[i].type == ENEMY_PLANE_WHITE)
			{
				if (e[i].direction == LEFTWARDS)
				{
					e[i].posX -= e[i].velX;
				}
				else if (e[i].direction == RIGHTWARDS)
				{
					e[i].posX += e[i].velX;
				}
			}
			else if (e[i].type == ENEMY_PLANE_RED)
			{
				if (e[i].direction == LEFTWARDS)
				{
					e[i].posX -= (e[i].velX + 1);
				}
				else if (e[i].direction == RIGHTWARDS)
				{
					e[i].posX += (e[i].velX + 1);
				}
			}
			if (e[i].posX < -PLANE_OFFSCREEN_X || e[i].posY < -PLANE_OFFSCREEN_Y ||
				e[i].posX > SCREEN_WIDTH + PLANE_OFFSCREEN_X ||
				e[i].posY > SCREEN_HEIGHT + PLANE_OFFSCREEN_Y)
			{
				e[i].alive = false;
			}
		}
	}
	e[0].spawnFrame--;
	if (e[0].spawnFrame < 0)
	{
		e[0].spawnFrame = PLANE_SPAWN_INTERVAL;
	}
	else if (e[0].spawnFrame > PLANE_SPAWN_INTERVAL)
	{
		e[0].spawnFrame = PLANE_SPAWN_INTERVAL;
	}

	for (int i = 0; i < NUM_COPTERS; i++)
	{
		if (copter[i].alive == true && gameplay.currentLevel == LEVEL02)
		{
			if (copter[i].type == ENEMY_COPTER_BLACK)
			{
				if (copter[i].direction == LEFTWARDS)
				{
					copter[i].posX -= copter[i].speed;
				}
				else if (copter[i].direction == RIGHTWARDS)
				{
					copter[i].posX += copter[i].speed;
				}
			}
			else if (copter[i].type == ENEMY_COPTER_RED)
			{
				if (copter[i].direction == LEFTWARDS)
				{
					copter[i].posX -= (copter[i].speed + 1);
				}
				else if (copter[i].direction == RIGHTWARDS)
				{
					copter[i].posX += (copter[i].speed + 1);
				}
			}
			else if (copter[i].type == ENEMY_COPTER_WHITE)
			{
				if (copter[i].direction == LEFTWARDS)
				{
					copter[i].posX -= (copter[i].speed - 2);

				}
				else if (copter[i].direction == RIGHTWARDS)
				{
					copter[i].posX += (copter[i].speed - 2);
				}
			}
			else if (copter[i].type == ENEMY_COPTER_BLUE)
			{
				if (copter[i].direction == LEFTWARDS)
				{
					copter[i].posX -= (copter[i].speed - 2);

				}
				else if (copter[i].direction == RIGHTWARDS)
				{
					copter[i].posX += (copter[i].speed - 2);
				}
			}

			if (copter[i].posX < -(COPTER_OFFSCREEN_X) || 
				copter[i].posY < -(COPTER_OFFSCREEN_Y) ||
				copter[i].posX > SCREEN_WIDTH + COPTER_OFFSCREEN_X ||
				copter[i].posY > SCREEN_HEIGHT + COPTER_OFFSCREEN_Y)
			{
				copter[i].alive = false;
			}

		}
	}

	for (int count = 0; count < NUM_COPTERS; count++)
	{
		if (copter[count].isAttacking == true)
		{
			copter[count].cooldown--;

			if (copter[count].cooldown < 0)
			{
				copter[count].cooldown = COPTER_COOLDOWN;
				copter[count].isAttacking = false;
			}
		}
	}
}

int randomizeEnemyType()
{
	int enemyType;

	enemyType = rand() % 3;

	return enemyType;
}

double randomizeEnemyPosition()
{
	double position;

	position = ENEMY_POSITION_BUFFER + rand() % (SCREEN_HEIGHT - ENEMY_POSITION_BUFFER);

	if (position <= SCREEN_HEIGHT * 0.20)
	{
		position = SCREEN_HEIGHT * 0.20;
	}
	else if (position >= SCREEN_HEIGHT * 0.80)
	{
		position = SCREEN_HEIGHT * 0.80;
	}

	return position;
}

int SpawnEnemy()
{
	int value = rand() % ENEMY_SPAWN_RATE;

	return value;
}

void InitCollectible()
{
	int i;
	for (i = 0; i < NUM_COLLECTIBLES; i++)
	{
		collect[i].ID = COLLECTIBLE;
		collect[i].x = -1;
		collect[i].y = -1;
		collect[i].currFrame = COLLECTIBLE_SPAWN_INTERVAL;
		collect[i].alive = false;
		collect[i].collected = false;

		collect[i].image = al_load_bitmap(COLLECTIBLE_BITMAP);

		if (collect[i].image != NULL && collect[i].image != nullptr)
		{
			al_convert_mask_to_alpha(collect[i].image, al_map_rgb(255, 0, 255));

			collect[i].width = al_get_bitmap_width(collect[i].image);

			collect[i].height = al_get_bitmap_height(collect[i].image);
		}

		collect[i].type = -1;
		collect[i].direction = -1;

		collect[i].speedX = COLLECTIBLE_SPEED;
		collect[i].speedY = COLLECTIBLE_SPEED;

		collect[i].borderX = COLLECTIBLE_BOUNDX;
		collect[i].borderY = COLLECTIBLE_BOUNDY;

		collect[i].type = COLLECTIBLE_COIN;
	}

	for (i = 0; i < NUM_HEARTS; i++)
	{
		powerup[i].ID = COLLECTIBLE;
		powerup[i].alive = false;
		powerup[i].collected = false;
		powerup[i].image = al_load_bitmap(HEALTH_BITMAP);
		powerup[i].x = SCREEN_WIDTH * 2;
		powerup[i].y = SCREEN_HEIGHT * 2;

		if (powerup[i].image != NULL && powerup[i].image != nullptr)
		{
			al_convert_mask_to_alpha(powerup[i].image, al_map_rgb(255, 0, 255));

			powerup[i].width = al_get_bitmap_width(powerup[i].image);

			powerup[i].height = al_get_bitmap_height(powerup[i].image);
		}

		powerup[i].type = COLLECTIBLE_HEALTH;
		powerup[i].direction = -1;

		powerup[i].speedX = COLLECTIBLE_SPEED;
		powerup[i].speedY = COLLECTIBLE_SPEED;

		powerup[i].borderX = COLLECTIBLE_BOUNDX;
		powerup[i].borderY = COLLECTIBLE_BOUNDY;
	}

	for (i = 0; i < NUM_SHIELDS; i++)
	{
		shields[i].ID = COLLECTIBLE;
		shields[i].alive = false;
		shields[i].currFrame = 0;
		shields[i].type = -1;
		shields[i].x = -1;
		shields[i].y = -1;
		shields[i].collected = false;

		shields[i].image = al_load_bitmap(SHIELD_BITMAP);

		if (shields[i].image != NULL || shields[i].image != nullptr)
		{
			al_convert_mask_to_alpha(shields[i].image, al_map_rgb(255, 0, 255));

			shields[i].width = al_get_bitmap_width(shields[i].image);

			shields[i].height = al_get_bitmap_height(shields[i].image);
		}
		shields[i].type = COLLECTIBLE_SHIELD;
		shields[i].direction = -1;

		shields[i].speedX = COLLECTIBLE_SPEED;
		shields[i].speedY = COLLECTIBLE_SPEED;

		shields[i].borderX = COLLECTIBLE_BOUNDX;
		shields[i].borderY = COLLECTIBLE_BOUNDY;
	}
}

void DrawCollectible()
{
	int i, j;

	for (i = 0; i < NUM_COLLECTIBLES; i++)
	{
		if (collect[i].alive == true)
		{
			if (collect[i].image == NULL || collect[i].image == nullptr)
			{
				al_draw_filled_circle(collect[i].x, collect[i].y, COLLECTIBLE_BOUNDX / 2, al_map_rgb(255, 255, 255));
			}
			else
			{
				al_draw_bitmap(collect[i].image, 
					collect[i].x - collect[i].width / 2, 
					collect[i].y - collect[i].height / 2, 
					NULL);
			}
		}
	}

	for (j = 0; j < NUM_HEARTS; j++)
	{
		if (powerup[j].alive == true)
		{
			//std::cout << "i = " << i << " j = " << j << " ." << std::endl;

			if (powerup[j].image == NULL || powerup[j].image == nullptr)
			{
				al_draw_filled_circle(powerup[j].x, powerup[j].y, COLLECTIBLE_BOUNDX / 2, al_map_rgb(234, 234, 234) );
			}
			else
			{
				al_draw_bitmap(powerup[j].image,
					powerup[j].x - powerup[j].width / 2,
					powerup[j].y - powerup[j].height / 2,
					0);
			}
		}
	}
}

void SpawnCollectible(int dir, double newPos, int type)
{
	int count = 0;

	if (type == COLLECTIBLE_COIN)
	{
		for (int i = 0; i < NUM_COLLECTIBLES; i++)
		{
			if (collect[i].alive == false)
			{
				double pos = randomizeCollectiblePosition(-1);

				collect[i].alive = true;
				collect[i].x = SCREEN_WIDTH + COLLECTIBLE_BUFFER_X;
				collect[i].y = newPos;
				break;
			}
		}
	}
	else if (type == COLLECTIBLE_HEALTH)
	{
		for (int i = 0; i < NUM_HEARTS; i++)
		{
			if (powerup[i].alive == false)
			{
				if (powerup[i].alive == false)
				{
					double pos = randomizeCollectiblePosition(-1);
					powerup[i].alive = true;
					powerup[i].x = SCREEN_WIDTH;
					powerup[i].y = newPos;
					break;
				}
			}
		}
	}
}

void UpdateCollectible()
{

	for (int i = 0; i < NUM_COLLECTIBLES; i++)
	{
		if (collect[i].alive == true)
		{
			collect[i].x -= collect[i].speedX;

			if (collect[i].x < 0 - COLLECTIBLE_BUFFER_X ||
				collect[i].y < 0 - COLLECTIBLE_BUFFER_X||
				collect[i].x > SCREEN_WIDTH + COLLECTIBLE_BUFFER_X ||
				collect[i].y > SCREEN_HEIGHT)
			{
				collect[i].alive = false;
				collect[i].x = collect[i].y = SCREEN_WIDTH * 2;
				//ship.lives--;
			}
		}
	}

	for (int i = 0; i < NUM_HEARTS; i++)
	{
		if (powerup[i].alive == true)
		{
			powerup[i].x -= powerup[i].speedX;

			if (powerup[i].x < 0 ||
				powerup[i].y < 0 ||
				powerup[i].x > SCREEN_WIDTH ||
				powerup[i].y > SCREEN_HEIGHT)
			{
				powerup[i].alive = false;
				powerup[i].x = powerup[i].y = SCREEN_WIDTH * 2;
				//ship.lives--;
			}
		}
	}
}
void GetCollectible()
{

	for (int i = 0; i < NUM_COLLECTIBLES; i++)
	{
		if (collect[i].alive == true)
		{
			if (collect[i].x - collect[i].borderX < ship.x + ship.boundX &&
				collect[i].x + collect[i].borderX > ship.x - ship.boundX &&
				collect[i].y - collect[i].borderY < ship.y + ship.boundY &&
				collect[i].y + collect[i].borderY > ship.y - ship.boundY)
			{
				// HÁ UM COLISÃO ENTRE NAVE E COMETA
				//ship.lives--;
				collect[i].alive = false;
				ship.collectibles++;
				//sfx.play();
				//al_stop_sample(sampleId);
				al_play_sample(coin, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
	}

	for (int i = 0; i < NUM_HEARTS; i++)
	{
		if (powerup[i].alive == true)
		{
			if (powerup[i].x - powerup[i].borderX < ship.x + ship.boundX &&
				powerup[i].x + powerup[i].borderX > ship.x - ship.boundX &&
				powerup[i].y - powerup[i].borderY < ship.y + ship.boundY &&
				powerup[i].y + powerup[i].borderY > ship.y - ship.boundY)
			{
				// HÁ UM COLISÃO ENTRE NAVE E COMETA
				//ship.lives--;
				powerup[i].alive = false;
				ship.lives++;
				//sfx.play();
				//al_stop_sample(sampleId);
				al_play_sample(heart, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);

			}
		}
	}

}

double randomizeCollectiblePosition(int dir)
{
	double position;

	if (dir == UPWARDS || dir == DOWNWARDS)
	{
		position = COLLECTIBLE_HORIZONTAL_BUFFER + rand() % (SCREEN_WIDTH - COLLECTIBLE_HORIZONTAL_BUFFER);
	}
	else if (dir == LEFTWARDS || dir == RIGHTWARDS)
	{
		
	}

	//position = ENEMY_POSITION_BUFFER + rand() % (SCREEN_HEIGHT - ENEMY_POSITION_BUFFER);
	position = COLLECTIBLE_VERTICAL_BUFFER + rand() % (SCREEN_HEIGHT - COLLECTIBLE_VERTICAL_BUFFER);

	if (position <= 0)
	{
		position = 0;
	}
	if (position >= SCREEN_HEIGHT)
	{
		position = SCREEN_HEIGHT;
	}
	if (position <= 0)
	{
		position = 0;
	}
	if (position >= SCREEN_WIDTH)
	{
		position = SCREEN_WIDTH;
	}

	return position;

}

void randomizeNumberOfCollectibles()
{

}

void ShowCollision()
{
	if (showCollision == true)
	{
		for (int i = 0; i < NUM_COLLECTIBLES; i++)
		{
			if (collect[i].alive == true)
			{
				al_draw_filled_rectangle(
					collect[i].x - collect[i].borderX, collect[i].y - collect[i].borderY,
					collect[i].x + collect[i].borderX, collect[i].y + collect[i].borderY,
					al_map_rgba(255, 0, 0, 127)
					);
			}
			
		}

		for (int j = 0; j < NUM_ENEMIES; j++)
		{
			if (e[j].alive == true)
			{
				al_draw_filled_circle(e[j].posX, e[j].posY, e[j].radius, al_map_rgba(255, 0, 255, 100));
			}

			if (copter[j].alive == true)
			{
				al_draw_filled_rectangle(copter[j].posX - copter[j].borderX + COPTER_LEFT_BOUNDX, 
					copter[j].posY - copter[j].borderY + COPTER_UP_BOUNDY,
					copter[j].posX + copter[j].borderX + COPTER_RIGHT_BOUNDX, 
					copter[j].posY + copter[j].borderY + COPTER_DOWN_BOUNDY,
					al_map_rgba(MAX_RGB_VALUE, CONST_ZERO, MAX_RGB_VALUE, 100));
			}
		}

		al_draw_filled_rectangle(ship.x - ship.boundX, ship.y - ship.boundY,
			ship.x + ship.boundX, ship.y + ship.boundY,
			al_map_rgba(MAX_RGB_VALUE, CONST_ZERO, MAX_RGB_VALUE, MAX_RGB_VALUE / 2));

		for (int count = 0; count < NUM_BOSSES; count++)
		{
			if (count == CONST_ONE)
			{
				al_draw_filled_rectangle(
					badGuy[count].x - badGuy[count].borderX,
					badGuy[count].y - badGuy[count].borderY,
					badGuy[count].x + badGuy[count].borderX,
					badGuy[count].y + badGuy[count].borderY,
					al_map_rgba(MAX_RGB_VALUE, CONST_ZERO, MAX_RGB_VALUE, MAX_RGB_VALUE / 3)
					);
			}
			else{
				al_draw_filled_rectangle(
					badGuy[count].x - badGuy[count].borderX,
					badGuy[count].y - badGuy[count].borderY * .18,
					badGuy[count].x + badGuy[count].borderX,
					badGuy[count].y + badGuy[count].borderY,
					al_map_rgba(MAX_RGB_VALUE, CONST_ZERO, MAX_RGB_VALUE, MAX_RGB_VALUE / 2)
					);
			}
			
		}
	}
}

void CollideEnemy(int obj1, int obj2, int obj1num, int obj2num)
{
	int i;

	for (i = 0; i < NUM_ENEMIES; i++){
		if (e[i].alive == true){
			if (threshold > CheckDistance(ship.x, ship.y, e[i].posX, e[i].posY)
				&& ct[0][i].isFiringBullets == false)
			{
				FireCT(i, 0);
			}

			if (e[i].posX - e[i].borderX < ship.x + ship.boundX &&
				e[i].posX + e[i].borderX > ship.x - ship.boundX &&
				e[i].posY - e[i].borderY < ship.y + ship.boundY &&
				e[i].posY + e[i].borderY > ship.y - ship.boundY)
			{
				// COLIDIU COM AVIÃO BRANCO
				if (ship.state != PLAYER_INVULNERABLE){
					ship.lives--;
					e[i].alive = false;
					al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
					ship.state = PLAYER_INVULNERABLE;
					StartExplosion(ship.x, ship.y, e[i].velX);
					
					//break;
					//std::cout << "ATACOU JOGADOR!" << std::endl;
				}
			}

			for (int count = 0; count < ENEMY_NUM_BULLETS; count++)
			{
				if (ct[count][i].alive == true)
				{
					if (ct[count][i].x > (ship.x - ship.boundX) &&
						ct[count][i].x < (ship.x + ship.boundX) &&
						ct[count][i].y > (ship.y - ship.boundY) &&
						ct[count][i].y < (ship.y + ship.boundY))
					{
						if (ship.state != PLAYER_INVULNERABLE)
						{
							ship.lives--;
							ct[count][i].alive = false;
							al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
							ship.state = PLAYER_INVULNERABLE;
						}
					}
				}
			}
		}

		if (copter[i].alive == true)
		{
			// SE O JOGADOR COLIDIU COM O HELICÓPTERO ATIVADO

			if (copter[i].posX - copter[i].borderX + COPTER_LEFT_BOUNDX < ship.x + ship.boundX &&
				copter[i].posX + copter[i].borderX + COPTER_RIGHT_BOUNDX > ship.x - ship.boundX &&
				copter[i].posY - copter[i].borderY + COPTER_UP_BOUNDY < ship.y + ship.boundY &&
				copter[i].posY + copter[i].borderY + COPTER_DOWN_BOUNDY > ship.y - ship.boundY)
			{
				if (ship.state != PLAYER_INVULNERABLE){
					ship.lives--;
					copter[i].alive = false;
					al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
					ship.state = PLAYER_INVULNERABLE;
					StartExplosion(ship.x, ship.y, copter[i].speed);
				}
			}
		}
	}

	for (int count = 0; count < NUM_BOSSES; count++){
		if (badGuy[count].isAlive == true && badGuy[count].currState == BOSS_IDLING && badGuy[count].numLives > 0){

			if (badGuy[count].x - badGuy[count].borderX < ship.x + ship.boundX &&
				badGuy[count].x + badGuy[count].borderX > ship.x - ship.boundX &&
				badGuy[count].y - badGuy[count].borderY * BOSS01_COLLISION_OFFSET < ship.y + ship.boundY &&
				badGuy[count].y + badGuy[count].borderY > ship.y - ship.boundY && 
				count == CONST_ZERO)
			{
				shipHitBoss:

				if (ship.state != PLAYER_INVULNERABLE){
					ship.lives--;
					al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
					ship.state = PLAYER_INVULNERABLE;
				}
			}
			else if (badGuy[count].x - badGuy[count].borderX < ship.x + ship.boundX &&
				badGuy[count].x + badGuy[count].borderX > ship.x - ship.boundX &&
				badGuy[count].y - badGuy[count].borderY < ship.y + ship.boundY &&
				badGuy[count].y + badGuy[count].borderY > ship.y - ship.boundY &&
				count != CONST_ZERO)
			{
				// SE O JOGADOR COLIDIU COM O BOSS

				goto shipHitBoss;
			}

			for (int j = 0; j < ENEMY_NUM_BULLETS; j++)
			{
				if (proj[j].alive)
				{
					if (proj[j].x < (ship.x + ship.boundX) &&
						proj[j].x > (ship.x - ship.boundX) &&
						proj[j].y < (ship.y + ship.boundY) &&
						proj[j].y > (ship.y - ship.boundY)
						)
					{
						if (ship.state != PLAYER_INVULNERABLE){
							ship.lives--;
							al_play_sample(hurt, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
							ship.state = PLAYER_INVULNERABLE;
							proj[j].alive = false;
						}
					}
				}
			}
		}
	}

	if (ship.lives <= PLAYER_MIN_LIVES)
	{
		ChangeState(LOST);
		InitEverything();
	}
	
}

void AudioSetup()
{
	//std::cout << "CHEGOU AQUI!" << std::endl;
	/*
	voice = al_create_voice(VOICE_SAMPLE_RATE, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	if (voice == NULL || voice == nullptr)
	{
		problems = CANNOT_CREATE_VOICE;
		//isGameLoopDone = true;
		goto endAudio;
	}

	masterMixer = al_create_mixer(MASTER_MIXER_SAMPLE_RATE, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	if (masterMixer == NULL || masterMixer == nullptr)
	{
		problems = CANNOT_CREATE_MASTER_MIXER;
		goto cannotCreateMasterMixer;
	}

	success = al_attach_mixer_to_voice(masterMixer, voice);

	if (success == false)
	{
		problems = CANNOT_ATTACH_MIXER_TO_VOICE;
		goto cannotAttachMixerToVoice;
	}

	mixerBGM = al_create_mixer(MUSIC_MIXER_SAMPLE_RATE, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	if (mixerBGM == NULL || mixerBGM == nullptr)
	{
		problems = CANNOT_CREATE_BGM_MIXER;
		goto YouAttachedMixerToVoice;
	}

	mixerSFX = al_create_mixer(SOUND_MIXER_SAMPLE_RATE, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	if (mixerSFX == NULL || mixerSFX == nullptr)
	{
		problems = CANNOT_CREATE_SFX_MIXER;
		goto YouCreatedMixerBGM;
	}

	mixerStream = al_create_mixer(STREAM_MIXER_SAMPLE_RATE, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	if (mixerStream == NULL || mixerStream == nullptr)
	{
		problems = CANNOT_CREATE_STREAM_MIXER;
		goto YouCreatedMixerSFX;
	}

	success = al_attach_mixer_to_mixer(mixerBGM, masterMixer);

	if (success == false)
	{
		problems = CANNOT_ATTACH_BGM_MIXER_TO_MASTER_MIXER;
		goto YouCreatedMixerStream;
	}

	success = al_attach_mixer_to_mixer(mixerSFX, masterMixer);

	if (success == false)
	{
		problems = CANNOT_ATTACH_SFX_MIXER_TO_MASTER_MIXER;
		goto YouAttachedMusicMixerToMasterMixer;
	}

	success = al_attach_mixer_to_mixer(mixerModule, masterMixer);

	if (success == false)
	{
		problems = CANNOT_ATTACH_MODULE_MIXER_TO_MASTER_MIXER;
		goto YouAttachedSoundMixerToMasterMixer;
	}

	success = al_attach_mixer_to_mixer(mixerStream, masterMixer);

	if (success == false)
	{
		problems = CANNOT_ATTACH_STREAM_MIXER_TO_MASTER_MIXER;
		goto YouAttachedModuleMixerToMasterMixer;
	}

	*/

	//music.openFromFile("assets/chemtrails/song.ogg");
	//music2.openFromFile("assets/chemtrails/bongos.ogg");

	//music.setVolume(100);
	//music2.setVolume(25);

	//voice = al_create_voice(48000, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	//masterMixer = al_create_mixer(48000, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);

	//al_attach_mixer_to_voice(masterMixer, voice);

	
	if (!al_reserve_samples(NUM_SOUNDS))
	{
		//std::cout << "CANNOT RESERVE SOUND SAMPLES!" << std::endl;
		problems = CANNOT_RESERVE_SAMPLES;
		return;
		//goto YouAttachedStreamMixerToMasterMixer;
	}

	//bongos = al_load_sample("assets/chemtrails/bongos.ogg");

	//bongosTrack = al_create_sample_instance(bongos);

	//al_set_sample_instance_playmode(bongosTrack, ALLEGRO_PLAYMODE_LOOP);

	//al_attach_sample_instance_to_mixer(bongosTrack, al_get_default_mixer());


	heart = al_load_sample(HEART_SFX);

	if (heart == NULL || heart == nullptr)
	{
		//std::cout << "CAN'T LOAD HEART SFX!" << std::endl;
	}

	coin = al_load_sample(COIN_SFX);

	shot = al_load_sample(SHOT_SFX);

	hurt = al_load_sample(HURT_SFX);

	sample = al_load_sample(STAGE_01_BGM);
	sample2 = al_load_sample(STAGE_02_BGM);
	bossSample = al_load_sample(BOSS_BGM);
	endingSample = al_load_sample(ENDING_BGM);
	titleSample = al_load_sample(TITLE_BGM);

	stage1 = al_create_sample_instance(sample);
	stage2 = al_create_sample_instance(sample2);
	bossInstance = al_create_sample_instance(bossSample);
	endingInstance = al_create_sample_instance(endingSample);
	titleInstance = al_create_sample_instance(titleSample);

	if (al_set_sample_instance_playmode(stage1, ALLEGRO_PLAYMODE_LOOP) == false)
	{
		problems = CANNOT_SET_SAMPLE_INSTANCE_PLAYMODE;
		goto CannotSetSampleInstancePlaymode;
	}

	if (al_attach_sample_instance_to_mixer(stage1, al_get_default_mixer()) == false)
	//if (al_attach_sample_instance_to_mixer(song, masterMixer) == false)
	{
		problems = CANNOT_ATTACH_SAMPLE_INSTANCE_TO_MIXER;
		return;
	}

	al_attach_sample_instance_to_mixer(stage2, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(bossInstance, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(endingInstance, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(titleInstance, al_get_default_mixer());

	songPosition = songLength = 0;
	songTime = songSpeed = 0.00;

	for (int i = 0; i < NUM_EXPLOSIONS; i++)
	{
		explosion[i] = al_load_sample(EXPLOSION_SAMPLE_PATH);

		if (explosion[i] == NULL)
		{
			//std::cout << "NÃO FOI POSSÍVEL CARREGAR SAMPLE DE BOOM = " << i << " ." << std::endl;
		}
	}

	for (int c = 0; c < NUM_ENEMIES; c++)
	{
		explode[c] = al_load_sample(ENEMY_EXPLOSION_SAMPLE);

		if (explode[c] == NULL)
		{
			//std::cout << "NÃO FOI POSSÍVEL CARREGAR SAMPLE DE INIMIGO = " << c << " ." << std::endl;
		}
	}

	menuSelect = NULL;
	menuCancel = NULL;
	menuConfigure = NULL;
	menuChange = NULL;
	menuOK = NULL;

	menuSelect = al_load_sample(MENU_SELECT_SAMPLE);
	menuChange = al_load_sample(MENU_CHANGE_SAMPLE);
	menuConfigure = al_load_sample(MENU_CONFIGURE_SAMPLE);
	menuCancel = al_load_sample(MENU_CANCEL_SAMPLE);
	menuOK = al_load_sample(MENU_CONFIRM_SAMPLE);

	PC.backgroundMusicVolume = BGM_START_VOLUME;
	PC.soundPan = 0.0;

	SetupAudio();

	return;

CannotSetSampleInstancePlaymode:
	al_destroy_sample_instance(stage1);
	al_destroy_sample(sample);
	//al_destroy_sample_instance(bongosTrack);
	//al_destroy_sample(bongos);
	

	/*
YouAttachedStreamMixerToMasterMixer:
	al_detach_mixer(mixerStream);

YouAttachedModuleMixerToMasterMixer:
	al_detach_mixer(mixerModule);

YouAttachedSoundMixerToMasterMixer:
	al_detach_mixer(mixerSFX);

YouAttachedMusicMixerToMasterMixer:
	al_detach_mixer(mixerBGM);

YouCreatedMixerStream:
	al_destroy_mixer(mixerStream);

YouCreatedMixerSFX:
	al_destroy_mixer(mixerSFX);

YouCreatedMixerBGM:
	al_destroy_mixer(mixerBGM);

YouAttachedMixerToVoice:
	al_detach_mixer(masterMixer);

cannotAttachMixerToVoice:
	al_destroy_mixer(masterMixer);

cannotCreateMasterMixer:
	al_destroy_voice(voice);

endAudio:
	return;
	*/
}

void AudioFinalization()
{
	//music.stop();
	//music2.stop();
	songPosition = songLength = 0;
	songTime = songSpeed = 0.00;

	if (bongosTrack != NULL)
	//al_destroy_sample_instance(bongosTrack);

	if (bongos != NULL)
	//al_destroy_sample(bongos);

	for (int i = 0; i < NUM_EXPLOSIONS; i++)
	{
		if (explosion[i] != NULL && explosion[i] != nullptr)
		{
			al_destroy_sample(explosion[i]);
			//std::cout << "SAMPLE DE BOOM DESTRUIDO " << i << std::endl;
		}
	}

	for (int j = 0; j < NUM_ENEMIES; j++)
	{
		if (explode[j] != NULL && explode[j] != nullptr)
		{
			al_destroy_sample(explode[j]);
			//std::cout << "SAMPLE DE INIMIGOS DESTRUIDO " << j << std::endl;
		}
	}

	//al_stop_samples();
	//al_destroy_sample(bongos);
	/*
	al_detach_mixer(mixerStream);
	al_detach_mixer(mixerModule);
	al_detach_mixer(mixerSFX);
	al_detach_mixer(mixerBGM);
	al_destroy_mixer(mixerStream);
	al_destroy_mixer(mixerSFX);
	al_destroy_mixer(mixerBGM);
	al_detach_mixer(masterMixer);
	al_destroy_mixer(masterMixer);
	al_destroy_voice(voice);
	*/
}

void PreparationScreen()
{
	switch (stage.nextLevel)
	{
	case LEVEL01:

		al_draw_textf(font18, color_transparent, 
			SCREEN_WIDTH * .5, SCREEN_HEIGHT * .5, NULL, 
			"Y'ALL READY FOR THIS?");

		break;
	}
}

void FadingTransition()
{
	switch (fadingType)
	{
	case FADE_IN_WHITE:
		
		break;

	case FADE_OUT_WHITE:
		break;

	case FADE_IN_BLACK:
		break;

	case FADE_OUT_BLACK:
		break;
	default:
		break;
	}
}

void InitFading()
{
	fade = FADE;
	fading = FADING;

	fader = nullptr;

	fader = al_load_bitmap(FADE_BITMAP);

	isFading = false;
	currFrame2 = 0;
}
void DrawFading()
{
	if (fader != NULL && fader != nullptr)
	{
		al_draw_tinted_bitmap(fader, al_map_rgba(0, 0, 0, fade), 0, 0, NULL);
		
		/*
		al_draw_tinted_scaled_bitmap(fader, al_map_rgba(0, 0, 0, fade), 
			0, 0, 
			al_get_bitmap_width(fader), al_get_bitmap_height(fader), 
			0, 0,
			8, 6, NULL);
			*/

		//std::cout << "FADE DRAWING WORKS!" << std::endl;
	}

	
}

void UpdateFading()
{
	if (fade < 0)
	{
		fade = 0;
	}
	if (fade > FADE_LIMIT)
	{
		fade = FADE_LIMIT;
	}

	if (isFading == true)
	{
		if (fading >= 59)
		{
			
		}

		if (fading <= 0)
		{
			//fade = FADING - 1;
			//isFading = false;
		}
	}
	
}

void InitAudio()
{
	
}

void PlayAudio()
{

}
void StopAudio()
{

}
void UpdateAudio()
{

}


void InitChemicalTrails()
{
	for (int j = 0; j < NUM_ENEMIES; j++)
	{
		for (int i = 0; i < ENEMY_NUM_BULLETS; i++)
		{

			ct[i][j].ID = BULLET;
			ct[i][j].alive = false;
			ct[i][j].speed = PLAYER_BULLET_SPEED / 4;
			ct[i][j].angle = 0.00;
			ct[i][j].bulletDirection = -1;
			ct[i][j].coolDown = PLANE_FIRING_COOLDOWN;
			ct[i][j].isFiringBullets = false;
			//ct[i][j].x = SCREEN_WIDTH * 2;
			//ct[i][j].y = SCREEN_HEIGHT	 * 2;
		}
	}
}

void DrawChemicalTrails()
{
	for (int j = 0; j < NUM_ENEMIES; j++)
	{
		for (int i = 0; i < ENEMY_NUM_BULLETS; i++)
		{
			//if (ct[i][j].alive == true && e[j].alive == true)
			if (ct[i][j].alive == true)
			{
				al_draw_filled_circle(ct[i][j].x, ct[i][j].y, 
					PLAYER_BULLET_RADIUS * 2, al_map_rgb(255, 0, 255));
				
			}
		}
	}

}

void FireCT(int enemy, int bullet)
{
	int c;

	for (c = 0; c < ENEMY_NUM_BULLETS; c++)
	{
		if (ct[c][enemy].alive == false)
		{
			// ATIRAR PROJÉTEIS DO INIMIGO CONTRA O JOGADOR

			ct[c][enemy].angle = AngleToTarget(e[enemy].posX, e[enemy].posY, ship.x, ship.y);
			ct[c][enemy].y = e[enemy].posY;
			ct[c][enemy].x = e[enemy].posX;
			ct[c][enemy].alive = true;
			ct[0][enemy].isFiringBullets = true;

			al_play_sample(enemyShot[enemy], PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
			break;
		}
	}

	// FAZER O HELICÓPTRO ATIRAR PROJÉTEIS CONTRA O JOGADOR
}

void UpdateChemicalTrails()
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (ct[0][i].isFiringBullets == true){
			ct[0][i].coolDown--;

			if (ct[0][i].coolDown < 0){
				ct[0][i].isFiringBullets = false;
				ct[0][i].coolDown = PLANE_FIRING_COOLDOWN;
			}
		}
	}

	for (int j = 0; j < NUM_ENEMIES; j++) {
		for (int i = 0; i < ENEMY_NUM_BULLETS; i++) {
			if (ct[i][j].alive == true) {
				//ct[i][j].y += ct[i][j].speed;

				if (e[j].type == ENEMY_PLANE_WHITE)
				{
					ct[i][j].y += (CHEMTRAILS_SPEEDY * std::sin(ct[i][j].angle));
					ct[i][j].x += (CHEMTRAILS_SPEEDX * std::cos(ct[i][j].angle));
				}
				else if (e[j].type == ENEMY_PLANE_RED)
				{
					ct[i][j].y += ( (CHEMTRAILS_SPEEDY + 1) * std::sin(ct[i][j].angle));
					ct[i][j].x += ( (CHEMTRAILS_SPEEDX + 1) * std::cos(ct[i][j].angle));
				}
				//ct[i][j].y += (CHEMTRAILS_SPEEDY * std::sin(e[j].angle));
				//ct[i][j].x += (CHEMTRAILS_SPEEDX * std::cos(e[j].angle));

				if (e[j].angle < CONST_ZERO)
				{
					e[j].angle = CONST_ZERO;
				}

				if (e[j].angle > CONST_360)
				{
					e[j].angle = CONST_360;
				}

				if (ct[i][j].x < 0 ||
					ct[i][j].y < 0 ||
					ct[i][j].x > SCREEN_WIDTH ||
					ct[i][j].y > SCREEN_HEIGHT)
				{
					ct[i][j].alive = false;
				}
			}
		}
	}
}

void InitBoss(int level)
{
	for (int i = 0; i < NUM_BOSSES; i++)
	{
		badGuy[i].ID = BOSS;
		badGuy[i].angle = 0.00;
		badGuy[i].attackDir = -1;
		badGuy[i].currState = BOSS_ANIMATING;
		badGuy[i].currFrame = BOSS_CUTSCENE;
		badGuy[i].borderX = BOSS01_BORDERX;
		badGuy[i].borderY = BOSS01_BORDERY;
		badGuy[i].image = al_load_bitmap(BOSS01_BITMAP_PATH);

		if (badGuy[i].image != nullptr || badGuy[i].image != NULL)
		{
			badGuy[i].imageWidth = al_get_bitmap_width(badGuy[i].image);

			badGuy[i].imageHeight = al_get_bitmap_height(badGuy[i].image);

			al_convert_mask_to_alpha(badGuy[i].image, al_map_rgb(255, 0, 255) );
		}
		badGuy[i].isAlive = false;
		badGuy[i].gotHit = false;
		badGuy[i].hitFrames = BOSS01_INVULNERABILITY_COOLDOWN;
		badGuy[i].isInvulnerable = false;
		badGuy[i].numLives = BOSS01_LIVES;
		badGuy[i].numTrans = BOSS01_NUM_PHASES;
		badGuy[0].transPhase = 0;
		badGuy[i].radius = 0.00;
		badGuy[i].speed = BOSS01_SPEED;
		badGuy[i].spriteDir = -1;
		badGuy[i].x = BOSS01_POSITIONX;
		badGuy[i].y = BOSS01_POSITIONY;

		if (badGuy[0].shoot == NULL)
		{
			badGuy[0].shoot = al_load_sample(BOSS01_SHOT_SAMPLE_PATH);
		}

		if (badGuy[0].hurt == NULL)
		{
			badGuy[0].hurt = al_load_sample(BOSS01_HURT_SAMPLE_PATH);
		}
		
		if (i == CONST_ONE)
		{
			badGuy[i].borderX = BOSS02_BOUNDX;
			badGuy[i].borderY = BOSS02_BOUNDY;
			badGuy[i].image = al_load_bitmap(BOSS02_BITMAP_PATH);

			if (badGuy[i].image != NULL)
			{
				badGuy[i].imageWidth = al_get_bitmap_width(badGuy[i].image);
				badGuy[i].imageHeight = al_get_bitmap_height(badGuy[i].image);
				al_convert_mask_to_alpha(badGuy[i].image, al_map_rgb(255, 0, 255));
			}

			badGuy[i].hitFrames = BOSS02_INVULNERABILITY_COOLDOWN;
			badGuy[i].numLives = BOSS02_LIVES;
			badGuy[i].numTrans = BOSS02_NUM_PHASES;
			badGuy[0].transPhase = 0;
			badGuy[i].radius = BOSS02_RADIUS;
			badGuy[i].speed = BOSS02_SPEED;
			badGuy[i].x = BOSS02_STARTX;
			badGuy[i].y = BOSS02_STARTY;
			badGuy[i].currFrame = BOSS02_ATTACK_COOLDOWN;
		}
	}

}

void DrawBoss(int level, int phase)
{
	// DESENHAR APENAS O BOSS EM CADA NÍVEL/FASE DO JOGO

	if (gameplay.currentFrame >= LEVEL_ENDING)
	{
		int count = -1;

		if (gameplay.currentLevel == LEVEL01)
		{
			count = CONST_ZERO;
		}
		else if (gameplay.currentLevel == LEVEL02)
		{
			count = CONST_ONE;
		}
		else if (gameplay.currentLevel == LEVEL03)
		{
			count = CONST_TWO;
		}

		if (badGuy[count].currState == BOSS_ANIMATING){
			al_draw_tinted_bitmap(
				badGuy[count].image,
				al_map_rgba(0, 0, 0, 127),
				badGuy[count].x - badGuy[count].imageWidth / 2,
				badGuy[count].y - badGuy[count].imageHeight / 2,
				ALLEGRO_FLIP_HORIZONTAL
				);
		}
		else
		{
			if (badGuy[count].gotHit == false){
				if (badGuy[count].spriteDir != BOSS_MOVING_RIGHT){
					al_draw_bitmap(badGuy[count].image,
						badGuy[count].x - badGuy[count].imageWidth / 2,
						badGuy[count].y - badGuy[count].imageHeight / 2,
						NULL);
				}
				else if (badGuy[count].spriteDir == BOSS_MOVING_RIGHT){
					al_draw_bitmap(badGuy[count].image,
						badGuy[count].x - badGuy[count].imageWidth / 2,
						badGuy[count].y - badGuy[count].imageHeight / 2,
						ALLEGRO_FLIP_HORIZONTAL);
				}
			}
			else
			{
				if (badGuy[count].spriteDir != BOSS_MOVING_RIGHT){
					al_draw_tinted_bitmap(
						badGuy[count].image,
						color_red,
						badGuy[count].x - badGuy[count].imageWidth / 2,
						badGuy[count].y - badGuy[count].imageHeight / 2,
						NULL);
				}
				else if (badGuy[count].spriteDir == BOSS_MOVING_RIGHT){
					al_draw_tinted_bitmap(
						badGuy[count].image,
						al_map_rgb(255, 0, 0),
						badGuy[count].x - badGuy[count].imageWidth / 2,
						badGuy[count].y - badGuy[count].imageHeight / 2,
						ALLEGRO_FLIP_HORIZONTAL);
				}
			}
		}
		
	}

	/*

	if (gameplay.currentFrame >= LEVEL_ENDING){
		for (int count = 0; count < NUM_BOSSES; count++){
			if (badGuy[count].image != NULL && badGuy[count].image != nullptr){
				if (badGuy[count].currState == BOSS_ANIMATING){
					al_draw_tinted_bitmap(
						badGuy[count].image,
						al_map_rgba(0, 0, 0, 127), 
						badGuy[count].x - badGuy[count].imageWidth / 2,
						badGuy[count].y - badGuy[count].imageHeight / 2,
						ALLEGRO_FLIP_HORIZONTAL
						);
				}
				else{
					if (badGuy[count].gotHit == false){
						if (badGuy[count].spriteDir != BOSS_MOVING_RIGHT){
							al_draw_bitmap(badGuy[count].image,
								badGuy[count].x - badGuy[count].imageWidth / 2,
								badGuy[count].y - badGuy[count].imageHeight / 2,
								NULL);
						}
						else if (badGuy[count].spriteDir == BOSS_MOVING_RIGHT){
							al_draw_bitmap(badGuy[count].image,
								badGuy[count].x - badGuy[count].imageWidth / 2,
								badGuy[count].y - badGuy[count].imageHeight / 2,
								ALLEGRO_FLIP_HORIZONTAL);
						}
					}
					else{
						if (badGuy[count].spriteDir != BOSS_MOVING_RIGHT){
							al_draw_tinted_bitmap(
								badGuy[count].image,
								color_red,
								badGuy[count].x - badGuy[count].imageWidth / 2,
								badGuy[count].y - badGuy[count].imageHeight / 2,
								NULL);
						}
						else if (badGuy[count].spriteDir == BOSS_MOVING_RIGHT){
							al_draw_tinted_bitmap(
								badGuy[count].image,
								al_map_rgb(255, 0, 0),
								badGuy[count].x - badGuy[count].imageWidth / 2,
								badGuy[count].y - badGuy[count].imageHeight / 2,
								ALLEGRO_FLIP_HORIZONTAL);
						}
					}
				}
			}
		}
	}
	*/
}

void StartBoss(int level)
{

}

void UpdateBoss(int level, int phase)
{
	int movement = 0;

	if (gameplay.currentFrame >= LEVEL_ENDING){

		if (gameplay.currentLevel == LEVEL01)
		{
			if (badGuy[0].currState == BOSS_ANIMATING){

				badGuy[0].x += badGuy[0].speed;

				if (badGuy[0].x >= SCREEN_WIDTH - 1)
				{
					badGuy[0].currState = BOSS_GETTING_READY;
					//badGuy[0].isAlive = true;
				}
			}
			else if (badGuy[0].currState == BOSS_GETTING_READY)
			{
				if (badGuy[0].currFrame > 0)
				{
					badGuy[0].currFrame--;
				}
				else
				{
					badGuy[0].currState = BOSS_IDLING;
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN;
					badGuy[0].isAlive = true;
				}
			}
			else if (badGuy[0].currState == BOSS_IDLING 
				|| badGuy[0].currState == BOSS_GETTING_HIT)
			{

				if (badGuy[0].isAlive == true)
				{
					
					if (badGuy[0].gotHit == true)
					{
						if (badGuy[0].hitFrames > 0)
						{
							badGuy[0].hitFrames--;
						}
						else
						{
							badGuy[0].hitFrames = BOSS01_INVULNERABILITY_COOLDOWN;
							badGuy[0].gotHit = false;
						}
					}

					if (badGuy[0].numLives <= BOSS01_LIVES * .5)
					{
						if (badGuy[0].transPhase == 1 || badGuy[0].transPhase == 2)
						{
							if (badGuy[0].y <= 0)
							{
								//badGuy[0].x++;
								badGuy[0].spriteDir = BOSS_MOVING_DOWN;
							}
							else if (badGuy[0].y >= SCREEN_HEIGHT)
							{
								//badGuy[0].x--;
								badGuy[0].spriteDir = BOSS_MOVING_UP;
							}
						}
						else if (badGuy[0].transPhase == 2)
						{
							if (badGuy[0].x <= 0)
							{
								//badGuy[0].x++;
								//badGuy[0].spriteDir = BOSS_MOVING_RIGHT;
							}
							else if (badGuy[0].x >= SCREEN_WIDTH)
							{
								//badGuy[0].x--;
								//badGuy[0].spriteDir = BOSS_MOVING_LEFT;
							}
						}
						if (badGuy[0].spriteDir == BOSS_MOVING_RIGHT)
						{
							//badGuy[0].x += badGuy[0].speed;
						}
						else if (badGuy[0].spriteDir == BOSS_MOVING_LEFT)
						{
							//badGuy[0].x -= badGuy[0].speed;
						}
						else if (badGuy[0].spriteDir == BOSS_MOVING_UP)
						{
							if (badGuy[0].transPhase == 1)
							{
								badGuy[0].y -= badGuy[0].speed / 3;
							}
							else if (badGuy[0].transPhase == 2)
							{
								badGuy[0].y -= badGuy[0].speed / 2;
							}
						}
						else if (badGuy[0].spriteDir == BOSS_MOVING_DOWN)
						{
							if (badGuy[0].transPhase == 1)
							{
								badGuy[0].y += badGuy[0].speed / 3;
							}
							else if (badGuy[0].transPhase == 2)
							{
								badGuy[0].y += badGuy[0].speed / 2;
							}
						}
					}
					else if (badGuy[0].numLives <= BOSS01_LIVES * 0.0)
					{
						//badGuy[0].isAlive = false;
						//badGuy[0].currFrame2 = BOSS_DEATH_TIMER;
						//StartExplosion(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					}
				}
				else
				{
					//StartExplosion(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					// BOSS WITH NO LIVES
					if (badGuy[0].currFrame2 > 0)
					{
						badGuy[0].currFrame2--;
					}
					else {
						badGuy[0].currFrame2 = BOSS_DEATH_TIMER;
					}

					if (badGuy[0].currFrame2 == BOSS_DEATH_TIMER / 3)
					{
						//StartExplosion(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
					}
				}
			}
			else if (badGuy[0].currState == BOSS_DYING || badGuy[0].numLives < 0.0)
			{
				//========================================================
				//
				// O BOSS FOI DERROTADO PELO JOGADOR
				//
				//========================================================

				for (int j = 0; j < BOSS_NUM_BULLETS; j++)
				{
					if (proj[j].alive)
					{
						proj[j].x = proj[j].y = SCREEN_WIDTH * 2;
					}
						
				}
			}
		}
		else if (gameplay.currentLevel == LEVEL02)
		{
			if (badGuy[1].currState == BOSS_ANIMATING){
				badGuy[1].y -= badGuy[1].speed;

				if (badGuy[1].y <= SCREEN_HEIGHT * 0.69)
				{
					badGuy[1].currState = BOSS_IDLING;
					badGuy[1].currFrame = BOSS02_ATTACK_COOLDOWN;
					badGuy[1].currFrame2 = BOSS02_ATTACK_COOLDOWN;
					badGuy[1].isAlive = true;
				}
			}
			else if (badGuy[1].currState == BOSS_GETTING_READY)
			{

			}
			else if (badGuy[1].currState == BOSS_IDLING)
			{
				if (badGuy[1].gotHit == true)
					badGuy[1].hitFrames--;

				if (badGuy[1].hitFrames > BOSS02_INVULNERABILITY_COOLDOWN)
				{
					badGuy[1].hitFrames = BOSS02_INVULNERABILITY_COOLDOWN;
				}
				if (badGuy[1].hitFrames <= 0 && badGuy[1].gotHit == true)
				{
					badGuy[1].hitFrames = BOSS02_INVULNERABILITY_COOLDOWN;
					badGuy[1].gotHit = false;
				}

				if (badGuy[1].numLives >= BOSS02_LIVES * 0.55 && badGuy[1].numLives < BOSS02_LIVES * 0.85){
					badGuy[1].currFrame2 = BOSS02_ATTACK_COOLDOWN / 2;
				}
				else if (badGuy[1].numLives >= BOSS02_LIVES * 0.40 && badGuy[1].numLives < BOSS02_LIVES * 0.55){
					badGuy[1].currFrame2 = (int)(BOSS02_ATTACK_COOLDOWN / 3);
				}
				else if (badGuy[1].numLives >= BOSS02_LIVES * 0.25 && badGuy[1].numLives < BOSS02_LIVES * 0.40){
					badGuy[1].currFrame2 = (int)(BOSS02_ATTACK_COOLDOWN / 4);
				}
				else if (badGuy[1].numLives > BOSS02_LIVES * 0.0 && badGuy[1].numLives < BOSS02_LIVES * 0.25){
					badGuy[1].currFrame2 = (int)(BOSS02_ATTACK_COOLDOWN / 3);
				}
			}
			else if (badGuy[1].currState == BOSS_ATTACKING)
			{

			}
			else if (badGuy[1].currState == BOSS_GETTING_HURT)
			{

			}
			else if (badGuy[1].currState == BOSS_GETTING_HIT)
			{
				// SE O CHEFE FOI ATINGIDO PELO JOGADOR

				if (badGuy[1].gotHit == true)
					badGuy[1].hitFrames--;

				if (badGuy[1].hitFrames > BOSS02_INVULNERABILITY_COOLDOWN)
				{
					badGuy[1].hitFrames = BOSS02_INVULNERABILITY_COOLDOWN;
				}
				if (badGuy[1].hitFrames <= 0 && badGuy[1].gotHit == true)
				{
					badGuy[1].hitFrames = BOSS02_INVULNERABILITY_COOLDOWN;
					badGuy[1].gotHit = false;
					badGuy[1].currState = BOSS_IDLING;
				}
			}
			else if (badGuy[1].currState == BOSS_DYING)
			{
				//========================================================
				//
				// O BOSS FOI DERROTADO PELO JOGADOR
				//
				//========================================================

				for (int j = 0; j < BOSS_NUM_BULLETS; j++)
				{
					if (projectiles[j].alive)
						projectiles[j].x = projectiles[j].y = SCREEN_WIDTH * 2;
				}

				badGuy[1].currFrame++;

				if (badGuy[1].currFrame < 0)
				{
					badGuy[1].currFrame = 0;
				}

				if (badGuy[1].currFrame == 25 || badGuy[1].currFrame == 150 || badGuy[1].currFrame == 375){
					StartExplosion(badGuy[1].x, badGuy[1].y, 0);
				}
				else if (badGuy[1].currFrame == 50 || badGuy[1].currFrame == 175 || badGuy[1].currFrame == 400){
					StartExplosion(badGuy[1].x / 2, badGuy[1].y / 2, 0);
				}
				else if (badGuy[1].currFrame == 75 || badGuy[1].currFrame == 200 || badGuy[1].currFrame == 450){
					StartExplosion(badGuy[1].x / 0.25, badGuy[1].y / 0.25, 0);
				}
				else if (badGuy[1].currFrame == 100 || badGuy[1].currFrame == 225 || badGuy[1].currFrame == 425){
					StartExplosion(badGuy[1].x / 2, badGuy[1].y, 0);
				}
				else if (badGuy[1].currFrame == 125 || badGuy[1].currFrame == 250 || badGuy[1].currFrame == 500){
					StartExplosion(badGuy[1].x, badGuy[1].y / 2, 0);
				}
				else if (badGuy[1].currFrame == 275 || badGuy[1].currFrame == 325 || badGuy[1].currFrame == 475){
					StartExplosion(badGuy[1].x * 0.40, badGuy[1].y * 0.40, 0);
				}
				else if (badGuy[1].currFrame == 300 || badGuy[1].currFrame == 350 || badGuy[1].currFrame == 525){
					StartExplosion(badGuy[1].x * 0.75, badGuy[1].y * 0.75, 0);
				}
				else if (badGuy[1].currFrame == 550 || badGuy[1].currFrame == 600)
				{
					StartExplosion(badGuy[1].x - 50, badGuy[1].y + 50, 0);
				}
				else if (badGuy[1].currFrame == 575 || badGuy[1].currFrame == 625)
				{
					StartExplosion(badGuy[1].x + 50, badGuy[1].y - 50, 0);
				}
				else if (badGuy[1].currFrame >= 800)
				{
					ChangeState(ENDING);
				}
			}
			else if (badGuy[1].currState == BOSS_ANIMATING)
			{

			}
		}

		//if (isSongPlaying == false){
		if (gameplay.currentLevel == LEVEL01 || gameplay.currentLevel == LEVEL02)
		{
			al_stop_sample_instance(stage1);	al_stop_sample_instance(stage2);	al_stop_sample_instance(titleInstance);	al_stop_sample_instance(lostSong);
			al_stop_sample_instance(endingInstance);	al_play_sample_instance(bossInstance);	//isSongPlaying = true;

			songPosition = al_get_sample_instance_position(bossInstance);
			songLength = al_get_sample_instance_length(bossInstance);
		}
		//}
		//else{
		//}
	}
}

void InitShot(int level)
{
	for (int i = 0; i < BOSS_NUM_BULLETS; i++){
		proj[i].ID = BULLET;
		proj[i].angle = 0.00;
		proj[i].bulletDirection = -1;
		proj[i].coolDown = BOSS01_ATTACK_COOLDOWN;
		proj[i].currFrame = 0;
		proj[i].isFiringBullets = false;
		proj[i].speed = BOSS01_BULLET_SPEED;
		proj[i].alive = false;
		proj[i].image = NULL;
		proj[i].r = BOSS01_BULLET_RADIUS;
		proj[i].distance = 0.00f;
		proj[i].dx = proj[i].dy = 0.00f;

		projectiles[i].ID = BULLET;
		projectiles[i].angle = 0.00f;
		projectiles[i].bulletDirection = -1;
		projectiles[i].coolDown = BOSS02_ATTACK_COOLDOWN;
		projectiles[i].currFrame = 0;
		projectiles[i].distance = projectiles[i].dx = projectiles[i].dy = 0.00f;
		projectiles[i].alive = false;
		projectiles[i].image = NULL;
		projectiles[i].height = projectiles[i].width = projectiles[i].r = BOSS02_BULLET_RADIUS;
		projectiles[i].shipX = projectiles[i].shipY = projectiles[i].x = projectiles[i].y = 0;
		projectiles[i].isFiringBullets = false;
		projectiles[i].speed = BOSS02_BULLET_SPEED;
	}
}

void DrawShot(int level)
{
	for (int i = 0; i < BOSS_NUM_BULLETS; i++){
		if (proj[i].alive){
			al_draw_filled_circle(proj[i].x, proj[i].y, proj[i].r, al_map_rgb(MAX_RGB_VALUE, CONST_ZERO, MAX_RGB_VALUE));
		}

		if (projectiles[i].alive){
			al_draw_filled_circle(projectiles[i].x, projectiles[i].y, projectiles[i].r, al_map_rgb(MAX_RGB_VALUE, CONST_ZERO, MAX_RGB_VALUE));
		}
	}
}

void FireShot(int level)
{
	int i;

	if (gameplay.currentLevel == LEVEL01){
		if (badGuy[0].currState == BOSS_IDLING){
			for (i = 0; i < BOSS_NUM_BULLETS; i++){
				if (proj[i].alive == false){
					proj[i].angle = AngleToTarget(badGuy[0].x * SPACESHIP_CANNON_X, badGuy[0].y + SPACESHIP_CANNON_Y, ship.x, ship.y);
					angle = proj[i].angle;

					proj[i].bulletDirection = badGuy[0].spriteDir;
					proj[i].y = badGuy[0].y + SPACESHIP_CANNON_Y;
					proj[i].x = badGuy[0].x * SPACESHIP_CANNON_X;
					proj[i].alive = true;

					al_play_sample(badGuy[0].shoot, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				}
			}
		}
	}
	else if (gameplay.currentLevel == LEVEL02){
		if (badGuy[1].currState == BOSS_IDLING){
			for (int count = 0; count < BOSS_NUM_BULLETS; count++){
				// O SEGUNDO CHEFÃO VAI ATIRAR NO JOGADOR

				//std::cout << "SOISAJSALSKAOSKAOSKAOS<---------------------" << std::endl;

				if (projectiles[count].alive == false){
					projectiles[count].angle = AngleToTarget(badGuy[1].x + BOSS02_FIREX, badGuy[1].y + BOSS02_FIREY, ship.x, ship.y);
					projectiles[count].bulletDirection = badGuy[1].spriteDir;
					projectiles[count].y = badGuy[1].y + BOSS02_FIREY;
					projectiles[count].x = badGuy[1].x + BOSS02_FIREX;
					projectiles[count].alive = true;
					al_play_sample(badGuy[0].shoot, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);

					count++;

					if (projectiles[count].alive == false){
						projectiles[count].angle = AngleToTarget(badGuy[1].x - BOSS02_FIREX, badGuy[1].y + BOSS02_FIREY, ship.x, ship.y);
						projectiles[count].bulletDirection = badGuy[1].spriteDir;
						projectiles[count].y = badGuy[1].y + BOSS02_FIREY;
						projectiles[count].x = badGuy[1].x - BOSS02_FIREX;
						projectiles[count].alive = true;
						break;
					}
					
				}
			}
		}
	}
}

void UpdateShot(int level)
{
	int i;

	
	for (i = 0; i < BOSS_NUM_BULLETS; i++ ){
		if (proj[i].alive == true){
			if (proj[i].x < 0 ||
				proj[i].y < 0 ||
				proj[i].x > SCREEN_WIDTH ||
				proj[i].y > SCREEN_HEIGHT)
			{
				proj[i].alive = false;
			}
		}

		if (projectiles[i].alive == true && 
			badGuy[1].currState != BOSS_DYING){
			if (projectiles[i].x < 0 ||
				projectiles[i].y < 0 ||
				projectiles[i].x > SCREEN_WIDTH ||
				projectiles[i].y > SCREEN_HEIGHT)
			{
				projectiles[i].alive = false;
			}
		}
	}

	if ((badGuy[0].currState == BOSS_IDLING || badGuy[0].currState == BOSS_GETTING_HIT) && gameplay.currentFrame >= LEVEL_ENDING){
		for (i = 0; i < BOSS_NUM_BULLETS; i++){
			if (proj[i].alive){
				proj[i].y += (proj[i].speed * std::sin(proj[i].angle));
				proj[i].x += (proj[i].speed * std::cos(proj[i].angle));
			}

			i++;

			if (proj[i].alive){
				proj[i].y += (proj[i].speed * std::sin(proj[i].angle));
				proj[i].x += (proj[i].speed * std::cos(proj[i].angle));
			}

			if (proj[i].x < 0 ||
				proj[i].y < 0 ||
				proj[i].x > SCREEN_WIDTH ||
				proj[i].y > SCREEN_HEIGHT)
			{
				//proj[i].alive = false;
			}
		}

		if (badGuy[0].isAlive == true){
			if (badGuy[0].currFrame <= 0){
				if (badGuy[0].numLives >= BOSS01_LIVES * .85){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN;
					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .75){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 2;
					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .7 && badGuy[0].transPhase <= 0){
					badGuy[0].spriteDir = BOSS_MOVING_UP;
					badGuy[0].transPhase++;
					
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .55){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 3;
					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .45){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 4;
					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .4 && badGuy[0].transPhase == 1){
					//badGuy[0].spriteDir = BOSS_MOVING_DOWN;
					badGuy[0].transPhase++;
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .35){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 5;
					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .25){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 4;

					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .15){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 6;

					FireShot(-1);
				}
				else if (badGuy[0].numLives >= BOSS01_LIVES * .05){
					badGuy[0].currFrame = BOSS01_ATTACK_COOLDOWN / 5;

					FireShot(-1);
				}
				else if (badGuy[0].numLives <= BOSS01_LIVES * 0.0){
					if (badGuy[0].currFrame2 >= BOSS_DEATH_TIMER){
						
					}
					else
					{
						//badGuy[0].currFrame = 0;
					}
				}
			}
			else{

				if (badGuy[0].numLives > 0.0){
					badGuy[0].currFrame--;
				}
				else
				{
					//badGuy[0].currFrame++;
				}
			}
		}
		else {
			
		}
	}
	else if (badGuy[1].currState == BOSS_IDLING && gameplay.currentFrame >= LEVEL_ENDING && gameplay.currentLevel == LEVEL02){
		// SEGUNDO BOSS DO JOGO

		for (i = 0; i < BOSS_NUM_BULLETS; i++){
			if (proj[i].alive == true){
				proj[i].y += (proj[i].speed) * std::sin(proj[i].angle);
				proj[i].x += (proj[i].speed)* std::cos(proj[i].angle);
			}

			if (projectiles[i].alive == true){
				projectiles[i].y += (projectiles[i].speed) * std::sin(projectiles[i].angle);
				projectiles[i].x += (projectiles[i].speed) * std::cos(projectiles[i].angle);
			}
		}

		if (badGuy[1].isAlive == true){
			if (badGuy[1].currFrame <= 0){
				// BOSS COMEÇAR A ATIRAR PROJÉTEIS NO JOGO
				badGuy[1].currFrame = badGuy[1].currFrame2;
				FireShot(0);
			}
			else{
				// CONTAGEM DE FRAMES PARA ATIRAR PROJÉTEIS
				badGuy[1].currFrame--;
			}
		}
	}

	//
	// CONTINUAR PROGRAMAÇÃO A PARTIR DAQUI!
	//

	
}

void RechargeShot(int level, int phase)
{

}

void InitExplosion()
{
	int count;

	for (count = 0; count < NUM_EXPLOSIONS; count++)
	{
		explosions[count].ID = ANIMATION;
		explosions[count].alive = false;
		explosions[count].direction = 1;
		explosions[count].image = al_load_bitmap(EXPLOSION_BITMAP);

		if (explosions[count].image != NULL && explosions[count].image != nullptr)
		{
			explosions[count].width = al_get_bitmap_width(explosions[count].image);
			explosions[count].height = al_get_bitmap_height(explosions[count].image);
			al_convert_mask_to_alpha(explosions[count].image, al_map_rgb(MAX_RGB_VALUE, MIN_RGB_VALUE, MAX_RGB_VALUE));
			explosions[count].explosionType = EXP_IMAGE;
		}
		else
		{
			explosions[count].explosionType = EXP_PRIMITIVE;
		}
		explosions[count].numFrames = EXPLOSION_TIMER;
		explosions[count].speed = -EXPLOSION_SPEED;
	}
}

void DrawExplosion()
{
	int i;

	for (i = 0; i < NUM_EXPLOSIONS; i++)
	{
		if (explosions[i].alive == true)
		{
			if (explosions[i].explosionType == EXP_IMAGE)
			{
				al_draw_bitmap(explosions[i].image,
					explosions[i].x - explosions[i].width / 2,
					explosions[i].y - explosions[i].height / 2,
					NULL);
			}
			else
			{
				al_draw_filled_circle(explosions[i].x, explosions[i].y, explosions[i].width / 2, al_map_rgb(MAX_RGB_VALUE, MIN_RGB_VALUE, MIN_RGB_VALUE));
			}
		}
	}
}

void StartExplosion(double x, double y, double speed)
{
	int num;

	for (num = 0; num < NUM_EXPLOSIONS; num++)
	{
		if (explosions[num].alive == false)
		{
			explosions[num].x = x;
			explosions[num].y = y;
			explosions[num].numFrames = EXPLOSION_TIMER;
			explosions[num].speed = speed;

			al_play_sample(explosion[num], PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);

			explosions[num].alive = true;
			break;
		}
	}
}

void UpdateExplosion()
{
	int i;

	for (i = 0; i < NUM_EXPLOSIONS; i++)
	{
		if (explosions[i].alive == true)
		{
			if (explosions[i].numFrames > 0)
			{
				explosions[i].numFrames--;

				if (badGuy[0].numLives > 0)
					explosions[i].x -= explosions[i].speed;
			}
			else
			{
				
				explosions[i].alive = false;
			}

			if (explosions[i].alpha < MIN_RGB_VALUE)
			{
				explosions[i].alpha = MIN_RGB_VALUE;
			}
			if (explosions[i].alpha > MAX_RGB_VALUE)
			{
				explosions[i].alpha = MAX_RGB_VALUE;
			}
		}
	}
}

void DrawHUD()
{
	// DESENHAR ELEMENTOS DO MENU NO DISPLAY DO JOGO

	/*al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0,
		"Health %d | Score %d | Collectibles %d | Frames: %d", 
		ship.lives, ship.score, ship.collectibles, gameplay.currentFrame);
		*/

	// DESENHAR "HEALTH POINTS" NA TELA, 
	/*
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025 + HUD_SPACING, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025 + HUD_SPACING * 2, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025 + HUD_SPACING * 3, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025 + HUD_SPACING * 4, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025 + HUD_SPACING * 5, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 5, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * 0.025 + HUD_SPACING * 6, SCREEN_HEIGHT * 0.025, 0.35, 0.35, 0, NULL);
	DrawFontNumber(ship.lives, SCREEN_WIDTH * 0.025 + HUD_SPACING * 7, SCREEN_HEIGHT * 0.025, 0.40, 0.40, 96, 96);
	*/

	// DESENHAR "HITS:" NA TELA DO JOGO NA JANELA
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 0, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 1, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 2, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96 * 2, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 3, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 5, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 4, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	DrawFontNumber(ship.lives, SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 5, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 96, 96);

	// DESENHAR "COINS:" NA TELA DO JOGO
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 7, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96 * 1, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 8, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 1, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 9, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 1, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 10, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96 * 2, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 11, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 5, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 12, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	//DrawFontNumber(ship.lives, SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 13, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 96, 96);
	al_draw_textf(font18, color_magenta, SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 13, SCREEN_HEIGHT * HUD_NUMBERS, NULL, "%02d", ship.collectibles);

	// DESENHAR "SCORE:" OU "POINTS:" NO JOGO
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96 * 2, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 16, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 17, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96 * 1, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 18, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 19, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 20, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 5, 96, 96, color_magenta, CONST_ONE, CONST_ONE,
		SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 21, SCREEN_HEIGHT * HUD_PLACEMENT, HUD_FONT_SIZE, HUD_FONT_SIZE, 0, NULL);
	al_draw_textf(font18, color_magenta, SCREEN_WIDTH * HUD_PLACEMENT + HUD_SPACING * 22, SCREEN_HEIGHT * HUD_NUMBERS, NULL, "%02d", ship.score);

	al_draw_tinted_bitmap(fader, al_map_rgba(0, 0, 0, fade), 0, 0, NULL);
}

void InitParallaxScrolling()
{
	if (level02_bkg.image == NULL)
	{
		level02_bkg.image = al_load_bitmap(LEVEL02_BACKGROUND);
		al_convert_mask_to_alpha(level02_bkg.image, al_map_rgb(255, 0, 255));
		level02_bkg.height = al_get_bitmap_height(level02_bkg.image);
		level02_bkg.width = al_get_bitmap_width(level02_bkg.image);
	}

	level02_bkg.posX = 0;
	level02_bkg.posY = 0;
	level02_bkg.dirX = 0;
	level02_bkg.dirY = 0;
	level02_bkg.speedX = level02_bkg.speedY = LEVEL02_BACKGROUND_SCROLLING_SPEED;

	if (level02_bkg2.image == NULL)
	{
		level02_bkg2.image = al_load_bitmap(LEVEL02_BACKGROUND2);
		al_convert_mask_to_alpha(level02_bkg2.image, al_map_rgb(255, 0, 255));
		level02_bkg2.height = al_get_bitmap_height(level02_bkg2.image);
		level02_bkg2.width = al_get_bitmap_width(level02_bkg2.image);
	}

	level02_bkg2.posX = 0;
	level02_bkg2.posY = 0;
	level02_bkg2.dirX = 0;
	level02_bkg2.dirY = 0;
	level02_bkg2.speedX = level02_bkg2.speedY = LEVEL02_BACKGROUND2_SCROLLING_SPEED;

	if (level02_bkg_loop.image == NULL)
	{
		level02_bkg_loop.image = al_load_bitmap(LEVEL02_BACKGROUND);
		al_convert_mask_to_alpha(level02_bkg_loop.image, al_map_rgb(255, 0, 255));
		level02_bkg_loop.height = al_get_bitmap_height(level02_bkg_loop.image);
		level02_bkg_loop.width = al_get_bitmap_width(level02_bkg_loop.image);
	}

	level02_bkg_loop.posX = SCREEN_WIDTH;
	level02_bkg_loop.posY = 0;
	level02_bkg_loop.dirX = 0;
	level02_bkg_loop.dirY = 0;
	level02_bkg_loop.speedX = level02_bkg_loop.speedY = LEVEL02_BACKGROUND_SCROLLING_SPEED;

	if (level02_bkg2_loop.image == NULL)
	{
		level02_bkg2_loop.image = al_load_bitmap(LEVEL02_BACKGROUND2);
		al_convert_mask_to_alpha(level02_bkg2_loop.image, al_map_rgb(255, 0, 255));
		level02_bkg2_loop.height = al_get_bitmap_height(level02_bkg2_loop.image);
		level02_bkg2_loop.width = al_get_bitmap_width(level02_bkg2_loop.image);
	}

	level02_bkg2_loop.posX = SCREEN_WIDTH;
	level02_bkg2_loop.posY = 0;
	level02_bkg2_loop.dirX = 0;
	level02_bkg2_loop.dirY = 0;
	level02_bkg2_loop.speedX = level02_bkg2_loop.speedY = LEVEL02_BACKGROUND2_SCROLLING_SPEED;
}

void ChangeEnemy()
{
	if (stage.levelNumber == LEVEL02)
	{
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			if (e[i].image != NULL && e[i].image != nullptr)
			{
				al_destroy_bitmap(e[i].image);
				e[i].image = NULL;

				e[i].image = al_load_bitmap(COPTER_BITMAP);

				if (e[i].image != NULL && e[i].image != nullptr)
				{
					e[i].width = al_get_bitmap_width(e[i].image);
					e[i].height = al_get_bitmap_height(e[i].image);
					al_convert_mask_to_alpha(e[i].image, al_map_rgb(255, 0, 255));
					e[i].type = ENEMY_COPTER_BLACK;
					al_play_sample(coin, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);

					//std::cout << "ENEMY COPTER BLACK!!!!! askalskaosjaosajsojaosjaosdsudisudsijdiasj" << std::endl;
				}
			}
		}

		if (enemyType == ENEMY_COPTER_BLACK)
		{
			
		}
		else if (enemyType == ENEMY_COPTER_RED)
		{

		}
	}
}

void InitProjectile(int enemy)
{
	for (int i = 0; i < NUM_COPTERS; i++)
	{
		for (int j = 0; j < COPTER_NUM_BULLETS; j++)
		{
			projs[i][j].alive = false;
			projs[i][j].angle = 0.00;
			projs[i][j].bulletDirection = -1;
			projs[i][j].coolDown = COPTER_COOLDOWN;
			projs[i][j].currFrame = 0;
			projs[i][j].distance = 0;
			projs[i][j].dx = projs[i][j].dy = 0;
			projs[i][j].isFiringBullets = false;
			projs[i][j].originX = 0;
			projs[i][j].originY = 0;
			projs[i][j].r = COPTER_BULLET_RADIUS;
			projs[i][j].speed = COPTER_BULLET_SPEED;
			projs[i][j].x = projs[i][j].y = 0;
			projs[i][j].ID = BULLET;
			projs[i][j].image = NULL;
		}
	}
}

void DrawProjectile(int enemy)
{
	for (int j = 0; j < NUM_COPTERS; j++)
	{
		for (int i = 0; i < COPTER_NUM_BULLETS; i++)
		{
			if (projs[j][i].alive == true)
			{
				al_draw_filled_circle(projs[j][i].x,
					projs[j][i].y,
					projs[j][i].r,
					color_red);
			}
		}
	}
}

void FireProjectile(int enemy)
{
	// COPTER ATIRA PROJÉTEIS CONTRA O JOGADOR

	if (gameplay.currentLevel != LEVEL02)
	{
		return;
	}

	for (int j = 0; j < NUM_COPTERS; j++)
	{
		if (copter[j].alive == true && copter[j].isAttacking == false)
		{
			for (int i = 0; i < COPTER_NUM_BULLETS; i++)
			{
				if (projs[j][i].alive == false)
				{
					// SE O INIMIGO É HELICÓPTERO PRETO
					if (copter[j].type == ENEMY_COPTER_BLACK)	return;

					// local de origem do projétil do helicóptero
					double cx = copter[j].posX;
					double cy = copter[j].posY;
					double sx = ship.x;
					double sy = ship.y;
					double x = projs[j][i].x = cx + COPTER_BULLET_INIT_X;
					double y = projs[j][i].y = cy + COPTER_BULLET_INIT_Y;
					double a = projs[j][i].angle = AngleToTarget(x, y, sx, sy);

					al_play_sample(enemyShot[j], PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
					projs[j][i].alive = true;

					copter[j].isAttacking = true;

					break;
				}
			}
		}
	}
}

void UpdateProjectile(int enemy)
{
	for (int j = 0; j < NUM_COPTERS; j++)
	{
		for (int i = 0; i < COPTER_NUM_BULLETS; i++)
		{
			if (projs[j][i].alive == true)
			{
				//projs[j][i].x -= projs[j][i].speed;

				// DESLOCAR O PROJÉTIL NA DIREÇÃO DO JOGADOR

				// SE O HELICÓPTERO É BRANCO

				if (copter[j].type == ENEMY_COPTER_WHITE)
				{
					projs[j][i].y += projs[j][i].speed * std::sin(projs[j][i].angle);
					projs[j][i].x += projs[j][i].speed * std::cos(projs[j][i].angle);
				}
				else if (copter[j].type == ENEMY_COPTER_BLUE)
				{
					projs[j][i].y += (projs[j][i].speed - 1) * std::sin(projs[j][i].angle);
					projs[j][i].x += (projs[j][i].speed - 1) * std::cos(projs[j][i].angle);
				}
				else if (copter[j].type == ENEMY_COPTER_RED)
				{
					projs[j][i].y += (projs[j][i].speed + 1) * std::sin(projs[j][i].angle);
					projs[j][i].x += (projs[j][i].speed + 1) * std::cos(projs[j][i].angle);
				}

				if (projs[j][i].x < 0 ||
					projs[j][i].y < 0 ||
					projs[j][i].x > SCREEN_WIDTH ||
					projs[j][i].y > SCREEN_HEIGHT)
				{
					projs[j][i].alive = false;
				}
			}
		}
	}
}

//void EventKeyboardKeyDown(int value);
//void EventKeyboardKeyUp(int value);
//void EventJoystickButtonDown(int value);
//void EventJoystickButtonUp(int value);
//void EventMouseButtonDown(int value);
//void EventMouseButtonUp(int value);

int MapInput(int inputDevice, int oldValue, int newValue)
{
	if (inputDevice == INPUT_DEVICE_KEYBOARD)
	{
		
	}
	else if (inputDevice == INPUT_DEVICE_JOYSTICK)
	{

	}
	else if (inputDevice == INPUT_DEVICE_MOUSE)
	{

	}
	else
	{
		inputDevice = INPUT_DEVICE_UNKNOWN;
	}

	return newValue;
}

void SetDefaultValues()
{
	if (state == OPTIONS || state == SETTING_AUDIO)
	{
		PC.soundPan = 0;

		PC.backgroundMusicVolume = BGM_START_VOLUME;

		PC.soundEffectVolume = SFX_START_VOLUME;

		PC.playerContinues = PLAYER_CONTINUES;

		PC.playerCredits = PLAYER_CREDITS;

		PC.playerLives = PLAYER_LIVES;
	}
	else if (state == CONTROLS)
	{

	}
	else if (state == PASSWORD)
	{

	}

	MenuChangeCommand();

}

void MenuSelectCommand()
{
	StopAllSamples();
	al_play_sample(menuSelect, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MenuChangeCommand()
{
	StopAllSamples();
	al_play_sample(menuChange, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MenuConfigureCommand()
{
	StopAllSamples();
	al_play_sample(menuConfigure, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MenuPauseCommand()
{
	al_play_sample(pauseSample, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void MenuConfirmCommand()
{
	al_play_sample(menuOK, PC.soundEffectVolume, PC.soundPan, PC.playbackSpeed, ALLEGRO_PLAYMODE_ONCE, NULL);
}

//void MenuCancelCommand();
//void MenuPauseCommand();
//void MenuUnpauseCommand();
//void MenuEscapeCommand();

void FadingIncrease()
{
	fade = fade + FADE_INCREASE;
}

void FadingDecrease()
{
	fade = fade + FADE_DECREASE;
}

void StopAllSamples()
{
	al_stop_samples();
}

void SaveGameScreen()
{
	
}

void PauseScreen()
{
	if (fader != NULL && fader != nullptr)
	{

		ALLEGRO_COLOR unselected = al_map_rgb(0, 234, 0);
		ALLEGRO_COLOR selected = al_map_rgb(234, 0, 0);

		// ESCURECER A TELA INTEIRA, COM IMAGEM DE FADING ("FADER")

		// VERIFICAR "PULO" NO DESPAUSAR DA TELA, PORQUE ALGUNS FRAMES DE UPDATE SÃO PULADOS E PERDIDOS NO PROCESSO DE PAUSE-DESPAUSE?

		// DESENHAR PAUSE NA TELA
		al_draw_bitmap_region(menuTitles, 0, 96 * 4, 96 * 2, 96, SCREEN_WIDTH / 2 - 96 * 2, SCREEN_HEIGHT / 3 - 96, NULL);
		al_draw_bitmap_region(menuTitles, 96 * 2, 96 * 3, 96 * 1, 96, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 - 96, NULL);
		al_draw_bitmap_region(menuTitles, 0, 96 * 5, 96 * 2, 96, SCREEN_WIDTH / 2 + 96, SCREEN_HEIGHT / 3 - 96, NULL);

		// DESENHAR OUTRAS COISAS NA TELA
		// OPÇÕES DO MENU DE PAUSE
		
		// OPÇÃO "RESUME" PARA VOLTAR AO JOGO/GAMEPLAY
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 1, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .60, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .64, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .68, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .72, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);

		if (menu.selected == 0){
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 1, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.60, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.64, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.68, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);

		}

		// MOSTRAR OPÇÃO "CONFIGURAR SOM" DO MENU
		if (menu.selected == 1)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 7, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.60, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.64, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.68, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
		}
		else
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.40, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.44, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 7, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.60, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.64, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.68, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
		}

		if (menu.selected == 2) //	"QUIT TO TITLE", "SAIR PARA TÍTULO", OPÇÃO DO MENU
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.38, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.41, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.47, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.60, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.64, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.68, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
		}
		else{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.38, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.41, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.47, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.60, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.64, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.68, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
		}
		if (menu.selected == 3)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.38, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.41, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.47, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.62, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96 * 4, 96, 96, selected, 1, 1, SCREEN_WIDTH * 0.65, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
		}
		else
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.32, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.38, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.41, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 3, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.47, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.56, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.59, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.62, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96 * 4, 96, 96, unselected, 1, 1, SCREEN_WIDTH * 0.65, SCREEN_HEIGHT * 0.75, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0, NULL);
		}
	}
}

void LoadGameScreen()
{
	if (titleImage != NULL && titleImage != nullptr)
	{
		al_draw_bitmap(titleImage, 0, 0, NULL);

		// DESENHAR OPÇÕES DE CARREGAMENTO DE JOGO

		// DESENHAR LETRAS "LOAD"
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * LOAD_START_X, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, CONST_ONE, CONST_ONE, 
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING * 2, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 0, 96, 96, color_white, CONST_ONE, CONST_ONE,
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING * 3.05, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);

		// DESENHAR LETRAS "GAME"
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, CONST_ONE, CONST_ONE,
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING * 5, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, CONST_ONE, CONST_ONE,
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING * 6.125, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96, 96, 96, color_white, CONST_ONE, CONST_ONE,
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING * 7.25, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, CONST_ONE, CONST_ONE,
			SCREEN_WIDTH * LOAD_START_X + LOAD_LETTER_SPACING * 8.3, SCREEN_HEIGHT * LOAD_START_Y, CONST_ONE, CONST_ONE, 0.0, NULL);
	}
}

void QuitToTitleScreen()
{
	if (state == QUIT_GAMEPLAY || state == QUIT_EVERYTHING)
		al_draw_bitmap(lost, 0, 0, NULL);

	if (fader != NULL && fader != nullptr)
	{
		ALLEGRO_COLOR unselected = al_map_rgb(0, 234, 0);
		ALLEGRO_COLOR selected = al_map_rgb(234, 0, 0);
		ALLEGRO_COLOR confirmation = al_map_rgb(255, 255, 0);

		// ESCURECER A TELA INTEIRA, COM IMAGEM DE FADING ("FADER")

		// DESENHAR PAUSE NA TELA

		if (state == QUITTING_GAMEPLAY || state == QUITTING_EVERYTHING){
			al_draw_bitmap_region(menuTitles, 0, 96 * 4, 96 * 2, 96, SCREEN_WIDTH / 2 - 96 * 2, SCREEN_HEIGHT / 3 - 96, NULL);
			al_draw_bitmap_region(menuTitles, 96 * 2, 96 * 3, 96 * 1, 96, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 - 96, NULL);
			al_draw_bitmap_region(menuTitles, 0, 96 * 5, 96 * 2, 96, SCREEN_WIDTH / 2 + 96, SCREEN_HEIGHT / 3 - 96, NULL);
		}
		else if (state == QUIT_GAMEPLAY || state == QUIT_EVERYTHING){
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 2, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 5, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 2, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
		}
		
		

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 0, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.30, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.33, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.36, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			0, 96 * 3, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.42, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 6, 96, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.45, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.48, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 2, 96 * 2, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.54, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 96 * 2, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.57, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96, 96 * 2, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.60, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 4, 0, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.63, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
			96 * 7, 96 * 4, 96, 96, confirmation, 1, 1, SCREEN_WIDTH * 0.66, SCREEN_HEIGHT * .45, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);

		if (menu.selected == 0)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .35, SCREEN_HEIGHT * .55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, selected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		}
		else{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 5, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .35, SCREEN_HEIGHT * .55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 6, 96, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .40, SCREEN_HEIGHT * .55, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		}

		if (menu.selected == 1)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 3, 96, 96, selected, 1, 1, SCREEN_WIDTH * .35, SCREEN_HEIGHT * .65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, selected, 1, 1, SCREEN_WIDTH * .38, SCREEN_HEIGHT * .65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, selected, 1, 1, SCREEN_WIDTH * .41, SCREEN_HEIGHT * .65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		}
		else
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				0, 96 * 3, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .35, SCREEN_HEIGHT * .65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 4, 0, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .38, SCREEN_HEIGHT * .65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont,
				96 * 2, 96 * 2, 96, 96, unselected, 1, 1, SCREEN_WIDTH * .41, SCREEN_HEIGHT * .65, PAUSE_FONT_SIZE, PAUSE_FONT_SIZE, 0.0, NULL);
		}
	}
}

void QuitToOperatingSystem()
{
	if (state == QUIT_EVERYTHING)
		al_draw_bitmap(lost, 0, 0, NULL);

	if (fader != NULL && fader != nullptr)
	{
		ALLEGRO_COLOR unselected = al_map_rgb(0, 234, 0);
		ALLEGRO_COLOR selected = al_map_rgb(234, 0, 0);
		ALLEGRO_COLOR confirmation = al_map_rgb(255, 255, 0);

		// ESCURECER A TELA INTEIRA, COM IMAGEM DE FADING ("FADER")

		// DESENHAR PAUSE NA TELA

		if (state == QUITTING_EVERYTHING){
			al_draw_bitmap_region(menuTitles, 0, 96 * 4, 96 * 2, 96, SCREEN_WIDTH / 2 - 96 * 2, SCREEN_HEIGHT / 3 - 96, NULL);
			al_draw_bitmap_region(menuTitles, 96 * 2, 96 * 3, 96 * 1, 96, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 - 96, NULL);
			al_draw_bitmap_region(menuTitles, 0, 96 * 5, 96 * 2, 96, SCREEN_WIDTH / 2 + 96, SCREEN_HEIGHT / 3 - 96, NULL);
		}
		else if (state == QUIT_EVERYTHING){
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 2, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 5, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 2, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, color_white, 1, 1,
				SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
		}
	}
}

void DrawFontNumber(double number, double x, double y, double scaleX, double scaleY, double sizeX, double sizeY)
{
	// DESENHAR NÚMEROS DA FONTE BITMAP NA TELA DO JOGO

	/*
	12345

	12345 % 10 = 5
	12345 % 100 = 45 / 10 ROUND = 4
	12345 % 1000 = 345 / 100 ROUND = 3

	*/

	double spaceX1 = x + sizeX / 4;
	double spaceX2 = x + ((sizeX / 4) * 3);
	ALLEGRO_COLOR fontColor = al_map_rgb(255, 1, 255);

	double fraction, integer, extraction;

	fraction = std::modf(number, &integer);

	extraction = number * 100;

	//al_draw_textf(font18, color_red, 25, 550, NULL, "NUMBER: %.2lf - FRACTION: %.2lf - INTEGER: %.0lf - EXTRACTED: %.0lf", number, fraction, integer, extraction);

	if (extraction < CONST_100){
		//al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 3, sizeX, sizeY, color_red, 1, 1, x + spaceX1, y, scaleX, scaleY, 0, NULL);
		//al_draw_textf(font18, al_map_rgb(255, 0, 255), 15, 15, NULL, "NUMERO MENOR QUE 100");
	}

	if (extraction < CONST_TEN){
		//al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 3, sizeX, sizeY, color_red, 1, 1, x, y, scaleX, scaleY, 0, NULL);
		//al_draw_textf(font18, al_map_rgb(255, 0, 255), 45, 45, NULL, "NUMERO MENOR QUE 10");
	}

	if (number == CONST_ZERO){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 3, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_ONE){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 3, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_TWO){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 3, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_THREE){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96 * 3, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_FOUR){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 96 * 3, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_FIVE){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 4, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_SIX){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 4, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_SEVEN){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96 * 4, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_EIGHT){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 4, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	else if (number == CONST_NINE){
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 4, sizeX, sizeY, fontColor, 1, 1, x, y, scaleX, scaleY, 0, NULL);
	}
	
}

void ifEventIsJoystickButtonDown()
{
	int jButton = ev.joystick.button;

	//std::cout << "BOTÃO DO JOYSTICK PRESSIONADO = " << jButton << std::endl;

	
}

void ifEventIsJoystickButtonUp()
{

}

void ifEventIsJoystickAxes()
{
	float arrow = ev.joystick.pos;
	int axis = ev.joystick.axis;

	//std::cout << "POSICAO = " << arrow << " , EIXO = " << axis << " " << std::endl;

	if (arrow == -CONST_ONE)
	{
		MoveShipUp();
	}
	else if (arrow == CONST_ONE)
	{
		MoveShipDown();
	}

}

void InitEverything()
{
	/*
	for (int bSize = 0; bSize < NUM_BOSSES; bSize++)
	{
	badGuy[bSize].angle = CONST_ZERO;
	badGuy[bSize].currState = CONST_ZERO;
	badGuy[bSize].gotHit = false;
	badGuy[bSize].transPhase = CONST_ZERO;
	badGuy[bSize].isInvulnerable = false;
	badGuy[bSize].isAlive = false;
	badGuy[0].numLives = BOSS01_LIVES;
	badGuy[1].numLives = BOSS02_LIVES;
	badGuy[2].numLives = -1;
	}
	*/
	ship.quantWeapons = PLAYER_NUM_WEAPONS;
	ship.nextWeapon = 0;
	showCollision = false;
	currFrame = 0;

	gameplay.currentFrame = CONST_ZERO;
	gameplay.currentFrame2 = CONST_ZERO;
	gameplay.bossFrame = CONST_ZERO;
	menu.selected = CONST_ZERO;

	ship.state = PLAYER_VULNERABLE;
	ship.invulnerability = PLAYER_INVULNERABILITY;
	ship.lives = PLAYER_LIVES;
	ship.collectibles = CONST_ZERO;
	ship.score = CONST_ZERO;
	ship.isFiringBullets = false;

	InitShip();
	InitBullet();
	//InitComet();
	//Comet_InitBullet();
	InitBoss(-1);
	InitShot(-1);
	InitExplosion();
	InitProjectile(-1);
	InitParallaxScrolling();
	InitEnemy();
	InitCollectible();
	InitChemicalTrails();


}

void LoseScreen()
{
	// TELA QUE APARECE PARA O JOGADOR CASO ELE PERCA A FASE

	al_draw_bitmap(lost, 0, 0, NULL);

	// DESENHAR "YOU LOST" OU "GAME OVER" NA TELA

	ALLEGRO_COLOR selected = al_map_rgb(234, 0, 0);
	ALLEGRO_COLOR confirmation = al_map_rgb(234, 234, 0);

	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, 1, 1, 
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 1, 1, 
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96, 96, 96, color_white, 1, 1, 
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 2, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);

	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 5, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_SPACING * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT, 1, 1, 0, NULL);

	// OPÇÃO "CONTINUE" OU "TRY AGAIN" 
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, color_white, 1, 1, 
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 10, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 11, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 12, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 13, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	if (menu.selected == 0)
	{
		// SE A PRIMEIRA OPÇÃO ESTIVER SELECIONADA
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 10, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 11, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 12, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 13, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	}

	// OPÇÃO "QUIT TO TITLE SCREEN" DO JOGO
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 1, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 2, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 4, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 10, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 11, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 1, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 12, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 13, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 15, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 16, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 17, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 18, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 19, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 20, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	if (menu.selected == 1)
	{
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 1, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 2, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 4, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 10, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 11, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 1, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 12, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 13, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 15, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 16, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 17, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 18, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 19, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 20, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 7,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	}

	// OPÇÃO "QUIT EVERYTHING" DO JOGO
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 4, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	// EVERYTHING
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 10, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 11, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 3, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 12, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 13, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 14, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 1, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 15, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 1, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 16, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, 1, 1,
		SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 17, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
		LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

	if (menu.selected == 2)
	{
		// OPÇÃO "QUIT EVERYTHING" DO JOGO
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 3, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 4, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 5, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 6, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);

		// EVERYTHING
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 8, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 10, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 11, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 3, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 12, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 13, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 14, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 1, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 15, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 1, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 16, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
		al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, selected, 1, 1,
			SCREEN_WIDTH * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 17, SCREEN_HEIGHT * LOST_SCREEN_PLACEMENT + LOST_SCREEN_LETTERS * 9,
			LOST_SCREEN_FONT_SIZE, LOST_SCREEN_FONT_SIZE, 0, NULL);
	}
}

void HandleBinaryFile()
{
	// MANIPULAÇÃO DE ARQUIVOS EM MODO BINÁRIO

	// PONTEIRO PARA O ARQUIVO A SER MANIPULADO
	FILE *p = NULL;

	// TAMANHO DO DADO A SER ESCRITO NO ARQUIVO
	size_t fileData;

	// TAMANHO DO ARQUIVO BINÁRIO CRIADO
	long fileSize;

	// TENTA ABRIR O ARQUIVO PARA LEITURA EM MODO BINÁRIO
	p = fopen("COISAS3.BIN", "rb+");

	if (p == NULL && p == nullptr)
	{

		// SE NÃO HÁ ARQUIVO PARA LER, ENTÃO ESCREVA ERRO NA TELA
		printf("ERROR OCURRED! THERE IS NO FILE HERE! \n");
		printf("ERROR CODE: %d\n\n", errno);
		getchar();

		// CRIAR O ARQUIVO BINÁRIO PARA ESCREVER NELE
		p = fopen("COISAS3.BIN", "wb+");

		if (p == NULL)
		{
			// SE HOUVE ERRO NA CRIAÇÃO DO ARQUIVO BINÁRIO
			printf("ERROR OCURRED! cannot create binary file\n");
			printf("ERROR CODE: %d\n\n", errno);
			exit(-9);
		}
	}

	// ARQUIVO BINÁRIO FOI CRIADO, JÁ EXISTE

	// STRING PARA ESCREVER NO ARQUIVO
	char content[] = "LOREM IPSUM";

	// ESCREVER DADOS NO ARQUIVO BINÁRIO

	/*
	fwrite(content,
	sizeof(content[0]),
	sizeof(content) / sizeof(content[0]),
	p
	);
	*/

	// BUSCAR O FINAL DO ARQUIVO BINÁRIO
	fseek(p, 0, SEEK_END);

	// PEGAR O TAMANHO DO ARUIVO
	fileSize = ftell(p);

	// VOLTAR PARA  COMEÇO DO ARQUIVO
	rewind(p);

	// CRIAR E USAR UM BUFFER DE TEXTO
	char* buffer = NULL;
	buffer = (char*)malloc(sizeof(char) * fileSize);

	// SE HOUVER ERRO NA ALOCAÇÃO DO BUFFER DE STRINGS
	if (buffer == NULL && buffer == nullptr)
	{
		printf("ERROR OCURRED!\n");
		printf("ERROR CODE: %d\n\n", errno);
		exit(-99);
	}

	// USAR VARIÁVEL PARA LER DADOS DO ARQUIVO
	fileData = fread(buffer, 1, fileSize, p);

	// VERIFICAR ERROS NA VARIÁVEL DE LEITURA DO DADO
	if (fileData != fileSize)
	{
		printf("ERROR OCURRED!\n");
		printf("ERROR CODE: %d\n\n", errno);
		exit(-999);
	}

	buffer[fileSize - 1] = '\0';
	// IMPRIMIR NA TELA BUFFER LIDO DO ARQUIVO
	printf("CONTEUDO LIDO: \n\n%s\n", buffer);

	// LIBERAR ESPAÇO DE MEMÓRIA OCUPADO PELO PONTEIRO
	fclose(p);

	// LIBERAR MEMÓRIA OCUPADA PELO STRING
	free(buffer); buffer = NULL;
}

void EndingScreen(int endingType)
{
	if (endingType <= 0)
	{
		// SE O ENDING TYPE É ZERO OU "-1"

		// DESENHAR "THE END" NA TELA

		if (endingFrames < ENDING_FRAMES)
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * 3, SCREEN_HEIGHT / 2 - 96, ENDING_FONT_SIZE, ENDING_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * 3 + ENDING_LETTER_SPACING, SCREEN_HEIGHT / 2 - 96, ENDING_FONT_SIZE, ENDING_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * 3 + ENDING_LETTER_SPACING * 2, SCREEN_HEIGHT / 2 - 96, ENDING_FONT_SIZE, ENDING_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * 3 + ENDING_LETTER_SPACING * 4, SCREEN_HEIGHT / 2 - 96, ENDING_FONT_SIZE, ENDING_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 1, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * 3 + ENDING_LETTER_SPACING * 5, SCREEN_HEIGHT / 2 - 96, ENDING_FONT_SIZE, ENDING_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * 3 + ENDING_LETTER_SPACING * 6, SCREEN_HEIGHT / 2 - 96, ENDING_FONT_SIZE, ENDING_FONT_SIZE, 0, NULL);
		}
		else if (endingFrames < CREDITS_FRAMES )
		{
			// "CREATED" WORD
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 1, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 2, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 3, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 4, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 5, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 6, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 7, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			// "BY" WORD
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 9, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 3, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 10, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			// "AUTHOR" WORD -> RICARDO GRETTER
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 2, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 3, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 4, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 5, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 6, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 7, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 9, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96 * 4, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 9.75, SCREEN_HEIGHT / 2 - 24, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 3, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 4, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 5, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 6, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 7, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 8, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 9, SCREEN_HEIGHT * CREDITS_THIRD_LINE, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
		}
		else if (endingFrames > CREDITS_FRAMES)	// THANK YOU FOR PLAYING!
		{
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 2, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 3, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 4, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 2, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 5, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 3, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 7, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 8, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 4, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 9, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 11, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 12, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96, 96 * 2, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 13, SCREEN_HEIGHT / 2 - 96, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);

			// PLAYING!
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 7, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 3, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 3, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 4, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 5, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 3, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 6, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 7, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 5, 96, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 8, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 96 * 6, 0, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 9, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
			al_draw_tinted_scaled_rotated_bitmap_region(menuFont, 0, 96 * 5, 96, 96, color_white, 0, 0,
				SCREEN_WIDTH / 2 - 96 * CREDITS_MARGIN + CREDITS_LETTER_SPACING * 10, SCREEN_HEIGHT / 2 - 36, CREDITS_FONT_SIZE, CREDITS_FONT_SIZE, 0, NULL);
		}
		
	}

	//al_draw_textf(font18, color_magenta, 5, 5, NULL, "ENDING FRAMES: %d", endingFrames);
}

// TELAS PARA SAIR DO MENU "GAME OVER", "LOST", "LOSE" DO JOGO
//void QuitEverything();
//void QuitGameplay();

//void GameOverScreen(){}

//void VictoryScreen(){}