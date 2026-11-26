#ifndef MHAA_POWER_EXAMPLE_FAKE_HPP
#define MHAA_POWER_EXAMPLE_FAKE_HPP

#include <power/sleep_controller.hpp>
#include <power/peripheral_clock_control.hpp>

namespace example
{
    using namespace mhaa::power;

    class FakeSleep final : public SleepController
    {
    public:
        Status enter(SleepMode mode) override
        {
            return mode == SleepMode::Idle ? Status::Success : Status::Unsupported;
        }
    };

    class FakeGates final : public PeripheralClockControl
    {
    public:
        Status set_enabled(PeripheralId peripheral, bool enable) override
        {
            ++calls;
            if (peripheral != PeripheralId{})
            {
                return Status::InvalidPeripheral;
            }
            enabled = enable;
            return Status::Success;
        }

        bool enabled = true;
        unsigned calls = 0;
    };
}

#endif
