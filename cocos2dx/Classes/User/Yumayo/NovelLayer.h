# ifndef __NovelLayer__
# define __NovelLayer__

# include "../LayerBase.h"

# include "TextData.h"
# include "TextLabels.h"
# include "TextScriptReader.h"
# include "TextChank.h"

namespace User
{
    class SwitchBoolean
    {
    public:
        SwitchBoolean( ) : frag( false ) { }
        SwitchBoolean( bool frag ) : frag( frag ) { }
    public:
        void on( ) { frag = true; }
        void off( ) { frag = false; }
    public:
        operator bool( ) { return frag; }
        bool operator!( ) { return !frag; }
    private:
        bool frag;
    };

    class NovelLayer : public LayerBase
    {
    public:
        CREATE_ARGS_FUNC( NovelLayer );
        NovelLayer( std::string const& novelPath );
        ~NovelLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta )override;
    public:
        void on( );
        void off( );
    public:
        void setNextChild( std::string const& name );
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
        // �I�����ŃV�i���I�̓ǂݍ��ݒ�~�@�\�̃X�C�b�`
        SwitchBoolean systemStop;
        void textUpdate( );
    private:
        std::string novelPath;
        double delayTime = 0.0F; // delayTime���c���Ă���ꍇ
        // �ǂݍ��݋@�\���~���邩�ǂ����B
        // �e�L�X�g��ǂݍ��ݓr���̏ꍇ��true�ɂȂ�܂��B
        void readingProceedUpdate( );
        void textNextRead( );
        void textActionStop( );
        // delay��0�ł��邩����Asys:l���e�L�X�g���S�Ė��܂�܂œǂݍ��݂܂��B
        void textRead( );
        // �X�N���v�g�����s���ǂݍ���
        void textPartyRead( );
        // �e�L�X�g�f�[�^����ɂ���B
        void textClear( );
        // �ǂݍ��񂾃e�L�X�g�f�[�^���m�x�����C���[�ɓ\��t����B
        void textPasting( );
        // �ǂݍ��݂���~�����܂œǂݍ��ނ��̃X�C�b�`
        SwitchBoolean systemRead;
        // �����ɓǂݔ�΂��@�\�̃X�C�b�`
        SwitchBoolean readProceed;
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
