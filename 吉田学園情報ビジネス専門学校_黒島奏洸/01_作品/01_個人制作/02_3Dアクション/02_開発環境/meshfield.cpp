//=============================================================================
//
// Meshfield.cpp
// Author : �����@�t��
//
//=============================================================================
#include "meshfield.h"
#include"application.h"
#include"rendere.h"
#include"object.h"
#include"object2D.h"
LPDIRECT3DTEXTURE9 CMeshfield::m_pTexture = {};

CMeshfield::CMeshfield(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CMeshfield::~CMeshfield()
{
}
//-------------------------------------------------------------------------
//���b�V���t�B�[���h�̏���������
//-------------------------------------------------------------------------
HRESULT CMeshfield::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRendere()->GetDevice();

	//���_�o�b�t�@�̐���(�C���f�b�N�X)
	pDevice->CreateIndexBuffer(sizeof(WORD) *  MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	//�C���f�b�N�X�ւ̃|�C���^0.
	WORD *pIdx;
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < MESHFIELD_Z_BLOCK + 1; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < MESHFIELD_X_BLOCK + 1; nCnt2++)
		{
			/*int nRand = rand() % 100 - 50;*/
			//���_���W�̐ݒ�
			//���_���W�̐ݒ�(���[���h���W�ł͂Ȃ����[�J�����W��ݒ�)
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-150.0f + (nCnt2 * 15.0f), 0.0f, 150.0f - (nCnt1 * 15.0f));
			//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[�̐ݒ�						
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W�̐ݒ�				  
			pVtx[nCnt2 + (nCnt1 * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCnt2, (float)nCnt1);
		}
	}
	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt1 = 0; nCnt1 < MESHFIELD_Z_BLOCK; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < MESHFIELD_X_BLOCK + 1; nCnt2++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCnt2 + nCnt1 * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCnt2 + nCnt1 * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);

			pIdx += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
	
	return S_OK;
}

//-------------------------------------------------------------------------
//���b�V���t�B�[���h�̏I������
//-------------------------------------------------------------------------
void CMeshfield::Uninit(void)
{
	
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//-------------------------------------------------------------------------
//���b�V���t�B�[���h�̍X�V����
//-------------------------------------------------------------------------
void CMeshfield::Update(void)
{
	
}

//------------------------------------------------------------------------
//���b�V���t�B�[���h�̕`�揈��
//-------------------------------------------------------------------------
void CMeshfield::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);									

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);		
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);	

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);					

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITVE_NUM);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, nullptr);
}
CMeshfield *CMeshfield::Create()
{
	CMeshfield *pMesh = nullptr;

	//���I����
	pMesh = new CMeshfield;
	if (pMesh != nullptr)
	{
		pMesh->Init();
		pMesh->SetType(OBJTYPE_MESHFIELD);
	}
	return pMesh;
}
void CMeshfield::Collision(D3DXVECTOR3 mpos)
{

	int primitive = MESHFIELD_PRIMITVE_NUM;
	VERTEX_3D* pVtx = NULL;			// ���_���ւ̃|�C���^
	WORD* pIdx;
	const int nTri = 3;
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{
		D3DXVECTOR3 posPoly[nTri];

		// ���_���W�̎擾
		posPoly[0] = pVtx[pIdx[nCnt + 0]].pos;
		posPoly[1] = pVtx[pIdx[nCnt + 1]].pos;
		posPoly[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// �k�ރ��b�V���t�B�[���h���΂�
			continue;
		}

		D3DXVECTOR3 vecLine[nTri];

		// ���_���W�̎擾
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		// ���_���W�̎擾
		vecPlayer[0] = m_pos - posPoly[0];
		vecPlayer[1] = m_pos - posPoly[1];
		vecPlayer[2] = m_pos - posPoly[2];

		float InOut[nTri];

		InOut[0] = vecLine[0].x * vecPlayer[0].x + vecLine[0].z * vecPlayer[0].z;
		InOut[1] = vecLine[1].x * vecPlayer[1].x + vecLine[1].z * vecPlayer[1].z;
		InOut[2] = vecLine[2].x * vecPlayer[2].x + vecLine[2].z * vecPlayer[2].z;


		if ((InOut[0] > 0 && InOut[1] > 0 && InOut[2] > 0)
			|| (InOut[0] < 0 && InOut[1] < 0 && InOut[2] < 0))
		{
			D3DXVECTOR3 V1 = posPoly[1] - posPoly[0];
			D3DXVECTOR3 V2 = posPoly[2] - posPoly[0];

			// ���ʂ̔�
			D3DXVECTOR3 vecNormal;
			// ���b�V���̖@�������߂�
			D3DXVec3Cross(&vecNormal, &V1, &V2);
			// �傫�����P�ɂ���
			D3DXVec3Normalize(&vecNormal, &vecNormal);

			mpos.y = posPoly[0].y - (vecNormal.x * (mpos.x - posPoly[0].x) + vecNormal.z * (mpos.z - posPoly[0].z)) / vecNormal.y;
		}
	}
		// �C���f�b�N�X�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
		// ���_�o�b�t�@���A�����b�N����
		m_pIdxBuff->Unlock();
}
//=============================================================================
// ���b�V���t�B�[���h�̕`��
//=============================================================================
HRESULT CMeshfield::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/��.jpg",
		&m_pTexture);

	return S_OK;
}
//=============================================================================
// ���b�V���t�B�[���h�̕`��
//=============================================================================
void CMeshfield::Unload(void)
{

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}


