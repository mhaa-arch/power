# Run the Power Management Core example

The example borrows a sleep-only fake and requests idle. It exits successfully when the simulation accepts the request. The behavior program supplies a separate clock-control fake, then tests a batch that applies one entry before rejecting an unknown ID.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
#include <power/power.hpp>
#include <power/peripheral_clocks.hpp>
#include "fake.hpp"

using namespace mhaa::power;
using namespace example;

int main()
{
    FakeSleep controller;
    Power power(controller);
    return power.sleep(SleepMode::Idle) == Status::Success ? 0 : 1;
}
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/power-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
