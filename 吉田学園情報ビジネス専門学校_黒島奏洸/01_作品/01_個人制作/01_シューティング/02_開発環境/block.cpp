//=============================================================================
//
// block.cpp
// Author : 
//
//=============================================================================]
#include"block.h"
#include"Input.h"
#include"application.h"
#include"explosion.h"
#include"rendere.h"
LPDIRECT3DTEXTURE9 CBlock::m_ptex = {};
CBlock::CBlock()
{
	m_move = { 0.0f,0.0f,0.0f };
}
CBlock::~CBlock()
{

}
//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CBlock::Init()
{
	CObject2D::Init();
	m_move = { 0.0f,0.0f,0.0f };
	BindTexture(m_ptex);
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CBlock::Uninit()
{
	CObject2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CBlock::Update()
{
	D3DXVECTOR3 bpos = Getpos();
	bpos.x += m_move.x;
	bpos.y += m_move.y;
	setpos(bpos);
	setTexture(0.0f, m_fWidth, 0.0f, m_fHeight);
	CObject2D::Update();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBlock::Draw()
{
	CObject2D::Draw();
}
//=============================================================================
// �N���G�C�g
//=============================================================================
CBlock *CBlock::Create(const D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CBlock *pblock = nullptr;

	//���I����
	pblock = new CBlock;

	pblock->Init();
	pblock->SetType(OBJTYPE_BLOCK);
	pblock->m_fWidth = fWidth;
	pblock->m_fHeight = fHeight;
	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZEBLOCK * fWidth, MAX_SIZEBLOCK * fHeight, 0.0f);
	pblock->setTexture(0.0f, fWidth, 0.0f,fHeight);
	pblock->setsize(size);
	pblock->setpos(pos);
	return pblock;
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetDevice();    //�f�o�C�X�ւ̃|�C���g		

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/texture/block.jpg",
		&m_ptex);

	return S_OK;

}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBlock::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_ptex != NULL)
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
}