//-------------------------------------------------------------------------================================
//
// Coin.cpp
// Author : �����@�t��
//
//-------------------------------------------------------------------------=================================
#include"Coin.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
#include"sound.h"
CCoin::CCoin(int nPriority) : CModel(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bUse = false;
	m_bOn = false;
}

CCoin::~CCoin()
{
}
//-------------------------------------------------------------------------
// �R�C���̏�����
//-------------------------------------------------------------------------
HRESULT CCoin::Init()
{
	m_CoinSEFlag = true;
	CModel::Init();
	SetCoin("data/model/coin.x");
	return S_OK;
}
//-------------------------------------------------------------------------
// �R�C���̏I��
//-------------------------------------------------------------------------
void CCoin::Uninit()
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
// �R�C���̍X�V
//-------------------------------------------------------------------------
void CCoin::Update()
{
	if (m_CoinSEFlag == false)
	{
		PlaySound(SOUND_LABEL_SE_COIN);
		m_CoinSEFlag = true;
	}
}
//-------------------------------------------------------------------------
// �R�C���̕`��
//-------------------------------------------------------------------------
void CCoin::Draw()
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
// �R�C���̐���
//-------------------------------------------------------------------------
CCoin *CCoin::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CCoin *pSbox = nullptr;

	//���I����
	pSbox = new CCoin;
	if (pSbox != nullptr)
	{
		pSbox->Init();
		pSbox->m_pos = pos;
		pSbox->SetType(OBJTYPE_ENEMY);
		pSbox->m_rot = rot;
		pSbox->bUse = true;
	}
	return pSbox;
}
//-------------------------------------------------------------------------
// �R�C���̐ݒ�
//-------------------------------------------------------------------------
void CCoin::SetCoin(char * pFile)
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
//�R�C���ƃv���C���[�̓����蔻��
//-------------------------------------------------------------------------
void CCoin::Collision(D3DXVECTOR3 *pPos,			//���݂̈ʒu
	D3DXVECTOR3 *pPosOld,								//�O��̈ʒu
	D3DXVECTOR3 size)									//�T�C�Y
{
	if (bUse == true)
	{
		CInput *pInput = CApplication::GetKeyboard();

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
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;
			}
			//��O�̓����蔻�� 
			if (
				pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
				&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f


				)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
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
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;

			}
			//�E�̓����蔻��
			if (
				pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
				&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2

				)
			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
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
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = true;
			}
			//���̓����蔻��
			if (pPosOld->y + size.y / 2 <= m_pos.y + m_vtxMin.y
				&& pPos->y + size.y / 2 > m_pos.y + m_vtxMin.y
				)

			{
				CGame::GetScore()->add(500);
				m_CoinSEFlag = false;
				bUse = false;
				m_bOn = false;
			}
		}
	}
}