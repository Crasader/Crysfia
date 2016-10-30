# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextData.h"
# include "TextLabels.h"
# include "TextScriptReader.h"
# include "TextChank.h"

namespace User
{
    class NovelLayer : public LayerBase
    {
    public:
        CREATE_FUNC( NovelLayer );
        NovelLayer( );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void setNextChild( std::string const& name );
        void textUpdate( );
        void switchIsSystemRead( ) { isSystemRead = !isSystemRead; }
        void switchIsNextText( ) { isNextText = !isNextText; }
        void switchIsReadingProceed( ) { isReadingProceed = !isReadingProceed; }
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
    private:
        double delayTime = 0.0F; // delayTime���c���Ă���ꍇ
        bool isSystemRead = false; // sys:l��3�s��ǂݍ��ނ܂Ŕ�΂����B
        bool isNextText = true; // �I�����Ȃǂœǂݍ��݂��~���邩�ǂ����B
        bool isReadingProceed = false; // �����ɓǂݔ�΂����ǂ����B
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
