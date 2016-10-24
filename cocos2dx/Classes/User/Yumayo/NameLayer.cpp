#include "NameLayer.h"

#include "ScriptName.h"
#include "ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    NameLayer::NameLayer( )
    {

    }
    NameLayer::~NameLayer( )
    {

    }
    bool NameLayer::init( )
    {
        if ( !Layer::init( ) ) return false;

        setName( typeid( *this ).name( ) );

        ScriptStaticData::addData( std::make_pair( u8"�N���G���O", std::make_unique<ScriptName>( this, u8"�N���G", u8"F910MinchoW3.otf" ) ) );
        ScriptStaticData::addData( std::make_pair( u8"�A�������O", std::make_unique<ScriptName>( this, u8"�A����", u8"F910MinchoW3.otf" ) ) );

        return true;
    }
    void NameLayer::setup( )
    {
        
    }
}
