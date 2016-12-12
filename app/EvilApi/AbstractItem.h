#pragma once


namespace evil
{

    struct AbstractItem
    {
    public:
        using Key = unsigned char;
        using Size = float;
        using Cost = size_t;
        using Value = size_t;

    public:
        Key type;
        Cost cost;
    };

    static_assert(sizeof( AbstractItem::Size ) == 4, "size must equal 4");
    static_assert(sizeof( AbstractItem::Value ) == 4, "value must equal 4");

}
