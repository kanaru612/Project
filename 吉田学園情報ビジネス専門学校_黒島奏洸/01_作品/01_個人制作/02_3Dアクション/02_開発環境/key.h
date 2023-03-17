//============================================================================
//
// Key.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _KEY_H_
#define _KEY_H_
#include "main.h"
class CKey
{
public:
	CKey();						
	~CKey();					

	HRESULT Init(void);			
	void Uninit();				
	static CKey *Create();		
							
	D3DXVECTOR3 GetPos() { return m_pos; }	
	D3DXVECTOR3 GetRot() { return m_rot; }	
										
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	

private:
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
};

#endif
