#define RED_LED_PIN 4
#define GREEN_LED_PIN 2
#define BLUE_LED_PIN 3
#define USENSOR_SIGNAL_PIN 5
#define SERIAL_NUMBER 9600
#define SPEED_OF_SOUND 286.75F
#define DISTANCE_THRESHOLD 0.70F
#define BUZZER_PIN 6
#define BUZZER_MAX_FREQUENCY 1000.0F

void set_rgb_color(
  unsigned char red_color,
  unsigned char green_color,
  unsigned char blue_color) {
  digitalWrite(RED_LED_PIN, (int)red_color);
  digitalWrite(GREEN_LED_PIN, (int)green_color);
  digitalWrite(BLUE_LED_PIN, (int)blue_color);
}

float get_distance() {
  pinMode(USENSOR_SIGNAL_PIN, OUTPUT);
  
  digitalWrite(USENSOR_SIGNAL_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(USENSOR_SIGNAL_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(USENSOR_SIGNAL_PIN, LOW);
  
  pinMode(USENSOR_SIGNAL_PIN, INPUT);
  
  float elapsed_us = pulseIn(USENSOR_SIGNAL_PIN, HIGH);
  float distance_meters = elapsed_us / SPEED_OF_SOUND;
  distance_meters /= 20;
  
  Serial.print("Distance: ");
  Serial.print(distance_meters);
  Serial.print(" m");
  Serial.println();
  return distance_meters;
}

void play_buzzer() {
  for (int i = BUZZER_MAX_FREQUENCY; i > 0; i--) {
    if (i % 50 == 0)
    	tone(BUZZER_PIN, i);
    
    delay(1);
  }
}

void setup()
{
  Serial.begin(SERIAL_NUMBER);
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
  float distance = get_distance();
  if (distance > DISTANCE_THRESHOLD) {
    set_rgb_color(0, 255, 0);
    noTone(BUZZER_PIN);
  }
  else {
    set_rgb_color(255, 0, 0);
    play_buzzer();
  }
}
