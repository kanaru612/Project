//============================================================================
//
// Goal.cpp
// Author : �����@�t��
//
//=============================================================================
#include"goal.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
CGoal::CGoal(int nPriority) : CModel(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bUse = false;
}

CGoal::~CGoal()
{
}
//-------------------------------------------------------------------------
// �S�[���̏�����
//-------------------------------------------------------------------------
HRESULT CGoal::Init()
{
	m_FadeFlag = false;
	CModel::Init();
	SetGoal("data/model/goal.x");
	return S_OK;
}
//-------------------------------------------------------------------------
// �S�[���̏I��
//-------------------------------------------------------------------------
void CGoal::Uninit()
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

	//Release();
}

//-------------------------------------------------------------------------
// �S�[���̍X�V
//-------------------------------------------------------------------------
void CGoal::Update()
{
	if (m_GoalFlag == true && m_FadeFlag == false)
	{
		CFade::Set(CApplication::MODE_RANKING);
		m_FadeFlag = true;
	}
}
//-------------------------------------------------------------------------
// �S�[���̕`��
//-------------------------------------------------------------------------
void CGoal::Draw()
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
		if (bUse == true)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//-------------------------------------------------------------------------
// �S�[���̐���
//-------------------------------------------------------------------------
CGoal *CGoal::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGoal *pGoal = nullptr;

	//���I����
	pGoal = new CGoal;
	if (pGoal != nullptr)
	{
		pGoal->Init();
		pGoal->m_pos = pos;
		pGoal->SetType(OBJTYPE_ENEMY);
		pGoal->m_rot = rot;
		pGoal->bUse = true;
	}
	return pGoal;
}
//============================================
// �S�[���̐ݒ�
//============================================
void CGoal::SetGoal(char * pFile)
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
//�S�[���ƃv���C���[�̓����蔻��
//-------------------------------------------------------------------------
void CGoal::Collision(D3DXVECTOR3 *pPos,			//���݂̈ʒu
	D3DXVECTOR3 *pPosOld,								//�O��̈ʒu
	D3DXVECTOR3 size)									//�T�C�Y
{

	if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
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
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
		}
		//��O�̓����蔻�� 
		if (
			pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
			&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f
			)
		{
			pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
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
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
		}
		//�E�̓����蔻��
		if (
			pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
			&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2
			)
		{
			pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
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
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);
		}
		//���̓����蔻��
		if (pPosOld->y + size.y / 2 <= m_pos.y + m_vtxMin.y
			&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
			)

		{
			pPos->y = m_pos.y + m_vtxMin.y - size.y;
			m_GoalFlag = true;
			//bUse = false;
			//CFade::Create(CApplication::MODE_RANKING);

		}
	}
}