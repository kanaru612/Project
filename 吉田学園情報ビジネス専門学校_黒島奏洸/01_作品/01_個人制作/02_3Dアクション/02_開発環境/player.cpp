//============================================================================
//
// Player.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include <stdio.h>
#include"player.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"objectX.h"
#include"shadow.h"
#include"camera.h"
#include"modelparts.h"
#include"meshfield.h"
#include"game.h"
#include"strongbox.h"
#include"motionset.h"
#include"keyset.h"
#include"key.h"
#include"enemy.h"
#include"gimmick.h"
#include"plife.h"
#include"coin.h"
#include"sound.h"
#include "goal.h"
#include"fade.h"
int CPlayer::m_nLife = 0;
bool CPlayer::m_bUseWeapon = false;
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_move = { 0.0f,0.0f,0.0f };
	m_nPattern = 0;
	m_nCntAnim = 0;
	m_bJump = false;
	m_nCnt = 10;
	m_nCntD = 0;
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pModelp[nCnt] = nullptr;
		m_nFrameSpeed[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//フレームスピードの初期化
		m_RotSpeed[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//回転スピードの初期化
	}
	m_nLife = 0;
	m_nType = OBJTYPE_PLAYER;
	m_nCountModel = 0;;
	m_pCamera = nullptr;
	m_bRoll = false;
	m_Rrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RrotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotspeed = 0.12f;
	m_bAttack = false;
	m_bWalk = false;
	m_bDie = false;

	m_AttackSEFlag = false;
}
CPlayer::~CPlayer()
{ 
}

//=============================================================================
// プレイヤーの初期化
//=============================================================================
HRESULT CPlayer::Init()
{
	m_AttackSEFlag = false;						//攻撃サウンドのfalse
	//モーションをニュートラルモーションにする
	m_Motiontype = MOTIONTYPE_NEUTRALMOTION;
	//ファイル読み込み
	Load();
	//最大値を求める
	m_vtxMax = m_pModelp[0]->GetVtxMax();
	//最小値を求める
	m_vtxMin = m_pModelp[0]->GetVtxMin();
	//サイズを求める
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;
	//プレイヤーのHPバーの表示
	CPlife::Create((m_pos));
	return S_OK;
}
//=============================================================================
// プレイヤーの終了
//=============================================================================
void CPlayer::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pModelp[nCnt]->Uninit();
		delete m_pModelp[nCnt];
		m_pModelp[nCnt] = nullptr;
	}
	StopSound();
	Release();
}

//=============================================================================
// プレイヤーの更新
//=============================================================================
void CPlayer::Update()
{
	//移動処理
	Move();
	//当たり判定
	Collision(&m_pos, &m_posOld, m_size);
	//角度の正規化
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
 	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.5f;
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}
	m_posOld = m_pos;
	//プレイヤーが死んだとき
	if (m_nLife <= 0 && m_bDie == false)
	{
		CFade::Set(CApplication::MODE_RESULT);
		m_bDie = true;
	}
	//攻撃処理
	Attack();
	//モーション
	Motionanimation();
}
//=============================================================================
// プレイヤーの描画
//=============================================================================
void CPlayer::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pModelp[nCnt]->Draw();
	}
}
//=============================================================================
// プレイヤーのクリエイト
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, int nLife)
{
	CPlayer *apPlayer = nullptr;

	//動的生成
	apPlayer = new CPlayer;
	if (apPlayer != nullptr)
	{	
		apPlayer->Init();
		apPlayer->SetType(OBJTYPE_PLAYER);
		apPlayer->setpos(pos);
		apPlayer->setlife(nLife);
	}
	return apPlayer;
}
//=============================================================================
// ファイル
//=============================================================================
void CPlayer::Load()
{
	int nNumParts;							//モデルのパーツの変数
	int nCntMotionSet = 0;					//モーションセットのカウント
	int Loop = 0;							//ループをするのかの変数
	int nCntKeySet = 0;						//モーションセット数のカウント
	int nCntKey = 0;						//キーのカウント
	char aText[2000];						//文字列を格納する配列
	char FileName[MAX_PARTS][2000];			//2次元配列

	FILE *pFile; //ファイルポインタを宣言

	pFile = fopen("data/player/Playermodel.txt", "r");

	aText[0] = '\0';	//文字列なし

	if (pFile != nullptr)
	{//ファイルが開けた場合
	 //ファイルに入力したデータを書き出す処理
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//テキストの最後の行を読み込むまで繰り返す
			fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
				continue;
			}

			//ファイルネームを複数個入力する
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);        // = を読み込む
				fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0番目から読み込まれる

																	//モデルパーツの生成
				m_pModelp[m_nCountModel] = CModelparts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_nCountModel++;
			}

			if (strcmp(&aText[0], "CHARACTERSET") == 0)
			{
				while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
						continue;
					}

					if (strcmp(&aText[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = を読み込む
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "PARTSSET") == 0)
					{
						D3DXVECTOR3 pos, rot;
						int IndexParent = 0;	//親の番号
						int Ind = 0;

						while (strcmp(&aText[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
								continue;
							}

							if (strcmp(&aText[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%d", &Ind);
							}

							else if (strcmp(&aText[0], "PARENT") == 0)
							{

								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%d", &IndexParent);
							}

							else if (strcmp(&aText[0], "POS") == 0)
							{
								float x = 0.0f;
								float y = 0.0f;
								float z = 0.0f;
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%f", &x);
								fscanf(pFile, "%f", &y);
								fscanf(pFile, "%f", &z);
								pos = D3DXVECTOR3(x, y, z);
							}

							else if (strcmp(&aText[0], "ROT") == 0)
							{
								float x = 0.0f;
								float y = 0.0f;
								float z = 0.0f;
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%f", &x);
								fscanf(pFile, "%f", &y);
								fscanf(pFile, "%f", &z);
								rot = D3DXVECTOR3(x, y, z);
							}
						}

						//モデルパーツの読み込み
						m_pModelp[Ind]->SetModel(&FileName[Ind][0]);

						//モデルパーツに情報が入っていたら
						if (m_pModelp[Ind])
						{
							//モデルパーツの向きの設定
							m_pModelp[Ind]->SetRot(rot);
						}

						//親の番号が0より下だったら
						if (IndexParent < 0)
						{
							//モデルパーツのマトリックスの設定
							m_pModelp[Ind]->SetMatrix(&m_mtxWorld);
						}
						//親の番号がモデルパーツより小さかったら
						else if (IndexParent < MAX_PARTS)
						{
							//モデルパーツのマトリックスの設定
							m_pModelp[Ind]->SetMatrix(m_pModelp[IndexParent]->GetMatrix());
						}
					}
				}
			}
			if (strcmp(&aText[0], "MOTIONSET") == 0)
			{//テキストの最初の行を読み込むまで繰り返す

				m_Motionset[nCntMotionSet] = CMotionset::Create();

				m_Motionset[nCntMotionSet]->SetNumParts(nNumParts);

				while (strcmp(&aText[0], "END_MOTIONSET") != 0)
				{//テキストの最後の行を読み込むまで繰り返す
					fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

					if (strcmp(&aText[0], "NUM_KEY") == 0)
					{
						int numKey = 0;
						fscanf(pFile, "%s %d", &aText[0], &numKey);
						m_Motionset[nCntMotionSet]->SetNumKey(numKey);
					}

					if (strcmp(&aText[0], "LOOP") == 0)
					{
						fscanf(pFile, "%s %d", &aText[0], &Loop);

						if (Loop == 1)
						{

							m_Motionset[nCntMotionSet]->GetLoop();
							m_Motionset[nCntMotionSet]->SetLoop(1);
						}

						else
						{
							m_Motionset[nCntMotionSet]->GetLoop();
							m_Motionset[nCntMotionSet]->SetLoop(0);
						}
					}

					if (strcmp(&aText[0], "KEYSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strcmp(&aText[0], "#") == 0)
							{
								fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
								continue;
							}

							if (strcmp(&aText[0], "END_KEYSET") == 0)
							{
								nCntKeySet++;
								nCntKey = 0;
								break;
							}

							if (strcmp(&aText[0], "FRAME") == 0)
							{
								int nFrame = 0;
								fscanf(pFile, "%s %d", &aText[0], &nFrame);

								m_Motionset[nCntMotionSet]->GetKeySet(nCntKeySet)->SetFrame(nFrame);
							}

							else if (strcmp(&aText[0], "KEY") == 0)
							{
								while (1)
								{
									fscanf(pFile, "%s", &aText[0]);

									if (strcmp(&aText[0], "END_KEY") == 0)
									{
										nCntKey++;

										if (nCntKey >= m_Motionset[nCntMotionSet]->GetNumParts())
										{
											nCntKey = 0;
										}
										break;
									}
									else if (strcmp(&aText[0], "POS") == 0)
									{
										float px = 0.0f;
										float py = 0.0f;
										float pz = 0.0f;
										fscanf(pFile, "%s", &aText[0]);
										fscanf(pFile, "%f", &px);
										fscanf(pFile, "%f", &py);
										fscanf(pFile, "%f", &pz);
										m_Motionset[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetPos(D3DXVECTOR3(px, py, pz));
									}

									else if (strcmp(&aText[0], "ROT") == 0)
									{
										float rx = 0.0f;
										float ry = 0.0f;
										float rz = 0.0f;
										fscanf(pFile, "%s", &aText[0]);
										fscanf(pFile, "%f", &rx);
										fscanf(pFile, "%f", &ry);
										fscanf(pFile, "%f", &rz);
										m_Motionset[nCntMotionSet]->GetKeySet(nCntKeySet)->GetKey(nCntKey)->SetRot(D3DXVECTOR3(rx, ry, rz));
									}
								}
							}
						}
					}
				}

				//モーションセットをインクリメント
				nCntMotionSet++;
				//モーションセット数の初期化
				nCntKeySet = 0;
				//キーカウントの初期化
				nCntKey = 0;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//nullチェック
		if (m_pModelp[nCnt] != nullptr)
		{
			//posとrotの変数宣言
			D3DXVECTOR3 pos, rot;

			//現在使われているモーションの位置情報をposに代入
			pos = m_Motionset[m_Motiontype]->GetKeySet(1)->GetKey(nCnt)->GetPos();

			//現在使われているモーションの向き情報をrotに代入
			rot = m_Motionset[m_Motiontype]->GetKeySet(1)->GetKey(nCnt)->GetRot();

			//モデルの位置と向きの設定
			m_pModelp[nCnt]->SetPos(pos);
			m_pModelp[nCnt]->SetRot(rot);
		}
	}
}

//=============================================================================
// 移動
//=============================================================================
void CPlayer::Move()
{

	CInput *pInput = CApplication::GetKeyboard();
	D3DXVECTOR3 pPos = Getpos();
	D3DXVECTOR3 pSize = Getsize();
	D3DXVECTOR3 crot = CCamera::Getrot();

	//移動量の更新
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	
	//宝箱
	if (CGame::GetSBox()->OnCollision() == true)
	{
		m_bJump = false;
		CGame::GetSBox()->SetOnCollision(false);
	}
	//土
	for (int nCnt = 0; nCnt < 75; nCnt++)
	{
		if (CGame::GetModel()[nCnt]->OnCollision() == true)
		{
			m_bJump = false;
			CGame::GetModel()[nCnt]->SetOnCollision(false);
		}
	}
	m_pos += m_move;
	//重力
	m_move.y -= 0.5f;
	if (m_pos.y < 1.0f)
	{
		m_pos.y = 1.0f;
		m_move.y = 0.0f;
		m_bJump = false;
	}
	if (m_Motiontype != MOTIONTYPE_ATTACK)
	{

		// Sキーが押された
		if (pInput->GetPress(DIK_S) == true)
		{
			if (pInput->GetPress(DIK_D) == true)
			{
				m_move.x += sinf(crot.y + D3DX_PI * 0.75f) * 0.1f;
				m_move.z += cosf(crot.y + D3DX_PI * 0.75f) * 0.1f;
				m_rotDest.y = (crot.y - D3DX_PI * 0.25f);

			}
			else if (pInput->GetPress(DIK_A) == true)
			{
				m_move.x -= sinf(crot.y + D3DX_PI * 0.25f) * 0.1f;
				m_move.z -= cosf(crot.y + D3DX_PI * 0.25f) * 0.1f;
				m_rotDest.y = (crot.y + D3DX_PI * 0.25f);

			}
			else
			{
				m_move.x -= sinf(crot.y) * 0.1f;
				m_move.z -= cosf(crot.y) * 0.1f;
				m_rotDest.y = (crot.y);

			}
			if (m_bWalk == false)
			{
				//移動モーションの設定
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		// Wキーが押された
		else if (pInput->GetPress(DIK_W) == true)
		{
			if (pInput->GetPress(DIK_D) == true)
			{
				m_move.x += sinf(crot.y + D3DX_PI * 0.25f) * 0.1f;
				m_move.z += cosf(crot.y + D3DX_PI * 0.25f) * 0.1f;
				m_rotDest.y = (crot.y - D3DX_PI * 0.75f);

			}
			else if (pInput->GetPress(DIK_A) == true)
			{
				m_move.x -= sinf(crot.y + D3DX_PI * 0.75f) * 0.1f;
				m_move.z -= cosf(crot.y + D3DX_PI * 0.75f) * 0.1f;
				m_rotDest.y = (crot.y + D3DX_PI * 0.75f);
			}
			else
			{
				m_move.x += sinf(crot.y) * 0.1f;
				m_move.z += cosf(crot.y) * 0.1f;
				m_rotDest.y = (crot.y + D3DX_PI);
			}
			if (m_bWalk == false)
			{
				//移動モーションの設定
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		// Dキーが押された
		else if (pInput->GetPress(DIK_D) == true)
		{
			m_move.x += sinf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_move.z += cosf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_rotDest.y = (crot.y - D3DX_PI / 2.0f);
			if (m_bWalk == false)
			{
				//移動モーションの設定
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		//// Aキーが押された
		else if (pInput->GetPress(DIK_A) == true)
		{
			m_move.x -= sinf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_move.z -= cosf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_rotDest.y = (crot.y + D3DX_PI / 2.0f);
			if (m_bWalk == false)
			{
				//移動モーションの設定
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		//移動モーションの設定
		if (pInput->GetPress(DIK_W) == false
			&& pInput->GetPress(DIK_A) == false
			&& pInput->GetPress(DIK_S) == false
			&& pInput->GetPress(DIK_D) == false
			&& m_Motiontype != MOTIONTYPE_NEUTRALMOTION
			
			)
		{
			SetMotionType(MOTIONTYPE_NEUTRALMOTION);
			m_bWalk = false;
		}
		
		//ジャンプ
		if (m_bJump == false)
		{
			if (pInput->GetTrriger(DIK_SPACE) == true)
			{
				m_move.y += 10.0f;
				m_bJump = true;
			}
		}
		if (m_pos.x - m_size.x * 2 <= -135.0f)
		{
			m_pos.x = -135.0f + m_size.x * 2;
		}
		if (m_pos.x + m_size.x * 2 >= 385.0f)
		{
			m_pos.x = 385.0f - m_size.x * 2;
		}
		if (m_pos.z - m_size.z * 2<= -365.0f)
		{
			m_pos.z = -365.0f + m_size.x * 2;
		}
		if (m_pos.z + m_size.x * 2>= 135.0f)
		{
			m_pos.z= 135.0f - m_size.x * 2;
		}
		//回転
		if (pInput->GetTrriger(DIK_LSHIFT) == true)
		{
			m_bRoll = true;
		}
		if (m_bRoll == true)
		{
			//下
			if (m_rotDest.y == 0.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.z += -0.3f / 2.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//上
			else if (m_rotDest.y == D3DX_PI)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, D3DX_PI ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.z += 0.3f / 2.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//左
			else if (m_rotDest.y == D3DX_PI / 2.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, D3DX_PI / 2.0f ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.x += -0.3f / 2.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//右
			else if (m_rotDest.y == -D3DX_PI / 2.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, -D3DX_PI / 2.0f ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.x += 0.3f / 2.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//右下
			else if (m_rotDest.y == -D3DX_PI / 4.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, -D3DX_PI / 4.0f ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.x += sqrt(0.3f) / 4.0f;
				m_move.z -= sqrt(0.3f) / 4.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//左下
			else if (m_rotDest.y == D3DX_PI / 4.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, D3DX_PI / 4.0f ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.x -= sqrt(0.3f) / 4.0f;
				m_move.z -= sqrt(0.3f) / 4.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//左上
			else if (m_rotDest.y == -D3DX_PI * 3.0f / 4.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, -D3DX_PI * 3.0f / 4.0f ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.x += sqrt(0.3f) / 4.0f;
				m_move.z += sqrt(0.3f) / 4.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
			//右下
			else if (m_rotDest.y == D3DX_PI * 3.0f / 4.0f)
			{
				m_Rrot.x -= D3DX_PI * m_rotspeed;
				setrot({ m_Rrot.x, D3DX_PI *3.0f / 4.0f ,0.0f });
				m_RrotDest.x = -D3DX_PI * 2.0f;
				m_move.x -= sqrt(0.3f) / 4.0f;
				m_move.z += sqrt(0.3f) / 4.0f;
				if (m_Rrot.x <= m_RrotDest.x)
				{
					m_Rrot.x = 0.0f;
					m_RrotDest.x = 0.0f;
					m_bRoll = false;
				}
			}
		}
	}

}
//-------------------------------------------------------------------------
//攻撃処理
//-------------------------------------------------------------------------
void CPlayer::attack()
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (CGame::GetEnemy()[nCnt] != nullptr)
		{
			D3DXVECTOR3 ePos = CGame::GetEnemy()[nCnt]->Getpos();

			if (ePos.x <= m_pos.x + m_size.x + 30.0f
				&& ePos.x >= m_pos.x - m_size.x - 30.0
				&& ePos.y <= m_pos.y + m_size.y
				&& ePos.y >= m_pos.y - m_size.y
				&& ePos.z <= m_pos.z + m_size.z + 30.0f
				&& ePos.z >= m_pos.z - m_size.z - 30.0f)
			{//この範囲内に入ったらダメージを与える
				m_nLifeE++;
				if (m_nLifeE >= 2)
				{
					m_nLifeE = 0;
					CGame::GetScore()->add(500);
					CGame::GetEnemy()[nCnt]->Uninit();
					CGame::GetEnemy()[nCnt] = nullptr;
				}
			}
		}
	}
}
void CPlayer::Attack()
{
	CInput *pInput = CApplication::GetKeyboard();
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (CGame::GetGimmick()[nCnt] != nullptr)
		{
			D3DXVECTOR3 Gpos = CGame::GetGimmick()[nCnt]->Getpos(); 
			D3DXVECTOR3 Gsize = CGame::GetGimmick()[nCnt]->Getsize();
			if (pInput->GetTrriger(DIK_RETURN) == true && m_Motiontype != MOTIONTYPE_ATTACK)
			{
				//エンターキーが押されてモーションがアタックもーションじゃないとき
				SetMotionType(MOTIONTYPE_ATTACK);
				if (m_AttackSEFlag == false)
				{
					PlaySound(SOUND_LABEL_SE_ATTACK);
					attack();
					m_AttackSEFlag = true;
				}
				
			}
			if (
				pInput->GetTrriger(DIK_RETURN) == true
				&&Gpos.x + Gsize.x >= m_pos.x - m_size.x
				&& Gpos.x - Gsize.x <= m_pos.x + m_size.x
				&& Gpos.z + Gsize.z >= m_pos.z - m_size.z
				&& Gpos.z - Gsize.z <= m_pos.z + m_size.z)
				{//この範囲内で攻撃したらギミックにダメージを与える
					m_nLifeG++;
					if (m_nLifeG >= 3)
					{
						m_nLifeG = 0;
						CGame::GetScore()->add(1000);
						CGame::GetGimmick()[nCnt]->Uninit();
						CGame::GetGimmick()[nCnt] = nullptr;
					}
				
				}
			if (!(pInput->GetTrriger(DIK_RETURN) == true))
			{
				m_AttackSEFlag = false;
			}
		}
	}
}
//-------------------------------------------------------------------------
//モデルとプレイヤーの当たり判定
//-------------------------------------------------------------------------
void CPlayer::Collision(D3DXVECTOR3 *pPos,			//現在の位置
	D3DXVECTOR3 *pPosOld,						//前回の位置
	D3DXVECTOR3 size)							//サイズ
{

	//宝箱
	CStrongbox *pSbox = CGame::GetSBox();
	if (pSbox != nullptr)
	{
		pSbox->Collision(pPos,
			pPosOld,
			size
		);
	}
	//ゴール
	CGoal *pGoal = CGame::GetGoal();
	if (pGoal != nullptr)
	{
		pGoal->Collision(pPos,
			pPosOld,
			size
		);
	}

	//土
	for (int nCnt = 0; nCnt < MAX_MODELFLOOR; nCnt++)
	{
		if (CGame::GetModel()[nCnt] != nullptr)
		{
			CGame::GetModel()[nCnt]->Collision(pPos,
				pPosOld,
				size
			);
		}
	}
	//敵との当たり判定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		
		if (CGame::GetEnemy()[nCnt] != nullptr)
		{
			CGame::GetEnemy()[nCnt]->Collision(pPos,
				pPosOld,
				size
			);
		}
	}
	//ギミックの当たり判定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (CGame::GetGimmick()[nCnt] != nullptr)
		{
			CGame::GetGimmick()[nCnt]->Collision(pPos,
				pPosOld,
				size
			);
		}
	}
	//コインの当たり判定
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		
		CCoin *pCoin = CGame::GetCoin(nCnt);
		if (pCoin != nullptr)
		{
			pCoin->Collision(pPos,
				pPosOld,
				size
			);
		}
	}
}
//-------------------------------------------------------------------------
//モーションアニメーション
//-------------------------------------------------------------------------
void CPlayer::Motionanimation(void)
{
	m_nFrame++;		//フレームのインクリメント
	
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		D3DXVECTOR3 pos = m_pModelp[nCnt]->GetPos();		
		D3DXVECTOR3 rot = m_pModelp[nCnt]->GetRot();		
		pos += m_nFrameSpeed[nCnt];							
		rot += m_RotSpeed[nCnt];							
		m_pModelp[nCnt]->SetPos(pos);						
		m_pModelp[nCnt]->SetRot(rot);						
	}

	if (m_nFrame >= m_Motionset[m_Motiontype]->GetKeySet(m_PresentKeyset)->GetFrame())
	{	//現在のアニメーションのフレーム数以上だったら

		int NextKeySet = 0;					//次のキーセット変数
		NextKeySet = m_PresentKeyset + 1;	//次のキーセットを代入

		if (NextKeySet >= m_Motionset[m_Motiontype]->GetNumKey() && m_Motionset[m_Motiontype]->GetLoop() == 1)
		{	//再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している

			NextKeySet = 0;					//再生中のキー数カウントを初期化
			m_PresentKeyset = NextKeySet;	//次のアニメーションの最初のモーションセットを設定する
		}
		else if (NextKeySet >= m_Motionset[m_Motiontype]->GetNumKey() && m_Motionset[m_Motiontype]->GetLoop() == 0)
		{	//再生中のキー数カウントがキー数の最大値を超えたとき

			m_Motionset[m_Motiontype]->SetLoop(false);		//ループをfalseに設定する	
			m_Motiontype = MOTIONTYPE_NEUTRALMOTION;		//モーションをニュートラルモーションにする
			NextKeySet = 0;									//次のキーセットの初期化
		}

		for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
		{
			//速度の計算
			m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_pModelp[nCnt]->GetPos());
			m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			//回転の計算
			m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_pModelp[nCnt]->GetRot());
			m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
		}

		m_nFrame = 0;						//フレームの初期化
		m_PresentKeyset = NextKeySet;		//現在のモーションに次のモーションを代入
	}
	
}

//-------------------------------------------------------------------------
//モーションの種類の設定
//-------------------------------------------------------------------------
void CPlayer::SetMotionType(MOTIONTYPE type)
{
	m_Motiontype = type;

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//速度の計算
		m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetPos() - m_pModelp[nCnt]->GetPos());
		m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		//回転の計算
		m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetRot() - m_pModelp[nCnt]->GetRot());
		m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
	}
}