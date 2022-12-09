#include"DxLib.h"
#include "SceneMain.h"
#include"../UI/Pad.h"
#include"../game.h"

namespace
{
	constexpr int kFieldHeight = 0;				//field�̑傫��
	constexpr int kFieldWindth = 0;				//field�̑傫��
	//constexpr int kFieldHeight = 75;
	//constexpr int kFieldWindth = 100;
	constexpr int kBlocHeight = 21;				//field�̍���
	constexpr int kBlocWindht = 12;				//field�̉���
	constexpr int kFieldFloor = 570;			//field�̉�

	constexpr int kFrameTimer = 50;
	constexpr int kMinoTimer = 10;

	int field[kBlocHeight][kBlocWindht];
	
	int m_coordinateX = 0;
	int m_coordinateY = 0;

	const char* kNameTitle = "Main���";
	const char* kNameGuide = "������";
}

SceneMain::SceneMain():
	m_frametimer(),								//�t���[���^�C�}�[
	m_pos(),									//�~�m�̃|�W�V����
	m_size(),									//�~�m�̃T�C�Y
	m_gravity(),								//�~�m�̏d��
	m_speed(),									//�~�m�̗����X�s�[�h
	m_placed(false),
	m_minotimer()
{
	MinoInit();
}

void SceneMain::Init()
{
	m_frametimer = kFrameTimer;					//�^�C�}�[��ݒ�
	m_minotimer = kMinoTimer;
	for (int i = 0; i < kBlocHeight; i++)
	{
		for (int j = 0; j < kBlocWindht; j++)
		{
			field[j][i] = 0;

		}
	}
	//for (int i = 0; i < kBlocHeight; i++)
	//{
	//	printfDx("\n");
	//	for (int j = 0; j < kBlocWindht; j++)
	//	{
	//		switch (field[j][i])
	//		{
	//		case 0:
	//			printfDx(" ");
	//			break;
	//		case 1:
	//			printfDx("1");
	//		default:
	//			break;
	//		}
	//	}
	//}
}


void SceneMain::MinoInit()
{
	m_pos.x = 150;								//�����ʒu
	m_pos.y = 0;								//�����ʒu
	m_size.x = 30;								//�����T�C�Y
	m_size.y = 30;								//�����T�C�Y
	m_gravity = m_size.y / 2;								//�d��
	m_speed = 2.5f;								//�X�s�[�h
	m_placed = false;
}

void SceneMain::MoveUpdate()
{
	m_coordinateY = m_pos.y / m_size.y;
	m_coordinateX = m_pos.x / m_size.x;

	if (m_pos.y == kFieldFloor)								//
	{
		//MinoInit();
		if (m_minotimer > 0)
		{
			m_minotimer--;
			return;
		}
		if (m_minotimer <= 0)
		{
			field[m_coordinateY][m_coordinateX] = 1;
			m_placed = true;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_LEFT))				//���̈ړ������A�ړ�����
	{
		m_pos.x -= m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�̈ړ������A�ړ�����
	{
		m_pos.x += m_size.x;						//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		if (m_pos.x > 270)
		{
			m_pos.x = 270;
		}
	}

	if (m_pos.y >= 570)								//field������o�Ȃ��悤�ɐݒ�
	{
		m_pos.y = 570;
	}
	if (Pad::isTrigger(PAD_INPUT_UP))				//��̈ړ�����
	{
		m_pos.y = kFieldFloor;						//�L�[�������ꂽ���u�ŉ��܂�
		m_placed = true;
	}

	if (Pad::isPress(PAD_INPUT_DOWN))				//���̈ړ�����
	{
		m_pos.y += m_speed;							//�L�[�������ꂽ�牟���ꂽ�����ɓ���
		return;										//������Ă���Ԃ̓t���[���^�C�}�[�̏������X�L�b�v����
	}

	if (m_frametimer > 0)							//���L�[��������Ă��Ȃ��Ƃ��̓^�C�}�[�̐������炷
	{
		m_frametimer--;
	}
	if (m_frametimer == 0)							//�^�C�}�[���[���ɂȂ����痎��������
	{
		m_pos.y += m_gravity;
		m_frametimer = kFrameTimer;					//������������^�C�}�[�̐��l�����ɖ߂�
	}
	if (m_pos.y >= 570)								//field������o�Ȃ��悤�ɐݒ�
	{
		m_pos.y = 570;
	}
}

SceneBase* SceneMain::Update()
{
	//if (m_placed == false)
	{
		MoveUpdate();									//�~�m�̈ړ�����
	}

	return this;
}
void SceneMain::Draw()
{
	if (Placed())
	{
		DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),						//�~�m�̕\��
			static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
			GetColor(255, 0, 0), false);
	}

	if (!Placed())
	{
		DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),						//�~�m�̕\��
		static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),
		GetColor(0, 255, 255), false);
	}

	DrawBox(kFieldWindth - 2, kFieldHeight - 2, 300 + 2, 600 + 2, GetColor(255, 255, 255), false);					//field�̘g




	///////////////////////////////////////
	///        �m�F�p�̐��l�\��         ///
	///////////////////////////////////////


	for (int i = 0; i < kBlocHeight; i++)
	{
		//DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		DrawFormatString(kFieldWindth, kFieldHeight + (i * 30), GetColor(255, 255, 255), " %d", i);
		for (int j = 0; j < kBlocWindht; j++)
		{
			DrawFormatString(kFieldWindth + (j * 30), kFieldHeight, GetColor(255, 255, 255), " %d", j);
		}
	}

	//DrawFormatString(500, 0, GetColor(255, 255, 255), " %d", m_frametimer);
	DrawFormatString(600, 0, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_pos.x / 30), static_cast<int>(m_pos.y / 30));		//���W
	DrawFormatString(600, 75, GetColor(255, 255, 255), " {x %d,y %d}", static_cast<int>(m_coordinateX), static_cast<int>(m_coordinateY));		//���W
	DrawFormatString(600, 100, GetColor(255, 255, 255), " y %d", m_coordinateY);		//���W
	//DrawFormatString(600, 125, GetColor(255, 255, 255), " x %d", x);		//���W

	if (field[m_coordinateY][m_coordinateX] == 1)
	{
		DrawFormatString(600, 50, GetColor(255, 255, 255), " %d", 1);
	}
	if (Placed() == true)
	{
		DrawFormatString(700, 300, GetColor(255, 255, 255), " a");		//���W
	}
	if (Placed() == false)
	{
		DrawFormatString(700, 300, GetColor(255, 255, 255), " b");		//���W
	}
}