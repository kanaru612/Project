//-------------------------------------------------------------------------================================
//
// Modelparts.cpp
// Author : �����@�t��
//
//-------------------------------------------------------------------------=================================
#include"modelparts.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"objectX.h"
#include"shadow.h"
#include"camera.h"

CModelparts::CModelparts()
{
	m_pVtxBuff = {};
	m_mtxWorld = {};
	//�ʒu�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
CModelparts::~CModelparts()
{
}

//-------------------------------------------------------------------------
// ���f���p�[�c�̏�����
//-------------------------------------------------------------------------
HRESULT CModelparts::Init()
{
	
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    
	//�ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
//-------------------------------------------------------------------------
// ���f���p�[�c�̏I��
//-------------------------------------------------------------------------
void CModelparts::Uninit()
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
}

//-------------------------------------------------------------------------
// ���f���p�[�c�̍X�V
//-------------------------------------------------------------------------
void CModelparts::Update()
{
}
//-------------------------------------------------------------------------
// ���f���p�[�c�̕`��
//-------------------------------------------------------------------------
void CModelparts::Draw()
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

	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_mtxParent);

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
// ���f���p�[�c�̐���
//-------------------------------------------------------------------------
CModelparts * CModelparts::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelparts *pModelparts = nullptr;

	// 3D�I�u�W�F�N�g�N���X�̐���
	pModelparts = new CModelparts;				// 3D�I�u�W�F�N�g�̃C���X�^���X����

	// nullptr�`�F�b�N
	if (pModelparts != nullptr)
	{
		// ����������
		pModelparts->Init();
		pModelparts->m_pos = pos;
		pModelparts->m_rot = rot;
	}
	return pModelparts;
}
//-------------------------------------------------------------------------
// ���f���p�[�c�̐ݒ�
//-------------------------------------------------------------------------
void CModelparts::SetModel(char * pFile)
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

	//���_���̎擾
	m_nNumvtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuf);

	for (int nCntvtx = 0; nCntvtx < m_nNumvtx; nCntvtx++)
	{
		//���_���W����
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuf;

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
		m_pVtxBuf += m_sizeFVF;
	}


	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();
}
