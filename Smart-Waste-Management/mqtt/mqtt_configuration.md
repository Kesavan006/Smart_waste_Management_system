# MQTT Configuration

The supplied firmware is configured for an MQTT broker using TLS on port `8883`.

## Repository-safe configuration

The GitHub version contains:

```cpp
const char* mqttUser = "YOUR_HIVEMQ_USERNAME";
const char* mqttPassword = "YOUR_HIVEMQ_PASSWORD";
```

Replace these locally with your own credentials.

### Important

Never commit:

- MQTT passwords
- Wi-Fi passwords
- API keys
- Access tokens
- Private certificates/keys

The firmware currently uses `espClient.setInsecure()` for testing in Wokwi. For a production deployment, certificate verification should be configured instead.
