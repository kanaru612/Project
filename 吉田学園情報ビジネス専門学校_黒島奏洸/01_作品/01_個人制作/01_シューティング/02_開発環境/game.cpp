//=============================================================================
//
// game.cpp
// Author : 
//
//=============================================================================]
#include"game.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"player.h"
#include"bullet.h"
#include"enemy.h"
#include"explosion.h"
#include"block.h"
#include"tail.h"
#include"bg.h"
#include"score.h"
#include"number.h"
#include"object.h"
#include"title.h"
#include"result.h"
#include"boss.h"
#include"fade.h"
#include"sound.h"
#include"life.h"
#include"plife.h"
LPDIRECT3DTEXTURE9 CGame::m_ptex = {};
CScore * CGame::m_nScor = {};
CGame::CGame()
{
}
CGame::~CGame()
{

}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CGame::Init()
{
	PlaySound(SOUND_LABEL_BGM000);
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CBlock::Load();
	CTail::Load();
	CPlayer::Load();
	CBg::Load();
	CNumber::Load();
	CBoss::Load();

	CBg::Create({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f });
	
	
	CBlock::Create({ 640.0f,690.0f,0.0f }, 20, 1);

	CBlock::Create({ 250.0f,500.0f,0.0f }, 2, 1);

	CBlock::Create({ 550.0f,500.0f,0.0f }, 2, 1);
	
	CBlock::Create({ 850.0f,500.0f,0.0f }, 2, 1);

	CEnemy::Create({ 1100,360,0.0f }, 300);

	CBoss::Create({ 640.0f,75.0f,0.0f });

	CLife::Create();
	CPlife::Create();

	m_nScor = CScore::Create({ 1400.0f,690.0f,0.0f });

	CPlayer::Create(3);
	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CGame::Uninit()
{
	StopSound();
	//CScore::SaveScore();
	CBullet::Unload();
	CPlayer::Unload();
	CEnemy::Unload();
	CTail::Unload();
	CExplosion::Unload();
	CBlock::Unload();
	CBg::Unload();
	CBoss::Unload();
	CNumber::Unload();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CGame::Update()
{
}
//=============================================================================
// クリエイト
//=============================================================================
CGame *CGame::Create()
{
	CGame *pgame = nullptr;

	//動的生成
	pgame = new CGame;

	pgame->Init();

	return pgame;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
HRESULT CGame::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

																			//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/renga.png",
		&m_ptex);

	return S_OK;

}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CGame::Unload(void)
{
	//テクスチャの破棄
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
}