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
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 30000;  //the value is a number of milliseconds
boolean flag2 = false;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN1, INPUT);
  pinMode(FSR_PIN2, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Press Button to ");
  lcd.setCursor(0,2); 
  lcd.print("Begin");
  pinMode(2, INPUT);
}


float getForce(int pin) {
  int fsrADC = analogRead(pin);
    lcd.clear();
    lcd.print("Count: "+String(count));
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
    if (fsrR <= 600)  {
      force = (fsrG - 0.00075) / 0.00000032639;
    } else {
      force =  fsrG / 0.000000642857;
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
      lcd.clear();
      lcd.print("Press Button to ");
      lcd.setCursor(0,2); 
      lcd.print("Begin ");
      flag2=false;}
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
    if(hm==1){
    int force1 = getForce(FSR_PIN1);
    int force2 = getForce(FSR_PIN2);
    int force3 = getForce(FSR_PIN3);
    int force4 = getForce(FSR_PIN4); 
    lcd.clear();
    lcd.print("Count: "+String(count));
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
      lcd.clear();
      lcd.print("Time has Elapsed");
      lcd.setCursor(0,2);
      lcd.print("Final count: "+ String(count));
      delay(4000);
      if(age>=90){
        if(gender){
          if(count>=4){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=7){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=8){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=10){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=11){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=12){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=12){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
            delay(5000);
            hm=0;
            count =0;
          }
        }
        else{
          if(count>=14){
            digitalWrite(12, HIGH);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.print("You Passed!!");
            delay(10000);
            hm =0;
            count =0;
          }
          else{
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            lcd.clear();
            lcd.print("You are at Risk");
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
        flag = false;
      }
    }
    if(flag==false){
      if(totalForce<1000){
        flag = true;
      }
    }
    lcd.clear();
    lcd.print("Count: "+String(count));
    }
}
