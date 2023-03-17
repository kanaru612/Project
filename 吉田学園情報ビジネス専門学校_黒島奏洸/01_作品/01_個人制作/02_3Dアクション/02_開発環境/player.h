//============================================================================
//
// Player.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"main.h"
#include"object.h"
#include"keyset.h"
#define MAX_SIZEP			(75)
#define MAX_PARTS			(4)
#define MAX_WORD			(1024)
#define MAX_MOVE			(5.0f)		
#define MOTION_NUMBER		(3)			

class CModelparts;
class CCamera;
class CMotionset;
class CKeyset;
class CKey;

class CPlayer : public CObject
{
public:
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRALMOTION = 0,			//ニュートラルモーション
		MOTIONTYPE_MOVE,						//移動モーション
		MOTIONTYPE_ATTACK,						//攻撃モーション
		MOTIONTYPE_NONE,
		MOTIONTYPE_MAX
	};

	explicit CPlayer(int nPriority = 2);
	~CPlayer()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Load();
	void Move();
	void setpos(const D3DXVECTOR3 pos) override { m_pos = pos; };
	void setlife(int life) override { m_nLife = life; };
	void setsize(D3DXVECTOR3 size) { m_size = size; };
	void setrot(D3DXVECTOR3 rot) { m_rot = rot; };
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
	void attack();
	void Attack();
	D3DXVECTOR3 Getpos(void) override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_size; };
	int Gettype(void) override { return m_nType; };
	int Getlife(void) override { return m_nLife; };
	D3DXVECTOR3 Getrot(void) override { return m_rot; };
	static CPlayer *Create(D3DXVECTOR3 pos,int nLife);
	void Motionanimation(void);		
	void SetMotionType(MOTIONTYPE type);		//モーションの種類の設定処理
	void SetHitegg(bool bHit) { m_bhitegg = bHit; };
	bool GetHitegg() { return m_bhitegg; };
private:

	float m_rotspeed;
	static int m_nLife;
	int m_nCntAnim;
	int m_nPattern;
	bool m_bJump;
	int m_nCnt;
	int m_nCntD;
	int m_nCountModel;	
	float m_fDistance;
	int m_nFrame;
	bool m_bRoll;
	static bool m_bUseWeapon;
	int m_PresentKeyset;					//現在のキーセット
	bool m_bAttack;
	bool m_bWalk;
	bool m_bhitegg;
	int m_nLifeE;
	int m_nLifeG;
	D3DXVECTOR3 m_move;				
	D3DXVECTOR3  m_pos;						//位置
	D3DXVECTOR3  m_posOld;					//前の位置
	D3DXVECTOR3  m_rot;						//向き
	D3DXVECTOR3  m_rotDest;					
	D3DXVECTOR3  m_Rrot;					//向き
	D3DXVECTOR3  m_RrotDest;				
	D3DXVECTOR3  m_size;
	D3DXVECTOR3  m_vtxMin;					//最小値
	D3DXVECTOR3  m_vtxMax;					//最大値
	D3DXMATRIX   m_mtxWorld;				//ワールドマトリックス
	LPD3DXMESH   m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	ObjeType m_nType;
	CModelparts *m_pModelp[MAX_PARTS];
	CCamera *m_pCamera;
	CMotionset *m_Motionset[MOTION_NUMBER];	
	MOTIONTYPE m_Motiontype;				//モーションの種類
	D3DXVECTOR3 m_nFrameSpeed[MAX_PARTS];	//フレームの速さ
	D3DXVECTOR3 m_RotSpeed[MAX_PARTS];		//回転の速さ
	bool m_bDie;
	bool m_AttackSEFlag;
};
#endif

