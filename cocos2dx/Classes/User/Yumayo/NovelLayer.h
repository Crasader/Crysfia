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

        void textUpdate( float delta );
        // �X�N���v�g�����s���ǂݍ���
        void textPartyUpdate( );
        // �e�L�X�g�f�[�^����ɂ���B
        void textClear( );
        // �ǂݍ��񂾃e�L�X�g�f�[�^���m�x�����C���[�ɓ\��t����B
        void textPasting( );
        // �ǂݍ��݂���~�����܂œǂݍ��ނ��̃X�C�b�`
        void switchIsSystemRead( ) { isSystemRead = !isSystemRead; }
        // �I�����ŃV�i���I�̓ǂݍ��ݒ�~�@�\�̃X�C�b�`
        void switchIsSelectStopping( ) { isSelectStopping = !isSelectStopping; }
        // �����ɓǂݔ�΂��@�\�̃X�C�b�`
        void switchIsReadingProceed( ) { isReadingProceed = !isReadingProceed; }
        void setDelayTime( double delayTime ) { this->delayTime = delayTime; }
    private:
        double delayTime = 0.0F; // delayTime���c���Ă���ꍇ
        bool isSystemRead = true; 
        bool isSelectStopping = true; // �I�����Ȃǂœǂݍ��݂��~���邩�ǂ����B
        bool isReadingProceed = false; // �����ɓǂݔ�΂����ǂ����B
        TextData textData;
        TextScriptReader textReader;
        TextChank textChank;
        TextLabels textLabels;
    };
}

# endif // __NovelLayer__
