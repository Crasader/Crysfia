# pragma once
# include "cocos2d.h"
# include "ui/CocosGUI.h"

# include "../../Lib/json.h"

namespace User
{
    // �t�F�[�h�C��
    // �������̍��F
    // �^�b�v������A�t�F�[�h�A�E�g���č폜�B
    class LayerNovelView : public cocos2d::LayerColor
    {
    public:
        static LayerNovelView* create( std::string const& scenario, std::function<void()> const& saveCallFunc );
        bool init( std::string const& scenario, std::function<void( )> const& saveCallFunc );
    private:
        std::function<void( )> saveCallFunc;
        bool isNext = false;
    };
}