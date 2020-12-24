#include <iostream>
#include <fstream>

#include "CGame.h"
#include "Utils.h"
#include "define.h"
#include "CPlayScene.h"
#include "debug.h"
#include "CAnimations.h"
#include "CTextures.h"
#include "CSprites.h"

CGame* CGame::__instance = NULL;
DWORD CGame::DeltaTime = 0;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = NULL;
	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	screen_height = r.bottom + 1;
	screen_width = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	d3ddv->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE); // enable Scissor Test

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::DrawEx(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT r, D3DXVECTOR3 pivot, int scale, D3DXVECTOR2 flip, int alpha)
{
	//float cx, cy;
	//cx = GetCurrentScene()->GetCamera()->position.x;
	//cy = GetCurrentScene()->GetCamera()->position.y;
	//D3DXVECTOR3 p(int(x - cx), int(y - cy), 0); // cam_x, cam_y

	RECT viewport;
	d3ddv->GetScissorRect(&viewport); // toa do viewport

	x += viewport.left; //ve theo toa do viewport
	y += viewport.top;

	D3DXVECTOR3 p(int(x), int(y), 0);

	if ((scale == 1) && (flip.x==1) && (flip.y==1))
		spriteHandler->Draw(texture, &r, &pivot, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	else {

		D3DXMATRIX oldMatrix, newMatrix, mMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		float width = r.right - r.left;
		float height = r.bottom - r.top;
		//&D3DXVECTOR2(scale*flipx*1.0f,scale*1.0f) scale và flip
		//&D3DXVECTOR2(x - cam_x + width / 2, y - cam_y + height / 2) tọa độ giữa sprite 
		//DebugOut(L"Size(%f, %f)\n", width, height);
		D3DXMatrixTransformation2D(&newMatrix,
			//&D3DXVECTOR2(x - cx + width / 2, y - cy + height / 2), 0, &D3DXVECTOR2(scale * flip.x, scale*flip.y), //tan scale | goc xoay (rad) | ti le scale
			&D3DXVECTOR2(x + width / 2, y + height / 2), 0, &D3DXVECTOR2(scale * flip.x, scale*flip.y), //tan scale | goc xoay (rad) | ti le scale
			NULL, NULL,//tam rotate | goc xoay (rad)
			NULL); //tam translation | trans
		mMatrix = oldMatrix * newMatrix;
		spriteHandler->SetTransform(&mMatrix);

		spriteHandler->Draw(texture, &r, &pivot, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

		spriteHandler->SetTransform(&oldMatrix);
	}
}

int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CGame::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CGame::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE*)&keyStates);



	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void CGame::SetViewport(long left, long top, long right, long bottom)
{
	ClipScene();
	RECT rect{ left, top, right, bottom };
	d3ddv->SetScissorRect(&rect);
}// set viewport

void CGame::ClipScene()
{
	spriteHandler->End();
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
}

/*
	Standard sweptAABB implementation
	Source: GameDev.net
*/
void CGame::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny, float& touchingLength)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -999999.0f;
		tx_exit = 999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999.0f;
		ty_exit = 99999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;
	touchingLength = 0;
	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
		// touching length
		float mst = mt + dy * t_entry;
		float msb = mb + dy * t_entry;
		touchingLength = min(msb, sb) - max(mst, st);
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
		//touching lenghth
		float msl = ml + dx * t_entry;
		float msr = mr + dx * t_entry;
		touchingLength = min(msr, sr) - max(msl, sl);
	}

}
//D3DXVECTOR2 CGame::GetCamPos()
//{
//	D3DXVECTOR2 c(cam_x, cam_y);
//	return c;
//}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}



void CGame::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
	{
		current_scene = atoi(tokens[1].c_str());
	}
	else
		DebugOut(L"[error] unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
}

void CGame::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	string path = tokens[1].c_str();
	long time = atoi(tokens[2].c_str());	
	LPSCENE scene = new CPlayScene(id, path,time);
	scenes[id] = scene;
}

void CGame::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return;

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
	/*DebugOut(CTextures::GetInstance()->Get(0) ? L"Have textures \n" : L"Dont have texture" );*/
}

void CGame::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return;

	int ID = atoi(tokens[0].c_str());
	RECT r;
	D3DXVECTOR3 p(0, 0, 0);
	r.left = atoi(tokens[1].c_str()) * 3;
	r.top = atoi(tokens[2].c_str()) * 3;
	r.right = atoi(tokens[3].c_str()) * 3 + r.left; //db là width và height
	r.bottom = atoi(tokens[4].c_str()) * 3 + r.top;
	int texID = atoi(tokens[5].c_str());
	if (tokens.size() > 6)
	{
		p.x = atoi(tokens[6].c_str()) * 3;
		p.y = atoi(tokens[7].c_str()) * 3;
	}

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, r, p,tex);
	//DebugOut(CSprites::GetInstance()->Get(ID) ? L"Have sprite \n" : L"Dont have sprite: %d \n",ID);
}

void CGame::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
	//DebugOut(L"--> %s \n", CAnimations::GetInstance()->Get(ani_id));
}

void CGame::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		DebugOut(ToLPCWSTR("[INFO] Ani ID: " + std::to_string(ani_id) + "\n"));

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}


/*
	Load game campaign file and load/initiate first scene
*/
void CGame::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];
	//LPCWSTR spritePath;
	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;
	LPCWSTR mariofile;
	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
		if (line == "[SPRITES]") { section = GAME_FILE_SECTION_SPRITES; continue; }
		//
		// data section
		//
		switch (section)
		{
		case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
		case GAME_FILE_SECTION_SPRITES: 
			vector<string> tokens = split(line);
			LoadSprite(ToLPCWSTR(tokens[0]));
			break;
		}
	}
	f.close();
	
	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);
	DebugOut(L"[INFO] Current scene : %d \n", current_scene);
	
	LPSCENE s = scenes[current_scene];
	CGame::GetInstance()->SetKeyHandler(s->GetKeyEventHandler());
	s->Load();


	//SwitchScene(current_scene);
	
}
void CGame::LoadSprite(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading sprites from : %s \n",gameFile);

	ifstream f;
	f.open(gameFile);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}
	f.close();
//	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(237, 28, 36)); //RGB BBOX
	DebugOut(L"[INFO] Done loading sprites resources %s\n", gameFile);
}

void CGame::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	scenes[current_scene]->Unload();

	/*CTextures::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();*/

	/*current_scene = scene_id;
	LPSCENE s = scenes[scene_id];
	CGame::GetInstance()->SetKeyHandler(s->GetKeyEventHandler());
	s->Load();*/
}

void CGame::SaveMarioLevel(int level)
{
	mario_level = level;
}

int CGame::GetMarioLevel()
{
	return mario_level;
}
