#include "TextString.h"

#include "TextTypes.hpp"

USING_NS_CC;

namespace User
{
    float TextString::readOutSpeed = 0.1F;

    TextString::TextString( )
    {
        
    }
    TextString::~TextString( )
    {
    }
    void TextString::actionStart( )
    {
        setActionStart( label->getStringLength( ) );
    }
    void TextString::actionAndCallfuncStart( std::function<void( )> const & $actionCallfunc )
    {
        // �R�[���o�b�N�֐���o�^�B
        actionCallfunc = $actionCallfunc;

         // ��O����
         // ��s�������ꍇ�����񎩑̂��Ȃ����߂��̎��̍s�����݂��Ă��Ă��A�R�[���o�b�N�Ăяo�����ł����\���ł��Ȃ����߁B
        if ( text == u8"" )
        {
            actionCallfunc( );
            return;
        }

        // ������(�Ō�̕������܂܂Ȃ�)
        int stringIndex = label->getStringLength( ) - 1;

        // �Ō�̕����ȊO�͒ʏ�̏����B
        setActionStart( stringIndex );

        // ��ԍŌ�̕����������ʏ���
        // ���̕�����̃A�N�V�������Ō�̕������\�����ꂽ��Ɏn�߂܂��B
        auto oneString = label->getLetter( stringIndex );
        if ( oneString )
        {
            oneString->runAction( Sequence::create( DelayTime::create( readOutSpeed * stringIndex ),
                                                    Show::create( ),
                                                    DelayTime::create( readOutSpeed ),
                                                    CallFunc::create( [ this ] { actionCallfunc( ); } ),
                                                    nullptr ) )->setTag( stringIndex ); // action�ɂ͉������ڂ��̏������Ă����܂��B
        }
    }
    void TextString::actionStop( )
    {
        for ( int i = 0; i < label->getStringLength( ); i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString )
            {
                oneString->stopActionByTag( i );
                oneString->setVisible( true );
            }
        }
    }
    void TextString::layerPasting( cocos2d::Layer * layer )
    {
        layer->addChild( label );
    }
    void TextString::layerPeelOff( cocos2d::Layer * layer )
    {
        layer->removeChildByTag( (int)Tag::Novel );
    }
    void TextString::setReadOutSpeed( float $readOutSpeed )
    {
        readOutSpeed = $readOutSpeed;
    }
    void TextString::setLabelString( std::string const & text )
    {
        this->text = text;
        label = Label::createWithTTF( text, u8"fonts/F910MinchoW3.otf", 36.0F );
        label->setTextColor( Color4B::WHITE );
        label->setTag( (int)Tag::Novel );
        for ( int i = 0; i < label->getStringLength( ); i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString ) oneString->setVisible( false );
        }
    }
    void TextString::setDrawPosition( cocos2d::Vec2 position )
    {
        auto size = label->getContentSize( );

        label->setPosition( position + Vec2( size.width / 2, 0 ) );
    }
    void TextString::setActionStart( size_t $stringLength )
    {
        for ( int i = 0; i < $stringLength; i++ )
        {
            auto oneString = label->getLetter( i );
            if ( oneString )
            {
                oneString->runAction( Sequence::create( DelayTime::create( readOutSpeed * i ),
                                                        Show::create( ),
                                                        nullptr ) )->setTag( i );
            }
        }
    }
}
