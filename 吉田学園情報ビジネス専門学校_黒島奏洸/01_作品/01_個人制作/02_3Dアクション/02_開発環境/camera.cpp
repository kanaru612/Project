//=============================================================================
//
//  Camera.cpp
//  Author : �����@�t��
//
//=============================================================================
#include "camera.h"
#include"input.h"
#include"application.h"
#include"rendere.h"
#include"player.h"
#include"game.h"
D3DXVECTOR3 CCamera::m_rot = {};

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}
//------------------------------------------------------------------------
//�J�����̏���������
//-------------------------------------------------------------------------
void CCamera::Init(void)
{
	//���_,�����_,�����,�p�x��ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 50.0f, 150.0f);
	//m_posV = D3DXVECTOR3(0.0f,200.0f,200.0f);
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rot  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//posR��posV�̋��������߂�
	m_fDistance = sqrtf((m_posV.x - m_posR.x)*(m_posV.x - m_posR.x) 
		+ (m_posV.z - m_posR.z)*(m_posV.z - m_posR.z)) ;
}

//------------------------------------------------------------------------
//�J�����̏I������
//-------------------------------------------------------------------------
void CCamera::Uninit(void)
{

}

//------------------------------------------------------------------------
//�J�����̍X�V����
//-------------------------------------------------------------------------
void CCamera::Update(void)
{
	//�����_�̐���
	//�p�x��-n�`n(-D3DX_PI �`D3DX_PI)-180�`180�͈̔͂Ɏ��܂�悤�ɂ���
	//(184�x�̏ꍇ-176�ɂ���)�p�x�̐��K��
	CInput *pInput = CApplication::GetKeyboard();
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	if (CApplication::GetMode() == CApplication::MODE_GAME)
	{
		CPlayer *pPlayer = CGame::GetPlayer();

		m_posRDest.x = pPlayer->Getpos().x + sin(m_rot.y) * -5.0f;
		m_posRDest.y = 0.0f;
		m_posRDest.z = pPlayer->Getpos().z + cos(m_rot.y) * -5.0f;

		m_posVDest.x = pPlayer->Getpos().x - sin(m_rot.y) * m_fDistance;
		m_posVDest.y = 0.0f;
		m_posVDest.z = pPlayer->Getpos().z - cos(m_rot.y) * m_fDistance;

		m_posR.x += (m_posRDest.x - m_posR.x) * 1.0f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 1.0f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 1.0f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 1.0f;
	}
}

//------------------------------------------------------------------------
//�J�����̐ݒ菈��
//-------------------------------------------------------------------------
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�ւ̃|�C���g

	pDevice = CApplication::GetRendere()->GetDevice();
	
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixLookAtLH(	&m_mtxView,
						&m_posV,
						&m_posR,
						&m_vecU);

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�҂낶���������}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		1000.0f
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}