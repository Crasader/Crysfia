# ifndef __TextScriptReader__
# define __TextScriptReader__

# include "TextTypes.hpp"

namespace User
{
    class TextScriptReader
    {
        friend class TextData;
    public:
        TextScriptReader( );
        ~TextScriptReader( );
    public:
        TagWithData createTagRawScriptPartsData( DebugWithLineData const& debugWithLineData );
    private:
        void makeNovelData( );
        void makeTagRawScriptData( );
    private:
        // ���@�`�F�b�N
        void syntaxCheck( StringArray const& scriptParts );
        // �S�Ẵo�b�t�@�[����ɂ��ĕK�v�ȃf�[�^������n���܂��B
        TagWithData getCleanedData( );
        void cleanUp( );
    private:
        ScriptDebugData debugData;

        std::string lineData;
        StringArray scriptParts;

        TagWithData tagWithData;
    };
}

# endif // __TextScriptReader__
