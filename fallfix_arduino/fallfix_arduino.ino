const int FSR_PIN1 = A0;// Pin connected to FSR/resistor divider
const int FSR_PIN2 = A1;
const int FSR_PIN3 = A2;
const int FSR_PIN4 = A3;
const int LED_PIN1 = 11;
const int LED_PIN2 = 12;
const int LED_PIN3 = 4;
int age = 65; 
boolean gender = false;
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor
int count = 0; 
int hm = 0;
boolean flag = true; 
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 30000;  //the value is a number of milliseconds
boolean flag2 = false;

#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "DukeVisitor"; //  your network SSID (name)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
char server[] = "172.28.87.86";    // name address for Arduino (using DNS)

// Initialize the Wifi client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN1, INPUT);
  pinMode(FSR_PIN2, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
 
  pinMode(2, INPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
}


float getForce(int pin) {
  int fsrADC = analogRead(pin);
   
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600)  {
      force = (fsrG - 0.00075) / 0.00000032639;
    } else {
      force =  fsrG / 0.000000642857;
    }      
    return force;
}

void loop() 
{
    if(digitalRead(2)==HIGH){
      hm=1;
      startMillis = millis();
      flag2 = true;
    }
    if(hm==0){
      if(flag2){
      flag2=false;}
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
    }
    if(hm==1){
    int force1 = getForce(FSR_PIN1);
    int force2 = getForce(FSR_PIN2);
    int force3 = getForce(FSR_PIN3);
    int force4 = getForce(FSR_PIN4); 
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
    currentMillis = millis();
    Serial.println("Force 1: " + String(force1) + " g");
    Serial.println("Force 2: " + String(force2) + " g");
    Serial.println("Force 3: " + String(force3) + " g");
    Serial.println("Force 4: " + String(force4) + " g");
    Serial.println("Count is at "+String(count));
    Serial.println();
    if(currentMillis - startMillis >= period){
      Serial.println("---------------------------------------------");
      Serial.println("Time has Elapsed: Final count is "+ String(count));
      delay(4000);
      if(age>=90){
        if(gender){
          if(count>=4){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
 
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=7){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          } 
        }
      }
      else if(age>=85){
        if(gender){
          if(count>=8){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=8){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
           
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          } 
        }
      }
      else if(age>=80){
        if(gender){
          if(count>=9){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
           
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=10){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          } 
        }
      }
      else if(age>=75){
        if(gender){
          if(count>=10){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=11){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          } 
        }
      }
      else if(age>=70){
        if(gender){
          if(count>=10){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=12){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
         
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
           
            delay(5000);
            hm=0;
            count =0;
          } 
        }
        
      }
      else if(age>=65){
        if(gender){
          if(count>=11){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
           
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
            
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=12){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
           
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
           
            delay(5000);
            hm=0;
            count =0;
          } 
        }
      }
      else{
        if(gender){
          if(count>=12){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
            
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
          
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=14){
            digitalWrite(12, HIGH);
            digitalWrite(11, LOW);
           
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
         
            delay(5000);
            hm=0;
            count =0;
          } 
        }
      }
    }
    int totalForce = force1+force2+force3+force4;
    Serial.println("Force: " + String(totalForce) + " g");
    delay(500);
    if(flag==true){
      if (totalForce>8000){
        count++;
        Serial.println("\nStarting connection to server...");
        // if you get a connection, report back via serial:
        if (client.connect(server, 80)) {
          Serial.println("Connected to server");
          // Make a HTTP request:
          client.println("GET /input/arya123/" + String(count) + " HTTP/1.1");
          client.println("Host: http://172.28.87.86:80");
          client.println("Connection: close");
          client.println();
          Serial.println("Request sent");
        }
        client.flush();
        
        flag = false;
      }
    }
    if(flag==false){
      if(totalForce<1000){
        flag = true;
      }
    }
   
    }
}
