# IBIII-Lab2-Etapa de ganancia y calibración

Repositorio del Laboratorio 2 del curso de Instrumentación Biomédica III en el cual se diseñó una etapa de amplificación no inversora que expande la señal bufferizada de un electrodo de pH simulado, y se calibró el sistema completo mediante regresión lineal.

## Objetivo

- Diseñar e implementar un amplificador no inversor con el TL084 que multiplique la señal bufferizada por una ganancia conocida (Av = 3), sin saturar la salida.
- Verificar experimentalmente la ganancia del amplificador y compararla con el valor teórico Av = 1 + Rf/R1.
- Construir una curva de calibración (voltaje de salida vs. pH simulado) mediante regresión lineal, obteniendo su ecuación y su R².
- Calcular la sensibilidad del sistema completo (buffer + amplificador) y su error respecto al valor esperado (Av·S ≈ 0.1775 V/pH).

## Cómo reproducir el experimento

1. Cargar el archivo de código .ino en el ESP32 usando el IDE de Arduino (Recuerda colocarlo con board: "ESP32 Dev Module"). El programa genera por el DAC (GPIO25) el voltaje Vin = 1.65 − 0.05916·(pH − 7) y solo acepta valores de pH entre 0 y 14.
2. Armar el circuito siguiendo el esquemático:
   - Etapa A (buffer): GPIO25 del ESP32 a la entrada no inversora del TL084 (pin 3); entrada inversora (pin 2) unida a la salida (pin 1). La salida del buffer es el punto de prueba TP1.
   - Etapa B (amplificador no inversor): TP1 a la entrada no inversora (pin 5); Rf = 20 kΩ (dos resistencias de 10 kΩ en serie) entre la salida (pin 7) y la entrada inversora (pin 6); R1 = 10 kΩ entre el pin 6 y GND. La salida del amplificador es el punto de prueba TP2.
   - Alimentar el TL084 con ±12 V (pin 4 = V+, pin 11 = V−). Los amplificadores sin usar (pines 8-9-10 y 12-13-14) se dejan en configuración seguidor.
3. Abrir el Monitor Serial (115200 baudios) e ingresar un valor de pH entre 0 y 14.
4. Etapa A: comparar con el multímetro el voltaje de salida del ESP32 y el de TP1 (la diferencia debe ser menor a 10 mV).
5. Etapa B: medir Vout en TP2 para pH = 0 y pH = 14 y calcular la ganancia experimental Av = ΔVout / ΔVin.
6. Etapa C: medir con el multímetro el voltaje en TP2 para pH = 0, 2, 4, 6, 8, 10, 12 y 14, y registrar los valores.
7. Realizar la regresión lineal Vout vs. pH y obtener la pendiente, el intercepto y el R²; comparar la sensibilidad experimental con la teórica.

## Autores
- Tito Fernandez, Dante Adrian       23190133
- Lázaro Canales, Jair Renato        23190377
- Arroyo Ramos, Rosbeth Nayelhy      23190114

- Tito Fernandez, Dante Adrian
- Lázaro Canales, Jair Renato
- Arroyo Ramos, Rosbeth Nayelhy
