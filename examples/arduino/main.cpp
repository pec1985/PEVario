#include <Arduino.h>
#include <PEVario.hpp>

// barometric pressure sensor
#include <MS5611.h>

#define BUZZER_PIN = 8;

MS5611 ms5611;
PE::Vario vario;

void varioCallback(double frequency, double duration, bool hasSound);

void setup() 
{
    Serial.begin(115200);
    
    // pressure sensor
    ms5611.begin();
    vario.begin(millis());
    m_vario.setCallback(&varioCallback);
}

void loop() 
{
    vario.update(ms5611.getPressure(), millis());
    vario.resetTime(millis());
}

// `duration` does not need to be used
void varioCallback(double frequency, double duration, bool hasSound) 
{
    if (!hasSound) {
        noTone(BUZZER_PIN);
        pinMode(BUZZER_PIN, LOW);
        return;
    }
    tone(BUZZER_PIN, frequency);
}
