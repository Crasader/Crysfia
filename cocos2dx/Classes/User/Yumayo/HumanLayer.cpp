#include "HumanLayer.h"

#include "ScriptHuman.h"
#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    HumanLayer::HumanLayer( )
    {

    }
    HumanLayer::~HumanLayer( )
    {

    }
    bool HumanLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        addTexture( "chloe.png" );
        ScriptStaticData::addData( std::make_pair( u8"クロエ画像", std::make_unique<ScriptHuman>( this, u8"chloe.png" ) ) );
        addTexture( "allen.png" );
        ScriptStaticData::addData( std::make_pair( u8"アレン画像", std::make_unique<ScriptHuman>( this, u8"allen.png" ) ) );

        return true;
    }
    void HumanLayer::setup( )
    {

    }
    void HumanLayer::addTexture( std::string texturePath )
    {
        Director::getInstance( )->getTextureCache( )->addImage( "res/texture/" + texturePath );
    }
}
