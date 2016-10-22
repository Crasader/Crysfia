# ifndef __TextData__
# define __TextData__

# include <deque>
# include <string>
# include <vector>

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
        std::string getLineMoved( );
        bool isEmpty( );
        void makeData( std::string filePath );
    private:
        // �s���쐬���Ƀm�x���f�[�^�ƃX�N���v�g�f�[�^�����݂��Ă���s���o�Ă����ꍇ�ɁA
        // �����𕪂��č쐬������A�R�����g���}�����Ă���s��A��s�Ȃǂ�r�����܂��B
        void tidydiness( std::string lineString );
        std::deque<std::string> data;
    };
}

# endif // __TextData__