#include <Arduino.h>

// En el ESP32 clásico (DevKit V1), el DAC de salida suele ser el pin GPIO 25 (DAC1) o GPIO 26 (DAC2)
const int DAC_PIN = 25; 

const float V_BIAS = 1.65;     // Voltaje central para pH = 7 (mitad de 3.3V)
const float S = 0.05916;       // Pendiente de Nernst (V/pH)

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("--- Laboratorio 2: Simulador de pH con ESP32 ---");
  Serial.println("Ingrese un valor de pH entre 0 y 14 en el Monitor Serie:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    float pH = input.toFloat();
    
    // Validar que el valor esté dentro del rango 0 - 14
    if (pH < 0.0 || pH > 14.0) {
      Serial.println("ADVERTENCIA: El valor de pH debe estar entre 0 y 14.");
      return;
    }
    
    // Cálculo del voltaje teórico de Nernst: Vin = Vbias - S * (pH - 7)
    float V_in = V_BIAS - S * (pH - 7.0);
    
    // Convertir el voltaje (0 a 3.3V) a valor entero de DAC de 8 bits (0 a 255)
    // El DAC del ESP32 es de 8 bits: 0V -> 0, 3.3V -> 255
    int dacValue = (int)((V_in / 3.3) * 255.0);
    if (dacValue < 0) dacValue = 0;
    if (dacValue > 255) dacValue = 255;
    
    // Escribir en el pin DAC físico
    dacWrite(DAC_PIN, dacValue);
    
    // Imprimir retroalimentación en consola
    Serial.print("pH Ingresado: ");
    Serial.print(pH, 2);
    Serial.print(" | V_in Generado (Teorico): ");
    Serial.print(V_in, 4);
    Serial.println(" V");
  }
}