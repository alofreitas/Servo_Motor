// Importação de bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição do pino do PWM
#define PWM_LED 12
#define WRAP_PERIOD 20000 // valor máx do contador wrap - 20 ms
#define DUTY_CYCLE_MAX 2400 
#define DUTY_CYCLE_MIN 500

const float PWM_DIVISOR = 125.0;

// Função para configurar o PWM
/*
Função para configurar o PWM
1 -> Seta o PWM a GPIO 22
2 -> Pega o número do slice do PWM
3 -> Seta o valor de wrap do PWM
4 -> Seta o divisor de clock do PWM
5 -> Habilita o PWM
*/
void configurar_pwm()
{
    gpio_set_function(PWM_LED, GPIO_FUNC_PWM); // habilitar o pino GPIO como PWM
    uint slice_num = pwm_gpio_to_slice_num(PWM_LED);
    pwm_set_wrap(slice_num, WRAP_PERIOD);
    pwm_set_clkdiv(slice_num, PWM_DIVISOR);
    pwm_set_enabled(slice_num, true);
}

// Função para definir o duty cycle do PWM
void setar_duty_cycle(uint slice_num, uint16_t duty_cycle)
{
    pwm_set_gpio_level(PWM_LED, duty_cycle);
}

// Função para mover o servo motor
void mover_servo_motor(uint16_t angulo)
{
    uint slice_num = pwm_gpio_to_slice_num(PWM_LED);

    // Mapeia o ângulo para o ciclo de trabalho do PWM
    uint16_t duty_cycle = (angulo * (DUTY_CYCLE_MAX - DUTY_CYCLE_MIN) / 180) + 500;

    setar_duty_cycle(slice_num, duty_cycle);
    sleep_ms(5000); // Aguarda 5 segundos
}

int main()
{

    // Inicializa a comunicação serial e configura o pwm
    stdio_init_all();
    configurar_pwm();

    // Move o servo motor para os angulos determinados no parâmetro da função
    mover_servo_motor(180);
    mover_servo_motor(90);
    mover_servo_motor(0);

    uint duty_cycle = 500;
    uint up_down = 1; // variável para controlar o movimento

    // Movimento suave do servo motor
    while (true) {
        if (up_down) {
            duty_cycle += 5;
            if (duty_cycle >= DUTY_CYCLE_MAX) {
                up_down = 0;
            }
        } else {
            duty_cycle -= 5;
            if (duty_cycle <= DUTY_CYCLE_MIN){
                up_down = 1;
            }
        }
        setar_duty_cycle(pwm_gpio_to_slice_num(PWM_LED), duty_cycle / 10);
        sleep_ms(10);
    }
    return 0;
}
