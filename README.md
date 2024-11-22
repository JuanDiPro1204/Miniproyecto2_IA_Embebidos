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
- **AppInventor**: Plataforma utilizada para la elaboración de la aplicación para las notificaciones.

> :memo: **Nota:** El proyecto inicialmente se deseaba para que según la clasificación del audio, activara una serie de servomotores para cada cultivo, por lo cual el documento MINIPROYECTO 2.pdf detalla información dirigida a este objetivo , pero para esta idea de los servos se puede realizar la implementación del mismo código para subir al arduino nano 33 BLE sense (Archivo llamado Código-librería-despliegueArduinoNano.ino), pero ahora se le debe conecar un modulo HC-05 a los pines **Rx** y **Tx** del arduino nano 33 para que este funcione como maestro, y se debe usar un arduino uno para mover los servomotores (ya que la idea es la comunicación inalambrica entre los dispositivos embebidos), además se le deben conectar los servomotres al arduino uno para la señal de control (Debido a que por potencia el arduino uno no puede suministrarle la corriente necesaria a los servos, por lo cual se necesita una alimentación externa y se debe tener tierra común con el arduino uno), por otra parte, al arduino uno se le debe conectar un módulo bluetooth HC-06 o HC-05 para que funcione como esclavo que también debe ir conectado por los pines **Rx** y **Tx**. Por último, a este arduino uno se le sube el código del archivo llamado Codigo_miniproyecto_2_para_ArduinoUNO.ino para el control de los servos con el resultado de la clasificación.

---

## 🎯 Objetivos

### Objetivo General
Desarrollar un sistema inteligente de riego basado en **TinyML** para identificar comandos de voz que indica cuando se activa/desactiva el riego de cultivos específicos y notificarlo mediando una aplicación de appinventor.

### Objetivos Específicos
1. Capturar y procesar señales de audio para clasificar cinco comandos: *banano, cebolla, mandarina, zanahoria y apagar*.  
2. Entrenar un modelo de clasificación utilizando un conjunto de datos dividido en 80% para entrenamiento y 20% para prueba.  
3. Implementar y cuantizar el modelo en un microcontrolador Arduino.  
4. Resolver problemas de despliegue en tiempo real mediante optimizaciones en el IDE de Arduino.
5. Mandar por bluetooth la categoría en la que se clasifique el audio captado.  

---

## 🔧 Metodología

### Componentes del sistema:
1. **Arduino Nano 33 BLE Sense**: Captura y procesa comandos de voz con ayuda del micrófono integrado (**Los datos capturados en el edge impulse se encuentran en el archivo Dataset.zip**).  
2. **Micrófono integrado**: Registra los comandos de audio en tiempo real.    
3. **Edge Impulse**: Plataforma utilizada para entrenar el modelo de clasificación.  
4. **Bluetooth**: Permite la comunicación y el control remoto.
5. **Aplicacion de AppInventor**: Notifica que cultivo se está regando con base al comando de voz que se le indique.

---

## 🚀 Implementación

### **Fase 1: Entrenamiento del Modelo en Edge Impulse**
- Conjunto de datos: 625 muestras para entrenamiento y 158 para prueba, distribuidas en cinco clases (**Los datos capturados se encuentran en el archivo llamado Dataset.zip**).  
- Arquitectura: Red neuronal convolucional (CNN) con 3 capas y filtros de tamaño 12, 24 y 36.  
- Optimización: Se aplicó **data augmentation** para añadir ruido y mejorar la robustez del modelo.  

[🔗 Proyecto en Edge Impulse](https://studio.edgeimpulse.com/public/535477/live)

### **Fase 2: Despliegue en Arduino Nano 33 BLE Sense**
- Cuantización del modelo: Convertido a **TensorFlow Lite (int8)** para optimizar su tamaño.  
  
### **Fase 3: Comunicación entre el Arduino nano 33 BLE sense y la aplicación**
- Para la comunicación entre estos, se utilizó un módulo HC-06 conectado directamente en el Nano 33 mediante sus puertos **Tx** y **Rx** en donde se enviará la categoría con mayor porcentaje de clasificación del audio.

### **Fase 4: Replicación en Google Colab**
- Se replicó el modelo en **Colab**, con importación de datos tomados con el arduino nano 33 para el entrenamiento y la validación, preprocesamiento y entrenamiento.  
- Se intentó el despliegue desde **Colab**, pero no se logró implementar completamente.

> :memo: **Nota:** El despliegue de la red se deseaba realizar con el código elaborado en colab (Es el archivo llamado Miniproyecto2_Embebidos.ipynb de este repositorio), en este cuaderno de colab las últimas líneas de código descargan el modelo convertido a tensorflow lite (Es el archivo llamado miniproyecto_model.tflite), sin embargo para subir el archivo al arduino Nano 33, se debía realizar con el IDE de arduino, y para esto este archivo de tflite se debe pasar a un archivo de C para usar en el IDE de arduino, por lo cual se usó la aplicación de gitbash para hacer la conversión para crear el archivo llamado model.h de este repositorio para usar este en un sketch con el que se hará la deteccion y clasificación del audio. Sin embargo, se optó por usar la herramienta de edge impulse en el apartado de despliegue con lo cual se descargará la red como una librería de arduino y descargará un archivo .zip (Archivo de este repositorio llamado Librería de edge impulse.zip) que se debe añadir a la librerías del IDE de arduino y posterior a esto en el apartado de ejemplos de arduino, se encontrará un ejemplo de microfono para el arduino nano 33 BLE sense, este codigo fue utilizado como base para el archivo llamado "Código-librería-despliegueArduinoNano.ino" que es el codigo que se debe subir al arduino nano 33 para poder usar la red y clasificar los audios.

## 🛠️ Resultados 

### Resultados:
- Modelo entrenado con buena precisión.  
- Sistema funcional para la activación/desactivación de alarmas en la aplicación basada en comandos de voz.  

---

🎉 **Gracias por explorar este proyecto!**  


