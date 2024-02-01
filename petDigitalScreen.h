//Bibliotecas
#include "SSD1306Wire.h" 
#include "string.h"
#include "expressoes.h"
#include <OneWire.h>
#include "tamagotchi.h"

const int tamanhoFonte = 10;
const int minAtributo = 1;
long elapsedTime;
long callTime;

#define D3 4  // no ttgo com display em cima do esp
#define D5 15

// Chama a função da Biblioteca Wire display que constroi o objeto display, passando o
// endereço de memória do buffer e dois pinos, eles ficam escritos na memória da tela
SSD1306Wire  display(0x3c, D3, D5);


void initScreen() {
  pinMode (16, OUTPUT); // no ttgo com display em cima do esp, o reset do display (active low) é conectado ao pino 16
  digitalWrite (16, HIGH); // reset tem que estar desativado para o display mostrar algo.

  //Inicializar a Tela
  display.init();
  display.flipScreenVertically();
}

void displayStatus(int time, struct Tamagotchi state){
  // Define se feliz ou triste a partir dos atributos fome ou sede
  display.clear();

  if(state.qntfome > minAtributo && state.qntsede > minAtributo && state.efeitoAdverso){
     display.drawXbm(32,0,96,64, feliz_bits);
  }else{
    display.drawXbm(32,0,96,64, triste_bits);
  }

  // Texto
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  String statusFome = "F: ";
  String statusSede = "S: ";
  String statusTemp = "T: ";

  statusFome += state.qntfome;
  statusSede += state.qntsede;
  statusTemp += static_cast<int>(getTempExternal());

  display.drawStringMaxWidth(5, 5, 32, statusFome);
  display.drawStringMaxWidth(5, (5 + tamanhoFonte + 1), 32, statusSede);
  display.drawStringMaxWidth(5, (5 + (2 * tamanhoFonte) + 2), 32, statusTemp);

  display.display();
  delay(time);

  display.clear();
  display.display();
}
