//=============================================================================
//
//  Enemy.h
//  Author : 黒島　奏洸
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include"main.h"
#include"object2D.h"
#include"modelparts.h"
#include"player.h"
#define MAX_SIZEH			(300)
#define MAX_SIZEW			(150)
#define MAX_PARTS_E			(4)
#define MOTION_NUMBER_E		(2)	
class CScore;
class CMotionset;
class CEnemy : public CObject
{
public:
	explicit CEnemy(int nPriority = 2);
	~CEnemy()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CEnemy *Create(const D3DXVECTOR3 pos, int nLife);
	void setpos(const D3DXVECTOR3 pos) override { m_pos = pos; };
	void setlife(int life) override { m_nLife = life; };
	void Load();
	D3DXVECTOR3 Getpos(void) override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_size; };
	int Gettype(void) override { return m_nType; };
	int Getlife(void) override { return m_nLife; };
	D3DXVECTOR3 Getrot(void) override { return m_rot; };
	void Motionanimation(void);
	void SetMotionType(CPlayer::MOTIONTYPE type);		//モーションの種類の設定処理
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
	void Move();
private:
	D3DXVECTOR3 m_move;						//敵の移動速度
	D3DXVECTOR3 m_rot;						//敵の角度
	D3DXVECTOR3 m_rotDest;						//敵の角度
	D3DXVECTOR3 m_pos;						//敵の位置
	D3DXVECTOR3 m_size;						//敵のサイズ
	D3DXVECTOR3  m_vtxMin;					//最小値
	D3DXVECTOR3  m_vtxMax;					//最大値
	int m_nFrame;	
	static LPDIRECT3DTEXTURE9 m_ptex;		
	CScore *m_pScore;						
	int m_nCnt;								//敵のカウント
	int m_nLife;							//敵の体力
	int m_nType;							//敵の種類
	int m_PresentKeyset;					//現在のキーセット
	bool m_bUse;
	LPD3DXBUFFER m_pBuffMat;				
	DWORD        m_nNumMat;					
	LPD3DXMESH   m_pMesh;					
	CPlayer *m_pPlayer;						
	D3DXMATRIX   m_mtxWorld;				
	CModelparts *m_pModele[MAX_PARTS_E];
	int m_nCountModel;
	CMotionset *m_Motionset[MOTION_NUMBER_E];
	CPlayer::MOTIONTYPE m_Motiontype;		//モーションの種類
	D3DXVECTOR3 m_nFrameSpeed[MAX_PARTS_E];	//フレームの速さ
	D3DXVECTOR3 m_RotSpeed[MAX_PARTS_E];	//回転の速さ
	bool m_bAttack;
};
#endif

