# ifndef __LayerBase__
# define __LayerBase__

# include "cocos2d.h"

# include <string>

namespace User
{
    class LayerBase : public cocos2d::Layer
    {
    public:
        LayerBase( );
        ~LayerBase( );
        // init�֐��̌�ɌĂ΂�܂��B
        // setup����getLayer���g����悤�ɂȂ�܂��B
        virtual void setup( );
    public:
        // ���̊֐��ŃV�[���ɒǉ�����Ă���S�Ẵ��C���[�ɃA�N�Z�X�ł��܂��B
        template<class LayerClass>
        LayerClass* getLayer( );
    };

    template<class LayerClass>
    inline LayerClass* LayerBase::getLayer( )
    {
        auto scene = this->getScene( );
        auto node = scene->getChildByName( typeid( LayerClass ).name( ) );
        return dynamic_cast<LayerClass*>( node );
    }
}

# endif // __SceneBase__
