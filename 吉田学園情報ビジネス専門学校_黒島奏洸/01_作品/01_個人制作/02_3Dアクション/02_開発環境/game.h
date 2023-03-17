//============================================================================
//
// Game.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include"mode.h"
#include"score.h"
#define MAX_MODELFLOOR	(255)		//���f����
#define MAX_GIMMICK		(6)			//�M�~�b�N��
#define MAX_ENEMY		(6)			//�G�̐�
#define MAX_COIN		(16)			//�R�C����

class CMode;
class CModel;
class CMeshfield;
class CPlayer;
class CStrongbox;
class CWeapon;
class CEnemy;
class CGimmick;
class CCoin;
class CGoal;
class CGame : public CMode
{
public:
	CGame();
	~CGame()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;

	static CGame *Create(void);
	static CScore *GetScore(void) { return m_nScor; };
	static CMeshfield* GetMeshfield(void) { return m_pMeshfield; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; };
	static CEnemy **GetEnemy() { return m_pEnemy; };
	static CStrongbox *GetSBox(void) { return m_pSbox; };
	static CWeapon *GetWeapon(void) { return m_pWeapon; };
	static CCoin *GetCoin(int nCnt) { return m_pCoin[nCnt]; };
	static CCoin **GetCoin(void) { return m_pCoin; }
	static CGoal *GetGoal(void) {return m_pGoal;}
	static CModel **GetModel(void) { return m_pModel; }
	static CGimmick **GetGimmick(void) { return m_pGimmick; };
private:
	static LPDIRECT3DTEXTURE9 m_ptex;
	float m_fWidth;
	float m_fHeight;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static CScore *m_nScor;
	static CMeshfield *m_pMeshfield;	//���b�V���t�B�[���h�̃C���X�^���X
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy[MAX_ENEMY];
	static CStrongbox *m_pSbox;
	static CWeapon *m_pWeapon;
	static CCoin *m_pCoin[MAX_COIN];
	static CModel *m_pModel[MAX_MODELFLOOR];
	static CGimmick *m_pGimmick[MAX_GIMMICK];
	static CGoal *m_pGoal;
	bool bSound;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};
#endif


