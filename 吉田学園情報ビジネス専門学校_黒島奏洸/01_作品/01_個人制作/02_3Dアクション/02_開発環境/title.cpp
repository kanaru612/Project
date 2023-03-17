//============================================================================
//
// Title.cpp
// Author : �����@�t��
//
//=============================================================================
#include"title.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"object2D.h"
#include"fade.h"
#include"object2D.h"
#include"sound.h"

CTitle::CTitle() 
{
	m_bf = false;
	m_sound = false;
}
CTitle::~CTitle()
{

}
//-------------------------------------------------------------------------
// �^�C�g���̏�����
//-------------------------------------------------------------------------
HRESULT CTitle::Init()
{
	m_bf = false;
	m_sound = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/title.png",
		&m_ptex);

	m_pObject = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject->setsize({ 640.0f,360.0f,0.0f });

	m_pObject->BindTexture(m_ptex);

	return S_OK;
}
//-------------------------------------------------------------------------
// �^�C�g���̏I��
//-------------------------------------------------------------------------
void CTitle::Uninit()
{
	StopSound();
	CObject::Release();
}

//-------------------------------------------------------------------------
// �^�C�g���̍X�V
//-------------------------------------------------------------------------
void CTitle::Update()
{
	if (m_sound == false)
	{
		PlaySound(SOUND_LABEL_BGM001);
		m_sound = true;
	}
	CInput *pInput = CApplication::GetKeyboard();
	//�G���^�[�L�[�Ŏ��̉�ʂ�

	if (pInput->GetTrriger(DIK_RETURN) == true && m_bf == false)
	{
		CFade::Set(CApplication::MODE_TUTRIAL);
		m_bf = true;
	}
}

//-------------------------------------------------------------------------
// �^�C�g���̐���
//-------------------------------------------------------------------------
CTitle *CTitle::Create()
{
	CTitle *ptitle = nullptr;

	//���I����
	ptitle = new CTitle;

	ptitle->Init();
	
	return ptitle;
}

