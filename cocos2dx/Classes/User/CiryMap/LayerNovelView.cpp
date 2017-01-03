
#include "LayerNovelView.h"

#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
    LayerNovelView * LayerNovelView::create( std::string const& scenario, std::function<void( )> const& saveCallFunc )
    {
        LayerNovelView *pRet = new( std::nothrow ) LayerNovelView( );
        if ( pRet && pRet->init( scenario, saveCallFunc ) )
        {
            pRet->autorelease( );
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    bool LayerNovelView::init( std::string const& scenario, std::function<void( )> const& saveCallFunc )
    {
        if ( !cocos2d::LayerColor::init( ) ) return false;

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        float fadeTime = 0.2F;

        // �F�͍��F
        setColor( Color3B::BLACK );

        // ������Ԃł̓��C���[�͓����B
        setOpacity( 0 );
        // �t�F�[�h�C��
        runAction( FadeTo::create( fadeTime, 196 ) );


        // �^�b�v������A�t�F�[�h�A�E�g���ă��C���[���폜����B
        // �_�u���^�b�v��h�����߂ɁA��x�����ꂽ��Aevent�𖳌��ɂ���B
        auto event = EventListenerTouchOneByOne::create( );
        event->setSwallowTouches( true );
        event->onTouchBegan = [this, event, fadeTime]( Touch* t, Event* e )
        {
            if ( isNext ) return true;

            for ( auto& child : getChildren( ) )
            {
                child->runAction( FadeOut::create( fadeTime ) );
            }

            auto fade = FadeTo::create( fadeTime, 0 );
            auto removeEvent = CallFunc::create( [event] { Director::getInstance( )->getEventDispatcher( )->removeEventListener( event ); } );
            runAction( Sequence::create( fade, removeEvent, RemoveSelf::create( ), nullptr ) );
            return true;
        };
        Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( event, this );

        // ��Ƀ^�C�g��
        // ���̉��ɃQ�b�g�ł���A�C�e���Ȃǂ�\��
        // ���Ɍ���{�^��

        // �^�C�g�� //
        auto titleLabel = Label::createWithTTF( scenario,
                                                u8"res/fonts/HGRGE.TTC",
                                                32 );
        titleLabel->setAnchorPoint( Vec2( 0.5F, 1.0F ) ); // �^�񒆏�
        titleLabel->setTextColor( Color4B( 242, 242, 242, 255 ) ); // ��
        titleLabel->setPosition( vo + Vec2( vs.width * 0.5F, vs.height ) ); // ��ʐ^��, ��
        addChild( titleLabel );

        // �A�C�e�����͂܂����� //

        // ����{�^�� //
        auto okButton = ui::Button::create( u8"res/texture/system/ok.button.png" );
        okButton->setAnchorPoint( Vec2( 0.5F, 0.0F ) );
        okButton->setPosition( vo + Vec2( vs.width * 0.5F, 0.0F ) );
        okButton->addTouchEventListener( [ this, okButton, scenario, saveCallFunc ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            // ��x�����Ȃ��悤�ɁB
            if ( isNext ) return;

            runAction( CallFunc::create( [ this, okButton, scenario, saveCallFunc ]
            {
                if ( auto sprite = Sprite::create( ) )
                {
                    sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                    sprite->setAnchorPoint( Vec2( 0, 0 ) );
                    sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                    sprite->setOpacity( 0 );
                    sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ this, scenario, saveCallFunc ]
                    {
                        SceneManager::createNovel( scenario, saveCallFunc );
                    } ), RemoveSelf::create( ), nullptr ) );
                    addChild( sprite );
                }
            } ) );

            okButton->pause( );
            isNext = true;
        } );
        addChild( okButton );

        for ( auto& child : getChildren( ) )
        {
            child->setOpacity( 0 );
            child->runAction( FadeIn::create( fadeTime ) );
        }

        return true;
    }
}
