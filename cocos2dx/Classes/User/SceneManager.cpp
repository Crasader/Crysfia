#include "SceneManager.h"
#include "LayerBase.h"

// scenario�Ɏg����ϐ��̃T�C�Y�Ȃǂ̏������B
#include "Yumayo/OptionalValues.h"

// �T���v���V�[�����쐬���܂��B
#include "Sample/SceneSample.h"

// ���[�}���V�[�����쐬���܂��B
#include "Yumayo/SceneYumayo.h"

// ���}�b�v�V�[�����쐬���܂��B
#include "IslandMap/SceneIslandMap.h"

// ��������̃z�[���V�[�����쐬���܂��B
#include "Breeding/SceneBreeding.h"

// ��������̃^�C�g���V�[����ǉ����܂��B
#include "Title/SceneTitle.h"

USING_NS_CC;

namespace User
{
    void SceneManager::createSystemAppDelegateStart( )
    {
        OptionalValues::setup( );

        createIslandMap( );
    }
    void SceneManager::createTitle( )
    {
        create<SceneTitle>( );
    }
    void SceneManager::createSample( )
    {
        create<SceneSample>( );
    }
    void SceneManager::createYumayo( )
    {
        create<SceneYumayo>( );
    }
    void SceneManager::createIslandMap( )
    {
        create<SceneIslandMap>( );
    }
    void SceneManager::createBreeding( )
    {
        create<SceneBreeding>( );
    }
    void SceneManager::childrenCallSetup( cocos2d::Scene* scene )
    {
        auto children = scene->getChildren( );
        for ( auto child : children )
        {
            if ( auto childLayer = dynamic_cast<LayerBase*>( child ) )
            {
                childLayer->setup( );
            }
            else
            {
                log( "dynamic_cast is failed : Layer[%s]", child->getName( ).c_str( ) );
            }
        }
    }
}
