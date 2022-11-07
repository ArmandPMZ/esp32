/* Con este codigo se realizan dos tareas las cuales experimentando con su prioridad se observo
en la condición de tener la misma prioridad las tareas un comportamiento mas estable entre estas dos tarea
y en la condición de tener una tarea con mayor prioridad e invertir esta prioridad se observo
que como era obvio la tarea con mayor prioridad es la tarea dominante por lo tanto se logra ver mas*/
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

 


static const int rate_1 = 500;  // ms
static const int rate_2 = 323;  // ms

 


static const int led_pin = 4;

 


void toggleLED_1(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}

 


void toggleLED_2(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
  }
}

 

void setup() {

 

  
  pinMode(led_pin, OUTPUT);

 

  
  xTaskCreatePinnedToCore(  
              toggleLED_1,  
              "Toggle 1",   
              1024,         
              NULL,         
              1,            
              NULL,         
              app_cpu);     

 

 
  xTaskCreatePinnedToCore(  
              toggleLED_2,  
              "Toggle 2",   
              1024,         
              NULL,         
              1,            
              NULL,         
              app_cpu);     

 

}

 

void loop() {

 

}
