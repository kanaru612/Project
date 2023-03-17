//============================================================================
//
// Player.cpp
// Author : �����@�t��
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
		m_nFrameSpeed[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�t���[���X�s�[�h�̏�����
		m_RotSpeed[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//��]�X�s�[�h�̏�����
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
// �v���C���[�̏�����
//=============================================================================
HRESULT CPlayer::Init()
{
	m_AttackSEFlag = false;						//�U���T�E���h��false
	//���[�V�������j���[�g�������[�V�����ɂ���
	m_Motiontype = MOTIONTYPE_NEUTRALMOTION;
	//�t�@�C���ǂݍ���
	Load();
	//�ő�l�����߂�
	m_vtxMax = m_pModelp[0]->GetVtxMax();
	//�ŏ��l�����߂�
	m_vtxMin = m_pModelp[0]->GetVtxMin();
	//�T�C�Y�����߂�
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;
	//�v���C���[��HP�o�[�̕\��
	CPlife::Create((m_pos));
	return S_OK;
}
//=============================================================================
// �v���C���[�̏I��
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
// �v���C���[�̍X�V
//=============================================================================
void CPlayer::Update()
{
	//�ړ�����
	Move();
	//�����蔻��
	Collision(&m_pos, &m_posOld, m_size);
	//�p�x�̐��K��
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
	//�v���C���[�����񂾂Ƃ�
	if (m_nLife <= 0 && m_bDie == false)
	{
		CFade::Set(CApplication::MODE_RESULT);
		m_bDie = true;
	}
	//�U������
	Attack();
	//���[�V����
	Motionanimation();
}
//=============================================================================
// �v���C���[�̕`��
//=============================================================================
void CPlayer::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pModelp[nCnt]->Draw();
	}
}
//=============================================================================
// �v���C���[�̃N���G�C�g
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, int nLife)
{
	CPlayer *apPlayer = nullptr;

	//���I����
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
// �t�@�C��
//=============================================================================
void CPlayer::Load()
{
	int nNumParts;							//���f���̃p�[�c�̕ϐ�
	int nCntMotionSet = 0;					//���[�V�����Z�b�g�̃J�E���g
	int Loop = 0;							//���[�v������̂��̕ϐ�
	int nCntKeySet = 0;						//���[�V�����Z�b�g���̃J�E���g
	int nCntKey = 0;						//�L�[�̃J�E���g
	char aText[2000];						//��������i�[����z��
	char FileName[MAX_PARTS][2000];			//2�����z��

	FILE *pFile; //�t�@�C���|�C���^��錾

	pFile = fopen("data/player/Playermodel.txt", "r");

	aText[0] = '\0';	//������Ȃ�

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C���ɓ��͂����f�[�^�������o������
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
				continue;
			}

			//�t�@�C���l�[���𕡐����͂���
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
				fscanf(pFile, "%s", &FileName[m_nCountModel][0]);	//0�Ԗڂ���ǂݍ��܂��

																	//���f���p�[�c�̐���
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
						fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
						continue;
					}

					if (strcmp(&aText[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "PARTSSET") == 0)
					{
						D3DXVECTOR3 pos, rot;
						int IndexParent = 0;	//�e�̔ԍ�
						int Ind = 0;

						while (strcmp(&aText[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
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

						//���f���p�[�c�̓ǂݍ���
						m_pModelp[Ind]->SetModel(&FileName[Ind][0]);

						//���f���p�[�c�ɏ�񂪓����Ă�����
						if (m_pModelp[Ind])
						{
							//���f���p�[�c�̌����̐ݒ�
							m_pModelp[Ind]->SetRot(rot);
						}

						//�e�̔ԍ���0��艺��������
						if (IndexParent < 0)
						{
							//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
							m_pModelp[Ind]->SetMatrix(&m_mtxWorld);
						}
						//�e�̔ԍ������f���p�[�c��菬����������
						else if (IndexParent < MAX_PARTS)
						{
							//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
							m_pModelp[Ind]->SetMatrix(m_pModelp[IndexParent]->GetMatrix());
						}
					}
				}
			}
			if (strcmp(&aText[0], "MOTIONSET") == 0)
			{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�

				m_Motionset[nCntMotionSet] = CMotionset::Create();

				m_Motionset[nCntMotionSet]->SetNumParts(nNumParts);

				while (strcmp(&aText[0], "END_MOTIONSET") != 0)
				{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
					fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

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
								fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
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

				//���[�V�����Z�b�g���C���N�������g
				nCntMotionSet++;
				//���[�V�����Z�b�g���̏�����
				nCntKeySet = 0;
				//�L�[�J�E���g�̏�����
				nCntKey = 0;
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//null�`�F�b�N
		if (m_pModelp[nCnt] != nullptr)
		{
			//pos��rot�̕ϐ��錾
			D3DXVECTOR3 pos, rot;

			//���ݎg���Ă��郂�[�V�����̈ʒu����pos�ɑ��
			pos = m_Motionset[m_Motiontype]->GetKeySet(1)->GetKey(nCnt)->GetPos();

			//���ݎg���Ă��郂�[�V�����̌�������rot�ɑ��
			rot = m_Motionset[m_Motiontype]->GetKeySet(1)->GetKey(nCnt)->GetRot();

			//���f���̈ʒu�ƌ����̐ݒ�
			m_pModelp[nCnt]->SetPos(pos);
			m_pModelp[nCnt]->SetRot(rot);
		}
	}
}

//=============================================================================
// �ړ�
//=============================================================================
void CPlayer::Move()
{

	CInput *pInput = CApplication::GetKeyboard();
	D3DXVECTOR3 pPos = Getpos();
	D3DXVECTOR3 pSize = Getsize();
	D3DXVECTOR3 crot = CCamera::Getrot();

	//�ړ��ʂ̍X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	
	//��
	if (CGame::GetSBox()->OnCollision() == true)
	{
		m_bJump = false;
		CGame::GetSBox()->SetOnCollision(false);
	}
	//�y
	for (int nCnt = 0; nCnt < 75; nCnt++)
	{
		if (CGame::GetModel()[nCnt]->OnCollision() == true)
		{
			m_bJump = false;
			CGame::GetModel()[nCnt]->SetOnCollision(false);
		}
	}
	m_pos += m_move;
	//�d��
	m_move.y -= 0.5f;
	if (m_pos.y < 1.0f)
	{
		m_pos.y = 1.0f;
		m_move.y = 0.0f;
		m_bJump = false;
	}
	if (m_Motiontype != MOTIONTYPE_ATTACK)
	{

		// S�L�[�������ꂽ
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
				//�ړ����[�V�����̐ݒ�
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		// W�L�[�������ꂽ
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
				//�ړ����[�V�����̐ݒ�
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		// D�L�[�������ꂽ
		else if (pInput->GetPress(DIK_D) == true)
		{
			m_move.x += sinf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_move.z += cosf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_rotDest.y = (crot.y - D3DX_PI / 2.0f);
			if (m_bWalk == false)
			{
				//�ړ����[�V�����̐ݒ�
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		//// A�L�[�������ꂽ
		else if (pInput->GetPress(DIK_A) == true)
		{
			m_move.x -= sinf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_move.z -= cosf(crot.y + D3DX_PI / 2.0f) * 0.1f;
			m_rotDest.y = (crot.y + D3DX_PI / 2.0f);
			if (m_bWalk == false)
			{
				//�ړ����[�V�����̐ݒ�
				SetMotionType(CPlayer::MOTIONTYPE_MOVE);
				m_bWalk = true;
			}
		}
		//�ړ����[�V�����̐ݒ�
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
		
		//�W�����v
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
		//��]
		if (pInput->GetTrriger(DIK_LSHIFT) == true)
		{
			m_bRoll = true;
		}
		if (m_bRoll == true)
		{
			//��
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
			//��
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
			//��
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
			//�E
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
			//�E��
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
			//����
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
			//����
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
			//�E��
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
//�U������
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
			{//���͈͓̔��ɓ�������_���[�W��^����
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
				//�G���^�[�L�[��������ă��[�V�������A�^�b�N���[�V��������Ȃ��Ƃ�
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
				{//���͈͓̔��ōU��������M�~�b�N�Ƀ_���[�W��^����
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
//���f���ƃv���C���[�̓����蔻��
//-------------------------------------------------------------------------
void CPlayer::Collision(D3DXVECTOR3 *pPos,			//���݂̈ʒu
	D3DXVECTOR3 *pPosOld,						//�O��̈ʒu
	D3DXVECTOR3 size)							//�T�C�Y
{

	//��
	CStrongbox *pSbox = CGame::GetSBox();
	if (pSbox != nullptr)
	{
		pSbox->Collision(pPos,
			pPosOld,
			size
		);
	}
	//�S�[��
	CGoal *pGoal = CGame::GetGoal();
	if (pGoal != nullptr)
	{
		pGoal->Collision(pPos,
			pPosOld,
			size
		);
	}

	//�y
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
	//�G�Ƃ̓����蔻��
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
	//�M�~�b�N�̓����蔻��
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
	//�R�C���̓����蔻��
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
//���[�V�����A�j���[�V����
//-------------------------------------------------------------------------
void CPlayer::Motionanimation(void)
{
	m_nFrame++;		//�t���[���̃C���N�������g
	
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
	{	//���݂̃A�j���[�V�����̃t���[�����ȏゾ������

		int NextKeySet = 0;					//���̃L�[�Z�b�g�ϐ�
		NextKeySet = m_PresentKeyset + 1;	//���̃L�[�Z�b�g����

		if (NextKeySet >= m_Motionset[m_Motiontype]->GetNumKey() && m_Motionset[m_Motiontype]->GetLoop() == 1)
		{	//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���

			NextKeySet = 0;					//�Đ����̃L�[���J�E���g��������
			m_PresentKeyset = NextKeySet;	//���̃A�j���[�V�����̍ŏ��̃��[�V�����Z�b�g��ݒ肷��
		}
		else if (NextKeySet >= m_Motionset[m_Motiontype]->GetNumKey() && m_Motionset[m_Motiontype]->GetLoop() == 0)
		{	//�Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ�

			m_Motionset[m_Motiontype]->SetLoop(false);		//���[�v��false�ɐݒ肷��	
			m_Motiontype = MOTIONTYPE_NEUTRALMOTION;		//���[�V�������j���[�g�������[�V�����ɂ���
			NextKeySet = 0;									//���̃L�[�Z�b�g�̏�����
		}

		for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
		{
			//���x�̌v�Z
			m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_pModelp[nCnt]->GetPos());
			m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			//��]�̌v�Z
			m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_pModelp[nCnt]->GetRot());
			m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
		}

		m_nFrame = 0;						//�t���[���̏�����
		m_PresentKeyset = NextKeySet;		//���݂̃��[�V�����Ɏ��̃��[�V��������
	}
	
}

//-------------------------------------------------------------------------
//���[�V�����̎�ނ̐ݒ�
//-------------------------------------------------------------------------
void CPlayer::SetMotionType(MOTIONTYPE type)
{
	m_Motiontype = type;

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//���x�̌v�Z
		m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetPos() - m_pModelp[nCnt]->GetPos());
		m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		//��]�̌v�Z
		m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetRot() - m_pModelp[nCnt]->GetRot());
		m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
	}
}