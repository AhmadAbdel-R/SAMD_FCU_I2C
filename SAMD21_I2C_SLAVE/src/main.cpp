#include <Arduino.h>
#include <Wire.h>

namespace
{
constexpr uint8_t kI2cAddress = 0x08;
constexpr uint8_t kRegPing = 0x00;
constexpr uint8_t kRegVersion = 0x01;
constexpr uint8_t kRegUptimeSeconds = 0x02;
constexpr uint8_t kPingValue = 0xA5;
constexpr uint8_t kFwMajor = 1;
constexpr uint8_t kFwMinor = 0;

volatile uint8_t gSelectedRegister = kRegPing;
volatile uint32_t gUptimeSeconds = 0;

void onI2cReceive(int byteCount)
{
  if (byteCount <= 0)
  {
    return;
  }

  gSelectedRegister = static_cast<uint8_t>(Wire.read());
  while (Wire.available())
  {
    (void)Wire.read();
  }
}

void onI2cRequest()
{
  switch (gSelectedRegister)
  {
  case kRegPing:
    Wire.write(kPingValue);
    break;
  case kRegVersion:
    Wire.write(kFwMajor);
    Wire.write(kFwMinor);
    break;
  case kRegUptimeSeconds:
  {
    const uint32_t uptimeSeconds = gUptimeSeconds;
    const uint8_t payload[4] = {
        static_cast<uint8_t>((uptimeSeconds >> 24) & 0xFF),
        static_cast<uint8_t>((uptimeSeconds >> 16) & 0xFF),
        static_cast<uint8_t>((uptimeSeconds >> 8) & 0xFF),
        static_cast<uint8_t>(uptimeSeconds & 0xFF),
    };
    Wire.write(payload, sizeof(payload));
    break;
  }
  default:
    Wire.write(static_cast<uint8_t>(0x00));
    break;
  }
}
} // namespace

void setup()
{
  Serial.begin(115200);
  Wire.begin(kI2cAddress);
  Wire.onReceive(onI2cReceive);
  Wire.onRequest(onI2cRequest);

  Serial.print("SAMD21 I2C slave online at 0x");
  Serial.println(kI2cAddress, HEX);
}

void loop()
{
  gUptimeSeconds = millis() / 1000UL;
  delay(10);
}
