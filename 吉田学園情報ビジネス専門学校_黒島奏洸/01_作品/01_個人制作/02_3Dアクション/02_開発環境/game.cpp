//============================================================================
//
// Game.cpp
// Author : •“‡@‘tŸ©
//
//-------------------------------------------------------------------------
#include"game.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"player.h"
#include"meshfield.h"
#include"light.h"
#include"score.h"
#include"object.h"
#include"title.h"
#include"result.h"
#include"fade.h"
#include"enemy.h"
#include"camera.h"
#include"strongbox.h"
#include"soil.h"
#include"goal.h"
#include"gimmick.h"
#include"plife.h"
#include"coin.h"
#include"sound.h"
LPDIRECT3DTEXTURE9 CGame::m_ptex = {};
CScore * CGame::m_nScor = {};
CMeshfield *CGame::m_pMeshfield = {};
CPlayer *CGame::m_pPlayer = {};
CEnemy *CGame::m_pEnemy[MAX_ENEMY] = {};
CStrongbox *CGame::m_pSbox = {};
CWeapon *CGame::m_pWeapon = {};
CCoin *CGame::m_pCoin[MAX_COIN] = {};
CModel *CGame::m_pModel[MAX_MODELFLOOR] = {};
CGimmick *CGame::m_pGimmick[MAX_GIMMICK]= {};

CGoal *CGame::m_pGoal = nullptr;

CGame::CGame() 
{
	bSound = false;
}
CGame::~CGame()
{

}
//-------------------------------------------------------------------------
// ƒQ[ƒ€‚Ì‰Šú‰»
//-------------------------------------------------------------------------
HRESULT CGame::Init()
{
	CNumber::Load();	
	CMeshfield::Load();
	m_pMeshfield = CMeshfield::Create();

	m_pSbox = CStrongbox::Create(D3DXVECTOR3(125.0f, 0.0f, 75.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	m_pGoal = CGoal::Create(D3DXVECTOR3(125.0f, 30.0f, 105.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	m_pModel[0] = CSoil::Create(D3DXVECTOR3(125.0f, 0.0f, 105.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//‰E‚Ì•Ç
	m_pModel[1] = CSoil::Create(D3DXVECTOR3(125.0f, 0.0f, -125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[2] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, 105.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[3] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, 75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[4] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, 45.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[5] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[6] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[7] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -45.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[8] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[9] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -105.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[10] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[11] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -165.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[12] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -195.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[13] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[14] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -245.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[15] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[16] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -305.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[17] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -335.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[18] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//¶‚Ì•Ç
	m_pModel[19] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[20] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, 105.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[21] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, 75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[22] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, 45.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[23] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[24] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[25] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -45.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[26] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[27] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -105.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[28] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[29] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -165.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[30] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -195.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[31] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[32] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -245.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[33] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[34] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -305.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[35] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -335.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[36] = CSoil::Create(D3DXVECTOR3(-135.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//‰º‚Ì
	m_pModel[37] = CSoil::Create(D3DXVECTOR3(-105.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[38] = CSoil::Create(D3DXVECTOR3(-75.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[39] = CSoil::Create(D3DXVECTOR3(-45.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[40] = CSoil::Create(D3DXVECTOR3(-15.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[41] = CSoil::Create(D3DXVECTOR3(15.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[42] = CSoil::Create(D3DXVECTOR3(45.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[43] = CSoil::Create(D3DXVECTOR3(75.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[44] = CSoil::Create(D3DXVECTOR3(105.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[45] = CSoil::Create(D3DXVECTOR3(135.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[46] = CSoil::Create(D3DXVECTOR3(165.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[47] = CSoil::Create(D3DXVECTOR3(195.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[48] = CSoil::Create(D3DXVECTOR3(225.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[49] = CSoil::Create(D3DXVECTOR3(255.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[50] = CSoil::Create(D3DXVECTOR3(285.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[51] = CSoil::Create(D3DXVECTOR3(315.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[52] = CSoil::Create(D3DXVECTOR3(345.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[53] = CSoil::Create(D3DXVECTOR3(375.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[54] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, -365.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ã‚Ì
	m_pModel[55] = CSoil::Create(D3DXVECTOR3(-105.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[56] = CSoil::Create(D3DXVECTOR3(-75.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[57] = CSoil::Create(D3DXVECTOR3(-45.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[58] = CSoil::Create(D3DXVECTOR3(-15.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[59] = CSoil::Create(D3DXVECTOR3(15.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[60] = CSoil::Create(D3DXVECTOR3(45.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[61] = CSoil::Create(D3DXVECTOR3(75.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[62] = CSoil::Create(D3DXVECTOR3(105.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[63] = CSoil::Create(D3DXVECTOR3(135.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[64] = CSoil::Create(D3DXVECTOR3(165.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[65] = CSoil::Create(D3DXVECTOR3(195.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[66] = CSoil::Create(D3DXVECTOR3(225.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[67] = CSoil::Create(D3DXVECTOR3(255.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[68] = CSoil::Create(D3DXVECTOR3(285.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[69] = CSoil::Create(D3DXVECTOR3(315.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[70] = CSoil::Create(D3DXVECTOR3(345.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[71] = CSoil::Create(D3DXVECTOR3(375.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[72] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[73] = CSoil::Create(D3DXVECTOR3(385.0f, 0.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pModel[74] = CSoil::Create(D3DXVECTOR3(125.0f, 0.0f, -125.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CLight::Create();
	m_nScor = CScore::Create(D3DXVECTOR3(1400.0f,690.0f,0.0f ));
 	m_pPlayer = CPlayer::Create(D3DXVECTOR3(125.0f, 40.0f, -125.0f), 5);

	m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(105.0f, 0.0f, 10.0f), 1);
	m_pEnemy[1] = CEnemy::Create(D3DXVECTOR3(55.0f, 0.0f, 10.0f), 1);
	m_pEnemy[2] = CEnemy::Create(D3DXVECTOR3(105.0f, 0.0f, 60.0f), 1);
	m_pEnemy[3] = CEnemy::Create(D3DXVECTOR3(105.0f, 0.0f, 100.0f), 1);

	m_pGimmick[0] = CGimmick::Create(D3DXVECTOR3(255.0f, 0.0f, -240.0f));
	m_pGimmick[1] = CGimmick::Create(D3DXVECTOR3(255.0f, 0.0f, 10.0f));
	m_pGimmick[2] = CGimmick::Create(D3DXVECTOR3( -5.0f, 0.0f, -240.0f));
	m_pGimmick[3] = CGimmick::Create(D3DXVECTOR3( -5.0f, 0.0f, 10.0f));
	m_pCoin[0]  = CCoin::Create(D3DXVECTOR3( 105.0f, 0.0f,   20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[1]  = CCoin::Create(D3DXVECTOR3( 145.0f, 0.0f,   20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[2]  = CCoin::Create(D3DXVECTOR3( 125.0f, 0.0f,    0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[3]  = CCoin::Create(D3DXVECTOR3( 125.0f, 0.0f,   40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[4]  = CCoin::Create(D3DXVECTOR3( 235.0f, 0.0f, -115.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[5]  = CCoin::Create(D3DXVECTOR3( 255.0f, 0.0f,  -95.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[6]  = CCoin::Create(D3DXVECTOR3( 255.0f, 0.0f, -135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[7]  = CCoin::Create(D3DXVECTOR3( 275.0f, 0.0f, -115.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[8]  = CCoin::Create(D3DXVECTOR3( 105.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[9]  = CCoin::Create(D3DXVECTOR3( 145.0f, 0.0f, -240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[10] = CCoin::Create(D3DXVECTOR3( 125.0f, 0.0f, -220.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[11] = CCoin::Create(D3DXVECTOR3( 125.0f, 0.0f, -260.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[12] = CCoin::Create(D3DXVECTOR3( -10.0f, 0.0f, -115.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[13] = CCoin::Create(D3DXVECTOR3(  10.0f, 0.0f,  -95.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[14] = CCoin::Create(D3DXVECTOR3(  10.0f, 0.0f, -135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCoin[15] = CCoin::Create(D3DXVECTOR3(  30.0f, 0.0f, -115.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CPlife::Create();
	return S_OK;
}
//============================================================================
// ƒQ[ƒ€‚ÌI—¹
//-------------------------------------------------------------------------
void CGame::Uninit()
{
	StopSound();
	CNumber::Unload();
	CMeshfield::Unload();
}

//-------------------------------------------------------------------------
// ƒQ[ƒ€‚ÌXV
//-------------------------------------------------------------------------
void CGame::Update()
{
	if (bSound == false)
	{
		PlaySound(SOUND_LABEL_BGM001);
		bSound = true;
	}
	if (m_pCoin[16] == nullptr)
	{
		bool flag = m_pSbox->GetCoinCreateFlag();
		if (flag == true)
		{
			m_pCoin[16] = CCoin::Create(D3DXVECTOR3(125.0f, 0.0f, 75.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
			flag = false;
			m_pSbox->SetCoinCreateFlag(flag);
		}
	}
}
//-------------------------------------------------------------------------
// ƒQ[ƒ€‚Ì¶¬
//-------------------------------------------------------------------------
CGame *CGame::Create()
{
	CGame *pgame = nullptr;

	//“®“I¶¬
	pgame = new CGame;

	pgame->Init();

	return pgame;
}