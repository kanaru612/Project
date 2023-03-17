//============================================================================
//
// Keyset.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _KEYSET_H_
#define _KEYSET_H_
#include "main.h"
#include"motionset.h"
#define MAX_MODEL		(4)			
class CKey;
class CKeyset
{
public:
	CKeyset();
	~CKeyset();

	HRESULT Init(void);			
	void Uninit(void);			
	static CKeyset *Create();
						
	int GetFrame() { return m_Frame; }				
	CKey *GetKey(int key) { return m_pKey[key]; }	
										
	void SetFrame(int frame) { m_Frame = frame; }	
	CKey *SetKey(int key) { m_pKey[key]; }			

private:
	int m_Frame;					//フレーム数
	CKey *m_pKey[MAX_MODEL];		//キー構造体の配列
};

#endif