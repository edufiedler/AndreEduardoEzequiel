//Bibliotecas
#include "SSD1306Wire.h" 
#include "string.h"
#include "expressoes.h"
#include "petDigitalMotionTracker.h"
#include "petDigitalTempSensors.h"
#include "tamagotchi.h"
#include "petDigitalScreen.h"

//Definições e Constantes
const int tamanhoFonte = 10;
const int minAtributo = 1;
int EcraLigado=0;
int threshold=20;
struct Tamagotchi state;


void botaoFome(){
  if(qntfome != 5){
    qntfome = 5;
    EcraLigado=0;
    buttonPress();
  }
}

void botaoSede() {
  if(qntsede != 5){
    qntsede = 5;
    EcraLigado=0;
    buttonPress();
  }
}

void initState() {
  //Tamagotchi state initialization
  state.qntfome = 5;
  state.qntsede = 5;
  state.efeitoAdverso = true;

  //Fixando interrupts e funcoes aos botoes
  touchAttachInterrupt (T8, botaoSede, threshold);
  touchAttachInterrupt(T9,botaoFome,threshold);

  //Tela
  InitScreen();

  //Realocar
  randomSeed(analogRead(0));
}

//Estados do tamagotchi
void frio (){
  /* Estado de Frio: Le a getTempExternal na chamada da função, muda tela para expressao triste e
  continuamente checa a temperatura ate que o alvo de temperatura seja atingido, retorna o tamagotchi ao
  estado normal e encerra execucao */
     
  float tempAtual = getTempExternal();
  float tempAlvo = tempAlvo + 2;

  while(tempAtual < tempAlvo){
    status(2000, state);
    tempAtual = getTempExternal();
  }
}

void calor (){
  /* Estado de Calor: Le a temperatura na chamada da função, muda tela para expressao triste e
  continuamente checa a temperatura ate que o alvo de temperatura seja atingido, retorna o tamagotchi ao
  estado normal e encerra execucao */
     
  float tempAtual = getTempExternal();
  float tempAlvo = tempAlvo - 2;

  while(tempAlvo < tempAtual){
    status(2000, state);
    tempAtual = getTempExternal();
  }
  status(2000, state);
}

 
void tedio() {
  /* Estado de Tedio: PLACEHOLDER - Mudar tela para expressao triste, ler saída do acelerometro e
  retornar o tamagotchi ao estado normal após alguns segundos de movimento intenso. */
  
  int delta = 5;
  int contadorDelta = 0;
  xyzFloat valoresG = myMPU9250.getGValues();
  float atualG = myMPU9250.getResultantG(valoresG);
  float anteriorG = atualG;
  state.efeitoAdverso = false;

  while(!state.efeitoAdverso){
    
    if(contadorDelta < 10){
      if(atualG - anteriorG > delta){
        contadorDelta++;
      }
      status(1000, state);
    }else{
      efeitoAdverso = true;
      status(1000, state);
    }

    anteriorG = atualG;
    valoresG = myMPU9250.getGValues();
    atualG = myMPU9250.getResultantG(valoresG);
  }
  
}


void fome() {
  /* Estado de fome: Mudar tela para expressao triste, aguardar ate que o botao de comida seja apertado e 
  retornar o tamagotchi ao estado normal. */
}

void sede(){
  /* Estado de Sede:  Mudar tela para expressao triste, aguardar ate que o botao de agua seja apertado e 
  retornar o tamagotchi ao estado normal. */
}

void carente(){
  /* Estado de Carente: PLACEHOLDER - Mudar tela para expressao de carente, checar sensor de batimento cardiaco para
  medicao da crianca  e retorna o tamagotchi ao estado normal, com exito ou nao.
  Em caso de exito, grava o resultado no log 
  Em caso de falha, descarta o resultado*/

}

void randomState(){
  switch(random(1,7)){
      case 1:
        if(qntfome > 1){
        qntfome -= 1;
        }
        break;
      case 2:
        if(qntsede > 1){
        qntsede -= 1;
        }
        break;
      case 3:
        frio();
        break;
      case 4:
        calor();
        break;
      case 5:
        tedio();
        break;
      case 6:
        carente();
        break;
      default:
        break;
    }
}

//Função principal
void ButtonPress() {

  if (EcraLigado==0) {
    display.clear();
    display.display();
    status(2000, state);
  }
  if (EcraLigado==10) {
    // apaga o display
    //touch_value_s touchRead(T8);
    //touch_value_f touchRead(T9);
    display.clear();
    display.display();
  }

  EcraLigado++;

  delay (250);
}
