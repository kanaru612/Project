//============================================================================
//
// Shadow.cpp
// Author : �����@�t��
//
//=============================================================================
#include "shadow.h"
#include"application.h"
#include"rendere.h"
#include"object3D.h"
CShadow::CShadow()
{
}

CShadow::~CShadow()
{
}
//-------------------------------------------------------------------------
//�e�̏���������
//-------------------------------------------------------------------------
HRESULT CShadow::Init(void)
{
	CObject3D::Init();
	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g			

	//�f�o�C�X�̎擾
	pDevice = CApplication::GetRendere()->GetDevice();
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/shadow000.jpg",
		&m_pTexture);

	return S_OK;
}

//-------------------------------------------------------------------------
//�e�̏I������
//-------------------------------------------------------------------------
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//-------------------------------------------------------------------------
//�e�̍X�V����
//-------------------------------------------------------------------------
void CShadow::Update(void)
{
	CObject3D::Update();
}
//-------------------------------------------------------------------------
//�e�̕`�揈��
//-------------------------------------------------------------------------
void CShadow::Draw(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g
								  //�f�o�C�X�̎擾
	pDevice = CApplication::GetRendere()->GetDevice();
	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CObject3D::Draw();

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//-------------------------------------------------------------------------
//�e�̐ݒ菈��
//-------------------------------------------------------------------------
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadow *pshadow = nullptr;

	//���I����
	pshadow = new CShadow;
	if (pshadow != nullptr)
	{
		pshadow->Init();
		pshadow->set(pos, rot);
		
	}
	return pshadow;
}
//-------------------------------------------------------------------------
//�e�̍X�V����
//-------------------------------------------------------------------------
void CShadow::SetPos(int nIdxShadow, D3DXVECTOR3 pos)
{
	//�����Ŏw�肳�ꂽ�ԍ��̉e��pos����
	m_aShadow[nIdxShadow].pos = pos;
}
int CShadow::set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (m_aShadow[nCntShadow].bUse == false)
		{
			m_aShadow[nCntShadow].pos = pos;
			m_aShadow[nCntShadow].rot = rot;
			m_aShadow[nCntShadow].bUse = true;
			break;
		}
	}
	return nCntShadow;
}