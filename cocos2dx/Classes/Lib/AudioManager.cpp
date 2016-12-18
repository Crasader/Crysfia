/****************************************************************************
Copyright (c) 2016 Yuji Toki(tokineco)
- MIT license
****************************************************************************/

#include "audio/include/AudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"

#include "AudioManager.h"

USING_NS_CC;
using namespace experimental;

AudioManager* AudioManager::_instance = nullptr;
cocos2d::Scheduler* AudioManager::_scheduler = nullptr;

// �R���X�g���N�^
AudioManager::AudioManager( )
    : _audioListFile( "" )
    , _bgmVolume( 0.0F )
    , _seVolume( 0.0F )
    , _fadeCondition( FadeType::NONE )
    , _bgmFadeVolumeNow( 0 )
    , _bgmFadeVolumeFrom( 0 )
    , _bgmFadeVolumeTo( 0 )
    , _bgmFadeTime( 0 )
    , _stopBgmReleaseFlg( true )
    , _voiceVolume( 0.0F )
{
    // �`�����N�z��̏�����
    for ( int i = 0; i < sizeof( _chunk ) / sizeof( _chunk[0] ); i++ ) {
        _chunk[i] = AudioEngine::INVALID_AUDIO_ID;
    }
}

// �f�X�g���N�^
AudioManager::~AudioManager( ) {
    CC_SAFE_RELEASE_NULL( _scheduler );
}

// ������
AudioManager* AudioManager::getInstance( ) {

    if ( _instance == nullptr ) {
        _instance = new AudioManager( );

        // �X�P�W���[�����C���X�^���X�ɒǉ����Aupdate���Ăяo����悤�ɂ���
        _scheduler = Director::getInstance( )->getScheduler( );
        _scheduler->retain( );
        _scheduler->scheduleUpdate( _instance, 0, false );
    }

    return _instance;
}

// �폜����ۂɎg�p
void AudioManager::deleteInstance( ) {

    if ( _instance != nullptr ) {
        delete _instance;
    }

    _instance = nullptr;
}


// �I�[�f�B�I�Ǘ��t�@�C����ǂݍ���
bool AudioManager::readAudioListFile( std::string const& fileName ) {

    // Resource�̒��ɂ���t�@�C����ǂݍ���
    // �t�@�C���ǂݍ���
    std::string strData = FileUtils::getInstance( )->getStringFromFile( fileName );

    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>( strData.c_str( ) );

    if ( doc.HasParseError( ) ) {
        // ��̓G���[
        CCLOG( "JSON parse error." );
        return false;
    }

    if ( doc.IsObject( ) ) {

        CCLOG( "%s", strData.c_str( ) );

        // ������
        _bgmList.clear( );
        _bgmLoopList.clear( );
        _seList.clear( );
        _voiceList.clear( );

        // BGM
        rapidjson::Value& bgms = doc["BGM"];

        // �L�[�ƒl�����X�g�ɓo�^����
        for ( rapidjson::Value::ConstMemberIterator it = bgms.MemberBegin( ); it != bgms.MemberEnd( ); it++ ) {
            std::string key = it->name.GetString( );
            const rapidjson::Value& value = it->value;
            // �ʏ�̃t�@�C���p�X�̏ꍇ
            if ( value.GetType( ) == rapidjson::kStringType ) {
                _bgmList[key] = value.GetString( );
            }
            // �z��̏ꍇ
            else if ( value.GetType( ) == rapidjson::kArrayType ) {

                    // 1�Ԗڂ̓t�@�C���p�X
                _bgmList[key] = value[0].GetString( );
                // 2�Ԗڂ̓��[�v��̍Đ��J�n�ʒu
                if ( value.Size( ) > 1 ) {
                    _bgmLoopList[key].startPos = (float)( value[1].GetDouble( ) );
                }
                // 3�Ԗڂ̓��[�v�I�[�ʒu
                if ( value.Size( ) > 2 ) {
                    _bgmLoopList[key].endPos = (float)( value[2].GetDouble( ) );
                }

            }
        }

        // SE
        rapidjson::Value& ses = doc["SE"];
        // �L�[�ƒl�����X�g�ɓo�^����
        for ( rapidjson::Value::ConstMemberIterator it = ses.MemberBegin( ); it != ses.MemberEnd( ); it++ ) {
            std::string key = it->name.GetString( );
            const rapidjson::Value& value = it->value;
            if ( value.GetType( ) == rapidjson::kStringType ) {
                _seList[key] = value.GetString( );
            }
        }

        // VOICE
        rapidjson::Value& voices = doc["VOICE"];
        // �L�[�ƒl�����X�g�ɓo�^����
        for ( rapidjson::Value::ConstMemberIterator it = voices.MemberBegin( ); it != voices.MemberEnd( ); it++ ) {
            std::string key = it->name.GetString( );
            const rapidjson::Value& value = it->value;
            if ( value.GetType( ) == rapidjson::kStringType ) {
                _voiceList[key] = value.GetString( );
            }
        }

        // ���݂̃t�@�C�����Z�b�g
        _audioListFile = fileName;


        /**
         * �{�����[���ނ̏�����
         */
        _bgmVolume = UserDefault::getInstance( )->getFloatForKey( u8"bgm" );
        _seVolume = UserDefault::getInstance( )->getFloatForKey( u8"se" );
        _voiceVolume = UserDefault::getInstance( )->getFloatForKey( u8"voice" );

        return true;
    }
    return false;
}

// �[�����Ƃɓǂݍ��ފg���q��ς��āA���̃t�@�C������Ԃ�
std::string AudioManager::getFileName( AudioType type, std::string baseName ) {

    // �I�[�f�B�I�Ǘ��t�@�C�����g���ꍇ�A�L�[����t�@�C�������擾����
    if ( _audioListFile != "" ) {

        /**
         * �Ǘ���switch������Ȃ������̂ŏ��������B
         */
        switch ( type )
        {
        case AudioType::BGM:
            if ( _bgmList.count( baseName ) != 0 ) {
                baseName = _bgmList[baseName];
            }
            break;
        case AudioType::SE:
            if ( _seList.count( baseName ) != 0 ) {
                baseName = _seList[baseName];
            }
            break;
        case AudioType::VOICE:
            if ( _voiceList.count( baseName ) != 0 ) {
                baseName = _voiceList[baseName];
            }
            break;
        default:
            break;
        }
    }

    /**
     * �v���b�g�t�H�[�����Ƃ̐��b�Ă��͂Ȃ����āA�t�@�C������������Ȃ������ꍇ�́A���̂܂ܕԂ��܂��B
     */
        // ������Ȃ���΁A���̐�ŃG���[�Ƃ���
    return baseName;
}

// AudioEngine�S�ẴL���b�V�����폜����
void AudioManager::releaseAll( ) {
    AudioEngine::uncacheAll( );
}

// ���t���[�����s
void AudioManager::update( float dt ) {

    // �t�F�[�h�C���A�A�E�g�����s����
    switch ( _fadeCondition ) {
    case FadeType::FADE_IN:
    case FadeType::FADE_IN_RESUME:
        // 0���Z���
        if ( _bgmFadeTime == 0 ) {
            _bgmFadeTime = 0.01f;
        }
        // dt���Ԍ�̑����{�����[�������߂�B _bgmVolume:_bgmFadeTime = dV : dt
        _bgmFadeVolumeNow += ( dt * ( _bgmFadeVolumeTo - _bgmFadeVolumeFrom ) ) / _bgmFadeTime;

        if ( _bgmFadeVolumeNow >= _bgmFadeVolumeTo ) {
            _bgmFadeVolumeNow = _bgmFadeVolumeTo;
            _bgmFadeVolumeFrom = _bgmFadeVolumeTo;
            _fadeCondition = FadeType::NONE;
        }

        this->setBgmVolume( _bgmFadeVolumeNow, false );
        break;
    case FadeType::FADE_OUT:
    case FadeType::FADE_OUT_PAUSE:
        // 0���Z���
        if ( _bgmFadeTime == 0 ) {
            _bgmFadeTime = 0.01f;
        }
        // dt���Ԍ�̌����{�����[�������߂�B _bgmVolume:_bgmFadeTime = dV : dt
        _bgmFadeVolumeNow += ( dt * ( _bgmFadeVolumeTo - _bgmFadeVolumeFrom ) ) / _bgmFadeTime;

        if ( _bgmFadeVolumeNow <= _bgmFadeVolumeTo ) {
            _bgmFadeVolumeNow = _bgmFadeVolumeTo;
            _bgmFadeVolumeFrom = _bgmFadeVolumeTo;

            if ( _fadeCondition == FadeType::FADE_OUT ) {
                // stopBgm�����s
                stopBgm( 0, _stopBgmReleaseFlg );
            }
            else if ( _fadeCondition == FadeType::FADE_OUT_PAUSE ) {
             // pauseBgm�����s
                pauseBgm( 0 );
            }

            _fadeCondition = FadeType::NONE;
        }

        this->setBgmVolume( _bgmFadeVolumeNow, false );
        break;
    default:
        break;
    }

    // ���[�v�`�F�b�N
    if ( this->isPlayingBgm( ) && _bgmLoopList.count( _bgmFileName ) > 0 ) {

        std::string fileName = getFileName( AudioType::BGM, _bgmFileName );

        if ( fileName != "" ) {
            // ���݂�BGM�����擾
            float currentTime = AudioEngine::getCurrentTime( _bgmId );    // ���݂̈ʒu
            float duration = AudioEngine::getDuration( _bgmId );                  // �I�[�f�B�I�̒���

            // ��Ԑݒ���
            float startPos = _bgmLoopList[_bgmFileName].startPos;
            float endPos = duration;
            // �J�n�ʒu�𒴂��Ă�����A��ԓ��t���O�𗧂Ă�
            if ( !_bgmLoopList[_bgmFileName].isLoopInterval && currentTime > startPos ) {
                _bgmLoopList[_bgmFileName].isLoopInterval = true;
            }
            if ( _bgmLoopList[_bgmFileName].endPos > 0 ) {
                endPos = _bgmLoopList[_bgmFileName].endPos;
                if ( endPos > duration ) {
                    endPos = duration;
                }
            }

            if ( endPos <= 0 ) {
                return;
            }

            if (// 2��ڈȍ~�Ȃ̂ɁA���[�v�J�n�n�_���O�ɂ�������
                ( _bgmLoopList[_bgmFileName].isLoopInterval && currentTime < startPos - 0.4f )
                // �܂��́AendPos���I�[�߂��ł͂Ȃ��āAendPos�𒴂��Ă���ꍇ
                 || ( duration - endPos >= 0.2f && currentTime >= endPos ) ) {

                CCLOG( "bgm end. current time is %f sec.", currentTime );
                AudioEngine::setCurrentTime( _bgmId, startPos );
            }
        }
    }

}


// BGM��SE�̉��ʂ̏�����
void AudioManager::initVolume( float bgmVolume, float seVolume ) {
    _bgmVolume = bgmVolume;
    _seVolume = seVolume;
}

// ���o�C���f�o�C�X���ǂ���
bool AudioManager::isMobileDevice( ) {
    auto platform = Application::getInstance( )->getTargetPlatform( );
    if ( platform == cocos2d::ApplicationProtocol::Platform::OS_ANDROID
         || platform == cocos2d::ApplicationProtocol::Platform::OS_IPHONE
         || platform == cocos2d::ApplicationProtocol::Platform::OS_IPAD ) {
        return true;
    }

    return false;
}

//===================
// BGM
//===================

// BGM��PreLoad
void AudioManager::preloadBgm( std::string const& baseName ) {

    std::string fileName = getFileName( AudioType::BGM, baseName );
    if ( fileName == "" ) {
        return;
    }

    AudioEngine::preload( fileName );

}

// BGM�̍Đ�
int AudioManager::playBgm( std::string const& baseName, float fadeTime /* =0*/, bool loop /* = true*/ ) {
    return playBgm( baseName, fadeTime, loop, _bgmVolume );
}
// BGM�̍Đ�
int AudioManager::playBgm( std::string const& baseName, float fadeTime, bool loop, float volume ) {

    int soundId = AudioEngine::INVALID_AUDIO_ID;

    std::string fileName = getFileName( AudioType::BGM, baseName );
    if ( fileName == "" ) {
        return soundId;
    }

    if ( _bgmFileName == baseName && AudioEngine::getState( _bgmId ) == AudioEngine::AudioState::PLAYING ) {
        // �O��Ɠ����t�@�C�����ŁA�Đ����̏ꍇ�͖�������
        return _bgmId;
    }

    // �O���BGM���~
    stopBgm( );

    // �t�F�[�h�w��̏ꍇ
    if ( fadeTime != 0 ) {
        _fadeCondition = FadeType::FADE_IN;
        _bgmFadeVolumeNow = 0;
        _bgmFadeVolumeFrom = 0;
        _bgmFadeTime = fadeTime;
    }
    else {
        _fadeCondition = FadeType::NONE;
        _bgmFadeVolumeNow = volume;
    }
    _bgmFadeVolumeTo = volume;

    _bgmId = AudioEngine::play2d( fileName, loop, volume );

    if ( loop ) {
        // FinishCallback �� ���[�v���ɂ͎��s����Ȃ�
        // ���s�������̂ݎ��s�����
        AudioEngine::setFinishCallback( _bgmId, [ this, loop, volume ] ( int bgmId, std::string fileName ) {
            stopBgm( 0, false );
            _bgmId = playBgm( _bgmFileName, 0, loop, volume );
        } );
    }

    _bgmFileName = baseName;

    if ( _bgmLoopList.count( _bgmFileName ) > 0 ) {
        _bgmLoopList[_bgmFileName].isLoopInterval = false;
    }

    return _bgmId;
}

// BGM���ꎞ��~����
void AudioManager::pauseBgm( float fadeTime /*= 0*/ ) {

    _bgmFadeVolumeTo = 0;

    if ( fadeTime != 0 ) {
        // �t�F�[�h�w��̏ꍇ
        _fadeCondition = FadeType::FADE_OUT_PAUSE;
        _bgmFadeVolumeNow = _bgmVolume;
        _bgmFadeVolumeFrom = _bgmVolume;
        _bgmFadeTime = fadeTime;
    }
    else {
     // �t�F�[�h�Ȃ��̏ꍇ
        _fadeCondition = FadeType::NONE;
        _bgmFadeVolumeNow = 0;

        pauseBgmEngine( );
    }

}

// pauseBgm�̎��s(fade�Ȃ��A�܂���update�ɂ��t�F�[�h��Ɏ��s�����)
void AudioManager::pauseBgmEngine( ) {
    AudioEngine::pause( _bgmId );
}

// BGM�����W���[���Đ�����
void AudioManager::resumeBgm( float fadeTime /*=0*/ ) {

    // �t�F�[�h�w��̏ꍇ
    if ( fadeTime != 0 ) {
        _fadeCondition = FadeType::FADE_IN_RESUME;
        _bgmFadeVolumeNow = 0;
        _bgmFadeVolumeFrom = 0;
        _bgmFadeTime = fadeTime;
    }
    else {
        _fadeCondition = FadeType::NONE;
        _bgmFadeVolumeNow = _bgmVolume;
    }
    _bgmFadeVolumeTo = _bgmVolume;

    AudioEngine::resume( _bgmId );
}

// BGM���~����
void AudioManager::stopBgm( float fadeTime /*= 0*/, bool release /* = true */ ) {

    _bgmFadeVolumeTo = 0;

    if ( fadeTime != 0 ) {
        // �t�F�[�h�w��̏ꍇ
        _fadeCondition = FadeType::FADE_OUT;
        _bgmFadeVolumeNow = _bgmVolume;
        _bgmFadeVolumeFrom = _bgmVolume;
        _bgmFadeTime = fadeTime;
        _stopBgmReleaseFlg = release;
    }
    else {
     // �t�F�[�h�Ȃ��̏ꍇ
        _fadeCondition = FadeType::NONE;
        _bgmFadeVolumeNow = 0;

        stopBgmEngine( release );
    }
}

// stopBgm�̎��s(fade�Ȃ��A�܂���update�ɂ��t�F�[�h��Ɏ��s�����)
void AudioManager::stopBgmEngine( bool release /* = true */ ) {

    AudioEngine::stop( _bgmId );

    // �L���b�V�����
    if ( release ) {
        releaseBgm( );
    }

    _bgmId = AudioEngine::INVALID_AUDIO_ID;
    _bgmFileName = "";

}

// BGM���Đ�����Ă��邩�ǂ���
bool AudioManager::isPlayingBgm( ) {

    if ( _bgmFileName == "" ) {
        return false;
    }

    std::string fileName = getFileName( AudioType::BGM, _bgmFileName );

    AudioEngine::AudioState state = AudioEngine::getState( _bgmId );
    if ( state == AudioEngine::AudioState::PLAYING ) {
        return true;
    }

    return false;
}

// BGM�̉��ʂ�ύX����
void AudioManager::setBgmVolume( float volume, bool save /* = true */ ) {

    // �ϐ��ێ��t���O��on�̏ꍇ�͕ϐ���؂�ւ���
    if ( save ) {
        _bgmVolume = volume;
    }

    AudioEngine::setVolume( _bgmId, volume );
}

// BGM�̉��ʂ��擾����
float AudioManager::getBgmVolume( ) {
    return _bgmVolume;
}

// BGM�̃L���V�����������
void AudioManager::releaseBgm( ) {
    auto fileName = getFileName( AudioType::BGM, _bgmFileName );
    AudioEngine::uncache( fileName );
}

//===================
// SE
//===================

// ���ʉ���PreLoad
void AudioManager::preloadSe( std::string const& baseName ) {

    std::string fileName = getFileName( AudioType::SE, baseName );
    if ( fileName == "" ) {
        return;
    }
    AudioEngine::preload( fileName );
}

// ���ʉ����Đ�����
int AudioManager::playSe( std::string const& baseName, int chunkNo ) {
    return this->playSe( baseName, chunkNo, false, _seVolume );
}
// ���ʉ����Đ�����
int AudioManager::playSe( std::string const& baseName, int chunkNo, bool loop, float volume ) {

    int soundId = AudioEngine::INVALID_AUDIO_ID;
    bool chunkFlag = false;

    std::string fileName = getFileName( AudioType::SE, baseName );
    if ( fileName == "" ) {
        return soundId;
    }

    // �`�����N���w�肳��Ă�����
    if ( chunkNo >= 0 && chunkNo < sizeof( _chunk ) / sizeof( _chunk[0] ) ) {
        chunkFlag = true;

        // �w��`�����N�̍Đ����̉����~
        this->stopSe( _chunk[chunkNo] );
    }

    soundId = AudioEngine::play2d( fileName, loop, volume );

    if ( chunkFlag ) {
        // �`�����N��SoundId��o�^
        _chunk[chunkNo] = soundId;
    }

    return soundId;

}
// ���ʉ����Đ�����
int AudioManager::playSe( std::string const& baseName, bool loop, float volume ) {

    return this->playSe( baseName, -1, loop, volume );
}
// ���ʉ����Đ�����
int AudioManager::playSe( std::string const& baseName, bool loop /* = false */ ) {
    return this->playSe( baseName, loop, _seVolume );
}

// ���ʉ����~����
void AudioManager::stopSe( int soundId ) {
    AudioEngine::stop( soundId );
}

// ���ʉ��̉��ʂ�ύX����
void AudioManager::setSeVolume( float volume ) {
    _seVolume = volume;
    //AudioEngine::setVolume(soundId, _seVolume);
}

// ���ʉ��̉��ʂ��擾����
float AudioManager::getSeVolume( ) {
    return _seVolume;
}

// ���ʉ��̃L���b�V�����������
void AudioManager::releaseSe( std::string const& baseName ) {

    std::string fileName = getFileName( AudioType::SE, baseName );
    if ( fileName == "" ) {
        return;
    }

    AudioEngine::uncache( fileName );
}


// AudioEngine���������
void AudioManager::endAudioEngine( ) {
    AudioEngine::end( );
}


//===================
// VOICE
//===================

// ���ʉ���PreLoad
void AudioManager::preloadVoice( std::string const& baseName ) {

    std::string fileName = getFileName( AudioType::VOICE, baseName );
    if ( fileName == "" ) {
        return;
    }
    AudioEngine::preload( fileName );
}

// ���ʉ����Đ�����
int AudioManager::playVoice( std::string const& baseName, Chunk chunkNo ) {
    return this->playVoice( baseName, chunkNo, false, _voiceVolume );
}
// ���ʉ����Đ�����
int AudioManager::playVoice( std::string const& baseName, Chunk chunkNo, bool loop, float volume ) {

    int soundId = AudioEngine::INVALID_AUDIO_ID;
    bool chunkFlag = false;

    std::string fileName = getFileName( AudioType::VOICE, baseName );
    if ( fileName == "" ) {
        return soundId;
    }

    // �`�����N���w�肳��Ă�����
    if ( chunkNo >= 0 && chunkNo < Chunk::End ) {
        chunkFlag = true;

        // �w��`�����N�̍Đ����̉����~
        this->stopVoice( _chunk[chunkNo] );
    }

    soundId = AudioEngine::play2d( fileName, loop, volume );

    if ( chunkFlag ) {
        // �`�����N��SoundId��o�^
        _chunk[chunkNo] = soundId;
    }

    return soundId;

}
// ���ʉ����Đ�����
int AudioManager::playVoice( std::string const& baseName, bool loop, float volume ) {

    return this->playVoice( baseName, Chunk::End, loop, volume );
}
// ���ʉ����Đ�����
int AudioManager::playVoice( std::string const& baseName, bool loop /* = false */ ) {
    return this->playVoice( baseName, loop, _voiceVolume );
}

// ���ʉ����~����
void AudioManager::stopVoice( int soundId ) {
    AudioEngine::stop( soundId );
}

// ���ʉ��̉��ʂ�ύX����
void AudioManager::setVoiceVolume( float volume ) {
    _voiceVolume = volume;
    //AudioEngine::setVolume(soundId, _seVolume);
}

// ���ʉ��̉��ʂ��擾����
float AudioManager::getVoiceVolume( ) {
    return _voiceVolume;
}

// ���ʉ��̃L���b�V�����������
void AudioManager::releaseVoice( std::string const& baseName ) {

    std::string fileName = getFileName( AudioType::VOICE, baseName );
    if ( fileName == "" ) {
        return;
    }

    AudioEngine::uncache( fileName );
}
