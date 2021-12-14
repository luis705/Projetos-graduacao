/*Pinagem
   LCD RS - pino D4
   LCD EN - pino D4
   LCD D4 - pino D4
   LCD D5 - pino D4
   LCD D6 - pino D4
   LCD D7 - pino D4

   RFID CS - pino D4
   SD CS - pino A0
   SCK - pino D13
   MOSI - pino D11
   MISO - pino D12

   LED Vermelho - pino D4
   LED Verde - pino D4

    Rele - pino 12

*/

#include <SPI.h>            // Comunicacao com o modulo RFID
#include <MFRC522.h>        // Biblioteca do modulo RFID
#include <LiquidCrystal.h>  // Biblioteca da tela
#include <SD.h>             // Biblioteca cartao SD
#include <Wire.h>           // Biblioteca do RTC
#include <RTClib.h>         // Biblioteca do RTC


#define SS_PIN 10
#define RST_PIN 9
#define atuador 2
#define MICRO_SD_PIN A0
#define VERMELHO A5
#define VERDE A4

int intervalo = 5000; // Tempo que a trava ficara aberta em ms

// Instanciando modulos
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(4, 3, 5, 6, 7, 8);
RTC_DS3231 rtc;

String admin = "";
String UID = "";
bool adicionar = false;

void setup() {
  SPI.begin();         // Inicia comunicacao SPI
  mfrc522.PCD_Init();  // Inicia o modulo RFID
  lcd.begin(16, 2);    // Inicializa o display LCD
  rtc.begin();         // Inicializa modulo RTC
  SD.begin();          // Inicializa modulo microSD
  boot();              // Rotina de texto inicial
}

void boot() {
  lcd.clear();
  lcd.print("Aproxime o seu");
  lcd.setCursor(0, 1);
  lcd.print("cartao no leitor");

  //Inicializa conexoes SPI
  pinMode(SS_PIN, OUTPUT);
  pinMode(MICRO_SD_PIN, OUTPUT);

  // Garante que o pino do atuador seja iniciado sem energia
  digitalWrite(atuador, LOW);

  // Cria diretorios se necessario
  digitalWrite(MICRO_SD_PIN, LOW);
  digitalWrite(SS_PIN, HIGH);
  if (!SD.exists("Permitido")) {
    SD.mkdir("Permitido");
  }
  if (!SD.exists("Negado")) {
    SD.mkdir("Negado");
  }
  if (!SD.exists("Log")) {
    SD.mkdir("Log");
  }

  // Garante que os pinos de chip select sejam inicializados corretamente
  digitalWrite(SS_PIN, LOW);
  digitalWrite(MICRO_SD_PIN, HIGH);
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
  UID.toUpperCase();

  if (admin == "") {
    admin = UID;
    return;
  }

  if (UID == admin) {
    adicionar = true;
  } else if (adicionar) {
    SD.open("/Permitido/" + UID, FILE_WRITE);
  }
}

void resposta () {
  digitalWrite(SS_PIN, HIGH);
  digitalWrite(MICRO_SD_PIN, LOW);

  //UID esperada do cartao liberado
  if (SD.exists("Permitido/" + UID)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem vindo");
    lcd.setCursor(0, 1);
    lcd.print("Acesso liberado!");
    digitalWrite(VERDE, HIGH);
    abrir();
    digitalWrite(VERDE, LOW);

    //Adiciona ao log do dia
    escreve_log(true);
    return;
  }

  //UID esperada do cartao bloqueado
  else if (SD.exists("Negado/" + UID)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Usuario");
    lcd.setCursor(0, 1);
    lcd.print("Bloqueado");
    digitalWrite(VERMELHO, HIGH);
    delay(intervalo);
    digitalWrite(VERMELHO, LOW);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acesso negado");
    digitalWrite(VERMELHO, HIGH);
    delay(intervalo);
    digitalWrite(VERMELHO, LOW);
  }
  // Adicionar ao log
  escreve_log(false);
  digitalWrite(SS_PIN, LOW);
  digitalWrite(MICRO_SD_PIN, HIGH);
}

void adicionar_cartao() {
  digitalWrite(SS_PIN, HIGH);
  digitalWrite(MICRO_SD_PIN, LOW);

  File arquivo_UID;

  if (SD.exists("Permitido/" + UID)) {
    SD.remove("Permitido/" + UID);
    arquivo_UID = SD.open("/Permitido/" + UID, FILE_WRITE);
    arquivo_UID.close();
  }
  else if (SD.exists("Negado/" + UID)) {
    SD.remove("Negado/" + UID);
    arquivo_UID = SD.open("/Permitido/" + UID, FILE_WRITE);
    arquivo_UID.close();
  } else {
    arquivo_UID = SD.open("/Permitido/" + UID, FILE_WRITE);
    arquivo_UID.close();
  }

  digitalWrite(SS_PIN, LOW);
  digitalWrite(MICRO_SD_PIN, HIGH);
}


void escreve_log(bool aberto) {
  // Abre ou cria o arquivo de log do dia
  DateTime agora = rtc.now();
  File log = SD.open("/Log/" + agora.day() + agora.month(), FILE_WRITE);
  log.seek(log.size());
  
  log.write("HORA: ");
  log.write(agora.hour());
  log.write(":");
  log.write(agora.minute());
  log.write(":");
  log.write(agora.second());
  log.write("    UID:");
  log.print(UID);
  log.write("Aberto: ");
  if (aberto) {
    log.write("SIM");
  } else {
    log.write("NAO");
  }
  log.println();
}

void loop() {
  ler_cartao();
  resposta();
}
