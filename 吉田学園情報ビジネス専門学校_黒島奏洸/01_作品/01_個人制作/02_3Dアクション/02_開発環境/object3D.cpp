//============================================================================
//
// Object3D.cpp
// Author : �����@�t��
//
//=============================================================================
#include"object3D.h"
#include"rendere.h"
#include"application.h"
#include"input.h"
//-------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
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
CObject3D::~CObject3D()
{
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̏�����
//-------------------------------------------------------------------------
HRESULT CObject3D::Init()
{

	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g		
	pDevice = CApplication::GetRendere()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[�J�����W��)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y, m_pos.z + 100.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z + 100.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y, m_pos.z - 100.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z - 100.0f);

	//�@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�J���[�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	m_fWidth = pVtx[2].pos.x - pVtx[0].pos.x;
	m_fHeight = pVtx[0].pos.y - pVtx[1].pos.y;


	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̏I��
//-------------------------------------------------------------------------
void CObject3D::Uninit()
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
void CObject3D::Update()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[�J�����W��)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �I�u�W�F�N�g�̕`��
//-------------------------------------------------------------------------
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;    //�f�o�C�X�ւ̃|�C���g

	pDevice = CApplication::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

								 //���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);

	//�I�u�W�F�N�g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

}
//-------------------------------------------------------------------------
// pos�ݒ�
//-------------------------------------------------------------------------
void CObject3D::setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0;

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �N���G�C�g
//-------------------------------------------------------------------------
CObject3D *CObject3D::Create()
{
	CObject3D *apObject3D = nullptr;

	//���I����
	apObject3D = new CObject3D;

	apObject3D->Init();
	apObject3D->Setpos3D({0.0f,0.0f,0.0f});
	apObject3D->Setsize3D(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	return apObject3D;
}
//-------------------------------------------------------------------------
// �e�N�X�`���̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}
//-------------------------------------------------------------------------
// �T�C�Y�̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::setsize(D3DXVECTOR3 size)
{
	m_Size = size;
	m_fHeight = size.y;
	m_fWidth = size.x;
	//�Ίp���̒���
	m_fLength = sqrtf(m_fHeight * m_fHeight + m_fWidth * m_fWidth);
	//�Ίp���̊p�x
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
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
// �e�N�X�`���̔��f
//-------------------------------------------------------------------------
void CObject3D::setTexture(float Upos1, float Upos2, float Bpos1, float Bpos2)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
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
void CObject3D::settype(int type)
{
	m_nType = type;
}

//-------------------------------------------------------------------------
// ���C�t�̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::setlife(int life)
{
	m_nLife = life;
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::setrotate(D3DXVECTOR3 rot)
{
	m_rot = rot;


	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

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
void  CObject3D::setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius)
{
	m_revCentor = Center;
	m_frevSpeed = fSpeed;
	m_frevRadius = fRadius;
}
//-------------------------------------------------------------------------
// �p�x�̐ݒ�
//-------------------------------------------------------------------------
void  CObject3D::setrevCenter(D3DXVECTOR3 revCenter)
{
	m_revCentor = revCenter;
}
//-------------------------------------------------------------------------
// �F�̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::setcolor(float r, float g, float b, float ��)
{
	VERTEX_3D*pVtx;				//���_���ւ̃|�C���^

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
//-------------------------------------------------------------------------
// �ʒu�̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::Setpos3D(D3DXVECTOR3 pos)
{
	m_pos = pos;
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�𐶐�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[�J�����W��)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//���_�����A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------------------------
// �T�C�Y�̐ݒ�
//-------------------------------------------------------------------------
void CObject3D::Setsize3D(D3DXVECTOR3 size)
{
	VERTEX_3D *pVtx;        //���_���ւ̃|�C���^

	m_Size = size;
																			  //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̍X�V
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
