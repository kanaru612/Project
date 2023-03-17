//============================================================================CEnemy=
//
// boss.cpp
// Author : 
//
//=============================================================================]
#include"boss.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"bullet.h"
#include"score.h"
#include"game.h"
LPDIRECT3DTEXTURE9 CBoss::m_ptex = {};
CBoss::CBoss()	:	CObject2D(3)
{
	m_move = { 0.0f,0.0f,0.0f };
	m_nCnt = 0;
	m_nLife = 0;
	m_pScore = {};
}

CBoss::~CBoss()
{
}
//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CBoss::Init()
{
	CObject2D::Init();
	m_move = { 0.0f,0.0f,0.0f };
	srand((unsigned int)time(NULL));
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CBoss::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CBoss::Update()
{
	D3DXVECTOR3 bpos = Getpos();
	D3DXVECTOR3 bsize = Getsize();
	bpos.x += m_move.x;
	bpos.y += m_move.y;
	setpos(bpos);
	m_nCnt++;
	if (m_nCnt >= 60)
	{
		m_nCnt = 0;
		int nrand = rand() % 2 + 1;
		if (nrand == 1)
		{
			CBullet::Create({ bpos.x - bsize.x * 2,bpos.y,bpos.z }, { -10.0f,0.0f,0.0f }, 1);
		}
		if (nrand == 2)
		{
			CBullet::Create({ bpos.x - bsize.x * 2,bpos.y,bpos.z }, { -10.0f,0.0f,0.0f }, 2);
		}
	}
	if (bpos.x + bsize.x > SCREEN_WIDTH)
	{
		m_move.x *= -1.0f;
	}
	if (bpos.x - bsize.x < 0)
	{
		m_move.x *= -1.0f;
	}
	CObject2D::Update();

}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBoss::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// �N���G�C�g
//=============================================================================
CBoss *CBoss::Create(const D3DXVECTOR3 pos)
{
	CBoss *pboss = nullptr;

	//���I����
	pboss = new CBoss;

	pboss->Init();
	pboss->setpos(pos);

	pboss->SetType(OBJTYPE_ENEMY);
	D3DXVECTOR3 size = D3DXVECTOR3(800, 100, 0.0f);
	pboss->setsize(size);

	return pboss;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/bosuatamanoue.png",
		&m_ptex);

	return S_OK;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBoss::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
}