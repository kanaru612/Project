//============================================================================
//
// Motionset.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _MOTIONSET_H_
#define _MOTIONSET_H_
#include "main.h"
#define KEY_NUMBER		(4)					//モーションキー数の最大
class CKeyset;
class CMotionset
{
public:
	CMotionset();
	~CMotionset();

	HRESULT Init(void);
	void Uninit(void);
	static CMotionset *Create();

	//getter
	int GetLoop(void) { return m_Loop; }				
	int GetNumKey(void) { return m_Num_Key; }			
	int GetNumParts(void) { return m_NumParts; }		
	CKeyset *GetKeySet(int keyset) { return m_apKeySet[keyset]; }

	//setter
	void SetLoop(int Loop) { m_Loop = Loop; }					
	void SetNumKey(int NumKey) { m_Num_Key = NumKey; }			
	void SetNumParts(int NumParts) { m_NumParts = NumParts; }	

private:
	int m_Loop;								//ループ
	int m_Num_Key;							//モーションの数
	int m_NumParts;							//パーツの種類
	CKeyset *m_apKeySet[KEY_NUMBER];	
};

#endif