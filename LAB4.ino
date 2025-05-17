#include <Arduino.h>

// STM32 Pin Definitions (adjust based on your board)
#define LDR_PIN PA7    // ADC1_IN0
#define POT_PIN PB0    // ADC1_IN1
#define PWM_PIN PA0    // TIM3_CH1

// STM32 Configuration
const float VREF = 5f;       
const int ADC_RESOLUTION = 4095; // 12-bit ADC

// Moving Average Filter
const int SAMPLE_SIZE = 10;
int ldrSamples[SAMPLE_SIZE], potSamples[SAMPLE_SIZE];
int ldrIndex = 0, potIndex = 0;
long ldrSum = 0, potSum = 0;

// Timing Control
unsigned long previousMillis = 0;
const long INTERVAL = 200;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // Set 12-bit ADC resolution
  
  // Initialize PWM (1KHz frequency)
  pinMode(PWM_PIN, OUTPUT);
  analogWriteFrequency(PWM_PIN, 1000); 
  analogWrite(PWM_PIN, 0);

  // Initialize sample arrays
  int initialLdr = analogRead(LDR_PIN);
  int initialPot = analogRead(POT_PIN);
  for(int i=0; i<SAMPLE_SIZE; i++){
    ldrSamples[i] = initialLdr;
    potSamples[i] = initialPot;
  }
  ldrSum = initialLdr * SAMPLE_SIZE;
  potSum = initialPot * SAMPLE_SIZE;
}

void loop() {
  // Read raw ADC values
  int ldrRaw = analogRead(LDR_PIN);
  int potRaw = analogRead(POT_PIN);

  // Update moving averages
  updateMovingAverage(ldrRaw, ldrSamples, &ldrIndex, &ldrSum);
  updateMovingAverage(potRaw, potSamples, &potIndex, &potSum);

  // Calculate filtered values
  float ldrFiltered = ldrSum / (float)SAMPLE_SIZE;
  float potFiltered = potSum / (float)SAMPLE_SIZE;

  // Control PWM (0-100% duty cycle)
  int pwmValue = map(potFiltered, 0, ADC_RESOLUTION, 0, 255);
  analogWrite(PWM_PIN, pwmValue);

  // Send data periodically
  if(millis() - previousMillis >= INTERVAL) {
    previousMillis = millis();
    
    // Convert to voltage and percentage
    float ldrVoltage = (ldrFiltered / ADC_RESOLUTION) * VREF;
    float potVoltage = (potFiltered / ADC_RESOLUTION) * VREF;
    float ldrPercent = (ldrFiltered / ADC_RESOLUTION) * 100;
    float potPercent = (potFiltered / ADC_RESOLUTION) * 100;

    // Format output
    Serial.print("LDR: ");
    Serial.print(ldrVoltage, 2);
    Serial.print("V (");
    Serial.print(ldrPercent, 1);
    Serial.print("%) \tPot: ");
    Serial.print(potVoltage, 2);
    Serial.print("V (");
    Serial.print(potPercent, 1);
    Serial.println("%)");
  }
}

// Separate moving average functions for each sensor
void updateMovingAverage(int newVal, int *samples, int *index, long *sum) {
  *sum = *sum - samples[*index] + newVal;
  samples[*index] = newVal;
  *index = (*index + 1) % SAMPLE_SIZE;
}