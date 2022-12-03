#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria a instacia do  MFRC522.

const int RELAY_PIN = 2; // Pino do rele

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin as an output.
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600); // Inicia a saida serial
  SPI.begin();  // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia a modulo MFRC522 
}

  void loop(){

    if (Serial.available() > 0){
        if (Serial.read() == 'x'){ // letra x
            Serial.println("Acionado pelo Telegram");
            digitalWrite(RELAY_PIN, HIGH);
            delay(1000);
            digitalWrite(RELAY_PIN, LOW);
            delay(1000);
        }
    }

      // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
    // Verify if the NUID has been readed
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }

    //Mostra informações do cartão na serial
    String conteudo= "";
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    conteudo.toUpperCase();
   
    if (conteudo.substring(1) == "5C E2 35 4A") //UID 1 - tag
      {
      Serial.println("Acionado via tag");
       Serial.println();
      digitalWrite(RELAY_PIN, HIGH); // ativa rele e abre a trava solenoide
      delay(1000);           // espera 3 segundos
      digitalWrite(RELAY_PIN, LOW);  // desativa rele e fecha a trava solenoide
      delay(1000);
      }
      
    if (conteudo.substring(1) == "F9 C3 6A C2") //UID 2 - tag
      {
      Serial.println("Acionado via tag");
       Serial.println();
      digitalWrite(RELAY_PIN, HIGH); // ativa rele e abre a trava solenoide
      delay(1000);           // espera 3 segundos
      digitalWrite(RELAY_PIN, LOW);  // desativa rele e fecha a trava solenoide
      delay(1000);
      }

    if (conteudo.substring(1) == "19 A5 CF C2") //UID 3 - tag
      {
      Serial.println("Acionado via tag");
       Serial.println();
      digitalWrite(RELAY_PIN, HIGH); // ativa rele e abre a trava solenoide
      delay(1000);           // espera 3 segundos
      digitalWrite(RELAY_PIN, LOW);  // desativa rele e fecha a trava solenoide
      delay(1000);
      }
      
    if (conteudo.substring(1) == "E7 BD 83 E0") //UID 4 - Cartao
    {
      Serial.println("Acionado pelo cartão Gabriel");
      Serial.println();
      digitalWrite(RELAY_PIN, HIGH); // ativa rele e abre a trava 
      delay(1000);           // espera 3 segundos
      digitalWrite(RELAY_PIN, LOW);  // desativa rele e fecha a trava solenoide
      delay(1000);
    } 

    if (conteudo.substring(1) == "AA 57 59 B6") //UID 5 - Cartao
    {
      Serial.println("Acionado pelo cartão Édelin");
      Serial.println();
      digitalWrite(RELAY_PIN, HIGH); // ativa rele e abre a trava 
      delay(1000);           // espera 3 segundos
      digitalWrite(RELAY_PIN, LOW);  // desativa rele e fecha a trava solenoide
      delay(1000);
    } 
        }
