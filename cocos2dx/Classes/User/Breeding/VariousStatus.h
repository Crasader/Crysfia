#pragma once

//�`�揇�p�X�e�[�^�X
enum class zOder {
	BACKGROUND = 0,
	CHARACTER,
	UI_MANAGER,
	MENU,
	OPTION,
	FOREGROUND,
	
};

enum class tabLayer
{
	BACKGROUND = 0,
	CHARACTER,
	UI_MANAGER,
	CLEANING,
	FOREGROUND,
	LAYER_MANAGER = -1,

	MAX
};

//���j���[�X�e�[�^�X
//�ǉ�����Ƃ���MAX�̏�ɋL�q���邱��
enum class ButtonType {
	STORY = 0,
	BREEDING,
	DIARY,
	OPTION,

	MAX
};

enum class SubButtonType
{
	BACK,
	MEAL,
	CLOTHES,
	CLEANING,

	MAX
};

enum class tabMenu {
	MAIN_MENU = 0,
	BREEDING_MENU,
	DIARY_MENU,
	OPTION,

	MAX
};
