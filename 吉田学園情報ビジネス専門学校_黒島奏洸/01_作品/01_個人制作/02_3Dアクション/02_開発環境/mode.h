//============================================================================
//
// Mode.h
// Author : çïìáÅ@ëtü©
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_
#include"main.h"
#include"object.h"
class CRendere;
class CInput;
class CCamera;
class CObject2D; 
class CMode	: public CObject
{
public:
	CMode();
	virtual~CMode();
	virtual HRESULT Init(void) { return S_OK; };
	virtual void Uninit(void) {};
	virtual void Update(void) = 0;

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