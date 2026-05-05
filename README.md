# SAMD FCU I2C

SAMD21 I2C slave firmware scaffold intended for FCU-side co-processor telemetry and control work.

Active PlatformIO project path:

- `SAMD21_I2C_SLAVE/`

## Scope

- Establish SAMD21 firmware project baseline
- Implement stable I2C slave responses for FCU integration
- Prepare interface for ESP32 <-> SAMD communication tests

## Build

1. Open `SAMD21_I2C_SLAVE` in PlatformIO.
2. Build and upload to target SAMD board.
3. Validate I2C transactions from host MCU.
