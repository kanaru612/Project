//=============================================================================
//
// Light.h
// Author : �����t��
//
//=============================================================================
#ifndef _LIGHT_H
#define _LIGHT_H_

#include "main.h"
#define MAX_LIGHT	(8)
class CLight
{
public:
	CLight();
	~CLight();
	//�v���g�^�C�v�錾
	void Init(void);
	void Uninit(void);
	void Update(void);
	static CLight *Create();
private:
	D3DLIGHT9 m_light[MAX_LIGHT];	//���C�g���
};
#endif
