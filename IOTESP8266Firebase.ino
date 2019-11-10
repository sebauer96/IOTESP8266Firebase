#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

const char* ssid = "wifi ssid";
const char* password = "wifi password";
const int rele =  14; 
FirebaseData firebaseData;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  //Configuración  del GPIO14
  pinMode(rele, OUTPUT);

  
  
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED) //Chequea si ya se conectó al wifi
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  Firebase.begin("yout_project_id.firebaseio.com", "your_Firebase_database_secret");
  
}

void loop() {
  


  if (WiFi.status() == WL_CONNECTED) {
     if (Firebase.getBool(firebaseData, "/Estado/Prendido")) //Obtenemos el estado de nuestro booleano en firebase {
      if(firebaseData.boolData() == 0)
      {
        
        digitalWrite(rele, HIGH);
        Serial.println("Apagar");
      }
      else {
        
        digitalWrite(rele, LOW);
        Serial.println("Prender");
      }
    

  } else {
    Serial.println(firebaseData.errorReason());
  }
  }
  // Delay
  delay(5000);
}
