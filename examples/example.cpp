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
