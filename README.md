
# 🚀 Workshop: Sistema de Telemetría en Tiempo Real

Este proyecto permite recolectar datos de sensores desde un **Arduino**, enviarlos a través de una **Raspberry Pi** (o PC) y visualizarlos en un **Dashboard Profesional** centralizado en una red LAN.

---

## 💻 1. Guía para los Alumnos (El Cliente)

Este script se encarga de leer los datos que el Arduino envía por el puerto serie y mandarlos al servidor central.

### 📋 Prerrequisitos
Tener instalado **Python 3.x** y las librerías necesarias. Abrí una terminal y ejecutá:
```bash
pip install pyserial requests
```

### 🔌 Paso 1: Programar el Arduino
Para que el sistema entienda los datos, tenés que enviarlos desde el Arduino usando el siguiente formato: `clave:valor,clave2:valor2`.

**Ejemplo de código en Arduino IDE:**
```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  int luz = analogRead(A0);
  float temp = 25.4; // Ejemplo de valor fijo o de sensor

  // IMPORTANTE: Respetar las comas y los dos puntos
  Serial.print("luz:"); Serial.print(luz);
  Serial.print(",temp:"); Serial.println(temp);
  
  delay(1000); // Enviar cada 1 segundo
}
```

### 🏃 Paso 2: Ejecutar el Cliente

1. **Descargar** el archivo `client.py` en tu carpeta de trabajo.
2. **Conectar** el Arduino por USB.
3. **Ejecutar** el script:

#### **En Windows:**
Abrí el CMD o PowerShell en la carpeta del script y escribí:
```bash
python client.py
```

#### **En Linux (Raspberry Pi):**
Abrí la terminal y ejecutá:
```bash
python3 client.py
```
> **Nota:** Si te tira error de permisos con el puerto serial, asegurate de que tu usuario esté en el grupo `dialout` o usá `sudo chmod 666 /dev/ttyACM0` (reemplazando por tu puerto).

4. **Configurar:** El script te va a pedir el **Nombre de tu Grupo** y que selecciones el **Puerto COM/tty** de la lista.

---

## 🖥️ 2. Guía para el Coordinador (El Servidor)

El servidor central corre en **Manjaro** y centraliza la visualización de todos los grupos.

### 📋 Prerrequisitos
Instalar las librerías de FastAPI y el servidor web:
```bash
pip install fastapi uvicorn pydantic
```

### 🛠️ Configuración de Red
1. **IP Estática:** Asegurate de conocer la IP de tu PC Manjaro en la red LAN (usá `ip addr`).
2. **Firewall:** Permití el tráfico en el puerto 8000 para que las Raspberry se puedan conectar:
   ```bash
   sudo ufw allow 8000/tcp
   ```

### 🚀 Ejecución del Server
1. Guardá el código del servidor como `server.py`.
2. Ejecutalo desde la terminal:
   ```bash
   python server.py
   ```
3. El servidor estará escuchando en `http://0.0.0.0:8000`.

### 📊 Visualización
Abrí cualquier navegador (preferentemente en el server o cualquier PC de la misma red) y entrá a:
* **Dashboard:** `http://TU_IP:8000/`
* **Documentación API:** `http://TU_IP:8000/docs` (para ver si los datos están llegando).

---

## 🛠️ Estructura del Mensaje (Resumen)
Para que el Dashboard genere gráficos automáticamente, recordá que los valores deben ser **numéricos**. 
* ✅ **Bien:** `luz:500,temp:24.5`
* ⚠️ **Texto (No grafica):** `estado:OK,puerta:Abierta`

## PROMPT INTERESANTE
```bash
Rol:
Actúa como un profesor de Arduino que explica de forma clara, sencilla y paso a paso. Tu objetivo es que el estudiante entienda lo que hace, no solo que copie código.

Contexto:
Estoy aprendiendo Arduino y quiero hacer proyectos prácticos. Necesito ayuda con el código, las conexiones y la explicación de cómo funciona.

Tarea:
A partir de la descripción que te dé, genera una solución completa que incluya:

1. Materiales:
- Lista de componentes necesarios.
- Breve explicación de qué hace cada uno.

2. Conexiones:
- Tabla clara en este formato:
  COMPONENTE | PIN COMPONENTE | PIN ARDUINO
- Incluir 5V, GND, etc.
- Explicar si algo puede romperse si se conecta mal.

3. Código Arduino:
- Código completo listo para copiar y pegar.
- Comentado en español de forma clara.
- Usar cosas simples:
  - int para pines
  - delay() (permitido para simplificar)
- Evitar cosas avanzadas innecesarias.
- Priorizar que sea fácil de entender.

4. Funcionamiento:
- Explicar paso a paso qué hace el programa.
- Qué pasa en setup() y loop().
- Cómo interactúan los componentes.

5. Mejoras (opcional):
- Ideas simples para mejorar el proyecto.

Librerías (si se usan):
- Nombre de la librería.
- Para qué sirve, explicado simple.

Formato de respuesta obligatorio:

--- MATERIALES ---
--- CONEXIONES ---
--- CÓDIGO ---
--- FUNCIONAMIENTO ---
--- MEJORAS (OPCIONAL) ---

Modo de interacción:
Si falta información, primero haz preguntas simples antes de dar la solución.
```
---
