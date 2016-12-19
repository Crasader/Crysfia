# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

#include "../../Lib/json.h"

namespace User
{
    struct ScenarioPointData
    {
        /**
         *  �f�[�^�̏��������s���܂��B
         *  �\���ɕK�v�ȃf�[�^�����l�߂܂��B
         */
        void initData( bool visit, cocos2d::Vec2 const& position, std::string const& scenario )
        {
            this->visit = visit;
            this->position = position;
            this->scenario = scenario;
        }

        /**
         *  �f�[�^�̏��������s���܂��B
         *  �R�s�[������Ă��̂܂ܑ�����܂��B
         */
        void initData( ScenarioPointData const& scenario ) { *this = scenario; }

        /**
         *  ���łɓǂ񂾃V�i���I�Ȃ̂��ǂ����B
         *  @true   �ǂ�ł�����
         *  @false  ���ǂȂ�
         */
        bool visit;

        /**
         *  �}�b�v�摜���̕\���ʒu�B
         */
        cocos2d::Vec2 position;

        /**
         *  �ǂݍ��ރV�i���I�t�@�C���̃p�X�B
         */
        std::string scenario;

        /**
         *  ���̃m�x���̃^�C�g���B
         */
        std::string title;
    };

    class LayerCityMark : protected ScenarioPointData, public cocos2d::ui::Button
    {
    public:
        void setButtonEndCallBack( std::function<void( )>const& callback );
    protected:
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
        std::function<void( )> buttonEnd;
    };

    class MainMark : public LayerCityMark
    {
    public:
        CREATE_FUNC( MainMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class SubMark : public LayerCityMark
    {
    public:
        CREATE_FUNC( SubMark );
        void pasteMap( cocos2d::Sprite* map, ScenarioPointData const& data );
    };

    class Calendar : public cocos2d::ui::Layout
    {
    public:
        CREATE_FUNC( Calendar );
        Calendar* make( );
    private:
        /**
         *  �J�����_�[�ɕ\��������ɂ��B
         */
        int day;
    };

    class CityMap : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( CityMap );
        CityMap* make( std::string const& backgroundfile );
    private:
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

        /**
         *  �}�b�v�����ɃX���C�h����Ƃ��Ɏg���܂��B
         */
        cocos2d::Vec2 translate;
    };

    class LayerCity : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( LayerCity );
        LayerCity( std::string const& path );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        void jsonRead( );
        cocos2d::ui::Button* createBackButton( );
        cocos2d::ui::Button* createOptionButton( );
    private:
        /**
         *  json�f�[�^�ւ̃p�X��ۑ����܂��B
         */
        std::string path;

        /**
         * ���̍s���ړI��\�����邽�߂̃f�[�^�B
         */
        std::map<std::string, cocos2d::Data> data;

        /**
         *
         */
        Json::Value root;
    };
}

# endif // __LayerCity__
