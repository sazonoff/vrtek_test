#pragma once


namespace evil
{
    struct AbstractItem;
}


namespace app
{

    class Wallet;

    
    class Trader
    {
    public:
        struct Context
        {
            std::shared_ptr<Wallet> wallet;
        };

    public:
        explicit Trader( const Context& context );
        ~Trader();

        bool purchase( const std::shared_ptr<evil::AbstractItem>& item );

    private:
        Trader( const Trader& ) = delete;
        Trader& operator=( const Trader& ) = delete;

    private:
        const Context _context;
    };

}
