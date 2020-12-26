#pragma once


#define WINDOW_CLASS_NAME L"MARIO BROS. 3"
#define MAIN_WINDOW_TITLE L"MARIO BROS. 3"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(156, 252, 240)
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 760

#define GAME_WIDTH 768
#define GAME_HEIGHT	576

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
//SCENE
#define PLAY_SCENE	1
#define WORLD_MAP	0
//TEXTURE
#define ID_TEX_BBOX -100
#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_EFFECT 40
#define ID_TEX_GOAL_EFFECT 50
#define DEFAULT_FRAME_TIME 100

//SCENE
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_GROUND	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_GHOST	3
#define OBJECT_TYPE_KOOPA	4
#define OBJECT_TYPE_COIN	6
#define OBJECT_TYPE_QUESTION_BOX	7
#define OBJECT_TYPE_BRICK	8
#define OBJECT_TYPE_PIRANHA	9
#define OBJECT_TYPE_END_GAME_REWARD	10
#define OBJECT_TYPE_VENUS	11
#define OBJECT_TYPE_SUPER_MUSHROOM	12
#define OBJECT_TYPE_SUPER_LEAF	13
#define OBJECT_TYPE_SWITCH_BUTTON	14
#define OBJECT_TYPE_FIREBALL	20
#define OBJECT_TYPE_TAIL	21
#define OBJECT_TYPE_VENUS_FIREBALL	22
#define OBJECT_TYPE_WORLD_MARIO	23
#define OBJECT_TYPE_TELEPORT	24


#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_EFFECT 51

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
#define MARIO_FLY_FORCE			0.2f

#define MARIO_WALKING_SPEED		0.22f 
#define MARIO_RUNNING_SPEED	0.45f

#define MARIO_POWER_METER_MAX	7
#define MARIO_POWER_METER_UP	0.008f
#define MARIO_POWER_METER_DOWN	0.0016f

#define MARIO_JUMP_SPEED_Y		0.8f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.00193f
#define	MARIO_FLOAT	0.00013f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define PI	 3.14159265359

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
#define MARIO_UNTOUCHABLE_TIME 3500
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
#define MARIO_ANI_SMALL_HOLD_IDLE	112
#define MARIO_ANI_SMALL_HOLD_FALL	104
#define MARIO_ANI_SMALL_HOLD	113

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
#define MARIO_ANI_BIG_HOLD_IDLE		134
#define MARIO_ANI_BIG_HOLD	135
#define MARIO_ANI_BIG_HOLD_FALL	136
#define MARIO_ANI_BIG_KICK		137

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
#define MARIO_ANI_RACOON_HOLD_IDLE		174
#define MARIO_ANI_RACOON_HOLD	175
#define MARIO_ANI_RACOON_HOLD_FALL	176


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
#define MARIO_ANI_FIRE_HOLD_IDLE		210
#define MARIO_ANI_FIRE_HOLD	211
#define MARIO_ANI_FIRE_HOLD_FALL	212


//MARIO FIRE BALL
#define FIREBALL_GRAVITY 0.00193f
#define FIREBALL_JUMP_FORCE 0.4f
#define FIREBALL_SPEED 0.48f
#define MARIO_FIRE_BALL_BBOX_WIDTH 24
#define MARIO_FIRE_BALL_BBOX_HEIGHT 24


#define MARIO_ANI_FIRE_BALL	500

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
#define KOOPA_STATE_FLYING 104


//GOOMBA
#define GOOMBA 1
#define RED_GOOMBA 2
#define GOOMBA_WALKING_SPEED 0.1f;

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 27

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_FLYING 101
#define GOOMBA_STATE_DIE 102
#define GOOMBA_STATE_WEAPON_DIE 103

#define GOOMBA_ANI_WALKING 1000
#define GOOMBA_ANI_DIE 1001


// QUESTION BOX
#define QUESTION_BOX_REWARD 1
#define QUESTION_BOX_BOUNC 2
#define QUESTION_BOX_EMPTY 3


//BRICK
#define BRICK_REWARD 1
#define BRICK_BOUNC 12
#define BRICK_EMPTY 13

#define BRICK_BREAKABLE 2
#define BRICK_BROKEN 21
#define BRICK_COIN 22

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

//PIRANHA
#define GREEN_PIRANHA_ANI	1017
#define RED_PIRANHA_ANI	1018

#define GREEN_TYPE	1
#define RED_TYPE	2
//VENUS

//COIN
#define COIN_ANI 602

//SUPER LEAF
#define SUPER_LEAF_BBOX_WIDTH	48
#define SUPER_LEAF_BBOX_HEIGHT	42
#define SUPER_LEAF_ANI	612

#define SUPER_LEAF_VELOCITY_X 0.2f
#define SUPER_LEAF_GRAVITY 0.001395f

#define SUPER_LEAF_STATE_UP	1
#define SUPER_LEAF_STATE_LEFT	2
#define SUPER_LEAF_STATE_RIGHT	3

// UI
#define POINT_100_ANI	1500
#define POINT_200_ANI	1501
#define POINT_400_ANI	1502
#define POINT_800_ANI	1503
#define POINT_1000_ANI	1504
#define POINT_2000_ANI	1505
#define POINT_4000_ANI	1506
#define POINT_8000_ANI	1507
#define POINT_1UP_ANI	1508

