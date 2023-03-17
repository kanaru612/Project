//============================================================================
//
// Object2D.cpp
// Author : �����@�t��
//
//=============================================================================
#include"object2D.h"
#include"rendere.h"
#include"application.h"
#include"input.h"

//-------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pos = {};
	m_fAngle = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
	m_fWidth = 0.0f;
	m_rot = { 0.0f,0.0f,0.0f };
	m_Size = { 0.0f,0.0f,0.0f };
	m_frevAngle = 0.0f;
	m_frevRadius = 0.0f;
	m_frevSpeed = 0.0f;
	m_revCentor = { 0.0f,0.0f,0.0f };
}

//-------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------
CObject2D::~CObject2D()
{
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̏�����
//-------------------------------------------------------------------------
HRESULT CObject2D::Init()
{

	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g		
	pDevice = CApplication::GetRendere()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fWidth = pVtx[2].pos.x - pVtx[0].pos.x;
	m_fHeight = pVtx[0].pos.y - pVtx[1].pos.y;

	//�Ίp���̒���
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth) / 2.0f;
	//�Ίp���̊p�x
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̏I��
//-------------------------------------------------------------------------
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̍X�V
//-------------------------------------------------------------------------
void CObject2D::Update()
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_frevRadius != 0.0f)
	{
		m_pos.x = m_revCentor.x + cosf(m_frevAngle) * m_frevRadius;
		m_pos.y = m_revCentor.y + sinf(m_frevAngle) * m_frevRadius;
	}
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	m_frevAngle += m_frevSpeed;
	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̕`��
//-------------------------------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g

	pDevice = CApplication::GetRendere()->GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);
	
	//�I�u�W�F�N�g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

}
//-------------------------------------------------------------------------
// pos�ݒ�
//-------------------------------------------------------------------------
void CObject2D::setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------
CObject2D *CObject2D::Create(const D3DXVECTOR3 pos)
{
	CObject2D *apObject2D = nullptr;
	
	//���I����
	apObject2D = new CObject2D;
	
	apObject2D->Init();
	apObject2D->setpos(pos);

	return apObject2D;
}
//-------------------------------------------------------------------------
// �e�N�X�`���̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}
//-------------------------------------------------------------------------
// �T�C�Y�̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::setsize(D3DXVECTOR3 size)
{
	m_Size = size;
	m_fHeight = size.y;
	m_fWidth = size.x;
	//�Ίp���̒���
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth);
	//�Ίp���̊p�x
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �e�N�X�`���̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::setTexture(float Upos1, float Upos2, float Bpos1 ,float Bpos2)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(Upos1, Bpos1);
	pVtx[1].tex = D3DXVECTOR2(Upos2, Bpos1);
	pVtx[2].tex = D3DXVECTOR2(Upos1, Bpos2);
	pVtx[3].tex = D3DXVECTOR2(Upos2, Bpos2);

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �^�C�v�̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::settype(int type)
{
	m_nType = type;
}
//-------------------------------------------------------------------------
//�@���C�t�̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::setlife(int life)
{
	m_nLife = life;
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::setrotate(D3DXVECTOR3 rot)
{
	m_rot = rot;


	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void  CObject2D::setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius)
{
	m_revCentor = Center;
	m_frevSpeed = fSpeed;
	m_frevRadius = fRadius;
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void  CObject2D::setrevCenter(D3DXVECTOR3 revCenter)
{
	m_revCentor = revCenter;
}
//-------------------------------------------------------------------------
// �F�̐ݒ�
//-------------------------------------------------------------------------
void CObject2D::setcolor(float r, float g, float b, float ��)
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
