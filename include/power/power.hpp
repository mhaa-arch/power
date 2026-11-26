#ifndef MHAA_POWER_HPP
#define MHAA_POWER_HPP

#include <power/sleep_controller.hpp>
#include <power/types.hpp>

namespace mhaa
{
    namespace power
    {
        /** @brief Selects a sleep mode on one borrowed controller. */
        class Power
        {
        public:
            explicit Power(SleepController &controller) : controller_(controller) {}

            Status sleep(SleepMode mode) { return controller_.enter(mode); }

        private:
            SleepController &controller_;
        };
    }
}

#endif
