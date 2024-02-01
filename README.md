# Tamagotchi 

## Introdução

A ideia é desenvolver um brinquedo interativo onde a criança se torne responsável por cuidar de um bichinho virtual para que ele tenha uma vida saudável. Por exemplo, de forma randômica, o bichinho virtual sentirá calor, frio, carência, entediado, sede e fome, solicitando à criança uma determinada ação de acordo com a necessidade do bichinho.

O brinquedo, porém, tem sensores próprios de temperatura ambiente e batimento cardíaco que permite o envio de informações para os pais, de forma que os pais podem atuar caso a criança esteja em um ambiente de risco, como por exemplo, caso a temperatura onde a criança esteja brincando esteja muito baixa, será enviado um email aos pais informando a temperatura lida e solicitando a verificação dos mesmos se a criança está agasalhada. Esta iteração com os pais não foi implementada a tempo, ficando para trabalhos futuros.

Funcionalidades para os pais:
+ reage à temperatura (sensor de temperatura na parte superior do tamagotchi - não implementado);
+ manda informações para os pais caso o ambiente esteja "insalubre" - não implementado;
+ medicao de batimento cardíaco (envia para os pais os batimentos cardíacos da criança - não implementado);
+ site para os pais acompanharem as informações do tamagotchi (registros com a data do arquivo, informações de temperatura e batimento cardíaco de acordo com um horário determinado).
 
Funcionalidades para a criança:
+ tela (rosto triste = tamagotchi está com fome, sede, frio ou calor. Rosto feliz = tamagotchi sem problemas);
+ Sentimentos do tamagotchi: Frio, Calor, Fome, sede, carência e tédio.
+ Tamagotchi morre.
O brinquedo funciona de forma offline e salva todos os eventos para envio para os pais quando houver rede.

## Lista de partes

+ 1 Sensor de batimento cardíaco;
+ 2 sensores de temperatura (um para a parte lúdica e outro para aviso aos pais);
+ 2 botões digitais (um de alimentação e um de água);
+ Placa MPU-9250 de Acelerômetro e Giroscópio 3 eixos;
+ Tela OLED SSD1306 (128px 64px);
+ 2 leds;
+ 1 caixa para o protótipo;
+ ESP32;
+ jumpers;
+ 2 resistores;
+ 2 protoboards.

## Programas usados

+ Arduino  IDE;
+ Plug-in para fazer upload dos arquivos (https://github.com/lorol/arduino-esp32fs-plugin);
+ GIMP;
+ Autocad.

## Montagem (com fotos)
+ Ezequiel irá desenvolver este capítulo

## Operação - Funcionamento do brinquedo

1. Lúdico (interação criança - tamagotchi):

Ao ligar o brinquedo, o brinquedo solicita a medição dos batimentos cardíacos da criança (não randômico, somente quando liga), o sensor de batimento cardíaco está localizado no nariz do tamagotchi. Após a medição dos batimentos cardíacos, o brinquedo tem de forma randômica algumas das sensações abaixo, exigindo interação da criança com o brinquedo: 
+ Ficar com frio: Aquecer o tamagotchi (criança aquece o sensor de temperatura até um determinado delta de temperatura);
+ Ficar com calor: Abanar ou assoprar o sensor de temperatura (criança tenta resfriar o sensor de temperatura por um determinado período de tempo. Se o sensor de temperatura estiver na temperatura ambiente, esta comparação será feita com o outro sensor de temperatura, se a diferença for menor do que 2ºC, será considerado que o tamgotchi já não está mais com calor)
+ Ficar com fome: Alimentar o tamagotchi (criança aperta um botão de alimentação)
+ Sentir sede: Dar água para o tamagotchi (criança aparta um botão de água)
+ Sentir carente: Criança se conecta ao tamagotchi através do sensor de batimento cardíaco (nariz do tamagotchi), os leds que representam os olhos do tamagotchi piscam de acordo com o batimento cardíaco da criança.
+ Sentir tédio: criança movimenta o acelerômetro para entreter o tamagotchi

2. (Não implementado) Monitoramento do ambiente para os pais (interação ambiente -> criança -> pais):
+ Temperatura alta/baixa, umidade alta/baixa, batimento cardíaco baixo/alto => aviso aos pais utiliando o wi-fi para verificar o ambiente da criança. Adicionalmente, para o brinquedo e mostra na tela do brinquedo um sinal para a criança procurar os pais em conjunto com um sinal sonoro.

## Histórico e método de desenvolvimento (Requisitos do projeto)

O projeto foi se desenvolvendo em etapas, conforme abaixo:
- Entender o funcionamento do ESP32;
- Instalar uma IDE para programação do ESP32;
- Implementar uma lógica para captar a temperatura do ambiente a cada segundo;
- Implementar o sensor de batimentos cardíacos e ler na tela do computador;
- Testar a implementação de um botão digital, a ser utilizado na disponibilização de comida e de água;
- Implementar o acelerômetro;
- Apresentar expressões na tela do OLED SSD1306;
- Testar o acendimento do led para utilização como os olhos do tamagotchi.
- Desenvolvimento do protótico;
- Integração dos sensores no protótipo;
- Desenvolvimento de interface web para acessar o log de utilização do tamagotchi pela criança. Esta interface utiliza a rede wi-fi.
