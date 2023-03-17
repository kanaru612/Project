//=============================================================================
//
// rendere.h
// Author : 
//
//=============================================================================
#ifndef _RENDERE_H_
#define _RENDERE_H_
#include"main.h"
class CRendere 
{
public:
	CRendere();
	~CRendere();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}
private:
	// Direct3Dオブジェクト
	LPDIRECT3D9 m_pD3D;
	// Deviceオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXFONT m_pFont;
#ifdef _DEBUG
	void DrawFPS();
#endif // _DEBUG
};
#endif