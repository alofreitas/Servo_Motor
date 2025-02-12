# Projeto envolvendo Servo Motor - EMBARCATECH

## Link do vídeo
https://drive.google.com/file/d/1nzT8B2mhCvPE-bNcQtR89rZ6QL4X0PfM/view?usp=sharing

## Descrição
Este programa permite controlar um servo motor usando a placa Raspberry Pi Pico. Ele utiliza o protocolo PWM (Pulse Width Modulation) para ajustar o ângulo do servo motor. O programa move o servo para três posições fixas (0°, 90° e 180°) e, em seguida, entra em um loop onde faz movimentos suaves entre as extremidades.

## Requisitos
- Raspberry Pi Pico
- Servo motor compatível com PWM
- Ambiente de desenvolvimento com suporte ao SDK do Raspberry Pi Pico
- Biblioteca `pico-sdk` instalada
- Conexão do servo ao GPIO 22 do Raspberry Pi Pico

## Conexão do Servo Motor
- **GND** -> GND da Raspberry Pi Pico
- **Sinal (PWM)** -> GPIO 22

## Compilando e Executando
1. Configure o ambiente de desenvolvimento do Raspberry Pi Pico conforme a documentação oficial.
2. Clone o repositório e acesse a pasta do projeto:
   ```sh
   git clone https://github.com/alofreitas/Servo_Motor.git
   cd Servo_Motor.c
   ```
3. Compile o programa:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Transfira o arquivo `.uf2` para a Raspberry Pi Pico:
   - Conecte a Raspberry Pi Pico ao computador mantendo o botão `BOOTSEL` pressionado.
   - Copie o arquivo gerado `main.uf2` para a unidade montada.
5. O programa será executado automaticamente após a transferência do arquivo.

## Funcionamento
- O programa inicia configurando o PWM no GPIO 22.
- Move o servo motor para os ângulos de 180°, 90° e 0° com um intervalo de 5 segundos entre cada movimento.
- Entra em um loop infinito onde o servo se movimenta suavemente entre os extremos de 0° a 180° e vice-versa.

## Ajustes e Personalização
- Para mudar o pino do PWM, altere a constante `GPIO_PWM` no código.
- Para modificar o tempo de espera entre os movimentos, ajuste os valores da função `sleep_ms()`.
- O incremento/decremento do duty cycle pode ser ajustado no loop para alterar a suavidade do movimento do servo.

