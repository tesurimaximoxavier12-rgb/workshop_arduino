// Parpadeo de LED utilizando delay y millis

//Librerias

//Definicion de Pines
const int ledPin = 13; //Pin del LED integrado en la placa

//Definicion de variables

/**
    * El setup se ejecuta una sola vez al iniciar el programa
    * y se utiliza para configurar los pines, iniciar la comunicacion serial, etc.
 */

// Funciones

// Función para parpadear el LED utilizando delay
void parpadeoConDelay(){
    digitalWrite(ledPin, HIGH); //Enciende el LED
    delay(1000); //Espera 1 segundo
    digitalWrite(ledPin, LOW); //Apaga el LED
    delay(1000); //Espera 1 segundo
}

// Función para parpadear el LED utilizando millis
void parpadeoConMilis(){
    static unsigned long previousMillis = 0; //Almacena el tiempo del último cambio de estado
    const long interval = 1000; //Intervalo de tiempo para el parpadeo (1 segundo)
    
    unsigned long currentMillis = millis(); //Obtiene el tiempo actual
    
    if (currentMillis - previousMillis >= interval) { //Si ha pasado el intervalo
        previousMillis = currentMillis; //Actualiza el tiempo del último cambio
        
        // Cambia el estado del LED
        if (digitalRead(ledPin) == LOW) {
            digitalWrite(ledPin, HIGH); //Enciende el LED
        } else {
            digitalWrite(ledPin, LOW); //Apaga el LED
        }
    }
}
//Diferencia entre delay y millis:
//- delay() bloquea la ejecución del programa durante el tiempo especificado, 
// lo que significa que no se pueden realizar otras tareas mientras el programa está en espera.

//- millis() permite realizar tareas sin bloquear el programa, ya que se basa en el tiempo transcurrido 
// desde que el programa comenzó a ejecutarse. Esto permite que el programa realice otras tareas mientras espera que 
// se cumpla el intervalo de tiempo para el parpadeo del LED.    


void setup(){
    pinMode(ledPin, OUTPUT); //Configura el pin del LED como salida
}

/**
    * El loop se ejecuta continuamente despues de setup, y es donde se coloca el codigo que se desea ejecutar repetidamente.
    *En este caso, se imprime "Hola Mundo" en el monitor serial cada segundo.
 */
void loop(){
    parpadeoConMilis();
}

