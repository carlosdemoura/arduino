#include <LiquidCrystal.h>


//DEFINIÇÕES, SETUP E LOOP
const int tipo = 0; //0:RECEPTOR    1: EMISSOR
const int ldr = A2;
int ldr_valor;

LiquidCrystal lcd(A0, A1, 3, 4, A4, A5); // Pinos RS, E, D4, D5, D6, D7 do LCD

String codigo_global = "";
const int led_tempo = 100;


void setup(){
  Serial.begin(9600); //////////////
  
  pinMode(ldr, INPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.clear();

  efeito_inicial(tipo);
  print_mensagem("Aguardando nova mensagem...");
}


void loop(){
  ldr_valor = analogRead(ldr);
  if (ldr_valor < 600 && codigo_global.length()>0){ //REPENSAR CONDIÇÃO INICIAL
    codigo_global += 0;
  } else if(ldr_valor >= 600){
    codigo_global += 1;
  }
  
  if (codigo_global.substring(codigo_global.length()-15,codigo_global.length())=="101010101010101"){
    lcd.clear();
    lcd.print("Recebendo sinal ...");
    codigo_global = "";
    leitura_codigo();
  }
  delay(led_tempo);
}





// FUNÇÕES DE RECEPÇÃO
void leitura_codigo(){
  while (codigo_global.substring(codigo_global.length()-10,codigo_global.length())!="0000000000"){
    ldr_valor = analogRead(ldr);
    if (ldr_valor < 700){
      codigo_global += 0;
    } else {
      codigo_global += 1;
    }
    delay(led_tempo);
  }
  decodificar(codigo_global);
  Serial.print(codigo_global);
  Serial.print("\n");
}


void decodificar(String codigo){ //mudar nome da var
  Serial.print(codigo);
  Serial.print("\n");
  codigo = codigo.substring(1,codigo.length()-10);
  Serial.print("\n\n");
  Serial.print(codigo);
  
  String mensagem = ""; 
  for(int i=0; i<=codigo.length(); i+=5){
    mensagem += anti_codigo(codigo.substring(i, i+5));
  }
  Serial.print("\n");
  Serial.print(mensagem);
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("RECEBIDO!");
  delay(500);
  lcd.clear();
  
  print_mensagem(mensagem);
  delay(3000);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Envio");
  lcd.setCursor(3,1);
  lcd.print("finalizado!");
  delay(100);
  codigo_global = "";
  print_mensagem("Aguardando nova mensagem...");
}





// FUNÇÕES GERAIS
void efeito_inicial(int tipo_local){
  lcd.setCursor(4,0);
  lcd.print("PARESITO");
  delay(200);
  lcd.setCursor(1,1);
  lcd.print("CCBY Carlos dM.");
  delay(500);  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("PARESITO");
  
  for (int i=0; i<16; i++){
    lcd.setCursor(i,1);
    lcd.print("=");
    delay(50);
  }
  
  lcd.clear();
  delay(50);
  lcd.setCursor(4,0);
  lcd.print("PARESITO");
  delay(50);
  lcd.setCursor(0,1);
  if (tipo_local == 0){
    lcd.print("=== RECEPTOR ===");
  } else {
    lcd.print("==== EMISSOR ===");
  }
  delay(500);
}


void print_mensagem(String mensagem){
  lcd.clear();

  mensagem = "  Nova mensagem " + mensagem;

  int nlinhas = mensagem.length() / 16;
  if (nlinhas==0){
    nlinhas++;
  }
  int dif = nlinhas*16 - mensagem.length();
  if (dif != 0){
    mensagem += repetir(dif+16, ' ');
  }

  Serial.print("\nprint: ");
  Serial.print(mensagem);

  for (int i=0; i<nlinhas; i++){
    lcd.setCursor(0,0);
    lcd.print(mensagem.substring(16*i,16*(i+1)));
    lcd.setCursor(0,1);
    lcd.print(mensagem.substring(16*(i+1),16*(i+2)));
    delay(1500);
  }
}

String repetir(int n, char a){
  String resp = "";
  for (int i=0; i<n; i++){
    resp += a;
  }
  return resp;
}





// DICIONÁRIOS COMO FUNÇÕES
String anti_codigo(String trecho){
  if(trecho == "00000") return " ";
  else if(trecho == "00001") return "a";
  else if(trecho == "00010") return "b";
  else if(trecho == "00011") return "c";
  else if(trecho == "00100") return "d";
  else if(trecho == "00101") return "e";
  else if(trecho == "00110") return "f";
  else if(trecho == "00111") return "g";
  else if(trecho == "01000") return "h";
  else if(trecho == "01001") return "i";
  else if(trecho == "01010") return "j";
  else if(trecho == "01011") return "k";
  else if(trecho == "01100") return "l";
  else if(trecho == "01101") return "m";
  else if(trecho == "01110") return "n";
  else if(trecho == "01111") return "o";
  else if(trecho == "10000") return "p";
  else if(trecho == "10001") return "q";
  else if(trecho == "10010") return "r";
  else if(trecho == "10011") return "s";
  else if(trecho == "10100") return "t";
  else if(trecho == "10101") return "u";
  else if(trecho == "10110") return "v";
  else if(trecho == "10111") return "w";
  else if(trecho == "11000") return "x";
  else if(trecho == "11001") return "y";
  else if(trecho == "11010") return "z";
  else if(trecho == "11011") return "1";
  else if(trecho == "11100") return "2";
  else if(trecho == "11101") return "3";
  else if(trecho == "11110") return "4";
  else if(trecho == "11111") return "E";
  else return "\0";
}
