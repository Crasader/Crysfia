#include "ScriptStaticData.h"

#include "ScriptSystem.h"

#include "NameLayer.h"
#include "ScriptName.h"

#include "HumanLayer.h"
#include "ScriptHuman.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene* ScriptStaticData::scene = nullptr;
    std::map<std::string, std::shared_ptr<ScriptBase>> ScriptStaticData::data;

    ScriptStaticData::ScriptStaticData( cocos2d::Scene* scene )
    {
        ScriptStaticData::scene = scene;

        Director::getInstance( )->getTextureCache( )->addImage( "fia.png" );

        auto nameLayer = dynamic_cast<Layer*>( scene->getChildByName( typeid( NameLayer ).name( ) ) );
        auto humanLayer = dynamic_cast<Layer*>( scene->getChildByName( typeid( HumanLayer ).name( ) ) );

        data =
        {
            std::make_pair( u8"sys", std::make_shared<ScriptSystem>( ) ),
            std::make_pair( u8"�N���G", std::make_shared<ScriptName>( nameLayer, u8"�N���G" ) ),
            std::make_pair( u8"�A����", std::make_shared<ScriptName>( nameLayer, u8"�A����" ) ),

            std::make_pair( u8"human�N���G", std::make_shared<ScriptHuman>( humanLayer, "fia.png" ) ),
            std::make_pair( u8"human�A����", std::make_shared<ScriptHuman>( humanLayer, "fia.png" ) ),
        };
    }
    ScriptStaticData::~ScriptStaticData( )
    {

    }
    void ScriptStaticData::run( FunctionScriptChip const& functionScriptChip )
    {
        auto itr = data.find( functionScriptChip.variable );
        if ( itr != data.cend( ) )
        {
            itr->second->run( functionScriptChip.functionInfo );
        }
    }
}
