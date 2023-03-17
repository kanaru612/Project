//=============================================================================
//
// Input.cpp
// Author : �����t��
//
//=============================================================================
#include"Input.h"
LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{
}

CInput::~CInput()
{
}
//-------------------------------------------------------------------------
//�C���v�b�g�̏�����
//-------------------------------------------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐ݒ�
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//-------------------------------------------------------------------------
//�C���v�b�g�̏I��
//-------------------------------------------------------------------------
void  CInput::Uninit(void)
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//-------------------------------------------------------------------------
//�C���v�b�g�̍X�V
//-------------------------------------------------------------------------
void  CInput::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateT[nCntKey] = (m_aKeyStateP[nCntKey] ^ aKeyState[nCntKey])  & aKeyState[nCntKey];
			m_aKeyStateP[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h�̃v���X�̏��
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//-------------------------------------------------------------------------
//�C���v�b�g�̃v���X
//-------------------------------------------------------------------------
bool CInput::GetPress(int nKey)
{
	return(m_aKeyStateP[nKey] & 0x80) ? true : false;
}
//-------------------------------------------------------------------------
//�C���v�b�g�̃g���K�[
//-------------------------------------------------------------------------
bool CInput::GetTrriger(int nKey)
{
	return (m_aKeyStateT[nKey] & 0x80) ? true : false;
}
