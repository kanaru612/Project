//=============================================================================
//
// Meshfield.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
#include"object.h"
#define MESHFIELD_X_BLOCK (36)	//X方向のブロック数
#define MESHFIELD_Z_BLOCK (36)	//Z方向のブロック数
//メッシュの頂点情報
#define MESHFIELD_VERTEX_NUM		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))	
//インデックス数
#define MESHFIELD_INDEX_NUM			((MESHFIELD_X_BLOCK + 1) * 2 * (MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1)) * ( 2 * (MESHFIELD_Z_BLOCK - 1)))
//ポリゴン数の自動変更
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
	//メッシュフィールドのテクスチャ
	static LPDIRECT3DTEXTURE9 m_pTexture;
	//頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	//インデックスバッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
	//メッシュフィールドの位置
	D3DXVECTOR3 m_pos;
	//メッシュフィールドの向き
	D3DXVECTOR3 m_rot;
	//メッシュフィールドの向き
	D3DXVECTOR3 m_size;
	//メッシュフィールドのワールドマトリックス
	D3DXMATRIX m_mtxWorld;
	//タイプ番号
	int m_nType;
	//ライフ
	int m_nLife;
};
#endif
