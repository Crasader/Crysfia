# ifndef __FlickFunctionLayer__
# define __FlickFunctionLayer__

# include "../LayerBase.h"
# include "ui/CocosGUI.h"

namespace User
{
    class Functions : public cocos2d::ui::Layout
    {
    public:
        CREATE_ARGS_FUNC( Functions );
    public:
        Functions( std::vector<std::pair<std::string, std::function<void( )>>> functions );
        int icon_size;
        void begin( );
        void cancel( );
        void end( );
        std::function<void( )> ended;
        std::function<void( )> canceled;
    private:
    };

    class FlickFunctionLayer : public LayerBase
    {
    public:
        CREATE_FUNC( FlickFunctionLayer );
        FlickFunctionLayer( );
        ~FlickFunctionLayer( );
        bool init( ) override;
        void setup( ) override;
        void end( );
    private:
        void createFlickCircle( );
    private:
        /**
         *  Novel���C���[��ۑ����܂��B
         *  ���j���[���o������ANovel���C���[�̃^�b�`�C�x���g�𖳌��ɂ��邽�߂ł��B
         */
        cocos2d::Layer* novelLayer = nullptr;

        /**
         *  �o�b�O���O���C���[��ۑ����܂��B
         *  �T�[�N���̋@�\�Ƃ��Ďg�����߂ł��B
         */
        cocos2d::Layer* backlogLayer = nullptr;

        /**
         * �l�[�����C���[��ۑ����܂��B
         * �m�x���E�B���h�E�̔�\����Ԃ̋@�\���������߂ł��B
         */
        cocos2d::Layer* nameLayer = nullptr;


        Functions* functions = nullptr;
    };
}

# endif // __FlickFunctionLayer__
