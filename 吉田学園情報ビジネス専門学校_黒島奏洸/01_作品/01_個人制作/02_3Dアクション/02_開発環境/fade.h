//============================================================================
//
// Fade.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include"main.h"
#include"object2D.h"
#include"application.h"
//フェードアウト
class CFade : public CObject2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,							//何もしてない状態
		FADE_IN,								//フェードイン状態
		FADE_OUT,								//フェードアウト状態
		FADE_MAX
	}FADE;

	CFade();
	~CFade()override;

	HRESULT Init(CApplication::MODE modeNext);
	void Uninit(void) override;
	void Update(void) override;

	static void Set(CApplication::MODE modeNext);
	FADE Get() { return m_fade;};
	static CFade *Create(CApplication::MODE modeNext);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//頂点バッファへのポインタ
	static FADE m_fade;										//フェードの情報
	static CApplication::MODE m_modeNext;					//次の画面(モード)
	static D3DXCOLOR m_color;								//ポリゴン(フェード)の色
};
#endif

