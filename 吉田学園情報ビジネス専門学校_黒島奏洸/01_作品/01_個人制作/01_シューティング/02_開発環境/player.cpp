//=============================================================================
//
// player.cpp
// Author : 
//
//=============================================================================
#include"player.h"
#include"application.h"
#include"Input.h"
#include"rendere.h"
#include"bullet.h"
#include"block.h"
#include"tail.h"
#include"fade.h"
#include"sound.h"
CPlayer::DamageState CPlayer::m_Damage = {};
int CPlayer::m_nLife = 0;
LPDIRECT3DTEXTURE9 CPlayer::m_ptex= {};
CPlayer::CPlayer()
{
	m_move = {0.0f,0.0f,0.0f};
	m_nPattern = 0;
	m_nCntAnim = 0;
	m_bJump = false;
	m_nstate = WALK;
	m_pTail = nullptr;
	m_nCnt = 10;
	m_Damage = NORMAL;
	m_nCntD = 0;
}
CPlayer::~CPlayer()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CPlayer::Init()
{
	CObject2D::Init();
	m_bJump = false;
	m_move = { 0.0f,0.0f,0.0f };
	m_nPattern = 0;
	m_nCntAnim = 0;
	m_nLife = 0;
	m_nstate = WALK;
	m_pTail = nullptr;
	m_nCnt = 10;
	m_nCntD = 0;

	BindTexture(m_ptex);
	setTexture((m_nPattern / 4.0f), ((m_nPattern + 1) / 4.0f), 0.0f, 0.5f);
	switch (m_nstate)
	{
	case STATE_NONE:
		break;
	case WALK:
		break;
	case JAMP:
		break;
	default:
		break;
	}
	switch (m_Damage)
	{
	case DAMAGE_NONE:
		break;
	case NORMAL:
		break;
	case DAMAGE:
		break;
	default:
		break;
	}
	
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CPlayer::Uninit()
{	
	StopSound();
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CPlayer::Update()
{
	CInput *pInput = CApplication::GetKeyboard();
	D3DXVECTOR3 pPos = Getpos();
	D3DXVECTOR3 pSize = Getsize();
	//�ړ��ʂ̍X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	//A�L�[�������ꂽ�Ƃ�
	if (pInput->GetPress(DIK_A) == true)
	{
		m_move.x += sinf(-D3DX_PI * 0.5) * 0.5f;
		
		if (pInput->GetPress(DIK_W) == true)
		{
			m_move.x = 0;
		}
		else if (pInput->GetPress(DIK_D) == true)
		{
			m_move.x = 0;
		}

	}
	//D�L�[�������ꂽ�Ƃ�
	else if (pInput->GetPress(DIK_D) == true)
	{
		m_move.x += sinf(D3DX_PI * 0.5) * 0.5f;
		if (pInput->GetPress(DIK_W) == true)
		{
			m_move.x = 0;
		}
	
	}
	//�W�����v
	if (m_bJump != true)
	{
		if (pInput->GetTrriger(DIK_SPACE) == true)
		{
			m_nstate = JAMP;
			m_move.y = -40.0f;
			m_bJump = true;
		}
	}

	if (pInput->GetPress(DIK_RETURN) == true)
	{

		m_nCnt--;

		if (m_nCnt <= 0)
		{
			PlaySound(SOUND_LABEL_SE_SHOT);
			CBullet::Create({ pPos.x ,pPos.y - pSize.y / 8 ,pPos.z }, { 14.1f,0.0f,0.0f }, 0);
			m_nCnt = 10;
		}

	}
	
	if (m_nstate == JAMP)
	{
		/*	CTail *pTail = nullptr;
			pTail = CTail::Create({ pPos.x - pSize.x,pPos.y ,pPos.z });
			m_nCntAnim++;
			if (m_nCntAnim >= 5)
			{
			m_nCntAnim = 0;
			setTexture((m_nPattern / 4.0f), ((m_nPattern + 1.0f) / 4.0f), 0.5f, 1.0f);
			m_nPattern++;
			if (m_nPattern > 4.0f)
			{
			m_nstate = STATE_WALK;
			pTail->Uninit();
			}
			}*/

		D3DXVECTOR3 rot = Getrot();
		rot.z -= D3DX_PI * 0.06f;
		setrotate({ rot });
		if (m_pTail == nullptr)
		{
			m_pTail = CTail::Create({ pPos.x - pSize.x,pPos.y ,pPos.z });
			//m_pTail->setrevPara({ pPos.x - pSize.x, pPos.y, pPos.z }, -rot.z, MAX_SIZEP / 2);
		}
		m_pTail->setpos({ pPos.x, pPos.y, pPos.z });
		//m_pTail->setrevCenter({ pPos.x - pSize.x, pPos.y + pSize.y, pPos.z });
		m_pTail->setrotate(rot);
	}

	if (pPos.x + pSize.x >= SCREEN_WIDTH - 300.0f)
	{
		pPos.x = SCREEN_WIDTH - 300.0f - pSize.x;
	}
	if (pPos.x - pSize.x <= 0)
	{
		pPos.x = pSize.x;
	}
	
	m_move.y += 1.3f;
	D3DXVECTOR3 pPosOld = pPos;
	pPos.x += m_move.x;
	pPos.y += m_move.y;

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		CObject *pObject;
		pObject = CObject::Getobject(nCnt,3);

		if (pObject != nullptr)
		{
			if (pObject->GetObjType() == OBJTYPE_BLOCK)
			{
				D3DXVECTOR3 blPos = pObject->Getpos();
				D3DXVECTOR3 blsize = pObject->Getsize();
				////��
				//if (  pPosOld.x + pSize.x >= blPos.x - blsize.x
				//	&&pPos.x - pSize.x < blPos.x - blsize.x
				//	&&pPos.y + pSize.y > blPos.y - blsize.y
				//	&&pPos.y - pSize.y < blPos.y + blsize.y
				//	)
				//{
				//	pPos.x = blPos.x - blsize.x - pSize.x;
				//	m_move.x = 0.0f;
				//}
				////�E
				//if (  pPosOld.x - pSize.x >= blPos.x + blsize.x
				//	&&pPos.x - pSize.x < blPos.x + blsize.x
				//	&&pPos.y + pSize.y > blPos.y - blsize.y
				//	&&pPos.y - pSize.y < blPos.y + blsize.y
				//	)
				//{
				//	pPos.x = blPos.x + blsize.x + pSize.x;
				//	m_move.x = 0.0f;
				//}

				//��
				if (  pPos.x + pSize.x > blPos.x - blsize.x
					&&pPos.x - pSize.x < blPos.x + blsize.x
					&&pPosOld.y - pSize.y <= blPos.y - blsize.y
					&&pPos.y + pSize.y > blPos.y - blsize.y
					)
				{
					m_nstate = WALK;
					m_bJump = false;
					pPos.y = blPos.y - blsize.y  - pSize.y;
					m_move.y = 0.0f;
					D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
					setrotate({ rot });
					if (m_pTail != nullptr)
					{
						m_pTail->Uninit();
						m_pTail = nullptr;
					}
				}
				//��
				else if (  pPos.x + pSize.x > blPos.x - blsize.x			
					&&pPos.x - pSize.x < blPos.x + blsize.x
					&&pPosOld.y + pSize.y >= blPos.y + blsize.y
					&&pPos.y - pSize.y < blPos.y + blsize.y
					)
				{
					pPos.y = blPos.y + blsize.y + pSize.y;
					m_move.y = 0.0f;
				}
				////�E�ɖ��܂����Ƃ������o��
				//else if (  pPos.x - pSize.x < blPos.x + blsize.x
				//	&&pPos.x + pSize.x > blPos.x - blsize.x
				//	&&pPos.y - pSize.y < blPos.y + blsize.y
				//	&&pPos.y + pSize.y > blPos.y - blsize.y
				//	)
				//{
				//	pPos.x = blPos.x + blsize.x + pSize.x;
				//	m_move.x = 0.0f;
				//}
				////���ɖ��܂����Ƃ������o��
				//else if (  pPos.x + pSize.x > blPos.x - blsize.x
				//	&&pPos.x - pSize.x < blPos.x + blsize.x
				//	&&pPos.y - pSize.y < blPos.y + blsize.y
				//	&&pPos.y - pSize.y > blPos.y - blsize.y
				//	)
				//{
				//	pPos.x = blPos.x - blsize.x;
				//	m_move.x = 0.0f;
				//}
			}
		}
	}
	if (m_Damage == DAMAGE)
	{
		m_nCntD++;
		setcolor(1.0f, 0.0f, 0.0f, 1.0f);
		if (m_nCntD >= 20)
		{
			m_nCntD = 0;
			setcolor(1.0f, 1.0f, 1.0f, 1.0f);
			m_Damage = NORMAL;
		}
	}
	setpos(pPos);
	setsize(pSize);
	
	CObject2D::Update();

	if (m_bJump != true && m_nstate == WALK)
	{
		m_nCntAnim++;
		if (m_nCntAnim >= 20)
		{
			m_nCntAnim = 0;
			setTexture((m_nPattern / 4.0f), ((m_nPattern + 1) / 4.0f), 0.0f, 0.5f);
			m_nPattern++;
		}
		if (m_nPattern >= 2)
		{
			m_nPattern = 0;
		}
	}

	if (m_nLife <= 0)
	{
		CFade::Set(CApplication::MODE_RESULT);
		Uninit();
	}
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CPlayer::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
CPlayer *CPlayer::Create(int nLife)
{
	CPlayer *apPlayer = nullptr;

	//���I����
	apPlayer = new CPlayer;
	apPlayer->Init();
	apPlayer->BindTexture(m_ptex);
	apPlayer->SetType(OBJTYPE_PLAYER);
	apPlayer->setpos(D3DXVECTOR3(100.0f, 200.0f, 0.0f));
	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZEP / 2, MAX_SIZEP / 2, 0.0f);
	apPlayer->setsize(size);
	apPlayer->setlife(nLife);
	
	return apPlayer;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/player4.png",
		&m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CPlayer::Unload(void)
{

	//�e�N�X�`���̔j��
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
	
}
//=============================================================================
// �N���G�C�g
//=============================================================================
void CPlayer::setlife(int life)
{
	m_nLife = life;
}
void CPlayer::setStatedamage(DamageState damage)
{
	m_Damage = damage;
}