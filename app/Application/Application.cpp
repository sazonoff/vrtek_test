// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "Application.h"

#include "Wallet/Wallet.h"
#include "Miner/MiningFactory.h"
#include "EvilApi/EvilApi.h"
#include "EvilApi/ItemFactory.h"
#include "Trader/Trader.h"
#include "ApiBinding/ApiBinding.h"

#include "Utils/Loader/Loader.h"
#include "Utils/Log/Log.h"


namespace
{
    const std::filesystem::path apiPath = "api.dll";
    const std::string apiInstanceName = "api";
}


namespace app
{

    Application::Application()
    {
    }

    Application::~Application()
    {
        auto& binding = ApiBinding::instance();
        binding.stop();
        binding.unsubscribeAll();
    }

    bool Application::init()
    {
        utils::Loader lib( apiPath );
        auto api = lib.resolve<evil::EvilApi *>( apiInstanceName );
        if ( api == nullptr )
        {
            TRACE << "Could not load \"Evil API\"";
            return false;
        }

        auto wallet = std::make_shared<Wallet>();
        auto miningFactory = std::make_unique<MiningFactory>( MiningFactory::Context{ wallet } );
        auto trader = std::make_shared<Trader>( Trader::Context{ wallet } );

        _api = api;
        _wallet = wallet;
        _miningFactory = std::move( miningFactory );
        _trader = std::move( trader );

        return true;
    }

    void Application::run()
    {
        _miningFactory->start();

        auto itemFactory = std::make_shared<evil::ItemFactory>();
        itemFactory->registerTypes();

        auto traderBind = [trader = _trader, itemFactory = itemFactory]( const std::vector<char>& data )
        {
            const auto item = itemFactory->createFromRaw( data );
            if ( item == nullptr )
            {
                TRACE << "Unknown item data received. Skipped.";
                return;
            }

            trader->purchase( item );
        };

        ApiBinding::Context context;
        context.api = _api;

        auto& binding = ApiBinding::instance();
        binding.setContext( context );
        binding.subscribe( traderBind );
        binding.start();
    }

}
