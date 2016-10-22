# ifndef __TextString__
# define __TextString__

# include "cocos2d.h"

# include <string>
# include <functional>

namespace User
{
    class TextString
    {
    public:
        TextString( );
        ~TextString( );
    public:
        // �ꕶ�����\��������Ƃ��̃A�N�V������ݒ肵�܂��B
        // ���̊֐����ĂԂƃA�N�V�������X�^�[�g���܂��B
        void actionStart( );
        // �ꕶ�����\��������Ƃ��̃A�N�V������ݒ肵�܂��B
        // ���̊֐����ĂԂƃR�[���o�b�N�֐���ݒ肵�A�A�N�V�������X�^�[�g���܂��B
        void actionAndCallfuncStart( std::function<void( )> const& $actionCallfunc );
        // �A�N�V�����������I�ɏI��点�܂��B
        void actionStop( );
        // ���C���[�ɓ\��t��
        void layerPasting( cocos2d::Layer* layer );
        // ���C���[���甍����
        void layerPeelOff( cocos2d::Layer* layer );
        // �ǂݏグ���x��ݒ肵�܂��B
        void setReadOutSpeed( float $readOutSpeed );
    public:
        void setLabelString( std::string const& text );
        void setDrawPosition( cocos2d::Vec2 position );
    private:
        // �ꕶ�����\��������Ƃ��̃A�N�V������ݒ肵�܂��B
        // ���� : ������̒����B
        void setActionStart( size_t $stringLength );
    private:
        cocos2d::Label* label; // ���������s�`�悷�邽�߁B
        std::string text; // �`�悷�镶����B
        std::function<void( )> actionCallfunc;
        static float readOutSpeed;
    };
}

# endif // __TextString__
