#pragma once


#define WINDOW_CLASS_NAME L"MARIO BROS. 3"
#define MAIN_WINDOW_TITLE L"MARIO BROS. 3"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 760
#define SCREEN_HEIGHT 720

#define MAX_FRAME_RATE 120

#define WORLD_MAP_1_1 101
// CAMERA
#define CAMERA_Y_POSITION 720
//CGAME
#define MAX_GAME_LINE 1024


#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2
#define GAME_FILE_SECTION_SPRITES 3

//TEXTURE
#define ID_TEX_BBOX -100
#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_EFFECT 40
#define DEFAULT_FRAME_TIME 100

//SCENE
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_GHOST	3
#define OBJECT_TYPE_KOOPA	4
#define OBJECT_TYPE_FIREBALL	20
#define OBJECT_TYPE_TAIL	21



#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

//CGAME
#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

//MARIO PHYSIC
#define MARIO_WALKING_ACCELERATION	0.000376f
#define MARIO_RUNNING_ACCELERATION	0.000288f
#define MARIO_SKID_ACCELERATION 0.001104f

#define MARIO_WALK_DRAG_FORCE	0.0002906f
#define MARIO_RUN_DRAG_FORCE	0.0006266f
#define MARIO_PUSH_FORCE 0.0022f
#define MARIO_JUMP_FORCE 0.6f
#define MARIO_HIGH_JUMP_FORCE 0.68f
#define MARIO_SUPER_JUMP_FORCE  0.68f
#define MARIO_FLY_FORCE			0.2f

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_RUNNING_SPEED	0.4f

#define MARIO_POWER_METER_MAX	7
#define MARIO_POWER_METER_UP	0.008f
#define MARIO_POWER_METER_DOWN	0.0016f

#define MARIO_JUMP_SPEED_Y		0.8f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.00193f
#define	MARIO_FLOAT	0.00013f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

//MARIO STATE
#define MARIO_STATE_WALKING 1
#define MARIO_STATE_RUNNING 2
#define MARIO_STATE_CROUCH	3

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_SKID	202

#define MARIO_STATE_JUMP_IDLE			300
#define MARIO_STATE_JUMP			301
#define MARIO_STATE_HIGH_JUMP	302
#define MARIO_STATE_SUPER_JUMP	303
#define MARIO_STATE_FALL	304
#define MARIO_STATE_SUPER_FALL	305
#define MARIO_STATE_FLOAT	306
#define MARIO_STATE_FLY	307

#define MARIO_STATE_ATTACK_START 400
#define MARIO_STATE_ATTACKING	401
#define MARIO_STATE_ATTACK_END 402
#define MARIO_ATTACK_TIME 250

#define MARIO_STATE_DIE				999
#define MARIO_STATE_KICK	500
//MARIO LEVEL
#define MARIO_UNTOUCHABLE_TIME 5000
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON		3
#define	MARIO_LEVEL_FIRE		4

//MARIO ANI
#define MARIO_ANI_DIE				999
#define MARIO_CROUCH_BBOX_HEIGHT 54
//SMALL MARIO
#define MARIO_SMALL_BBOX_WIDTH  38
#define MARIO_SMALL_BBOX_HEIGHT 45

#define MARIO_ANI_SMALL_IDLE	102
#define MARIO_ANI_SMALL_WALKING		103
#define MARIO_ANI_SMALL_RUNNING		106
#define MARIO_ANI_SMALL_JUMP		108
#define MARIO_ANI_SMALL_SUPER_JUMP		109
#define MARIO_ANI_SMALL_SKID	105

// BIG MARIO
#define MARIO_BIG_BBOX_WIDTH  45
#define MARIO_BIG_BBOX_HEIGHT 81

#define MARIO_ANI_BIG_IDLE		121
#define MARIO_ANI_BIG_WALKING		123
#define MARIO_ANI_BIG_RUNNING		127
#define MARIO_ANI_BIG_FALL		125
#define MARIO_ANI_BIG_JUMP		130
#define MARIO_ANI_BIG_SUPER_JUMP		131
#define MARIO_ANI_BIG_CROUCH	132
#define MARIO_ANI_BIG_SKID		126

//RACOON MARIO
#define MARIO_RACOON_BBOX_WIDTH  45
#define MARIO_RACOON_BBOX_HEIGHT 81

#define MARIO_ANI_RACOON_WALKING	155
#define MARIO_ANI_RACOON_IDLE	154
#define MARIO_ANI_RACOON_FLOAT	159
#define MARIO_ANI_RACOON_RUNNING		163
#define MARIO_ANI_RACOON_JUMP		162
#define MARIO_ANI_RACOON_FALL		157
#define MARIO_ANI_RACOON_SKID		158
#define MARIO_ANI_RACOON_SUPER_JUMP		168
#define MARIO_ANI_RACOON_SUPER_FALL		167
#define MARIO_ANI_RACOON_FLY	166
#define MARIO_ANI_RACOON_SPIN	169
#define MARIO_ANI_RACOON_CROUCH	172

//FIRE MARIO
#define MARIO_FIRE_BBOX_WIDTH 45
#define MARIO_FIRE_BBOX_HEIGHT 81

#define MARIO_ANI_FIRE_IDLE	196
#define MARIO_ANI_FIRE_WALKING	197
#define MARIO_ANI_FIRE_RUNNING		203
#define MARIO_ANI_FIRE_JUMP		206
#define MARIO_ANI_FIRE_SKID		200
#define MARIO_ANI_FIRE_THROW	201
#define MARIO_ANI_FIRE_FALL		199
#define MARIO_ANI_FIRE_SUPER_JUMP		207
#define MARIO_ANI_FIRE_CROUCH	208

//HAMMER MARIO
#define MARIO_HAMMER_BBOX_WIDTH 45
#define MARIO_HAMMER_BBOX_HEIGHT 81

#define MARIO_ANI_HAMMER_IDLE	225
#define MARIO_ANI_HAMMER_WALKING	226
#define MARIO_ANI_HAMMER_RUNNING		232
#define MARIO_ANI_HAMMER_JUMP		235
#define MARIO_ANI_HAMMER_SKID		229
#define MARIO_ANI_HAMMER_FALL		228
#define MARIO_ANI_HAMMER_CROUCH	237

//MARIO FIRE BALL
#define FIREBALL_GRAVITY 0.00193f
#define FIREBALL_JUMP_FORCE 0.4f
#define FIREBALL_SPEED 0.48f
#define MARIO_FIRE_BALL_BBOX_WIDTH 24
#define MARIO_FIRE_BALL_BBOX_HEIGHT 24

#define MARIO_FIRE_BALL_STATE 0
#define MARIO_FIRE_BALL_STATE_DAMAGED 1

#define MARIO_ANI_FIRE_BALL	500
#define MARIO_ANI_FIRE_BALL_DAMAGED	501

//MARIO TAIL
#define MARIO_TAIL_BBOX_WIDTH 9
#define MARIO_TAIL_BBOX_HEIGHT 9

//KOOPA
#define KOOPA_WALKING_SPEED 0.07f;
#define SHELL_SPEED 0.5f;

#define KOOPA_BBOX_WIDTH 48
#define KOOPA_BBOX_HEIGHT 48

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_CROUCH 101
#define KOOPA_STATE_SHELL_RUNNING 102
#define KOOPA_STATE_DIE 103

#define KOOPA_ANI_WALKING 1002
#define KOOPA_ANI_CROUCH 1005
#define KOOPA_SHELL_ANI_RUN 1003
#define KOOPA_ANI_RESPAWN 1004


//GOOMBA
#define GOOMBA_WALKING_SPEED 0.1f;

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 27

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 101
#define GOOMBA_STATE_WEAPON_DIE 102

#define GOOMBA_ANI_WALKING 1000
#define GOOMBA_ANI_DIE 1001


