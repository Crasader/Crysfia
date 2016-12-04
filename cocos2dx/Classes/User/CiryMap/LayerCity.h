# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class Mark : public cocos2d::Sprite
    {
    protected:
        /**
         *  ���łɓǂ񂾃V�i���I�Ȃ̂��ǂ����B
         *  @true   �ǂ�ł�����
         *  @false  ���ǂȂ�
         */
        bool isChecked;
    };

    class MainMark : public Mark
    {
    public:
        static MainMark* createMark( );
        MainMark( ) { }
        ~MainMark( ) { }
    private:
        CREATE_FUNC( MainMark );
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( LayerCity );
        LayerCity( std::string const& backgroundPath );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
        void initBackground( );
        void initCountry( );
        void initListener( );
    private:
        bool isDebug = false;
        cocos2d::ui::Button* createDebugButton( );
    private:
        // �w�i�摜���E�B���h�E�̏c�Ƀs�b�^���ƍ��킹��T�C�Y
        float backgroundWindowHeightFitScale;
        cocos2d::Vec2 translate;
        cocos2d::Size targetSize;
        cocos2d::Sprite* background;
    private:
        std::string backgroundPath;

        /**
         * ���̍s���ړI��\�����邽�߂̃f�[�^�B
         */
        std::map<std::string, cocos2d::Data> data;

        /**
         *  ��
         */
        int month;

        /**
         *  ��
         */
        int day;

        /**
         *  ����
         */
        enum Times
        {
            morning,
            daytime,
            night
        };
        Times times;



    };
}

# endif // __LayerCity__
