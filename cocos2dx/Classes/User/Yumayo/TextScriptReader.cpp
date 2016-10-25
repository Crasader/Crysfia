#include "TextScriptReader.h"

#include "TextData.h"

#include <functional>
#include <algorithm>

namespace User
{
    TextScriptReader::TextScriptReader( )
    {

    }
    TextScriptReader::~TextScriptReader( )
    {

    }
    TagWithData TextScriptReader::createTagRawScriptPartsData( DebugWithLineData const& debugWithLineData )
    {
        // ������̐擪��"@"������ꍇ�̓X�N���v�g
        if ( debugWithLineData.lineData[0] == '@' )
        {
            // �擪��"@"�̌��̃f�[�^��n���܂��B
            this->lineData = debugWithLineData.lineData.substr( std::string( u8"@" ).size( ) );
            this->debugData = debugWithLineData.debugData;
            makeTagRawScriptData( );
        }
        // �����łȂ��ꍇ�̓m�x���f�[�^�ł��B
        else
        {
            this->lineData = debugWithLineData.lineData;
            this->debugData = debugWithLineData.debugData;
            makeNovelData( );
        }

        return getCleanedData( );
    }
    void TextScriptReader::makeNovelData( )
    {
        tagWithData = { TagWithData::Tag::NOV, debugData, StringArray( ), lineData };
    }
    void TextScriptReader::makeTagRawScriptData( )
    {
        scriptParts.clear( );

        auto scriptLine = lineData;
        spaceErase( scriptLine );

        size_t findPosition = 0;
        std::string findString;

        auto find = [ & ] ( std::string const& $findString )
        {
            findString = $findString;
            return ( findPosition = scriptLine.find_first_of( $findString ) ) != std::string::npos;
        };

        auto partsAdd = [ & ] ( size_t findPosition )
        {
            auto str = scriptLine.substr( 0, findPosition );
            if ( str != u8"" ) scriptParts.emplace_back( str );
        };

        struct Syntax
        {
            bool isFind;
            std::string partsString;
            size_t position;
        };

        std::function<void( )> disassembly = [ & ]
        {
            std::vector<Syntax> syntaxs;
            syntaxs.push_back( { find( u8":" ), findString, findPosition } );
            syntaxs.push_back( { find( u8"(" ), findString, findPosition } );
            syntaxs.push_back( { find( u8")" ), findString, findPosition } );
            syntaxs.push_back( { find( u8"," ), findString, findPosition } );

            auto findSyntaxItr = std::min_element( syntaxs.begin( ), syntaxs.end( ), [ ] ( Syntax& a, Syntax& b )
            {
                return a.position < b.position;
            } );

            // �\�������������ꍇ�́A�ǂ�ǂ񕪊����Ă����܂��B
            if ( findSyntaxItr->isFind )
            {
                partsAdd( findSyntaxItr->position );
                scriptParts.emplace_back( findSyntaxItr->partsString );
                scriptLine = scriptLine.substr( findSyntaxItr->position + std::string( findSyntaxItr->partsString ).size( ) );

                disassembly( );
            }
            // �\����������Ȃ������ꍇ�́A�c����������ǉ����ďI���ł��B
            else
            {
                partsAdd( findSyntaxItr->position );
            }
        };

        disassembly( );

        syntaxCheck( scriptParts );

        // �ϐ����̂Ƃ����"$"�}�[�N������ΐV�����ϐ��Ƃ��č쐬�o���܂��B
        if ( scriptParts[0].find( u8"$" ) != std::string::npos )
        {
            tagWithData = { TagWithData::Tag::VAR, debugData, scriptParts, u8"" };
        }
        // �Ⴄ�Ȃ�A�֐��Ăяo���ɂȂ�܂��B
        else
        {
            tagWithData = { TagWithData::Tag::FUN, debugData, scriptParts, u8"" };
        }
    }
    void TextScriptReader::syntaxCheck( StringArray const & scriptParts )
    {
        auto error = [ &, this ] ( std::string const& errorString ) { throw( "[syntaxError : " + errorString + "][ file : " + debugData.fileName + "][line : " + std::to_string( debugData.lineNumber ) + "]" ); };
        auto isAllAlphabet = [ & ] ( std::string const& string )
        {
            return std::all_of( string.cbegin( ), string.cend( ), isalpha );
        };
        auto isValue = [ & ] ( std::string const& string )
        {
            double value;
            try { value = std::stod( string ); }
            catch ( const std::logic_error& e ) { return false; }
            return true;
        };

        auto& parts = scriptParts;

        TagWithData::Tag tag;

        if ( parts.size( ) < 3U ) error( "�Œ�� [@ NAME : RUN] �̌`�ŋL�����Ă��������B" );

        if ( parts[1] != u8":" ) error( "�y�A�\���Ɍ�肪����܂��B" );

        if ( parts[0].find( u8"$" ) != std::string::npos ) tag = TagWithData::Tag::VAR;
        else tag = TagWithData::Tag::FUN;

        switch ( tag )
        {
        case User::TagWithData::Tag::VAR:
            do
            {
                if ( 3U < parts.size( ) ) error( "�ϐ��̎��͈̂�łȂ��Ƃ����܂���B" );
                if ( !isValue( parts[2] ) ) error( "�ϐ��錾�ɑ΂��鐔�����s���Ȓl�ł��B" );
            } while ( false );
            break;
        case User::TagWithData::Tag::FUN:
            do
            {
                if ( 3U < parts.size( ) )
                {
                    if ( parts[3] != u8"(" ) error( "�֐��̈����\�����Ԉ���Ă��܂��B" );
                    if ( parts.back( ) != u8")" ) error( "�֐��̈������X�g�̍Ō�� \")\" ������܂���B" );

                    for ( size_t i = 4; i < parts.size( ) - 1; ++i )
                    {
                        if ( ( i & 0x1 ) == 0x1 ) // �
                        {
                            if ( parts[i] != u8"," ) error( "�֐��̈������X�g������ł͂���܂���B" );
                        }
                        else // ����
                        {
                            // �S�Ă��A���t�@�x�b�g�ł��邩�A�����Ƃ��ėL���Ȃ�OK�ł��B
                            if ( !isAllAlphabet( parts[i] ) && !isValue( parts[i] ) )
                            {
                                // �ϐ��łȂ�������G���[���΂��܂��B
                                if ( parts[i].find( u8"$" ) == std::string::npos ) error( "�֐��̈������s���Ȓl�ł��B" );
                            }
                        }
                    }
                }
            } while ( false );
            break;
        default:
            break;
        }
    }
    TagWithData TextScriptReader::getCleanedData( )
    {
        auto script = tagWithData;
        cleanUp( );
        return script;
    }
    void TextScriptReader::cleanUp( )
    {
        lineData.clear( );

        debugData.fileName.clear( );
        debugData.lineNumber = 0;

        tagWithData.tag = TagWithData::Tag::NIL;
        tagWithData.debugData.fileName.clear( );
        tagWithData.debugData.lineNumber = 0;
        tagWithData.novel.clear( );
        tagWithData.scriptParts.clear( );
    }
}