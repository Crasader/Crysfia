﻿# ifndef __SceneManager__
# define __SceneManager__

# include "cocos2d.h"

# include <string>
# include "../Lib/json.h"

namespace User
{
    class SceneManager
    {
    public:
        static void createSystemAppDelegateStart( );
    public:
        static void createTitle( );
        static void createNovel( std::string const& scenario, std::function<void()> const& saveCallFunc );
        static void createCityMap( );
        static void createBreeding( );
        static void createDiary( );
        static void createIshibashi( );
    private:
        static void childrenCallSetup( cocos2d::Scene* scene );
        template <typename Ty>
        static void create( );
        template <typename Ty, typename... Args>
        static void create( Args... args );
        template <typename Ty, typename TyTranstion, typename ...TyTranstionArgs>
        static void create( TyTranstionArgs... tyTranstionArgs );
    };

    template<typename Ty>
    inline void SceneManager::create( )
    {
        auto scene = Ty::create( );

        childrenCallSetup( scene );

        cocos2d::Director::getInstance( )->replaceScene( scene );
    }
    template<typename Ty, typename... Args>
    inline void SceneManager::create( Args... args )
    {
        auto scene = Ty::create( args... );

        childrenCallSetup( scene );

        cocos2d::Director::getInstance( )->replaceScene( scene );
    }
    template<typename Ty, typename TyTranstion, typename ...TyTranstionArgs>
    inline void SceneManager::create( TyTranstionArgs... tyTranstionArgs )
    {
        Ty base;
        auto scene = base.create( );

        childrenCallSetup( scene );

        auto transtion = TyTranstion::create( tyTranstionArgs..., scene );

        cocos2d::Director::getInstance( )->replaceScene( transtion );
    }
}

# endif // __SceneManager__
