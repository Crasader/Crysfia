/**
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
#include "SampleLive2DSprite.h"
#include "base/CCDirector.h"
#include "util/UtSystem.h"

#include "graphics/DrawProfileCocos2D.h"
#include "platform/CCFileUtils.h"

using namespace live2d;
USING_NS_CC;
const char* TEXTURES [ ] = {
    "res/epsilon/Epsilon2.1.2048/texture_00.png" ,
    NULL
};
SampleLive2DSprite::SampleLive2DSprite( )
    : live2DModel( nullptr )
{
}

SampleLive2DSprite::~SampleLive2DSprite( )
{
    delete live2DModel;
    // �e�N�X�`�������
    Director::getInstance( )->getTextureCache( )->removeTextureForKey( std::string( TEXTURES[0] ) );

}

bool SampleLive2DSprite::init( )
{
    if ( DrawNode::init( ) )
    {
        if ( live2DModel != nullptr )
        {
            delete live2DModel;
            live2DModel = nullptr;
        }

        const char* MODEL = "res/epsilon/Epsilon2.1.moc";

        unsigned char* buf;
        ssize_t bufSize;
        buf = FileUtils::getInstance( )->getFileData( MODEL, "rb", &bufSize );

        live2DModel = Live2DModelOpenGL::loadModel( buf, bufSize );
        free( buf );

        auto chacheMgr = Director::getInstance( )->getTextureCache( );
        for ( int i = 0; TEXTURES[i] != NULL; i++ )
        {
            Texture2D* texture = chacheMgr->addImage( TEXTURES[i] );

            Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
            texture->setTexParameters( texParams );
            texture->generateMipmap( );

            int glTexNo = texture->getName( );

            live2DModel->setTexture( i, glTexNo );// �e�N�X�`���ƃ��f�������т���
        }

        // Live2D���f���̓��[�J�����W�ō�������_�ɂ���(CanvasWidth�ACanvasWidth)
        // �̃T�C�Y�ɂȂ邽�߁A�ȉ��̂悤�ɂ��Ē������Ă��������B
        float w = Director::getInstance( )->getWinSize( ).width;
        float h = Director::getInstance( )->getWinSize( ).height;
        float scx = 2.0 / live2DModel->getCanvasWidth( );
        float scy = -2.0 / live2DModel->getCanvasWidth( ) * ( w / h );
        float x = -1;
        float y = 1;
        float matrix [ ] = {
            scx , 0 , 0 , 0 ,
            0 , scy ,0 , 0 ,
            0 , 0 , 1 , 0 ,
            x , y , 0 , 1
        };

        live2DModel->setMatrix( matrix );// �ʒu��ݒ�

        live2DModel->setPremultipliedAlpha( true );
    }

    return true;
}

void SampleLive2DSprite::draw( cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags )
{
    DrawNode::draw( renderer, transform, flags );


    _customCommand.init( _globalZOrder );
    _customCommand.func = CC_CALLBACK_0( SampleLive2DSprite::onDraw, this, transform, flags );
    renderer->addCommand( &_customCommand );
}

void SampleLive2DSprite::onDraw( const cocos2d::Mat4 &transform, uint32_t flags )
{
    kmGLPushMatrix( );
    kmGLLoadMatrix( &transform );


    // ���f���̃p�����[�^��ύX�B����m�F�p�ł��B
    double t = ( UtSystem::getUserTimeMSec( ) / 1000.0 ) * 2 * M_PI;// 1�b���Ƃ�2��(1����)������
    double cycle = 3.0;// �p�����[�^��������鎞��(�b)
    double value = sin( t / cycle );// -1����1�̊Ԃ��������Ƃɕω�����
    live2DModel->setParamFloat( "PARAM_ANGLE_X", (float)( 30 * value ) );// PARAM_ANGLE_X�̃p�����[�^��[cycle]�b���Ƃ�-30����30�܂ŕω�����


                                                                         // Live2D�̕`��O�ƕ`���Ɉȉ��̊֐����Ă�ł�������
                                                                         // live2d::DrawProfileCocos2D::preDraw() ;
                                                                         // live2d::DrawProfileCocos2D::postDraw() ;
                                                                         // �����OpenGL�̏�Ԃ����Ƃɖ߂����߂̏����ł��B
                                                                         // ������s��Ȃ��ꍇ�ACocos2D��Live2D�ǂ��炩�ŏ�Ԃ̕s�������N����܂��B
    live2d::DrawProfileCocos2D::preDraw( );

    live2DModel->update( );
    live2DModel->draw( );

    live2d::DrawProfileCocos2D::postDraw( );

    kmGLPopMatrix( );
}

SampleLive2DSprite* SampleLive2DSprite::createDrawNode( )
{
    SampleLive2DSprite *ret = new SampleLive2DSprite( );
    if ( ret && ret->init( ) )
    {
        ret->autorelease( );
        return ret;
    }
    else
    {
        CC_SAFE_DELETE( ret );
        return nullptr;
    }


}
