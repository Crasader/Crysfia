# ifndef __LayerOption__
# define __LayerOption__

# include "../LayerBase.h"

#include "ui/CocosGUI.h"

namespace User
{
    class SlideBar : public cocos2d::Node
    {
    public:
        CREATE_ARGS_FUNC( SlideBar );
        SlideBar( );
        SlideBar( float t );
        SlideBar( std::string key );
        std::function<void( float )> move;
        std::function<void( float )> ended;
        cocos2d::ui::Slider* slider;
    private:
        std::string key;
    };

    /**
     * ���[�_�����C���[�ɂȂ��Ă���̂ŁA���̂܂�create���邾���ő��v�ł��B
     */
    class LayerOption : public LayerBase
    {
    public:
        CREATE_FUNC( LayerOption );
        LayerOption( );
        ~LayerOption( );
        bool init( ) override;
        void setup( ) override;
    private:
        cocos2d::ui::Button* createBackButton( );
        cocos2d::ui::Button* createDeleteButton( );
        cocos2d::Node* createModal( );
        cocos2d::ui::Layout* createSlider( std::string const& str, std::function<void( float )> const& move = nullptr, std::function<void( float )> const& ended = nullptr );
        cocos2d::ui::Layout* createDialog( std::string const& str, std::function<void( )>const& yes, std::function<void( )>const& no );
    };
}

# endif // __LayerOption__