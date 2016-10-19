#include "TextChank.h"

#include <algorithm>

namespace User
{
    TextChank::TextChank( )
    {

    }
    TextChank::~TextChank( )
    {

    }
    void TextChank::insertScript( TagRawScriptData const & tagRawScriptData )
    {
        bufferTagRawScriptData = tagRawScriptData;
        switch ( bufferTagRawScriptData.tag )
        {
        case TagRawScriptData::Tag::NOV:
            makeNovel( );
            break;
        case TagRawScriptData::Tag::VAR:
            makeVariableScript( );
            break;
        case TagRawScriptData::Tag::FUN:
            makeFunctionScript( );
            break;
        default:
            return;
            break;
        }
        bufferTagRawScriptData.tag = TagRawScriptData::Tag::NIL;
        bufferTagRawScriptData.data.clear( );
    }
    bool TextChank::isNext( )
    {
        return novelIndex == novelData.size( );
    }
    NovelData TextChank::getNovelData( )
    {
        return novelData;
    }
    void TextChank::clear( )
    {
        bufferTagRawScriptData.tag = TagRawScriptData::Tag::NIL;
        bufferTagRawScriptData.data.clear( );

        functionScriptData.clear( );
        //variableScriptData.clear( ); // �ϐ��̏������͂��Ȃ��B
        novelIndex = 0;
        for ( auto& obj : novelData ) obj = u8"";
    }
    FunctionScriptData TextChank::getFunctionScript( )
    {
        return FunctionScriptData( );
    }
    void TextChank::makeVariableScript( )
    {
        auto data = bufferTagRawScriptData.data;

        auto values = data;
        auto variableName = data[0]; // ���f�[�^�� �z��0�Ԗڂɂ́A�ϐ������L�ڂ���Ă��܂��B
        auto currentStatusName = data[2]; // ���f�[�^�� �z��2�Ԗڂɂ́A���̕ϐ��̎��̂��L�ڂ���Ă��܂��B

        variableScriptData.insert( std::make_pair( variableName, currentStatusName ) );
    }
    void TextChank::makeFunctionScript( )
    {
        auto data = bufferTagRawScriptData.data;

        auto values = data;
        auto variableName = data[0]; // ���f�[�^�� �z��0�Ԗڂɂ́A�ϐ������L�ڂ���Ă��܂��B
        auto functionName = data[2]; // ���f�[�^�� �z��2�Ԗڂɂ́A�֐������L�ڂ���Ă��܂��B

        // �����Ȃ��̏ꍇ
        // ���@��֐���"()"���ȗ��ł���悤�ɂ��Ă���̂ŁB
        if ( values.size( ) == 3U )
        {
            // �֐������쐬�B
            // �֐��̖��O�ƁA�������X�g��ۑ����܂��B
            FunctionScript functionInfo = { functionName, ArgumentList( ) };

            // �ŏI�I�ɁA�֐������������}�b�v�𐶐����܂��B
            functionScriptData.insert( std::make_pair( variableName, functionInfo ) );
        }
        // ��������̏ꍇ
        // "()"�𖾎��I�ɏ����Ă�OK�Ȃ悤�ɂ��Ă��܂��B
        else
        {
            // �֐��̈����������c���܂��B
            values.erase( values.begin( ), values.begin( ) + 4 );
            values.pop_back( );

            // �������X�g���쐬���܂��B
            ArgumentList argumentList;
            // 2��΂��Ȃ̂́A�Ԃ�","�����邽�߁B
            // �ق�Ƃ��ɕK�v�Ȃ̂́A�����Ԃɂ�������݂̂ł��B
            for ( size_t i = 0; i < values.size( ); i += 2 )
            {
                if ( values[i].find( u8"$" ) != std::string::npos )
                {
                    auto itr = variableScriptData.find( values[i] );
                    if ( itr != variableScriptData.cend( ) ) argumentList.emplace_back( itr->second );
                    else throw( "�w�肵���ϐ������݂��܂���B" );
                }
                else argumentList.emplace_back( values[i] );

            }
            // �֐������쐬�B
            // �֐��̖��O�ƁA�������X�g��ۑ����܂��B
            FunctionScript functionInfo = { functionName, argumentList };

            // �ŏI�I�ɁA�֐������������}�b�v�𐶐����܂��B
            functionScriptData.insert( std::make_pair( variableName, functionInfo ) );
        }
    }
    void TextChank::makeNovel( )
    {
        auto data = bufferTagRawScriptData.data;

        novelIndex = std::min( novelIndex + 1U, novelData.size( ) );

        novelData[novelIndex - 1] = data[0];
    }
}
