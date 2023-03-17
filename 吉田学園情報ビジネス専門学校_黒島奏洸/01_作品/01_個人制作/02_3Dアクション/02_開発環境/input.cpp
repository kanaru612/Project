//=============================================================================
//
// Input.cpp
// Author : 黒島奏洸
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
//インプットの初期化
//-------------------------------------------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
//-------------------------------------------------------------------------
//インプットの終了
//-------------------------------------------------------------------------
void  CInput::Uninit(void)
{
	//入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//-------------------------------------------------------------------------
//インプットの更新
//-------------------------------------------------------------------------
void  CInput::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//キーボードの入力情報
	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateT[nCntKey] = (m_aKeyStateP[nCntKey] ^ aKeyState[nCntKey])  & aKeyState[nCntKey];
			m_aKeyStateP[nCntKey] = aKeyState[nCntKey];	//キーボードのプレスの情報
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//-------------------------------------------------------------------------
//インプットのプレス
//-------------------------------------------------------------------------
bool CInput::GetPress(int nKey)
{
	return(m_aKeyStateP[nKey] & 0x80) ? true : false;
}
//-------------------------------------------------------------------------
//インプットのトリガー
//-------------------------------------------------------------------------
bool CInput::GetTrriger(int nKey)
{
	return (m_aKeyStateT[nKey] & 0x80) ? true : false;
}
