#include "TextScriptAnalysis.h"

#include "ScriptStaticData.h"
#include "ScriptSystem.h"

#include <algorithm>

namespace User
{
    void TextScriptAnalysis::makeScript( TagWithData const& tagWithData )
    {
        this->tagWithData = tagWithData;
        switch ( tagWithData.tag )
        {
        case TagWithData::Tag::NOV:
            makeNovelScript( );
            break;
        case TagWithData::Tag::VAR:
            makeVariableScript( );
            break;
        case TagWithData::Tag::FUN:
            makeFunctionScript( );
            break;
        default:
            return;
            break;
        }
    }
    void TextScriptAnalysis::clear( )
    {
        tagWithData.tag = TagWithData::Tag::NIL;
        tagWithData.debugData.fileName.clear( );
        tagWithData.debugData.lineNumber = 0;
        tagWithData.novel.clear( );
        tagWithData.scriptParts.clear( );

        functionScript.variable.clear( );
        functionScript.functionInfo.name.clear( );
        functionScript.functionInfo.argumentList.clear( );

        variableScript.variable.clear( );
        variableScript.currentStatus.clear( );

        novelScript.novel.clear( );
    }
    void TextScriptAnalysis::makeVariableScript( )
    {
        auto variableName = tagWithData.scriptParts[0]; // ���f�[�^�� �z��0�Ԗڂɂ́A�ϐ������L�ڂ���Ă��܂��B
        auto currentStatusName = tagWithData.scriptParts[2]; // ���f�[�^�� �z��2�Ԗڂɂ́A���̕ϐ��̎��̂��L�ڂ���Ă��܂��B

        variableScript = { variableName, currentStatusName };
    }
    void TextScriptAnalysis::makeFunctionScript( )
    {
        auto variableName = tagWithData.scriptParts[0]; // ���f�[�^�� �z��0�Ԗڂɂ́A�ϐ������L�ڂ���Ă��܂��B
        auto functionName = tagWithData.scriptParts[2]; // ���f�[�^�� �z��2�Ԗڂɂ́A�֐������L�ڂ���Ă��܂��B

        // �����Ȃ��̏ꍇ
        // ���@��֐��̈������Ȃ��ꍇ��"()"���ȗ��ł���悤�ɂ��Ă���̂ŁB
        if ( tagWithData.scriptParts.size( ) == 3U )
        {
            // �֐������쐬�B
            // �֐��̖��O�ƁA�������X�g��ۑ����܂��B
            FunctionInfo functionInfo = { functionName, ArgumentList( ) };

            functionScript = { variableName, functionInfo };
        }
        // ��������̏ꍇ
        // "()"�𖾎��I�ɏ����Ă�OK�Ȃ悤�ɂ��Ă��܂��B
        else
        {
            // �֐��̈����������c���܂��B
            auto values = tagWithData.scriptParts; // [var][:][name][(][hoge][,][huga]...[)]
            values.erase( values.begin( ), values.begin( ) + 4 ); // [hoge][,][huga]...[)]
            values.pop_back( ); // [hoge][,][huga]...

            // �������X�g���쐬���܂��B
            ArgumentList argumentList;
            // 2��΂��Ȃ̂́A�Ԃ�","�����邽�߁B
            // �ق�Ƃ��ɕK�v�Ȃ̂́A�����Ԃɂ�������݂̂ł��B
            for ( size_t i = 0; i < values.size( ); i += 2 ) argumentList.emplace_back( values[i] );
            // �֐������쐬�B
            // �֐��̖��O�ƁA�������X�g��ۑ����܂��B
            FunctionInfo functionInfo = { functionName, argumentList };

            functionScript = { variableName, functionInfo };
        }
    }
    void TextScriptAnalysis::makeNovelScript( )
    {
        novelScript.novel = tagWithData.novel;
    }
}
