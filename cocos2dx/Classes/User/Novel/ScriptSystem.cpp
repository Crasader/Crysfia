#include "ScriptSystem.h"

#include "ScriptStaticData.h"
#include "OptionalValues.h"

#include "SystemLayer.h"
#include "NameLayer.h"
#include "BackgroundLayer.h"
#include "HumanLayer.h"
#include "NovelLayer.h"
#include "SelectLayer.h"
#include "StillLayer.h"
#include "HeartLayer.h"
#include "Live2dLayer.h"
#include "ItemLayer.h"
#include "VoiceLayer.h"

#include "ScriptHuman.h"
#include "ScriptBackground.h"
#include "ScriptName.h"
#include "ScriptStill.h"
#include "ScriptHeart.h"
#include "ScriptLive2d.h"
#include "ScriptVoice.h"

#include "ui/CocosGUI.h"

#include "SimpleAudioEngine.h"

#include "StringUtil.h"

#include "../../Lib/Utility/Utilitys.h"

USING_NS_CC;

namespace User
{
    size_t ScriptSystem::novelIndex = 0;
    bool ScriptSystem::isShowNovel = true;

    ScriptSystem::ScriptSystem( cocos2d::Layer* layer )
        : ScriptBase( layer )
    {
        REGIST_FUNC( ScriptSystem, l );
        REGIST_FUNC( ScriptSystem, select );
        REGIST_FUNC( ScriptSystem, stop );
        REGIST_FUNC( ScriptSystem, heart );
        REGIST_FUNC( ScriptSystem, bgm );
        REGIST_FUNC( ScriptSystem, se );
        REGIST_FUNC( ScriptSystem, name );
        REGIST_FUNC( ScriptSystem, human );
        REGIST_FUNC( ScriptSystem, background );
        REGIST_FUNC( ScriptSystem, still );
        REGIST_FUNC( ScriptSystem, live2d );
        REGIST_FUNC( ScriptSystem, voice );
        REGIST_FUNC( ScriptSystem, novelon );
        REGIST_FUNC( ScriptSystem, noveloff );
        REGIST_FUNC( ScriptSystem, novelswitch );
        REGIST_FUNC( ScriptSystem, item );
    }
    ScriptSystem::~ScriptSystem( )
    {

    }
    void ScriptSystem::setup( )
    {
        ScriptStaticData::setup( );

        novelIndex = 0;
        isShowNovel = true;

        auto systemLayer = dynamic_cast<SystemLayer*>( layer );
        humanLayer = systemLayer->getLayer<HumanLayer>( );
        backgroundLayer = systemLayer->getLayer<BackgroundLayer>( );
        nameLayer = systemLayer->getLayer<NameLayer>( );
        novelLayer = systemLayer->getLayer<NovelLayer>( );
        selectLayer = systemLayer->getLayer<SelectLayer>( );
        stillLayer = systemLayer->getLayer<StillLayer>( );
        heartLayer = systemLayer->getLayer<HeartLayer>( );
        live2dLayer = systemLayer->getLayer<Live2dLayer>( );
        itemLayer = systemLayer->getLayer<ItemLayer>( );
        voiceLayer = systemLayer->getLayer<ItemLayer>( );
    }
    SCRIPT( ScriptSystem::l )
    {
        novelIndex = lineSize;
    }
    SCRIPT( ScriptSystem::select )
    {
        l( args );

        auto novel = dynamic_cast<NovelLayer*>( novelLayer );
        novel->systemStop.on( );

        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );


        Vector<MenuItem*> buttons;
        for ( size_t i = 0; i < args.size( ); ++i )
        {
            auto menuitem = MenuItemImage::create( u8"res/texture/system/select.base.png", u8"res/texture/system/select.select.png", [ = ] ( Ref* p )
            {
                novel->select( args[i] );
                novel->click( );
            } );

            auto scale = 1.0F / Director::getInstance( )->getContentScaleFactor( );
            menuitem->setScale( Lib::fitWidth( menuitem, 500 * scale ) );
            auto label = Label::createWithTTF( args[i], OptionalValues::fontName, OptionalValues::fontSize );
            label->setColor( Color3B( 39, 39, 39 ) );
            label->setPosition( menuitem->getContentSize( ) * 0.5 );
            label->setScale( 1.0 / Lib::fitWidth( menuitem, 500 * scale ) );
            menuitem->addChild( label );
            buttons.pushBack( menuitem );
        }

        if ( auto menu = Menu::createWithArray( buttons ) )
        {
            menu->setPosition( origin + visibleSize * 0.5F );
            menu->alignItemsVerticallyWithPadding( OptionalValues::fontSize );
            menu->setName( u8"select" );
            selectLayer->addChild( menu );
        }
    }
    SCRIPT( ScriptSystem::stop )
    {
        auto novel = dynamic_cast<NovelLayer*>( novelLayer );
        switch ( args.size( ) )
        {
        case 0:
            novel->setDelayTime( 1.0 );
            break;
        case 1:
            novel->setDelayTime( std::stod( args[0] ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::novelon )
    {
        isShowNovel = true;
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->on( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->on( );
    }
    SCRIPT( ScriptSystem::noveloff )
    {
        isShowNovel = false;
        if ( auto ptr = dynamic_cast<NameLayer*>( nameLayer ) ) ptr->off( );
        if ( auto ptr = dynamic_cast<NovelLayer*>( novelLayer ) ) ptr->off( );
    }
    SCRIPT( ScriptSystem::novelswitch )
    {
        if ( isShowNovel )
        {
            noveloff( args );
        }
        else
        {
            novelon( args );
        }
    }
    SCRIPT( ScriptSystem::item )
    {
        if ( auto ptr = dynamic_cast<ItemLayer*>( itemLayer ) )
        {
            ptr->make( args[0] );
        }
    }

    SCRIPT( ScriptSystem::name )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::string variable = args[0];
            std::string humanName = variable;
            auto pos = variable.find( u8"���O" );
            if ( pos != std::string::npos ) humanName = variable.substr( pos + std::string( u8"���O" ).size( ) );

            REGIST_VARIABLE( variable, new ScriptName( nameLayer, humanName, u8"F910MinchoW3.otf" ) );
        }
        break;
        case 2:
        {
            REGIST_VARIABLE( args[0], new ScriptName( nameLayer, args[1], u8"F910MinchoW3.otf" ) );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::background )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptBackground( backgroundLayer, args[0] + u8".png" ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::bgm )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::string file = u8"res/bgm/" + args[0];
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance( );
            audio->playBackgroundMusic( file.c_str( ) );
        }
        break;
        case 2:
        {
            std::string file = u8"res/bgm/" + args[0];
            bool loop = StringUtil::string_value<bool>( args[1] );
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance( );
            audio->playBackgroundMusic( file.c_str( ), loop );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::se )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            std::string file = u8"res/se/" + args[0];
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance( );
            audio->playEffect( file.c_str( ) );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::human )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptHuman( stillLayer, args[0] + u8".png" ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::still )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptStill( stillLayer, args[0] + u8".png" ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::heart )
    {
        switch ( args.size( ) )
        {
        case 1:
            REGIST_VARIABLE( args[0], new ScriptHeart( heartLayer ) );
            break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::live2d )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto model = args[0];
            auto dir = u8"res/live2d/" + model + u8"/";
            REGIST_VARIABLE( args[0], new ScriptLive2d( live2dLayer, model, dir ) );
        }
        break;
        default:
            break;
        }
    }
    SCRIPT( ScriptSystem::voice )
    {
        switch ( args.size( ) )
        {
        case 1:
        {
            auto var = args[0];
            auto dir = u8"res/voice/" + var + u8"/";
            REGIST_VARIABLE( var, new ScriptVoice( voiceLayer, dir ) );
        }
        break;
        default:
            break;
        }
    }
}
