# Driver for Surface Aggregator Module on 4th Generation Surface Devices

Work in progress. Experimental.

The Surface System Aggregator Module is an embedded controller that can be found on 4th and later generation Microsoft Surface devices.
On 5th and later generation devices, this is already supported via the Surface System Aggregator Module driver at [github.com/linux-surface/surface-aggregator-module][1].
Unfortunately, the interface via which the EC is connected to the host is different for 4th generation devices, specifically, instead of a USART, it is connected via I2C and uses an HID-over-I2C-based protocol.

This repository is intended to eventually provide support for this EC.
At the moment, support is limited to enabling communication via ACPI, which is essential to enabling the discrete GPU.

[1]: https://github.com/linux-surface/surface-aggregator-module
