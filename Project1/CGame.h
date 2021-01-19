#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <unordered_map>

#include "CKeyEventHandler.h"

#include <dinput.h>
#include "CScene.h"
#include "Mario.h"
#include "define.h"

using namespace std;

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
	

	int screen_width;
	int screen_height;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	D3DXVECTOR2 world_pos= D3DXVECTOR2(0,0);
	CMario* mario;
	int life = 4;
	int stageclear=0;
	//int mario_level=MARIO_LEVEL_SMALL;
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line); 
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);


public:
	void InitKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void DrawEx(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT r, D3DXVECTOR3 pivot, int scale, D3DXVECTOR2 flip, int alpha = 255);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void Load(LPCWSTR gameFile);
	void LoadSprite(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	int GetCurrentSceneID() { return current_scene; }
	void SwitchScene(int scene_id);

	/*void SaveMarioLevel(int level);
	int GetMarioLevel();*/
	void SaveMarioState(CMario* player);
	CMario* GetMario();
	void SaveMarioWorldPos(D3DXVECTOR2 pos);
	void StateClear();
	void SetMarioLife(int a);
	D3DXVECTOR2 GetMarioWorldPos();
	int GetMarioLife();
	int GetStageClear();

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

	void SetViewport(long left, long top, long right, long bottom);
	void ClipScene();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny,
		float &touchingLength);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	//void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	//void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
	//D3DXVECTOR2 GetCamPos();
	static CGame* GetInstance();
	static DWORD DeltaTime;
	~CGame();
};