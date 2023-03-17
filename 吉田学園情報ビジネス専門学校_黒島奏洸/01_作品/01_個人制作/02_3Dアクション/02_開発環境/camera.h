//=============================================================================
//
// Camera.h
// Author : 黒島　奏洸
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

	//プロトタイプ宣言
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Set(void);
	static D3DXVECTOR3 Getrot(void) { return m_rot; };
private:

	D3DXMATRIX m_mtxProjection;			//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;				//ビューマトリックス
	D3DXVECTOR3 m_posV;					//位置
	D3DXVECTOR3 m_posR;					//前回の位置
	D3DXVECTOR3 m_vecU;					//移動量
	static D3DXVECTOR3 m_rot;			//角度
	float m_fDistance;					//距離
	D3DXVECTOR3 m_posVDest;				//位置
	D3DXVECTOR3 m_posRDest;				//前回の位置
};

#endif
