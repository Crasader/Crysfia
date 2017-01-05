# ifndef __LayerCity__
# define __LayerCity__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

#include "../../Lib/json.h"

namespace User
{
    struct ScenarioPointData
    {
        void initScenarioPointData( Json::Value const& root )
        {
            scenario = root[u8"scenario"].asString( );
            visit = root[u8"visit"].asBool( );
            position = cocos2d::Vec2( root[u8"position"][0].asInt( ),
                                  root[u8"position"][1].asInt( ) );
            title = root[u8"title"].asString( );

            auto& day = root[u8"day"];
            switch ( day.size( ) )
            {
            case 1:
                day_begin = day[0].asInt( );
                day_end = day[0].asInt( );
                break;
            case 2:
                day_begin = day[0].asInt( );
                day_end = day[1].asInt( );
                break;
            default:
                break;
            }

            auto& time = root[u8"time"];
            switch ( time.size( ) )
            {
            case 1:
                time_begin = ( ScenarioPointData::Times )time[0].asInt( );
                time_end = ( ScenarioPointData::Times )time[0].asInt( );
                break;
            case 2:
                time_begin = ( ScenarioPointData::Times )time[0].asInt( );
                time_end = ( ScenarioPointData::Times )time[1].asInt( );
                break;
            default:
                break;
            }
        }

        void initScenarioPointData( ScenarioPointData const& data )
        {
            *this = data;
        }

        /**
         * �ǂ������C�x���g�Ȃ̂�
         */
        enum Event
        {
            none,
            force,
            main,
            sub
        };
        Event event = none;

        /**
         *  ���łɓǂ񂾃V�i���I�Ȃ̂��ǂ����B
         *  @true   �ǂ�ł�����
         *  @false  ���ǂȂ�
         */
        bool visit = false;

        int day_begin = -1;

        int day_end = -1;

        enum Times
        {
            morning,
            daytime,
            night
        };
        Times time_begin = Times::morning;

        Times time_end = Times::night;

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
        bool init( );
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
        LayerCity( std::string const& name );
        ~LayerCity( );
        bool init( ) override;
        void setup( ) override;
        void jsonRead( );
        void time_next( );
        cocos2d::Label* createLabel( std::string const& title );
        cocos2d::ui::Button* createBackButton( );
        cocos2d::ui::Button* createOptionButton( );
        cocos2d::ui::Button* createTimeNextButton( );
    private:
        /**
         *  �Z�[�u�f�[�^�̖��O��ۑ����܂��B
         */
        std::string save_name;

        /**
         *  ���̓��̖��O��ۑ����܂��B
         */
        std::string island_name;

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
