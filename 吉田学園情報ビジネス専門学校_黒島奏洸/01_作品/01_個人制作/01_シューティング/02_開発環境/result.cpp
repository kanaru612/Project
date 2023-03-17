//=============================================================================
//
// block.cpp
// Author : 
//
//=============================================================================]
#include"result.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"fade.h"
#include"score.h"
#include"sound.h"
LPDIRECT3DTEXTURE9 CResult::m_ptex[2] = {};
CResult::CResult()
{
	m_bfr = false;
}
CResult::~CResult()
{

}
//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CResult::Init()
{

	m_bfr = false;
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		
	PlaySound(SOUND_LABEL_BGM002);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/result.jpg",
		&m_ptex[0]);
	

	m_pObject = CObject2D::Create({ 640.0f,360.0f,0.0f });
	m_pObject->setsize({ 640.0f,360.0f,0.0f });
	m_pObject->BindTexture(m_ptex[0]);

	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CResult::Uninit()
{
	StopSound();
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		m_pObject = nullptr;
	}
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{

		if (m_ptex[nCnt] != NULL)
		{
			m_ptex[nCnt]->Release();
			m_ptex[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CResult::Update()
{
	CInput *pInput = CApplication::GetKeyboard();
	//�G���^�[�L�[�Ŏ��̉�ʂ�

	if (pInput->GetTrriger(DIK_RETURN) == true && m_bfr == false)
	{
		CFade::Set(CApplication::MODE_RANKING);
		m_bfr = true;
	}
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CResult *CResult::Create()
{
	CResult *presult = nullptr;

	//���I����
	presult = new CResult;

	presult->Init();
	return presult;
}