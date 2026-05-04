// Secuencias con 4 LEDs

//Librerias

//Definicion de Pines
// const int ledPin = 10;
// const int ledPin2 = 11;
// const int ledPin3 = 12;
// ...
// En lugar de definir cada pin por separado, se puede utilizar un array para almacenar los pines de los LEDs
const int ledPins[] = {10, 11, 12, 13}; //Pines de los LEDs

//Definicion de variables

/**
    * El setup se ejecuta una sola vez al iniciar el programa
     y se utiliza para configurar los pines, iniciar la comunicacion serial, etc.
 */
void setup(){
    // Configura los pines de los LEDs como salida
    // El bucle for se utiliza para configurar cada pin del array ledPins como salida
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}

/**
    * El loop se ejecuta continuamente despues de setup, y es donde se coloca el codigo que se desea ejecutar repetidamente.
     En este caso, se imprime "Hola Mundo" en el monitor serial cada segundo.
 */
void loop(){
    // TODO: Agregar secuencia de encendido y apagado de los LEDs
    // PISTA: Utilizar bucles for para controlar el encendido y apagado de los LEDs

    // Ejemplo: digitalWrite(ledPins[i], HIGH); //Enciende el LED
    //           delay(500); //Espera 500 ms
}