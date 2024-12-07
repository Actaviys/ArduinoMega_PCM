#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

#define LED1 52
#define LED2 51

// 50 - Клавіш вводу
// 0 - 
// 1 - 

// `--` Головний екран  
// `<-` Попередня сторінка
// `->` Наступна сторінка



// ВСІ сенсорні панелі та проводка ІНШІ
// копіювати та вставляти результати з TouchScreen_Calibr_native.ino
const int XP=8,XM=A2,YP=A3,YM=9; 
const int TS_LEFT=912,TS_RT=109,TS_TOP=50,TS_BOT=955;


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button prev_btn, home_btn, next_btn; // Функціональні клавіші
Adafruit_GFX_Button btn_0, btn_1, btn_2, btn_3, btn_4, btn_5, btn_6, btn_7, btn_8, btn_9; // Числові клавіші

// Букви
Adafruit_GFX_Button btn_10, btn_11, btn_12; 


int pixel_x, pixel_y;     //Touch_getXY() оновлює глобальні змінні
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //відновити спільні шпильки
    pinMode(XM, OUTPUT);      //тому що TFT контрольні штифти
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv має сенс для мене
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK          0x0000
#define BLUE           0x001F
#define RED            0xF800
#define GREEN          0x07E0
#define CYAN           0x07FF
#define MAGENTA        0xF81F
#define YELLOW         0xFFE0
#define WHITE          0xFFFF
#define BROWN          0x00cc6d
#define DARK_BROWN     0x228B22
#define DARK_BLUE      0x8B008B
#define DARK_RED       0x808080


int width_funk_but = 80; // Ширина функціональних кнопок
int height_funk_but = 10; // Висота функціональних кнопок

int width_text_but = 24;  // Ширина текстових кнопок
int height_text_but = 28; // Висота текстових кнопок


// Функція для ініціалізації всіх кнопок на екрані
void inits_buttons(){
  prev_btn.initButton(&tft,  40, 395-(height_funk_but/3), width_funk_but, height_funk_but, WHITE, GREEN, BLACK, "<-", 1);
  home_btn.initButton(&tft, 120, 395-(height_funk_but/3), width_funk_but, height_funk_but, WHITE, GREEN, BLACK, "--", 1);
  next_btn.initButton(&tft, 200, 395-(height_funk_but/3), width_funk_but, height_funk_but, WHITE, GREEN, BLACK, "->", 1);

  // Числові клавіши
  btn_0.initButton(&tft, (width_text_but/2), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "0", 2); // "0"
  btn_1.initButton(&tft, (width_text_but/2+width_text_but), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "1", 2); // "1"
  btn_2.initButton(&tft, (width_text_but/2+(width_text_but*2)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "2", 2); // "2"
  btn_3.initButton(&tft, (width_text_but/2+(width_text_but*3)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "3", 2); // "3"
  btn_4.initButton(&tft, (width_text_but/2+(width_text_but*4)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "4", 2); // "4"
  btn_5.initButton(&tft, (width_text_but/2+(width_text_but*5)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "5", 2); // "5"
  btn_6.initButton(&tft, (width_text_but/2+(width_text_but*6)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "6", 2); // "6"
  btn_7.initButton(&tft, (width_text_but/2+(width_text_but*7)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "7", 2); // "7"
  btn_8.initButton(&tft, (width_text_but/2+(width_text_but*8)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "8", 2); // "8"
  btn_9.initButton(&tft, (width_text_but/2+(width_text_but*9)), 221+(height_text_but/2), width_text_but, height_text_but, WHITE, CYAN, BLACK, "9", 2); // "9"
  

  // Букви
  btn_10.initButton(&tft, (width_text_but/2), 221+(height_text_but/2+height_text_but), width_text_but, height_text_but, WHITE, CYAN, BLACK, "q", 2); // "q"
  btn_11.initButton(&tft, (width_text_but/2+width_text_but), 221+(height_text_but/2+height_text_but), width_text_but, height_text_but, WHITE, CYAN, BLACK, "w", 2); // "w"
  btn_12.initButton(&tft, (width_text_but/2+(width_text_but*2)), 221+(height_text_but/2+height_text_but), width_text_but, height_text_but, WHITE, CYAN, BLACK, "e", 2); // "e"



  next_btn.drawButton(false);
  prev_btn.drawButton(false);
  home_btn.drawButton(false);
  btn_0.drawButton(false);
  btn_1.drawButton(false);
  btn_2.drawButton(false);
  btn_3.drawButton(false);
  btn_4.drawButton(false);
  btn_5.drawButton(false);
  btn_6.drawButton(false);
  btn_7.drawButton(false);
  btn_8.drawButton(false);
  btn_9.drawButton(false);
  btn_10.drawButton(false);
  btn_11.drawButton(false);
  btn_12.drawButton(false);
}


void setup(void)
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
  tft.begin(0x7793); // write-only shield //240x400 ID=0x7793
  tft.setRotation(0);  //PORTRAIT(0) //HORIZONTAL(1) //PORTRAIT(2) //HORIZONTAL(3)
  tft.fillScreen(BLACK);
  // tft.fillScreen(MAGENTA);
  inits_buttons(); // Ініціалізація всіх кнопок

  tft.fillRect(40, 80, 160, 80, WHITE);
}


void functionals_button(){
}


void frame_buttons(){
  // tft.writeLine(0, 200, 10, 60, MAGENTA);
  int x_0 = 0; 
  int x_1 = 220;
  int y_0 = 239;
  int y_1 = 385;
  tft.drawLine(x_0, x_1, y_0, x_1, MAGENTA); // Горизонтальна лінія (1)
  tft.drawLine(x_0, x_1, x_0, y_1, MAGENTA); // Вертикальна лінія (1)
  tft.drawLine(y_0, x_1, y_0, y_1, MAGENTA); // Вертикальна лінія (2)
  tft.drawLine(x_0, y_1, y_0, y_1, MAGENTA); // Горизонтальна лінія (2)

  tft.drawRect(0, 190, 239, 30, CYAN); // Пряпокутник
}


String input_text_keys = ""; // Зберігаю текст з клавіш
boolean led1_flag = 0;
boolean led2_flag = 0;
void button_list_startup(){
  bool down = Touch_getXY();
  prev_btn.press(down && prev_btn.contains(pixel_x, pixel_y));
  home_btn.press(down && home_btn.contains(pixel_x, pixel_y));
  next_btn.press(down && next_btn.contains(pixel_x, pixel_y));

  btn_0.press(down && btn_0.contains(pixel_x, pixel_y)); // "0"
  btn_1.press(down && btn_1.contains(pixel_x, pixel_y)); // "1"
  btn_2.press(down && btn_2.contains(pixel_x, pixel_y)); // "2"
  btn_3.press(down && btn_3.contains(pixel_x, pixel_y)); // "3"
  btn_4.press(down && btn_4.contains(pixel_x, pixel_y)); // "4"
  btn_5.press(down && btn_5.contains(pixel_x, pixel_y)); // "5"
  btn_6.press(down && btn_6.contains(pixel_x, pixel_y)); // "6"
  btn_7.press(down && btn_7.contains(pixel_x, pixel_y)); // "7"
  btn_8.press(down && btn_8.contains(pixel_x, pixel_y)); // "8"
  btn_9.press(down && btn_9.contains(pixel_x, pixel_y)); // "9"
  btn_10.press(down && btn_10.contains(pixel_x, pixel_y)); // "q"
  btn_11.press(down && btn_11.contains(pixel_x, pixel_y)); // "w"
  btn_12.press(down && btn_12.contains(pixel_x, pixel_y)); // "e"

  if (prev_btn.justReleased()) prev_btn.drawButton();
  if (prev_btn.justPressed()) {
    prev_btn.drawButton(true);
    led1_flag = !led1_flag;
    digitalWrite(LED1, led1_flag);
    tft.fillRect(40, 80, 160, 80, MAGENTA);
  }

  if (next_btn.justReleased()) next_btn.drawButton();
  if (next_btn.justPressed()) {
    next_btn.drawButton(true);
    led2_flag = !led2_flag;
    digitalWrite(LED2, led2_flag);
    tft.fillRect(40, 80, 160, 80, RED);
  }


  if (home_btn.justReleased()) home_btn.drawButton();
  if (home_btn.justPressed()) {
    home_btn.drawButton(true);
    Serial.print("Send: ");
    Serial.println(input_text_keys);
    input_text_keys = "";
    tft.fillScreen(BLACK);
    inits_buttons();
  }


  
  if (btn_0.justReleased()) btn_0.drawButton(); // "0"
  if (btn_0.justPressed()) {
    btn_0.drawButton(true);
    input_text_keys += "0";
    // Serial.println("0");
  }

  if (btn_1.justReleased()) btn_1.drawButton(); // "1"
  if (btn_1.justPressed()) {
    btn_1.drawButton(true);
    input_text_keys += "1";
    // Serial.println("1");
  }


  if (btn_10.justReleased()) btn_10.drawButton(); // "q"
  if (btn_10.justPressed()) {
    btn_10.drawButton(true);
    input_text_keys += "q";
    // Serial.println("q");
  }

  if (btn_11.justReleased()) btn_11.drawButton(); // "w"
  if (btn_11.justPressed()) {
    btn_11.drawButton(true);
    input_text_keys += "w";
    // Serial.println("w");
  }
}


String status_text = "Status:";
void texts_actives(){
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.print(status_text);

  
  tft.setCursor(4, 193);
  tft.setTextColor(RED);  tft.setTextSize(3);
  tft.print(input_text_keys);

  tft.clearWriteError();

}



void loop(void){
  button_list_startup();
  texts_actives();
  frame_buttons();
  
}