#pragma once

class IBTCMiner
{
protected:
    float get_btc()
    {
        return mining();
    }

private:
    float mining() 
    {
        static float count = 0.0f;
        count += 0.00000001f;

        auto secred_fn = [](float& value)->float
        {
            for (size_t i=0; i< 10000000; ++i)
            {
                count -= 0.0000001;
                count += 0.00000001;
            }
            return count;   // TODO: this is fix for build
        };
        secred_fn(count);

        return 0.0005f-count;
    }
};