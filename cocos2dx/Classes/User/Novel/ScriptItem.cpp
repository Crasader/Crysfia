#include "ScriptItem.h"

USING_NS_CC;

namespace User
{
    ScriptItem::ScriptItem( cocos2d::Layer* layer, std::string textureName )
        : ScriptBase( layer )
        , textureName( textureName )
    {
        REGIST_FUNC( ScriptItem, in );
        REGIST_FUNC( ScriptItem, out );
        REGIST_FUNC( ScriptItem, fadein );
        REGIST_FUNC( ScriptItem, fadeout );
        REGIST_FUNC( ScriptItem, circlein );
        REGIST_FUNC( ScriptItem, circleout );
    }
    ScriptItem::~ScriptItem( )
    {

    }
    SCRIPT( ScriptItem::in )
    {
        create( );
    }
    SCRIPT( ScriptItem::out )
    {
        layer->removeChildByTag( (int)Tag::Still );
    }
    SCRIPT( ScriptItem::fadein )
    {
        auto sprite = create( );
        if ( !sprite ) return;

        sprite->setOpacity( 0 );

        auto fade = FadeIn::create( 1.0 );
        sprite->runAction( Sequence::create( fade, nullptr ) );
    }
    SCRIPT( ScriptItem::fadeout )
    {
        if ( auto node = layer->getChildByTag( (int)Tag::Still ) )
        {
            auto fade = FadeOut::create( 1.0 );
            auto remove = RemoveSelf::create( );
            node->runAction( Sequence::create( fade, remove, nullptr ) );
        }
    }
    SCRIPT( ScriptItem::circlein )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return;

        sprite->setPosition( origin + visibleSize / 2 );
        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );

        auto clipSprite = Sprite::create( "res/texture/novel/mask.png" );
        if ( !clipSprite ) return;

        clipSprite->setTag( (int)Tag::Still );
        clipSprite->setScale( 0.0 );
        clipSprite->runAction( ScaleTo::create( 2.0, 1.0 ) );
        clipSprite->setPosition( origin + visibleSize / 2 );

        auto clipping = ClippingNode::create( );
        if ( !clipping ) return;

        clipping->setStencil( clipSprite );
        clipping->setInverted( false );
        clipping->setAlphaThreshold( 0.0 );
        clipping->addChild( sprite );

        layer->addChild( clipping );
    }
    SCRIPT( ScriptItem::circleout )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return;

        sprite->setPosition( origin + visibleSize / 2 );
        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );

        auto clipSprite = Sprite::create( "res/texture/novel/mask.png" );
        if ( !clipSprite ) return;

        clipSprite->setTag( (int)Tag::Still );
        clipSprite->setScale( 1.0 );
        clipSprite->runAction( ScaleTo::create( 2.0, -1.0 ) );
        clipSprite->setPosition( origin + visibleSize / 2 );

        auto clipping = ClippingNode::create( );
        if ( !clipping ) return;

        clipping->setStencil( clipSprite );
        clipping->setInverted( false );
        clipping->setAlphaThreshold( 0.0 );
        clipping->addChild( sprite );

        layer->addChild( clipping );
    }
    cocos2d::Sprite * ScriptItem::create( )
    {
        layer->removeChildByTag( (int)Tag::Still );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return nullptr;

        sprite->setTag( (int)Tag::Still );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );

        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );
        layer->addChild( sprite );

        return sprite;
    }
}