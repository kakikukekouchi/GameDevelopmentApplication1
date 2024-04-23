#pragma once

#define D_KEYCODE_MAX (256)		//�L�[�R�[�h�̑���

//
class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];		//���݂̓��͏��
	static char old_key[D_KEYCODE_MAX];		//�O�t���[���̓��͏��

public:
	static void Update();					//�X�V����

	static bool GetKey(int key_code);			//���������Ă����
	static bool GetKeyDown(int key_code);		//�������u��
	static bool GetKeyUp(int key_code);			//�������u��

private:
	static bool CheckKeyCodeRange(int key_code);//�L�[�R�[�h�z��`�F�b�N
};



