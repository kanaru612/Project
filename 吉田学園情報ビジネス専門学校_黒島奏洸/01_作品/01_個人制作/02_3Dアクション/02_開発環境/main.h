//=============================================================================
//
// Main.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
//*****************************************************************************
// ライブラリーリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")	
//*****************************************************************************
// インクルード
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#include <assert.h>
#define DIRECTINPUT_VERSION	(0x0800)//ビルド時警告対処用マクロ
#include <dinput.h>
#include <time.h>
#include "xaudio2.h"			//サウンド処理に必要
//*****************************************************************************
// 定数定義
//*****************************************************************************
// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int Getfps(void);
//マクロ
#define MAX_OBJECT	(1024)
#endif