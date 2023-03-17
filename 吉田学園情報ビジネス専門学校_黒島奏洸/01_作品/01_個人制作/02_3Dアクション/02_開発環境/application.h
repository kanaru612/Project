//============================================================================
//
// Application.h
// Author : çïìáÅ@ëtü©
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include"main.h"
class CRendere;
class CInput;
class CCamera;
class CObject2D;
class CMode;
class CCamera;
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
	static CCamera *Getcamera() { return m_pCamera; };

private:
	static CRendere *m_pRendere;
	static CInput *m_pKey;
	static MODE m_mode;
	static CMode *m_pMode;
	CObject2D * m_pObject2D[4];
	static CCamera *m_pCamera;
};
#endif
