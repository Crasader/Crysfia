# ifndef __Layer_meal__
# define __Layer_meal__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class Layer_meal : public LayerBase
    {
    protected:
        void confirmButton( );//����{�^����\������
                              //void backButton();//�z�[���ɖ߂�{�^��

        void eatText( );//�H�ސ����p�E�B���h�E

        void foodText( std::string commentary, int x, int y, int size);//�H�ސ���
        void eraseFoodText( );

        //void eatButton(int food_num);//�H�ޕ`��p �������ŕ`�悷����̂�ύX

        void Menu( );//�I��p�E�B���h�E
        void selectedItemEvent( Ref *pSender, cocos2d::ui::ListView::EventType type );

        void eatTime( std::string eatTime );//���ԕ\���H

        void character(std::string chara_texture, std::string puppet);//�L�����N�^�[�`��

		void eraseCharacter();

        void animation( int anime_num );//�H���A�j���[�V����

        void normalButton( int text_number, std::string button_photo, int normalButtonTag );//�{�^���ėp�p

        void heart( );//�D���x�\��(��)

        void buttonAudio( std::string audio_name, int volume );//���ʉ��ǂݍ��ݗp volume 0.0~1.0

        void mealDressVolume();//���ʒ��ߗp

        void mealTutorial( );//�`���[�g���A���p?

        void eraseMealTutorial( );

        void loadData( );

		void loveMetor();

		void dressAnimetion(int my_dress, int dress_num);//���݂̃h���X�ԍ��A���ւ��̃h���X�ԍ�

		void dressChange();

		void decoration();//�����p

    public:
        bool exist;//�H�ו��摜�p
        bool reside;//����̗L���p
        int change;//�H���ƒ��ւ�
		cocos2d::UserDefault * now;
		int now_dress;//���̕�
		int next_dress = 0;//���ւ�����̕�
		int love_degrees = 0;//�e���x�󂯓n���p
        int audio_volume = 1.0f;
        int animation_num = 0;//�A�j���[�V�����ԍ�
        cocos2d::Sprite * food;//�A�j���[�V�����p�摜

        enum situation
        {
            meal,
            dressClothes,
        };

        //�H�ו��摜
        std::vector<std::string> food_button;

        //�H�ו��擾�L��
        std::vector<bool> food_gain;//false�Ŗ��擾

        //�ߑ��摜
        std::vector<std::string> dress_button;

        //�ߑ��̗L��
        std::vector<bool> dress_gain;//false�Ŗ��擾

        //�ߑ����
        std::vector<std::string> dress_commentary
        {
            u8"�����s�[�X",
            u8"�h���X",
            u8"�������",
            u8"�V�X�^�[��",
            u8"�Z�[���[��",
        };

		std::vector<std::string> dress_text2
		{
			u8"�l�p���`�̂������B",
			u8"�����ď��������ԁB",
			u8"�Î_���ς��ʕ��B",
			u8"�J���t���ł��킢���`�������������B",
			u8"�N���X�t�B�A���H�ׂ�����ʂȐH�ו��B",
		};

		std::vector<std::string> dress_text3
		{
			u8"�H�ו��Ƃ��Ă͏���������Ȃ������B",
			u8"���肪������������������B",
			u8"�W�����ɂ��Ă����������B",
			u8"�ƂĂ����킢�炵���B",
			u8"�s�v�c�ƌ��C�����ӂ�Ă���B",
		};

        //�H�ו����
        std::vector<std::string> food_commentary
        {
            u8"�p����",
            u8"�X�Y����",
            u8"�u���[�x���[",
            u8"����؂��Ƃ�",
            u8"�V�g�������",
        };

		std::vector<std::string> food_text2
		{
			u8"�l�p���`�̂������B",
			u8"�����ď��������ԁB",
			u8"�Î_���ς��ʕ��B",
			u8"�J���t���ł��킢���`�������������B",
			u8"�N���X�t�B�A���H�ׂ�����ʂȐH�ו��B",
		};

		std::vector<std::string> food_text3
		{
			u8"�H�ו��Ƃ��Ă͏���������Ȃ������B",
			u8"���肪������������������B",
			u8"�W�����ɂ��Ă����������B",
			u8"�ƂĂ����킢�炵���B",
			u8"�s�v�c�ƌ��C�����ӂ�Ă���B",
		};

		//�N���G�����t�@�b�V�����V���[
		std::vector<std::string> fashion_show;

		//�Z���N���G
		std::vector<std::string> clear;

        CREATE_ARGS_FUNC( Layer_meal );
		Layer_meal();
        Layer_meal( int layer );
        ~Layer_meal( );

        bool init( )override;
        void setup( ) override;
        void update( float delta ) override;

        void setLayer( int _layerName );
    };
}

# endif // __Layer_meal__