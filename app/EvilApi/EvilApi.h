#pragma once


namespace evil
{
    
    class EvilApi
    {
    public:
        using Callback = void( *)(const char*, size_t);
        using Value = size_t;
        using Size = float;

    public:
        virtual void get_raw_rare( Callback callback ) = 0;
        virtual void get_test_string( char* ptr ) = 0;
        virtual ~EvilApi() = default;
    };

}
