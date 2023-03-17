//=============================================================================
//
// Enemy.cpp
// Author : �����@�t��
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
//�G�̏�����
//-------------------------------------------------------------------------
HRESULT CEnemy::Init()
{
	//�t�@�C���ǂݍ���
	Load();
	//�ő�l
	m_vtxMax = m_pModele[0]->GetVtxMax();
	//�ŏ��l
	m_vtxMin = m_pModele[0]->GetVtxMin();
	//�T�C�Y
	m_size.x = m_vtxMax.x - m_vtxMin.x;
	m_size.y = m_vtxMax.y - m_vtxMin.y;
	m_size.z = m_vtxMax.z - m_vtxMin.z;
	//���[�V�������j���[�g������
	SetMotionType(CPlayer::MOTIONTYPE_NEUTRALMOTION);
	m_move = { 0.0f,0.0f,0.0f };
	return S_OK;
}
//-------------------------------------------------------------------------
// �G�̏I��
//-------------------------------------------------------------------------
void CEnemy::Uninit()
{
	Release();
}

//-------------------------------------------------------------------------
// �G�̍X�V
//-------------------------------------------------------------------------
void CEnemy::Update()
{	
	Move();
	Motionanimation();
}
//-------------------------------------------------------------------------
// �G�̕`��
//-------------------------------------------------------------------------
void CEnemy::Draw()
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
	if (m_bUse == true)
	{
		for (int nCnt = 0; nCnt < MAX_PARTS_E; nCnt++)
		{
			m_pModele[nCnt]->Draw();
		}
	}
}
//-------------------------------------------------------------------------
// �N���G�C�g
//-------------------------------------------------------------------------
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, int nLife)
{
	CEnemy *pEnemy = nullptr;

	//���I����
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
// �t�@�C��
//-------------------------------------------------------------------------
void CEnemy::Load()
{
	int nNumParts;							//���f���̃p�[�c�̕ϐ�
	int nCntMotionSet = 0;					//���[�V�����Z�b�g�̃J�E���g
	int Loop = 0;							//���[�v������̂��̕ϐ�
	int nCntKeySet = 0;						//���[�V�����Z�b�g���̃J�E���g
	int nCntKey = 0;						//�L�[�̃J�E���g
	char aText[2000];						//��������i�[����z��
	char FileName[MAX_PARTS_E][2000];			//2�����z��

	FILE *pFile; //�t�@�C���|�C���^��錾

	pFile = fopen("data/Enemy/Enemymodel.txt", "r");

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
						m_pModele[Ind]->SetModel(&FileName[Ind][0]);

						//���f���p�[�c�ɏ�񂪓����Ă�����
						if (m_pModele[Ind])
						{
							//���f���p�[�c�̌����̐ݒ�
							m_pModele[Ind]->SetRot(rot);
						}

						//�e�̔ԍ���0��艺��������
						if (IndexParent < 0)
						{
							//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
							m_pModele[Ind]->SetMatrix(&m_mtxWorld);
						}
						//�e�̔ԍ������f���p�[�c��菬����������
						else if (IndexParent < MAX_PARTS_E)
						{
							//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
							m_pModele[Ind]->SetMatrix(m_pModele[IndexParent]->GetMatrix());
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

	for (int nCnt = 0; nCnt < MAX_PARTS_E; nCnt++)
	{
		//null�`�F�b�N
		if (m_pModele[nCnt] != nullptr)
		{
			//pos��rot�̕ϐ��錾
			D3DXVECTOR3 pos, rot;

			//���ݎg���Ă��郂�[�V�����̈ʒu����pos�ɑ��
			pos = m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetPos();

			//���ݎg���Ă��郂�[�V�����̌�������rot�ɑ��
			rot = m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetRot();

			//���f���̈ʒu�ƌ����̐ݒ�
			m_pModele[nCnt]->SetPos(pos);
			m_pModele[nCnt]->SetRot(rot);
		}
	}
}
//-------------------------------------------------------------------------
// ���[�V����
//-------------------------------------------------------------------------
void CEnemy::Motionanimation(void)
{
	m_nFrame++;		//�t���[���̃C���N�������g

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
			m_Motiontype = CPlayer::MOTIONTYPE_NEUTRALMOTION;		//���[�V�������j���[�g�������[�V�����ɂ���
			NextKeySet = 0;									//���̃L�[�Z�b�g�̏�����
		}

		for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
		{
			//���x�̌v�Z
			m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetPos() - m_pModele[nCnt]->GetPos());
			m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			//��]�̌v�Z
			m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetKey(nCnt)->GetRot() - m_pModele[nCnt]->GetRot());
			m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
			m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(NextKeySet)->GetFrame();
		}

		m_nFrame = 0;						//�t���[���̏�����
		m_PresentKeyset = NextKeySet;		//���݂̃��[�V�����Ɏ��̃��[�V��������
	}
}
//-------------------------------------------------------------------------
// ���[�V�����̎��
//-------------------------------------------------------------------------
void CEnemy::SetMotionType(CPlayer::MOTIONTYPE type)
{
	m_Motiontype = type;

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		//���x�̌v�Z
		m_nFrameSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetPos() - m_pModele[nCnt]->GetPos());
		m_nFrameSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_nFrameSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		//��]�̌v�Z
		m_RotSpeed[nCnt] = (m_Motionset[m_Motiontype]->GetKeySet(0)->GetKey(nCnt)->GetRot() - m_pModele[nCnt]->GetRot());
		m_RotSpeed[nCnt].x /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].y /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
		m_RotSpeed[nCnt].z /= (float)m_Motionset[m_Motiontype]->GetKeySet(0)->GetFrame();
	}
}
//-------------------------------------------------------------------------
//�G�ƃv���C���[�̓����蔻��
//-------------------------------------------------------------------------
void CEnemy::Collision(D3DXVECTOR3 *pPos,				//���݂̈ʒu
	D3DXVECTOR3 *pPosOld,								//�O��̈ʒu
	D3DXVECTOR3 size)									//�T�C�Y
{
	CInput *pInput = CApplication::GetKeyboard();
	if (m_bUse == true)
	{
		if (pPos->x - size.x / 2 < m_pos.x + m_vtxMax.x
			&& pPos->x + size.x / 2 > m_pos.x + m_vtxMin.x)
		{
			//���̓����蔻��
			if (
				pPosOld->z >= m_pos.z + m_vtxMax.z + size.z / 2.0f
				&& pPos->z < m_pos.z + m_vtxMax.z + size.z / 2.0f
				)
			{
				pPos->z = m_pos.z + m_vtxMax.z + size.z / 2.0f;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//��O�̓����蔻�� 
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

			//���̓����蔻��
			if (
				pPosOld->x <= m_pos.x + m_vtxMin.x - size.x / 2
				&& pPos->x > m_pos.x + m_vtxMin.x - size.x / 2
				)
			{
				pPos->x = m_pos.x + m_vtxMin.x - size.x / 2;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//�E�̓����蔻��
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
			//��̓����蔻��
			if (pPosOld->y >= m_pos.y + m_vtxMax.y
				&& pPos->y < m_pos.y + m_vtxMax.y)
			{
				pPos->y = m_pos.y + m_vtxMax.y;
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//���̓����蔻��
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
// �Ǐ]�ƍU������
//-------------------------------------------------------------------------
void CEnemy::Move()
{
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = pPlayer->Getpos();
	int nLife = pPlayer->Getlife();
	//�Ǐ]
	m_move.x = m_pos.x - pos.x;
	m_move.z = m_pos.z - pos.z;
	//���K��
	D3DXVec3Normalize(&m_move, &m_move);
	//����
	m_move *= 0.5;
	m_pos += (-m_move) * 1.0f;
	//�Ǐ]�̌���
	float rotDestx = m_pos.x - pos.x;
	float rotDestz = m_pos.z - pos.z;

	float rotDest = atan2f(rotDestx, rotDestz);

	//�ړI�̌����̐ݒ�
	m_rotDest = D3DXVECTOR3(0.0f, rotDest, 0.0f);

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
	//�U��
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