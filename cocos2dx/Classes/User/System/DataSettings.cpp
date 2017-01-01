#include "DataSettings.h"

#include "../Novel/INIReader.h"
#include "../Novel/INIWriter.h"
#include "../Novel/StringUtil.h"

USING_NS_CC;

namespace User
{
    void iniDataRead( INIReader & reader, std::string const& name )
    {
        auto file = FileUtils::getInstance( );
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
        {
            reader.read( file->getWritablePath( ) + name );
        }
        else
        {
            reader.read( name );
        }
    }
    void iniDataRead( INIReader & reader, std::string const & name, std::string const & defalutDirectory )
    {
        auto file = FileUtils::getInstance( );
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
        {
            reader.read( file->getWritablePath( ) + name );
        }
        else
        {
            reader.read( defalutDirectory + name );
        }
    }

    void setUserDefault( INIReader& iniReader )
    {
        auto userDefault = UserDefault::getInstance( );

        using Type = std::string; // bool, int, float, string�̕���������܂��B
        using Key = std::string; // �ϐ��ɕt�������O���i�[���܂��B
        using Value = std::string; // �ϐ��̎��Ԃ��i�[���܂��B
        using ValueMap = std::map<Key, Value>; // �ϐ��̖��O��ϐ��̎��̂��܂Ƃ߂��ꗗ���i�[���܂��B

        {
            Type type = u8"bool";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                Value value = map.second;

                userDefault->setBoolForKey( key.c_str( ), StringUtil::string_value<bool>( value ) );
            }
        }
        {
            Type type = u8"int";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                Value value = map.second;

                userDefault->setIntegerForKey( key.c_str( ), StringUtil::string_value<int>( value ) );
            }
        }
        {
            Type type = u8"float";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                Value value = map.second;

                userDefault->setFloatForKey( key.c_str( ), StringUtil::string_value<float>( value ) );
            }
        }
        {
            Type type = u8"string";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                Value value = map.second;

                userDefault->setStringForKey( key.c_str( ), StringUtil::string_value<std::string>( value ) );
            }
        }
    }
    // ���[�U�[�f�t�H���g�̒��g��INI�^�ɂ��ĕԂ��܂��B
    // ���[�U�[�f�t�H���g�ł́A���g��񋓂��邱�Ƃ��o���Ȃ��̂ŁA
    // �f�[�^�����o���ۂɁA�L�[�̌��ƂȂ�INI�t�@�C����񎦂��Ȃ��Ƃ����܂���B
    INIReader getUserDefault( INIReader& iniReader )
    {
        INIReader ret;

        // INI�f�[�^�̃L�[�����v���郆�[�U�[�f�t�H���g�̒��g�����o�������B
        using Type = std::string; // bool, int, float, string�̕���������܂��B
        using Key = std::string; // �ϐ��ɕt�������O���i�[���܂��B
        using Value = std::string; // �ϐ��̎��Ԃ��i�[���܂��B
        using ValueMap = std::map<Key, Value>; // �ϐ��̖��O��ϐ��̎��̂��܂Ƃ߂��ꗗ���i�[���܂��B

        auto userDefault = UserDefault::getInstance( );

        {
            Type type = u8"bool";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                auto velue = userDefault->getBoolForKey( key.c_str( ) );
                ret[type][key] = StringUtil::value_string( velue );
            }
        }
        {
            Type type = u8"int";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                auto value = userDefault->getIntegerForKey( key.c_str( ) );
                ret[type][key] = StringUtil::value_string( value );
            }
        }
        {
            Type type = u8"float";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                auto value = userDefault->getFloatForKey( key.c_str( ) );
                ret[type][key] = StringUtil::value_string( value );
            }
        }
        {
            Type type = u8"string";
            for ( auto const& map : iniReader[type] )
            {
                Key key = map.first;
                auto value = userDefault->getStringForKey( key.c_str( ) );
                ret[type][key] = StringUtil::value_string( value );
            }
        }
        return ret;
    }
    void userDefaultSetup( )
    {
        auto data = UserDefault::getInstance( );
        if ( !data->getBoolForKey( u8"INITDATA", false ) )
        {
            INIReader reader;
            iniDataRead( reader, u8"res/data/saveLayout.ini" );

            std::map<std::string, std::function<void( std::map<std::string, std::string> )>> calls;

            calls.insert( { u8"bool", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setBoolForKey( value.first.c_str( ), StringUtil::string_value<bool>( value.second ) );
            } } );
            calls.insert( { u8"int", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setIntegerForKey( value.first.c_str( ), StringUtil::string_value<int>( value.second ) );
            } } );
            calls.insert( { u8"float", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setFloatForKey( value.first.c_str( ), StringUtil::string_value<float>( value.second ) );
            } } );
            calls.insert( { u8"string", [ ] ( std::map< std::string, std::string > tag )
            {
                auto data = UserDefault::getInstance( );
                for ( auto& value : tag )
                    data->setStringForKey( value.first.c_str( ), StringUtil::string_value<std::string>( value.second ) );
            } } );

            for ( auto& tag : reader.getData( ) )
            {
                auto itr = calls.find( tag.first );
                if ( itr != calls.end( ) )
                {
                    itr->second( tag.second );
                }
            }
            data->setBoolForKey( u8"INITDATA", true );
        }
    }
    void userDefaultForceSetup( )
    {
        UserDefault::getInstance( )->setBoolForKey( u8"INITDATA", false );
        userDefaultSetup( );
    }
    std::string getLocalReadPath( std::string const & name )
    {
        auto file = FileUtils::getInstance( );
        std::string path;
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
            path = file->getWritablePath( ) + name;
        else
            path = name;
        return path;
    }
    std::string getLocalReadPath( std::string const & name, std::string const & directory )
    {
        auto file = FileUtils::getInstance( );
        std::string path;
        if ( file->isFileExist( file->getWritablePath( ) + name ) )
            path = file->getWritablePath( ) + name;
        else
            path = directory + name;
        return path;
    }
    void writeUserLocal( std::string const & data, std::string const & name )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeStringToFile( data, path + name );
        }
    }
    void writeUserLocal( std::string const & data, std::string const & name, std::string const & directory )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeStringToFile( data, path + directory + name );
        }
    }
    void writeDataUserLocal( cocos2d::Data const & data, std::string const & name )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeDataToFile( data, path + name );
        }
    }
    void writeDataUserLocal( cocos2d::Data const & data, std::string const & name, std::string const & directory )
    {
        auto fileUtil = FileUtils::getInstance( );

        auto path = fileUtil->getWritablePath( );
        if ( !path.empty( ) )
        {
            fileUtil->writeDataToFile( data, path + directory + name );
        }
    }
}