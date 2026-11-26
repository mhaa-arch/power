# Use the Power Management Core

Public entry headers are [power/peripheral_clocks.hpp](../include/power/peripheral_clocks.hpp), [power/power.hpp](../include/power/power.hpp).

## Sleep and wake

Construct `Power` from a live `SleepController&`. Configure any target wake condition through composition before making a request that depends on it. `sleep` forwards the category and reports the Adapter's status if it returns.

## Apply gate changes in order

Construct `PeripheralClocks` independently from a `PeripheralClockControl&`. The single-ID overload forwards one change. The array overload applies each entry in order and stops at the first failure. `completed` counts the accepted prefix. A failure leaves previous changes in effect. A zero count needs no buffer, and a null buffer with a positive count is invalid.

## Composition and lifetime

Application code calls the Power Management Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
