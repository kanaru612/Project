//=============================================================================
//
// Gimmick.cpp
// Author : �����@�t��
//
//=============================================================================
#include <assert.h>
#include <stdio.h>
#include "gimmick.h"
#include "application.h"
#include "rendere.h"
#include"Input.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
#include"goal.h"
CGimmick::CGimmick(int nPriority) : CModel(nPriority)
{

	m_pos = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_bOn = false;
}

CGimmick::~CGimmick()
{

}
//-------------------------------------------------------------------------
// �M�~�b�N�̏�����
//-------------------------------------------------------------------------
HRESULT CGimmick::Init(void)
{
	CModel::Init();
	CModel::SetModel("data/model/egg.x");
	CModel::Vtx();
	return S_OK;
}
//-------------------------------------------------------------------------
// �M�~�b�N�̏I��
//-------------------------------------------------------------------------
void CGimmick::Uninit()
{
	CModel::Uninit();
}
//-------------------------------------------------------------------------
// �M�~�b�N�̍X�V
//-------------------------------------------------------------------------
void CGimmick::Update()
{
	m_pos = Getpos();
}
//-------------------------------------------------------------------------
// �M�~�b�N�̕`��
//-------------------------------------------------------------------------
void CGimmick::Draw()
{
	CModel::Draw();
}
//-------------------------------------------------------------------------
// �M�~�b�N�̐���
//-------------------------------------------------------------------------
CGimmick * CGimmick::Create(const D3DXVECTOR3 pos)
{
	CGimmick *pGimmick = nullptr;
	pGimmick = new CGimmick;
	if (pGimmick != nullptr)
	{
		pGimmick->Init();
		pGimmick->setpos(pos);
		pGimmick->SetType(OBJTYPE_ENEMY);
		pGimmick->m_bUse = true;
	}
	return pGimmick;
}
//-------------------------------------------------------------------------
// �M�~�b�N�̐ݒ�
//-------------------------------------------------------------------------
void CGimmick::SetGimmick(char * pFile)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);
	int nNumvtx;						//���_��				
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuf;						//���_�o�b�t�@�ւ̃|�C���^
										//���_���̎擾
	nNumvtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuf);

	for (int nCntvtx = 0; nCntvtx < nNumvtx; nCntvtx++)
	{
		//���_���W����
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuf;

		//���_���W���r���ă��f���̍ŏ��l�A�ő�l���擾(if��)
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuf += sizeFVF;
	}
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();
}
//-------------------------------------------------------------------------
//�v���C���[�ƃM�~�b�N�̓����蔻��
//-------------------------------------------------------------------------
void CGimmick::Collision(D3DXVECTOR3 *pPos,				//���݂̈ʒu
	D3DXVECTOR3 *pPosOld,								//�O��̈ʒu
	D3DXVECTOR3 size)									//�T�C�Y
{
	CInput *pInput = CApplication::GetKeyboard();
	CPlayer *pPlayer = CGame::GetPlayer();

	m_vtxMax = CModel::GetvtxMax();
	m_vtxMin = CModel::GetvtxMin();

	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;

	if (   pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
		&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x
		&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
		&& pPos->y - size.y / 2 < m_pos.y + m_vtxMax.y
		)
	{
		//���̓����蔻��
		if (
			pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
			&& pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f

			)
		{
			pPos->z = m_pos.z + m_vtxMax.z + size.z / 2.0f;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
			}
			m_bOn = false;
		}
		//��O�̓����蔻�� 
		if (
			pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
			&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f


			)
		{
			pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
				
			}
			m_bOn = false;
		}
	}
	if (pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z
		&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
		&& pPos->y - size.y / 2 < m_pos.y + m_vtxMax.y
		)
	{

		//���̓����蔻��
		if (
			pPosOld->x <= m_pos.x + m_vtxMin.x - size.x / 2
			&& pPos->x > m_pos.x + m_vtxMin.x - size.x / 2

			)
		{
			pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
			}
			m_bOn = false;
		}
		//�E�̓����蔻��
		if (
			pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
			&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2

			)
		{
			pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
			if (pInput->GetTrriger(DIK_RETURN) == true)
			{
				pPlayer->SetHitegg(true);
			}
			m_bOn = false;
		}
	}

	if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
		&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x
		&& pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z
		)

	{
		//��̓����蔻��
		if (pPosOld->y + m_size.y / 2 >= m_pos.y + m_vtxMax.y
			&& pPos->y - m_size.y / 2 < m_pos.y + m_vtxMax.y)
		{
			pPos->y = m_pos.y + m_vtxMax.y + m_size.y / 2;
			m_bOn = true;
		}
		//���̓����蔻��
		if (pPosOld->y + size.y / 2 <= m_pos.y + m_vtxMin.y
			&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
			)

		{
			pPos->y = m_pos.y + m_vtxMin.y - size.y;
			m_bOn = false;
		}
	}

}