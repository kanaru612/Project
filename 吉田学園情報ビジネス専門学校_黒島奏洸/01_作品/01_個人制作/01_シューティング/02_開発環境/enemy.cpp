//============================================================================CEnemy=
//
// enemy.cpp
// Author : 
//
//=============================================================================]
#include"enemy.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"bullet.h"
#include"score.h"
#include"game.h"
#include"fade.h"
LPDIRECT3DTEXTURE9 CEnemy::m_ptex = {};
int CEnemy::m_nLife = 0;
CEnemy::CEnemy()
{
	m_move = { 0.0f,0.0f,0.0f };
	m_nCnt = 0;
	m_nLife = 0;
	m_pScore = {};
}

CEnemy::~CEnemy()
{
}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CEnemy::Init()
{
	CObject2D::Init();
	m_move = { 0.0f,0.0f,0.0f };
	srand((unsigned int)time(NULL));
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CEnemy::Update()
{
	D3DXVECTOR3 bpos = Getpos();
	D3DXVECTOR3 bsize = Getsize();

	bpos.x += m_move.x;
	bpos.y += m_move.y;

	setpos(bpos);

	m_nCnt++;
	if (m_nCnt == 45 && m_nLife < 300)
	{
		int nRand = rand() % 10 + 10;
		float nrand2 = rand() % 240 + 400.0f;
		if (nRand == 15)
		{
			CBullet::Create({ bpos.x - bsize.x / 2 ,nrand2,bpos.z }, { -10.0f,0.0f,0.0f }, 3);
		}
	}
	if (m_nCnt >= 60 && m_nLife >= 200 && m_nLife < 300)
	{
		m_nCnt = 0;

		int nrand = rand() % 4 + 1;

		float nrand2 = rand() % 240 + 400.0f;

		if (nrand == 1)
		{
			CBullet::Create({ bpos.x - bsize.x / 2,nrand2,bpos.z }, { -10.0f,0.0f,0.0f }, 1);
		}
		if (nrand == 2)
		{
			CBullet::Create({ bpos.x - bsize.x / 2 ,nrand2,bpos.z }, { -10.0f,0.0f,0.0f }, 2);
		}
		if (nrand == 3)
		{
			CBullet::Create({ bpos.x - bsize.x / 2,nrand2,bpos.z }, { -10.0f,0.0f,0.0f }, 1);
		}
		if (nrand == 4)
		{
			CBullet::Create({ bpos.x - bsize.x / 2 ,nrand2,bpos.z }, { -10.0f,0.0f,0.0f }, 2);
		}
	}
	if (m_nCnt >= 60 && m_nLife >= 100 && m_nLife < 200)
	{
		m_nCnt = 0;

		int nrand = rand() % 4 + 1;
		float nrand2 = rand() % 1000 + 0.0f;
		float nrand3 = rand() % 1000 + 0.0f;
		float nrand4 = rand() % 1000 + 0.0f;
		float nrand5 = rand() % 1000 + 0.0f;
		float nrand6 = rand() % 240 + 400.0f;
		if (nrand == 1)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
		}
		if (nrand == 2)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
		}
		if (nrand == 3)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
		}
		if (nrand == 4)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
		}
	}
	if (m_nCnt >= 60 && m_nLife >= 0 && m_nLife < 100)
	{
		m_nCnt = 0;
		int nrand = rand() % 4 + 1;
		float nrand2 = rand() % 1000 + 0.0f;
		float nrand3 = rand() % 1000 + 0.0f;
		float nrand4 = rand() % 1000 + 0.0f;
		float nrand5 = rand() % 1000 + 0.0f;
		float nrand6 = rand() % 240 + 400.0f;
		if (nrand == 1)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
			CBullet::Create({ bpos.x - bsize.x / 2 ,nrand6,bpos.z }, { -10.0f,0.0f,0.0f }, 2);
		}
		if (nrand == 2)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
			CBullet::Create({ bpos.x - bsize.x / 2,nrand6,bpos.z }, { -10.0f,0.0f,0.0f }, 1);
		}
		if (nrand == 3)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 1);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 1);
			CBullet::Create({ bpos.x - bsize.x / 2,nrand6,bpos.z }, { -10.0f,0.0f,0.0f }, 1);
		}
		if (nrand == 4)
		{
			CBullet::Create({ nrand2,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand3,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
			CBullet::Create({ nrand4,0.0f ,bpos.z }, { 0.0f,10.0f,0.0f }, 2);
			CBullet::Create({ nrand5,720.0f ,bpos.z }, { 0.0f,-10.0f,0.0f }, 2);
			CBullet::Create({ bpos.x - bsize.x / 2 ,nrand6,bpos.z }, { -10.0f,0.0f,0.0f }, 2);
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

	if (m_nLife <= 0)
	{
		CGame::GetScore()->add(5000);
		CFade::Set(CApplication::MODE_RANKING);
		Uninit();
		return;
	}
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CEnemy::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// クリエイト
//=============================================================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, int nLife)
{
	CEnemy *pEnemy = nullptr;

	//動的生成
	pEnemy = new CEnemy;

	pEnemy->Init();
	pEnemy->setpos(pos);
	pEnemy->SetType(OBJTYPE_ENEMY);
	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZEW, MAX_SIZEH, 0.0f);
	pEnemy->setsize(size);
	pEnemy->setlife(nLife);
	return pEnemy;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/bosu.png",
		&m_ptex);

	return S_OK;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CEnemy::Unload(void)
{
	//テクスチャの破棄
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
}
//=============================================================================
// クリエイト
//=============================================================================
void  CEnemy::setlife(int life)
{
	m_nLife = life;
}