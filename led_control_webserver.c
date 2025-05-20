/**
 * AULA IoT - Embarcatech - Ricardo Prates - 004 - Webserver Raspberry Pi Pico w - wlan
 *
 * Material de suporte
 * 
 * https://www.raspberrypi.com/documentation/pico-sdk/networking.html#group_pico_cyw43_arch_1ga33cca1c95fc0d7512e7fef4a59fd7475 
 */

#include <stdio.h>               // Biblioteca padrão para entrada e saída
#include <string.h>              // Biblioteca manipular strings
#include <stdlib.h>              // funções para realizar várias operações, incluindo alocação de memória dinâmica (malloc)

#include "pico/stdlib.h"         // Biblioteca da Raspberry Pi Pico para funções padrão (GPIO, temporização, etc.)
#include "hardware/adc.h"        // Biblioteca da Raspberry Pi Pico para manipulação do conversor ADC
#include "pico/cyw43_arch.h"     // Biblioteca para arquitetura Wi-Fi da Pico com CYW43  

#include "lwip/pbuf.h"           // Lightweight IP stack - manipulação de buffers de pacotes de rede
#include "lwip/tcp.h"            // Lightweight IP stack - fornece funções e estruturas para trabalhar com o protocolo TCP
#include "lwip/netif.h"          // Lightweight IP stack - fornece funções e estruturas para trabalhar com interfaces de rede (netif)

#include "hardware/pwm.h"       //Para usar periféricos como o Buzzer
#include "hardware/clocks.h"

#include "hardware/pio.h"       // Para a matriz de leds

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

//Display oled
#include "hardware/i2c.h"
 #include "lib/ssd1306.h"
 #include "lib/font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
ssd1306_t ssd;     


// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PINX 7

// Credenciais WIFI - Tome cuidado se publicar no github!
#define WIFI_SSID "XXXXXXXX"
#define WIFI_PASSWORD "Senha do usuario"

// Definição dos pinos dos LEDs
#define LED_PIN CYW43_WL_GPIO_LED_PIN   // GPIO do CI CYW43
#define LED_BLUE_PIN 12                 // GPIO12 - LED azul
#define LED_GREEN_PIN 11                // GPIO11 - LED verde
#define LED_RED_PIN 13                  // GPIO13 - LED vermelho

// Configuração do pino do buzzer
#define BUZZER_PIN 21

// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin) {

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite() {
  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}


void anima_one(){

    npSetLED(12, 255, 0, 0); // Define o LED de índice 12 para vermelho.
    npWrite();
    sleep_ms(250);
    npSetLED(18, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(22, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(16, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(14, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(6, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(2, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(8, 255, 0, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(10, 255, 0, 0);
    npWrite();
    sleep_ms(1000);
    npClear();
    npWrite();


}

// Novo

void anima_two(){

    npSetLED(24, 0, 255, 0); // Define o LED de índice 12 para vermelho.
    npWrite();
    sleep_ms(250);
    npSetLED(15, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(16, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(13, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(12, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(7, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(8, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(1, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(0, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(9, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(10, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(19, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(20, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(2, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(3, 0, 255, 0);
    npWrite();
    sleep_ms(250);
    npSetLED(4, 0, 255, 0);
    npWrite();
    //sleep_ms(250);




    sleep_ms(1000);
    npClear();
    npWrite();


}




// Notas musicais para a música tema de Star Wars
const uint star_wars_notes[] = {
    330, 330, 330, 262, 392, 523, 330, 262,
    392, 523, 330, 659, 659, 659, 698, 523,
    415, 349, 330, 262, 392, 523, 330, 262,
    392, 523, 330, 659, 659, 659, 698, 523,
    415, 349, 330, 523, 494, 440, 392, 330,
    659, 784, 659, 523, 494, 440, 392, 330,
    659, 659, 330, 784, 880, 698, 784, 659,
    523, 494, 440, 392, 659, 784, 659, 523,
    494, 440, 392, 330, 659, 523, 659, 262,
    330, 294, 247, 262, 220, 262, 330, 262,
    330, 294, 247, 262, 330, 392, 523, 440,
    349, 330, 659, 784, 659, 523, 494, 440,
    392, 659, 784, 659, 523, 494, 440, 392
};

// Duração das notas em milissegundos
const uint note_duration[] = {
    500, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 500, 500, 500, 350, 150,
    300, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 650, 500, 150, 300, 500, 350,
    150, 300, 500, 150, 300, 500, 350, 150,
    300, 650, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 500, 500, 500, 350, 150,
    300, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 350, 150, 300, 500, 500,
    350, 150, 300, 500, 500, 350, 150, 300,
};

// Inicializa o PWM no pino do buzzer
void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Ajusta divisor de clock
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0); // Desliga o PWM inicialmente
}

// Toca uma nota com a frequência e duração especificadas
void play_tone(uint pin, uint frequency, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t top = clock_freq / frequency - 1;

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(pin, top / 2); // 50% de duty cycle

    sleep_ms(duration_ms);

    pwm_set_gpio_level(pin, 0); // Desliga o som após a duração
    sleep_ms(50); // Pausa entre notas
}

// Função principal para tocar a música
void play_star_wars(uint pin) {
    for (int i = 0; i < sizeof(star_wars_notes) / sizeof(star_wars_notes[0]); i++) {
        if (star_wars_notes[i] == 0) {
            sleep_ms(note_duration[i]);
        } else {
            play_tone(pin, star_wars_notes[i], note_duration[i]);
        }
    }
}


//NOVO
// Notas musicais para a parte introdutória de Für Elise
const uint fur_elise_notes[] = {
    659, 622, 659, 622, 659, 494, 587, 523,
    440, 0, 330, 440, 523, 0, 330, 523,
    587, 0, 330, 587, 659, 622, 659, 622,
    659, 494, 587, 523, 440, 0, 330, 440,
    523, 0, 330, 523, 587, 523, 440, 0
};

// Duração das notas em milissegundos
const uint fur_elise_duration[] = {
    200, 200, 200, 200, 200, 200, 200, 200,
    400, 200, 200, 200, 400, 200, 200, 200,
    400, 200, 200, 200, 200, 200, 200, 200,
    200, 200, 200, 200, 400, 200, 200, 200,
    400, 200, 200, 200, 400, 200, 400, 200
};

// Função para tocar Für Elise
void play_fur_elise(uint pin) {
    for (int i = 0; i < sizeof(fur_elise_notes) / sizeof(fur_elise_notes[0]); i++) {
        if (fur_elise_notes[i] == 0) {
            sleep_ms(fur_elise_duration[i]); // Pausa para notas com frequência 0
        } else {
            play_tone(pin, fur_elise_notes[i], fur_elise_duration[i]);
        }
    }
}

// Inicializar os Pinos GPIO para acionamento dos LEDs da BitDogLab
void gpio_led_bitdog(void);

// Função de callback ao aceitar conexões TCP
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err);

// Função de callback para processar requisições HTTP
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

// Leitura da temperatura interna
float temp_read(void);

// Tratamento do request do usuário
void user_request(char **request);



// Função principal
int main()
{
    //Inicializa todos os tipos de bibliotecas stdio padrão presentes que estão ligados ao binário.
    stdio_init_all();

    pwm_init_buzzer(BUZZER_PIN);

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PINX);
    npClear();

    // I2C Initialisation. Using it at 400Khz.
   i2c_init(I2C_PORT, 400 * 1000);
 
   gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
   gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
   gpio_pull_up(I2C_SDA);                                        // Pull up the data line
   gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
   
                                                 // Inicializa a estrutura do display
        ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
        ssd1306_config(&ssd);                                         // Configura o display
        ssd1306_send_data(&ssd);                                      // Envia os dados para o display

 


    printf("tudo pronto\n");

    // Inicializar os Pinos GPIO para acionamento dos LEDs da BitDogLab
    gpio_led_bitdog();

    
    

    //Inicializa a arquitetura do cyw43
    while (cyw43_arch_init())
    {
        printf("Falha ao inicializar Wi-Fi\n");
        sleep_ms(100);
        return -1;
    }

    // GPIO do CI CYW43 em nível baixo
    cyw43_arch_gpio_put(LED_PIN, 0);

    // Ativa o Wi-Fi no modo Station, de modo a que possam ser feitas ligações a outros pontos de acesso Wi-Fi.
    cyw43_arch_enable_sta_mode();

    // Conectar à rede WiFI - fazer um loop até que esteja conectado
    printf("Conectando ao Wi-Fi...\n");
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 20000))
    {
        printf("Falha ao conectar ao Wi-Fi\n");
        sleep_ms(100);
        return -1;
    }
    printf("Conectado ao Wi-Fi\n");

    // Caso seja a interface de rede padrão - imprimir o IP do dispositivo.
    if (netif_default)
    {
        printf("IP do dispositivo: %s\n", ipaddr_ntoa(&netif_default->ip_addr));
    }

    // Configura o servidor TCP - cria novos PCBs TCP. É o primeiro passo para estabelecer uma conexão TCP.
    struct tcp_pcb *server = tcp_new();
    if (!server)
    {
        printf("Falha ao criar servidor TCP\n");
        return -1;
    }

    //vincula um PCB (Protocol Control Block) TCP a um endereço IP e porta específicos.
    if (tcp_bind(server, IP_ADDR_ANY, 80) != ERR_OK)
    {
        printf("Falha ao associar servidor TCP à porta 80\n");
        return -1;
    }

    // Coloca um PCB (Protocol Control Block) TCP em modo de escuta, permitindo que ele aceite conexões de entrada.
    server = tcp_listen(server);

    // Define uma função de callback para aceitar conexões TCP de entrada. É um passo importante na configuração de servidores TCP.
    tcp_accept(server, tcp_server_accept);
    printf("Servidor ouvindo na porta 80\n");

    // Inicializa o conversor ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);

    while (true)
    {
        /* 
        * Efetuar o processamento exigido pelo cyw43_driver ou pela stack TCP/IP.
        * Este método deve ser chamado periodicamente a partir do ciclo principal 
        * quando se utiliza um estilo de sondagem pico_cyw43_arch 
        */
        cyw43_arch_poll(); // Necessário para manter o Wi-Fi ativo
        sleep_ms(100);      // Reduz o uso da CPU
    }

    //Desligar a arquitetura CYW43.
    cyw43_arch_deinit();
    return 0;
}

// -------------------------------------- Funções ---------------------------------

// Inicializar os Pinos GPIO para acionamento dos LEDs da BitDogLab
void gpio_led_bitdog(void){
    // Configuração dos LEDs como saída
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_put(LED_BLUE_PIN, false);
    
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_put(LED_GREEN_PIN, false);
    
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_put(LED_RED_PIN, false);
}

// Função de callback ao aceitar conexões TCP
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

// Tratamento do request do usuário - digite aqui
void user_request(char **request){

    if (strstr(*request, "GET /music_01") != NULL)
    {
        play_star_wars(BUZZER_PIN);
    }
    else if (strstr(*request, "GET /display_01") != NULL)
    {
         
        sleep_ms(200);
    // Limpa o display. O display inicia com todos os pixels apagados.
        ssd1306_fill(&ssd, false);
        ssd1306_send_data(&ssd);

        ssd1306_draw_string(&ssd, "O que o 0", 16, 10);
        ssd1306_draw_string(&ssd, "disse pro 8?", 8, 20);
        ssd1306_draw_string(&ssd, "Belo cinto!", 32, 40);

        ssd1306_send_data(&ssd);


        sleep_ms(4000);
    // Limpa o display. O display inicia com todos os pixels apagados.
        ssd1306_fill(&ssd, false);
        ssd1306_send_data(&ssd);

    }
    else if (strstr(*request, "GET /music_02") != NULL)
    {
        play_fur_elise(BUZZER_PIN);
    }
    else if (strstr(*request, "GET /display_02") != NULL)
    {//NOVO
       sleep_ms(200);
    // Limpa o display. O display inicia com todos os pixels apagados.
        ssd1306_fill(&ssd, false);
        ssd1306_send_data(&ssd);

        ssd1306_draw_string(&ssd, "O que e um", 24, 20);
        ssd1306_draw_string(&ssd, "pontinho preto?", 8, 30);
        ssd1306_draw_string(&ssd, "Um byte!", 40, 50);

        ssd1306_send_data(&ssd);


        sleep_ms(4000);
    // Limpa o display. O display inicia com todos os pixels apagados.
        ssd1306_fill(&ssd, false);
        ssd1306_send_data(&ssd);
    }
    else if (strstr(*request, "GET /animation_01") != NULL)
    {
        anima_one();
    }
    else if (strstr(*request, "GET /animation_02") != NULL)
    {
       anima_two();
    }
    else if (strstr(*request, "GET /on") != NULL)
    {
        cyw43_arch_gpio_put(LED_PIN, 1);
    }
    else if (strstr(*request, "GET /off") != NULL)
    {
        cyw43_arch_gpio_put(LED_PIN, 0);
    }
};

// Leitura da temperatura interna
float temp_read(void){
    adc_select_input(4);
    uint16_t raw_value = adc_read();
    const float conversion_factor = 3.3f / (1 << 12);
    float temperature = 27.0f - ((raw_value * conversion_factor) - 0.706f) / 0.001721f;
        return temperature;
}

// Função de callback para processar requisições HTTP
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (!p)
    {
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    // Alocação do request na memória dinámica
    char *request = (char *)malloc(p->len + 1);
    memcpy(request, p->payload, p->len);
    request[p->len] = '\0';

    printf("Request: %s\n", request);

    // Tratamento de request - Controle dos LEDs
    user_request(&request);
    
    // Leitura da temperatura interna
    float temperature = temp_read();

    // Cria a resposta HTML
    char html[1024];

    // Instruções html do webserver
    snprintf(html, sizeof(html), // Formatar uma string e armazená-la em um buffer de caracteres
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "\r\n"
             "<!DOCTYPE html>\n"
             "<html>\n"
             "<head>\n"
             "<title> Embarcatech - Smart house simulator </title>\n"
             "<style>\n"
             "body { background-color:rgb(251, 181, 181); font-family: Times New Roman, serif; text-align: center; margin-top: 50px;  }\n"
             "h1 { font-size: 64px; margin-bottom: 30px; }\n"
             "button { background-color: LightGray; font-size: 36px; margin: 10px; padding: 20px 40px; border-radius: 10px; }\n"
             ".temperature { font-size: 48px; margin-top: 30px; color: #333; }\n"
             "</style>\n"
             "</head>\n"
             "<body>\n"
             "<h1>Embarcatech:Smart House Simulator</h1>\n"
             "<form action=\"./music_01\"><button>Tocar Musica 1</button></form>\n"
             "<form action=\"./display_01\"><button>Piada 1</button></form>\n"
             "<form action=\"./music_02\"><button>Musica 2</button></form>\n"
             "<form action=\"./display_02\"><button>Piada 2</button></form>\n"
             "<form action=\"./animation_01\"><button>Animation 1</button></form>\n"
             "<form action=\"./animation_02\"><button>Animation 2</button></form>\n"
             "<p class=\"temperature\">Temperatura Interna: %.2f &deg;C</p>\n"
             "</body>\n"
             "</html>\n",
             temperature);

    // Escreve dados para envio (mas não os envia imediatamente).
    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);

    // Envia a mensagem
    tcp_output(tpcb);

    //libera memória alocada dinamicamente
    free(request);
    
    //libera um buffer de pacote (pbuf) que foi alocado anteriormente
    pbuf_free(p);

    return ERR_OK;
}

