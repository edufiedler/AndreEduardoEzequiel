// Bibliotecas
#include "SSD1306Wire.h"
#include "string.h"
#include "petDigitalMotionTracker.h"
#include "petDigitalTempSensors.h"
#include "petDigitalScreen.h"
#include "petDigitalPulseSensor.h"

// Definições e Constantes
int EcraLigado = 0;
int threshold = 20;
struct Tamagotchi state;

void buttonPress()
{

  if (EcraLigado == 0)
  {
    display.clear();
    display.display();
    displayStatus(2000, state);
  }
  if (EcraLigado == 10)
  {
    // apaga o display
    // touch_value_s touchRead(T8);
    // touch_value_f touchRead(T9);
    display.clear();
    display.display();
  }

  EcraLigado++;

  delay(250);
}

void botaoFome()
{
  if (state.qntfome != 5)
  {
    state.qntfome = 5;
    EcraLigado = 0;
    buttonPress();
  }
}

void botaoSede()
{
  if (state.qntsede != 5)
  {
    state.qntsede = 5;
    EcraLigado = 0;
    buttonPress();
  }
}

void initState()
{
  // Tamagotchi state initialization
  state.qntfome = 5;
  state.qntsede = 5;
  state.efeitoAdverso = false;

  // Fixando interrupts e funcoes aos botoes
  attachInterrupt(digitalPinToInterrupt(34), botaoSede, RISING);
  attachInterrupt(digitalPinToInterrupt(39), botaoFome, RISING);

  initMPU9250();
  initTempSensors();
  initPulseSensor();

  // Tela
  initScreen();
  displayStatus(3000, state);

  // Realocar
  randomSeed(analogRead(0));
}

// Estados do tamagotchi
void frio()
{
  /* Estado de Frio: Le a getTempExternal na chamada da função, muda tela para expressao triste e
  continuamente checa a temperatura ate que o alvo de temperatura seja atingido, retorna o tamagotchi ao
  estado normal e encerra execucao */
  displayText("FRIO");
  float tempAtual = getTempExternal();
  float tempAlvo = tempAlvo + 5;
  state.efeitoAdverso = 'F';

  while (tempAtual < tempAlvo)
  {
    displayStatus(2000, state);
    tempAtual = getTempExternal();
  }
  state.efeitoAdverso = false;
}

void calor()
{
  /* Estado de Calor: Le a temperatura na chamada da função, muda tela para expressao triste e
  continuamente checa a temperatura ate que o alvo de temperatura seja atingido, retorna o tamagotchi ao
  estado normal e encerra execucao */
  displayText("CALOR");
  float tempAtual = getTempExternal();
  float tempAlvo = tempAlvo - 1;
  state.efeitoAdverso = 'C';

  while (tempAtual > tempAlvo)
  {
    displayStatus(2000, state);
    tempAtual = getTempExternal();
  }
  displayStatus(2000, state);
  state.efeitoAdverso = false;
}

void tedio()
{
  /* Estado de Tedio: PLACEHOLDER - Mudar tela para expressao triste, ler saída do acelerometro e
  retornar o tamagotchi ao estado normal após alguns segundos de movimento intenso. */
  displayText("ENTEDIADO");
  int delta = 2;
  int contadorDelta = 0;
  xyzFloat valoresG = myMPU9250.getGValues();
  float atualG = myMPU9250.getResultantG(valoresG);
  float anteriorG = atualG;
  state.efeitoAdverso = 'E';

  while (state.efeitoAdverso)
  {

    if (contadorDelta < 10)
    {
      if (atualG - anteriorG > delta)
      {
        contadorDelta++;
      }
      displayStatus(1000, state);
    }
    else
    {
      state.efeitoAdverso = false;
      displayStatus(1000, state);
    }

    anteriorG = atualG;
    valoresG = myMPU9250.getGValues();
    atualG = myMPU9250.getResultantG(valoresG);
  }
}

void fome()
{
  /* Estado de fome: Mudar tela para expressao triste, aguardar ate que o botao de comida seja apertado e
  retornar o tamagotchi ao estado normal. */
}

void sede()
{
  /* Estado de Sede:  Mudar tela para expressao triste, aguardar ate que o botao de agua seja apertado e
  retornar o tamagotchi ao estado normal. */
}

void carente()
{
  /* Estado de Carente: PLACEHOLDER - Mudar tela para expressao de carente, checar sensor de batimento cardiaco para
  medicao da crianca  e retorna o tamagotchi ao estado normal, com exito ou nao. */
  displayText("CARENTE");
  state.efeitoAdverso = 'S';
  displayStatus(1000, state);

  int bpm = getBPMPulseSensor();

  state.efeitoAdverso = false;
  displayStatus(1000, state);
}

void randomState()
{
  if (!state.efeitoAdverso)
  {
    return;
  }
  switch (random(1, 7))
  {
  case 1:
    if (state.qntfome > 1)
    {
      state.qntfome -= 1;
    }
    break;
  case 2:
    if (state.qntsede > 1)
    {
      state.qntsede -= 1;
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
