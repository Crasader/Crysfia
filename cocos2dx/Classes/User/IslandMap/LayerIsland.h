# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
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
    };
}

# endif // __LayerIsland__
