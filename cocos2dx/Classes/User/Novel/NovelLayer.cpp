#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

#include "../SceneManager.h"

#include "ScriptStaticData.h"

#include "../TouchiEvent/EventListenerGesture.h"

#include "../../Lib/Utilitys.h"

USING_NS_CC;

namespace User
{
    cocos2d::Image* NovelLayer::screen = nullptr;

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
                textChunkManager.make( novelPath );
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

        auto touch = EventListenerTouchOneByOne::create( );
        touch->onTouchBegan = [ this ] ( Touch* touch, Event* event )
        {
            tap_began = true;

            return true;
        };
        touch->onTouchEnded = [ this ] ( Touch* touch, Event* event )
        {
            if ( automode )
            {
                removeChild( automode );
                automode = nullptr;
            }
            click( );

            readProceed.off( );

            tap_began = false;
            long_tap_began = false;
            tap_time = 0.0F;
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( touch, this );

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
            // �����ŃX�N�V�����B��
            delete screen;
            screen = utils::captureNode( Director::getInstance( )->getRunningScene( ) );

            auto visibleSize = Director::getInstance( )->getVisibleSize( );
            auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
            auto size = novelWindow->getContentSize( );
            auto mul = size.width / visibleSize.width;
            auto position = Vec2( 950.0F * scale, ( 400.0F - 340.0F ) * scale );
            auto icon = NovelReadedPointer::create( )->make( );
            icon->setPosition( position );
            novelWindow->addChild( icon );

            if ( automode )
            {
                if ( !systemStop ) automode->restart( );
            }
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
            systemStop.on( );
            systemRead.off( );
            textChunkManager.novelEndCallBack = nullptr;

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
        // �����O�^�b�v
        if ( ( tap_began ) && ( !long_tap_began ) && ( 0.3F < ( tap_time += delta ) ) )
        {
            readProceed.on( );
            long_tap_began = true;
        }

        textChunkManager.updateDelay( delta );

        // �����ǂݍ��݂̃A�b�v�f�[�g
        // �L�[�{�[�h�̍�����CTRL�������Ă���Ԃ��������ǂݍ��݋@�\��ON�ɂȂ�܂��B
        readingProceedUpdate( );

        // �e�L�X�g�̓ǂݍ��݁B
        // delay��0�ł������A�e�L�X�g��ǂݍ��ݑ����܂��B
        readNextNovel( );
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
    void NovelLayer::stop( )
    {
        readProceed.off( );

        tap_began = false;
        long_tap_began = false;
        tap_time = 0.0F;

        pause( );
    }
    void NovelLayer::restart( )
    {
        resume( );
    }
    void NovelLayer::addAuto( )
    {
        if ( automode )
        {
            removeChild( automode );
            automode = nullptr;
        }

        // ���łɒ�~���
        if ( textLabels.getIsReadOuted( ) )
        {
            // �����ɁA���̃A�j���[�V�����ɉf��B
            click( );
            automode = AutoMode::create( [ this ] { click( ); } );
            addChild( automode );
        }
        else
        {
            automode = AutoMode::create( [ this ] { click( ); } );
            addChild( automode );
        }
    }
    void NovelLayer::select( std::string const & name )
    {
        systemStop.off( );
        restart( );

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
        if ( systemStop ) return;

        if ( automode )
        {
            automode->stop( );
        }

        if ( textLabels.getIsReadOuted( ) )
        {
            novelWindow->removeChildByName( u8"novelReadedAnimation" );
            makeLoadingFeatureOn( );
        }
        else
        {
            auto action = Director::getInstance( )->getActionManager( );
            action->update( 10.0F );
            textActionStop( );
        }
    }
    void NovelLayer::next( )
    {
        if ( systemStop ) return;

        if ( automode )
        {
            automode->stop( );
        }

        textActionStop( );
        novelWindow->removeChildByName( u8"novelReadedAnimation" );
        makeLoadingFeatureOn( );
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
    AutoMode::AutoMode( std::function<void( )> tick )
        :tick( tick )
    {
        pause( );
        setName( typeid( this ).name( ) );
        scheduleUpdate( );
    }
    void AutoMode::update( float t )
    {
        if ( 3.0F < ( timer += t ) )
        {
            if ( tick )tick( );
            timer = 0.0F;
        }
    }
    void AutoMode::stop( )
    {
        pause( );
    }
    void AutoMode::restart( )
    {
        resume( );
        timer = 0.0F;
    }
}
