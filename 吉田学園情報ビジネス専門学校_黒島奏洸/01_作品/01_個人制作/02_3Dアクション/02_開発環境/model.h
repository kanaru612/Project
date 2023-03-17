//============================================================================
//
// Model.h
// Author : �����@�t��
//
//=============================================================================
#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include"object.h"
class CModel : public CObject
{
public:
	explicit CModel(int nPriority = 2);
	~CModel()override;
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	void setpos(const D3DXVECTOR3 pos) override { m_pos = pos; };
	void setlife(int life) override { m_nLife = life; };

	D3DXVECTOR3 Getpos(void) override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_size; };
	int Gettype(void) override { return m_nType; };
	int Getlife(void) override { return m_nLife; };
	D3DXVECTOR3 Getrot(void) override { return m_rot; };
	D3DXVECTOR3 GetvtxMax(void) { return m_vtxMax; };
	D3DXVECTOR3 GetvtxMin(void) { return m_vtxMin; }
	void Vtx(void);
	void SetModel(char * pFile);
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	virtual void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 size);
	virtual bool OnCollision() { return m_bOn; };
	virtual void SetOnCollision(bool bOn) { m_bOn = bOn; };
private:
	D3DXVECTOR3 m_rot;								//����
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_size;								//�T�C�Y
	D3DXVECTOR3 m_vtxMax;							//�ő�l
	D3DXVECTOR3 m_vtxMin;							//�ŏ��l
	D3DXMATRIX *m_mtxParent;						//�e�̃��[���h�}�g���b�N�X	
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X	
	int m_nLife;									//�̗�
	int m_nType;									//���
	bool m_bOn;
	LPD3DXBUFFER m_pBuffMat;
	DWORD        m_nNumMat;
	LPD3DXMESH   m_pMesh;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};

#endif

