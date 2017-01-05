# ifndef __ScriptLive2d__
# define __ScriptLive2d__

# include "cocos2d.h"

# include "ScriptBase.h"

namespace User
{
    class ScriptLive2d : public ScriptBase
    {
    public:
        ScriptLive2d( cocos2d::Layer* layer, std::string model, std::string dir );
        ~ScriptLive2d( );
    public:
        SCRIPT( in );
        SCRIPT( out );
    public:
        // �\��Ɋւ��X�N���v�g�ł��B
        SCRIPT( normal );
        SCRIPT( rejoice );
        SCRIPT( sorrow );
        SCRIPT( getSurprise );
        SCRIPT( getAngry );
        SCRIPT( �^�ʖڂȊ� );
        SCRIPT( �Y��ł�� );
    public:
        SCRIPT( touchon );
        SCRIPT( touchoff );
    private:
        cocos2d::Node* node = nullptr;
    };
}

# endif // __ScriptLive2d__
