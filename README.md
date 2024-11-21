# Automatización del Riego de Cultivos Mediante Reconocimiento de Voz con TinyML 🌱🎤

---

## 📋 Resumen

Este proyecto implementa un sistema de notificación de riego de cultivo basado en **TinyML** y el reconocimiento de voz.  
El modelo es capaz de clasificar comandos para mandar notificaciones a una aplicación de appinventor y asociarlo a diferentes cultivos:
- **Tomate**
- **Cebolla**
- **Mandarina**
- **Zanahoria**
- **Banano**  
Además, incluye el comando "apagar" para indicar la finalización del riego de los cultivos.  

### Principales Componentes:
- **Arduino Nano 33 BLE Sense**: Microcontrolador central con micrófono integrado.
- **Edge Impulse**: Plataforma utilizada para el entrenamiento del modelo de reconocimiento de voz.
- **TensorFlow Lite**: Para la cuantización y despliegue del modelo en dispositivos embebidos.
- **Bluetooth**: Comunicación inalámbrica para el monitoreo remoto.

---

## 🎯 Objetivos

### Objetivo General
Desarrollar un sistema inteligente de riego basado en **TinyML** para identificar comandos de voz que activen/desactiven el riego de cultivos específicos.

### Objetivos Específicos
1. Capturar y procesar señales de audio para clasificar cinco comandos: *banano, cebolla, mandarina, zanahoria y apagar*.  
2. Entrenar un modelo de clasificación utilizando un conjunto de datos dividido en 80% para entrenamiento y 20% para prueba.  
3. Implementar y cuantizar el modelo en un microcontrolador Arduino.  
4. Resolver problemas de despliegue en tiempo real mediante optimizaciones en el IDE de Arduino.  

---

## 🔧 Metodología

### Componentes del sistema:
1. **Arduino Nano 33 BLE Sense**: Captura y procesa comandos de voz.  
2. **Micrófono integrado**: Registra los comandos de audio en tiempo real.  
3. **Servomotores**: Controlan el riego en función de la clasificación del comando.  
4. **Edge Impulse**: Plataforma utilizada para entrenar el modelo de clasificación.  
5. **Bluetooth**: Permite la comunicación y el control remoto.  

---

## 🚀 Implementación

### **Fase 1: Entrenamiento del Modelo**
- Conjunto de datos: 625 muestras para entrenamiento y 158 para prueba, distribuidas en cinco clases.  
- Arquitectura: Red neuronal convolucional (CNN) con 3 capas y filtros de tamaño 12, 24 y 36.  
- Optimización: Se aplicó **data augmentation** para añadir ruido y mejorar la robustez del modelo.  

[🔗 Proyecto en Edge Impulse](https://studio.edgeimpulse.com/public/535477/live)

### **Fase 2: Despliegue en Arduino Nano 33 BLE Sense**
- Cuantización del modelo: Convertido a **TensorFlow Lite (int8)** para optimizar su tamaño.  
- Control de riego: Cada comando activa un servomotor que abre el flujo de agua hacia un cultivo específico.

### **Fase 3: Comunicación entre Arduinos**
- Comunicación directa mediante puertos **Tx** y **Rx** debido a limitaciones con módulos Bluetooth disponibles.

### **Fase 4: Replicación en Google Colab**
- Se replicó el modelo en **Colab**, con importación de datos, preprocesamiento y entrenamiento.  
- Se intentó el despliegue desde **Colab**, pero no se logró implementar completamente.

---

## 🛠️ Resultados y Mejoras Futuras

### Resultados:
- Modelo entrenado con buena precisión.  
- Sistema funcional para la activación/desactivación de motores basada en comandos de voz.  

### Mejoras Futuras:
1. **Optimización del preprocesamiento de audio** para mejorar la calidad del reconocimiento.  
2. **Ampliación del dataset** para incluir más clases y aumentar la robustez frente a diferentes acentos.  
3. **Integración de sensores adicionales** (humedad, temperatura) para un riego más eficiente.  
4. Desarrollo de una **Interfaz Gráfica de Usuario (GUI)** para facilitar el monitoreo remoto.  

---

## 🌍 Alineación con los Objetivos de Desarrollo Sostenible (ODS)
- **ODS 6: Agua limpia y saneamiento**: Uso eficiente del agua en el riego.  
- **ODS 12: Producción y consumo responsables**: Optimización de recursos en prácticas agrícolas.  

---

## 📜 Referencias
- [Arduino Nano 33 BLE Sense](https://store.arduino.cc/nano-33-ble-sense)  
- [Edge Impulse Docs](https://docs.edgeimpulse.com/docs/tutorials/arduino-nano-33-ble-sense)  

---

## 📂 Estructura del Proyecto
