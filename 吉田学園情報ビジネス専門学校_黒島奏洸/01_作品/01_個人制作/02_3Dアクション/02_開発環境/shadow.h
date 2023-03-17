//============================================================================
//
// Shadow.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include"object3D.h"
#define MAX_SHADOW	(128)
class CShadow	:	public CObject3D
{
public:
	CShadow();
	~CShadow()override;
	//�e�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;					//�ʒu
		D3DXVECTOR3 rot;					//����
		D3DXMATRIX mtxWorld;
		bool bUse;
	}Shadow;

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	int set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetPos(int nIdx, D3DXVECTOR3 pos);
private:
	//�O���[�o���錾
	LPDIRECT3DTEXTURE9		m_pTexture;
	Shadow m_aShadow[MAX_SHADOW];
};

#endif
