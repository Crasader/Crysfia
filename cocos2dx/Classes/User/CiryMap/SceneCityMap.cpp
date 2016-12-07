#include "SceneCityMap.h"

#include "LayerCity.h"

#include "../Novel/HeartLayer.h"

#include "../Novel/SystemLayer.h"
#include "../Novel/ScriptSystem.h"
#include "../Novel/ScriptStaticData.h"

USING_NS_CC;

namespace User
{
    cocos2d::Scene* SceneCityMap::create( std::string const & backgroundPath )
    {
        auto scene = Scene::create( );

        scene->addChild( createLayer<HeartLayer>( ), (int)Tag::Heart );

        // �V�X�e�����C���[�̓o�^
        // �S�ẴX�N���v�g���i��"sys"�͏������̎��_�œo�^�����܂��B
        auto system = createLayer<SystemLayer>( );
        scene->addChild( system, (int)Tag::System );
        auto script = new ScriptSystem( system );
        script->setup( );
        REGIST_VARIABLE( u8"sys", script );

        auto data = UserDefault::getInstance( );
        auto �D���x = data->getFloatForKey( u8"�D���x" );
        �D���x += 0.1;
        data->setFloatForKey( u8"�D���x", �D���x );

        scene->addChild( createLayer<LayerCity>( backgroundPath ) );

        return scene;
    }
}
