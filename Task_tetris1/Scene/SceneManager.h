#pragma once
#include"SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	//������
	void Init();
	//�I������
	void End();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:
	// �V�[���x�[�X�|�C���^
	SceneBase* m_pScene;
};