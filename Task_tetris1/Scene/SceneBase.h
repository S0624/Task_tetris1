#pragma once

//�V�[���̃x�[�X�ɂȂ�N���X
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}
	//������
	virtual void Init() {}				//������
	//�I������
	virtual void End() {}
	//�X�V����
	virtual SceneBase* Update() { return this; }			//�X�V����
	//�t�F�[�h����
	virtual void Fade(){};
	//�`��
	virtual void Draw() {}									//�`�揈��

protected:

};

