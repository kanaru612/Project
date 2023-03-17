//============================================================================
//
// Fade.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include"main.h"
#include"object2D.h"
#include"application.h"
//�t�F�[�h�A�E�g
class CFade : public CObject2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,							//�������ĂȂ����
		FADE_IN,								//�t�F�[�h�C�����
		FADE_OUT,								//�t�F�[�h�A�E�g���
		FADE_MAX
	}FADE;

	CFade();
	~CFade()override;

	HRESULT Init(CApplication::MODE modeNext);
	void Uninit(void) override;
	void Update(void) override;

	static void Set(CApplication::MODE modeNext);
	FADE Get() { return m_fade;};
	static CFade *Create(CApplication::MODE modeNext);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
	static FADE m_fade;										//�t�F�[�h�̏��
	static CApplication::MODE m_modeNext;					//���̉��(���[�h)
	static D3DXCOLOR m_color;								//�|���S��(�t�F�[�h)�̐F
};
#endif

