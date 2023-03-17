//=============================================================================
//
// bullet.h
// Author : 
//
//=============================================================================]
#include"bullet.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
#include"enemy.h"
#include"player.h"
#include"score.h"
#include"game.h"
LPDIRECT3DTEXTURE9 CBullet::m_pTex[] = {};

CBullet::CBullet()
{
	m_move = {0.0f,0.0f,0.0f};
	m_nLife = 0;
}

CBullet::~CBullet()
{

}
//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CBullet::Init()
{
	m_nLife = 0;
	CObject2D::Init();
	m_move = { 0.0f,0.0f,0.0f };
	switch (m_nType)
	{
	case 0:
		m_pTex[m_nType];
		BindTexture(m_pTex[0]);
		break;
	case 1:
		m_pTex[m_nType];
		BindTexture(m_pTex[1]);
	case 2:
		m_pTex[m_nType];
		BindTexture(m_pTex[2]);
	case 3:
		m_pTex[m_nType];
		BindTexture(m_pTex[3]);
	default:
		break;
	}
	
	return S_OK;
}
//=============================================================================
// ポリゴンの終了
//=============================================================================
void CBullet::Uninit()
{
	CObject2D::Uninit();
}
//=============================================================================
// ポリゴンの更新
//=============================================================================
void CBullet::Update()
{
	D3DXVECTOR3 bPos = Getpos();
	D3DXVECTOR3 bSize = Getsize();
	bPos += m_move;

	setpos(bPos);
	
	if (m_nLife > 0)
	{
		m_nLife--;
	}
	
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		CObject *pObject;
		pObject = CObject::Getobject(nCnt,3);

		if (pObject != nullptr)
		{		
			if (pObject->GetObjType() == OBJTYPE_ENEMY && m_nType == 0)
			{
				D3DXVECTOR3 ePos = pObject->Getpos();
				D3DXVECTOR3 eSize = pObject->Getsize();
				int eLife = CEnemy::Getlife();
				if (bPos.x + bSize.x >= ePos.x - eSize.x
				  &&bPos.x - bSize.x <= ePos.x + eSize.x
				  &&bPos.y + bSize.y >= ePos.y - eSize.y
				  &&bPos.y - bSize.y <= ePos.y + eSize.y
					)
				{
					m_nLife = 0;
					eLife --;
					pObject->setlife(eLife);
				}
			}
			if (pObject->GetObjType() == OBJTYPE_PLAYER && m_nType == 1)
			{
				D3DXVECTOR3 pPos = pObject->Getpos();
				D3DXVECTOR3 pSize = pObject->Getsize();
				int pLife = CPlayer::Getlife();
				if (  bPos.x + bSize.x >= pPos.x - pSize.x
					&&bPos.x - bSize.x <= pPos.x + pSize.x
					&&bPos.y + bSize.y >= pPos.y - pSize.y
					&&bPos.y - bSize.y <= pPos.y + pSize.y
					)
				{
					m_nLife = 0;
  					pLife --;
					CPlayer::setStatedamage(CPlayer::DAMAGE);
					pObject->setlife(pLife);			
				}
			}
			if (pObject->GetObjType() == OBJTYPE_PLAYER && m_nType == 2 )
			{
				D3DXVECTOR3 pPos = pObject->Getpos();
				D3DXVECTOR3 pSize = pObject->Getsize();
				int pLife = CPlayer::Getlife();
				if (bPos.x + bSize.x >= pPos.x - pSize.x
					&&bPos.x - bSize.x <= pPos.x + pSize.x
					&&bPos.y + bSize.y >= pPos.y - pSize.y
					&&bPos.y - bSize.y <= pPos.y + pSize.y
					)
				{
					CGame::GetScore()->add(100);
					m_nLife = 0;
				}
			}
			if (pObject->GetObjType() == OBJTYPE_PLAYER && m_nType == 3)
			{
				D3DXVECTOR3 pPos = pObject->Getpos();
				D3DXVECTOR3 pSize = pObject->Getsize();
 				int pLife = CPlayer::Getlife();
				if (bPos.x + bSize.x >= pPos.x - pSize.x
					&&bPos.x - bSize.x <= pPos.x + pSize.x
					&&bPos.y + bSize.y >= pPos.y - pSize.y
					&&bPos.y - bSize.y <= pPos.y + pSize.y
					)
				{
					CGame::GetScore()->add(500);
 					pLife ++;
					pObject->setlife(pLife);
					m_nLife = 0;
				}
			}
		}
	}
	if (m_nLife <= 0) 
	{
		CExplosion::Create(bPos);
		Uninit();
		return;
	}
	CObject2D::Update();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBullet::Draw()
{
	CObject2D::Draw();	
}
//=============================================================================
// クリエイト
//=============================================================================
CBullet *CBullet::Create(const D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType)
{
	CBullet *pBullet = nullptr;

	//動的生成
	pBullet = new CBullet;

	pBullet->SetType(OBJTYPE_BULLET);
	pBullet->settype(nType);

	pBullet->Init();

	pBullet->m_move = move;
	pBullet->setpos(pos);

	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZEB, MAX_SIZEB, 0.0f);
	pBullet->setsize(size);

	pBullet->m_nLife = 100;
	pBullet->BindTexture(pBullet->m_pTex[nType]);
	return pBullet;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //デバイスへのポイント		

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/bullet.png",
		&m_pTex[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/kuro.png",
		&m_pTex[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/bullet1.png",
		&m_pTex[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/ha-to.png",
		&m_pTex[3]);

	return S_OK;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTex[nCnt] != NULL)
		{

			m_pTex[nCnt]->Release();
			m_pTex[nCnt] = NULL;
		}
	}
	
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBullet::settype(int type)
{
	m_nType = type;
}
