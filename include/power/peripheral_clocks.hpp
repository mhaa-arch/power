#ifndef MHAA_POWER_PERIPHERAL_CLOCKS_HPP
#define MHAA_POWER_PERIPHERAL_CLOCKS_HPP

#include <power/peripheral_clock_control.hpp>
#include <stddef.h>
#include <power/types.hpp>

namespace mhaa
{
    namespace power
    {
        struct ClockBatchResult
        {
            Status status;
            size_t completed;
        };

        /** @brief Applies clock gating to a list of resources in order. */
        class PeripheralClocks
        {
        public:
            explicit PeripheralClocks(PeripheralClockControl &control) : control_(control) {}

            Status set_enabled(PeripheralId peripheral, bool enabled)
            {
                return control_.set_enabled(peripheral, enabled);
            }

            /** @brief Applies an ordered list and reports the first rejection and accepted prefix. */
            ClockBatchResult set_enabled(const PeripheralId *peripherals, size_t count, bool enabled)
            {
                if (count && !peripherals)
                {
                    return {Status::InvalidArgument, 0};
                }
                for (size_t i = 0; i < count; ++i)
                {
                    const Status status = set_enabled(peripherals[i], enabled);
                    if (status != Status::Success)
                    {
                        return {status, i};
                    }
                }
                return {Status::Success, count};
            }

        private:
            PeripheralClockControl &control_;
        };
    }
}

#endif
