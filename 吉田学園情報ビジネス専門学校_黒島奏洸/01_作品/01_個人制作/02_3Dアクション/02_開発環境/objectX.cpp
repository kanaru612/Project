//============================================================================
//
// ObjectX.cpp
// Author : �����@�t��
//
//=============================================================================
#include"main.h"
#include"object.h"
#include"objectX.h"
#include"rendere.h"
#include"application.h"
#include"input.h"
#include"game.h"
//-------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pos = {};
	m_fAngle = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
	m_fWidth = 0.0f;
	m_rot = { 0.0f,0.0f,0.0f };
	m_Size = { 0.0f,0.0f,0.0f };
	m_frevAngle = 0.0f;
	m_frevRadius = 0.0f;
	m_frevSpeed = 0.0f;
	m_revCentor = { 0.0f,0.0f,0.0f };
	m_bUse = false;
}

//-------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------
CObjectX::~CObjectX()
{
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̏�����
//-------------------------------------------------------------------------
HRESULT CObjectX::Init()
{
	m_bUse = false;
	set("data/model/ken.x");
	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g		
	pDevice = CApplication::GetRendere()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z - m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z - m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);

	//�@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�J���[�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_fWidth = pVtx[2].pos.x - pVtx[0].pos.x;
	m_fHeight = pVtx[0].pos.y - pVtx[1].pos.y;

	//�Ίp���̒���
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth) / 2.0f;
	//�Ίp���̊p�x
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̏I��
//-------------------------------------------------------------------------
void CObjectX::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	Release();
}

//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̍X�V
//-------------------------------------------------------------------------
void CObjectX::Update()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (m_frevRadius != 0.0f)
	{
		m_pos.x = m_revCentor.x + cosf(m_frevAngle) * m_frevRadius;
		m_pos.y = m_revCentor.y + sinf(m_frevAngle) * m_frevRadius;
	}

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	m_frevAngle += m_frevSpeed;
	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̕`��
//-------------------------------------------------------------------------
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g

	pDevice = CApplication::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCnt = 0; nCnt < MAX_MODELFLOOR; nCnt++)
	{
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

		//���݂̃}�e���A���̕ێ�
		pDevice->GetMaterial(&matDef);

		////�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
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
// pos�ݒ�
//-------------------------------------------------------------------------
void CObjectX::setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̐���
//-------------------------------------------------------------------------
CObjectX *CObjectX::Create(const D3DXVECTOR3 pos)
{
	CObjectX *apObject2D = nullptr;

	//���I����
	apObject2D = new CObjectX;

	apObject2D->Init();
	apObject2D->setpos(pos);

	return apObject2D;
}
//-------------------------------------------------------------------------
// �e�N�X�`���̐ݒ�
//-------------------------------------------------------------------------
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}
//-------------------------------------------------------------------------
// �T�C�Y�̐ݒ�
//-------------------------------------------------------------------------
void CObjectX::setsize(D3DXVECTOR3 size)
{
	m_Size = size;
}
//-------------------------------------------------------------------------
// �e�N�X�`���̔��f
//-------------------------------------------------------------------------
void CObjectX::setTexture(float Upos1, float Upos2, float Bpos1, float Bpos2)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(Upos1, Bpos1);
	pVtx[1].tex = D3DXVECTOR2(Upos2, Bpos1);
	pVtx[2].tex = D3DXVECTOR2(Upos1, Bpos2);
	pVtx[3].tex = D3DXVECTOR2(Upos2, Bpos2);

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �^�C�v�̐ݒ�
//-------------------------------------------------------------------------
void CObjectX::settype(int type)
{
	m_nType = type;
}
//-------------------------------------------------------------------------
// ���C�t�̐ݒ�
//-------------------------------------------------------------------------
void CObjectX::setlife(int life)
{
	m_nLife = life;
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void CObjectX::setrotate(D3DXVECTOR3 rot)
{
	m_rot = rot;


	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void  CObjectX::setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius)
{
	m_revCentor = Center;
	m_frevSpeed = fSpeed;
	m_frevRadius = fRadius;
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void  CObjectX::setrevCenter(D3DXVECTOR3 revCenter)
{
	m_revCentor = revCenter;
}
//-------------------------------------------------------------------------
// �F�̐ݒ�
//-------------------------------------------------------------------------
void CObjectX::setcolor(float r, float g, float b, float ��)
{
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(r, g, b, ��);
	pVtx[1].col = D3DXCOLOR(r, g, b, ��);
	pVtx[2].col = D3DXCOLOR(r, g, b, ��);
	pVtx[3].col = D3DXCOLOR(r, g, b, ��);

	//���_�o�b�t�@���A�����b�N����
	Buffer->Unlock();
}
//-------------------------------------------------------------------------
// �ݒ�
//-------------------------------------------------------------------------
CObjectX *CObjectX::set(char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		
	for (int nCnt = 0; nCnt < MAX_MODELFLOOR; nCnt++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			//�t�@�C����,
			pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);
	}
	m_bUse = true;
	return S_OK;
}
