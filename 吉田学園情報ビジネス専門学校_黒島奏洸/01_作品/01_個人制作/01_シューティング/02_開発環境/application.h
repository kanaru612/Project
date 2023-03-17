//=============================================================================
//
// application.h
// Author : 
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include"main.h"
#include"object2D.h"
class CRendere;
class CInput;
class CPlayer;
class CBullet;
class CTitle;
class CResult;
class CGame;
class CScore;
class CMode;
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TUTRIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	};
	CApplication();
	~CApplication();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRendere *GetRendere(void){ return m_pRendere; };
	static CInput *GetKeyboard() { return m_pKey; };
	static MODE GetMode() { return m_mode; };
	static void SetMode(MODE mode);
private:
	static CRendere *m_pRendere;
	static CInput *m_pKey;
	static MODE m_mode;
	static CMode *m_pMode;
};
class CObject;
class CMode	: public CObject
{
public:
	CMode();
	virtual~CMode();
	virtual HRESULT Init(void) { return S_OK; };
	virtual void Uninit(void) {};
	virtual void Update(void)  = 0;

	void Draw(void) override {};
	void setpos(const D3DXVECTOR3 pos) override { pos; };
	void setlife(int life) override {  };
	D3DXVECTOR3 Getpos(void)override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_pos; };
	int Gettype(void) override { return 0; };
	int Getlife(void) override { return 0; };
	D3DXVECTOR3 Getrot(void) override { return m_pos; };
private:
	D3DXVECTOR3 m_pos;
};

#endif
