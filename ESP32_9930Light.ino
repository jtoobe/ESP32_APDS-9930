/****************************************************************

 ESP32     APDS-9930 Board     Funcion
 
 3.3V         VCC              Power
 GND          GND              Ground
 21           SDA              I2C Data
 22           SCL              I2C Clock
****************************************************************/

#define DUMP_REGS

#include <Wire.h>
#include <APDS9930.h>

// Pins ESP32
 
#define APDS9960_SDA    21  
#define APDS9960_SCL    22  


// Variables Globales
APDS9930 apds = APDS9930();
float ambient_light = 0; // podria tambien ser long
uint16_t ch0 = 0;
uint16_t ch1 = 1;

void setup() 
{

   //Arranca I2C con los pines definidos
  Wire.begin(APDS9960_SDA,APDS9960_SCL);
  
  // Inicializa el Serial port
  Serial.begin(115200);
  Serial.println();
  
  // Inicializa APDS-9930 (configura I2C y valores iniciales)
  if ( apds.init() ) 
  {
    Serial.println("APDS-9930 ok");
  } 
  else 
  {
    Serial.println("APDS-9930 Fallo !!!");
  }
  
  // Start running the APDS-9930 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) 
  {
    Serial.println("Sensor de Luz corriendo !!");
  } 
  else 
  {
    Serial.println("Algo fallo al inicializar el sensor de luz!");
  }

  // espera por finalizacion y calibracion
  delay(1000);
}


void loop() 
{
  
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLightLux(ambient_light) ||
        !apds.readCh0Light(ch0) || 
        !apds.readCh1Light(ch1) ) {
    Serial.println("Error leyendo valores de luz");
  } 
  else 
  {
    Serial.print("Ambiente: ");
    Serial.print(ambient_light);
    Serial.print("  Ch0: ");
    Serial.print(ch0);
    Serial.print("  Ch1: ");
    Serial.println(ch1);
  }
  
  // Wait 1 second before next reading
  delay(1000);
}

