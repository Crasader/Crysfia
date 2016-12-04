# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    struct ScenarioData
    {
        /**
         *  �f�[�^�̏��������s���܂��B
         *  �\���ɕK�v�ȃf�[�^�����l�߂܂��B
         */
        void initData( bool isChecked, cocos2d::Vec2 const& position, std::string const& scenario )
        {
            this->isChecked = isChecked;
            this->position = position;
            this->scenario = scenario;
        }

        /**
         *  �f�[�^�̏��������s���܂��B
         *  �R�s�[������Ă��̂܂ܑ�����܂��B
         */
        void initData( ScenarioData const& scenario ) { *this = scenario; }

        /**
         *  ���łɓǂ񂾃V�i���I�Ȃ̂��ǂ����B
         *  @true   �ǂ�ł�����
         *  @false  ���ǂȂ�
         */
        bool isChecked;

        /**
         *  �}�b�v�摜���̕\���ʒu�B
         */
        cocos2d::Vec2 position;

        /**
         *  �ǂݍ��ރV�i���I�t�@�C���̃p�X�B
         */
        std::string scenario;
    };

    class Mark : protected ScenarioData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, ScenarioData const& data );
    };

    class MainMark : public Mark
    {
    public:
        CREATE_FUNC( MainMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioData const& data );
        MainMark( ) { }
        ~MainMark( ) { }
    };

    class SubMark : public Mark
    {
    public:
        CREATE_FUNC( SubMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioData const& data );
        SubMark( ) { }
        ~SubMark( ) { }
    };

    class Calendar : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( Calendar );
        Calendar* make( int day );
    private:
        /**
        *  �J�����_�[�ɕ\��������ɂ��B
        */
        int day;
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
         *  ���̎��ԁB
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
