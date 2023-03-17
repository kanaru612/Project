//=============================================================================
//
// Input.h
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include"main.h"
//マクロ定義
#define NUM_KEY_MAX	(256)						//キーの最大数

class CInput
{
public:
	CInput();
	~CInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void) ;
	bool GetPress(int nKey);
	bool GetTrriger(int nKey);
private:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
	BYTE m_aKeyStateP[NUM_KEY_MAX];
	BYTE m_aKeyStateT[NUM_KEY_MAX];
};


#endif