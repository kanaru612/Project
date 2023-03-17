//============================================================================
//
// Player.h
// Author : �����@�t��
//
//=============================================================================
#include <assert.h>
#include "plife.h"
#include "application.h"
#include "rendere.h"
#include "fade.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
CPlife::CPlife()
{

}

CPlife::~CPlife()
{

}

//-------------------------------------------------------------------------
//�v���C���[��HP�o�[�̏�����
//-------------------------------------------------------------------------
HRESULT CPlife::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();


	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;

	m_nLife = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f - PLIFE_WIDTH * m_nLife, 720.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f - PLIFE_WIDTH * m_nLife, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-------------------------------------------------------------------------
//�v���C���[��HP�o�[�̏I��
//-------------------------------------------------------------------------
void CPlife::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�j������
	CObject::Release();
}

//-------------------------------------------------------------------------
//�v���C���[��HP�o�[�̍X�V
//-------------------------------------------------------------------------
void CPlife::Update()
{
	CPlayer *pPlayer = CGame::GetPlayer();
	m_nLife = pPlayer->Getlife();
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(300.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(300.0f, 30.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	if (m_nLife <= 2)
	{
		SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_nLife <= 1)
	{
		SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_nLife <= 5 && m_nLife > 2)
	{
		SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_nLife > 5)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(300.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f - PLIFE_WIDTH * m_nLife, 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(300.0f, 30.0f, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}
//-------------------------------------------------------------------------
//�v���C���[��HP�o�[�̕`��
//-------------------------------------------------------------------------
void CPlife::Draw()
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------------------------------------
//�v���C���[��HP�o�[�̐���
//-------------------------------------------------------------------------
CPlife *CPlife::Create(D3DXVECTOR3 pos)
{
	CPlife *pLife = nullptr;

	pLife = new CPlife;

	pLife->Init();
	pLife->setpos(pos);
	return pLife;
}
//-------------------------------------------------------------------------
//�v���C���[��HP�o�[�̐F�̐ݒ�
//-------------------------------------------------------------------------
void CPlife::SetColor(float r, float g, float b, float ��)
{
	VERTEX_2D*pVtx;				//���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 Buffer = GetBuffer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	Buffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(r, g, b, ��);
	pVtx[1].col = D3DXCOLOR(r, g, b, ��);
	pVtx[2].col = D3DXCOLOR(r, g, b, ��);
	pVtx[3].col = D3DXCOLOR(r, g, b, ��);

	//���_�o�b�t�@���A�����b�N����
	Buffer->Unlock();
}
