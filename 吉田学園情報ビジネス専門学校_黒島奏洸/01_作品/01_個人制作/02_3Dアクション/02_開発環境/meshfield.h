//=============================================================================
//
// Meshfield.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
#include"object.h"
#define MESHFIELD_X_BLOCK (36)	//X�����̃u���b�N��
#define MESHFIELD_Z_BLOCK (36)	//Z�����̃u���b�N��
//���b�V���̒��_���
#define MESHFIELD_VERTEX_NUM		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))	
//�C���f�b�N�X��
#define MESHFIELD_INDEX_NUM			((MESHFIELD_X_BLOCK + 1) * 2 * (MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1)) * ( 2 * (MESHFIELD_Z_BLOCK - 1)))
//�|���S�����̎����ύX
#define MESHFIELD_PRIMITVE_NUM		(MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * (2 + (MESHFIELD_Z_BLOCK - 1)) * (4 *( MESHFIELD_Z_BLOCK - 1)))			
class CMeshfield		:public CObject
{
public:
	explicit CMeshfield(int nPriority = 2);
	~CMeshfield()override;
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Draw(void)override;
	void Update(void)override;
	static CMeshfield *Create();
	void Collision(D3DXVECTOR3 mpos);
	void setpos(const D3DXVECTOR3 pos) override { m_pos = pos; };
	void setlife(int life) override { m_nLife = life; };
	static HRESULT Load(void);
	static void Unload(void);

	D3DXVECTOR3 Getpos(void)override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_size; };
	int Gettype(void) override { return m_nType; };
	int Getlife(void) override { return m_nLife; };
	D3DXVECTOR3 Getrot(void) override { return m_rot; };
private:
	//���b�V���t�B�[���h�̃e�N�X�`��
	static LPDIRECT3DTEXTURE9 m_pTexture;
	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
	//���b�V���t�B�[���h�̈ʒu
	D3DXVECTOR3 m_pos;
	//���b�V���t�B�[���h�̌���
	D3DXVECTOR3 m_rot;
	//���b�V���t�B�[���h�̌���
	D3DXVECTOR3 m_size;
	//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
	//�^�C�v�ԍ�
	int m_nType;
	//���C�t
	int m_nLife;
};
#endif
