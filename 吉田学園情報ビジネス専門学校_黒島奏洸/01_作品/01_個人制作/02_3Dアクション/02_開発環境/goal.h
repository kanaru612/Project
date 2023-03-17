//============================================================================
//
// Goal.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_
#include"model.h"
class CGoal : public CModel
{
public:
	explicit CGoal(int nPriority = 2);
	~CGoal()override;
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static CGoal *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void SetGoal(char * pFile);
	void setrot(const D3DXVECTOR3 rot) { m_rot = rot; };
	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size)override;
	bool OnCollision()override { return false; };
	void SetOnCollision(bool bOn) override { m_bOn = bOn; };

private:
	D3DXVECTOR3 m_rot;						//�S�[���̊p�x
	D3DXVECTOR3 m_pos;						//�S�[���̈ʒu
	D3DXVECTOR3 m_size;						//�S�[���̃T�C�Y
	D3DXVECTOR3  m_vtxMin;					//�S�[���̍ŏ��l
	D3DXVECTOR3  m_vtxMax;					//�S�[���̍ő�l
	static LPDIRECT3DTEXTURE9 m_ptex;		
	int m_nLife;							
	int m_nType;							
	bool bUse;								
	bool m_bOn;
	LPD3DXBUFFER m_pBuffMat;				
	DWORD        m_nNumMat;					
	LPD3DXMESH   m_pMesh;					
	D3DXMATRIX   m_mtxWorld;			


	bool m_GoalFlag;
	bool m_FadeFlag;
};

#endif

