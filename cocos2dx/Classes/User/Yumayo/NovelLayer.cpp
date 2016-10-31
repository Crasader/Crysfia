#include "NovelLayer.h"

#include "OptionalValues.h"

#include "SelectLayer.h"

USING_NS_CC;

namespace User
{
    NovelLayer::NovelLayer( )
        : textLabels( this )
    {

    }
    NovelLayer::~NovelLayer( )
    {

    }
    bool NovelLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        scheduleUpdate( );

        auto keyEvent = EventListenerKeyboard::create( );
        keyEvent->onKeyPressed = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_F5 )
            {
                textData.makeData( "scenario1.txt" );
            }
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL�L�[�������ꂽ�獂���ǂݍ��݂��J�n����B
                switchIsReadingProceed( );
            }
        };

        keyEvent->onKeyReleased = [ this ] ( EventKeyboard::KeyCode code, Event* event )
        {
            if ( code == EventKeyboard::KeyCode::KEY_LEFT_CTRL )
            {
                // ������CTRL���b���ꂽ�獂���ǂݍ��݂��~����B
                switchIsReadingProceed( );
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( keyEvent, this );

        auto mouseEvent = EventListenerMouse::create( );
        mouseEvent->onMouseDown = [ this ] ( EventMouse* event )
        {
            if ( event->getMouseButton( ) == MOUSE_BUTTON_LEFT )
            {
                //�@�e�L�X�g�̃A�j���[�V�������I����Ă���ꍇ
                if ( textLabels.getIsReadOuted( ) )
                {
                    // �e�L�X�g�̒��g�������܂��B
                    textClear( );
                    // �ǂݍ��݂��J�n���܂��B
                    switchIsSystemRead( );
                }
                // �e�L�X�g�̃A�j���[�V�������I����Ă��Ȃ��ꍇ
                else
                {
                    // �e�L�X�g�̒��g�������܂��B
                    textClear( );

                    while ( delayTime == 0.0 )
                    {
                        // �e�L�X�g��ǂݎn�߂܂��B
                        textPartyUpdate( );

                        // �ǂݍ��ݏI���Ȃ�
                        if ( textChank.isReadFinished( ) )
                        {
                            // �e�L�X�g�f�[�^��\��t���āB
                            textPasting( );
                            // �V�X�e���ǂݍ��݂��~�B
                            switchIsSystemRead( );

                            break;
                        }

                        // �f�B���C�͊��S�ɖ������܂��B
                        delayTime = 0.0;
                    }
                }
            }
        };
        this->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( mouseEvent, this );

        return true;
    }
    void NovelLayer::setup( )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        Rect rect = Rect( origin.x, origin.y, visibleSize.width, OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize );
        Sprite* square = Sprite::create( );
        square->setColor( Color3B( 0, 0, 0 ) );
        square->setOpacity( 128 );
        square->setTextureRect( rect );
        square->setPosition( rect.origin + rect.size / 2 );
        this->addChild( square );

        textData.makeData( "scenario1.txt" );
        textUpdate( 0.0F );
    }
    void NovelLayer::update( float delta )
    {
        // �����ǂݍ��݂��\�Ȃ當����1�t���[����1��ǂݑ�����B
        if ( isReadingProceed )
        {
            textUpdate( delta );
        }

        // �ǂݍ���
        if ( isSystemRead )
        {
            textUpdate( delta );
        }
    }
    void NovelLayer::setNextChild( std::string const & name )
    {
        auto selectLayer = this->getLayer<SelectLayer>( );

        // �I�����̃��C���[���폜
        selectLayer->removeAllChildren( );

        // ���ɓǂݍ��ރV�i���I�f�[�^���w��B
        textData.setNextChild( name );

        switchIsSelectStopping( );
    }
    void NovelLayer::textUpdate( float delta )
    {
        while ( delayTime == 0.0 )
        {
            // �e�L�X�g��ǂݎn�߂܂��B
            textPartyUpdate( );

            // �ǂݍ��ݏI���Ȃ�
            if ( textChank.isReadFinished( ) )
            {
                // �e�L�X�g�f�[�^��\��t���āB
                textPasting( );
                // �V�X�e���ǂݍ��݂��~�B
                switchIsSystemRead( );

                break;
            }

            delayTime = std::max( delayTime - delta, 0.0 );
        }
    }
    void NovelLayer::textPartyUpdate( )
    {
        if ( !textChank.isReadFinished( ) && !textData.isEmpty( ) )
        {
            textChank.insertScript( textReader.createTagWithData( textData.getLineMoved( ) ) );
        }
    }
    void NovelLayer::textClear( )
    {
        // �ǂݍ��݂𖳌��ɂ��Ă���Ȃ瑁�����^�[�����܂��B
        if ( !isSelectStopping ) return;

        textChank.clear( );
        textLabels.clear( );
    }
    void NovelLayer::textPasting( )
    {
        // �e�L�X�g�f�[�^��ǂݍ��ݏI������烉�x���ɓ\��t����B
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        textLabels.setStrings( textChank.getNovelData( ),
                               origin +
                               Vec2( ( visibleSize.width - OptionalValues::stringViewSize.x ) * 0.5F,
                                     OptionalValues::stringViewSize.y + OptionalValues::fontSize + OptionalValues::lineSpaceSize ) );
    }
}
