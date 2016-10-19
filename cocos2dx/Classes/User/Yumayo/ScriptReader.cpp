#include "ScriptReader.h"

#include <functional>
#include <algorithm>

namespace User
{
    ScriptReader::ScriptReader( )
    {

    }
    ScriptReader::~ScriptReader( )
    {

    }
    TagRawScriptData ScriptReader::createTagRawScriptData( std::string const& lineRawData )
    {
        if ( lineRawData == u8"" ) return TagRawScriptData( );

        auto temp = spaceErase( lineRawData );
        if ( temp[0] == '@' )
        {
            this->rawLineData = lineRawData.substr( std::string( u8"@" ).size( ) );
            makeTagRawScriptData( );
        }
        else
        {
            this->rawLineData = lineRawData;
            makeNovelData( );
        }

        return getCleanedData( );
    }
    void ScriptReader::makeNovelData( )
    {
        auto scriptLine = rawLineData;
        scriptLine = commentErase( scriptLine );

        if ( scriptLine.empty( ) )
        {
            tagRawScriptData = { TagRawScriptData::Tag::NIL, RawScriptPartsData( ) };
        }
        else
        {
            rawScriptPartsData.emplace_back( scriptLine );
            tagRawScriptData = { TagRawScriptData::Tag::NOV, rawScriptPartsData };
        }
    }
    void ScriptReader::makeTagRawScriptData( )
    {
        auto scriptLine = rawLineData;
        scriptLine = spaceErase( scriptLine );
        scriptLine = commentErase( scriptLine );

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
            if ( str != u8"" ) rawScriptPartsData.emplace_back( scriptLine.substr( 0, findPosition ) );
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
                rawScriptPartsData.emplace_back( findSyntaxItr->partsString );
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

        syntaxCheck( rawScriptPartsData );

        // �ϐ����̂Ƃ����"$"�}�[�N������ΐV�����ϐ��Ƃ��ďo���܂��B
        if ( rawScriptPartsData[0].find( u8"$" ) != std::string::npos )
        {
            tagRawScriptData = { TagRawScriptData::Tag::VAR, rawScriptPartsData };
        }
        // �Ⴄ�Ȃ�A�֐��Ăяo���ɂȂ�܂��B
        else
        {
            tagRawScriptData = { TagRawScriptData::Tag::FUN, rawScriptPartsData };
        }
    }
    std::string ScriptReader::spaceErase( std::string lineString )
    {
        const std::string spaceString = u8" ";
        for ( size_t eraseStr = lineString.find_first_of( spaceString ); eraseStr != std::string::npos; eraseStr = lineString.find_first_of( spaceString ) )
        {
            lineString.erase( eraseStr, spaceString.size( ) );
        }
        return lineString;
    }
    std::string ScriptReader::commentErase( std::string lineString )
    {
        size_t beginComment;
        if ( ( beginComment = lineString.find( u8"//" ) ) != std::string::npos )
        {
            return lineString.substr( 0, beginComment );
        }
        return lineString;
    }
    void ScriptReader::syntaxCheck( RawScriptPartsData const & rawScriptPartsData )
    {
        auto error = [ ] ( std::string const& errorString ) { throw( "syntaxError : " + errorString ); };
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

        auto& raw = rawScriptPartsData;

        TagRawScriptData::Tag tag;

        if ( raw.size( ) < 3U ) error( "�Œ�� @ NAME : RUN �̌`�ŋL�����Ă��������B" );

        if ( raw[1] != u8":" ) error( "�y�A�\���Ɍ�肪����܂��B" );

        if ( raw[0].find( u8"$" ) != std::string::npos ) tag = TagRawScriptData::Tag::VAR;
        else tag = TagRawScriptData::Tag::FUN;

        switch ( tag )
        {
        case User::TagRawScriptData::Tag::VAR:
            do
            {
                if ( 3U < raw.size( ) ) error( "�ϐ��̎��͈̂�łȂ��Ƃ����܂���B" );
                if ( !isValue( raw[2] ) ) error( "�ϐ��錾�ɑ΂��鐔�����s���Ȓl�ł��B" );
            } while ( false );
            break;
        case User::TagRawScriptData::Tag::FUN:
            do
            {
                if ( 3U < raw.size( ) )
                {
                    if ( raw[3] != u8"(" ) error( "�֐��̈����\�����Ԉ���Ă��܂��B" );
                    if ( raw.back( ) != u8")" ) error( "�֐��̈������X�g�̍Ō�� \")\" ������܂���B" );

                    for ( size_t i = 4; i < raw.size( ) - 1; ++i )
                    {
                        if ( ( i & 0x1 ) == 0x1 ) // �
                        {
                            if ( raw[i] != u8"," ) error( "�֐��̈������X�g������ł͂���܂���B" );
                        }
                        else // ����
                        {
                            // �S�Ă��A���t�@�x�b�g�ł��邩�A�����Ƃ��ėL���Ȃ�OK�ł��B
                            if ( !isAllAlphabet( raw[i] ) && !isValue( raw[i] ) )
                            {
                                // �ϐ��łȂ�������G���[���΂��܂��B
                                if ( raw[i].find( u8"$" ) == std::string::npos ) error( "�֐��̈������s���Ȓl�ł��B" );
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
    TagRawScriptData ScriptReader::getCleanedData( )
    {
        auto script = tagRawScriptData;
        cleanUp( );
        return script;
    }
    void ScriptReader::cleanUp( )
    {
        rawLineData.clear( );
        rawScriptPartsData.clear( );
        tagRawScriptData.data.clear( );
        tagRawScriptData.tag = TagRawScriptData::Tag::NIL;
    }
}