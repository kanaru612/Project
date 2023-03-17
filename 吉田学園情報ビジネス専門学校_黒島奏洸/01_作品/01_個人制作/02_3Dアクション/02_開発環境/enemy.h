//=============================================================================
//
//  Enemy.h
//  Author : �����@�t��
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
	void SetMotionType(CPlayer::MOTIONTYPE type);		//���[�V�����̎�ނ̐ݒ菈��
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
	void Move();
private:
	D3DXVECTOR3 m_move;						//�G�̈ړ����x
	D3DXVECTOR3 m_rot;						//�G�̊p�x
	D3DXVECTOR3 m_rotDest;						//�G�̊p�x
	D3DXVECTOR3 m_pos;						//�G�̈ʒu
	D3DXVECTOR3 m_size;						//�G�̃T�C�Y
	D3DXVECTOR3  m_vtxMin;					//�ŏ��l
	D3DXVECTOR3  m_vtxMax;					//�ő�l
	int m_nFrame;	
	static LPDIRECT3DTEXTURE9 m_ptex;		
	CScore *m_pScore;						
	int m_nCnt;								//�G�̃J�E���g
	int m_nLife;							//�G�̗̑�
	int m_nType;							//�G�̎��
	int m_PresentKeyset;					//���݂̃L�[�Z�b�g
	bool m_bUse;
	LPD3DXBUFFER m_pBuffMat;				
	DWORD        m_nNumMat;					
	LPD3DXMESH   m_pMesh;					
	CPlayer *m_pPlayer;						
	D3DXMATRIX   m_mtxWorld;				
	CModelparts *m_pModele[MAX_PARTS_E];
	int m_nCountModel;
	CMotionset *m_Motionset[MOTION_NUMBER_E];
	CPlayer::MOTIONTYPE m_Motiontype;		//���[�V�����̎��
	D3DXVECTOR3 m_nFrameSpeed[MAX_PARTS_E];	//�t���[���̑���
	D3DXVECTOR3 m_RotSpeed[MAX_PARTS_E];	//��]�̑���
	bool m_bAttack;
};
#endif

