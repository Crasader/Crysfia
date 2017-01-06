/****************************************************************************
 Copyright (c) 2016 Yuji Toki(tokineco)
 - MIT license
****************************************************************************/
#ifndef __AudioManager__
#define __AudioManager__

#include "cocos2d.h"

class AudioManager {

private:

    enum AudioType {
        BGM,
        SE,
        VOICE
    };

    enum FadeType {
        NONE = 0,
        FADE_IN = 1,
        FADE_OUT = 2,
        FADE_IN_RESUME = 3,
        FADE_OUT_PAUSE = 4
    };

public:
    /**
     * �`�����N�ԍ��𐔎��œ��͂���̂͂����D���Ȃ�����������̂�enum��
     */
    enum Chunk
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15,
        End
    };
private:

    AudioManager( );
    static AudioManager* _instance;

    // update���s�p
    static cocos2d::Scheduler* _scheduler;

    // BGM�t�@�C�����X�g
    std::map<std::string, std::string> _bgmList;
    // BGM�t�@�C����Ԑݒ胊�X�g
    struct BgmLoopParams {
        float startPos;
        float endPos;
        bool isLoopInterval;
    };
    std::map<std::string, BgmLoopParams> _bgmLoopList;
    // SE�t�@�C�����X�g
    std::map<std::string, std::string> _seList;

    // SE�p�`�����N
    int _chunk[Chunk::End];

    // BGM��1��ނ̂�
    int _bgmId = -1;
    // �����t�@�C�����̏ꍇ�͖���
    std::string _bgmFileName = "";

    // �I�[�f�B�I�Ǘ��t�@�C�����g�p����ꍇ�͂��̃t�@�C���p�X
    CC_SYNTHESIZE( std::string, _audioListFile, AudioListFile );

    // BGM����
    float  _bgmVolume;
    // SE����
    float _seVolume;

    // BGM�t�F�[�h�֘A
    FadeType _fadeCondition;
    float _bgmFadeVolumeFrom;
    float _bgmFadeVolumeTo;
    float _bgmFadeVolumeNow;
    float _bgmFadeTime;
    bool _stopBgmReleaseFlg;

    //==========================

public:

    ~AudioManager( );
    static AudioManager* getInstance( );
    static void deleteInstance( );

    // ���t���[�����s
    virtual void update( float dt );

    // �I�[�f�B�I�Ǘ��t�@�C����ǂݍ���
    bool readAudioListFile( std::string const& fileName );
    // AudioEngine�S�ẴL���b�V�����폜����
    void releaseAll( );

    // BGM��SE�̉��ʂ̏�����
    void initVolume( float bgmVolume, float seVolume );

    // BGM��PreLoad
    void preloadBgm( std::string const& baseName );
    // BGM�̍Đ�
    int playBgm( std::string const& baseName, float fadeTime = 0, bool loop = true );
    int playBgm( std::string const& baseName, float fadeTime, bool loop, float volume );
    // BGM���ꎞ��~����
    void pauseBgm( float fadeTime = 0 );
    // BGM�����W���[���Đ�����
    void resumeBgm( float fadeTime = 0 );
    // BGM���~����
    // Arg2 - release : �L���b�V����j������ꍇ��true
    void stopBgm( float fadeTime = 0, bool release = true );
    // BGM���Đ�����Ă��邩�ǂ���
    bool isPlayingBgm( );
    // BGM�̉��ʂ�ύX����
    // Arg2 - save : �ϐ�_bgmVolume�ɕۑ�����ꍇ��true
    void setBgmVolume( float volume, bool save = true );
    // BGM�̉��ʂ��擾����
    float getBgmVolume( );
    // BGM�̃L���V�����������
    void releaseBgm( );

    // ���ʉ���PreLoad
    void preloadSe( std::string const& baseName );
    // ���ʉ����Đ�����
    // Args2 - chunkNo : �`�����N���w�肷��Ɠ����`�����N�ԍ����w�肳�ꂽ�ꍇ�́A�O�̉����㏑������
    int playSe( std::string const& baseName, int chunkNo );
    int playSe( std::string const& baseName, int chunkNo, bool loop, float volume );
    int playSe( std::string const& baseName, bool loop = false );
    int playSe( std::string const& baseName, bool loop, float volume );
    // ���ʉ����~����
    void stopSe( int soundId );
    // ���ʉ��̉��ʂ�ύX����
    void setSeVolume( float volume );
    // ���ʉ��̉��ʂ��擾����
    float getSeVolume( );
    // ���ʉ��̃L���b�V�����������
    void releaseSe( std::string const& baseName );

    // AudioEngine���������
    void endAudioEngine( );

    /**
     * VOICE�̒ǉ�
     * SE�Ƌ@�\�͓���
     * ��{�I�ɂ̓{�����[�����ʉ���}�邽�߂̂���
     * <!--chunk��se�̂��̂Ƌ��L���Ďg���Ă���̂Œ���-->
     */
    float _voiceVolume;
    std::map<std::string, std::string> _voiceList;
     // ���ʉ���PreLoad
    void preloadVoice( std::string const& baseName );
    // ���ʉ����Đ�����
    // Args2 - chunkNo : �`�����N���w�肷��Ɠ����`�����N�ԍ����w�肳�ꂽ�ꍇ�́A�O�̉����㏑������
    int playVoice( std::string const& baseName, Chunk chunkNo );
    int playVoice( std::string const& baseName, Chunk chunkNo, bool loop, float volume );
    int playVoice( std::string const& baseName, bool loop = false );
    int playVoice( std::string const& baseName, bool loop, float volume );
    // ���ʉ����~����
    void stopVoice( int soundId );
    // ���ʉ��̉��ʂ�ύX����
    void setVoiceVolume( float volume );
    // ���ʉ��̉��ʂ��擾����
    float getVoiceVolume( );
    // ���ʉ��̃L���b�V�����������
    void releaseVoice( std::string const& baseName );

private:
    // ���ɉ����Ċg���q�t���t�@�C�����ɕϊ�����
    std::string getFileName( AudioType type, std::string baseName );

    // pauseBgm�̎��s(fade�Ȃ��A�܂���update�ɂ��t�F�[�h��Ɏ��s�����)
    void pauseBgmEngine( );

    // stopBgm�̎��s(fade�Ȃ��A�܂���update�ɂ��t�F�[�h��Ɏ��s�����)
    void stopBgmEngine( bool release = true );

    // ���o�C���f�o�C�X���ǂ���
    bool isMobileDevice( );
};

#endif /* defined(__AudioManager__) */
