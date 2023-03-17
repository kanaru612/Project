//=============================================================================
//
// Enemy.cpp
// Author : 黒島　奏洸
//
//=============================================================================
#include <stdio.h>
#include"enemy.h"
#include"Input.h"
#include"application.h"
#include"rendere.h"
#include"score.h"
#include"game.h"
#include"fade.h"
#include"player.h"
#include"motionset.h"
#include"key.h"
#include"keyset.h"
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_move = { 0.0f,0.0f,0.0f };
	m_nCnt = 0;
	m_nLife = 0;
	m_pScore = {};
	m_bUse = false;
	m_bAttack = false;
}
CEnemy::~CEnemy()
{
}
//-------------------------------------------------------------------------
//敵の初期化
//-------------------------------------------------------------------------
HRESULT CEnemy::Init()
{
	//ファイル読み込み
	Load();
	//最大値
	m_vtxMax = m_pModele[0]->GetVtxMax();
	//最小値
	m_vtxMin = m_pModele[0]->GetVtxMin();
	//サイズ
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;
	//モーションをニュートラルへ
	SetMotionType(CPlayer::MOTIONTYPE_NEUTRALMOTION);
	m_move = { 0.0f,0.0f,0.0f };
	return S_OK;
}
//-------------------------------------------------------------------------
// 敵の終了
//-------------------------------------------------------------------------
void CEnemy::Uninit()
{
	Release();
}

//-------------------------------------------------------------------------
// 敵の更新
//-------------------------------------------------------------------------
void CEnemy::Update()
{	
	Move();
	Motionanimation();
}
//-------------------------------------------------------------------------
// 敵の描画
//-------------------------------------------------------------------------
void CEnemy::Draw()
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
	if (m_bUse == true)
	{
		for (int nCnt = 0; nCnt < MAX_PARTS_E; nCnt++)
		{
			m_pModele[nCnt]->Draw();
		}
	}
}
//-------------------------------------------------------------------------
// クリエイト
//-------------------------------------------------------------------------
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, int nLife)
{
	CEnemy *pEnemy = nullptr;

	//動的生成
	pEnemy = new CEnemy;
	if (pEnemy != nullptr)
	{
		pEnemy->Init();
		pEnemy->setpos(pos);
		pEnemy->SetType(OBJTYPE_ENEMY);
		pEnemy->setlife(nLife);
		pEnemy->m_bUse = true;
	}
	return pEnemy;
}
//-------------------------------------------------------------------------
// ファイル
//-------------------------------------------------------------------------
void CEnemy::Load()
{
	int nNumParts;							//モデルのパーツの変数
	int nCntMotionSet = 0;					//モーションセットのカウント
	int Loop = 0;							//ループをするのかの変数
	int nCntKeySet = 0;						//モーションセット数のカウント
	int nCntKey = 0;						//キーのカウント
	char aText[2000];						//文字列を格納する配列
	char FileName[MAX_PARTS_E][2000];			//2次元配列

	FILE *pFile; //ファイルポインタを宣言

	pFile = fopen("data/Enemy/Enemymodel.txt", "r");

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
				m_pModele[m_nCountModel] = CModelparts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
						m_pModele[Ind]->SetModel(&FileName[Ind][0]);

						//モデルパーツに情報が入っていたら
						if (m_pModele[Ind])
						{
							//モデルパーツの向きの設定
							m_pModele[Ind]->SetRot(rot);
						}

						//親の番号が0より下だったら
						if (IndexParent < 0)
						{
							//モデルパーツのマトリックスの設定
							m_pModele[Ind]->SetMatrix(&m_mtxWorld);
						}
						//親の番号がモデルパーツより小さかったら
						else if (IndexParent < MAX_PARTS_E)
						{
							//モデルパーツのマトリックスの設定
							m_pModele[Ind]->SetMatrix(m_pModele[IndexParent]->GetMatrix());
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

	for (int nCnt = 0; nCnt < MAX_PARTS_E; nCnt++)
	{
		//nullチェック
		if (m_pModele[nCnt] != nullptr)
		{
			//posとrotの変数宣言
			D3DXVECTOR3 pos, rot;

			//現在使われているモーションの位置情報をposに代入
			pos = m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetPos();

			//現在使われているモーションの向き情報をrotに代入
			rot = m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetRot();

			//モデルの位置と向きの設定
			m_pModele[nCnt]->SetPos(pos);
			m_pModele[nCnt]->SetRot(rot);
		}
	}
}
//-------------------------------------------------------------------------
// モーション
//-------------------------------------------------------------------------
void CEnemy::Motionanimation(void)
{
	m_nFrame++;		//フレームのインクリメント

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		D3DXVECTOR3 pos = m_pModele[nCnt]->GetPos();		
		D3DXVECTOR3 rot = m_pModele[nCnt]->GetRot();		
		pos += m_nFrameSpeed[nCnt];							
		rot += m_RotSpeed[nCnt];							
		m_pModele[nCnt]->SetPos(pos);						
		m_pModele[nCnt]->SetRot(rot);						
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
			m_Motiontype = CPlayer::MOTIONTYPE_NEUTRALMOTION;		//モーションをニュートラルモーションにする
			NextKeySet = 0;									//次のキーセットの初期化
		}

		for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
		{
			//速度の計算
			m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_pModele[nCnt]->GetPos());
			m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			//回転の計算
			m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_pModele[nCnt]->GetRot());
			m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
		}

		m_nFrame = 0;						//フレームの初期化
		m_PresentKeyset = NextKeySet;		//現在のモーションに次のモーションを代入
	}
}
//-------------------------------------------------------------------------
// モーションの種類
//-------------------------------------------------------------------------
void CEnemy::SetMotionType(CPlayer::MOTIONTYPE type)
{
	m_Motiontype = type;

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//速度の計算
		m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetPos() - m_pModele[nCnt]->GetPos());
		m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		//回転の計算
		m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetRot() - m_pModele[nCnt]->GetRot());
		m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
	}
}
//-------------------------------------------------------------------------
//敵とプレイヤーの当たり判定
//-------------------------------------------------------------------------
void CEnemy::Collision(D3DXVECTOR3 *pPos,				//現在の位置
	D3DXVECTOR3 *pPosOld,								//前回の位置
	D3DXVECTOR3 size)									//サイズ
{
	CInput *pInput = CApplication::GetKeyboard();
	if (m_bUse == true)
	{
		if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
			&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x)
		{
			//奥の当たり判定
			if (
				pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
				&& pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f
				)
			{
				pPos->z = m_pos.z + m_vtxMax.z + size.z / 2.0f;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//手前の当たり判定 
			if (
				pPosOld->z <= m_pos.z + m_vtxMin.z - size.z / 2.0f
				&& pPos->z > m_pos.z + m_vtxMin.z - size.z / 2.0f

				)
			{
				pPos->z = m_pos.z + m_vtxMin.z - size.z / 2.0f;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		if (pPos->z - size.z / 2.0f < m_pos.z + m_vtxMax.z
			&& pPos->z + size.z / 2.0f > m_pos.z + m_vtxMin.z)
		{

			//左の当たり判定
			if (
				pPosOld->x <= m_pos.x + m_vtxMin.x - size.x / 2
				&& pPos->x > m_pos.x + m_vtxMin.x - size.x / 2
				)
			{
				pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//右の当たり判定
			if (
				pPosOld->x >= m_pos.x + m_vtxMax.x + size.x / 2
				&& pPos->x < m_pos.x + m_vtxMax.x + size.x / 2
				)
			{
				pPos->x = m_pos.x + m_vtxMax.x + size.x / 2;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		if (pPos->x - size.x / 2.0f < m_pos.x + m_vtxMax.x
			&& pPos->x + size.x / 2.0f > m_pos.x + m_vtxMin.x
			&&pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
			&&pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f)
		{
			//上の当たり判定
			if (pPosOld->y >= m_pos.y + m_vtxMax.y
				&& pPos->y < m_pos.y + m_vtxMax.y)
			{
				pPos->y = m_pos.y + m_vtxMax.y;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//下の当たり判定
			if (pPosOld->y + size.y <= m_pos.y + m_vtxMin.y
				&& pPos->y + size.y > m_pos.y + m_vtxMin.y)
			{
				pPos->y = m_pos.y + m_vtxMin.y - size.y;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
}

//-------------------------------------------------------------------------
// 追従と攻撃処理
//-------------------------------------------------------------------------
void CEnemy::Move()
{
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->Getpos();
	int nLife = pPlayer->Getlife();
	//追従
	m_move.x = m_pos.x - pos.x;
	m_move.z = m_pos.z - pos.z;
	//正規化
	D3DXVec3Normalize(&m_move, &m_move);
	//慣性
	m_move *= 0.5;
	m_pos += (-m_move) * 1.0f;
	//追従の向き
	float rotDestx = m_pos.x - pos.x;
	float rotDestz = m_pos.z - pos.z;

	float rotDest = atan2f(rotDestx, rotDestz);

	//目的の向きの設定
	m_rotDest = D3DXVECTOR3(0.0f, rotDest, 0.0f);

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
	//攻撃
	if (pos.x <= m_pos.x + m_size.x + 3.0f
		&& pos.x >= m_pos.x - m_size.x - 3.0f
		&& pos.y <= m_pos.y + m_size.y + 3.0f
		&& pos.y >= m_pos.y - m_size.y - 3.0f
		&& pos.z <= m_pos.z + m_size.z + 3.0f
		&& pos.z >= m_pos.z - m_size.z - 3.0f)
	{
		m_nCnt++;
		if (m_bAttack == false && m_Motiontype != CPlayer::MOTIONTYPE_MOVE)
		{
			SetMotionType(CPlayer::MOTIONTYPE_MOVE);
			m_bAttack = true;
		}
		if (m_nCnt >= 120)
		{
			nLife--;
			pPlayer->setlife(nLife);
			m_nCnt = 0;
		}
	
	}
	if (!(pos.x <= m_pos.x + m_size.x + 3.0f)
		&& !(pos.x >= m_pos.x - m_size.x - 3.0f)
		&& !(pos.y <= m_pos.y + m_size.y + 3.0f)
		&& !(pos.y >= m_pos.y - m_size.y - 3.0f)
		&& !(pos.z <= m_pos.z + m_size.z + 3.0f)
		&& !(pos.z >= m_pos.z - m_size.z - 3.0f)
		&& !(m_Motiontype != CPlayer::MOTIONTYPE_MOVE))
	{
		SetMotionType(CPlayer::MOTIONTYPE_NEUTRALMOTION);
		m_bAttack = false;
	}
}