#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

#include "../SceneManager.h"

#include "ScriptStaticData.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( std::string const & novelPath )
        : textLabels( this )
        , novelPath( novelPath )
        , readProceed( false )
        , systemRead( true )
        , systemStop( false )
    {
    }
    NovelLayer::~NovelLayer( )
    {

    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        this->scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                //textData.makeData( novelPath );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL�L�[�������ꂽ�獂���ǂݍ��݂��J�n����B
                readProceed.on( );
            }
        };
        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL�������ꂽ�獂���ǂݍ��݂��~����B
                readProceed.off( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto multiTouchEvent = EventListenerTouchAllAtOnce::create( );
        multiTouchEvent->onTouchesEnded = [ this ] ( const std::vector<Touch*>& touches, Event* event )
        {
            for ( auto& touch : touches )
            {
                click( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( multiTouchEvent, this );

        //auto mouseEvent = EventListenerMouse::create( );
        //mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        //{
        //    if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
        //    {
        //        textUpdate( );
        //    }
        //};
        //this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );

        return true;
    }
    void NovelLayer::setup( )
    {
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto vs = Director::getInstance( )->getVisibleSize( );
        Sprite* window = Sprite::create( u8"res/texture/system/message.window.png" );
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
        window->setAnchorPoint( Vec2( 0, 0 ) );
        auto boardPixel = window->getContentSize( ) / scale;
        auto boardScale = Lib::fitWidth( window, vs.width );
        window->setScale( boardScale, boardScale );
        this->addChild( window );
        novelWindow = window;

        textLabels.animationEndCallBack = [ this ]
        {
            auto visibleSize = Director::getInstance( )->getVisibleSize( );
            auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
            auto size = novelWindow->getContentSize( );
            auto mul = size.width / visibleSize.width;
            auto position = Vec2( 950.0F * scale, ( 400.0F - 340.0F ) * scale );
            auto icon = NovelReadedPointer::create( )->make( );
            icon->setPosition( position );
            novelWindow->addChild( icon );
        };
        textChunkManager.readEndCallBack = [ this ]
        {
            // �e�L�X�g�f�[�^��\��t���āB
            textPasting( );
            // �V�X�e���ǂݍ��݂��~�B
            systemRead.off( );
        };
        textChunkManager.novelEndCallBack = [ this ]
        {
            systemRead.off( );

            if ( auto sprite = Sprite::create( ) )
            {
                sprite->setTextureRect( Rect( Vec2( 0, 0 ), Director::getInstance( )->getVisibleSize( ) ) );
                sprite->setAnchorPoint( Vec2( 0, 0 ) );
                sprite->setColor( Color3B( 0, 0, 0 ) );
                sprite->setOpacity( 0 );
                sprite->setPosition( Director::getInstance( )->getVisibleOrigin( ) );
                sprite->runAction( Sequence::create( FadeIn::create( 1.0F ), CallFunc::create( [ ]
                {
                    auto day = UserDefault::getInstance( )->getIntegerForKey( u8"��" );
                    UserDefault::getInstance( )->setIntegerForKey( u8"��", day + 1 );
                    SceneManager::createIslandMap( );
                } ), RemoveSelf::create( ), nullptr ) );
                Director::getInstance( )->getRunningScene( )->addChild( sprite, 20000 );
            }
        };

        textChunkManager.make( novelPath );
    }
    void NovelLayer::update( float delta )
    {
        textChunkManager.updateDelay( delta );

        // �����ǂݍ��݂̃A�b�v�f�[�g
        // �L�[�{�[�h�̍�����CTRL�������Ă���Ԃ��������ǂݍ��݋@�\��ON�ɂȂ�܂��B
        readingProceedUpdate( );

        // �e�L�X�g�̓ǂݍ��݁B
        // delay��0�ł������A�e�L�X�g��ǂݍ��ݑ����܂��B
        readNextNovel( );
    }
    void NovelLayer::delayOn( )
    {
        this->scheduleOnce( [ this ] ( float delay )
        {
            this->resume( );
        }, 0.016F, std::string( "novel.layer.delay" ) );

        this->setVisible( true );
    }
    void NovelLayer::on( )
    {
        this->resume( );
        this->setVisible( true );
    }
    void NovelLayer::off( )
    {
        this->pause( );
        this->setVisible( false );
    }
    void NovelLayer::select( std::string const & name )
    {
        systemStop.off( );

        auto selectLayer = this->getLayer<SelectLayer>( );

        // �I�����̃��C���[���폜
        if ( auto ptr = dynamic_cast<Menu*>( selectLayer->getChildByName( u8"select" ) ) )
        {
            ptr->setEnabled( false );
            ptr->runAction( Sequence::create( FadeOut::create( 0.3 ), RemoveSelf::create( ), nullptr ) );
        }

        // ���ɓǂݍ��ރV�i���I�f�[�^���w��B
        textChunkManager.select( name );
    }
    void NovelLayer::textClear( )
    {
        textChunkManager.gotoNext( );
        textLabels.clear( );
    }
    void NovelLayer::textPasting( )
    {
        // �e�L�X�g�f�[�^��ǂݍ��ݏI������烉�x���ɓ\��t����B
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );
        textLabels.setStrings( textChunkManager.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     311 * scale - OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
    void NovelLayer::readingProceedUpdate( )
    {
        // �����ǂݍ��݂��\�Ȃ當����1�t���[����1��ǂݑ�����B
        if ( readProceed )
        {
            // �����ǂݍ��݂ł�delay�͖������܂��B
            textChunkManager.setDelayTime( 0.0F );
            click( );
        }
    }
    void NovelLayer::click( )
    {
        if ( textLabels.getIsReadOuted( ) )
        {
            novelWindow->removeChildByName( u8"novelReadedAnimation" );
            makeLoadingFeatureOn( );
        }
        else
        {
            textActionStop( );
        }
    }
    //�@�e�L�X�g�̃A�j���[�V�������I����Ă���ꍇ
    void NovelLayer::makeLoadingFeatureOn( )
    {
        // �V�����e�L�X�g��ǂݍ���ŗǂ��ꍇ�B
        if ( !systemStop )
        {
            // �e�L�X�g�̒��g�������܂��B
            textClear( );
            // �ǂݍ��݂��J�n�̍��}���o���܂��B
            systemRead.on( );
        }
    }
    void NovelLayer::readNextNovel( )
    {
        if ( systemRead )
        {
            textChunkManager.textRead( );
        }
    }
    // �e�L�X�g�̃A�j���[�V�������I����Ă��Ȃ��ꍇ
    void NovelLayer::textActionStop( )
    {
        textChunkManager.setDelayTime( 0.0F );
        readNextNovel( );

        textLabels.actionStop( );
    }
    NovelReadedPointer* NovelReadedPointer::make( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto path = u8"res/texture/system/crystal.png";
        auto sprite = Sprite::create( path );
        auto size = sprite->getContentSize( );
        const int sx = 6;
        const int sy = 5;
        const auto parts = Size( size.width / sx, size.height / sy );
        setContentSize( parts * scale );
        Vector<SpriteFrame*> frames;
        for ( int y = 0; y < sy; ++y )
        {
            for ( int x = 0; x < sx; ++x )
            {
                auto rect = Rect( x * parts.width, y * parts.height, parts.width, parts.height );
                frames.pushBack( SpriteFrame::create( path, rect ) );
            }
        }
        auto animation = Animation::createWithSpriteFrames( frames, 0.016F );
        setScale( Lib::fitHeight( this, 64 * scale ), Lib::fitHeight( this, 64 * scale ) );
        runAction( RepeatForever::create( Animate::create( animation ) ) );
        setName( u8"novelReadedAnimation" );
        setAnchorPoint( Vec2( 1, 0 ) );

        return this;
    }
}
