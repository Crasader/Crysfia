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
         *  �^�b�v���Ă��鎞�Ԃ�ۑ����܂��B
         */
        float holdTapTime = 0.0F;

        /**
         *  �����O�^�b�v�Ɉڍs����܂ł̎��Ԃł��B
         *  < holdTapTime > �����̎��Ԃ𒴂���ƃ����O�^�b�v�����ɂȂ�܂��B
         */
        const float longTapShiftTime = 0.8F;

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
         *  �����O�^�b�v�����������ꍇ�Ɂutrue�v�ɂȂ�܂��B
         */
        bool isLongTap = false;

        /**
         *  �����̃T�[�N���̃|�C���^��ۑ����Ă����܂��B
         */
        FunctionCircle* circle = nullptr;
    };
}

# endif // __FlickFunctionLayer__
