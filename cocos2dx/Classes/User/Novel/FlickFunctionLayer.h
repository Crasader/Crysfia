# ifndef __FlickFunctionLayer__
# define __FlickFunctionLayer__

# include "../LayerBase.h"

namespace User
{
    class FunctionCircle : public cocos2d::DrawNode
    {
    public:
        CREATE_FUNC( FunctionCircle );
        void drawDot( const cocos2d::Vec2 &pos, float radius, const cocos2d::Color4F &color )
        {
            cocos2d::DrawNode::drawDot( pos, radius, color );
            this->radius = radius;
            this->color = color;
        }
    private:
        cocos2d::Color4F color;
        float radius;
    public:
        cocos2d::Color4F getDrawColor( ) { return color; }
        float getRadius( ) { return radius; }
        cocos2d::Vec2 getWorldPosition( ) { return convertToWorldSpaceAR( cocos2d::Point::ZERO ); }
    };

    class FlickFunctionLayer : public LayerBase
    {
    public:
        CREATE_FUNC( FlickFunctionLayer );
        FlickFunctionLayer( );
        ~FlickFunctionLayer( );
        bool init( ) override;
        void setup( ) override;
        void update( float delta ) override;
    private:
        void began( cocos2d::Touch* touch );
        void moved( cocos2d::Touch* touch );
        void ended( cocos2d::Touch* touch );
        void createFlickCircle( );
    private:
        /**
         *  �����O�^�b�v�Ȃ�utrue�v
         *  �����łȂ��Ȃ�uflase�v
         */
        bool isLongTap( ) { return isTap && isSuccessLongTap && ( longTapShiftTime <= holdTapTime ); }

        /**
         *  �����O�^�b�v�Ńt�@���N�V�������Ăяo���Ă���Ƃ��Ɂutrue�v�ɂȂ�܂��B
         *  �\�����\���ɐ؂�ւ��Ƃ��̃��[�V�������ƕ\������Ă��Ȃ��Ƃ��́ufalse�v�ɂȂ�܂��B
         *  �����ɋ@�\���g����Ƃ��̂݁utrue�v�ɂȂ�܂��B
         */
        bool isFunction = false;

        /**
         *  �^�b�v���Ă���Ԃ́utrue�v�ɂȂ�܂��B
         */
        bool isTap = false;

        /**
         *  �����O�^�b�v������������utrue�v�ɂȂ�܂��B
         */
        bool isSuccessLongTap = false;

        /**
         *  �^�b�v���Ă��鎞�Ԃ�ۑ����܂��B
         */
        float holdTapTime = 0.0F;

        /**
         *  �����O�^�b�v�Ɉڍs����܂ł̎��Ԃł��B
         *  < holdTapTime > �����̎��Ԉȏ�Ń����O�^�b�v�����ɂȂ�܂��B
         */
        const float longTapShiftTime = 0.8F;

        /**
         *  �����O�^�b�v�Ƃ݂Ȃ����̋����ł��B
         *  �ŏ��Ƀ^�b�v�����ʒu���炱�̎��Ԉȏ�Ń����O�^�b�v�ł͂Ȃ��Ȃ�܂��B
         */
        const float longTapShiftLength = 50.0F;

        /**
         *  �^�b�v�����u�Ԃ̏ꏊ��ۑ����Ă����܂��B
         */
        cocos2d::Vec2 tapBeganPosition;

        /**
         *  �Ō�ɐG�����ꏊ��ۑ����Ă����܂��B
         *  �^�b�v���Ă���Ԃɏꏊ�̕ύX���������ꍇ�͂��̒l�ɕς��܂��B
         */
        cocos2d::Vec2 tapLastPosition;

        /**
         *  �����̃T�[�N���̃|�C���^��ۑ����Ă����܂��B
         */
        FunctionCircle* circle = nullptr;

        /**
         *  �����̃T�[�N���̔��a�ł��B
         */
        const float circleRadius = 100.0F;

        /**
         *  �T�u���j���[�T�[�N���̔��a�ł��B
         */
        const float subMenuRadius = 60.0F;

        /**
         *  Novel���C���[��ۑ����܂��B
         *  ���j���[���o������ANovel���C���[�̃^�b�`�C�x���g�𖳌��ɂ��邽�߂ł��B
         */
        cocos2d::Layer* novelLayer = nullptr;
    };
}

# endif // __FlickFunctionLayer__
