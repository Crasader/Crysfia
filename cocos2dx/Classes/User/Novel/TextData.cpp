#include "TextData.h"

#include "cocos2d.h"

#include "TextScriptReader.h"
#include "TextScriptAnalysis.h"

#include <sstream>

USING_NS_CC;

namespace User
{
    void spaceErase( std::string & lineString )
    {
        const std::string spaceString = u8" ";
        for ( size_t eraseStr = lineString.find_first_of( spaceString ); eraseStr != std::string::npos; eraseStr = lineString.find_first_of( spaceString ) )
        {
            lineString.erase( eraseStr, spaceString.size( ) );
        }
    }

    void commentErase( std::string & lineString )
    {
        size_t findPosition;
        if ( ( findPosition = lineString.find( u8"//" ) ) != std::string::npos ) lineString = lineString.substr( 0, findPosition );
    }

    void alignFirst( std::string & lineString )
    {
        // �s�̐擪�ɋ󔒂��������ꍇ�͋l�߂܂��B
        size_t findPosition;
        if ( ( findPosition = lineString.find_first_not_of( u8" " ) ) != std::string::npos ) lineString = lineString.substr( findPosition );
        else lineString = u8"";
    }

    TextData::TextData( )
    {
        preprocess.insert( std::make_pair( u8"import", std::bind( &TextData::import, this, std::placeholders::_1 ) ) );
        preprocess.insert( std::make_pair( u8"beginland", std::bind( &TextData::beginland, this, std::placeholders::_1 ) ) );
        preprocess.insert( std::make_pair( u8"endland", std::bind( &TextData::endland, this, std::placeholders::_1 ) ) );
    }
    TextData::~TextData( )
    {

    }
    DebugWithLineData TextData::getLineMoved( )
    {
        DebugWithLineData ret;
        if ( work->data.empty( ) )
        {
            if ( work->parentPointer )
            {
                work = work->parentPointer;
                ret = work->data.front( );
                work->data.pop_front( );
            }
        }
        else
        {
            ret = work->data.front( );
            work->data.pop_front( );
        }
        return ret;
    }
    bool TextData::isEmpty( )
    {
        // �q���͊֌W�Ȃ��ł��B
        // �I�����ł͕K���̂Ă���I��������̂ŁB
        return !work->parentPointer && /*work->children.empty( ) &&*/ work->data.empty( );
    }
    void TextData::clear( )
    {
        chunk.children.clear( );
        chunk.data.clear( );
        chunk.parentPointer = nullptr;
    }
    void TextData::makeData( std::string fileName )
    {
        clear( );
        this->fileName = fileName;
        work = &chunk;

        auto fileUtils = FileUtils::getInstance( );
        auto fullPath = fileUtils->fullPathForFilename( u8"res/data/" + fileName );
        auto str = fileUtils->getStringFromFile( fullPath );

        size_t stringPosition = 0;
        size_t findPosition = 0;
        size_t lineNumber = 1; // ���ʂ̃e�L�X�g�G�f�B�^�ł͍s�ԍ��́u1�v����n�܂�̂ŁB
        const std::string eolString = u8"\r\n";
        const size_t eolSize = std::string( eolString ).size( );
        while ( findPosition != std::string::npos )
        {
            findPosition = str.find( eolString, stringPosition );
            tidydiness( str.substr( stringPosition, findPosition - stringPosition ), lineNumber );
            stringPosition = findPosition + eolSize;
            lineNumber += 1;
        }

        for ( auto& line : work->data )
        {
            log( "%s", line.lineData.c_str( ) );
        }
    }
    void TextData::setNextChild( std::string const & selectName )
    {
        auto itr = work->children.find( selectName );
        if ( itr != work->children.cend( ) )
        {
            work = &itr->second;
        }
        else
        {
            try
            {
                errorSStream( "�I�����̑Ή��悪������܂���B", work->data.back( ).debugData );
            }
            catch ( char const* str )
            {

            }
        }
    }
    void TextData::tidydiness( std::string lineString, size_t lineNumber )
    {
        ScriptDebugData debugData;
        debugData.fileName = fileName;
        debugData.lineNumber = lineNumber;

        auto commentErased = lineString;
        commentErase( commentErased );
        alignFirst( commentErased );

        auto scriptPosition = commentErased.find( u8"@", 0 );

        // �X�N���v�g�f�[�^�����܂��B
        DebugWithLineData lineData;
        // �f�o�b�O�f�[�^�̓m�x���f�[�^�ƃX�N���v�g�f�[�^�ŋ��ʂȂ̂ŁA��ɋl�ߍ��݂܂��B
        lineData.debugData = debugData;

        // �X�N���v�g�f�[�^�����������ꍇ�B
        if ( scriptPosition != std::string::npos )
        {
            auto novelString = commentErased.substr( 0, scriptPosition );
            auto scriptString = commentErased.substr( scriptPosition );

            // �m�x���f�[�^���܂܂�Ă���ꍇ
            if ( novelString != u8"" )
            {
                lineData.lineData = novelString;
                work->data.emplace_back( lineData );
            }

            lineData.lineData = scriptString;

            try
            {
                // �X�N���v�g�f�[�^�̒��Ƀv���v���Z�X���߂��������ꍇ�Ɋ��荞�ݏ��������܂��B
                if ( !isPreprocess( lineData ) ) work->data.emplace_back( lineData );
            }
            catch ( char const* str )
            {

            }
        }
        // �m�x���f�[�^�����̏ꍇ
        else if ( commentErased != u8"" )
        {
            lineData.lineData = commentErased;
            work->data.emplace_back( lineData );
        }
    }
    bool TextData::isPreprocess( DebugWithLineData const & debugWithLineData )
    {
        TextScriptReader scriptReader;
        TextScriptAnalysis scriptAnalysis;
        scriptAnalysis.makeScript( scriptReader.createTagWithData( debugWithLineData ) );

        try
        {
            if ( scriptAnalysis.getTag( ) == TagWithData::Tag::FUN )
            {
                auto& func = scriptAnalysis.getFunctionScript( );
                if ( func.variable == u8"sys" )
                {
                    auto itr = preprocess.find( func.functionInfo.name );
                    if ( itr != preprocess.cend( ) )
                    {
                        itr->second( func.functionInfo.argumentList );
                        return true;
                    }
                }
            }
        }
        catch ( char const* errorString )
        {
            // �����̃G���[�͏�w�̊֐���try�������Ă��܂��B
            errorSStream( errorString, scriptAnalysis.getTagWithData( ).debugData );
        }

        return false;
    }
    void TextData::import( ArgumentList const& args )
    {
        if ( args.size( ) != 1 ) throw( "import�̃t�@�C���͈�łȂ��Ƃ����܂���B" );

        TextData textData;
        textData.makeData( args[0] );
        work->data.insert( work->data.cend( ), textData.work->data.cbegin( ), textData.work->data.cend( ) );
        work->children.insert( textData.work->children.cbegin( ), textData.work->children.cend( ) );
    }
    void TextData::beginland( ArgumentList const& args )
    {
        if ( args.size( ) != 1 ) throw( "beginland�̃^�O�͈�łȂ��Ƃ����܂���B" );

        work->children.insert( std::make_pair( args[0], TextChankData( work ) ) );
        work = &work->children[args[0]];
    }
    void TextData::endland( ArgumentList const& args )
    {
        if ( !work->parentPointer ) throw( "endland�ɑΉ�����beginland��������܂���ł����B" );

        work = work->parentPointer;
    }
}