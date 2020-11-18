### PEVario

Source code for free flight variometer, written in C++.

This is not a stand alone application. The is a library meant to be used inside another program, such as Arduino, mobile altimeter, etc.. 

Sample usage:

```
#include "Vario.hpp"

// for arduino you can use millis() instead
#include <chrono>
using namespace std::chrono;

void callback(double freq, double duration, bool silent) {
    // beep at frequency _freq_ if not _silent_
}
int main(int argc, char const *argv[])
{
    // start time
    auto now = duration_cast<milliseconds >(
        system_clock::now().time_since_epoch()
    );

    PE::Vario vario;
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
```

Pedro Enrique  
Release Nov 18th, 2020  
MIT License  
