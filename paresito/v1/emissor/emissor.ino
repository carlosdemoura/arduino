#include <LiquidCrystal.h>
#include <Keypad.h>


//DEFINIÇÕES, SETUP E LOOP
const int tipo = 1; //0:RECEPTOR    1: EMISSOR
const int led = 2;
const int led_tempo = 100;

LiquidCrystal lcd(A0, A1, 3, A3, A4, A5); // Pinos RS, E, D4, D5, D6, D7 do LCD

// Definição do teclado
const byte ROWS = 4;
const byte COLS = 4;
char mapa_teclado[ROWS][COLS] = {
  {'a','e','i','o'},
  {'s','r','n','u'},
  {'d','t','m','c'},
  {'<',' ','#','^'},
};
byte rowPins[ROWS] = {13,12,11,10}; // Pinos das linhas do teclado
byte colPins[COLS] = {9,8,7,6};
Keypad keypad = Keypad(makeKeymap(mapa_teclado), rowPins, colPins, ROWS, COLS);

String mensagem = "";
int cont = 0;


void setup(){
  Serial.begin(9600); //////////////
  
  pinMode(led, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.clear();

  efeito_inicial(tipo);
  print_mensagem("Digite sua mensagem:");
}


void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY){
    //SHIFT
    if (mensagem.substring(mensagem.length()-1, mensagem.length()) == "^"){
      key = shift(key);
      if (key != '<'){
        mensagem = mensagem.substring(0,mensagem.length()-1);
        cont--;
      }
    }
    
    // ENVIAR
    if (key == '#'){
      lcd.clear();
      lcd.setCursor(0,0);
      
      String aviso = "Sua mensagem:   " + mensagem;
      print_mensagem(aviso);
      lcd.clear();
      
      emitir(mensagem);
      mensagem = "";
      cont = 0;
    
    // BACKSPACE
    } else if (key == '<'){
      if(mensagem.length()>0){
        mensagem = mensagem.substring(0,mensagem.length()-1);
        cont--;
        lcd.clear();
      }
      if(mensagem.length()>0 && mensagem.length()<=16){
        lcd.setCursor(0,0);
        lcd.print(mensagem);
      } else if(mensagem.length()>16 && mensagem.length()<=32){
        print_mensagem(mensagem);
      } else if (mensagem.length()>32) { //MELHORAR
        int x = mensagem.length()/32;
        int y = mensagem.length() - x*32;
        print_mensagem(mensagem.substring(32*x-1, mensagem.length()-1));
        if (y<=16){
          lcd.setCursor(y, 0);
        } else {
          lcd.setCursor(y-16, 1);
        }
      }
    
    // IMPRIMIR
    } else {
      mensagem += key;
      cont++;
      if (cont==1){
        lcd.clear();
        lcd.setCursor(0,0);
      } else if (cont>1 && cont<=16){
        lcd.setCursor(cont-1,0);
      } else if (cont>16 && cont<=32){
        lcd.setCursor(cont-17,1);
      } else if (cont>32){
        lcd.setCursor(31,1);
        cont-=32;
        lcd.clear();
      }
      lcd.print(key);
    }
  }
}





void emitir(String mensagem){
  
  String codigo = "";
  for(int i=0; i<mensagem.length(); i++){
    codigo += codigo_bin(mensagem.substring(i,i+1));
  }
  
  codigo = "101010101010101" + codigo + "000000000000000";
  print_mensagem("Transmitindo sinal...");
  
  for(int i=0; i<codigo.length(); i++){
    if (codigo.substring(i,i+1) == "0"){
      digitalWrite(led, 0);
    } else {
      digitalWrite(led, 1);
    }
   	delay(led_tempo);
  }
  lcd.clear();
  print_mensagem("Mensagem enviadacom sucesso!");
  delay(1000);
  lcd.clear();
  print_mensagem("Digite sua mensagem:");
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
  int nlinhas = mensagem.length() / 16;
   
   int dif = nlinhas*16 - mensagem.length();
   if (dif != 0){
    mensagem += repetir(dif+16, ' ');
  }
  
  for (int i=0; i<nlinhas; i++){
    lcd.setCursor(0,0);
    lcd.print(mensagem.substring(16*i,16*(i+1)));
    lcd.setCursor(0,1);
    lcd.print(mensagem.substring(16*(i+1),16*(i+2)));
    delay(1500);
  }
}


void print_texto(String texto){
  int nlinhas = texto.length() / 16;
   
  int dif = nlinhas*16 - texto.length();
  if (dif != 0){
    texto += repetir(dif+16, ' ');
  }
 
  texto =  "-=- mensagem -=-" + texto + "---- sair < ----";
  int linha = 0;
  while (true){
    char key = keypad.getKey();
    if (key == '^'){
      linha = min(linha+1, nlinhas+1);
    } else if (key == 'o'){
      linha = max(linha-1, 0);
    } else if (key == '<'){
      lcd.clear();
      break;
    }
   
    lcd.setCursor(0,0);
    lcd.print(texto.substring(16*linha,16*(linha+1)));
    lcd.setCursor(0,1);
    lcd.print(texto.substring(16*(linha+1),16*(linha+2)));
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
String codigo_bin(String letra){
  if(letra == " ") return "00000";
  else if(letra == "a") return "00001";
  else if(letra == "b") return "00010";
  else if(letra == "c") return "00011";
  else if(letra == "d") return "00100";
  else if(letra == "e") return "00101";
  else if(letra == "f") return "00110";
  else if(letra == "g") return "00111";
  else if(letra == "h") return "01000";
  else if(letra == "i") return "01001";
  else if(letra == "j") return "01010";
  else if(letra == "k") return "01011";
  else if(letra == "l") return "01100";
  else if(letra == "m") return "01101";
  else if(letra == "n") return "01110";
  else if(letra == "o") return "01111";
  else if(letra == "p") return "10000";
  else if(letra == "q") return "10001";
  else if(letra == "r") return "10010";
  else if(letra == "s") return "10011";
  else if(letra == "t") return "10100";
  else if(letra == "u") return "10101";
  else if(letra == "v") return "10110";
  else if(letra == "w") return "10111";
  else if(letra == "x") return "11000";
  else if(letra == "y") return "11001";
  else if(letra == "z") return "11010";
  else if(letra == "1") return "11011";
  else if(letra == "2") return "11100";
  else if(letra == "3") return "11101";
  else if(letra == "4") return "11110";
  else if(letra == "5") return "11111";
  else return "";
}


char shift(char letra){
  if(letra == 'a') return 'l';
  else if(letra == 'e') return 'p';
  else if(letra == 'i') return 'v';
  else if(letra == 'o') return 'g';
  else if(letra == 's') return 'h';
  else if(letra == 'r') return 'q';
  else if(letra == 'n') return 'b';
  else if(letra == 'u') return 'f';
  else if(letra == 'd') return 'z';
  else if(letra == 't') return 'j';
  else if(letra == 'm') return 'x';
  else if(letra == 'c') return 'k';
  else if(letra == ' ') return 'y';
  else if(letra == '^') return '<';
  else if(letra == '#') return 'w';
  else if(letra == '<') return '<';
}
