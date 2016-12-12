# ifndef __LayerIsland__
# define __LayerIsland__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    struct CityPointData
    {
        /**
         *  �f�[�^�̏��������s���܂��B
         *  �\���ɕK�v�ȃf�[�^�����l�߂܂��B
         */
        void initData( cocos2d::Vec2 const& position, std::string const& path )
        {
            this->position = position;
            this->path = path;
        }

        /**
         *  �f�[�^�̏��������s���܂��B
         *  �R�s�[������Ă��̂܂ܑ�����܂��B
         */
        void initData( CityPointData const& scenario ) { *this = scenario; }

        /**
         *  �}�b�v�摜���̕\���ʒu�B
         */
        cocos2d::Vec2 position;

        /**
         *  ���̏��B
         */
        std::string path;
    };

    class LayerIslandMark : protected CityPointData, public cocos2d::ui::Button
    {
    protected:
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class CityMark : public LayerIslandMark
    {
    public:
        CREATE_FUNC( CityMark );
        void pasteMap( cocos2d::Sprite* map, CityPointData const& data );
    };

    class IslandMap : public cocos2d::Sprite
    {
    public:
        CREATE_FUNC( IslandMap );
        IslandMap* make( );
        /**
        *  �؍ݒ��̓�
        */
        enum Islands
        {
            none,
            first,
            second,
            third,
            forth,
            fifth,
        };

        /**
        *  ���̎��ԁB
        */
        enum Times
        {
            morning,
            daytime,
            night
        };
    private:
        Islands islands = Islands::none;

        Times times = Times::morning;

        /**
         *  �}�b�v�����ɃX���C�h����Ƃ��Ɏg���܂��B
         */
        cocos2d::Vec2 translate;
    };

    class LayerIsland : public LayerBase
    {
    public:
        CREATE_FUNC( LayerIsland );
        LayerIsland( );
        ~LayerIsland( );
        bool init( ) override;
        void setup( ) override;
    private:
        void movePoint( cocos2d::Sprite* map, cocos2d::Vec2 start, cocos2d::Vec2 end, std::string path );
    };
}

# endif // __LayerIsland__
