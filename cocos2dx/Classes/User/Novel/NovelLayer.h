# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextLabels.h"
# include "TextChunkManager.h"

# include "../../Lib/json.h"

namespace User
{
    class SwitchBoolean
    {
    public:
        SwitchBoolean( ) : frag( false ) { }
        SwitchBoolean( bool frag ) : frag( frag ) { }
    public:
        void on( ) { frag = true; if ( onCall ) onCall( ); }
        void off( ) { frag = false; if ( offCall ) offCall( ); }
    public:
        std::function<void( )> onCall;
        std::function<void( )> offCall;
        operator bool( ) { return frag; }
        bool operator!( ) { return !frag; }
    private:
        bool frag;
    };

    class NovelReadedPointer : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( NovelReadedPointer );
        NovelReadedPointer* make( );
    };

    class AutoMode : public cocos2d::Node
    {
        float timer = 0.0F;
        std::function<void( )> tick;
    public:
        static AutoMode* create( std::function<void( )> const& tick );
        bool init( std::function<void( )> const& tick );
        void update( float t ) override;
        void stop( );
        void restart( );
    };

    class NovelLayer : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( NovelLayer );
        NovelLayer( std::string const& scenario, std::function<void( )> const& saveCallFunc );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void in( );
        void out( );
        void on( );
        void off( );
        void stop( );
        void restart( );
    public:
        void addAuto( );
        void select( std::string const& name );
        void setDelayTime( double delayTime ) { textChunkManager.setDelayTime( delayTime ); }
        // �I�����ŃV�i���I�̓ǂݍ��ݒ�~�@�\�̃X�C�b�`
        SwitchBoolean systemStop;
        void click( );
        void next( );
        TextChunkManager& getTextChunkManager( ) { return textChunkManager; }

        /**
        * �Ō�ɃN���b�N�����Ƃ��̉�ʂ�ۑ����Ă����܂��B
        */
        static cocos2d::Image* screen;
    private:
        std::function<void( )> saveCallFunc;

        std::string novelPath;
        // �ǂݍ��݋@�\���~���邩�ǂ����B
        // �e�L�X�g��ǂݍ��ݓr���̏ꍇ��true�ɂȂ�܂��B
        void readingProceedUpdate( );
        void makeLoadingFeatureOn( );
        void readNextNovel( );
        void textActionStop( );
        // �e�L�X�g�f�[�^����ɂ���B
        void textClear( );
        // �ǂݍ��񂾃e�L�X�g�f�[�^���m�x�����C���[�ɓ\��t����B
        void textPasting( );
        // �ǂݍ��݂���~�����܂œǂݍ��ނ��̃X�C�b�`
        SwitchBoolean systemRead;
        // �����ɓǂݔ�΂��@�\�̃X�C�b�`
        SwitchBoolean readProceed;
        TextLabels textLabels;
        TextChunkManager textChunkManager;

        bool tap_began = false;
        bool long_tap_began = false;
        float tap_time = 0.0F;

        AutoMode* automode = nullptr;

        /**
         *  �m�x����\��������摜��ۑ����܂��B
         */
        cocos2d::Sprite* novelWindow = nullptr;
    };
}

# endif // __NovelLayer__
