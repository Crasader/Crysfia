#include "ScriptHeart.h"

#include "ui/CocosGUI.h"

#include "StringUtil.h"

#include "INIWriter.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

Vec2 operator*( Vec2 const& left, Vec2 const& right )
{
    return Vec2( left.x * right.x, left.y * right.y );
}

namespace User
{
    HeartGauge* HeartGauge::make( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        {
            auto size = Director::getInstance( )->getVisibleSize( );
            auto origin = Director::getInstance( )->getVisibleOrigin( );
            setPosition( origin + Vec2( 0, size.height ) );
        }

        // �n�[�g�A�C�R��
        auto icon = Sprite::create( u8"res/texture/system/heart.icon.png" ); if ( !icon ) return this;
        // �e���x�̃Q�[�W
        auto frame = Sprite::create( u8"res/texture/system/heart.frame.png" ); if ( !frame ) return this;


        // ����āA���C�A�E�g�̃T�C�Y�́A�A�C�R���̉��ƁA�Q�[�W�̉��𑫂����l�B
        // �c�̓A�C�R���̕����g���܂��B
        setContentSize( Size( icon->getContentSize( ).width + frame->getContentSize( ).width,
                              std::max( icon->getContentSize( ).height, frame->getContentSize( ).height ) ) );
        setAnchorPoint( Vec2( 0, 1 ) );

        // �A�C�R���̐ݒ�
        {
            icon->setAnchorPoint( Vec2( 0, 0.5 ) );
            icon->setPosition( 0, getContentSize( ).height * 0.5 );
            addChild( icon );
        }

        // �Q�[�W�̐ݒ�
        {
            frame->setAnchorPoint( Vec2( 0, 0.5 ) );
            frame->setPosition( icon->getContentSize( ).width, getContentSize( ).height * 0.5 );
            addChild( frame );
        }

        // �摜�̃s�N�Z������o�^���Ă����܂��B
        {
            size = frame->getTexture( )->getContentSizeInPixels( );
        }

        // ���݂̐e���x��o�^�B
        now = UserDefault::getInstance( )->getIntegerForKey( u8"�e���x" );

        // �}�X�N�����ʒu�����߂܂��B
        // start�̓Q�[�W�̍��[�̑傫���B
        start = 5;
        // end�̓Q�[�W�̉E�[�܂ł̒����B
        end = size.width - 5;

        // ��������}�X�N�̏����������܂��B
        if ( auto clipping = ClippingNode::create( ) )
        {
            {
                // �N���b�s���O�m�[�h�̓Q�[�W�̎q���Ƃ��܂��B
                frame->addChild( clipping );
                // ���������̂Ƃ��ɁA���_�����킹�邽�߈ȉ��̐��l�������Ă����܂��B
                clipping->setPosition( frame->getAnchorPoint( ) * frame->getContentSize( ) );
            }

            // ���ۂɏ������ނ̂͐F�̂��镔���ł��B
            clipping->setInverted( false );
            // �����������}�X�N���܂��B
            clipping->setAlphaThreshold( 0.0 );

            // �}�X�N�摜��p�ӂ��܂��B
            if ( auto mask = Sprite::create( "res/texture/system/heart.mask.png" ) )
            {
                clipping->setStencil( mask );
                mask->setAnchorPoint( Vec2( 0, 0.5 ) );
            }

            // �h��Ԃ��C���[�W��p�ӂ��܂��B
            // �����Ń��[�v�摜�Ƃ��Ďg���̂ŁA�T�C�Y��2�ׂ̂���Œ�ł��B
            if ( auto background = Sprite::create( u8"res/texture/system/favoritegauge.png",
                                                   Rect( 0, 0, ( start + getWidth( now ) ) * scale, size.height * scale ) ) )
            {
                this->background = background;
                clipping->addChild( background );
                background->setAnchorPoint( Vec2( 0, 0.5 ) );
                background->getTexture( )->setTexParameters( { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT } );
            }
        }

        return this;
    }

    HeartGauge* HeartGauge::scriptUpAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( value ) );
        setScale( Lib::fitWidth( this, Director::getInstance( )->getVisibleSize( ).width / 2 ) );
        return this;
    }

    HeartGauge* HeartGauge::scriptDownAction( std::string const & str )
    {
        auto value = StringUtil::string_value<int>( str );
        if ( value < 1 ) return nullptr;
        runAction( createInValueStopOutExitAction( -value ) );
        setScale( Lib::fitWidth( this, Director::getInstance( )->getVisibleSize( ).width / 2 ) );
        return this;
    }

    HeartGauge * HeartGauge::up( int value )
    {
        if ( value < 1 ) return nullptr;
        runAction( createValueAction( value ) );
        return this;
    }

    HeartGauge * HeartGauge::down( int value )
    {
        if ( value < 1 ) return nullptr;
        runAction( createValueAction( -value ) );
        return this;
    }

    int HeartGauge::getWidth( int value )
    {
        float t = value;
        return ( end - start ) * ( t / max );
    }

    cocos2d::FiniteTimeAction * HeartGauge::createValueAction( int value )
    {
        if ( !background ) return nullptr;

        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        return CallFunc::create( [ this, value, scale ]
        {
            auto targetValue = clampf( now + value, 0, max );

            UserDefault::getInstance( )->setIntegerForKey( u8"�e���x", targetValue );
            auto rect = background->getTextureRect( );
            background->runAction( ActionFloat::create( 1.0F, now, targetValue, [ = ] ( float t )
            {
                background->setTextureRect( Rect( rect.origin.x, rect.origin.y, ( start + getWidth( t ) ) * scale, rect.size.height ) );
            } ) );

            now = targetValue;
        } );
    }

    cocos2d::Sequence* HeartGauge::createInValueStopOutExitAction( int value )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        auto pixel = getContentSize( ) / scale;
        setPosition( getPosition( ) + Vec2( 0, pixel.height ) * scale );
        auto movein = EaseExponentialOut::create( MoveBy::create( 0.5, Vec2( 0, -pixel.height ) * scale ) );
        auto moveout = EaseExponentialOut::create( MoveBy::create( 0.5, Vec2( 0, pixel.height ) * scale ) );

        auto stop = DelayTime::create( 2.0F );
        auto exit = RemoveSelf::create( );

        if ( auto action = createValueAction( value ) )
        {
            return Sequence::create( movein, action, stop, moveout, exit, nullptr );
        }
        return nullptr;
    }

    ScriptHeart::ScriptHeart( cocos2d::Layer * layer )
        : ScriptBase( layer )
    {
        REGIST_FUNC( ScriptHeart, up );
        REGIST_FUNC( ScriptHeart, down );
    }
    SCRIPT( ScriptHeart::up )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            if ( auto heart = HeartGauge::create( )->make( )->scriptUpAction( args[0] ) )
            {
                layer->addChild( heart );
            }
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptHeart::down )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            if ( auto heart = HeartGauge::create( )->make( )->scriptDownAction( args[0] ) )
            {
                layer->addChild( heart );
            }
        }
        break;
        default:
            break;
        }
    }
}
