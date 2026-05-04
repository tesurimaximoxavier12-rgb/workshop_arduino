import serial
import serial.tools.list_ports
import requests
import time
import sys

# === CONFIGURACIÓN ===
SERVER_IP = "192.168.1.100"  # <--- CAMBIAR POR LA IP DE TU MANJARO
PORT = 8000
URL = f"http://{SERVER_IP}:{PORT}/update"
BAUD_RATE = 9600

def seleccionar_puerto():
    """Lista los puertos disponibles y le pide al usuario que elija uno."""
    while True:
        puertos = list(serial.tools.list_ports.comports())
        
        if not puertos:
            print("\n [X] No se detectaron puertos serie.")
            input("Conectá el Arduino y presioná Enter para reintentar...")
            continue

        print("\n--- Puertos Disponibles ---")
        for i, p in enumerate(puertos):
            print(f"[{i}] {p.device} - {p.description}")
        
        try:
            opcion = input("\nSeleccioná el número del puerto: ")
            idx = int(opcion)
            if 0 <= idx < len(puertos):
                return puertos[idx].device
            else:
                print(" [?] Número fuera de rango. Intentá de nuevo.")
        except ValueError:
            print(" [?] Por favor, ingresá un número válido.")

def parsear_linea(linea):
    """Convierte 'temp:25.5,hum:40' en un diccionario."""
    try:
        partes = linea.split(',')
        datos = {}
        for p in partes:
            clave, valor = p.split(':')
            datos[clave.strip()] = valor.strip()
        return datos
    except Exception:
        return None

def main():
    print("==========================================")
    print("   CLIENTE DE TELEMETRÍA - MANUAL        ")
    print("==========================================\n")

    # 1. Identificación
    grupo = input(">> Nombre del Grupo: ").strip()
    while not grupo:
        grupo = input(">> El nombre no puede estar vacío: ").strip()

    # 2. Selección de Puerto
    puerto_elegido = seleccionar_puerto()
    
    try:
        # 3. Conexión Serial
        ser = serial.Serial(puerto_elegido, BAUD_RATE, timeout=1)
        ser.reset_input_buffer()
        print(f"\n[+] Conectado a {puerto_elegido}")
        print(f"[+] Enviando datos a: {URL}")
        print("[*] Presioná Ctrl+C para cerrar.\n")

        # 4. Bucle Principal
        while True:
            if ser.in_waiting > 0:
                try:
                    linea_raw = ser.readline().decode('utf-8', errors='ignore').strip()
                    
                    if linea_raw:
                        datos_dict = parsear_linea(linea_raw)
                        
                        if datos_dict:
                            payload = {"group_name": grupo, "data": datos_dict}
                            try:
                                r = requests.post(URL, json=payload, timeout=1)
                                if r.status_code == 200:
                                    print(f" [OK] {grupo} -> {datos_dict}")
                                else:
                                    print(f" [!] Error Server ({r.status_code})")
                            except requests.exceptions.RequestException:
                                print(f" [!] Error: Sin conexión con el servidor.")
                        else:
                            print(f" [?] Error de formato en: {linea_raw}")
                
                except Exception as e:
                    print(f" [!] Error en lectura: {e}")
            
            time.sleep(0.01)

    except KeyboardInterrupt:
        print("\n\n[!] Saliendo...")
    except Exception as e:
        print(f"\n[X] Error crítico: {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()