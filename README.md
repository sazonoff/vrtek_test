Test task for VRTek Senior/Lead C++ developer

Known issues / possible improvements:
- btc_miner was fixed to be compilable
- No feature to instantly terminate application because of btc_miner/api limitations.
- Crutch with detecting size of packets in evil::ItemFactory.
- No crash detection. May be solved with using of google breakpad library.
- Singleton is used to connect api.dll with code, because api doesn't provide any user data storage for callbacks.
- Wallet class may be improved with some kind of payment transactions. So there is no possibility to know current number of coins and do a transaction in one thread lock. But ut was not required by a task.
- Some glitches with text output, because api.dll doesn't provide interface for thread-safe std::cout usage
- Some classes (like Wallet) may be done as templates, so it is possible to use different containers for tuning up performace.
- Some code from my old projects (in Utils)
