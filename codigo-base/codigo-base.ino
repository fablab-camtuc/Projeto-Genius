#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define BUZZER 11

int som = 0;          // som a ser tocado
int temp = 0;         // Variável temporária
int digito = 0;       // Digito atual
String resp = "";     // Sequencia da resposta
int tseq = 0;         // Tamanho da seq do jogador
int acertos = 0;      // Numero de acertos
bool gerada = false; // Ve se a senha foi gerada
int leds[4] = {LED1, LED2, LED3, LED4};
int tons[4] = {200, 225, 250, 275};

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Gera uma seed aleatória
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  digito = 0;
  acertos = 0;
  // Gerar a chave:
  if (gerada == false){
    temp = random(4);
    Serial.println("fase = " + String(resp.length()));
    resp += String(leds[temp]);
    Serial.println("Resposta = " + resp);
    gerada = true;

    // Mostrar a chave ao usuário
    for (int i = 0; i < resp.length() ; i++){
      temp = int(resp[i]) - 48; // valor da resposta
      for (int j = 0; j < 4; j++){
        if (leds[j] == temp){
          som = tons[j]; // Definindo o som a ser tocado
        }
      }
      digitalWrite(int(resp[i]) - 48, HIGH);
      tone(BUZZER, som); delay(500); noTone(BUZZER);
      delay(500);
      digitalWrite(int(resp[i]) - 48, LOW);
      delay(500);
    } // fim do for de fora
  } // fim do if

  // Lendo e avaliando a entrada do usuario
  while (digito < resp.length()){
    for(int i = 0; i < 4; i++){
      if (digitalRead(leds[i]) == HIGH){
        while(digitalRead(leds[i]) == HIGH){}
        temp = leds[i]; // valor do botao apertado
        for (int j = 0; j < 4; j++){
          if (leds[j] == temp){
            som = tons[j]; // Definindo o som a ser tocado
          }
        }
        tone(BUZZER, som); delay(500); noTone(BUZZER);
        Serial.println("Tocando o tom: " + String(som));
        if (String(resp[digito]) == String(leds[i])) {
          Serial.println("Digito " + String(digito)); digito += 1; acertos += 1; gerada = false;
        } else {
          Serial.println("Game Over");
          for (int z = 0; z < 2; z++){
            digitalWrite(leds[0] ,HIGH);
            digitalWrite(leds[1] ,HIGH);
            digitalWrite(leds[2] ,HIGH);
            digitalWrite(leds[3] ,HIGH);
            tone(BUZZER, 500);
            delay(500);
            digitalWrite(leds[0] ,LOW);
            digitalWrite(leds[1] ,LOW);
            digitalWrite(leds[2] ,LOW);
            digitalWrite(leds[3] ,LOW);
            noTone(BUZZER);
            delay(500);
          }
          delay(500);
          digito = 0; resp = ""; gerada = false; acertos = 0; break;
        } // fim do else

        Serial.println("Voce jogou: " + String(leds[i]));

      } // fim do if
    } // fim do for
  } // fim do while()

  Serial.println("Acertos = " + String(acertos));
  Serial.println("Tamanho senha = " + String(resp.length()));
  delay(1000);

} // fim do loop()
