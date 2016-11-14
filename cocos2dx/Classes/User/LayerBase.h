# ifndef __LayerBase__
# define __LayerBase__

# include "cocos2d.h"

# include <string>

// �ϒ��z��ɑΉ�����create�֐������܂��B
// ���g��CREATE_FUNC�Ɠ����ł��B
#define CREATE_ARGS_FUNC(__TYPE__) \
template <class... Args> \
static __TYPE__* create(Args... args) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(args...); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

namespace User
{
    class LayerBase : public cocos2d::Layer
    {
    public:
        LayerBase( );
        virtual ~LayerBase( );
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
