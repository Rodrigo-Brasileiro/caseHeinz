// O projeto HEINZ agricultura vertical
#include "dht.h" // inclui biblioteca baixada do sensor DHT-11
#include <LiquidCrystal.h> // inclui biblioteca da tecla LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;
float sensordeluminosidade = A0;
const int pinoDHT11 = A2;
float valorldr = 0;
int umidadesolo = 0;
int sensorsolo = 0;
int motor = 10;
int motorState = 1;
int IntensidadeLuz;
int led_laranja = 13;

void setup()
{
  	pinMode(A2, INPUT);
  	pinMode(A3, INPUT);
  	pinMode(A4, INPUT);
  	pinMode(motor, OUTPUT);
	  pinMode(sensordeluminosidade, INPUT);
    lcd.begin(16, 2);
  	Serial.begin(9600);
  	pinMode(13, OUTPUT);
  	
}
void loop()
{
 
   	umidadesolo = analogRead(A0); // lê o valor da entrada a0
   	sensorsolo = map(umidadesolo, 0, 1023, 0, 100);
    DHT.read11(pinoDHT11);  // lê o pino A2 Dht11
    valorldr = analogRead(sensordeluminosidade); // lé o pino a0
    IntensidadeLuz = map(valorldr, 0, 1023, 1, 100); // deixa o valor lido no a0 entre 1 a 100
    
    lcd.clear(); // tela lcd é "limpa"
   	delay(100);
   	
    analogWrite(13, map(analogRead(A4), 0, 1023, 0, 255));
	luz();
}
long luz() { //começo das funções implementadas para ler e avaliar as condições apresentadas pelos sensores, tomando as medidas corretas estavelecidas
  if((IntensidadeLuz) >= 0  && (IntensidadeLuz) <= 20){ 
      lcd.setCursor(0, 0);
      lcd.print("Ambiente claro");
      lcd.setCursor(14,0);
      lcd.print(IntensidadeLuz); 
      lcd.setCursor(0, 1);
      lcd.print("Altera a luz LED");
      delay(5000);
      temp();
  }
  if((IntensidadeLuz) > 20 && (IntensidadeLuz) < 50 ){
      lcd.setCursor(0, 0);
      lcd.print("Ambiente ideal");
      lcd.setCursor(0, 1);
      lcd.print(IntensidadeLuz); 
      delay(5000);
      temp();
  }
  if((IntensidadeLuz) >=  50){
      lcd.setCursor(0, 0);
      lcd.print("Local escuro");
      lcd.setCursor(14,0);
      lcd.print(IntensidadeLuz); 
      lcd.setCursor(0, 1);
      lcd.print("Altera a luz LED");
      delay(5000);
      temp();
  }
}

long temp() {
  if((DHT.temperature) >= 20 && (DHT.temperature) <= 30 ){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp OK");
      lcd.setCursor(0, 10);
      lcd.print(DHT.temperature);
      lcd.setCursor(5, 1);
      lcd.print("C");
      delay(5000);
      umi();
      
  }
  if((DHT.temperature) < 10){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp baixa");
      lcd.setCursor(0, 10);
      lcd.print(DHT.temperature);
      lcd.setCursor(5, 1);
      lcd.print("C");
      delay(5000);
      umi();
      
  }
  if((DHT.temperature) > 30){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp alta");
      lcd.setCursor(0, 10);
      lcd.print(DHT.temperature);
      lcd.setCursor(5, 1);
      lcd.print("C");
      delay(5000);
      umi();  
  }
}
long umi() {
  if((DHT.humidity) >= 50 && (DHT.humidity) <= 70){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Umidade ok");
      lcd.setCursor(0, 1);
      lcd.print(DHT.humidity);
      lcd.print("%");
      delay(5000);
      solo();
  }
  if((DHT.humidity) < 50){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Umidade baixa");
      lcd.setCursor(0, 1);
      lcd.print(DHT.humidity);
      lcd.print("%");
      delay(5000);
      solo();
  }
  if((DHT.humidity) > 70){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Umidade Alta");
      lcd.setCursor(0, 1);
      lcd.print(DHT.humidity);
      lcd.print("%");
      delay(5000);
      solo();
  }
}
long solo(){
  if((sensorsolo) > 50 && (sensorsolo) < 90){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Solo umido");
      digitalWrite(motor, HIGH);
      delay(5000);
  }
  if((sensorsolo) < 50){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Solo seco");
      lcd.setCursor(0, 1);
      lcd.print("Ativando agua");
      motorState = digitalRead(motor);
      digitalWrite(motor, LOW);
      delay(5000);
  }
  if ((sensorsolo) > 90 ){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Solo inundado");
      delay(5000);
  }
}