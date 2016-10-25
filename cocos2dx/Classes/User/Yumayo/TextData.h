# ifndef __TextData__
# define __TextData__

# include <deque>
# include "TextTypes.hpp"

namespace User
{
    void spaceErase( std::string& lineString );
    void commentErase( std::string& lineString );
    void alignFirst( std::string& lineString );

    class TextData
    {
    public:
        TextData( );
        ~TextData( );
    public:
        DebugWithLineData getLineMoved( );
        bool isEmpty( );
        void makeData( std::string fileName );
    private:
        // �s���쐬���Ƀm�x���f�[�^�ƃX�N���v�g�f�[�^�����݂��Ă���s���o�Ă����ꍇ�ɁA
        // �����𕪂��č쐬������A�R�����g���}�����Ă���s��A��s�Ȃǂ�r�����܂��B
        void tidydiness( std::string lineString, size_t lineNumber );
        std::deque<DebugWithLineData> data;
        std::string fileName;
    };
}

# endif // __TextData__