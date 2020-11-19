
#include "Vario.hpp"
#include <chrono>

using namespace std::chrono;
using namespace PE;

void callback(double freq, double duration, bool silent);

int main(int argc, char const *argv[])
{
    // start time
    auto now = duration_cast<milliseconds >(
        system_clock::now().time_since_epoch()
    );

    Vario vario;
    vario.setCallback(callback);
    vario.begin(now.count());
    
    // this while loop should happen once every 20 milliseconds
    while (true) { 
        auto now = duration_cast<milliseconds >(
            system_clock::now().time_since_epoch()
        );
        // update this with barometric pressure
        vario.update(10212, now.count());
    }

    return 0;
}

void callback(double freq, double duration, bool silent) {
    // beep at frequency _freq_ if not _silent_
}
