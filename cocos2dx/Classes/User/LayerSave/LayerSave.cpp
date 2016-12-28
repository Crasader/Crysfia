#include "LayerSave.h"

#include "../../Lib/Utilitys.h"

#include "ui/CocosGUI.h"

#include "../Novel/OptionalValues.h"

#include "../SceneManager.h"

#include "../../Lib/AudioManager.h"

#include "../System/DataSettings.h"

#include "../../Lib/json.h"

#include "../Novel/NovelLayer.h"

#include "../CiryMap/LayerOption.h"

USING_NS_CC;

namespace User
{
    LayerSave::LayerSave( )
    {

    }
    LayerSave::~LayerSave( )
    {

    }
    bool LayerSave::init( )
    {
        if ( !Layer::init( ) ) return false;

        addChild( createModal( ) );

        scheduleUpdate( );


        std::string dir = u8"res/texture/system/";
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        panelSize = Vec2( 300, 270 ) / scale;

        auto background = Sprite::create( dir + u8"save.background.png" );
        addChild( background );
        background->setScale( Lib::fitWidth( background, vs.width ) );
        background->setPosition( vo + vs * 0.5 );

        /**
        *  ��ʉ����̃��j���[
        */
        auto board = Sprite::create( u8"res/texture/system/board.png" );
        addChild( board );
        {
            auto boardPixel = board->getContentSize( ) / scale;
            board->setScale( Lib::fitWidth( board, vs.width ) );
            board->setAnchorPoint( Vec2( 0, 0 ) );
            board->setPosition( vo );

            auto height = boardPixel.height - 10 * 2;

            if ( auto button = createBackButton( ) )
            {
                board->addChild( button );
                button->setScale( Lib::fitHeight( button, height * scale ), Lib::fitHeight( button, height * scale ) );
                button->setPosition( Vec2( 10, 10 ) * scale );
            }
        }


        // �^�C�g���{�^���̐ݒu
        auto title = Sprite::create( dir + u8"save.title.png" );
        title->setPosition( background->getContentSize( ).width * 0.5, background->getContentSize( ).height - 140 * scale );
        background->addChild( title );

        // �Z�[�u�Q�[�W������������ׂ�
        auto list = ui::ListView::create( );
        list->setAnchorPoint( Vec2( 0.5, 0.5 ) );
        list->setPosition( vo + background->getContentSize( ) * 0.5 );
        list->setContentSize( Size( panelSize.width * 2,
                                    background->getContentSize( ).height
                                    - board->getContentSize( ).height * board->getScale( ) //  ���̃��j���[�̕�
                                    - title->getContentSize( ).height * title->getScale( ) // ��̃^�C�g���̕�
                                    - 140 * scale // �^�C�g����̌��Ԃ̕�

        ) );
        background->addChild( list );

        // �Ƃ肠����10�񕪕��ׂ܂��B
        // ����2����̂�20���̃Z�[�u�f�[�^���쐬�ł��܂��B
        // 20 + �I�[�g�Z�[�u����21�m�ۂ��Ă����܂��傤�B
        const std::string default_name = u8"system.save.";
        for ( int i = 0, save = 1; i < 10; ++i, save += 2 )
        {
            list->addChild( createSavePanelSide( default_name + StringUtils::toString( save ),
                                                 default_name + StringUtils::toString( save + 1 ) ) );
        }

        return true;
    }
    void LayerSave::setup( )
    {

    }
    cocos2d::ui::Button * LayerSave::createBackButton( )
    {
        auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );

        auto button = ui::Button::create( u8"res/texture/system/backbutton.png" );

        button->setScale( Lib::fitWidth( button, 128 * scale ), Lib::fitWidth( button, 128 * scale ) );
        button->setAnchorPoint( Vec2( 0, 0 ) );
        button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                if ( auto p = getParent( ) )
                {
                    p->removeAllChildrenWithCleanup( true );
                    p->init( );
                }
            }
        } );
        return button;
    }
    cocos2d::Node * LayerSave::createModal( )
    {
        // �ȈՓI�ȃ��[�_�����C���[�ł��B
        // �����ȉ摜����ʂ����ς��ɓ\�邱�Ƃŋ@�\���Ă��܂��B
        std::string dir = u8"res/texture/system/";
        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto modal = ui::Button::create( dir + u8"null.png" );

        modal->setScale( vs.width * 0.5 * scale, vs.height * 0.5 * scale );
        modal->setPosition( vo + vs * 0.5 );

        return modal;
    }
    cocos2d::ui::Layout* LayerSave::createDialog( std::string const& str, std::function<void( )> const & yes, std::function<void( )> const & no )
    {
        auto layout = ui::Layout::create( );

        layout->addChild( createModal( ) );

        auto vs = Director::getInstance( )->getVisibleSize( );
        auto vo = Director::getInstance( )->getVisibleOrigin( );
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        //���j���[�̔w�i
        auto menuImage = ui::Scale9Sprite::create( u8"res/Image/WindowBase/WinBase_61.png",
                                                   Rect( 0 / scale, 0 / scale,
                                                         120 / scale, 120 / scale ),
                                                   Rect( 32 / scale, 32 / scale,
                                                         64 / scale, 64 / scale ) );

        auto content_size = Size( 640, 640 ) * scale;
        menuImage->setContentSize( content_size );
        menuImage->setPosition( vo + vs * 0.5 );
        layout->addChild( menuImage );

        auto label = Label::createWithTTF( str, u8"res/fonts/HGRGE.TTC", 36 );
        label->setPosition( content_size * 0.5 );
        menuImage->addChild( label );

        auto yes_button = ui::Button::create( u8"res/texture/system/yes.button.base.png", u8"res/texture/system/yes.button.push.png" );
        yes_button->setPosition( Vec2( content_size.width * 0.25, content_size.height * 0.1 ) );
        yes_button->setScale( 0.5 );
        yes_button->setAnchorPoint( Vec2( 0, 0 ) );
        menuImage->addChild( yes_button );
        yes_button->addTouchEventListener( [ = ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            if ( yes )yes( );
            layout->removeFromParentAndCleanup( true );
        } );
        auto no_button = ui::Button::create( u8"res/texture/system/no.button.base.png", u8"res/texture/system/no.button.push.png" );
        no_button->setPosition( Vec2( content_size.width * 0.75, content_size.height * 0.1 ) );
        no_button->setAnchorPoint( Vec2( 1, 0 ) );
        no_button->setScale( 0.5 );
        menuImage->addChild( no_button );
        no_button->addTouchEventListener( [ = ] ( Ref* ref, ui::Widget::TouchEventType type )
        {
            if ( type != ui::Widget::TouchEventType::ENDED ) return;

            if ( no )no( );
            layout->removeFromParentAndCleanup( true );
        } );

        return layout;
    }
    cocos2d::ui::Layout * User::LayerSave::createSavePanel( std::string const& name )
    {
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto ui = ui::Layout::create( );

        auto panel = Sprite::create( u8"res/texture/system/save.gauge.png" );
        panel->setAnchorPoint( Vec2( 0, 0 ) );
        ui->addChild( panel );

        auto reload = [ name, scale, panel, ui, this ]
        {
            ui->removeChildByName( u8"thumb" );
            Director::getInstance( )->getTextureCache( )->removeTextureForKey( getLocalReadPath( name + u8".png" ) );
            auto thumb = Sprite::create( getLocalReadPath( name + u8".png" ) );
            if ( thumb )
            {
                thumb->setName( u8"thumb" );
                thumb->setScale( Lib::fitHeight( thumb, 163 / scale ) );
                thumb->setAnchorPoint( Vec2( 0, 0 ) );
                thumb->setPosition( Vec2( 12 / scale, panel->getContentSize( ).height - 175 / scale ) );
                ui->addChild( thumb );
            }
        };

        reload( );


        auto save = ui::Button::create( u8"res/texture/system/save.button.save.png" );
        save->setAnchorPoint( Vec2( 0, 0 ) );
        save->setPosition( Vec2( 12 / scale, panel->getContentSize( ).height - 255 / scale ) );
        ui->addChild( save );
        auto load = ui::Button::create( u8"res/texture/system/save.button.load.png" );
        load->setAnchorPoint( Vec2( 0, 0 ) );
        load->setPosition( Vec2( 155 / scale, panel->getContentSize( ).height - 255 / scale ) );
        ui->addChild( load );

        save->addTouchEventListener( [ this, name, reload ] ( LAMBDA_TOUCH )
        {
            switch ( type )
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addChild( createDialog( u8"�Z�[�u���܂����H",
                                        [ name, reload ] {
                    if ( NovelLayer::screen ) // �T���l�C���摜�������Ԃł����Z�[�u�ł��܂���B
                    {
                        {
                            auto data = FileUtils::getInstance( )->getDataFromFile( FileUtils::getInstance( )->getWritablePath( ) + u8"autosave.json" );
                            writeDataUserLocal( data, name + u8".json" );
                        }
                        {
                            auto ptr = NovelLayer::screen;
                            if ( ptr )
                            {
                                ptr->saveToFile( FileUtils::getInstance( )->getWritablePath( ) + name + u8".png" );
                            }
                        }
                        {
                            auto data = FileUtils::getInstance( )->getDataFromFile( FileUtils::getInstance( )->getWritablePath( ) + u8"UserDefault.xml" );
                            writeDataUserLocal( data, name + u8".xml" );
                        }
                        reload( );
                    }

                },
                                        [ ] {

                } ) );
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        } );
        load->addTouchEventListener( [ this, name, reload ] ( LAMBDA_TOUCH )
        {
            switch ( type )
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                addChild( createDialog( u8"���[�h���܂����H",
                                        [ name, reload ] {

                    if ( FileUtils::getInstance( )->isFileExist( FileUtils::getInstance( )->getWritablePath( ) + name + u8".json" ) )
                    {
                        {
                            auto data = FileUtils::getInstance( )->getDataFromFile( FileUtils::getInstance( )->getWritablePath( ) + name + u8".json" );
                            writeDataUserLocal( data, u8"autosave.json" );
                        }
                        {

                        }
                        {
                            auto user = UserDefault::getInstance( );
                            auto bgm = user->getFloatForKey( u8"bgm" );
                            auto se = user->getFloatForKey( u8"se" );
                            auto novel_speed = user->getFloatForKey( u8"novel.speed" );
                            auto voice = user->getFloatForKey( u8"voice" );

                            auto data = FileUtils::getInstance( )->getDataFromFile( FileUtils::getInstance( )->getWritablePath( ) + name + u8".xml" );
                            writeDataUserLocal( data, u8"UserDefault.xml" );

                            UserDefault::getInstance( )->flush( );

                            user = UserDefault::getInstance( );
                            user->setFloatForKey( u8"bgm", bgm );
                            user->setFloatForKey( u8"se", se );
                            user->setFloatForKey( u8"novel.speed", novel_speed );
                            user->setFloatForKey( u8"voice", voice );
                        }
                    }
                },
                                        [ ] {

                } ) );
                break;
            case cocos2d::ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        } );

        ui->setContentSize( panel->getContentSize( ) );

        return ui;
    }
    cocos2d::ui::Layout * User::LayerSave::createSavePanelSide( std::string const& left_name, std::string const& right_name )
    {
        auto scale = Director::getInstance( )->getContentScaleFactor( );

        auto ui = ui::Layout::create( );

        auto left = createSavePanel( left_name );
        auto right = createSavePanel( right_name );

        ui->addChild( left );

        right->setPosition( Vec2( panelSize.width, 0 ) );
        ui->addChild( right );

        ui->setContentSize( Size( panelSize.width * 2, panelSize.height ) );
        return ui;
    }
}
