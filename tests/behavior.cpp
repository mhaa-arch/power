#include <power/power.hpp>
#include <power/peripheral_clocks.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::power;
using namespace example;

int main()
{
    FakeSleep controller;
    Power power(controller);
    assert(power.sleep(SleepMode::Standby) == Status::Unsupported);
    assert(power.sleep(SleepMode::Idle) == Status::Success);
    FakeGates gates;
    PeripheralClocks clocks(gates);
    assert(clocks.set_enabled(nullptr, 1, false).status == Status::InvalidArgument);
    assert(clocks.set_enabled(nullptr, 0, false).completed == 0 && gates.calls == 0);
    const PeripheralId ids[] = {PeripheralId{}, static_cast<PeripheralId>(1), PeripheralId{}};
    const ClockBatchResult result = clocks.set_enabled(ids, 3, false);
    assert(result.status == Status::InvalidPeripheral && result.completed == 1);
    assert(!gates.enabled && gates.calls == 2);
    assert(clocks.set_enabled(ids, 1, true).status == Status::Success && gates.enabled);

    assert(clocks.set_enabled(static_cast<PeripheralId>(1), false) == Status::InvalidPeripheral);
    assert(clocks.set_enabled(PeripheralId{}, false) == Status::Success && !gates.enabled);
}
