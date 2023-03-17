//=============================================================================
//
// Light.cpp
// Author : �����t��
//
//=============================================================================
#include"light.h"
#include"application.h"
#include"rendere.h"
//�O���[�o���ϐ�
CLight::CLight()
{
}

CLight::~CLight()
{
}
//------------------------------------------------------------------------
//���C�g�̏���������
//------------------------------------------------------------------------
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CApplication::GetRendere()->GetDevice();

	D3DXVECTOR3 vecDir; //���C�g�̕����̃x�N�g��
	//
	//1��
	//
	//���C�g���N���A�ɂ���
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;        //���s����

	//���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //���C�g�̐F

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);	//�������O
	//���K������i�傫���̂P�̃x�N�g���ɂ���j       
	D3DXVec3Normalize(&vecDir, &vecDir);

	//���C�g��ݒ肷��
	m_light[0].Direction = vecDir;
	pDevice->SetLight(0, &m_light[0]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//
	//2��
	//
	//���C�g���N���A�ɂ���
	ZeroMemory(&m_light[1], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;        //���s����

	//���C�g�̊g�U����ݒ�
	m_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //���C�g�̐F
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	//��O���牜
	//���K������i�傫���̂P�̃x�N�g���ɂ���j       
	D3DXVec3Normalize(&vecDir, &vecDir);
	//���C�g��ݒ肷��
	m_light[1].Direction = vecDir;
	pDevice->SetLight(1, &m_light[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);
	//
	//3��
	//
	//���C�g���N���A�ɂ���
	ZeroMemory(&m_light[2], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;        //���s����

	//���C�g�̊g�U����ݒ�
	m_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //���C�g�̐F
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);	//��O���牜
	//���K������i�傫���̂P�̃x�N�g���ɂ���j       
	D3DXVec3Normalize(&vecDir, &vecDir);
	//���C�g��ݒ肷��
	m_light[2].Direction = vecDir;
	pDevice->SetLight(2, &m_light[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);
	//
	//4��
	//
	//���C�g���N���A�ɂ���
	ZeroMemory(&m_light[3], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_light[3].Type = D3DLIGHT_DIRECTIONAL;        //���s����

	//���C�g�̊g�U����ݒ�
	m_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);      //���C�g�̐F
	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.5f, -1.0f, 0.5f);	//��O���牜
	//���K������i�傫���̂P�̃x�N�g���ɂ���j       
	D3DXVec3Normalize(&vecDir, &vecDir);
	//���C�g��ݒ肷��
	m_light[3].Direction = vecDir;
	pDevice->SetLight(3, &m_light[3]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(3, TRUE);

}

//------------------------------------------------------------------------
//���C�g�̏I������
//------------------------------------------------------------------------
void CLight::Uninit(void)
{

}
//------------------------------------------------------------------------
//���C�g�̍X�V����
//------------------------------------------------------------------------
void CLight::Update(void)
{

}
//------------------------------------------------------------------------
//���C�g�̍X�V����
//------------------------------------------------------------------------
CLight *CLight::Create()
{
	CLight *plight = nullptr;

	//���I����
	plight = new CLight;

	if (plight != nullptr)
	{
		plight->Init();
	}
	return plight;
}

