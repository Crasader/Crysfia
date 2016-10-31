#include "LayerIsland.h"

#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
    LayerIsland::LayerIsland( )
    {

    }
    LayerIsland::~LayerIsland( )
    {

    }
    //�u���b�N�I�u�W�F�N�g�쐬  
    /*LayerColor * LayerIsland::createBlockLayer( const char *strlabel, Color3B fontColor, Color4B backColor )
    {
        LayerColor * ret = LayerColor::create( backColor, 128, 128 );
        CCLabelTTF *Label = CCLabelTTF::create( strlabel, "Arial-BoldMT", 28, CCSizeMake( 128, 128 ), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter );
        Label->setColor( fontColor );
        Label->setAnchorPoint( CCPointZero );
        ret->addChild( Label );
        return ret;
    }*/

    bool LayerIsland::init( )
    {
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto label = Label::createWithTTF( u8"LayerIsland", "res/fonts/Marker Felt.ttf", 24 );
        label->setPosition( origin + Vec2( visibleSize.width / 2,
                                           visibleSize.height - label->getContentSize( ).height * 2 ) );
        this->addChild( label, 1000 );

        this->scheduleUpdate( );

        ////���j���[�{�^���I�u�W�F�쐬  
        //Array *menuItems = Array::create( );

        ////STAGE  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "STARGE", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0xFF ) ) ) );
        ////�I�N�g�p�X  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�I�N�g�p�X", ccc3( 0xFF, 0x7F, 0x7F ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////�y���M��  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�y���M��", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////MAP  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "MAP", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0x7F ) ) ) );
        ////�A���}�W��  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�A���}�W��", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////NOP  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        ////�G���t�@���g  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�G���t�@���g", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////�t�@���R��  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�t�@���R��", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////NOP  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "", ccc3( 0x00, 0x00, 0x00 ), ccc4( 0xFF, 0xFF, 0xFF, 0x7F ) ) ) );
        ////�N���K�^  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�N���K�^", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////SPEC  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "SPEC", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0x7F ) ) ) );
        ////�}���g�q�q  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�}���g�q�q", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////�J�����I��  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "�J�����I��", ccc3( 0xFF, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0xFF, 0xFF ) ) ) );
        ////WONDER  
        //menuItems->addObject( CCMenuItemLabel::create( createBlockLayer( "WONDER", ccc3( 0x00, 0xFF, 0x00 ), ccc4( 0x7F, 0x7F, 0x7F, 0x7F ) ) ) );

        //Menu *menu = Menu::createWithArray( menuItems );
        //this->addChild( menu );

        ////�{�^�������ɐ��ڂ���  
        //menu->alignItemsHorizontallyWithPadding( 0 );

        ////�{�^�����c�ɐ��ڂ���  
        //menu->alignItemsVerticallyWithPadding( 0 );

        ////�z�u  
        //menu->alignItemsInColumns( 4, 4, 4, 4 );

        return true;
    }
    void LayerIsland::setup( )
    {
        
    }
    void LayerIsland::update( float delta )
    {
        SceneManager::createYumayo( );
    }
}
