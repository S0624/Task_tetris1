#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase		//�p�����ăN���X���쐬
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}

	//������
	virtual void Init()override;
	//�I������
	virtual void End()override;

	//�X�V����
	virtual SceneBase* Update()override;
	//�t�F�[�h����
	virtual void Fead();
	//�`�揈��
	virtual void Draw() override;

private:
	int m_background;
	int m_fadeSpeed;				//�t�F�[�h���x
	int m_fadeColor;				//�t�F�[�h�J���[
};

