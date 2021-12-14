/*Pinagem
  *LCD RS - pino D4
  *LCD EN - pino D4
  *LCD D4 - pino D4
  *LCD D5 - pino D4
  *LCD D6 - pino D4
  *LCD D7 - pino D4
  *
  *RFID NSS - pino D4
  *RFID SCK - pino D4
  *RFID MOSI - pino D4
  *RFID MISO - pino D4
  *
  *LED Vermelho - pino D4
  *LED Verde - pino D4
  *
  * Rele - pino 12
*
*/

#include <SPI.h>            // Comunicacao com o modulo RFID
#include <MFRC522.h>        // Biblioteca do modulo RFID
#include <LiquidCrystal.h>  // Biblioteca da tela

#define SS_PIN 10
#define RST_PIN 9
#define atuador 2

int intervalo = 5000; // Tempo que a trava ficara aberta em ms

// Instanciando o modulo RFID e LCD
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(4,3,5,6,7,8);

String UID = "";

void setup() {
  SPI.begin();        // Inicia comunicacao SPI
  mfrc522.PCD_Init(); // Inicia o modulo RFID
  lcd.begin(16,2);    // Inicializa o display LCD
  boot();             // Rotina de texto inicial
}

void boot() {
  lcd.clear();
  lcd.print("Aproxime o seu");
  lcd.setCursor(0, 1);
  lcd.print("cartao no leitor");

  // Garante que o pino do atuador seja iniciado sem energia
  digitalWrite(atuador, LOW);
}

void abrir() {
  // Abre a fechadura e depois a fecha
  digitalWrite(atuador, HIGH);
  delay(intervalo);
  digitalWrite(atuador, LOW);
}

void ler_cartao() {
  // Procurar cartao
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Ler dados do cartao
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Receber UID do cartao
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    UID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
}

void resposta (){
  UID.toUpperCase();

  //UID esperada do cartao liberado
  if (UID.substring(1) == "FF FF FF FF") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem vindo");
    lcd.setCursor(0, 1);
    lcd.print("Acesso liberado!");
 } 

  //UID esperada do cartao bloqueado
  else if (UID.substring(1) == "00 00 00 00") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Usuario");
    lcd.setCursor(0, 1);
    lcd.print("Bloqueado");
  }
  else if (UID.substring(1) != ""){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acesso negado");
  }
}

void loop() {
  ler_cartao();
  resposta();
}
