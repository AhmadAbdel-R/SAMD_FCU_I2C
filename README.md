# SAMD FCU I2C

SAMD21-side firmware for FCU helper communication over I2C.

## Active Firmware Folder

- `SAMD21_I2C_SLAVE/`

## Current Functionality

- Runs as I2C slave at address `0x08`
- register-style request flow
- ping register returns `0xA5`
- version and uptime registers available

## Why It Exists

This repo is used to stabilize ESP32 <-> SAMD communication before bigger FCU integration.

## Build

1. Open `SAMD21_I2C_SLAVE` in PlatformIO.
2. Build and flash target SAMD21 board.
3. Query the slave from master firmware for ping/version/uptime.
