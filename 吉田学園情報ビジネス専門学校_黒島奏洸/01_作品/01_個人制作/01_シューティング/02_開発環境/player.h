//=============================================================================
//
// object.h
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"main.h"
#include"object2D.h"
#define MAX_SIZEP	(75)
class CBullet;
class CTail;
class CPlayer : public CObject2D
{
public:
	enum State
	{
		STATE_NONE = 0,
		WALK,
		JAMP,
	};
	enum DamageState
	{
		DAMAGE_NONE = 0,
		NORMAL,
		DAMAGE,
	};
	CPlayer();
	~CPlayer()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CPlayer *Create(int nLife);
	static HRESULT Load(void);
	State Getstate(void) { return m_nstate; };
	DamageState Getstategamage(void) { return m_Damage; };
	static void setStatedamage(DamageState damage);
	static void Unload(void);
	void setlife(int life)override;
	static int Getlife(void)  { return m_nLife; };
private:
	D3DXVECTOR3 m_move;
	static int m_nLife;
	static DamageState m_Damage;
	ObjeType m_nType;
	static LPDIRECT3DTEXTURE9 m_ptex;
	int m_nCntAnim;
	int m_nPattern;
	State m_nstate;
	bool m_bJump;
	CTail *m_pTail;
	int m_nCnt;
	int m_nCntD;
};
#endif

