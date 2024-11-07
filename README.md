# Proyecto: Transmisión y Recepción de Código Morse utilizando ESP32

## Descripción

Este proyecto implementa un sistema de comunicación utilizando código Morse, donde un láser, controlado por un microcontrolador ESP32, transmite información a través de pulsos de luz. Un fotoresistor (LDR) detecta los pulsos de luz en el receptor, y otro ESP32 decodifica las señales recibidas para reconstruir el mensaje original.

### Objetivo
El objetivo de este proyecto es transmitir información utilizando luz como medio de comunicación, implementando un sistema simple pero efectivo basado en código Morse. Es ideal para situaciones en las que otros métodos de comunicación (como cables o señales de radio) no son viables.

## Componentes Utilizados

- **Microcontrolador ESP32**: Controla el diodo láser y el fotoresistor.
- **Diodo láser**: Utilizado para transmitir los pulsos de luz que representan los puntos y rayas del código Morse.
- **Fotoresistor (LDR)**: Detecta los pulsos de luz provenientes del láser y convierte las señales ópticas en señales eléctricas.
- **Resistor de 10kΩ**: Utilizado para el sensor LDR en el receptor.
- **Cables jumper macho-macho**: Para conectar los componentes.

## Fundamentos Técnicos

### Modulación de Señales Ópticas
El código Morse es transmitido mediante modulación de luz: el láser se enciende y apaga para representar puntos y rayas. El tiempo de encendido determina si la señal es un punto (breve) o una raya (más larga). Esta modulación por impulsos es utilizada en la transmisión de datos digitales.

### Código Morse
El código Morse convierte letras y números en secuencias de señales ópticas (pulsos de luz) representadas por puntos y rayas. Por ejemplo:
- **A** = ".-"
- **B** = "-..."
  
### Fotoresistor o LDR
El LDR cambia su resistencia según la cantidad de luz que recibe. Su variación de resistencia es detectada por el ESP32 para interpretar los pulsos de luz y convertirlos en el código Morse correspondiente.

## Esquemas de Conexión

### Transmisor

El transmisor consta de un **diodo láser** controlado por un ESP32. El diodo está conectado al **pin GPIO5** del ESP32 para encenderse y apagarse según el código Morse que se desea transmitir.

**Esquema**:
- Diodo láser: Terminal positiva al pin GPIO5, terminal negativa a GND.

### Receptor

El receptor utiliza un **fotoresistor (LDR)** para detectar los pulsos de luz del láser. La señal del LDR se conecta a un **pin analógico** (GPIO34) del ESP32 para leer la intensidad de luz y convertirla en señales de puntos y rayas.

**Esquema**:
- LDR: Un terminal a 3.3V, el otro a una resistencia de 10kΩ, y el otro extremo de la resistencia a GND. El punto de unión entre el LDR y la resistencia se conecta al pin GPIO34.

## Procedimiento

1. **Configuración del Transmisor**: El ESP32 actúa como servidor web, permitiendo que los usuarios ingresen un mensaje que será convertido a código Morse y transmitido mediante el láser.
   
2. **Configuración del Receptor**: El ESP32 receptor recibe las señales del LDR, las evalúa para determinar si corresponden a un punto o una raya y luego las decodifica en texto.

3. **Pruebas**: El sistema fue probado para garantizar la correcta transmisión y recepción del mensaje en código Morse. Se ajustaron los tiempos de transmisión para minimizar errores de decodificación.

## Código

El proyecto está implementado utilizando la plataforma Arduino IDE para programar ambos ESP32. El código de cada parte del sistema (transmisor y receptor) se encuentra en los archivos correspondientes.

### Archivos de código:
- `transmisor.ino`: Código para el ESP32 transmisor.
- `receptor.ino`: Código para el ESP32 receptor.

## Resultados

El sistema transmite y recibe mensajes en código Morse con una tasa de error baja en condiciones controladas. Sin embargo, el sistema sigue siendo sensible a la interferencia lumínica ambiental, lo que limita su eficacia en entornos con alta luz ambiental.

## Conclusiones

El proyecto demostró la viabilidad de utilizar luz como medio para transmitir datos simples en forma de código Morse. A pesar de las limitaciones de interferencia lumínica, se logró una comunicación precisa y eficiente en condiciones controladas.

## Referencias

1. National Geographic. (2024). "Código Morse: ¿qué es, cómo funciona y qué tiene que ver con el Titanic?"
2. 123RF. (2024). "Tabla de código Morse".
3. Tecnosalva. (2024). "Qué es y cómo funciona una LDR".
4. Grupostop. (2024). "Qué es un diodo láser y cómo funciona".
5. REPOSITORIO ACADÉMICO DIGITAL. (2024). "Resistor / resistencia".
6. TodoMaker. (2024). "CONOCIENDO AL ESP32".
7. Instructable. (2017). "Morse Code Communication Transmitter and Receiver"
