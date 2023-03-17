//=============================================================================
//
// Camera.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	//�v���g�^�C�v�錾
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Set(void);
	static D3DXVECTOR3 Getrot(void) { return m_rot; };
private:

	D3DXMATRIX m_mtxProjection;			//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;				//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_posV;					//�ʒu
	D3DXVECTOR3 m_posR;					//�O��̈ʒu
	D3DXVECTOR3 m_vecU;					//�ړ���
	static D3DXVECTOR3 m_rot;			//�p�x
	float m_fDistance;					//����
	D3DXVECTOR3 m_posVDest;				//�ʒu
	D3DXVECTOR3 m_posRDest;				//�O��̈ʒu
};

#endif
