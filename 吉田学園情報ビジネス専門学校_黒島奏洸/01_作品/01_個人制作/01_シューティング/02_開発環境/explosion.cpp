//=============================================================================
//
// explosion.cpp
// Author : 
//
//=============================================================================
#include"explosion.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"bullet.h"
#define MAX_EXPLOSION (256)
#define MAX_SIZEE	(50)
#define MAX_ESPLOSIONANIM	(8.0f)
LPDIRECT3DTEXTURE9 CExplosion::m_ptex = {};

CExplosion::CExplosion()
{
	m_nPattern = 0;
	nCntAnim = 0;
}

CExplosion::~CExplosion()
{
}
//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CExplosion::Init()
{
	CObject2D::Init();
	BindTexture(m_ptex);
	setTexture((m_nPattern / MAX_ESPLOSIONANIM), ((m_nPattern + 1) / MAX_ESPLOSIONANIM), 0.0f, 1.0f);
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CExplosion::Update()
{	
	nCntAnim++;

	if (nCntAnim % 3 == 0)
	{
		setTexture((m_nPattern / MAX_ESPLOSIONANIM), ((m_nPattern + 1) / MAX_ESPLOSIONANIM), 0.0f, 1.0f);
		m_nPattern++;
		nCntAnim = 0;
	}

	if (m_nPattern >= MAX_ESPLOSIONANIM)
	{
		m_nPattern = 0;
		Uninit();
		return;
	}

	CObject2D::Update();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CExplosion::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos)
{
	CExplosion *pExpl = nullptr;

	//���I����
	pExpl = new CExplosion;
	pExpl->Init();
	pExpl->setpos(pos);
	pExpl->SetType(OBJTYPE_EXPLSION);
	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZEB, MAX_SIZEB, 0.0f);
	pExpl->setsize(size);
	return pExpl;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/explosion000.png",
		&m_ptex);

	return S_OK;

}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CExplosion::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
}