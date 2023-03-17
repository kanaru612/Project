//-------------------------------------------------------------------------================================
//
// Mode.cpp
// Author : �����@�t��
//
//-------------------------------------------------------------------------=================================
#include"model.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"objectX.h"
#include"shadow.h"
#include"camera.h"
#include"model.h"
#include"player.h"
#include"game.h"

CModel::CModel(int nPriority) : CObject(nPriority)
{
	//�ʒu�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
CModel::~CModel()
{
}

//-------------------------------------------------------------------------
// ���[�h�̏�����
//-------------------------------------------------------------------------
HRESULT CModel::Init()
{
	//�ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
//-------------------------------------------------------------------------
// ���[�h�̏I��
//-------------------------------------------------------------------------
void CModel::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	Release();
}

//-------------------------------------------------------------------------
// ���[�h�̍X�V
//-------------------------------------------------------------------------
void CModel::Update()
{
	setpos(m_pos);
}
//-------------------------------------------------------------------------
// ���[�h�̕`��
//-------------------------------------------------------------------------
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[�J���}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//-------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pweapon = nullptr;

	pweapon = new CModel;				// 3D�I�u�W�F�N�g�̃C���X�^���X����

	// null�`�F�b�N
	if (pweapon != nullptr)
	{
		pweapon->Init();
		pweapon->m_pos = pos;
		pweapon->m_rot = rot;
	}

	return pweapon;
}
//-------------------------------------------------------------------------
// ���f���̐ݒ�
//-------------------------------------------------------------------------
void CModel::SetModel(char * pFile)
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

	
}
//-------------------------------------------------------------------------
//���f���ƃv���C���[�̓����蔻��
//-------------------------------------------------------------------------
void CModel::Collision(D3DXVECTOR3 *pPos,				//���݂̈ʒu
	D3DXVECTOR3 *pPosOld,								//�O��̈ʒu
	D3DXVECTOR3 size)									//�T�C�Y
{
	CInput *pInput = CApplication::GetKeyboard();
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->Getpos();

	if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
		&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x)
	{
		//���̓����蔻��
		if (
			pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
			&& pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f
			)
		{
			pPos->z = m_pos.z + m_vtxMax.z + size.z / 2.0f;
			m_bOn = false;
		}
		//��O�̓����蔻�� 
		if (
			pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
			&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f

			)
		{
			pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
			m_bOn = false;
		}
	}
	if (pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
		&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z)
	{

		//���̓����蔻��
		if (
			pPosOld->x <= m_pos.x + m_vtxMin.x - size.x / 2
			&& pPos->x > m_pos.x + m_vtxMin.x - size.x / 2
			)
		{
			pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
			m_bOn = false;
		}
		//�E�̓����蔻��
		if (
			pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
			&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2
			)
		{
			pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
			m_bOn = false;
		}
	}

	if (pPos->x - size.x / 2.0f < m_pos.x + m_vtxMax.x
		&& pPos->x + size.x / 2.0f > m_pos.x + m_vtxMin.x
		&&pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
		&&pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f)
	{
		//��̓����蔻��
		if (pPosOld->y >= m_pos.y + m_vtxMax.y
			&& pPos->y < m_pos.y + m_vtxMax.y)
		{
			pPos->y = m_pos.y + m_vtxMax.y;
			m_bOn = true;
		}
		//���̓����蔻��
		if (pPosOld->y + size.y <= m_pos.y + m_vtxMin.y
			&& pPos->y + size.y > m_pos.y + m_vtxMin.y)
		{
			pPos->y = m_pos.y + m_vtxMin.y - size.y;
			m_bOn = false;
		}
	}
}
//-------------------------------------------------------------------------
//�T�C�Y
//-------------------------------------------------------------------------
void CModel::Vtx(void)
{
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