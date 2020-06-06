/*
 * This program is used to simulate a mesurement system.
 * VCC = 5V
 * BUZZER - 100ohm - PIN_BUZZER
 * LED - PIN_LED
 * ADC - PIN_ADC
 * LCD_VO - 1ohm - GND
 * LCD_RS - PIN_RS
 * LCD_RW - GND
 * LCD_K - GND
 * LCD_A - 200ohm - VCC
 * LCD_DB4 - PIN_DB4
 * LCD_DB5 - PIN_DB5
 * LCD_DB6 - PIN_DB6
 * LCD_DB7 - PIN_DB7
 * IR - PIN_IR
 * L293D_OUT1 - M1
 * L293D_OUT2 - M1
 * L293D_OUT3 - M2
 * L293D_OUT4 - M2
 * L293D_IN1 - PIN_IN1
 * L293D_IN2 - PIN_IN2
 * L293D_IN3 - PIN_IN3
 * L293D_IN4 - PIN_IN4
 * L293D_EN12 - PIN_PWM1
 * L293D_EN34 - PIN_PWM2
 */

#include <Adafruit_NeoPixel.h>
#include <IRremote.h>
#include <LiquidCrystal.h>

#define PIN_IR 11
#define PIN_LED 13
#define PIN_RS 7
#define PIN_E A1
#define PIN_DB4 A2
#define PIN_DB5 A3
#define PIN_DB6 A4
#define PIN_DB7 A5
#define PIN_PWM1 5
#define PIN_IN1 2
#define PIN_IN2 3
#define PIN_PWM2 6
#define PIN_IN3 8
#define PIN_IN4 9
#define PIN_ADC A0
#define PIN_BUZZER 12
#define RESULT 7
#define SPEED 100
#define BAUD_RATIO 9600
#define BUZZER_TONE 3000
#define LED_NUMBER 12
#define BRIGHTNESS 40
#define RED 0xFF0000
#define GREEN 0X00C100
#define YELLOW 0XFFFF00
#define POWER 0xFD00FF
#define VOL_PLUS 0xFD807F
#define FUNC_STOP 0xFD40BF
#define LEFT 0xFD20DF
#define PLAY 0xFDA05F
#define RIGHT 0xFD609F
#define DOWN 0xFD10EF
#define VOL_MINUS 0xFD906F
#define UP 0xFD50AF
#define LCD_COLUMNS 16
#define LCD_LINES 2

uint8_t zh0[8] = {
	10, 23, 26, 15, 16, 31, 5, 31,
}; // 结
uint8_t zh1[8] = {
	31, 21, 31, 21, 31, 4, 31, 21,
}; // 果
Adafruit_NeoPixel strip =
Adafruit_NeoPixel(LED_NUMBER, PIN_LED, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(PIN_RS, PIN_E, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
IRrecv rc(PIN_IR);
decode_results results;
int speed = SPEED;

void setup() {
	Serial.begin(BAUD_RATIO);
	strip.begin();
	rc.enableIRIn();
	lcd.begin(LCD_COLUMNS, LCD_LINES);
	lcd.createChar(0, zh0);
	lcd.createChar(1, zh1);
	pinMode(PIN_ADC, INPUT);
	pinMode(PIN_BUZZER, OUTPUT);
	pinMode(PIN_PWM1, OUTPUT);
	pinMode(PIN_PWM2, OUTPUT);
	pinMode(PIN_IN1, OUTPUT);
	pinMode(PIN_IN2, OUTPUT);
	pinMode(PIN_IN3, OUTPUT);
	pinMode(PIN_IN4, OUTPUT);
}

void loop() {
	if (rc.decode(&results)) {
		switch (results.value) {
			case POWER:
				break;
			case VOL_PLUS:
				forward();
				break;
			case FUNC_STOP:
				break;
			case LEFT:
				turnLeft();
				break;
			case PLAY:
				stop();
				break;
			case RIGHT:
				turnRight();
				break;
			case DOWN:
				speedDown();
				break;
			case VOL_MINUS:
				backward();
				break;
			case UP:
				speedUp();
		}
		rc.resume();
	}
	float result = adc();
	Serial.print("Result: ");
	Serial.println(result);
	lcdRun(result);
	ledRun(result);
	buzzerRun(result);
}

float adc() {
	float measurement = analogRead(PIN_ADC);
	float result = (measurement / 1023.0) * 12;
	return result;
}

void lcdRun(float result) {
	lcd.setCursor(0, 0);
	lcd.write((uint8_t)0);
	lcd.write((uint8_t)1);
	lcd.setCursor(0, 1);
	lcd.print(result);
}

void ledRun(float result) {
	strip.setBrightness(BRIGHTNESS);
	for (int i = 0; i < result; i++) {
		if (i < 4)
			strip.setPixelColor(i, GREEN);
		else if (i < 8)
			strip.setPixelColor(i, YELLOW);
		else
			strip.setPixelColor(i, RED);
		for (int j = result; j <= 12; j++)
			strip.setPixelColor(j, 0, 0, 0);
		strip.show();
	}
}

void buzzerRun(float result) {
	// if (result > RESULT)
	// 	tone(PIN_BUZZER, 3000);
	// else
	// 	noTone(PIN_BUZZER);
}

void forward() {
	Serial.println("forward");
	analogWrite(PIN_PWM1, speed);
	analogWrite(PIN_PWM2, speed);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, LOW);
}

void backward() {
	Serial.println("backward");
	analogWrite(PIN_PWM1, speed);
	analogWrite(PIN_PWM2, speed);
	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, HIGH);
	digitalWrite(PIN_IN3, LOW);
	digitalWrite(PIN_IN4, HIGH);
}

void turnLeft() {
	Serial.println("turnLeft");
	analogWrite(PIN_PWM1, 0);
	analogWrite(PIN_PWM2, speed);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, LOW);
}

void turnRight() {
	Serial.println("turnRight");
	analogWrite(PIN_PWM1, speed);
	analogWrite(PIN_PWM2, 0);
	digitalWrite(PIN_IN1, HIGH);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, HIGH);
	digitalWrite(PIN_IN4, LOW);
}

void stop() {
	Serial.println("stop");
	digitalWrite(PIN_IN1, LOW);
	digitalWrite(PIN_IN2, LOW);
	digitalWrite(PIN_IN3, LOW);
	digitalWrite(PIN_IN4, LOW);
}

void speedUp() {
	Serial.println("speedUp");
	speed += 10;
	if (speed > 255)
		speed = 255;
	analogWrite(PIN_PWM1, speed);
	analogWrite(PIN_PWM2, speed);
}

void speedDown() {
	Serial.println("speedDown");
	speed -= 10;
	if (speed < 0)
		speed = 0;
	analogWrite(PIN_PWM1, speed);
	analogWrite(PIN_PWM2, speed);
}
