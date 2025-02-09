// Importação de bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição do pino do PWM e do WRAP para 20 ms (20000)
#define GPIO_PWM 22 
#define PWM_WRAP 20000 

// Função para configurar o PWM
/*
Função para configurar o PWM
1 -> Seta o PWM a GPIO 22
2 -> Pega o número do slice do PWM
3 -> Seta o valor de wrap do PWM
4 -> Seta o divisor de clock do PWM
5 -> Habilita o PWM
*/
void configurar_pwm() {
    gpio_set_function(GPIO_PWM, GPIO_FUNC_PWM); 
    uint slice_num = pwm_gpio_to_slice_num(GPIO_PWM); 
    pwm_set_wrap(slice_num, PWM_WRAP); 
    pwm_set_clkdiv(slice_num, 125.0f); 
    pwm_set_enabled(slice_num, true); 
}

// Função para setar o duty cycle do PWM
void setar_duty_cycle(uint slice_num, uint16_t duty_cycle) {
    pwm_set_gpio_level(GPIO_PWM, duty_cycle);
}

// Função para mover o servo motor
void mover_servo_motor(uint16_t angulo) {
    uint slice_num = pwm_gpio_to_slice_num(GPIO_PWM);
    
    // Mapeia o ângulo para o ciclo de trabalho do PWM
    uint16_t duty_cycle = (angulo * (2400 - 500) / 180) + 500;
    
    setar_duty_cycle(slice_num, duty_cycle);
    sleep_ms(5000); // Aguarda 5 segundos
}


int main() {

    // Inicializa a comunicação serial e configura o pwm
    stdio_init_all();
    configurar_pwm(); 

    // Move o servo motor para os angulos determinados no parâmetro da função
    mover_servo_motor(180);
    mover_servo_motor(90);
    mover_servo_motor(0);

    // Laço for para o servo motor fazer movimentos suaves
    while (true) {
        for (uint16_t duty_cycle = 500; duty_cycle <= 2400; duty_cycle += 5) {
            setar_duty_cycle(pwm_gpio_to_slice_num(GPIO_PWM), duty_cycle);
            sleep_ms(10);
        }
        for (uint16_t duty_cycle = 2400; duty_cycle >= 500; duty_cycle -= 5) {
            setar_duty_cycle(pwm_gpio_to_slice_num(GPIO_PWM), duty_cycle);
            sleep_ms(10);
        }
    }
        
    return 0;
}