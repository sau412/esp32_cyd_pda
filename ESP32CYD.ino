/*
Что-то вроде КПК для ESP32 CYD (Cheap Yellow Display/Device)

Предположения:
- Ориентация экрана вертикальная
- ФС FFat/SD
- Папка настроек /Settings

Функции:
- Лаунчер
- Калькулятор
- Информация о системе
- Файловый менеджер
- Виртуальная клавиатура
- Фонарик
- Калибровка тач-сенсора
- Рисование (с сохранением)
- Пароль на вход
- Счётчик
- Тест экрана
- Скринсейвер
- Игра пятнашки
- Игра выключи свет
- Читалка
- Редактирование файла
- Генератор случайных чисел
- Таймер
- Яркость
- Секундомер
- Заметки
- Жизнь (клеточный автомат)
- I2C сканер
- Часы
- Неточные часы
- Подключение к вай-фаю
- Гофер браузер
- Погода (с настройкой координат)
- Чат
- Контакты
- Дела
- Расходы
- Расписание
- Просмотр шрифта
- Игра змейка
- Пасьянс турецкий платок
- Файловый сервер (с загрузкой файлов)
- Сохранение скриншотов по кнопке BOOT

Лог разработки:
2026-03-11 Лаунчер и статическая информация о системе
2026-03-12 Функция "нарисуй матрицу кнопок x на y в указанном месте", "проверить указанную матрицу кнопок на попадание нажатий", калькулятор (частично)
2026-03-13 Окошко с сообщением и кнопками, файловый менеджер (частично)
2026-03-16 Управление фонариком, файловый менеджер (частично), ввод клавиатурой (частично), рисование (без сохранения), алгоритм калибровки
2026-03-17 Калибровка при запуске, ввод клавиатурой, файловый менеджер: создание файлов, просмотр, удаление, правка
2026-03-18 Тест Wi-Fi, тест экрана, доработка клавиатурного ввода, основные файлы, FFAT
2026-03-19 Доработка файлового менеджера, переход к папкам, исправление багов
2026-03-23 Выход из приложений, двойной тап в файлах, калькулятор дробные значения, стрелки в калибровке
2026-03-24 Баг в скринсейвере, игра пятнашки
2026-04-28 Список, файловый менеджер со списком
2026-04-29 Сохранение результатов калибровки, калибровка по касанию экрана на старте, просмотр больших файлов
2026-05-07 Редактирование файла
2026-05-08 Цифровой пароль на вход, управление паролем и информацией о владельце, отладка редактирования файла
2026-05-09 Счётчик, редактирование файла
2026-05-10 Генератор случаных чисел, аптайм в информации о системе, папка System теперь Settings
2026-05-11 Баг с двукратным нажатием для выхода, автообновление информации о системе, выход через touchCheckNoWait
2026-05-12 Копирование и перемещение файлов, рисование линиями, таймер, яркость
2026-05-13 Секундомер, свободная память (heap) в информации о системе,
  доработка шрифтов, фоторезистор в информацию, особые кнопки у клавиатуры, индикатор выхода из приложения
2026-05-14 Баг секундомера, баг таймера, дыхательный таймер, подключение к Wi-Fi
2026-05-15 Выложил проект на гитхаб, ютуб, реддит; создание папки настроек после форматирования, константы, игра выключи свет, выигрыш в пятнашках
2026-05-16 Прошивка через веб, исправлен порядок инициализации ФС
2026-05-18 Исправлен глюк с редактированием, заметки, клеточный автомат жизнь, лаунчер в две колонки
2026-05-19 Информация о сети
2026-05-21 Исправил баг со списком сетей вай-фай, баг со списком заметок, возможность отключиться от Wi-Fi сети,
  информационный стенд, I2C сканер
2026-05-22 Исправлен баг с календарём, неточные часы
2026-05-23 Исправлены баги гофер-браузера, приложение книги
2026-05-25 Исправлен баг когда сеть по умолчанию вай-фай недоступна, погода и координаты
2026-05-26 Значки, чат
2026-05-27 Настройка времени, часового пояса, немного звуков, работа часов без интернета
2026-05-28 Текст справа в списке, общая PIM-функция, контакты, дела, расходы, баг в чате, размеры файлов в файловом менеджере
2026-05-29 Баг с выходом из просмотра, Обработка пар \n\r и \r\n в просмотре, убрать мигание чата, рисование с сохранением, баг выхода,
  знак вопроса в клавиатурные символы
2026-05-31 Русский шрифт, частично
2026-06-01 Русский шрифт доработки, расписание
2026-06-02 Русский шрифт доработки, PIM список по ширине экрана, улучшение счётчика, улучшение информации о системе, ускорение сохранения картинок
2026-06-03 Баг со сдвигом на пиксель в списках, баг в просмотре файлов, улучшение рисования, баг в расходах при ручном вводе,
  бип на новые сообщения в чате, баги и улучшения калькулятора, улучшения случайных чисел, поддержка SD как хранилища
2026-06-04 Цифры и символы на клавиатурах в зависимости от shift, отщёлкивать shift, не сохранять если не было изменений,
  ограничение длины надписи в списке, возможность редактировать несуществующий файл, удалять пустой файл PIM,
  ключ-значение чтение и запись, сохранять текущее положение в книгах, процент в калькуляторе,
  прокрутка текста в drawPrompt, змейка
2026-06-05 Просмотр шрифта, пасьянс турецкий платок
2026-06-06 Исправлено несколько багов в турецком платке, зелёный фон
2026-06-08 проблемы с большими файлами с SD, проблема с MP3, веб-сервер зато заработал, сохранение скриншотов по кнопке BOOT,
  сохранять пароль вай-фая
2026-06-09 Баг двойной смены направления в змейке, игра memory match, автозапуск, ханойские башни, пианино, группы приложений

Направления работы:
- Читать всю ФС как файл (для бэкапов на SD/http сервер)
- Записывать всю ФС как файл (для восстановления из бэкапа)
- Приложение настроек
- Группы приложений в лаунчере? А то уже в экран не влезает
- Повтор последовательности
- N назад
- Терминал
- Устный счёт
- Карточки для запоминания слов
- Справка
- Бэкапы (SD)
- IRC
- Консоль для пингов и прочего
- Бэкапы (через сеть)
- RSS
- 2048
- Камешки (Bejeweled)
- Ханойские башни
- Арканоид
- Проигрыватель мелодий нокии
- Метроном
- Тетрис
- MP3-плеер
- Интернет-радио

Улучшения тут и там:
- (б) Проблема при работе с SD, запись больше 2 кб
- (б) Гофер браузер - баг с повторяющимися строками?
- (д) В файловом менеджере открывать папки / файлы по двойному нажатию
- (д) Не прокручивать при редактировании дальше конца файла
- (д) Погода: символ градуса или цельсия возле температуры (выглядит ужасно если взять другой шрифт. Нужно другое решение)
- (д) Prompt - возможность переставлять курсор
- (д) Гофер браузер - менять домашнюю страницу
- (д) Гофер браузер - специальная домашняя страница для CYD с объяснениями
- (д) Гофер браузер - кнопка назад
- (д) Расписание: выводить планы на день по первому нажатию, редактирование по второму или двойному
- (д) Редактирование: меньше мигания
- (д) Просмотр: меньше мигания
- (д) Просмотр: прокручивать вперёд без перемотки файла
- (д) Выложить шрифты на гитхаб
- (д) Категории для PIM
- (д) Возможность отключать звук
- (д) Пасьянс - более чёткий указатель
- (д) Если SD есть, то основная память SD, если нет то нет
- (д) Автозапуск - настройка для выбора

*/

//#define ALT_KEYBOARD_ENABLED

#define IS_WIFI_ENABLED

//#define USE_SD_AS_STORAGE

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "FS.h"
#include "FFat.h"
#include "SD.h"
#include <Wire.h>
//#include "Audio.h" 

#ifdef IS_WIFI_ENABLED

#include "WiFi.h"
#include <HTTPClient.h>
#include <ESPping.h>
#include <WebServer.h>

#endif

#define FORMAT_FS_IF_FAILED false

TFT_eSPI tft = TFT_eSPI();

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

#define BACKLIGHT_LED 21
#define LIGHT_SENSOR 34

#define LED_RED 4
#define LED_GREEN 16
#define LED_BLUE 17

#define I2C_SDA 27 
#define I2C_SCL 22

#define BUZZER_PIN 26

#define BOOT_BUTTON_PIN 0

// SD SPI pins
#define SD_CS   5
#define SD_SCK 18
#define SD_MISO 19
#define SD_MOSI 23

SPIClass sdSPI(HSPI);
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define FONT_MONOSPACE 1
#define FONT_DEFAULT 2
#define FONT_BIG 4
#define FONT_BIGGER 6
#define FONT_BIG_SEGMENT 7
#define FONT_BIGGEST 8

#define APP_MODE_LAUNCH 1
#define APP_MODE_RETURN_NAME 0
#define APP_MODE_RETURN_ICON 2

#ifdef USE_SD_AS_STORAGE
#define Storage SD
//FS Storage = SD; 
#else
#define Storage FFat
//FS Storage = FFat;
#endif

char enter[] = {
  8, 8,
  B00000011,
  B00000011,
  B00100011,
  B01100011,
  B11111111,
  B11111111,
  B01100000,
  B00100000
};

char shift[] = {
  8, 8,
  B00011000,
  B00111100,
  B01111110,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
};

char backspace[] = {
  8, 8,
  B00000000,
  B00100000,
  B01100000,
  B11111111,
  B11111111,
  B01100000,
  B00100000,
  B00000000
};

char change_keyboard[] = {
  8, 8,
  B01111110,
  B00000010,
  B00000111,
  B00000010,
  B01000000,
  B11100000,
  B01000000,
  B01111110
};

// Калибровка тач-скрина
float d = -12314407;
float ax = -852720 / d;
float bx = 14880 / d;
float cx = 254777760 / d; 
float ay = 19840 / d;
float by = -1109440 / d;
float cy = 325691200 / d;

unsigned long global_touch_begin;
unsigned long global_touch_length;
TS_Point global_touch_p;
int global_touch_x;
int global_touch_y;
char global_touch_present_flag;
char global_exit_flag;
unsigned long global_exit_flag_touch_begin;
unsigned long global_exit_flag_touch_length;

float global_lat = 0;
float global_lon = 0;
int global_brightness = 255;

// После подключения к вай-фаю можно узнать текущее время
long global_unixtime_retrieved = 0;
long global_unixtime_retrieved_millis = 0;
long global_timezone = 0;

// Переменные для человекочитаемых параметров времени
int global_year = 0;
int global_month = 0;
int global_day = 0;
int global_hours = 0;
int global_minutes = 0;
int global_seconds = 0;
int global_moon_day = 0;
int global_day_of_week = 0;
char global_is_lap_year = 0;

void launcher(char mode, char *io_buff);
void calculator(char mode, char *io_buff);
void system_info(char mode, char *io_buff);
void files(char mode, char *io_buff);
void keyboard(char mode, char *io_buff);
void torch(char mode, char *io_buff);
void draw(char mode, char *io_buff);
#ifdef IS_WIFI_ENABLED
void wifi(char mode, char *io_buff);
void gopher(char mode, char *io_buff);
void chat(char mode, char *io_buff);
void weather(char mode, char *io_buff);
void http_file_access(char mode, char *io_buff);
#endif
void screen_test(char mode, char *io_buff);
void screensaver(char mode, char *io_buff);
void touch_calibration(char mode, char *io_buff);
void fifteen(char mode, char *io_buff);
void security(char mode, char *io_buff);
void counter(char mode, char *io_buff);
void random_numbers(char mode, char *io_buff);
void timer(char mode, char *io_buff);
void stopwatch_app(char mode, char *io_buff);
void breathe(char mode, char *io_buff);
void brightness_app(char mode, char *io_buff);
void lights_off(char mode, char *io_buff);
void notes(char mode, char *io_buff);
void contacts(char mode, char *io_buff);
void books(char mode, char *io_buff);
void todo(char mode, char *io_buff);
void expenses(char mode, char *io_buff);
void schedule(char mode, char *io_buff);
void life(char mode, char *io_buff);
void i2c_scanner(char mode, char *io_buff);
void dashboard(char mode, char *io_buff);
void fuzzy_clock(char mode, char *io_buff);
void set_clock(char mode, char *io_buff);
void snake(char mode, char *io_buff);
void view_font(char mode, char *io_buff);
void turkish_scarf(char mode, char *io_buff);
void memory_match(char mode, char *io_buff);
void hanoi_towers(char mode, char *io_buff);
void piano(char mode, char *io_buff);
void time_and_date_group(char mode, char *io_buff);
void games_group(char mode, char *io_buff);
void launcher_return_back(char mode, char *io_buff);

typedef void (*function_application_pointer) (char mode, char *io_buff);
typedef void (*function_action_pointer) (int action, char *filename);
typedef void (*function_conversion_pointer) (fs::File file, char *buff);

function_application_pointer apps[40] = {
  launcher,
  calculator,
  files,
  notes,
  contacts,
  todo,
  schedule,
  expenses,
  books,
  system_info,
  torch,
  draw,
#ifdef IS_WIFI_ENABLED
  wifi,
  gopher,
  chat,
  weather,
  http_file_access,
#endif
  counter,
  random_numbers,
  //timer,
  //stopwatch_app,
  //breathe,
  piano,
  screen_test,
  screensaver,
  security,
  brightness_app,
  touch_calibration,
  //fifteen,
  //lights_off,
  //snake,
  //turkish_scarf,
  //memory_match,
  //hanoi_towers,
  life,
  i2c_scanner,
  dashboard,
  //fuzzy_clock,
  //set_clock,
  view_font,
  time_and_date_group,
  games_group,
  NULL
};
function_application_pointer time_and_date_apps[40] = {
  launcher,
  launcher_return_back,
  timer,
  stopwatch_app,
  breathe,
  dashboard,
  fuzzy_clock,
  set_clock,
  NULL
};
function_application_pointer games_apps[40] = {
  launcher,
  launcher_return_back,
  fifteen,
  lights_off,
  snake,
  turkish_scarf,
  memory_match,
  hanoi_towers,
  NULL
};
function_application_pointer main_apps[40];

void launcher(char mode, char *io_buff) {
  int touch_x;
  int touch_y;
  char redraw_flag;
  char app_my_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Launcher");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_my_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Launcher");

  int row, col;
  char app_name[80];
  char app_icon[80];
  int apps_eol = 0;

  redraw_flag = 1;
  while(1) {
    if(redraw_flag) {
      for(col = 0; col < 2; col++) {
        for(row = 0; row < 19; row++) {
          if(!apps_eol) {
            if(apps[row + col * 19 + 1]) {
              apps[row + col * 19 + 1](APP_MODE_RETURN_NAME, app_name);
              apps[row + col * 19 + 1](APP_MODE_RETURN_ICON, app_icon);
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
              tft.drawString(app_name, 19 + col * tft.width() / 2, (row + 1) * 16, FONT_DEFAULT);
              image_from_bits(col * tft.width() / 2, (row + 1) * 16, app_icon, TFT_BLACK, TFT_WHITE);
            }
            else {
              apps_eol = row + col * 19 + 1;
            }
          }
        }
      }
      redraw_flag = 0;
    }

    touchExitActionReset();
    touchWaitRelease();
    touchWaitPress();

    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);

    row = (touch_y - 16) / 16;
    col = touch_x / (tft.width() / 2);

    if(row + col * 19 + 1 < apps_eol) {
      apps[row + col * 19 + 1](APP_MODE_RETURN_NAME, app_name);
      apps[row + col * 19 + 1](APP_MODE_RETURN_ICON, app_icon);
      tft.fillRect(col * tft.width() / 2, (row + 1) * 16, tft.width() / 2, 16, TFT_BLUE);
      tft.setTextColor(TFT_WHITE, TFT_BLUE);
      tft.drawString(app_name, 19 + col * tft.width() / 2, (row + 1) * 16, FONT_DEFAULT);
      image_from_bits(col * tft.width() / 2, (row + 1) * 16, app_icon, TFT_WHITE, TFT_BLUE);
      delay(100);
      touchWaitRelease();

      tft.fillRect(col * tft.width() / 2, (row + 1) * 16, tft.width() / 2, 16, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString(app_name, 19 + col * tft.width() / 2, (row + 1) * 16, FONT_DEFAULT);
      image_from_bits(col * tft.width() / 2, (row + 1) * 16, app_icon, TFT_BLACK, TFT_WHITE);

      apps[row + col * 19 + 1](APP_MODE_LAUNCH, NULL);
      break;
    }
  }
}

void time_and_date_group(char mode, char *io_buff) {
  int i;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00011111, B11111110,
    B00010000, B00000010,
    B01110000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01011111, B11111110,
    B01000000, B00001000,
    B01111111, B11111000,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Time & Date");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  for(i = 0; i < 40; i++) {
    apps[i] = time_and_date_apps[i];
  }
}

void games_group(char mode, char *io_buff) {
  int i;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00011111, B11111110,
    B00010000, B00000010,
    B01110000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01010000, B00000010,
    B01011111, B11111110,
    B01000000, B00001000,
    B01111111, B11111000,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Games");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  for(i = 0; i < 40; i++) {
    apps[i] = games_apps[i];
  }
}

void launcher_return_back(char mode, char *io_buff) {
  int i;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01001000, B00000010,
    B00011000, B00000010,
    B00111000, B00000010,
    B01111111, B11110010,
    B01111111, B11110010,
    B00111000, B00000010,
    B00011000, B00000010,
    B01001000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Back");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  for(i = 0; i < 40; i++) {
    apps[i] = main_apps[i];
  }
}


void calculator(char mode, char *io_buff) {
  double a = 0;
  double b = 0;
  double m = 0;

  char screen[20];
  char buff[20];
  char error_flag = 0;
  char dot_flag = 0;
  char op = '=';
  char clear_on_input = 0;
  char *buttons[] = {
    "MC",  "%",   "SQR", "+/-", "1/x",
    "MR",  "7",   "8",   "9",   "/",
    "M+",  "4",   "5",   "6",   "x",
    "CE",  "1",   "2",   "3",   "-",
    "C",   "0",   ".",   "=",   "+",
  };
  int button_pressed = 0;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01011111, B11111010,
    B01011111, B11111010,
    B01000000, B00000010,
    B01010101, B01011010,
    B01000000, B00000010,
    B01010101, B01011010,
    B01000000, B00000010,
    B01010101, B01011010,
    B01000000, B00000010,
    B01010101, B01011010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Calculator");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Calculator");

  strcpy(screen, "0");

  while(1) {
    tft.fillRect(0, 16, tft.width(), 80 - 16, TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    if(error_flag) {
      strcpy(screen, "Error");
    }
    tft.drawRightString(screen, tft.width() - 16, 40, FONT_BIG);

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    if(m != 0) {
      sprintf(buff, "M = %lg", m);
      tft.drawString(buff, 1, 16, FONT_DEFAULT);
    }
    if(op != '=') {
      sprintf(buff, "%lg %c", b, op);
      tft.drawRightString(buff, tft.width() - 1, 16, FONT_DEFAULT);
    }

    drawButtonMatrix(0, 80, tft.width(), 240, buttons, 5, 5);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 80, tft.width(), 240, buttons, 5, 5);
    if(button_pressed != -1) {
      if(!error_flag) {
        // MC
        if(button_pressed == 0) {
          m = 0;
        }
        // MR
        if(button_pressed == 5) {
          a = m;
          clear_on_input = 1;
          sprintf(screen, "%lg", a);
        }
        // M+
        if(button_pressed == 10) {
          m += a;
          clear_on_input = 1;
        }

        // SQR
        if(button_pressed == 2) {
          if(a < 0) {
            error_flag = 1;
          }
          else {
            a = sqrt(a);
          }
          clear_on_input = 1;
          sprintf(screen, "%lg", a);
        }
        // +/-
        if(button_pressed == 3) {
          a = -a;
          sprintf(screen, "%lg", a);
        }
        // 1/x
        if(button_pressed == 4) {
          if(a == 0) {
            error_flag = 1;
          }
          else {
            a = 1 / a;
          }
          clear_on_input = 1;
          sprintf(screen, "%lg", a);
        }
        // Цифровые кнопки
        if(button_pressed == 6 || button_pressed == 7 || button_pressed == 8
          || button_pressed == 11 || button_pressed == 12 || button_pressed == 13
          || button_pressed == 16 || button_pressed == 17 || button_pressed == 18
          || button_pressed == 21
        ) {
          if(clear_on_input) {
            a = 0;
            dot_flag = 0;
            clear_on_input = 0;
            strcpy(screen, "0");
          }
          if(strlen(screen) < 14) {
            // Строка не "0" или добавляем не 0
            if(strcmp(screen, "0")) {
              strcat(screen, buttons[button_pressed]);
            }
            else {
              strcpy(screen, buttons[button_pressed]);
            }
          }
          sscanf(screen, "%lf", &a);
        }

        // Операции
        if(button_pressed == 9 || button_pressed == 14 || button_pressed == 19
          || button_pressed == 23 || button_pressed == 24
        ) {
          // Выполнить предыдущую операцию
          if(op == '+') a = b + a;
          if(op == '-') a = b - a;
          if(op == '*') a = b * a;
          if(op == '/') a = b / a;
          b = a;
          sprintf(screen, "%lg", a);
          clear_on_input = 1;

          // Запомнить следующую операцию
          if(button_pressed == 9) {
            op = '/';
          }
          if(button_pressed == 14) {
            op = '*';
          }
          if(button_pressed == 19) {
            op = '-';
          }
          if(button_pressed == 24) {
            op = '+';
          }
          if(button_pressed == 23) {
            op = '=';
          }
        }
        if(button_pressed == 1) {
          // Выполнить предыдущую операцию как с процентами
          if(op == '+') a = b + a * b / 100;
          if(op == '-') a = b - a * b / 100;
          if(op == '*') a = a * b / 100;
          if(op == '/') a = 100 * b / a;
          b = a;
          sprintf(screen, "%lg", a);
          clear_on_input = 1;
          op = '=';
        }
      }
      // CE
      if(button_pressed == 15) {
        a = 0;
        error_flag = 0;
        dot_flag = 0;
        strcpy(screen, "0");
      }
      // C
      if(button_pressed == 20) {
        a = 0;
        b = 0;
        error_flag = 0;
        op = '=';
        clear_on_input = 0;
        dot_flag = 0;
        strcpy(screen, "0");
      }
      // Десятичная точка
      if(button_pressed == 22 && dot_flag == 0) {
        dot_flag = 1;
        if(strlen(screen) < 14) {
          strcat(screen, buttons[button_pressed]);
        }
        sscanf(screen, "%lf", &a);
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void system_info(char mode, char *io_buff) {
  char buff[80];
  int i = 0;
  long update_millis = millis();
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000011, B10000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000011, B11000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };


  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "System Info");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("System Info");
  
  while(1) {

    i = 0;
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "ESP32 CYD PDA by sau412");
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Build time: %s %s", __DATE__, __TIME__);
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "SDK: %s", ESP.getSdkVersion());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Chip model: %s", ESP.getChipModel());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Chip cores, speed: %d @ %d MHz", ESP.getChipCores(), ESP.getCpuFreqMHz());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "---");
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Total: %d bytes", ESP.getHeapSize());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Free: %d bytes (%d%%)", ESP.getFreeHeap(), (int)floor(100 * ESP.getFreeHeap() / ESP.getHeapSize()));
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Min Free: %d bytes", ESP.getMinFreeHeap());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Max Alloc: %d bytes", ESP.getMaxAllocHeap());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "---");
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Flash: %d bytes", ESP.getFlashChipSize());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Sketch: %d bytes", ESP.getSketchSize());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    if(Storage.totalBytes() > 1024 * 1024) {
      sprintf(buff, "Storage Total: %d MiB ", Storage.totalBytes() / (1024 * 1024));
    }
    else if(Storage.totalBytes() > 1024) {
      sprintf(buff, "Storage Total: %d kiB ", Storage.totalBytes() / (1024));
    }
    else {
      sprintf(buff, "Storage Total: %d bytes ", Storage.totalBytes());
    }
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    if(Storage.usedBytes() > 4096 * 1024) {
      sprintf(buff, "Storage Used: %d MiB (%d%%) ", Storage.usedBytes() / (1024 * 1024), (int)floor(100 * Storage.usedBytes() / Storage.totalBytes()));
    }
    else if(Storage.usedBytes() > 4096) {
      sprintf(buff, "Storage Used: %d kiB (%d%%) ", Storage.usedBytes() / (1024), (int)floor(100 * Storage.usedBytes() / Storage.totalBytes()));
    }
    else {
      sprintf(buff, "Storage Used: %d bytes (%d%%) ", Storage.usedBytes(), (int)floor(100 * Storage.usedBytes() / Storage.totalBytes()));
    }
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "---");
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;


    sprintf(buff, "Uptime: %dh %dm %ds     ", millis() / 3600000, (millis() / 60000) % 60, (millis() / 1000) % 60);
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Light sensor: %d    ", analogRead(LIGHT_SENSOR));
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    while(millis() - update_millis < 1000) {
      touchCheckNowait();
      if(global_exit_flag) {
        drawAppTitle("Exit");
        touchWaitRelease();
        touchExitActionReset();
        return;
      }
    }
    update_millis = millis();
  }
}

#define FILES_COUNT_MAX 1024

void files(char mode, char *io_buff) {
  fs::File current_dir;
  fs::File file;
  fs::File file_copy;
  int file_selected = 0;
  int prev_file_selected = 0;
  int file_offset = 0;
  int file_index = 0;
  char redraw_required = 0;
  char continue_flag = 0;
  int current_op = -1;
  char show_updir = 0;
  char path[80] = "/";
  char buff2[80];
  char buff3[80];
  char buff4[80];
  char user_input[80];
  char byte;
  char **files = NULL; // 14 элементов на экране
  int touch_x;
  int touch_y;
  int i;
  char *file_operations[] = {
    "New",    "View", "Edit", "Rename",
    "NewDir", "Copy", "Move", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00111111, B00000000,
    B01000000, B10000000,
    B01000000, B01111100,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Files");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Files");
  
  redraw_required = 1;
  
  while(1) {
    if(redraw_required) {
      clearScreen();
      drawAppTitle("Files");

      drawButtonMatrix(0, tft.width(), 240, 80, file_operations, 4, 2);

      redraw_required = 0;
    }

    // Список файлов
    current_dir = Storage.open(path);
    file_index = 0;

    if (!current_dir) {
      drawError("Failed to open directory");
      return;
    }
    if (!current_dir.isDirectory()) {
      drawError("Not a directory");
#ifndef USE_SD_AS_STORAGE
      if(!strcmp("/", path)) {
        if(drawConfirm("Format storage?") == 0) {
          FFat.format();
          FFat.begin(FORMAT_FS_IF_FAILED);
          Storage.mkdir("/Settings");
        }
      }
#endif
      return;
    }

    // Текущий путь
    file_index = 0;
    sprintf(buff2, "Path: %s", path);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.fillRect(0, 16, tft.width(), 16, TFT_WHITE);
    tft.drawString(buff2, 8, 16, FONT_DEFAULT);

    // Освобождаем память
    if(files) {
      for(i = 0; files[i] != NULL; i++) {
        free(files[i]);
      }
      free(files);
    }
    // Занимаем память, сразу на FILES_COUNT_MAX элементов, с realloc глючит
    files = (char**)malloc(FILES_COUNT_MAX * sizeof(char*));
    files[0] = NULL;
    //delay(1000);
    if(strcmp(path, "/")) {
      sprintf(buff2, "[u] ..");
      files[file_index] = (char*)malloc((strlen(buff2) + 1) * sizeof(char));
      strcpy(files[file_index], buff2);
      files[file_index + 1] = NULL;
      file_index ++;
    }
    while(file = current_dir.openNextFile()) {
      //realloc(files, (file_index + 2) * sizeof(char*));
      if(file.isDirectory()) {
        sprintf(buff2, "%s\t%s", file.name(), "[dir]");
      }
      else {
        if(file.size() > 4096) {
          sprintf(buff2, "%s\t%dk", file.name(), file.size() / 1024);
        }
        else {
          sprintf(buff2, "%s\t%db", file.name(), file.size());
        }
      }
      files[file_index] = (char*)malloc((strlen(buff2) + 1) * sizeof(char));
      strcpy(files[file_index], buff2);
      files[file_index + 1] = NULL;
      file_index ++;
    }

    // Сначала проверить нажатия, потом нарисовать, так нажатие сработает сразу
    touchCheckList(0, 40, 240, 192, files, 12, &file_offset, &file_selected);
    drawList(0, 40, 240, 192, files, 12, &file_offset, &file_selected);

    drawButtonMatrix(0, 240, tft.width(), 80, file_operations, 4, 2);

    touchWaitPress();
    touchCheckList(0, 40, 240, 192, files, 12, &file_offset, &file_selected);

    // Операции
    current_op = touchCheckMatrix(0, 240, tft.width(), 80, file_operations, 4, 2);
    if(current_op != -1) {
      // Находим нужный файл
      current_dir = Storage.open(path);
      file_index = 0;
      if(strcmp(path, "/")) {
        file_index++;
      }
      while(file = current_dir.openNextFile()) {
        if(file_selected == file_index) break;
        file_index++;
      }

      // Новый файл
      if(current_op == 0) {
        strcpy(user_input, "");
        drawPrompt("New file name", user_input);
        if(strlen(user_input) > 0) {
          sprintf(buff2, "%s%s", path, user_input);
          file = Storage.open(buff2, FILE_WRITE);
          if (!file) {
            drawAlert("Failed to create new file");
            return;
          }
          file.close();
        }
        current_op = -1;
        redraw_required = 1;
      }
      // Просмотр или переход к папке
      if(current_op == 1) {
        // Если не корень, и был выбран нулевой элемент, то переход на уровень выше
        if(strcmp(path, "/") && file_selected == 0) {
          path[strlen(path) - 1] = 0;
          while(path[strlen(path) - 1] != '/' && strlen(path) > 0) {
            path[strlen(path) - 1] = 0;
          }
          if(strlen(path) == 0) {
            strcpy(path, "/");
          }
          file_selected = 0;
          file_offset = 0;
        }
        else {
          if(file.isDirectory()) {
            strcat(path, file.name());
            strcat(path, "/");
            file_selected = 0;
            file_offset = 0;
          }
          else {
            sprintf(buff2, "View: %s%s", path, file.name());
            sprintf(buff3, "%s%s", path, file.name());
            view_file(buff2, buff3);
          }
        }
      }
      // Редактирование
      if(current_op == 2) {
        if(strcmp(path, "/") && file_selected == 0) {
          drawError("Unable to edit directory");
        }
        else {
          sprintf(buff2, "Edit: %s%s", path, file.name());
          sprintf(buff3, "%s%s", path, file.name());
          edit_file(buff2, buff3);
        }
      }
      // Переименование
      if(current_op == 3) {
        strcpy(user_input, "");
        drawPrompt("Rename file name", user_input);
        if(strlen(user_input) != 0) {
          sprintf(buff3, "%s%s", path, file.name());
          sprintf(buff4, "%s%s", path, user_input);
          if(!Storage.rename(buff3, buff4)) {
            drawAlert("Rename failed");
            drawInfo(buff3);
            drawInfo(buff4);
          }
        }
      }
      // Новая папка
      if(current_op == 4) {
        strcpy(user_input, "");
        drawPrompt("New directory name", user_input);
        sprintf(buff3, "%s%s", path, user_input);
        if (!Storage.mkdir(buff3)) {
          drawAlert("Failed to create new directory");
          return;
        }
      }
      // Копирование
      if(current_op == 5) {
        strcpy(user_input, "");
        drawPrompt("Enter path to copy", user_input);
        if(strlen(user_input) != 0) {
          sprintf(buff3, "%s%s", path, file.name());
          strcpy(buff4, user_input);
          
          // Если путь без / в начале, то это относительный путь
          if(user_input[0] != '/') {
            sprintf(buff4, "%s%s", path, user_input);
          }
          strcpy(user_input, buff4);

          // Если путь не заканчивается на /, то надо проверить, папка это или файл, который нужно создать
          if(user_input[strlen(user_input) - 1] == '/') {
            sprintf(buff4, "%s%s", user_input, file.name());
          }
          else {
            // Если это папка нужно добавить '/' и имя файла
            current_dir = Storage.open(user_input);
            if(current_dir) {
              if(current_dir.isDirectory()) {
                sprintf(buff4, "%s/%s", user_input, file.name());
              }
              current_dir.close();
            }
            // А если нет, то ничего не трогать
          }

          // Копирование
          file = Storage.open(buff3);
          file_copy = Storage.open(buff4, FILE_WRITE);
          if(!file) {
            drawAlert("Cannot open source file");
          }
          else if(!file_copy) {
            drawAlert("Cannot open destination file");
          }
          else {
            while(file.available()) {
              byte = file.read();
              file_copy.print(byte);
            }
            file.close();
            file_copy.close();
          }
        }
      }
      // Перемещение
      if(current_op == 6) {
        strcpy(user_input, "");
        drawPrompt("Enter path to move", user_input);
        if(strlen(user_input) != 0) {
          sprintf(buff3, "%s%s", path, file.name());
          strcpy(buff4, user_input);

          // Если путь без / в начале, то это относительный путь
          if(user_input[0] != '/') {
            sprintf(buff4, "%s%s", path, user_input);
          }
          strcpy(user_input, buff4);

          // Если путь заканчивается без /, то надо проверить, папка это или файл, который нужно создать
          if(user_input[strlen(user_input) - 1] == '/') {
            sprintf(buff4, "%s%s", user_input, file.name());
          }
          else {
            // Если это папка нужно добавить '/' и имя файла
            current_dir = Storage.open(user_input);
            if(current_dir && current_dir.isDirectory()) {
              sprintf(buff4, "%s/%s", user_input, file.name());
            }
            current_dir.close();
          }
          sprintf(buff4, "%s", user_input);
          if(!Storage.rename(buff3, buff4)) {
            drawAlert("Rename failed");
            drawInfo(buff3);
            drawInfo(buff4);
          }
        }
      }
      // Удаление
      if(current_op == 7) {
        if(drawConfirm("Delete file?") == 0) {
          sprintf(buff3, "%s%s", path, file.name());
          if(file.isDirectory()) {
            Storage.rmdir(buff3);
          }
          else {
            Storage.remove(buff3);
          }
          current_op = -1;
          file_selected = 0;
        }
      }
      redraw_required = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();

      if(files) {
        for(i = 0; files[i] != NULL; i++) {
          free(files[i]);
        }
        free(files);
      }
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

// ====================================================
// Заметки
// ====================================================

#define NOTES_PATH "/Notes"

void notes_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  if(action_index == 0) {
    // Редактируем новый файл
    sprintf(buff, "%s/%s", NOTES_PATH, "__New");
    //file = Storage.open(buff, FILE_WRITE);
    //file.close();
    edit_file("New note", buff);

    file = Storage.open(buff);
    if(!file) {
      return;
    }
    else if(file.size() == 0) {
      file.close();
      Storage.remove(buff);
    }
    else {
      file.close();
      // Меняем название в соответствии с содержимым
      pim_rename_file(NOTES_PATH, "__New", NULL);
    }
  }
  else if(action_index == 1) {
    // Редактируем существующий файл
    sprintf(buff, "%s/%s", NOTES_PATH, filename);
    edit_file("Edit note", buff);

    // Меняем название в соответствии с содержимым
    pim_rename_file(NOTES_PATH, filename, NULL);
  }
  else if(action_index == 2) {
    if(drawConfirm("Delete this note?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", NOTES_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void notes_file_to_list(fs::File file, char *buff) {
  char left[80];
  char right[80];
  char byte;
  int offset;
  // Левая колонка - первая непустая строчка файла
  offset = 0;
  left[offset] = 0;
  while(file.available()) {
    byte = file.read();
    if(byte == '\n') break;
    left[offset] = byte;
    offset++;
    left[offset] = 0;
    if(offset > 39) {
      break;
    }
  }
  sprintf(buff, "%s", left);
}

void notes(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Edit", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00110110, B01101100,
    B01001001, B10010010,
    B01000000, B00000010,
    B01010110, B11111010,
    B01000000, B00000010,
    B01011110, B11000010,
    B01000000, B00000010,
    B01010101, B11111010,
    B01000000, B00000010,
    B01011101, B10000010,
    B01000000, B00000010,
    B01010111, B11110010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Notes");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Notes", NOTES_PATH, notes_file_to_list, buttons, notes_action);
}

// ====================================================
// Контакты
// ====================================================

#define CONTACTS_PATH "/Contacts"

void contacts_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  if(action_index == 0) {
    // Редактируем новый файл
    sprintf(buff, "%s/%s", CONTACTS_PATH, "__New");
    //file = Storage.open(buff, FILE_WRITE);
    //file.close();
    edit_file("New contact", buff);

    // Меняем название в соответствии с содержимым
    file = Storage.open(buff);
    if(!file) {
      return;
    }
    else if(file.size() == 0) {
      file.close();
      Storage.remove(buff);
    }
    else {
      file.close();
      // Меняем название в соответствии с содержимым
      pim_rename_file(CONTACTS_PATH, "__New", NULL);
    }
  }
  else if(action_index == 1) {
    // Редактируем существующий файл
    sprintf(buff, "%s/%s", CONTACTS_PATH, filename);
    edit_file("Edit note", buff);

    // Меняем название в соответствии с содержимым
    pim_rename_file(CONTACTS_PATH, filename, NULL);
  }
  else if(action_index == 2) {
    if(drawConfirm("Delete this contact?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", CONTACTS_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void contacts_file_to_list(fs::File file, char *buff) {
  char left[80];
  char right[80];
  char byte;
  int offset;
  // Первая строчка - имя
  offset = 0;
  left[offset] = 0;
  while(file.available()) {
    byte = file.read();
    if(byte == '\n') break;
    left[offset] = byte;
    offset++;
    left[offset] = 0;
    if(offset > 39) {
      break;
    }
  }
  // Вторая строчка - телефон (почта, аська, скайп, что угодно)
  offset = 0;
  right[offset] = 0;
  while(file.available()) {
    byte = file.read();
    if(byte == '\n') break;
    right[offset] = byte;
    offset++;
    right[offset] = 0;
    if(offset > 39) {
      break;
    }
  }
  sprintf(buff, "%s\t%s", left, right);
}

void contacts(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Edit", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000011, B11000010,
    B01000111, B11100010,
    B01000111, B11100010,
    B01000111, B11100010,
    B01000011, B11000010,
    B01000001, B10000010,
    B01000011, B11000010,
    B01001111, B11110010,
    B01011111, B11111010,
    B01011111, B11111010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Contacts");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Contacts", CONTACTS_PATH, contacts_file_to_list, buttons, contacts_action);
}

// ====================================================
// Дела
// ====================================================

#define TODO_PATH "/Todo"

void todo_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  char new_filename[80];
  char old_path_filename[80];
  char new_path_filename[80];
  if(action_index == 0) {
    // Редактируем новый файл
    sprintf(buff, "%s/%s", TODO_PATH, "__New");
    //file = Storage.open(buff, FILE_WRITE);
    //file.close();
    edit_file("New todo item", buff);

    file = Storage.open(buff);
    if(!file) {
      return;
    }
    else if(file.size() == 0) {
      file.close();
      Storage.remove(buff);
    }
    else {
      file.close();
      // Меняем название в соответствии с содержимым
      pim_rename_file(TODO_PATH, "__New", NULL);
    }
  }
  else if(action_index == 1) {
    // Переключить отметку
    strcpy(new_filename, filename);
    if(filename[0] == '0') {
      new_filename[0] = '1';
    }
    else {
      new_filename[0] = '0';
    }
    sprintf(old_path_filename, "%s/%s", TODO_PATH, filename);
    sprintf(new_path_filename, "%s/%s", TODO_PATH, new_filename);
    Storage.rename(old_path_filename, new_path_filename);
  }
  else if(action_index == 2) {
    // Редактируем существующий файл
    sprintf(buff, "%s/%s", TODO_PATH, filename);
    edit_file("Edit todo item", buff);

    // Меняем название в соответствии с содержимым
    pim_rename_file(TODO_PATH, filename, (char*)(filename[0] == '1' ? "1_" : "0_"));
  }
  else if(action_index == 3) {
    if(drawConfirm("Delete this todo item?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", TODO_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void todo_file_to_list(fs::File file, char *buff) {
  char left[80];
  char right[80];
  char byte;
  char check = 0;
  int offset;
  // Если имя файла начинается с 1 то отметка есть
  if(file.name()[0] == '1') {
    check = 1;
  }
  // Левая колонка - название
  offset = 0;
  left[offset] = 0;
  while(file.available()) {
    byte = file.read();
    if(byte == '\n') break;
    if(offset <= 39) {
      left[offset] = byte;
      offset++;
      left[offset] = 0;
    }
  }
  // Правая колонка - есть ли что-то кроме названия
  offset = 0;
  right[offset] = 0;
  while(file.available()) {
    byte = file.read();
    if(byte == '\n') break;
    if(offset > 39) {
      right[offset] = byte;
      offset++;
      right[offset] = 0;
    }
  }
  sprintf(buff, "[%c] %s\t%s", check ? 'V' : ' ', left, strlen(right) > 0 ? "+" : "");
}

void todo(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Toggle", "Edit", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00011010,
    B01000000, B00011010,
    B01000000, B00110010,
    B01000000, B00110010,
    B01000000, B01100010,
    B01011000, B01100010,
    B01001100, B11000010,
    B01000110, B11000010,
    B01000011, B11000010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Todo");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Todo", TODO_PATH, todo_file_to_list, buttons, todo_action);
}

// ====================================================
// Расходы
// ====================================================

#define EXPENSES_PATH "/Expenses"

void expenses_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  char name[80];
  float item;
  if(action_index == 0) {
    // Добавляем категорию
    if(drawPrompt("Category name", name) == 0) {
      sprintf(buff, "%s/%s", EXPENSES_PATH, "__New");
      file = Storage.open(buff, FILE_WRITE);
      file.println(name);
      file.close();

      // Меняем название в соответствии с содержимым
      pim_rename_file(EXPENSES_PATH, "__New", NULL);
    }
  }
  else if(action_index == 1) {
    // Добавить расход
    strcpy(name, "");
    if(drawPrompt("Expense amount", name) == 0) {
      sscanf(name, "%f", &item);
      if(item == 0) {
        drawError("Expense amount cannot be zero");
      }
      else {
        sprintf(buff, "%s/%s", EXPENSES_PATH, filename);
        file = Storage.open(buff, FILE_APPEND);
        file.println(name);
        file.close();
      }
    }
  }
  else if(action_index == 2) {
    if(drawConfirm("Delete this category?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", EXPENSES_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void expenses_file_to_list(fs::File file, char *buff) {
  char left[80];
  char right[80];
  char byte;
  int offset;
  float item;
  float summ = 0;
  // Левая колонка - первая непустая строчка файла (название категории)
  offset = 0;
  left[offset] = 0;
  while(file.available()) {
    byte = file.read();
    if(byte == '\n' && file.peek() == '\r') {
      file.read();
    }
    if(byte == '\r' && file.peek() == '\n') {
      file.read();
    }
    if(byte == '\n' || byte == '\r') break;
    if(offset <= 39) {
      left[offset] = byte;
      offset++;
      left[offset] = 0;
    }
  }
  // Суммируем последующие строки
  offset = 0;
  right[offset] = 0;
  summ = 0;
  while(file.available()) {
    byte = file.read();
    right[offset] = byte;
    offset++;
    right[offset] = 0;
    if(byte == '\n' && file.peek() == '\r') {
      file.read();
    }
    if(byte == '\r' && file.peek() == '\n') {
      file.read();
    }
    if(byte == '\n' || byte == '\r') {
      item = 0;
      sscanf(right, "%f", &item);
      if(item) {
        summ += item;
      }
      offset = 0;
      right[offset] = 0;
    }
  }
  if(strlen(right) > 0) {
    sscanf(right, "%f", &item);
    if(item) {
      summ += item;
    }
  }

  sprintf(buff, "%s\t%0.2f", left, summ);
}

void expenses(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Expense", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000001, B10000010,
    B01001111, B11111010,
    B01010001, B10000010,
    B01010001, B10000010,
    B01001111, B11110010,
    B01000001, B10001010,
    B01000001, B10001010,
    B01000001, B10001010,
    B01011111, B11110010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Expenses");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Expenses", EXPENSES_PATH, expenses_file_to_list, buttons, expenses_action);
}

// ====================================================
// Книги
// ====================================================

#define BOOKS_PATH "/Books"

void books_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  char new_name[80];
  char old_path_filename[80];
  char new_path_filename[80];

  if(action_index == 0) {
    // Чтение
    sprintf(buff, "%s/%s", BOOKS_PATH, filename);
    view_file(filename, buff);
  }
  else if(action_index == 1) {
    // Переименование
    strcpy(buff, filename);
    if(drawPrompt("New book name", buff) == 0) {
      // Если название не пустое
      if(strcmp(buff, "")) {
        sprintf(old_path_filename, "%s/%s", BOOKS_PATH, filename);
        sprintf(new_path_filename, "%s/%s", BOOKS_PATH, buff);
        Storage.rename(old_path_filename, new_path_filename);
      }
    }
  }
  else if(action_index == 2) {
    if(drawConfirm("Delete this book?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", BOOKS_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void books_file_to_list(fs::File file, char *buff) {
  char left[80];
  char right[80];
  char byte;
  int offset;
  if(file.size() > 4096) {
    sprintf(buff, "%s\t%dk", file.name(), file.size() / 1024);
  }
  else {
    sprintf(buff, "%s\t%d", file.name(), file.size());
  }
}

void books(char mode, char *io_buff) {
  char *buttons[] = {
    "Read", "Rename", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00011111, B11111110,
    B00100000, B00000100,
    B00100000, B00000100,
    B00111111, B11111110,
    B01000000, B00001000,
    B01000000, B00001000,
    B00111111, B11111110,
    B00100000, B00000100,
    B00100000, B00000100,
    B00111111, B11111110,
    B01000000, B00000100,
    B01000000, B00000100,
    B01000000, B00000100,
    B00111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Books");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Books", BOOKS_PATH, books_file_to_list, buttons, books_action);
}

// ====================================================
// Рисование
// ====================================================

#define DRAW_PATH "/Images"

void draw_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  char old_path_filename[80];
  char new_path_filename[80];
  int index;

  if(action_index == 0) {
    // Придумываем новое название
    index = 0;
    while(1) {
      index++;
      sprintf(buff, "%s/Draw %d.bmp", DRAW_PATH, index);
      file = Storage.open(buff);
      if(!file) {
        break;
      }
      file.close();
    }
    draw_edit("New", buff);
  }
  else if(action_index == 1) {
    // Редактируем существующий файл
    sprintf(buff, "%s/%s", DRAW_PATH, filename);
    draw_edit(filename, buff);
  }
  else if(action_index == 2) {
    // Переименование
    strcpy(buff, filename);
    if(drawPrompt("New image name", buff) == 0) {
      // Если название не пустое
      if(strcmp(buff, "")) {
        sprintf(old_path_filename, "%s/%s", DRAW_PATH, filename);
        sprintf(new_path_filename, "%s/%s", DRAW_PATH, buff);
        Storage.rename(old_path_filename, new_path_filename);
      }
    }
  }
  else if(action_index == 3) {
    if(drawConfirm("Delete this image?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", DRAW_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void draw_file_to_list(fs::File file, char *buff) {
  sprintf(buff, "%s", file.name());
}

void draw(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Edit", "Rename", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00001110,
    B01000000, B00010010,
    B01000000, B00010010,
    B01000110, B00001010,
    B01001001, B00001010,
    B01001000, B10001010,
    B01010000, B01001010,
    B01010000, B00110010,
    B01010000, B00000010,
    B01100000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Draw");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Draw", DRAW_PATH, draw_file_to_list, buttons, draw_action);
}

void draw_edit(char *title, char *filename) {
  fs::File file;
  char buff[80];
  char draw_header[118] = {
    0x42, 0x4D, 0x76, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x20, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87,
    0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00
  };

  int i;
  TS_Point p;
  
  int color = TFT_BLACK;
  int color_index = 0;
  
  int colors[] = {
    TFT_BLACK, TFT_MAROON, TFT_DARKGREEN, TFT_OLIVE,
    TFT_NAVY, TFT_PURPLE, TFT_DARKCYAN, TFT_LIGHTGREY,
    TFT_DARKGREY, TFT_RED, TFT_GREEN, TFT_YELLOW,
    TFT_BLUE, TFT_MAGENTA, TFT_CYAN, TFT_WHITE};
  int touch_x;
  int touch_y;
  int x, y;
  int prev_touch_x;
  int prev_touch_y;
  int prev2_touch_x;
  int prev2_touch_y;
  char touch_started = 0;
  char byte;
  int pixel_color;
  char modified = 0;

  clearScreen();

  drawAppTitle("Loading...");

  // Загрузка из файла (если он есть)
  file = Storage.open(filename);
  if(file) {
    // Пропускаем заголовок BMP (у меня вышло 118 байт, но лучше ориентироваться на размер файла)
    i = file.size() - tft.width() * (tft.height() - 32) / 2;
    for(; i > 0; i--) {
      file.read();
    }
    // Читаем данные изображения и выводим на экран
    x = 0;
    y = 288;
    while(file.available()) {
      //Половина размера экрана (120) должна быть кратна размеру буфера
      file.read((unsigned char*)buff, 60);
      for(i = 0; i < 60; i++) {
        byte = buff[i];
        color_index = byte >> 4;
        color = colors[color_index];
        tft.drawPixel(x, y + 16, color);
        x++;
        color_index = byte & B00001111;
        color = colors[color_index];
        tft.drawPixel(x, y + 16, color);
        x++;
      }
      if(x >= tft.width()) {
        x = 0;
        y --;
      }
      if(y < 0) break;
    }
    file.close();
  }
  else {
    tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
  }

  drawAppTitle(title);

  for(color_index = 0; color_index < 16; color_index++) {
    tft.fillRect(color_index * tft.width() / 16, 304, tft.width() / 16, 16, colors[color_index]);
  }
  color_index = 0;

  color = TFT_BLACK;
  while(1) {
    touchWaitPress();
    while(touchscreen.tirqTouched() && touchscreen.touched()) {
      touchCheckNowait();
      p = touchscreen.getPoint();
      touch_x = touchMapX(p.x, p.y);
      touch_y = touchMapY(p.x, p.y);

      if(touch_x >= 0 && touch_x < tft.width() && touch_y >= 16 && touch_y < 304) {
        // Если линия движется медленно, рисовать линию
        // Нужно для избегания рывков линии при подъёме стилуса
        if(touch_started) {
          if(abs(touch_x - prev_touch_x) + abs(touch_y - prev_touch_y) < 10) {
            tft.drawLine(prev_touch_x, prev_touch_y, touch_x, touch_y, colors[color_index]);
          }
        }
        else {
          tft.drawPixel(touch_x, touch_y, colors[color_index]);
          touch_started = 1;
          modified = 1;
        }
      }
      else {
        touch_started = 0;
      }
      prev_touch_x = touch_x;
      prev_touch_y = touch_y;
      if(touch_x >= 0 && touch_x < tft.width() && touch_y >= 304 && touch_y < tft.height()) {
        color_index = floor(touch_x * 16 / tft.width());
      }
      touchCheckNowait();

      //touchWaitReleaseOrExit();
      if(global_exit_flag) {
        drawAppTitle("Exit");
        touchWaitRelease();
        if(modified) {
          drawAppTitle("Saving...");
          file = Storage.open(filename, FILE_WRITE);
          file.write((const uint8_t *)draw_header, 118);
          // Записываем данные изображения с экрана
          x = 0;
          y = 288;
          while(y >= 0) {
            // Половина ширины картинки (120) должна без остатка делиться на размер буфера
            for(i = 0; i < 60; i++) {
              byte = 0;
              pixel_color = tft.readPixel(x, y + 16);
              for(color_index = 0; color_index < 16; color_index++) {
                if(pixel_color == colors[color_index]) break;
              }
              byte |= color_index << 4;
              x++;
              pixel_color = tft.readPixel(x, y + 16);
              for(color_index = 0; color_index < 16; color_index++) {
                if(pixel_color == colors[color_index]) break;
              }
              byte |= color_index;
              x++;
              //file.write(byte);
              buff[i] = byte;
            }
            file.write((const uint8_t *)buff, 60);
            //file.flush();
            if(x >= tft.width()) {
              sprintf(buff, "Saving... (%d/288)", 288 - y);
              drawAppTitle(buff);
              x = 0;
              y--;
            }
          }

          file.close();
        }
        touchExitActionReset();
        return;
      }
    }
    touchWaitRelease();
    touch_started = 0;
  }
}

// ====================================================
// Общие PIM-функции
// ====================================================

#define PIM_FILES_COUNT_MAX 1000
// Рисует типичное приложение PIM (заметки, контакты, книги, расходы, дела, рисунки)
// title - заголовок приложения
// path - путь к файлам
// file_to_list_function - функция для преобразования содержимого файла в элемент списка
// buttons - кнопки действий
// action_function - функция активации по индексу кнопки
void pim_app(char *title, char *path, function_conversion_pointer file_to_list_function, char **buttons, function_action_pointer action_function) {
  fs::File current_dir;
  fs::File file;
  int button_pressed;
  int buttons_count;
  int file_offset = 0;
  int file_selected = 0;
  int i;
  int offset;
  char buff[80];
  char buff2[80];
  char buff3[80];
  char left[80];
  char right[80];
  char byte;
  char update_list_flag = 1;
  char rename_file_flag = 0;
  char **files_list = NULL;
  char **visible_list = NULL;

  // Считаем число кнопок
  buttons_count = 0;
  while(buttons[buttons_count]) {
    buttons_count++;
  }

  // Резервируем память, инициализируем
  files_list = (char **)malloc(PIM_FILES_COUNT_MAX * sizeof(char *));
  visible_list = (char **)malloc(PIM_FILES_COUNT_MAX * sizeof(char *));
  for(i = 0; i < PIM_FILES_COUNT_MAX; i++) {
    files_list[i] = NULL;
    visible_list[i] = NULL;
  }

  update_list_flag = 1;
  while(1) {
    // Обновляем список файлов если нужно
    if(update_list_flag) {
      clearScreen();
      drawAppTitle(title);
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      offset = 0;
      // Освобождаем память
      for(i = 0; i < PIM_FILES_COUNT_MAX; i++) {
        if(files_list[i]) {
          free(files_list[i]);
          free(visible_list[i]);
        }
        files_list[i] = NULL;
        visible_list[i] = NULL;
      }
      // Получаем список файлов
      current_dir = Storage.open(path);
      if(!current_dir) {
        Storage.mkdir(path);
        current_dir = Storage.open(path);
        if(!current_dir) {
          drawError("Cannot open path");
          return;
        }
      }
      while(file = current_dir.openNextFile()) {
        // Пропускаем папки
        if(file.isDirectory()) continue;
        // Читаем файл
        // Первая строчка - Имя
        (*file_to_list_function)(file, buff);
        files_list[offset] = (char *)malloc((strlen(file.name()) + 1) * sizeof(char));
        visible_list[offset] = (char *)malloc((strlen(buff) + 1) * sizeof(char));

        strcpy(files_list[offset], file.name());
        strcpy(visible_list[offset], buff);
        offset++;
      }
      update_list_flag = 0;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    touchCheckList(0, 32 -8, tft.width(), tft.height() - 72, visible_list, 15, &file_offset, &file_selected);
    drawList(0, 32 - 8, tft.width(), tft.height() - 72, visible_list, 15, &file_offset, &file_selected);
    drawButtonMatrix(0, 280, tft.width(), 40, buttons, buttons_count, 1);

    touchWaitPress();

    touchCheckList(0, 32 - 8, tft.width(), tft.height() - 72, visible_list, 15, &file_offset, &file_selected);
    button_pressed = touchCheckMatrix(0, 280, tft.width(), 40, buttons, buttons_count, 1);
    if(button_pressed != -1) {
      (*action_function)(button_pressed, files_list[file_selected]);
      update_list_flag = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      for(i = 0; i < PIM_FILES_COUNT_MAX; i++) {
        if(files_list[i]) {
          free(files_list[i]);
        }
        if(visible_list[i]) {
          free(visible_list[i]);
        }
      }
      free(files_list);
      free(visible_list);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

// Переименовывает файл в соответствии с содержимым
void pim_rename_file(char *path, char *old_filename, char *prefix) {
  fs::File file;
  char old_path_filename[80];
  char new_path_filename[80];
  char new_filename[80];
  char byte;
  int offset;

  sprintf(old_path_filename, "%s/%s", path, old_filename);
  file = Storage.open(old_path_filename);
  new_filename[0] = 0;
  offset = 0;
  while(file.available()) {
    byte = file.read();
    // Если уже хоть что-то в названии есть - достаточно
    if(offset > 0 && (byte == '\n' || byte == '\r')) {
      break;
    }
    // Только алфавитно-цифровые символы
    if(byte >= '0' && byte <= '9' || byte == ' ' || byte >= 'a' && byte <= 'z' || byte >= 'A' && byte <= 'Z') {
      // Пробел меняем на подчёркивание
      if(byte == ' ') byte = '_';
      new_filename[offset] = byte;
      offset++;
      new_filename[offset] = 0;
      if(offset > 20) break;
    }
    if(byte == '\n' || byte == '\r') break;
  }
  file.close();

  // Проверяем что такого названия нет
  if(strcmp("", new_filename) != 0) {
    sprintf(new_path_filename, "%s/%s%s", path, prefix ? prefix : "", new_filename);
    file = Storage.open(new_path_filename);
    if(file) {
      file.close();
      strcpy(new_filename, "");
    }
  }

  // Если название не сформировалось даём ему первый свободный цифровой номер
  if(strcmp("", new_filename) == 0) {
    for(offset = 1;; offset++) {
      sprintf(new_filename, "%d", offset);
      sprintf(new_path_filename, "%s/%s%s", path, prefix ? prefix : "", new_filename);
      file = Storage.open(new_path_filename);
      if(!file) {
        break;
      }
      file.close();
    }
  }

  // Переименовываем файл если есть новое название, и оно отличается
  if(strcmp("", new_filename) != 0 && strcmp(old_filename, new_filename)) {
    sprintf(new_path_filename, "%s/%s%s", path, prefix ? prefix : "", new_filename);
    // Проверяем что мы не затрём какой-нибудь файл
    file = Storage.open(new_path_filename);
    if(!file) {
      // И только тогда переименовываем
      Storage.rename(old_path_filename, new_path_filename);
    }
    else {
      file.close();
    }
  }
}

#define SCHEDULE_PATH "/Schedule"

void schedule(char mode, char *io_buff) {
  fs::File file;
  int wifi_status;
  char filename[80];
  char buff[80];
  char schedule_file_template[] = "8:00 \n9:00 \n10:00 \n11:00 \n12:00 \n13:00 \n14:00 \n15:00 \n16:00 \n17:00 \n18:00 \n";
  int day_of_week;
  int year;
  int month;
  int day;
  int prev_day;
  int cal_dow;
  int cal_day;
  int cal_row;
  int cal_col;
  int selected_day;
  int button_pressed;
  char redraw_flag;
  char prev_month_dow;
  char next_month_dow;
  char is_lap_year;
  char touch_check_flag;

  char *day_of_week_name[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
  };
  char *day_of_week_short[] = {
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
  };
  char *month_name[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
  };
  char *buttons[] = {
    "Prev", "Next",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000010, B10100010,
    B01000101, B01000010,
    B01000010, B10100010,
    B01000101, B01000010,
    B01000010, B10100010,
    B01000101, B01000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Schedule");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Schedule");

  redraw_flag = 1;
  set_local_time_from_unix_timestamp();

  day_of_week = (global_day_of_week + 7 - (global_day - 1) % 7) % 7;
  year = global_year;
  month = global_month;
  day = 1;

  while(1) {
    drawButtonMatrix(0, tft.height() - 32, tft.width(), 32, buttons, 2, 1);
    if(redraw_flag == 0) {
      touchWaitPress();
      redraw_flag = 1;
      touch_check_flag = 1;
    }
    if(redraw_flag || touch_check_flag) {
      drawAppTitle("Schedule");
      if(touch_check_flag == 0) {
        tft.fillRect(0, 16, tft.width(), tft.height() - 16 - 32 + 1, TFT_WHITE);
      }
      prev_day = day;

      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      sprintf(buff, "%s, %04d", month_name[month], year);
      tft.drawCentreString(buff, tft.width() / 2, 32, FONT_BIG);

      // Календарь на текущий месяц
      cal_day = 1;
      cal_dow = day_of_week;
      selected_day = -1;
      is_lap_year = 0;
      if(year % 4 == 0 && (year % 100 == 0 || year % 400 != 0)) {
        is_lap_year = 1;
      }

      prev_month_dow = 0;
      next_month_dow = 0;
      for(cal_row = 0; cal_row < 7; cal_row++) {
        for(cal_col = 0; cal_col < 7; cal_col++) {
          if(cal_row == 0) {
            strcpy(buff, day_of_week_short[cal_col]);
          }
          else {
            if(cal_row == 1 && cal_col < cal_dow) {
              prev_month_dow = cal_col;
              continue;
            }
            sprintf(buff, "%d", cal_day);
            next_month_dow = cal_col;
            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
              if(cal_day > 31) break;
            }
            if(month == 4 || month == 6 || month == 9 || month == 11) {
              if(cal_day > 30) break;
            }
            if(is_lap_year && month == 2 && cal_day > 29) break;
            if(!is_lap_year && month == 2 && cal_day > 28) break;
            cal_day++;
          }
          // Проверяем касание
          if(global_touch_present_flag) {
            if(global_touch_x >= cal_col * tft.width() / 7 && global_touch_x < (cal_col + 1) * tft.width() / 7
              &&
              global_touch_y >= 70 + cal_row * 32 - 8 && global_touch_y < 70 + (cal_row + 1) * 32 - 8
            ) {
              selected_day = (cal_day - 1);
            }
          }
          if((global_day + 1) == cal_day && month == global_month && year == global_year) {
            tft.fillRect(cal_col * tft.width() / 7, 70 + cal_row * 32 - 8, tft.width() / 7, 32, TFT_BLUE);
            tft.setTextColor(TFT_WHITE, TFT_BLUE);
          }
          else {
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
          }
          tft.drawCentreString(buff, (cal_col + 0.5) * tft.width() / 7, 70 + cal_row * 32, FONT_DEFAULT);
        }
      }
      redraw_flag = 0;
      touch_check_flag = 0;
    }
    
    if(selected_day != -1) {
      sprintf(filename, "%s/%04d-%02d-%02d", SCHEDULE_PATH, year, month, selected_day);
      sprintf(buff, "%04d-%02d-%02d", year, month, selected_day);
      // Если файла нет, то его нужно создать
      file = Storage.open(filename);
      if(file) {
        file.close();
      }
      else {
        file = Storage.open(filename, FILE_WRITE);
        file.print(schedule_file_template);
        file.close();
      }
      edit_file(buff, filename);
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, tft.height() - 32, tft.width(), 32, buttons, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        month--;
        if(month == 0) {
          year--;
          month = 12;
        }
        day = 1;
        if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
          day_of_week = (day_of_week + 35 - 31) % 7;
        }
        if(month == 4 || month == 6 || month == 9 || month == 11) {
          day_of_week = (day_of_week + 35 - 30) % 7;
        }
        if(month == 2) {
          if(is_lap_year) {
            day_of_week = (day_of_week + 35 - 29) % 7;
          }
          else {
            day_of_week = (day_of_week + 35 - 28) % 7;
          }
        }
      }
      else if(button_pressed == 1) {
        Serial.print("day_of_week="); Serial.println(day_of_week);
        Serial.print("is_lap_year="); Serial.println((int)is_lap_year);
        Serial.print("month="); Serial.println(month);
        if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
          day_of_week = (day_of_week + 31) % 7;
        }
        if(month == 4 || month == 6 || month == 9 || month == 11) {
          day_of_week = (day_of_week + 30) % 7;
        }
        if(month == 2) {
          if(is_lap_year) {
            day_of_week = (day_of_week + 29) % 7;
          }
          else {
            day_of_week = (day_of_week + 28) % 7;
          }
        }
        month++;
        if(month > 12) {
          month = 1;
          year++;
        }
      }
      redraw_flag = 1;
      continue;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void torch(char mode, char *io_buff) {
  int button_pressed;
  char *buttons[] = {
    "Off", "Red",
    "Green", "Yellow",
    "Blue", "Magenta",
    "Cyan", "White",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000111, B11100010,
    B01001000, B00010010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01001000, B00010010,
    B01000100, B00100010,
    B01000011, B11000010,
    B01000011, B11000010,
    B01000011, B11000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Torch");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Torch");

  drawButtonMatrix(0, 20, tft.width(), 300, buttons, 2, 4);
  
  while(1) {
    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 20, tft.width(), 300, buttons, 2, 4);
    if(button_pressed != -1) {
      drawButtonMatrix(0, 20, tft.width(), 300, buttons, 2, 4);
      digitalWrite(LED_RED, !(button_pressed & 0b0001));
      digitalWrite(LED_GREEN, !(button_pressed & 0b010));
      digitalWrite(LED_BLUE, !(button_pressed & 0b100));
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void security(char mode, char *io_buff) {
  int button_pressed;
  char correct_password[80] = "";
  char user_input[80] = "";
  char owner_info[80] = "";
  char password_correct_flag;
  char *buttons[] = {
    "Set owner info",
    "Change password",
    "Delete password",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000111, B11100010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01011111, B11111010,
    B01011111, B11111010,
    B01011110, B01111010,
    B01011110, B01111010,
    B01001111, B11110010,
    B01000111, B11100010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Security");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Security");
  
  while(1) {
    read_file_to_buff("/Settings/Owner", 79, owner_info);
    read_file_to_buff("/Settings/Password", 79, correct_password);

    tft.fillRect(0, 16, tft.width(), 100, TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Owner info:", 8, 20, FONT_DEFAULT);
    tft.drawString(owner_info, 8, 20 + 16, FONT_DEFAULT);
    
    if(strlen(correct_password) > 0) {
      tft.drawString("Password is set", 8, 20 + 16 + 16 + 8, FONT_DEFAULT);
    }
    else {
      tft.drawString("Password is not set", 8, 20 + 16 + 16 + 8, FONT_DEFAULT);
    }

    drawButtonMatrix(8, 100, tft.width() - 8 * 2, 100, buttons, 1, 3);

    touchWaitPress();
    button_pressed = touchCheckMatrix(8, 100, tft.width() - 8 * 2, 100, buttons, 1, 3);
    if(button_pressed != -1) {
      // Проверяем пароль если он задан
      password_correct_flag = 0;
      if(strlen(correct_password) > 0) {
        user_input[0] = 0;
        drawPrompt("Enter password", user_input);
        if(!strcmp(user_input, correct_password)) {
          password_correct_flag = 1;
        }
      }
      else {
        password_correct_flag = 1;
      }

      if(!password_correct_flag) {
        drawError("Password incorrect");
        tft.fillRect(0, 16, tft.width(), tft.height(), TFT_WHITE);
        continue;
      }

      // Смена информации о владельце
      if(button_pressed == 0) {
        if(drawPrompt("Enter owner info", owner_info) == 0) {
          write_file_from_buff("/Settings/Owner", owner_info);
        }
        tft.fillRect(0, 16, tft.width(), tft.height(), TFT_WHITE);
      }
      // Смена пароля
      else if(button_pressed == 1) {
        if(drawPrompt("Enter new password (digits only)", user_input) == 0) {
          write_file_from_buff("/Settings/Password", user_input);
        }
        tft.fillRect(0, 16, tft.width(), tft.height(), TFT_WHITE);
      }
      // Удаление пароля
      else if(button_pressed == 2) {
        Storage.remove("/Settings/Password");
        drawInfo("Password deleted");
        tft.fillRect(0, 16, tft.width(), tft.height(), TFT_WHITE);
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void counter(char mode, char *io_buff) {
  int button_pressed;
  long counter = 0;
  int prev_touch_millis = 0;
  char buff[80] = "";
  float bpm = 0;
  char password_correct_flag;
  char *buttons_inc[] = {
    "+",
    NULL
  };
  char *buttons_other[] = {
    "-",
    "reset",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00010010,
    B01000000, B00110010,
    B01000010, B00010010,
    B01000010, B00010010,
    B01001111, B10010010,
    B01000010, B00010010,
    B01000010, B00010010,
    B01000000, B00111010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Counter");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Counter");
  
  while(1) {
    tft.fillRect(0, 16, tft.width(), 30, TFT_WHITE);

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, " %ld ", counter);
    tft.drawCentreString(buff, tft.width() / 2, 32, FONT_BIGGER);

    sprintf(buff, "   BPM: %f   ", bpm);
    tft.drawCentreString(buff, tft.width() / 2, 210, FONT_DEFAULT);

    drawButtonMatrix(0, 100, tft.width(), 100, buttons_inc, 1, 1);
    drawButtonMatrix(0, tft.height() - 64, tft.width(), 64, buttons_other, 2, 1);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 100, tft.width(), 100, buttons_inc, 1, 1);
    if(button_pressed != -1) {
      // Защита от двойного срабатывания
      if(millis() - prev_touch_millis > 100) {
        counter++;
        if(prev_touch_millis) {
          bpm = (bpm + 60000 / ((float)(millis() - prev_touch_millis))) / 2;
        }
        prev_touch_millis = millis();
      }
    }
    button_pressed = touchCheckMatrix(0, tft.height() - 64, tft.width(), 64, buttons_other, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        counter--;
      }
      else if(button_pressed == 1) {
        counter = 0;
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void random_numbers(char mode, char *io_buff) {
  int button_pressed;
  int result = 0;
  int i;
  char buff[80];
  char *buttons[] = {
    "Coin", "1/4",
    "1/6", "1/8",
    "1/10", "1/12",
    "1/20", "1/100",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01011000, B00011010,
    B01011000, B00011010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01011000, B00011010,
    B01011000, B00011010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Random Numbers");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Random Numbers");

  while(1) {
    drawButtonMatrix(0, 52, tft.width(), tft.height() - 52, buttons, 2, 4);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 52, tft.width(), tft.height() - 52, buttons, 2, 4);
    if(button_pressed != -1) {
      tft.fillRect(0, 16, tft.width(), 34, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawCentreString("Spin...", tft.width() / 2, 24, FONT_BIG);
      delay(500);
      if(button_pressed == 0) {
        result = random(0, 2);
      }
      else if(button_pressed == 1) {
        result = random(0, 4) + 1;
      }
      else if(button_pressed == 2) {
        result = random(0, 6) + 1;
      }
      else if(button_pressed == 3) {
        result = random(0, 8) + 1;
      }
      else if(button_pressed == 4) {
        result = random(0, 10) + 1;
      }
      else if(button_pressed == 5) {
        result = random(0, 12) + 1;
      }
      else if(button_pressed == 6) {
        result = random(0, 20) + 1;
      }
      else if(button_pressed == 7) {
        result = random(0, 100) + 1;
      }
      sprintf(buff, "%ld", result);
      if(button_pressed == 0) {
        if(result == 0) {
          strcpy(buff, "Head");
        }
        else if(result == 1) {
          strcpy(buff, "Tails");
        }
        else {
          strcpy(buff, "Edge");
        }
      }

      tft.fillRect(0, 16, tft.width(), 34, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawCentreString(buff, tft.width() / 2, 24, FONT_BIG);
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void brightness_app(char mode, char *io_buff) {
  int button_pressed;
  int result = 0;
  int i;
  char buff[80];
  char *buttons[] = {
    "Off", "Min",
    "5 %", "10 %",
    "20 %", "50 %",
    "75 %", "Max",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01111110, B10000010,
    B01111101, B01000010,
    B01111110, B10000010,
    B01111101, B01000010,
    B01111110, B10000010,
    B01111101, B01000010,
    B01111110, B10000010,
    B01111101, B01000010,
    B01111110, B10000010,
    B01111101, B01000010,
    B01111110, B10000010,
    B01111101, B01000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Brightness");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Brightness");

  while(1) {
    sprintf(buff, "   %d   ", get_brightness());
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString(buff, tft.width() / 2, 20, FONT_BIG);

    drawButtonMatrix(0, 50, tft.width(), tft.height() - 50, buttons, 2, 4);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 50, tft.width(), tft.height() - 50, buttons, 2, 4);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        set_brightness(0);
      }
      else if(button_pressed == 1) {
        set_brightness(1);
      }
      else if(button_pressed == 2) {
        set_brightness(255 * 0.05);
      }
      else if(button_pressed == 3) {
        set_brightness(255 * 0.1);
      }
      else if(button_pressed == 4) {
        set_brightness(255 * 0.2);
      }
      else if(button_pressed == 5) {
        set_brightness(255 * 0.5);
      }
      else if(button_pressed == 6) {
        set_brightness(255 * 0.75);
      }
      else if(button_pressed == 7) {
        set_brightness(255);
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      save_brightness();
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void timer(char mode, char *io_buff) {
  int button_pressed;
  int i;
  int preset_minutes = 1;
  int preset_seconds = 0;
  long start_millis;
  long time_remains;
  char timer_run = 0;
  char auto_restart = 0;
  char redraw_flag = 0;
  int minutes = preset_minutes;
  int seconds = preset_seconds;
  char buff[80];
  char *buttons_presets[] = {
    "1 minute", "2 minutes",
    "5 minutes", "10 minutes",
    NULL
  };
  char *buttons_up[] = {
    "+", "+",
    NULL
  };
  char *buttons_down[] = {
    "-", "-",
    NULL
  };
  char *buttons_start_stop[] = {
    "Start", "Stop",
    NULL
  };
  char *buttons_auto_restart[] = {
    "Auto restart", NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00111111, B11111100,
    B00111111, B11111100,
    B00010000, B00001000,
    B00001000, B00010000,
    B00000111, B11100000,
    B00000011, B11000000,
    B00000001, B10000000,
    B00000001, B10000000,
    B00000010, B01000000,
    B00000100, B00100000,
    B00001001, B10010000,
    B00010011, B11001000,
    B00111111, B11111100,
    B00111111, B11111100,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Timer");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Timer");

  while(1) {
    if(timer_run) {
      // Оставшееся время в секундах
      time_remains = preset_minutes * 60 + preset_seconds - (millis() - start_millis) / 1000;
      if(time_remains <= 0) {
        if(auto_restart == 0) {
          // Хочу видеть ноль секунд когда время вышло
          sprintf(buff, "%02d", 0);
          tft.drawCentreString(buff, 3 * tft.width() / 4, 56, FONT_BIG);

          drawInfo("Time's up!");
          tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
          minutes = preset_minutes;
          seconds = preset_seconds;
          timer_run = 0;
          redraw_flag = 1;
          continue;
        }
        else {
          start_millis = millis();
          tone(BUZZER_PIN, 1000, 100);
          time_remains = preset_minutes * 60 + preset_seconds - (millis() - start_millis) / 1000;
        }
      }
      minutes = time_remains / 60;
      seconds = time_remains % 60;
    }
    else {
      minutes = preset_minutes;
      seconds = preset_seconds;
    }

    // Рисуем время
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "%02d", minutes);
    tft.drawCentreString(buff, 1 * tft.width() / 4, 56, FONT_BIG);
    sprintf(buff, "%02d", seconds);
    tft.drawCentreString(buff, 3 * tft.width() / 4, 56, FONT_BIG);

    // Если таймер запущен и касаний нет - остальное не рисуем
    if(timer_run && touchCheckNowait() == 0 && redraw_flag == 0) {
      continue;
    }

    drawButtonMatrix(0, 20, tft.width(), 32, buttons_up, 2, 1);
    drawButtonMatrix(0, 84, tft.width(), 32, buttons_down, 2, 1);
    drawButtonMatrix(0, 140, tft.width(), 32, buttons_start_stop, 2, 1);

    drawButtonMatrix(0, 190, tft.width() / 2, 32, buttons_auto_restart, 1, 1);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    if(auto_restart) {
      tft.drawCentreString(" on ", 3 * tft.width() / 4, 196, FONT_DEFAULT);
    }
    else {
      tft.drawCentreString(" off ", 3 * tft.width() / 4, 196, FONT_DEFAULT);
    }
    drawButtonMatrix(0, 240, tft.width(), tft.height() - 240, buttons_presets, 2, 2);

    if(redraw_flag) {
      redraw_flag = 0;
    }

    if(!timer_run) {
      touchWaitPress();
    }

    button_pressed = touchCheckMatrix(0, 20, tft.width(), 32, buttons_up, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        if(preset_minutes < 99) {
          preset_minutes++;
        }
        else {
          preset_minutes = 0;
        }
      }
      else if(button_pressed == 1) {
        if(preset_seconds < 59) {
          preset_seconds++;
        }
        else {
          preset_seconds = 0;
        }
      }
      redraw_flag = 1;
    }
    button_pressed = touchCheckMatrix(0, 84, tft.width(), 32, buttons_down, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        if(preset_minutes > 0) {
          preset_minutes--;
        }
        else {
          preset_minutes = 99;
        }
      }
      else if(button_pressed == 1) {
        if(preset_seconds > 0) {
          preset_seconds--;
        }
        else {
          preset_seconds = 59;
        }
      }
      redraw_flag = 1;
    }
    button_pressed = touchCheckMatrix(0, 140, tft.width(), 32, buttons_start_stop, 2, 1);
    if(button_pressed != -1) {
      // Старт
      if(button_pressed == 0) {
        if(preset_minutes > 0 || preset_seconds > 0) {
          start_millis = millis();
          timer_run = 1;
        }
      }
      // Cтоп
      else if(button_pressed == 1) {
        timer_run = 0;
      }
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, 190, tft.width() / 2, 32, buttons_auto_restart, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        if(auto_restart) {
          auto_restart = 0;
        }
        else {
          auto_restart = 1;
        }
      }
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, 240, tft.width(), tft.height() - 240, buttons_presets, 2, 2);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        preset_minutes = 1;
        preset_seconds = 0;
        minutes = preset_minutes;
        seconds = preset_seconds;
        start_millis = millis();
      }
      else if(button_pressed == 1) {
        preset_minutes = 2;
        preset_seconds = 0;
        minutes = preset_minutes;
        seconds = preset_seconds;
        start_millis = millis();
      }
      else if(button_pressed == 2) {
        preset_minutes = 5;
        preset_seconds = 0;
        minutes = preset_minutes;
        seconds = preset_seconds;
        start_millis = millis();
      }
      else if(button_pressed == 3) {
        preset_minutes = 10;
        preset_seconds = 0;
        minutes = preset_minutes;
        seconds = preset_seconds;
        start_millis = millis();
      }
      redraw_flag = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }

    touchWaitRelease();
  }
}

#define STOPWATCH_MAX_LAPS 100

void stopwatch_app(char mode, char *io_buff) {
  int button_pressed;
  int i;
  long millis_from_start = 0;
  long millis_prev = 0;
  long millis_value = 0;
  long millis_from_lap = 0;
  char stopwatch_run = 0;
  char redraw_flag = 0;
  char buff[80];
  char *buttons_control[] = {
    "Start", "Lap", "Stop", "Reset",
    NULL
  };
  char *buttons_lap_control[] = {
    "Delete", "Delete all",
    NULL
  };
  char **stopwatch_laps;
  int current_lap = 0;
  int lap_list_offset = 0;
  int lap_list_selected = 0;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10010010,
    B01000111, B11100010,
    B01001000, B00010010,
    B01001001, B00010010,
    B01001001, B00010010,
    B01001001, B11010010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01000111, B11100010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  // 100 laps
  stopwatch_laps = (char **)malloc(STOPWATCH_MAX_LAPS * sizeof(char *));
  for(i = 0; i < STOPWATCH_MAX_LAPS; i++) {
    stopwatch_laps[i] = NULL;
  }

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Stopwatch");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Stopwatch");

  while(1) {
    if(stopwatch_run) {
      millis_value = millis();
      millis_from_start += millis_value - millis_prev;
      millis_from_lap += millis_value - millis_prev;
      millis_prev = millis_value;
    }
    sprintf(buff, "%02d:%02d:%02d.%02d",
        millis_from_start / 36000000,
        (millis_from_start / 60000) % 60,
        (millis_from_start / 1000) % 60,
        (millis_from_start / 10) % 100);

    // Рисуем время
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString(buff, tft.width() / 2, 20, FONT_BIG);

    // Если таймер запущен и касаний нет - остальное не рисуем
    if(stopwatch_run && touchCheckNowait() == 0 && redraw_flag == 0) {
      continue;
    }

    drawButtonMatrix(0, 52, tft.width(), 64, buttons_control, 4, 1);
    drawButtonMatrix(0, 288, tft.width(), 32, buttons_lap_control, 2, 1);

    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    if(redraw_flag) {
      drawList(8, 120, tft.width() - 8 * 2, 160, stopwatch_laps, 10, &lap_list_offset,  &lap_list_selected);
      redraw_flag = 0;
    }

    if(!stopwatch_run) {
      touchWaitPress();
    }

    touchCheckList(8, 120, tft.width() - 8 * 2, 160, stopwatch_laps, 10, &lap_list_offset,  &lap_list_selected);
    drawList(8, 120, tft.width() - 8 * 2, 160, stopwatch_laps, 10, &lap_list_offset,  &lap_list_selected);

    button_pressed = touchCheckMatrix(0, 52, tft.width(), 64, buttons_control, 4, 1);
    if(button_pressed != -1) {
      // Start
      if(button_pressed == 0) {
        stopwatch_run = 1;
        millis_prev = millis();
      }
      // Lap
      else if(button_pressed == 1) {
        if(stopwatch_run && current_lap < 99) {
          sprintf(buff, "%02d:%02d:%02d.%02d",
            millis_from_lap / 36000000,
            (millis_from_lap / 60000) % 60,
            (millis_from_lap / 1000) % 60,
            (millis_from_lap / 10) % 100);
          stopwatch_laps[current_lap] = (char*)malloc(25 * sizeof(char));
          sprintf(stopwatch_laps[current_lap], "Lap %d - %s", current_lap + 1, buff);
          millis_from_lap = 0;
          current_lap++;
        }
      }
      // Stop
      else if(button_pressed == 2) {
        stopwatch_run = 0;
      }
      // Reset
      else if(button_pressed == 3) {
        current_lap = 0;
        lap_list_offset = 0;
        lap_list_selected = 0;
        stopwatch_run = 0;
        millis_from_start = 0;
        millis_from_lap = 0;
        for(i = 0; i < 100; i++) {
          if(stopwatch_laps[i] != NULL) {
            free(stopwatch_laps[i]);
          }
          stopwatch_laps[i] = NULL;
        }
      }
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, 288, tft.width(), 32, buttons_lap_control, 2, 1);
    if(button_pressed != -1) {
      // Delete one
      if(button_pressed == 0) {
        if(current_lap > 0) {
          if(stopwatch_laps[lap_list_selected]) {
            free(stopwatch_laps[lap_list_selected]);
          }
          for(i = lap_list_selected; i < STOPWATCH_MAX_LAPS; i++) {
            if(i < STOPWATCH_MAX_LAPS - 1) {
              stopwatch_laps[i] = stopwatch_laps[i + 1];
            }
            else {
              stopwatch_laps[i] = NULL;
            }
          }
          current_lap--;
          lap_list_offset = 0;
          lap_list_selected = 0;
        }
      }
      // Delete all laps
      else if(button_pressed == 1) {
        current_lap = 0;
        lap_list_offset = 0;
        lap_list_selected = 0;
        millis_from_lap = millis_from_start;
        for(i = 0; i < STOPWATCH_MAX_LAPS; i++) {
          if(stopwatch_laps[i] != NULL) {
            free(stopwatch_laps[i]);
          }
          stopwatch_laps[i] = NULL;
        }
      }
      redraw_flag = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      for(i = 0; i < STOPWATCH_MAX_LAPS; i++) {
        if(stopwatch_laps[i] != NULL) {
          free(stopwatch_laps[i]);
        }
        stopwatch_laps[i] = NULL;
      }
      free(stopwatch_laps);
      touchExitActionReset();
      return;
    }

    touchWaitRelease();
  }
}

void breathe(char mode, char *io_buff) {
  int button_pressed;
  int i;
  long time_remains;
  char breathe_run = 0;
  char redraw_flag = 0;
  char step = 0;
  long step_start_millis = millis();
  long current_millis = 0;
  long total_millis = 0;
  long this_step_seconds; 
  int inhale = 4;
  int inhale_hold = 4;
  int exhale = 4;
  int exhale_hold = 4;
  char stage[80];
  char buff[80];
  char *buttons_controls[] = {
    "Start", "Pause", "Reset",
    NULL
  };
  char *buttons_presets[] = {
    "4-4-4-4", "4-0-4-0",
    "4-7-8-0",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00110010,
    B01000000, B01001010,
    B01000000, B00001010,
    B01011111, B11110010,
    B01000000, B00000010,
    B01001111, B11110010,
    B01000000, B00001010,
    B01000000, B00110010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Breathe");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Breathe");

  redraw_flag = 1;
  while(1) {
    if(breathe_run) {
      total_millis += millis() - current_millis;
      current_millis = millis();
      this_step_seconds = (millis() - step_start_millis) / 1000 + 1;
      if(step == 0) {
        sprintf(stage, " Inhale ", this_step_seconds);
        strcpy(buff, " ");
        for(i = 1; i < inhale; i++) {
          if(i < this_step_seconds) strcat(buff, "* ");
          else strcat(buff, "_ ");
        }
        if(this_step_seconds > inhale) {
          tone(BUZZER_PIN, 1000, 100);
          tft.fillRect(0, 16, tft.width(), 132, TFT_WHITE);
          step_start_millis = millis();
          step++;
        }
      }
      else if(step == 1) {
        sprintf(stage, "   Hold   ", this_step_seconds);
        strcpy(buff, " ");
        for(i = 1; i < inhale_hold; i++) {
          if(i < this_step_seconds) strcat(buff, "* ");
          else strcat(buff, "_ ");
        }
        if(this_step_seconds > inhale_hold) {
          tone(BUZZER_PIN, 1000, 100);
          tft.fillRect(0, 16, tft.width(), 132, TFT_WHITE);
          step_start_millis = millis();
          step++;
        }
      }
      else if(step == 2) {
        sprintf(stage, " Exhale ", this_step_seconds);
        strcpy(buff, " ");
        for(i = 1; i < exhale; i++) {
          if(i < this_step_seconds) strcat(buff, "* ");
          else strcat(buff, "_ ");
        }

        if(this_step_seconds > exhale) {
          tone(BUZZER_PIN, 1000, 100);
          tft.fillRect(0, 16, tft.width(), 132, TFT_WHITE);
          step_start_millis = millis();
          step++;
        }
      }
      else if(step == 3) {
        sprintf(stage, "   Hold   ", this_step_seconds);
        strcpy(buff, " ");
        for(i = 1; i < exhale_hold; i++) {
          if(i < this_step_seconds) strcat(buff, "* ");
          else strcat(buff, "_ ");
        }

        if(this_step_seconds > exhale_hold) {
          tone(BUZZER_PIN, 1000, 100);
          tft.fillRect(0, 16, tft.width(), 132, TFT_WHITE);
          step_start_millis = millis();
          step = 0;
        }
      }

      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawCentreString(stage, tft.width() / 2, 46, FONT_BIG);
      tft.drawCentreString(buff, tft.width() / 2, 80, FONT_BIG);

      sprintf(buff, "Total time: %02d:%02d", total_millis / 60000, (total_millis / 1000) % 60);
      tft.drawCentreString(buff, tft.width() / 2, 20, FONT_DEFAULT);
    }

    // Если таймер запущен и касаний нет - остальное не рисуем
    if(breathe_run && touchCheckNowait() == 0 && redraw_flag == 0) {
      continue;
    }

    drawButtonMatrix(0, 150, tft.width(), 64, buttons_controls, 3, 1);
    drawButtonMatrix(0, 280, tft.width(), tft.height() - 280, buttons_presets, 3, 1);

    if(redraw_flag) {
      redraw_flag = 0;
    }

    if(!breathe_run) {
      touchWaitPress();
    }

    button_pressed = touchCheckMatrix(0, 150, tft.width(), 64, buttons_controls, 3, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        current_millis = millis();
        step = 0;
        step_start_millis = millis();
        breathe_run = 1;
      }
      else if(button_pressed == 1) {
        breathe_run = 0;
      }
      else if(button_pressed == 2) {
        breathe_run = 0;
        step = 0;
        total_millis = 0;
        tft.fillRect(0, 16, tft.width(), 132, TFT_WHITE);
      }
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, 280, tft.width(), tft.height() - 280, buttons_presets, 3, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        inhale = 4;
        inhale_hold = 4;
        exhale = 4;
        exhale_hold = 4;
      }
      else if(button_pressed == 1) {
        inhale = 4;
        inhale_hold = 0;
        exhale = 4;
        exhale_hold = 0;
      }
      else if(button_pressed == 2) {
        inhale = 4;
        inhale_hold = 7;
        exhale = 8;
        exhale_hold = 0;
        
      }
      redraw_flag = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }

    touchWaitRelease();
  }
}

#define LIFE_CELL_PIXELS 4
#define LIFE_FIELD_WIDTH_CELLS (tft.width() / LIFE_CELL_PIXELS)
#define LIFE_FIELD_HEIGHT_CELLS ((tft.height() - 16 - 40) / LIFE_CELL_PIXELS)

void life(char mode, char *io_buff) {
  char life_run = 0;
  char *field = NULL;
  char *field_next = NULL;
  int button_pressed;
  int x, y;
  int touch_x, touch_y;
  int cell_color;
  int near_count;
  char current_cell;
  long prev_millis;
  TS_Point p;
  char *buttons[] = {
    "Start", "Step", "Stop", "Rnd", "Clr",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00110010,
    B01000000, B00110010,
    B01000000, B00000010,
    B01001100, B00110010,
    B01001100, B00110010,
    B01000000, B00000010,
    B01000001, B10110010,
    B01000001, B10110010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  field = (char *)malloc(LIFE_FIELD_WIDTH_CELLS * LIFE_FIELD_HEIGHT_CELLS / 8 * sizeof(char));
  field_next = (char *)malloc(LIFE_FIELD_WIDTH_CELLS * LIFE_FIELD_HEIGHT_CELLS / 8 * sizeof(char));

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Life");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Life");
  
  while(1) {
    if(life_run) {
      if(millis() - prev_millis > 200) {
        for(y = 0; y < LIFE_FIELD_HEIGHT_CELLS; y++) {
          for(x = 0; x < LIFE_FIELD_WIDTH_CELLS; x++) {
            near_count = 0;
            current_cell = life_get_cell(x, y, field);
            if(life_get_cell(x - 1, y - 1, field)) near_count++;
            if(life_get_cell(x - 1, y, field)) near_count++;
            if(life_get_cell(x - 1, y + 1, field)) near_count++;
            if(life_get_cell(x, y - 1, field)) near_count++;
            if(life_get_cell(x, y + 1, field)) near_count++;
            if(life_get_cell(x + 1, y - 1, field)) near_count++;
            if(life_get_cell(x + 1, y    , field)) near_count++;
            if(life_get_cell(x + 1, y + 1, field)) near_count++;
            if(current_cell) {
              if(near_count < 2 || near_count > 3) life_set_cell(x, y, field_next, 0);
              else life_set_cell(x, y, field_next, 1);
            }
            else {
              if(near_count == 3) life_set_cell(x, y, field_next, 1);
              else life_set_cell(x, y, field_next, 0);
            }
          }
        }
        // Копируем обратно
        memcpy(field, field_next, LIFE_FIELD_WIDTH_CELLS * LIFE_FIELD_HEIGHT_CELLS / 8 * sizeof(char));
        prev_millis = millis();
      }
      if(life_run == 1) {
        life_run = 0;
      }
    }

    // Нарисовать поле
    for(y = 0; y < LIFE_FIELD_HEIGHT_CELLS; y++) {
      for(x = 0; x < LIFE_FIELD_WIDTH_CELLS; x++) {
        cell_color = TFT_WHITE;
        if(life_get_cell(x, y, field)) {
          cell_color = TFT_BLUE;
        }
        tft.fillRect(
          x * LIFE_CELL_PIXELS,
          16 + y * LIFE_CELL_PIXELS + 1,
          LIFE_CELL_PIXELS - (LIFE_CELL_PIXELS > 2 ? 1 : 0),
          LIFE_CELL_PIXELS - (LIFE_CELL_PIXELS > 2 ? 1 : 0),
          cell_color
        );
      }
    }

    // Если запущено и касаний нет - обновляем
    if(life_run && touchCheckNowait() == 0) {
      continue;
    }

    drawButtonMatrix(0, 280, tft.width(), 40, buttons, 5, 1);

    touchWaitPress();
    // Смотрим, нет ли попадания в поле
    p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);
    if(touch_y >= 17 && touch_y < 280) {
      x = touch_x / LIFE_CELL_PIXELS;
      y = (touch_y - 17) / LIFE_CELL_PIXELS;
      if(life_get_cell(x, y, field)) {
        life_set_cell(x, y, field, 0);
      }
      else {
        life_set_cell(x, y, field, 1);
      }
    }

    button_pressed = touchCheckMatrix(0, 280, tft.width(), 40, buttons, 5, 1);
    if(button_pressed != -1) {
      // Start
      if(button_pressed == 0) {
        life_run = 2;
      }
      // Step
      else if(button_pressed == 1) {
        life_run = 1;
        prev_millis = 0;
      }
      // Stop
      else if(button_pressed == 2) {
        life_run = 0;
      }
      // Rnd
      else if(button_pressed == 3) {
        for(y = 0; y < LIFE_FIELD_HEIGHT_CELLS; y++) {
          for(x = 0; x < LIFE_FIELD_WIDTH_CELLS; x++) {
            life_set_cell(x, y, field, random(0, 2));
          }
        }
      }
      // Clr
      else if(button_pressed == 4) {
        for(y = 0; y < LIFE_FIELD_HEIGHT_CELLS; y++) {
          for(x = 0; x < LIFE_FIELD_WIDTH_CELLS; x++) {
            life_set_cell(x, y, field, 0);
          }
        }
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      free(field);
      free(field_next);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

char life_get_cell(int x, int y, char *field) {
  int byte;
  int offset;
  while(x < 0) x += LIFE_FIELD_WIDTH_CELLS;
  while(y < 0) y += LIFE_FIELD_HEIGHT_CELLS;
  while(x >= LIFE_FIELD_WIDTH_CELLS) x %= LIFE_FIELD_WIDTH_CELLS;
  while(y >= LIFE_FIELD_HEIGHT_CELLS) y %= LIFE_FIELD_HEIGHT_CELLS;
  //if(x < 0 || y < 0 || x >= LIFE_FIELD_WIDTH_CELLS || y >= LIFE_FIELD_HEIGHT_CELLS) return 0;

  byte = (x + y * LIFE_FIELD_WIDTH_CELLS) / 8;
  offset = (x + y * LIFE_FIELD_WIDTH_CELLS) % 8;
  if(field[byte] & (1 << offset)) return 1;
  return 0;
}

void life_set_cell(int x, int y, char *field, char value) {
  int byte;
  int offset;
  while(x < 0) x += LIFE_FIELD_WIDTH_CELLS;
  while(y < 0) y += LIFE_FIELD_HEIGHT_CELLS;
  while(x >= LIFE_FIELD_WIDTH_CELLS) x %= LIFE_FIELD_WIDTH_CELLS;
  while(y >= LIFE_FIELD_HEIGHT_CELLS) y %= LIFE_FIELD_HEIGHT_CELLS;
  //if(x < 0 || y < 0 || x >= LIFE_FIELD_WIDTH_CELLS || y >= LIFE_FIELD_HEIGHT_CELLS) return;
  byte = (x + y * LIFE_FIELD_WIDTH_CELLS) / 8;
  offset = (x + y * LIFE_FIELD_WIDTH_CELLS) % 8;
  if(value) field[byte] |= (1 << offset);
  else field[byte] &= ~(1 << offset);
}

#define SNAKE_CELL_PIXELS 8
#define SNAKE_FIELD_WIDTH_CELLS (tft.width() / SNAKE_CELL_PIXELS)
#define SNAKE_FIELD_HEIGHT_CELLS ((tft.height() - 32) / SNAKE_CELL_PIXELS)
#define SNAKE_MOVE_INTERVAL_MILLIS 200

void snake(char mode, char *io_buff) {
  char *field = NULL;
  char *body = NULL;
  int x, y;
  int touch_x, touch_y;
  int cell_color;
  long prev_millis = 0;
  TS_Point p;
  char direction = 'u';
  char next_direction = direction;
  int head_x = SNAKE_FIELD_WIDTH_CELLS / 2;
  int head_y = SNAKE_FIELD_HEIGHT_CELLS / 2;
  int bait_x;
  int bait_y;
  int segment_x;
  int segment_y;
  int length = 3;
  int record = length;
  int i;
  char lose_flag = 0;
  char restart_flag = 1;
  char bait_flag = 1;
  char buff[80];
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000111, B11010010,
    B01000100, B00000010,
    B01000100, B00000010,
    B01000100, B00000010,
    B01000111, B11110010,
    B01000000, B00010010,
    B01011111, B11010010,
    B01000000, B01010010,
    B01000000, B01110010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  field = (char *)malloc(SNAKE_FIELD_WIDTH_CELLS * SNAKE_FIELD_HEIGHT_CELLS / 8 * sizeof(char));
  body = (char *)malloc(SNAKE_FIELD_WIDTH_CELLS * SNAKE_FIELD_HEIGHT_CELLS);
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Snake");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Snake");
  
  tft.drawLine(0, 16, tft.width(), tft.height(), TFT_BLACK);
  tft.drawLine(tft.width(), 16, 0, tft.height(), TFT_BLACK);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawCentreString("UP", tft.width() / 2, tft.height() / 4, FONT_DEFAULT);
  tft.drawCentreString("DOWN", tft.width() / 2, 3 * tft.height() / 4, FONT_DEFAULT);
  tft.drawCentreString("LEFT", tft.width() / 4, tft.height() / 2, FONT_DEFAULT);
  tft.drawCentreString("RIGHT", 3 * tft.width() / 4, tft.height() / 2, FONT_DEFAULT);
  touchWaitPress();
  touchWaitRelease();

  restart_flag = 1;
  while(1) {
    if(restart_flag) {
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      lose_flag = 0;
      bait_flag = 1;
      direction = 'u';
      length = 3;
      head_x = SNAKE_FIELD_WIDTH_CELLS / 2;
      head_y = SNAKE_FIELD_HEIGHT_CELLS / 2;
      memset(field, 0, SNAKE_FIELD_WIDTH_CELLS * SNAKE_FIELD_HEIGHT_CELLS / 8);
      for(x = 0; x < SNAKE_FIELD_WIDTH_CELLS; x++) {
        snake_set_cell(x, 0, field, 1);
        snake_set_cell(x, SNAKE_FIELD_HEIGHT_CELLS - 1, field, 1);
      }
      for(y = 0; y < SNAKE_FIELD_WIDTH_CELLS; y++) {
        snake_set_cell(0, y, field, 1);
        snake_set_cell(SNAKE_FIELD_WIDTH_CELLS - 1, y, field, 1);
      }

      memset(body, 'u', SNAKE_FIELD_WIDTH_CELLS * SNAKE_FIELD_HEIGHT_CELLS);
      restart_flag = 0;
    }

    // Игоровой цикл
    if(millis() - prev_millis > SNAKE_MOVE_INTERVAL_MILLIS) {
      direction = next_direction;
      // Перемещаем голову
      if(direction == 'u') {
        head_y--;
      }
      else if(direction == 'd') {
        head_y++;
      }
      else if(direction == 'l') {
        head_x--;
      }
      else if(direction == 'r') {
        head_x++;
      }

      // Если уже что-то есть в этом месте, это либо тело, либо граница, либо еда
      if(head_x == bait_x && head_y == bait_y) {
        length++;
        if(length > record) record = length;
        //tone(BUZZER_PIN, 3000, 100);
        bait_flag = 1;
      }
      else if(snake_get_cell(head_x, head_y, field)) {
        lose_flag = 1;
      }
      else {
        snake_set_cell(head_x, head_y, field, 1);
      }
      // Сдвигаем массив
      for(i = SNAKE_FIELD_WIDTH_CELLS * SNAKE_FIELD_HEIGHT_CELLS - 1; i > 0; i--) {
        body[i] = body[i - 1];
      }
      body[0] = direction;

      // Ищем хвост, стираем его
      segment_x = head_x;
      segment_y = head_y;
      for(i = 0; i < SNAKE_FIELD_WIDTH_CELLS * SNAKE_FIELD_HEIGHT_CELLS; i++) {
        if(body[i] == 'u') segment_y++;
        if(body[i] == 'd') segment_y--;
        if(body[i] == 'l') segment_x++;
        if(body[i] == 'r') segment_x--;
        if(i == length - 1) {
          snake_set_cell(segment_x, segment_y, field, 0);
        }
      }

      // Кладём еду
      while(bait_flag) {
        bait_x = random(1, SNAKE_FIELD_WIDTH_CELLS - 2);
        bait_y = random(1, SNAKE_FIELD_HEIGHT_CELLS - 2);
        if(snake_get_cell(bait_x, bait_y, field) == 0) bait_flag = 0;
      }
      snake_set_cell(bait_x, bait_y, field, 1);


      prev_millis = millis();
    }

    // Нарисовать поле
    for(y = 0; y < SNAKE_FIELD_HEIGHT_CELLS; y++) {
      for(x = 0; x < SNAKE_FIELD_WIDTH_CELLS; x++) {
        cell_color = TFT_WHITE;
        if(snake_get_cell(x, y, field)) {
          cell_color = TFT_DARKGREEN;
        }
        if(x == 0 || y == 0 || x == SNAKE_FIELD_WIDTH_CELLS - 1 || y == SNAKE_FIELD_HEIGHT_CELLS - 1) {
          cell_color = TFT_DARKGREY;
        }
        if(x == bait_x && y == bait_y) {
          cell_color = TFT_RED;
        }
        tft.fillRect(
          x * SNAKE_CELL_PIXELS + 1,
          32 + y * SNAKE_CELL_PIXELS + 1,
          SNAKE_CELL_PIXELS - (SNAKE_CELL_PIXELS > 2 ? 2 : 0),
          SNAKE_CELL_PIXELS - (SNAKE_CELL_PIXELS > 2 ? 2 : 0),
          cell_color
        );
      }
    }
    // Счёт и рекорд
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "Length: %d", length);
    tft.drawString(buff, 1, 16, FONT_DEFAULT);
    sprintf(buff, "Record: %d", record);
    tft.drawString(buff, tft.width() / 2, 16, FONT_DEFAULT);

    // Проигрыш
    if(lose_flag) {
      drawInfo("You lose");
      restart_flag = 1;
      lose_flag = 0;
    }
    // Если запущено и касаний нет - обновляем
    if(touchCheckNowait() == 0) {
      continue;
    }

//    drawButtonMatrix(0, 280, tft.width(), 40, buttons, 5, 1);

    touchWaitPress();
    // Смотрим, нет ли попадания в поле
    p = touchscreen.getPoint();
    // Относительные единицы!
    touch_x = touchMapX(p.x, p.y) * 100 / tft.width();
    touch_y = touchMapY(p.x, p.y) * 100 / tft.height();
    if(touch_x > touch_y) {
      if(touch_x > 100 - touch_y) {
        if(direction != 'l') next_direction = 'r';
      }
      else {
        if(direction != 'd') next_direction = 'u';
      }
    }
    else {
      if(touch_y > 100 - touch_x) {
        if(direction != 'u') next_direction = 'd';
      }
      else {
        if(direction != 'r') next_direction = 'l';
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      free(field);
      free(body);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

char snake_get_cell(int x, int y, char *field) {
  int byte;
  int offset;
  while(x < 0) x += SNAKE_FIELD_WIDTH_CELLS;
  while(y < 0) y += SNAKE_FIELD_HEIGHT_CELLS;
  while(x >= SNAKE_FIELD_WIDTH_CELLS) x %= SNAKE_FIELD_WIDTH_CELLS;
  while(y >= SNAKE_FIELD_HEIGHT_CELLS) y %= SNAKE_FIELD_HEIGHT_CELLS;
  //if(x < 0 || y < 0 || x >= SNAKE_FIELD_WIDTH_CELLS || y >= SNAKE_FIELD_HEIGHT_CELLS) return 0;

  byte = (x + y * SNAKE_FIELD_WIDTH_CELLS) / 8;
  offset = (x + y * SNAKE_FIELD_WIDTH_CELLS) % 8;
  if(field[byte] & (1 << offset)) return 1;
  return 0;
}

void snake_set_cell(int x, int y, char *field, char value) {
  int byte;
  int offset;
  while(x < 0) x += SNAKE_FIELD_WIDTH_CELLS;
  while(y < 0) y += SNAKE_FIELD_HEIGHT_CELLS;
  while(x >= SNAKE_FIELD_WIDTH_CELLS) x %= SNAKE_FIELD_WIDTH_CELLS;
  while(y >= SNAKE_FIELD_HEIGHT_CELLS) y %= SNAKE_FIELD_HEIGHT_CELLS;
  //if(x < 0 || y < 0 || x >= SNAKE_FIELD_WIDTH_CELLS || y >= SNAKE_FIELD_HEIGHT_CELLS) return;
  byte = (x + y * SNAKE_FIELD_WIDTH_CELLS) / 8;
  offset = (x + y * SNAKE_FIELD_WIDTH_CELLS) % 8;
  if(value) field[byte] |= (1 << offset);
  else field[byte] &= ~(1 << offset);
}


void turkish_scarf(char mode, char *io_buff) {
  char field[60];
  char deck[52];
  char card;
  char suit;
  char *suits[] = {"H", "D", "S", "C", NULL};
  char *cards[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", NULL};
  int column1;
  int column2;
  char card1;
  char card2;
  int x, y;
  int touch_x, touch_y;
  int cell_color;
  long prev_millis = 0;
  TS_Point p;
  char direction = 'u';
  int moves;
  int i;
  int j;
  char lose_flag = 0;
  char restart_flag = 1;
  char cards_present_flag;
  char buff[80];
  int suit_color;
  int tries;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01001110, B01110010,
    B01011111, B11111010,
    B01011111, B11111010,
    B01011111, B11111010,
    B01001111, B11110010,
    B01000111, B11100010,
    B01000011, B11000010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  char suit_hearts[] = {
      8, 8,
      B01100110,
      B11111111,
      B11111111,
      B11111111,
      B11111111,
      B01111110,
      B00111100,
      B00011000
  };
  char suit_diamonds[] = {
      8, 8,
      B00011000,
      B00111100,
      B01111110,
      B11111111,
      B11111111,
      B01111110,
      B00111100,
      B00011000
  };
  char suit_spades[] = {
      8, 8,
      B00011000,
      B00111100,
      B01111110,
      B11111111,
      B11111111,
      B01011010,
      B00011000,
      B00111100
  };
  char suit_clubs[] = {
      8, 8,
      B00011000,
      B00111100,
      B00011000,
      B11011011,
      B11111111,
      B11011011,
      B00011000,
      B00111100
  };
  char *suit_images[] = {suit_hearts, suit_diamonds, suit_spades, suit_clubs};

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Turkish Scarf");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Turkish Scarf");
  
  restart_flag = 1;
  while(1) {
    while(restart_flag) {
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_DARKGREEN);
      memset(field, 0xFF, 60);
      // Инициализируем колоду
      for(i = 0; i < 52; i++) {
        deck[i] = i;
      }
      // Перемешиваем колоду
      for(i = 0; i < 52; i++) {
        card1 = i;
        card2 = random(0, 52);
        card = deck[card2];
        deck[card2] = deck[card1];
        deck[card1] = card;
      }

      // Разбираем колоду
      for(i = 0; i < 52; i++) {
        // Снимаем карту
        card1 = deck[i];
        deck[i] = 0xFF;
        if(card1 == 0xFF) continue;
        // Находим карту такого же достоинства
        for(j = i + 1; j < 52; j++) {
          if(card1 % 13 == deck[j] % 13) {
            card2 = deck[j];
            deck[j] = 0xFF;
            break;
          }
        }
        // Выбираем колонку для карты, пытаемся положить туда карту
        while(card1 != 0xFF) {
          y = 0;
          column1 = random(0, 10);
          do {
            if(column1 + y  * 10 >= 52) break;
            if(field[column1 + y  * 10] == 0xFF) {
              field[column1 + y  * 10] = card1;
              card1 = 0xFF;
            }
            y++;
          } while(card1 != 0xFF);
        }
        // 100 попыток положить вторую карту
        // иначе возможна ситуция зависания, когда последние две карты оказываются в одной колонке
        tries = 100;
        while(card2 != 0xFF) {
          y = 0;
          column2 = random(0, 10);
          // В ту же нельзя
          if(column1 == column2) continue;
          do {
            if(column2 + y  * 10 >= 52) break;
            if(field[column2 + y  * 10] == 0xFF) {
              field[column2 + y  * 10] = card2;
              card2 = 0xFF;
            }
            y++;
          } while(card2 != 0xFF);
          tries--;
          if(tries == 0) break;
        }
        // Не удалось разложить поле, начинаем сначала
        if(tries == 0) break;
      }
      column1 = -1;
      column2 = -1;
      // Не удалось разложить поле, начинаем сначала
      if(tries > 0) {
        restart_flag = 0;
      }
    }

    // Нарисовать поле
    for(y = 0; y < 6; y++) {
      for(x = 0; x < 10; x++) {
        if(x + y * 10 >= 52) break;
        card = field[x + y * 10];
        if(card == 0xFF) {
          tft.fillRect(x * tft.width() / 10, 48 + y * 40, tft.width() / 10, 40, TFT_DARKGREEN);
        }
        else {
          suit = card / 13;
          card = card % 13;
          sprintf(buff, "%s%s", cards[card], suits[suit]);

          suit_color = TFT_BLACK;
          if(suit <= 1) {
            suit_color = TFT_RED;
          }
          tft.setTextColor(suit_color, TFT_WHITE);
          tft.fillRoundRect(x * tft.width() / 10 + 1, 48 + y * 40 + 1, tft.width() / 10 - 2, 40 - 2, 3, TFT_WHITE);
          tft.drawRoundRect(x * tft.width() / 10 + 1, 48 + y * 40 + 1, tft.width() / 10 - 2, 40 - 2, 3, TFT_BLACK);
          tft.drawCentreString(cards[card], x * tft.width() / 10 + tft.width() / 20, 48 + y * 40 + 4, FONT_DEFAULT);
          image_from_bits(x * tft.width() / 10 + tft.width() / 20 - 4, 48 + y * 40 + 20 + 2, suit_images[suit], suit_color, TFT_WHITE);
        }
      }
    }

    // Количество ходов
    moves = 0;
    cards_present_flag = 0;
    for(i = 0; i < 9; i++) {
      // Берём одну карту
      y = 5;
      card1 = 0xFF;
      while(field[i + y * 10] == 0xFF) {
        y--;
        if(y < 0) break;

      }
      if(y >= 0) card1 = field[i + y * 10] % 13;
      if(card1 == 0xFF) continue;
      cards_present_flag = 1;

      for(j = i + 1; j < 10; j++) {
        // Берём другую карту
        y = 5;
        card2 = 0xFF;
        while(field[j + y * 10] == 0xFF) {
          y--;
          if(y < 0) break;
        }
        if(y >= 0) card2 = field[j + y * 10] % 13;
        if(card2 != 0xFF) cards_present_flag = 1;
        if(card1 == card2) {
          moves++;
          break;
        }
      }
    }
    tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
    sprintf(buff, "Moves: %d", moves);
    tft.drawString(buff, 1, 16, FONT_DEFAULT);

    if(cards_present_flag == 0) {
      drawInfo("You won!");
      restart_flag = 1;
      continue;
    }
    else if(moves == 0) {
      drawInfo("No moves left");
      restart_flag = 1;
      continue;
    }
    touchWaitPress();

    // Смотрим, какая колонка выбрана
    p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);

    column2 = column1;
    column1 = touch_x / (tft.width() / 10);

    tft.fillRect(0, tft.height() - 16, tft.width(), 16, TFT_DARKGREEN);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
    tft.drawCentreString("^", column1 * tft.width() / 10 + tft.width() / 20, tft.height() - 16, FONT_DEFAULT);

    Serial.print("column1="); Serial.println(column1);
    Serial.print("column2="); Serial.println(column2);

    if(column2 != -1 && column1 != column2) {
      // Берём одну карту
      y = 5;
      card1 = 0xFF;
      while(field[column1 + y * 10] == 0xFF) {
        y--;
        if(y < 0) break;

      }
      if(y >= 0) card1 = field[column1 + y * 10] % 13;

      // Берём вторую карту
      y = 5;
      card2 = 0xFF;
      while(field[column2 + y * 10] == 0xFF) {
        y--;
        if(y < 0) break;
      }
      if(y >= 0) card2 = field[column2 + y * 10] % 13;

      Serial.print("card1="); Serial.println((int)card1);
      Serial.print("card2="); Serial.println((int)card2);

      // Если они одинаковые - убираем
      if(card1 != 0xFF && card1 == card2) {
        // Убираем одну карту
        y = 5;
        while(field[column1 + y * 10] == 0xFF) {
          y--;
          if(y < 0) break;
        }
        if(y >= 0) field[column1 + y * 10] = 0xFF;

        // Убираем другую карту
        y = 5;
        while(field[column2 + y * 10] == 0xFF) {
          y--;
          if(y < 0) break;
        }
        if(y >= 0) field[column2 + y * 10] = 0xFF;

        column1 = -1;
        column2 = -1;
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

#define STAR_COUNT 40

void screensaver(char mode, char *io_buff) {
  int stars_x[STAR_COUNT];
  int stars_y[STAR_COUNT];
  int i;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000100, B00000010,
    B01000000, B00100010,
    B01000000, B01110010,
    B01000000, B00100010,
    B01000000, B00000010,
    B01000010, B00000010,
    B01000000, B00000010,
    B01001000, B00010010,
    B01000000, B00000010,
    B01000010, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Screensaver");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  tft.fillScreen(TFT_BLACK);
  for(i = 0; i != STAR_COUNT; i++) {
    stars_x[i] = random(0, tft.width());
    stars_y[i] = random(0, tft.height());
    tft.drawPixel(stars_x[i], stars_y[i], TFT_WHITE);
  }

  while(1) {
    for(i = 0; i != STAR_COUNT; i++) {
      tft.drawPixel(stars_x[i] + 1, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] + 1, TFT_WHITE);
      tft.drawPixel(stars_x[i] - 1, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] - 1, TFT_WHITE);
      delay(200);
      tft.drawPixel(stars_x[i] + 2, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] + 2, TFT_WHITE);
      tft.drawPixel(stars_x[i] - 2, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] - 2, TFT_WHITE);
      delay(200);
      tft.drawPixel(stars_x[i] + 2, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] + 2, TFT_BLACK);
      tft.drawPixel(stars_x[i] - 2, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] - 2, TFT_BLACK);
      delay(200);
      tft.drawPixel(stars_x[i] + 1, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] + 1, TFT_BLACK);
      tft.drawPixel(stars_x[i] - 1, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] - 1, TFT_BLACK);
      delay(200);
      tft.drawPixel(stars_x[i], stars_y[i], TFT_BLACK);

      stars_x[i] = random(0, tft.width());
      stars_y[i] = random(0, tft.height());

      tft.drawPixel(stars_x[i], stars_y[i], TFT_WHITE);
      delay(200);
      tft.drawPixel(stars_x[i] + 1, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] + 1, TFT_WHITE);
      tft.drawPixel(stars_x[i] - 1, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] - 1, TFT_WHITE);
      delay(200);
      tft.drawPixel(stars_x[i] + 2, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] + 2, TFT_WHITE);
      tft.drawPixel(stars_x[i] - 2, stars_y[i], TFT_WHITE);
      tft.drawPixel(stars_x[i], stars_y[i] - 2, TFT_WHITE);
      delay(200);
      tft.drawPixel(stars_x[i] + 2, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] + 2, TFT_BLACK);
      tft.drawPixel(stars_x[i] - 2, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] - 2, TFT_BLACK);
      delay(200);
      tft.drawPixel(stars_x[i] + 1, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] + 1, TFT_BLACK);
      tft.drawPixel(stars_x[i] - 1, stars_y[i], TFT_BLACK);
      tft.drawPixel(stars_x[i], stars_y[i] - 1, TFT_BLACK);
      delay(200);
      if(touchCheckNowait()) {
        touchWaitRelease();
        return;
      }
    }
  }
}

#ifdef IS_WIFI_ENABLED

#define WIFI_MAX_NETWORKS 128

void wifi(char mode, char *io_buff) {
  int wifi_status;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000111, B11100010,
    B01011000, B00011010,
    B01000000, B00000010,
    B01000111, B11100010,
    B01001000, B00010010,
    B01000000, B00000010,
    B01000011, B11000010,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Wi-Fi");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  WiFi.waitForConnectResult(10);

  while(1) {
    wifi_status = WiFi.status();
    if(wifi_status == WL_CONNECTED) {
      wifi_network_info();
    }
    else {
      wifi_select_network();
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void wifi_select_network() {
  char **networks;
  int button_pressed;
  int networks_found;
  int networks_unique;
  int network_index;
  int network_offset = 0;
  int network_selected = 0;
  int i;
  int wifi_status;
  long millis_connecting_start;
  char network_listed;
  char rescan_flag;
  char password[80];
  char *buttons[] = {
    "Connect", "Rescan",
    NULL
  };

  networks = (char**)malloc(WIFI_MAX_NETWORKS * sizeof(char *));
  for(network_index = 0; network_index < WIFI_MAX_NETWORKS; network_index++) {
    networks[network_index] = NULL;
  }

  clearScreen();
  drawAppTitle("Wi-Fi");

  //WiFi.setAutoReconnect(false);
  WiFi.disconnect();
  WiFi.STA.begin();

  rescan_flag = 1;
  while(1) {
    tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
    if(rescan_flag) {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("Scanning...      ", 0, 16, FONT_DEFAULT);
      for(network_index = 0; network_index < WIFI_MAX_NETWORKS; network_index++) {
        if(networks[network_index]) {
          free(networks[network_index]);
        }
        networks[network_index] = NULL;
      }

      networks_unique = 0;
      networks_found = WiFi.scanNetworks();
      for (i = 0; i < networks_found; i++) {
        network_listed = 0;
        // Ищем сети с таким же названием
        for(network_index = 0; network_index < networks_unique; network_index++) {
          if(!strcmp(networks[network_index], WiFi.SSID(i).c_str())) {
            network_listed = 1;
          }
        }
        // Если сеть ещё не фигурировала - добавялем в список
        if(network_listed == 0) {
          //Serial.println(WiFi.SSID(i).c_str());
          networks[networks_unique] = (char *)malloc(80 * sizeof(char));
          strcpy(networks[networks_unique], WiFi.SSID(i).c_str());
          networks_unique++;
        }
      }
      rescan_flag = 0;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Select network:", 0, 16, FONT_DEFAULT);

    touchCheckList(8, 32, tft.width() - 8 * 2, tft.height() - 72, networks, 15, &network_offset, &network_selected);
    drawList(8, 32, tft.width() - 8 * 2, tft.height() - 72, networks, 15, &network_offset, &network_selected);

    drawButtonMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 2, 1);
    
    touchWaitPress();
    touchCheckList(8, 32, tft.width() - 8 * 2, tft.height() - 32 - 40, networks, 15, &network_offset, &network_selected);

    button_pressed = touchCheckMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        strcpy(password, "");
        read_key_value_from_file("/Settings/Wifi", networks[network_selected], password);
        drawPrompt("Enter password", password);
        WiFi.begin(networks[network_selected], password);
        millis_connecting_start = millis();
        do {
          wifi_status = WiFi.status();
          if(millis() - millis_connecting_start >= 30000) break;
        } while (wifi_status == WL_DISCONNECTED || wifi_status == WL_IDLE_STATUS);
        
        if(wifi_status == WL_CONNECTED) {
          WiFi.setAutoReconnect(true);
          write_key_value_to_file("/Settings/Wifi", networks[network_selected], password);
          drawInfo("Connected");
          return;
        }
        else if(wifi_status == WL_NO_SSID_AVAIL) {
          drawError("SSID unavailable");
        }
        else if(wifi_status == WL_CONNECT_FAILED) {
          drawError("Connect failed (wrong password?)");
        }
        else if(wifi_status == WL_DISCONNECTED) {
          drawError("Wi-Fi disconnected");
        }
        else if(wifi_status == WL_IDLE_STATUS) {
          drawError("Wi-Fi in idle status");
        }
        else if(wifi_status == WL_STOPPED) {
          drawError("Wi-Fi stopped");
        }
        else {
          drawError("Unknown status");
        }
      }
      else if(button_pressed == 1) {
        rescan_flag = 1;
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      // Флаг не сбрасываем, так как не основное приложение
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

void wifi_network_info() {
  int wifi_status;
  int screen_offset;
  int button_pressed;
  int prev_update_millis = 0;
  char buff[80];
  char buff2[80];
  IPAddress ip;

  char *buttons[] = {
    "Ping", "DNS", "Disconnect",
  };

  clearScreen();
  drawAppTitle("Wi-Fi");

  while(1) {
    if(millis() - prev_update_millis > 1000) {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      screen_offset = 20;
      sprintf(buff, "SSID: %s  ", WiFi.SSID());
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      sprintf(buff, "BSSID: %02x:%02x:%02x:%02x:%02x:%02x  ", WiFi.BSSID()[0], WiFi.BSSID()[1], WiFi.BSSID()[2], WiFi.BSSID()[3], WiFi.BSSID()[4], WiFi.BSSID()[5]);
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      sprintf(buff, "RSSI: %d (%d%%)  ", WiFi.RSSI(), constrain(2 * (WiFi.RSSI() + 100), 0, 100));
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      sprintf(buff, "My MAC: %02x:%02x:%02x:%02x:%02x:%02x  ", WiFi.macAddress()[0], WiFi.macAddress()[1], WiFi.macAddress()[2], WiFi.macAddress()[3], WiFi.macAddress()[4], WiFi.macAddress()[5]);
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      sprintf(buff, "IP: %s  ", WiFi.localIP().toString());
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      sprintf(buff, "Netmask: %s  ", WiFi.subnetMask().toString());
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      // Какой-то глюк с этим адресом
      //sprintf(buff, "Broadcast: %s", WiFi.broadcastIP().toString());
      //tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      //screen_offset += 16;
      sprintf(buff, "Gateway: %s  ", WiFi.gatewayIP().toString());
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;
      sprintf(buff, "DNS: %s  ", WiFi.dnsIP().toString());
      tft.drawString(buff, 8, screen_offset, FONT_DEFAULT);
      screen_offset += 16;

      drawButtonMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 3, 1);

      prev_update_millis = millis();
    }
    if(!touchCheckNowait()) continue;
    touchWaitPress();

    button_pressed = touchCheckMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 3, 1);
    if(button_pressed != -1) {
      // Ping
      if(button_pressed == 0) {
        strcpy(buff, "");
        drawPrompt("IP to ping", buff);
        if(strcmp(buff, "")) {
          if(Ping.ping(buff, 3)) {
            sprintf(buff2, "Average of 3 pings is %d ms", Ping.averageTime());
          }
          else {
            sprintf(buff2, "Error");
          }
          drawInfo(buff2);
        }
      }
      // Resolve host
      else if(button_pressed == 1) {
        strcpy(buff, "");
        drawPrompt("Host to resolve", buff);
        if(strcmp(buff, "")) {
          WiFi.hostByName(buff, ip);
          drawInfo((char *)ip.toString().c_str());
        }
      }
      // Disconnect
      else if(button_pressed == 2) {
        WiFi.setAutoReconnect(false);
        WiFi.disconnect();
        return;
      }
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      // Флаг не сбрасываем, так как не основное приложение
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

void get_current_timestamp_wifi() {
  HTTPClient http;
  int httpResponseCode;
  char buff[80];
  http.begin("http://109.230.144.68/cyd/unixtime.php");
  httpResponseCode = http.GET();
  if(httpResponseCode > 0) {
    strcpy(buff, http.getString().c_str());
    sscanf(buff, "%lu", &global_unixtime_retrieved);
    global_unixtime_retrieved_millis = millis();
  }
  http.end();
}

#define GOPHER_BYTES_MAX 32768

void gopher(char mode, char *io_buff) {
  int wifi_status;
  char buff[160];
  char address[80];
  char path[80];
  char address_to_go[160];
  char *page = NULL;
  char reload_page;
  char ask_address;
  char type;
  int page_offset;
  int button_pressed;
  char *buttons[] = {
    "PgUp", "Home", "URL", "PgDn",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000011, B11000010,
    B01000100, B00100010,
    B01001000, B00010010,
    B01001000, B00000010,
    B01001000, B01110010,
    B01001000, B00010010,
    B01000100, B00100010,
    B01000011, B11000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Gopher Browser");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  page = (char *)malloc(GOPHER_BYTES_MAX * sizeof(char));
  clearScreen();
  drawAppTitle("Gopher Browser");

  wifi_status = WiFi.status();
  if(wifi_status != WL_CONNECTED && global_unixtime_retrieved == 0) {
    drawError("Wi-Fi connection required");
    return;
  }
  reload_page = 1;
  ask_address = 0;
  
  strcpy(address, "gopher.floodgap.com");
  //strcpy(address, "gopher.floodgap.com:70/0gopher/proxy");
  while(1) {
    // Спрашиваем адрес
    if(ask_address) {
      drawPrompt("Enter address", address);
      if(strlen(address) > 0) {
        reload_page = 1;
      }
      ask_address = 0;
    }
    if(reload_page) {
      if(gopher_get_page(address, page, &type)) {
        page_offset = 0;
      }
      else {
        drawError("Error fetching data");
      }
      reload_page = 0;
    }

    tft.fillRect(0, 16, tft.width(), 16 - 1, TFT_LIGHTGREY);
    tft.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
    tft.drawString(address, 1, 20, FONT_MONOSPACE);

    // Выводим всё
    tft.fillRect(0, 32, tft.width(), tft.height() - 32, TFT_WHITE);
    gopher_show_page(page, &page_offset, type, 0, address_to_go);

    drawButtonMatrix(0, tft.height() - 32, tft.width(), 32, buttons, 4, 1);
    
    touchWaitPress();
    gopher_show_page(page, &page_offset, type, 1, address_to_go);
    if(strlen(address_to_go) > 0) {
      strcpy(address, address_to_go);
      reload_page = 1;
    }

    button_pressed = touchCheckMatrix(0, tft.height() - 32, tft.width(), 32, buttons, 4, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        page_offset -= 31;
        if(page_offset < 0) page_offset = 0;
      }
      if(button_pressed == 1) {
        strcpy(address, "gopher.floodgap.com");
        reload_page = 1;
      }
      if(button_pressed == 2) {
        ask_address = 1;
      }
      if(button_pressed == 3) {
        page_offset += 31;
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      free(page);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

int gopher_get_page(char *address, char *buff_output, char *type) {
  char buff[80];
  char server[80];
  char path[160];
  int port = 70;
  char server_flag;
  char port_flag;
  char path_flag;
  char type_flag;
  char finish_flag;
  WiFiClient client;
  String line;
  long query_start_millis;
  int address_offset;
  int str_offset;

  server_flag = 1;
  port_flag = 0;
  path_flag = 0;
  type_flag = 0;
  str_offset = 0;
  finish_flag = 0;
  strcpy(server, "");
  strcpy(path, "");
  strcpy(buff_output, "");
  *type = 0;

  for(address_offset = 0; address_offset < strlen(address); address_offset++) {
    if(server_flag) {
      if(address[address_offset] == ':') {
        server_flag = 0;
        port_flag = 1;
        str_offset = 0;
      }
      else if(address[address_offset] == '/') {
        server_flag = 0;
        type_flag = 1;
        str_offset = 0;
      }
      else {
        server[str_offset] = address[address_offset];
        str_offset++;
        server[str_offset] = 0;
      }
    }
    else if(port_flag) {
      if(address[address_offset] == '/') {
        port_flag = 0;
        type_flag = 1;
        str_offset = 0;
        sscanf(buff, "%d", &port);
      }
      buff[str_offset] = address[address_offset];
      str_offset++;
      buff[str_offset] = 0;
    }
    else if(type_flag) {
      *type = address[address_offset];
      type_flag = 0;
      path_flag = 1;
      str_offset = 0;
    }
    else if(path_flag) {

      path[str_offset] = address[address_offset];
      str_offset++;
      path[str_offset] = 0;
    }
  }

  if(*type == 0) {
    *type = '1';
  }
  if(port == 0) {
    port = 70;
  }
  if(strlen(path) == 0) {
    strcpy(path, "/");
  }
  if(strlen(server) == 0) {
    return 1;
  }

  if (client.connect(server, port)) {
    client.println(path);
    query_start_millis = millis();

    while (!client.available()) {
      if(millis() - query_start_millis > 10000) return 0;
    }

    strcpy(buff_output, "");
    while (client.available()) {
      line = client.readStringUntil('\r');
      Serial.println(line);
      if(strlen(buff_output) + strlen(line.c_str()) >= GOPHER_BYTES_MAX) {
        break;
      }
      strcat(buff_output, line.c_str());
      if(!client.available()) delay(1000);
    }
    client.stop();
    return 1;
  }
  return 0;
}

void gopher_show_page(char *page, int *offset_lines, char address_type, char get_touch_address, char *address_to_go) {
  int current_line = 0;
  int screen_offset = 0;
  long page_byte_offset;
  int buff_offset;
  char buff_line[200];
  char buff[80];
  char text[80];
  char server[80];
  char port[80];
  char path[80];
  char query[80];

  char line_type;
  char reset_line_type;
  char line_skip_to_end;
  char new_line_flag;
  char line_shown;
  int line_offset;
  int touch_line = -1;
  TS_Point p;
  int touch_x, touch_y;

  page_byte_offset = 0;
  buff_offset = 0;
  line_type = 0;
  line_skip_to_end = 0;
  new_line_flag = 1;
  strcpy(address_to_go, "");

  if(touchCheckNowait()) {
    p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);
    if(touch_y >= 32 && touch_y < tft.height() - 32) {
      touch_line = (touch_y - 32) / 8;
    }
  }
  while(screen_offset < 31) {
    strcpy(buff_line, "");
    // Прочитать строку гофера в буфер
    for(buff_offset = 0; buff_offset < 199; buff_offset++) {
      if(page[page_byte_offset] == '\n') {
        page_byte_offset++;
        break;
      }
      buff_line[buff_offset] = page[page_byte_offset];
      buff_line[buff_offset+1] = 0;
      page_byte_offset++;
      if(page[page_byte_offset] == 0) break;
    }
    // Парсить её
    if(address_type == '0') {
      strcpy(text, buff_line);
      line_type = 'i';
      strcpy(path, "");
      strcpy(server, "");
      strcpy(port, "");
    }
    else {
      gopher_parse_line(buff_line, &line_type, text, path, server, port);
    }

    // Выводим текст построчно
    line_offset = 0;
    line_shown = 0;
    while(line_shown == 0) {
      for(buff_offset = 0; buff_offset < 40; line_offset++) {
        if(text[line_offset] == 0) {
          buff[buff_offset] = 0;
          line_shown = 1;
          break;
        }
        buff[buff_offset] = text[line_offset];
        buff_offset++;
        buff[buff_offset] = 0;
      }

      if(current_line < *offset_lines) {
        current_line++;
        continue;
      }

      if(line_type == 'i') {
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
      }
      else if(line_type == '0' || line_type == '1') {
        if(get_touch_address && touch_line == screen_offset) {
          tft.setTextColor(TFT_WHITE, TFT_BLUE);
          sprintf(address_to_go, "%s:%s/%c%s", server, port, line_type, path);
        }
        else {
          tft.setTextColor(TFT_BLUE, TFT_WHITE);
        }
      }
      else if(line_type == '7') {
        if(get_touch_address && touch_line == screen_offset) {
          tft.setTextColor(TFT_WHITE, TFT_BLUE);
          strcpy(query, "");
          drawPrompt("Query", query);
          sprintf(address_to_go, "%s:%s/%c%s\t%s", server, port, line_type, path, query);
        }
        else {
          tft.setTextColor(TFT_BLUE, TFT_WHITE);
        }
      }
      else if(line_type == '3') {
        tft.setTextColor(TFT_RED, TFT_WHITE);
      }
      else {
        tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
      }
      tft.drawString(buff, 1, 32 + screen_offset * 8, FONT_MONOSPACE);
      screen_offset++;
      current_line++;
    }
    if(page[page_byte_offset] == 0) break;
  }
}

void gopher_parse_line(char *line, char *line_type, char *line_text, char *path, char *server, char *port) {
  int line_offset;
  int text_offset;
  char line_type_flag;
  char line_flag;
  char path_flag;
  char server_flag;
  char port_flag;
  line_type_flag = 1;
  line_flag = 0;
  path_flag = 0;
  server_flag = 0;
  port_flag = 0;
  line_offset = 0;
  text_offset = 0;
  while(line[line_offset] != 0) {
    if(line_type_flag) {
      line_type_flag = 0;
      line_flag = 1;
      *line_type = line[line_offset];
    }
    else if(line_flag) {
      if(line[line_offset] == '\t') {
        line_flag = 0;
        path_flag = 1;
        text_offset = 0;
      }
      else {
        line_text[text_offset] = line[line_offset];
        text_offset++;
        line_text[text_offset] = 0;
      }
    }
    else if(path_flag) {
      if(line[line_offset] == '\t') {
        path_flag = 0;
        server_flag = 1;
        text_offset = 0;
      }
      else {
        path[text_offset] = line[line_offset];
        text_offset++;
        path[text_offset] = 0;
      }
    }
    else if(server_flag) {
      if(line[line_offset] == '\t') {
        server_flag = 0;
        port_flag = 1;
        text_offset = 0;
      }
      else {
        server[text_offset] = line[line_offset];
        text_offset++;
        server[text_offset] = 0;
      }
    }
    else if(port_flag) {
      if(line[line_offset] == '\t') {
        server_flag = 0;
        port_flag = 0;
        text_offset = 0;
      }
      else {
        port[text_offset] = line[line_offset];
        text_offset++;
        port[text_offset] = 0;
      }
    }
    line_offset++;
  }
}

#define WEATHER_AUTO_UPDATE_INTERVAL 300000

void weather(char mode, char *io_buff) {
  HTTPClient http;
  int httpResponseCode;
  int button_pressed;
  int wifi_status;
  long prev_update_data_millis;
  int i;
  char buff[80];
  char weather[80];
  char temp[80];
  char wind[80];
  char temp_flag;
  char wind_flag;
  char weather_flag;
  char from_offset = 0;
  char update_flag;
  char *buttons[] = {
    "Update now",
    "Set Latitude",
    "Set Longitude",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000011, B10000010,
    B01000100, B01000010,
    B01001000, B11110010,
    B01001101, B00001010,
    B01010010, B00001010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01001111, B11110010,
    B01000000, B00000010,
    B01010101, B01000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Weather");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Weather");

  wifi_status = WiFi.status();
  if(wifi_status != WL_CONNECTED && global_unixtime_retrieved == 0) {
    drawError("Wi-Fi connection required");
    return;
  }

  update_flag = 1;
  prev_update_data_millis = millis();
  while(1) {
    if(update_flag) {
      sprintf(buff, "http://109.230.144.68/cyd/weather.php?lat=%f&lon=%f", global_lat, global_lon);
      http.begin(buff);
      httpResponseCode = http.GET();
      if(httpResponseCode > 0) {
        prev_update_data_millis = millis();
        strcpy(buff, http.getString().c_str());
        temp_flag = 1;
        wind_flag = 0;
        weather_flag = 0;
        strcpy(temp, "");
        strcpy(wind, "");
        strcpy(weather, "");
        
        for(i = 0; i < strlen(buff); i++) {
          if(buff[i] == ',') {
            if(temp_flag) {
              temp_flag = 0;
              wind_flag = 1;
              // Начало строки с температурой, без градусов цельсия
              memcpy(temp, buff, i - 2);
              temp[i - 2] = 0;
              from_offset = i + 1;
            }
            else if(wind_flag) {
              wind_flag = 0;
              weather_flag = 1;
              memcpy(wind, buff + from_offset + 1, i - from_offset - 1);
              wind[i - from_offset - 1] = 0;
              strcpy(weather, buff + i + 2);
            }
          }
        }
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.drawCentreString(temp, tft.width() / 2, 35, FONT_BIGGER);
        //tft.drawString("C", tft.width() / 2 + tft.textWidth(temp, FONT_BIGGER) / 2 + 8, 35, FONT_BIG);

        tft.drawCentreString(wind, tft.width() / 2, 100, FONT_BIG);
        tft.drawCentreString(weather, tft.width() / 2, 150, FONT_DEFAULT);
        update_flag = 0;
      }
    }

    drawButtonMatrix(0, tft.height() - 96, tft.width() / 2, 96, buttons, 1, 3);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "%f", global_lat);
    tft.drawCentreString(buff, 3 * tft.width() / 4, tft.height() - 64 + 8, FONT_DEFAULT);
    sprintf(buff, "%f", global_lon);
    tft.drawCentreString(buff, 3 * tft.width() / 4, tft.height() - 32 + 8, FONT_DEFAULT);

    while(!touchCheckNowait()) {
      tft.setTextColor(TFT_LIGHTGREY, TFT_WHITE);
      sprintf(buff, "  Next update in %d min %d sec  ",
        (prev_update_data_millis + WEATHER_AUTO_UPDATE_INTERVAL - millis()) / 60000,
        ((prev_update_data_millis + WEATHER_AUTO_UPDATE_INTERVAL - millis()) / 1000) % 60
      );
      tft.drawCentreString(buff, tft.width() / 2, tft.height() - 128, FONT_DEFAULT);

      if(millis() - prev_update_data_millis > WEATHER_AUTO_UPDATE_INTERVAL) {
        update_flag = 1;
        break;
      }
    }
    // Если нет касания и нужно обновить - обновляем
    if(touchCheckNowait() == 0 && update_flag) {
      continue;
    }
    touchWaitPress();

    button_pressed = touchCheckMatrix(0, tft.height() - 96, tft.width() / 2, 96, buttons, 1, 3);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        update_flag = 1;
      }
      else if(button_pressed == 1) {
        sprintf(buff, "%f", global_lat);
        drawPrompt("Enter latitude", buff);
        if(strlen(buff) > 0) {
          sscanf(buff, "%f", &global_lat);
          sprintf(buff, "%f %f", global_lat, global_lon);
          write_file_from_buff("/Settings/Coordinates", buff);
        }
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      }
      else if(button_pressed == 2) {
        sprintf(buff, "%f", global_lon);
        drawPrompt("Enter longitude", buff);
        if(strlen(buff) > 0) {
          sscanf(buff, "%f", &global_lon);
          sprintf(buff, "%f %f", global_lat, global_lon);
          write_file_from_buff("/Settings/Coordinates", buff);
        }
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      // Флаг не сбрасываем, так как не основное приложение
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

#define CHAT_AUTO_UPDATE_INTERVAL 30000
#define CHAT_NICKNAME_FILE "/Settings/Nickname"

void chat(char mode, char *io_buff) {
  HTTPClient http;
  int httpResponseCode;
  int button_pressed;
  int wifi_status;
  long prev_update_data_millis;
  int i;
  int screen_line;
  int messages_offset;
  int buff_offset;
  char buff[80];
  char nickname[80];
  char *query = NULL;
  char message[80];
  char *messages = NULL;
  char *prev_messages = NULL;
  char update_flag;
  char *buttons[] = {
    "Send message",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00111111, B11111100,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01001101, B10110010,
    B01001101, B10110010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B00111111, B01111100,
    B00000001, B01000000,
    B00000011, B10000000,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Chat");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Chat");

  wifi_status = WiFi.status();
  if(wifi_status != WL_CONNECTED && global_unixtime_retrieved == 0) {
    drawError("Wi-Fi connection required");
    return;
  }

  strcpy(message, "");
  strcpy(nickname, "");
  read_file_to_buff(CHAT_NICKNAME_FILE, 79, nickname);
  while(1) {
    drawPrompt("Your nickname (up to 10 chars)", nickname);
    if(strlen(nickname) == 0) {
      drawError("Nickname cannot be empty");
      continue;
    }
    if(strlen(nickname) > 10) {
      drawError("Nickname too long");
      continue;
    }
    break;
  }
  write_file_from_buff(CHAT_NICKNAME_FILE, nickname);
  tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
  
  messages = (char*)malloc(2048 * sizeof(char));
  prev_messages = (char*)malloc(2048 * sizeof(char));
  query = (char*)malloc(300 * sizeof(char));

  messages[0] = 0;
  prev_messages[0] = 0;

  update_flag = 1;
  while(1) {
    if(update_flag) {
      http.begin("http://109.230.144.68/cyd/chat_data.txt");
      httpResponseCode = http.GET();
      if(httpResponseCode > 0) {
        strcpy(messages, http.getString().c_str());
        // Если сообщения изменились - бибикнуть
        if(strlen(prev_messages) > 0 && strcmp(messages, prev_messages)) {
          tone(BUZZER_PIN, 1000, 100);
        }
        strcpy(prev_messages, messages);
        screen_line = 0;
        buff_offset = 0;
        memset(buff, ' ', 40);
        buff[40] = 0;
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        //tft.fillRect(0, 16, tft.width(), tft.height() - 16 - 32 - 8, TFT_WHITE);
        for(messages_offset = 0; messages[messages_offset] != 0; messages_offset++) {
          if((messages[messages_offset] == '\n' || messages[messages_offset] == '\r') || buff_offset >= 40) {
            if(messages[messages_offset] == '\n' && messages[messages_offset + 1] == '\r') messages_offset++;
            else if(messages[messages_offset] == '\r' && messages[messages_offset + 1] == '\n') messages_offset++;
            tft.drawString(buff, 1, 20 + screen_line * 8, FONT_MONOSPACE);
            screen_line++;
            buff_offset = 0;
            memset(buff, ' ', 40);
            // Не терять последний символ в строке
            if(messages[messages_offset] != '\n' && messages[messages_offset] != '\r') {
              buff[buff_offset] = messages[messages_offset];
              buff_offset++;
            }
            buff[buff_offset] = 0;
            if(screen_line == 32) break;
            continue;
          }
          buff[buff_offset] = messages[messages_offset];
          buff_offset++;
          //buff[buff_offset] = 0;
        }
        update_flag = 0;
      }
      prev_update_data_millis = millis();
    }

    drawButtonMatrix(0, tft.height() - 32, tft.width(), 32, buttons, 1, 1);

    while(!touchCheckNowait()) {
      tft.setTextColor(TFT_LIGHTGREY, TFT_WHITE);
      sprintf(buff, "Next update in %d sec  ",
        ((prev_update_data_millis + CHAT_AUTO_UPDATE_INTERVAL - millis()) / 1000) % 60
      );
      tft.drawString(buff, 1, tft.height() - 40, FONT_MONOSPACE);

      if(millis() - prev_update_data_millis > CHAT_AUTO_UPDATE_INTERVAL) {
        update_flag = 1;
        break;
      }
    }
    if(touchCheckNowait() == 0 && update_flag) {
      continue;
    }
    touchWaitPress();

    button_pressed = touchCheckMatrix(0, tft.height() - 32, tft.width(), 32, buttons, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        drawPrompt("Message to send", message);
        if(strlen(message) > 0) {
          if(strlen(message) < 80) {
            sprintf(query, "http://109.230.144.68/cyd/chat_post.php?nickname=%s&message=%s", nickname, message);
            http.begin(query);
            httpResponseCode = http.GET();
            if(httpResponseCode == 0) {
              drawError("Sending error");
            }
            else {
              strcpy(buff, http.getString().c_str());
              if(strcmp(buff, "ok")) {
                drawError(buff);
              }
              else {
                strcpy(message, "");
              }
            }
          }
          else {
            drawError("Message too long");
          }
        }
        update_flag = 1;
      }
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      // Флаг не сбрасываем, так как не основное приложение
      drawAppTitle("Exit");
      touchWaitRelease();
      free(messages);
      free(prev_messages);
      free(query);
      return;
    }
    touchWaitRelease();
  }
}

WebServer httpServer(80);

void http_file_access(char mode, char *io_buff) {
  HTTPClient http;
  int httpResponseCode;
  int button_pressed;
  int wifi_status;
  long prev_update_data_millis;
  int i;
  int screen_line;
  int messages_offset;
  int buff_offset;
  char buff[80];
  char nickname[80];
  char *query = NULL;
  char message[80];
  char *messages = NULL;
  char *prev_messages = NULL;
  char update_flag;
  char *buttons[] = {
    "Send message",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000100, B00000010,
    B01001110, B00100010,
    B01011111, B00100010,
    B01000100, B00100010,
    B01000100, B00100010,
    B01000100, B00100010,
    B01000100, B00100010,
    B01000100, B11111010,
    B01000100, B01110010,
    B01000000, B00100010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "File Server");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("File Server");

  wifi_status = WiFi.status();
  if(wifi_status != WL_CONNECTED && global_unixtime_retrieved == 0) {
    drawError("Wi-Fi connection required");
    return;
  }

  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("Use next URL to control files:", 1, 20, FONT_DEFAULT);
  sprintf(buff, "http://%s/", WiFi.localIP().toString());
  tft.drawString(buff, 1, 36, FONT_DEFAULT);

  httpServer.begin();
  httpServer.on("/", http_file_access_handle);
  httpServer.on("/upload", HTTP_POST, http_file_upload_handle_done, http_file_upload_handle);

  while(1) {
    httpServer.handleClient();
    if(touchCheckNowait() == 0) continue;
    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

void http_file_access_handle() {
  char *contents = NULL;
  char upload_form_begin[] = "<br>\n<form method='POST' action='/upload' enctype='multipart/form-data'>";
  char upload_form_end[] = "<input type=file name=file>\n<input type=submit value='Upload'>\n</form>\n";
  char filename[80];
  char buff[80];
  fs:File file;
  // Если есть filename - выдать содержимое
  if(httpServer.hasArg("filename")) {
    strcpy(filename, httpServer.arg("filename").c_str());
  }
  else {
    strcpy(filename, "/");
  }
  file = Storage.open(filename);
  if(file) {
    if(file.isDirectory()) {
      contents = (char *)malloc(20000 * sizeof(char));
      strcpy(contents, "");
      sprintf(buff, "Used: %d bytes of %d bytes (%d %%)<br>\n", Storage.usedBytes(), Storage.totalBytes(), (int)floor(100 * Storage.usedBytes() / Storage.totalBytes()));
      strcat(contents, buff);
      strcat(contents, "<b>Files:</b><br>\n<br>\n");
      http_file_access_show_dir(filename, contents);
      strcat(contents, upload_form_begin);
      sprintf(buff, "<input type=hidden name=path value='%s'>", filename);
      strcat(contents, buff);
      strcat(contents, upload_form_end);
      httpServer.send(200, "text/html", contents);
      free(contents);
    }
    else {
      sprintf(buff, "attachment; filename=\"%s\"", file.name());
      httpServer.sendHeader("Content-Disposition", buff);
      httpServer.streamFile(file, "text/plain");
    }
    file.close();
  }
  else {
    httpServer.send(404, "text/plain", "No such file");
  }
}

void http_file_access_show_dir(char *path, char *contents) {
  Serial.println(path);
  fs::File file;
  fs::File current_dir;
  char buff[80];
  char updir[80];
  current_dir = Storage.open(path);
  if(current_dir.isDirectory()) {
    // Если это не корневая папка, то добавляем ссылки
    if(strcmp(path, "/")) {
      strcpy(updir, path);
      while(strlen(updir) > 0 && updir[strlen(updir) - 1] != '/') {
        updir[strlen(updir) - 1] = 0;
      }
      sprintf(buff, "<a href='?filename=%s'>..</a><br>\n", updir);
      strcat(contents, buff);
    }
    while(file = current_dir.openNextFile()) {
      if(strcmp(path, "/")) {
        if(file.isDirectory()) {
          sprintf(buff, "<a href='?filename=%s/%s'>%s/%s</a> (dir)<br>\n", path, file.name(), path, file.name());
        }
        else {
          sprintf(buff, "<a href='?filename=%s/%s'>%s/%s</a> (%d bytes)<br>\n", path, file.name(), path, file.name(), file.size());
        }
      }
      else {
        if(file.isDirectory()) {
          sprintf(buff, "<a href='?filename=/%s'>/%s</a> (dir)<br>\n", file.name(), file.name());
        }
        else {
          sprintf(buff, "<a href='?filename=/%s'>/%s</a> (%d bytes)<br>\n", file.name(), file.name(), file.size());
        }
      }
      strcat(contents, buff);
    }
  }
}

fs::File uploadFile;

void http_file_upload_handle() {
  char buff[80];
  HTTPUpload& upload = httpServer.upload();

  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;

    if(httpServer.hasArg("path")) {
      filename = httpServer.arg("path") + "/" + filename;
    }
    else if(!filename.startsWith("/")) {
      filename = "/" + filename;
    }

    Serial.printf("Start upload: %s\n", filename.c_str());
    // Open file for writing in LittleFS
    uploadFile = Storage.open(filename, FILE_WRITE);
  } 
  else if (upload.status == UPLOAD_FILE_WRITE) {
    if (uploadFile) {
      // Write the chunk of received data to flash memory
      uploadFile.write(upload.buf, upload.currentSize);
    }
  } 
  else if (upload.status == UPLOAD_FILE_END) {
    if (uploadFile) {
      uploadFile.close(); // Save and close file
      Serial.printf("Upload success: %u bytes\n", upload.totalSize);
    } else {
      httpServer.send(500, "text/plain", "File creation failed");
    }
  }
}

void http_file_upload_handle_done() {
  if(httpServer.hasArg("path")) {
    httpServer.sendHeader("Location", "/?filename=" + httpServer.arg("path"));
  }
  else {
    httpServer.sendHeader("Location", "/");
  }
  httpServer.send(301, "text/html", "");
}

#endif

#define I2C_MAX_DEVICES 127

void i2c_scanner(char mode, char *io_buff) {
  char **devices;
  int button_pressed;
  int device_index;
  int device_found;
  int device_offset = 0;
  int device_selected = 0;
  int i;
  int error;
  char rescan_flag;
  char *buttons[] = {
    "Scan", "Clear",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000010, B00000010,
    B01001001, B00000010,
    B01000010, B00000010,
    B01011011, B00111010,
    B01001000, B01000010,
    B01001000, B01000010,
    B01001000, B01000010,
    B01001000, B01000010,
    B01011100, B00111010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "I2C Scanner");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  devices = (char**)malloc(I2C_MAX_DEVICES * sizeof(char *));
  for(device_index = 0; device_index < I2C_MAX_DEVICES; device_index++) {
    devices[device_index] = NULL;
  }

  clearScreen();
  drawAppTitle("I2C Scanner");

  Wire.begin(I2C_SDA, I2C_SCL);

  rescan_flag = 1;
  while(1) {
    if(rescan_flag) {
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("Scanning...      ", 1, 16, FONT_DEFAULT);

      for(device_index = 0; device_index < I2C_MAX_DEVICES; device_index++) {
        if(devices[device_index]) {
          free(devices[device_index]);
        }
        devices[device_index] = NULL;
      }

      device_found = 0;
      for(device_index = 1; device_index < 127; device_index++) {
        Wire.beginTransmission(device_index);
        error = Wire.endTransmission();
        if(error == 0) {
          devices[device_found] = (char*)malloc(80 * sizeof(char));
          sprintf(devices[device_found], "0x%02x", device_index);
          device_found++;
        }
      }
      rescan_flag = 0;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("Found devices:", 1, 16, FONT_DEFAULT);

    touchCheckList(8, 32, tft.width() - 8 * 2, tft.height() - 72, devices, 15, &device_offset, &device_selected);
    drawList(8, 32, tft.width() - 8 * 2, tft.height() - 72, devices, 15, &device_offset, &device_selected);

    drawButtonMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 2, 1);
    
    touchWaitPress();
    touchCheckList(8, 32, tft.width() - 8 * 2, tft.height() - 72, devices, 15, &device_offset, &device_selected);

    button_pressed = touchCheckMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        rescan_flag = 1;
      }
      else if(button_pressed == 1) {
        for(device_index = 0; device_index < I2C_MAX_DEVICES; device_index++) {
          if(devices[device_index]) {
            free(devices[device_index]);
          }
          devices[device_index] = NULL;
        }
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      // Флаг не сбрасываем, так как не основное приложение
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

// ====================================================
// Дашборд (часы, календарь, информация)
// ====================================================

#define CLOCK_UPDATE_SCREEN_INTERVAL 1000
#define CLOCK_UPDATE_DATA_INTERVAL 600000

void dashboard(char mode, char *io_buff) {
  char buff[80];
  char weather[80];
  char rates[80];
#ifdef IS_WIFI_ENABLED
  int wifi_status;
  HTTPClient http;
  int httpResponseCode;
#endif
  long unix_timestamp;
  int hour;
  int min;
  int sec;
  long days_since_epoch;
  long days_remain;
  int day_of_week;
  int year;
  int month;
  int day;
  int prev_day;
  int moon_day;
  int cal_dow;
  int cal_day;
  int cal_row;
  int cal_col;
  long prev_update_millis = 0;
  long prev_update_data_millis = -CLOCK_UPDATE_DATA_INTERVAL;
  char *day_of_week_name[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
  };
  char *day_of_week_short[] = {
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
  };
  char *month_name[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111110, B11111110,
    B01000010, B10000010,
    B01000010, B00000010,
    B01000010, B10000010,
    B01111110, B10000010,
    B00000000, B10000000,
    B01111110, B10000010,
    B01000010, B11111110,
    B00000010, B00000000,
    B01000010, B11111110,
    B01000010, B10000010,
    B01000000, B10000010,
    B01000010, B10000010,
    B01111110, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Dashboard");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Dashboard");

#ifdef IS_WIFI_ENABLED
  wifi_status = WiFi.status();
  if(wifi_status != WL_CONNECTED && global_unixtime_retrieved == 0) {
    drawError("Wi-Fi connection required");
    return;
  }
#endif

  strcpy(weather, "");
  strcpy(rates, "");

  while(1) {
    // Обновление данных раз в десять минут
    if(millis() - prev_update_data_millis > CLOCK_UPDATE_DATA_INTERVAL) {
      prev_update_data_millis = millis();

#ifdef IS_WIFI_ENABLED
      if(global_unixtime_retrieved == 0) {
        get_current_timestamp_wifi();
      }

      // Погода
      sprintf(buff, "http://109.230.144.68/cyd/weather.php?lat=%f&lon=%f", global_lat, global_lon);
      http.begin(buff);
      httpResponseCode = http.GET();
      if(httpResponseCode > 0) {
        strcpy(weather, http.getString().c_str());
      }
      else {
        strcpy(weather, "Weather unknown");
      }
      http.end();

      // Курсы валют
      http.begin("http://109.230.144.68/cyd/rates.php");
      httpResponseCode = http.GET();
      if(httpResponseCode > 0) {
        strcpy(rates, http.getString().c_str());
      }
      else {
        strcpy(rates, "Rates unknown");
      }
      http.end();
#endif

      tft.fillRect(0, 242, tft.width(), tft.height() - 242, TFT_WHITE);
    }
    if(millis() - prev_update_millis > CLOCK_UPDATE_SCREEN_INTERVAL) {
      prev_update_millis = millis();

      set_local_time_from_unix_timestamp();

      day_of_week = global_day_of_week;
      year = global_year;
      month = global_month;
      day = global_day;

      hour = global_hours;
      min = global_minutes;
      sec = global_seconds;

      moon_day = global_moon_day;

      // Если день изменился - очистить экран
      if(prev_day != day) {
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      }
      prev_day = day;

      // Выводим всё
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      sprintf(buff, " %d:%02d:%02d ", hour, min, sec);
      tft.drawCentreString(buff, tft.width() / 2, 35, FONT_BIGGER);

      //tft.drawCentreString(day_of_week_name[day_of_week], tft.width() / 2, 70, FONT_BIG);
      sprintf(buff, "%s, %04d", month_name[month], year);
      tft.drawCentreString(buff, tft.width() / 2, 90, FONT_BIG);

      // Календарь на текущий месяц
      cal_day = 1;
      cal_dow = (day_of_week + 7 - (day - 1) % 7) % 7;
      for(cal_row = 0; cal_row < 7; cal_row++) {
        for(cal_col = 0; cal_col < 7; cal_col++) {
          if(cal_row == 0) {
            strcpy(buff, day_of_week_short[cal_col]);
          }
          else {
            if(cal_row == 1 && cal_col < cal_dow) continue;
            sprintf(buff, "%d", cal_day);
            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
              if(cal_day > 31) break;
            }
            if(month == 2 || month == 4 || month == 6 || month == 9 || month == 11) {
              if(cal_day > 30) break;
            }
            if(global_is_lap_year && month == 2 && cal_day > 29) break;
            if(!global_is_lap_year && month == 2 && cal_day > 28) break;
            cal_day++;
          }
          if((day + 1) == cal_day) {
            tft.fillRect(cal_col * tft.width() / 7, 130 + cal_row * 16, tft.width() / 7, 16, TFT_BLUE);
            tft.setTextColor(TFT_WHITE, TFT_BLUE);
          }
          else {
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
          }
          tft.drawCentreString(buff, (cal_col + 0.5) * tft.width() / 7, 130 + cal_row * 16, FONT_DEFAULT);
        }
      }

      // Лунный день
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      sprintf(buff, "Moon day: %d", moon_day);
      tft.drawCentreString(buff, tft.width() / 2, 242, FONT_DEFAULT);
      tft.drawCentreString(weather, tft.width() / 2, 258, FONT_DEFAULT);
      tft.drawCentreString(rates, tft.width() / 2, 274, FONT_DEFAULT);

      // До следующего обновления данных
      tft.setTextColor(TFT_LIGHTGREY, TFT_WHITE);
      sprintf(buff, "  Next update in %d min %d sec  ",
        (prev_update_data_millis + CLOCK_UPDATE_DATA_INTERVAL - millis()) / 60000,
        ((prev_update_data_millis + CLOCK_UPDATE_DATA_INTERVAL - millis()) / 1000) % 60
      );
      tft.drawCentreString(buff, tft.width() / 2, tft.height() - 16, FONT_DEFAULT);
    }
    
    if(!touchCheckNowait()) continue;

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

// ====================================================
// Неточные часы
// ====================================================

#define FUZZY_CLOCK_UPDATE_SCREEN_INTERVAL 60000

void fuzzy_clock(char mode, char *io_buff) {
  int wifi_status;
  char buff[80];
  long unix_timestamp;
  int hour;
  int min;
  int sec;
  int row, col;
  int i;
  long prev_update_millis = 0;
  char hour_flag[12];
  char five_flag;
  char ten_flag;
  char quarter_flag;
  char twenty_flag;
  char past_flag;
  char half_flag;
  char to_flag;
  char minutes_flag;
  char oclock_flag;

  char *symbols[] = {
  // 01234567890
    "ITXISMHALFZ", // 0
    "TWENTYMFIVE", // 1
    "QUARTERXTEN", // 2
    "MINUTESXTOV", // 3
    "PASTRTWELVE", // 4
    "ONESIXTHREE", // 5
    "FOURGTENTWO", // 6
    "EIGHTELEVEN", // 7
    "SEVENMNINEZ", // 8
    "FIVEXOCLOCK"  // 9
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01001101, B01010010,
    B01010001, B01010010,
    B01001001, B00100010,
    B01000101, B01010010,
    B01011001, B01010010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Fuzzy Clock");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Fuzzy Clock");

#ifdef IS_WIFI_ENABLED
  wifi_status = WiFi.status();
  if(wifi_status != WL_CONNECTED && global_unixtime_retrieved == 0) {
    drawError("Wi-Fi connection required");
    return;
  }

  get_current_timestamp_wifi();
  store_current_timestamp();
#endif

  prev_update_millis = -FUZZY_CLOCK_UPDATE_SCREEN_INTERVAL;
  while(1) {
    if(millis() - prev_update_millis > FUZZY_CLOCK_UPDATE_SCREEN_INTERVAL) {
#ifdef IS_WIFI_ENABLED
      if(global_unixtime_retrieved == 0) {
        get_current_timestamp_wifi();
      }
#endif
      prev_update_millis = millis();

      unix_timestamp = global_unixtime_retrieved + (millis() - global_unixtime_retrieved_millis) / 1000;

      hour = ((unix_timestamp + global_timezone) / 3600) % 12;
      min = ((unix_timestamp + global_timezone) / 60) % 60;

      for(i = 0; i < 12; i++) hour_flag[i] = 0;
      five_flag = 0;
      ten_flag = 0;
      quarter_flag = 0;
      twenty_flag = 0;
      past_flag = 0;
      to_flag = 0;
      half_flag = 0;
      minutes_flag = 0;
      oclock_flag = 0;
      if(min < 5) {
        hour_flag[hour] = 1;
        oclock_flag = 1;
      }
      else if(min < 35) {
        past_flag = 1;
        hour_flag[hour] = 1;
        if(min < 10) {
          five_flag = 1;
        }
        else if(min < 15) {
          ten_flag = 1;
        }
        else if(min < 20) {
          quarter_flag = 1;
        }
        else if(min < 25) {
          twenty_flag = 1;
        }
        else if(min < 30) {
          twenty_flag = 1;
          five_flag = 1;
        }
        else {
          half_flag = 1;
        }
      }
      else {
        to_flag = 1;
        hour_flag[(hour + 1) % 12] = 1;
        if(min < 40) {
          minutes_flag = 1;
          twenty_flag = 1;
          five_flag = 1;
        }
        else if(min < 45) {
          minutes_flag = 1;
          twenty_flag = 1;
        }
        else if(min < 50) {
          quarter_flag = 1;
        }
        else if(min < 55) {
          minutes_flag = 1;
          ten_flag = 1;
        }
        else {
          minutes_flag = 1;
          five_flag = 1;
        }
      }


      // Выводим всё
      for(row = 0; row < 10; row++) {
        for(col = 0; col < 11; col++) {
          tft.setTextColor(TFT_LIGHTGREY, TFT_WHITE);
          // it is
          if(row == 0 && (col == 0 || col == 1 || col == 3 || col == 4)) {
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
          }
          if(oclock_flag) {
            if(row == 9 && col >= 5) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(past_flag) {
            if(row == 4 && col < 4) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(to_flag) {
            if(row == 3 && col >= 8 && col < 10) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(five_flag) {
            if(row == 1 && col >= 7) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(ten_flag) {
            if(row == 2 && col >= 8) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(quarter_flag) {
            if(row == 2 && col < 7) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(twenty_flag) {
            if(row == 1 && col < 6) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(half_flag) {
            if(row == 0 && col >= 6 && col < 10) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(minutes_flag) {
            if(row == 3 && col < 7) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[0]) {
            if(row == 4 && col >= 5) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[1]) {
            if(row == 5 && col < 3) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[2]) {
            if(row == 6 && col >= 8) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[3]) {
            if(row == 5 && col >= 6) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[4]) {
            if(row == 6 && col < 4) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[5]) {
            if(row == 9 && col < 4) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[6]) {
            if(row == 5 && col >= 3 && col < 6) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[7]) {
            if(row == 8 && col < 5) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[8]) {
            if(row == 7 && col < 5) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[9]) {
            if(row == 8 && col >= 6 && col < 10) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[10]) {
            if(row == 6 && col >= 5 && col < 8) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          if(hour_flag[11]) {
            if(row == 7 && col >= 5) {
              tft.setTextColor(TFT_BLACK, TFT_WHITE);
            }
          }
          sprintf(buff, "%c", symbols[row][col]);
          tft.drawCentreString(buff, (col + 0.5) * tft.width() / 11, 45 + row * 24, FONT_BIG);
        }
      }
    }
    
    if(!touchCheckNowait()) continue;

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

// ====================================================
// Настройка времени
// ====================================================

void set_clock(char mode, char *io_buff) {
  int button_pressed;
  int i;
  long start_millis;
  long time_remains;
  char timer_run = 0;
  char auto_restart = 0;
  char redraw_flag = 0;
  char buff[80];
  char *buttons_up[] = {
    "+", "+", "+",
    NULL
  };
  char *buttons_down[] = {
    "-", "-", "-",
    NULL
  };
  char *buttons_timezone[] = {
    "Set timezone", NULL
  };
  char *buttons_sync[] = {
    "Sync via Wi-Fi", NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00011111, B11111000,
    B00100000, B00000100,
    B01000001, B00000010,
    B01000001, B00000010,
    B01000001, B00000010,
    B01000001, B00000010,
    B01000001, B00000010,
    B01000001, B11110010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B00100000, B00000100,
    B00011111, B11111000,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Set Clock");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Set Clock");

  redraw_flag = 1;
  while(1) {
    // Обновляем время
    set_local_time_from_unix_timestamp();
    // Рисуем время
    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    sprintf(buff, " %04d ", global_year);
    tft.drawCentreString(buff, 1 * tft.width() / 6, 56, FONT_BIG);
    sprintf(buff, " %02d ", global_month);
    tft.drawCentreString(buff, 3 * tft.width() / 6, 56, FONT_BIG);
    sprintf(buff, " %02d ", global_day);
    tft.drawCentreString(buff, 5 * tft.width() / 6, 56, FONT_BIG);

    if(global_timezone == 0) {
      sprintf(buff, "%d", 0);
    }
    else if(global_timezone % 3600 == 0) {
      sprintf(buff, "%c%dh", global_timezone >= 0 ? '+' : '-', global_timezone / 3600);
    }
    else if(global_timezone % 60 == 0) {
      sprintf(buff, "%c%dh %dm", global_timezone >= 0 ? '+' : '-', global_timezone / 3600, (global_timezone / 60) % 60);
    }
    else {
      sprintf(buff, "%c%d", global_timezone >= 0 ? '+' : '-', global_timezone);
    }
    tft.drawCentreString(buff, 3 * tft.width() / 4, 132, FONT_BIG);

    sprintf(buff, " %2d ", global_hours);
    tft.drawCentreString(buff, 1 * tft.width() / 6, 206, FONT_BIG);
    sprintf(buff, " %02d ", global_minutes);
    tft.drawCentreString(buff, 3 * tft.width() / 6, 206, FONT_BIG);
    sprintf(buff, " %02d ", global_seconds);
    tft.drawCentreString(buff, 5 * tft.width() / 6, 206, FONT_BIG);

    // Если таймер запущен и касаний нет - остальное не рисуем
    if(redraw_flag == 0 && touchCheckNowait() == 0) {
      continue;
    }

    drawButtonMatrix(0, 20, tft.width(), 32, buttons_up, 3, 1);
    drawButtonMatrix(0, 84, tft.width(), 32, buttons_down, 3, 1);
    drawButtonMatrix(0, 128, tft.width() / 2, 32, buttons_timezone, 1, 1);
    drawButtonMatrix(0, 170, tft.width(), 32, buttons_up, 3, 1);
    drawButtonMatrix(0, 234, tft.width(), 32, buttons_down, 3, 1);

#ifdef IS_WIFI_ENABLED
    drawButtonMatrix(0, tft.height() - 32, tft.width(), 32, buttons_sync, 1, 1);
#endif

    redraw_flag = 0;

    // Год - месяц - день
    button_pressed = touchCheckMatrix(0, 20, tft.width(), 32, buttons_up, 3, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        global_unixtime_retrieved += 365 * 24 * 60 * 60;
      }
      else if(button_pressed == 1) {
        global_unixtime_retrieved += 30 * 24 * 60 * 60;
      }
      else if(button_pressed == 2) {
        global_unixtime_retrieved += 24 * 60 * 60;
      }
      redraw_flag = 1;
    }
    button_pressed = touchCheckMatrix(0, 84, tft.width(), 32, buttons_down, 3, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        global_unixtime_retrieved -= 365 * 24 * 60 * 60;
      }
      else if(button_pressed == 1) {
        global_unixtime_retrieved -= 30 * 24 * 60 * 60;
      }
      else if(button_pressed == 2) {
        global_unixtime_retrieved -= 24 * 60 * 60;
      }
      redraw_flag = 1;
    }

    // Часовой пояс
    button_pressed = touchCheckMatrix(0, 128, tft.width() / 2, 32, buttons_timezone, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        sprintf(buff, "%ld", global_timezone);
        if(drawPrompt("Timezone in seconds", buff) == 0) {
          sscanf(buff, "%ld", &global_timezone);
          save_current_timezone();
        }
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      }
      redraw_flag = 1;
    }

    // Часы - минуты - секунды
    button_pressed = touchCheckMatrix(0, 170, tft.width(), 32, buttons_up, 3, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        global_unixtime_retrieved += 60 * 60;
      }
      else if(button_pressed == 1) {
        global_unixtime_retrieved += 60;
      }
      else if(button_pressed == 2) {
        global_unixtime_retrieved += 1;
      }
      redraw_flag = 1;
    }
    button_pressed = touchCheckMatrix(0, 234, tft.width(), 32, buttons_down, 3, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        global_unixtime_retrieved -= 60 * 60;
      }
      else if(button_pressed == 1) {
        global_unixtime_retrieved -= 60;
      }
      else if(button_pressed == 2) {
        global_unixtime_retrieved -= 1;
      }
      redraw_flag = 1;
    }

#ifdef IS_WIFI_ENABLED
    // Получить время через вай-фай
    button_pressed = touchCheckMatrix(0, tft.height() - 32, tft.width(), 32, buttons_sync, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        get_current_timestamp_wifi();
        store_current_timestamp();
      }
    }
#endif

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      store_current_timestamp();
      touchWaitRelease();
      touchExitActionReset();
      return;
    }

    touchWaitRelease();
  }
}

// ====================================================
// Просмотр шрифта
// ====================================================

void view_font(char mode, char *io_buff) {
  int i;
  unsigned char byte;
  char buff[80];
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000010, B01000010,
    B01000100, B00100010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01001111, B11110010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "View Font");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("View Font");

  byte = 0;
  while(1) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    for(i = 0; i < 16; i++) {
      sprintf(buff, " %d 0x%02X %c     ", (int)byte, (int)byte, byte);
      tft.drawString(buff, 1, 16 + i * 16, FONT_DEFAULT);
      tft.drawString(buff, tft.width() / 2, 16 + i * 16 + 4, FONT_MONOSPACE);
      byte++;
    }

    touchWaitPress();
    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      store_current_timestamp();
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

// ====================================================
// Общие функции для устройства
// ====================================================

void set_local_time_from_unix_timestamp() {
  unsigned long unix_timestamp;
  unsigned long days_since_epoch;
  unsigned long days_remain;
  int year;
  int month;
  int day;
  char is_lap_year;
  char retry_retrieve;
  int prev_day;

  // Если время уже было откуда-то загружено и день был установлен, то есть эта функция уже отработала раз
  if(global_unixtime_retrieved != 0 && global_day != 0) {
    retry_retrieve = 1;
  }

  unix_timestamp = global_unixtime_retrieved + (millis() - global_unixtime_retrieved_millis) / 1000;

  // Дней с начала эпохи
  days_since_epoch = (unix_timestamp + global_timezone) / 86400;
  // День недели
  global_day_of_week = (days_since_epoch + 3) % 7;
  // Высчитываем дату
  days_remain = days_since_epoch;
  year = 1970;
  month = 1;
  day = 1;
  while(days_remain > 0) {
    // Високосные годы
    is_lap_year = 0;
    if(year % 4 == 0 && (year % 100 == 0 || year % 400 != 0)) {
      is_lap_year = 1;
    }
    if(is_lap_year && days_remain >= 366) {
      days_remain -= 366;
      year++;
      continue;
    }
    // Обычные годы
    if(!is_lap_year && days_remain >= 365) {
      days_remain -= 365;
      year++;
      continue;
    }
    //Serial.println(days_remain);
    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && days_remain >= 31) {
      days_remain -= 31;
      month++;
      continue;
    }
    if((month == 4 || month == 6 || month == 9 || month == 11) && days_remain >= 30) {
      days_remain -= 30;
      month++;
      continue;
    }
    if(month == 2 && days_remain >= 29 & is_lap_year) {
      days_remain -= 29;
      month++;
      continue;
    }
    if(month == 2 && days_remain >= 28 & !is_lap_year) {
      days_remain -= 28;
      month++;
      continue;
    }
    day += days_remain;
    break;
  }

  // Если дата изменилась
  if(retry_retrieve && global_day != day) {
    store_current_timestamp();
  }

  global_year = year;
  global_month = month;
  global_day = day;
  global_is_lap_year = is_lap_year;

  global_hours = ((unix_timestamp + global_timezone) / 3600) % 24;
  global_minutes = ((unix_timestamp + global_timezone) / 60) % 60;
  global_seconds = (unix_timestamp + global_timezone) % 60;

  global_moon_day = fmod(25 + days_since_epoch, 29.53059);
}

// Сохранить текущую дату в ФС
void store_current_timestamp() {
  char buff[80];
  unsigned long current_timestamp;
  unsigned long saved_timestamp;

/*
  // Если время не было обновлено - ничего не делаем
  if(global_unixtime_retrieved == 0) return;


  read_file_to_buff("/Settings/Timestamp", 79, buff);
  sscanf(buff, "%lu", &saved_timestamp);

  // Сохраняем время если разница больше суток в любую сторону
  // Компилятор ругается что нельзя взять модуль от unsigned
  if((current_timestamp > saved_timestamp && current_timestamp - saved_timestamp >= 86400)
    ||
    (current_timestamp < saved_timestamp && saved_timestamp - current_timestamp >= 86400)
  ) {
    sprintf(buff, "%lu", current_timestamp);
    write_file_from_buff("/Settings/Timestamp", buff);
  }
  */
  Serial.println("store_current_timestamp");
  current_timestamp = global_unixtime_retrieved + (millis() - global_unixtime_retrieved_millis) / 1000;
  sprintf(buff, "%lu", current_timestamp);
  write_file_from_buff("/Settings/Timestamp", buff);
}

void get_current_timestamp_fs() {
  char buff[80];
  if(read_file_to_buff("/Settings/Timestamp", 79, buff)) {
    sscanf(buff, "%lu", &global_unixtime_retrieved);
    global_unixtime_retrieved_millis = millis();
  }
}

void get_current_timezone() {
  char buff[80];
  if(read_file_to_buff("/Settings/Timezone", 79, buff)) {
    sscanf(buff, "%ld", &global_timezone);
  }
}

void save_current_timezone() {
  char buff[80];
  sprintf(buff, "%ld", global_timezone);
  write_file_from_buff("/Settings/Timezone", buff);
}

void screen_test(char mode, char *io_buff) {
  int i;
  int colors[] = {TFT_WHITE, TFT_RED, TFT_GREEN, TFT_BLUE, TFT_MAGENTA, TFT_CYAN, TFT_YELLOW, TFT_BLACK};
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01010101, B00000010,
    B01010101, B00000010,
    B01010101, B00000010,
    B01010101, B00000010,
    B01010101, B00000010,
    B01010101, B00000010,
    B01111111, B11111110,
    B01111111, B00000010,
    B01111111, B11111110,
    B01111111, B00000010,
    B01111111, B11111110,
    B01111111, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Screen Test");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  for(i = 0; i < 8; i++) {
    tft.fillScreen(colors[i]);

    touchWaitPress();
    touchWaitRelease();
  }

  tft.fillScreen(TFT_WHITE);
  for(i = 0; i != 160; i++) {
    tft.drawLine(0, i * 2, tft.width(), i * 2, TFT_BLACK);
  }
  touchWaitPress();
  touchWaitRelease();

  tft.fillScreen(TFT_WHITE);
  for(i = 0; i != 160; i++) {
    tft.drawLine(0, i * 2 + 1, tft.width(), i * 2 + 1, TFT_BLACK);
  }
  touchWaitPress();
  touchWaitRelease();
  
  tft.fillScreen(TFT_WHITE);
  for(i = 0; i != 120; i++) {
    tft.drawLine(i * 2, 0, i * 2, tft.height(), TFT_BLACK);
  }
  touchWaitPress();
  touchWaitRelease();

  tft.fillScreen(TFT_WHITE);
  for(i = 0; i != 120; i++) {
    tft.drawLine(i * 2 + 1, 0, i * 2 + 1, tft.height(), TFT_BLACK);
  }
  touchWaitPress();
  touchWaitRelease();
}

// Просмотр файла
void view_file(char *title, char *filename) {
  fs::File file;
  int word_offset;
  int word_in_line_offset = 0;
  int show_file_offset_lines = 0;
  int current_file_offset_lines = 0;
  int current_line_on_screen = 0;
  int touch_x, touch_y;
  int i;
  char new_line_flag = 0;
  char show_line_flag = 0;
  char show_next_line_flag = 0;
  char long_string_flag = 0;
  char last_line_visible_flag = 0;
  char byte;
  char buff[80];
  char current_string[80];
  char current_word[80];

  clearScreen();
  drawAppTitle(title);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  file = Storage.open(filename);
  if(!file) {
    drawError("Cannot open file");
    return;
  }
  if(file.isDirectory()) {
    drawError("Cannot view directory");
    return;
  }

  // Нет ли сохранённого смещения для файла?
  if(read_key_value_from_file("/Settings/View", filename, buff)) {
    sscanf(buff, "%d", &show_file_offset_lines);
  }

  while(1) {
    // Вывести текст по текущему смещению
    // Начинаем с начала файла и читаем пока не попадём на отображаемую часть
    file.seek(0);
    current_file_offset_lines = 0;
    current_line_on_screen = 0;
    word_in_line_offset = 0;
    current_string[0] = 0;
    tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);

    word_offset = 0;
    current_word[word_offset] = 0;
    while(file.available()) {
      // Читаем слово
      new_line_flag = 0;
      show_line_flag = 0;
      long_string_flag = 0;
      while(file.available()) {
        byte = file.read();
        current_word[word_offset] = byte;
        word_offset++;
        current_word[word_offset] = 0;
        if(byte == '\n') {
          if(file.peek() == '\r') file.read();
        }
        if(byte == '\r') {
          if(file.peek() == '\n') file.read();
        }
        // Пробел, дефис, перевод строки завершают слово
        if(byte == '\n' || byte == '\r') {
          new_line_flag = 1;
        }
        if(byte == ' ' || byte == '\n' || byte == '\r') {
          break;
        }
        // Кроме дефиса в начале слова
        if(byte == '-' && word_offset > 0) {
          break;
        }
        if(word_offset >= 60) {
          break;
        }
      }

      // Проверяем, помещается ли слово в текущую строку по ширине, байтам
      if(tft.textWidth(current_string, FONT_DEFAULT) + tft.textWidth(current_word, FONT_DEFAULT) < (tft.width() - 2)
        && strlen(current_string) + strlen(current_word) < 79) {
        // Помещаем туда слово, повторяем
        strcat(current_string, current_word);
        word_offset = 0;
        current_word[word_offset] = 0;

        // Если ещё не перенос и файл не закончился - читаем следующее слово
        if(new_line_flag == 0 && file.available()) {
          continue;
        }
      }

      // Если строка пустая, а слово не поместилось, то нужно вывести часть слова, остальное оставить на потом
      if(strlen(current_string) == 0 && tft.textWidth(current_word, FONT_DEFAULT) < (tft.width() - 2)) {
        // Убавляем символы из строки пока не поместимся в экран
        strcpy(current_string, current_word);
        while(tft.textWidth(current_string, FONT_DEFAULT) >= (tft.width() - 2)) {
          current_string[strlen(current_string) - 1] = 0;
        }
        // От текущего слова надо отрезать соответствующий кусок
        for(i = 0; i <strlen(current_string); i++) {
          current_word[i] = current_word[i + strlen(current_string)];
        }
        current_word[i] = 0;
      }

      // Пора выводить строку
      // Пока не заполнен экран
      while(current_line_on_screen <= 18) {
        // Выводить строку только если достигнуто смещение в строках, иначе просто считать строки
        if(current_file_offset_lines >= show_file_offset_lines) {
            tft.drawString(current_string, 1, 16 + current_line_on_screen * 16, FONT_DEFAULT);
            current_line_on_screen++;
        }
        current_file_offset_lines++;
        current_string[0] = 0;

        // Если файл закончился или есть остаток строки,
        // а место на экране ещё есть, нужно вывести остаток из current_word
        if(!file.available() || new_line_flag) {
          // Если ничего не осталось - пора выходить
          if(strlen(current_string) == 0 && strlen(current_word) == 0) {
            break;
          }
          // Убавляем символы из строки пока не поместимся в экран
          strcpy(current_string, current_word);
          while(tft.textWidth(current_string, FONT_DEFAULT) >= (tft.width() - 2)) {
            current_string[strlen(current_string) - 1] = 0;
          }
          // От текущего слова надо отрезать соответствующий кусок
          for(i = 0; i < strlen(current_string); i++) {
            current_word[i] = current_word[i + strlen(current_string)];
          }
          current_word[i] = 0;
        }
        else {
          break;
        }
      }
      current_string[0] = 0;

      // Если экран заполнен - выходим
      if(current_line_on_screen > 18) {
        break;
      }
    }

    touchWaitPress();
    // Смотрим куда нажатие, двигаемся либо вперёд по файлу, либо назад
    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);
    if(touch_y > 16) {
      // Левая часть экрана - назад
      if(touch_x < tft.width() / 2) {
          show_file_offset_lines -= 19;
          if(show_file_offset_lines < 0) {
            show_file_offset_lines = 0;
          }
      }
      // Правая - вперёд, если есть куда
      else if(touch_x > tft.width() / 2) {
        if(file.available() || strlen(current_word) > 0) {
          show_file_offset_lines += 19;
        }
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      drawAppTitle(title);
      sprintf(buff, "%d", show_file_offset_lines);
      write_key_value_to_file("/Settings/View", filename, buff);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

#define EDIT_FILE_LENGTH_MAX 8192

// Редактирование небольшого файла
void edit_file(char *title, char *filename) {
  int file_offset_bytes = 0;
  // Позиция курсора в байтах, перед каким символом стоит курсор
  int cursor_offset_bytes = 0;
  // Позиция курсора на экране
  int cursor_screen_pos_x = 0;
  int cursor_screen_pos_y = 0;
  // Флаги если курсор не на экране
  char cursor_too_high = 0;
  char cursor_too_low = 0;
  char cursor_line_number = 0;
  char set_cursor_from_touch = 0;
  char changes_present = 0;

  int string_offset;
  int file_line_number = 0; // Номер текущей строки в файле
  int screen_line_number = 0; // Номер строки на экране в процессе вывода
  int file_skip_lines = 0; // Сколько строк фалйа пропустить
  int touch_x, touch_y;
  int button;
  char byte;
  char buff[80];
  char current_string[80];
  char *contents;
  char caps_flag = 0;
  char symbol_flag = 0;
  char alt_flag = 0;
  int prev_width = 0;
  
  char *keyboard_nocaps[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "-",
    ":shift:", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", ":enter:",
    ":change:", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", " ",
    NULL
  };
  char *keyboard_caps[] = {
    "~",  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", ":backspace:",
    " ", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "_",
    ":shift:", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", ":enter:",
    ":change:", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", " ",
    NULL
  };
  char *keyboard_symbol[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ",  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "=",
    ":shift:", "[", "]", "<", ">", ".", ",", ":", ";", "\"", "'", ":enter:",
    ":change:", "{", "}", "+", "-", "*", "/", "\\", "~", "|", "?", " ",
    NULL
  };
  char *keyboard_alt_nocaps[] = {
    "\xB8",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    "\xE9", "\xF6", "\xF3", "\xEA", "\xE5", "\xED", "\xE3", "\xF8", "\xF9", "\xE7", "\xF5", "\xFA",
    ":shift:", "\xF4", "\xFB", "\xE2", "\xE0", "\xEF", "\xF0", "\xEE", "\xEB", "\xE4", "\xE6", ":enter:",
    ":change:", "\xFF", "\xF7", "\xF1", "\xEC", "\xE8", "\xF2", "\xFC", "\xE1", "\xFE", "\xFD", " ",
    NULL
  };
  char *keyboard_alt_caps[] = {
    "\xA8",  "!", "\"", "\xB9", ";", "%", ":", "?", "*", "(", ")", ":backspace:",
    "\xC9", "\xD6", "\xD3", "\xCA", "\xC5", "\xCD", "\xC3", "\xD8", "\xD9", "\xC7", "\xD5", "\xDA",
    ":shift:", "\xD4", "\xDB", "\xC2", "\xC0", "\xCF", "\xD0", "\xCE", "\xCB", "\xC4", "\xC6", ":enter:",
    ":change:", "\xDF", "\xD7", "\xD1", "\xCC", "\xC8", "\xD2", "\xDC", "\xC1", "\xDE", "\xDD", " ",
    NULL
  };

  char **keyboard_current = keyboard_nocaps;
  fs::File file;

  contents = (char *)malloc(EDIT_FILE_LENGTH_MAX * sizeof(char));

  clearScreen();
  drawAppTitle(title);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  contents[0] = 0;
  file = Storage.open(filename);
  if(file) {
    if(file.isDirectory()) {
      drawError("Cannot edit directory");
      return;
    }

    // Читаем файл в буфер, но не более 8191 байт
    file_offset_bytes = 0;
    while(file.available()) {
      contents[file_offset_bytes] = file.read();
      contents[file_offset_bytes + 1] = 0;
      file_offset_bytes++;
      if(file_offset_bytes >= (EDIT_FILE_LENGTH_MAX - 1)) break;
    }
    // Если файл ещё не кончился - сообщаем об ошибке
    if(file.available()) {
      drawError("File too large to edit");
      return;
    }

    file.close();
  }

  file_skip_lines = 0;
  while(1) {
    // Вывести текст по текущему смещению
    // Начинаем с начала файла и читаем пока не попадём на отображаемую часть
    current_string[0] = 0;
    tft.fillRect(0, 16, tft.width(), 200 - 16, TFT_WHITE);

    cursor_too_low = 0;
    cursor_too_high = 0;
    file_offset_bytes = 0;
    file_line_number = 0;
    screen_line_number = 0;
    cursor_line_number = -1;
    // Файл может быть пустым, в этом случае курсор стоит в начале первой строки
    if(contents[file_offset_bytes] == 0) {
      cursor_screen_pos_x = 0;
      cursor_screen_pos_y = 16 + screen_line_number * 16;
      cursor_offset_bytes = 0;
      cursor_line_number = screen_line_number;
    }
    while(contents[file_offset_bytes] != 0) {
      // Читаем символы в буфер пока текст помещается по ширине в экран
      string_offset = 0;
      buff[0] = 0;
      prev_width = 0;
      // Читаем строку пока строка не закончится по какому-либо условию
      while(contents[file_offset_bytes] != 0) {
        byte = contents[file_offset_bytes];
        // Если курсор не перемещали касанием, то находим его место
        if(set_cursor_from_touch == 0 && cursor_offset_bytes == file_offset_bytes) {
          cursor_screen_pos_x = tft.textWidth(buff, FONT_DEFAULT);
          cursor_screen_pos_y = 16 + screen_line_number * 16;
          cursor_line_number = screen_line_number;
        }

        if(set_cursor_from_touch) {
          // Если нажатие от текущего символа до конца строки, то переставить курсор сюда
          // Таким образом курсор может оказаться от начала строки до конца строки
          if(touch_y >= 16 + screen_line_number * 16
            && touch_y < 16 + (screen_line_number + 1) * 16
            && touch_x >= tft.textWidth(buff, FONT_DEFAULT)
          ) {
            cursor_screen_pos_x = tft.textWidth(buff, FONT_DEFAULT);
            cursor_offset_bytes = file_offset_bytes;

            // Если это последний символ в файле, то если касание правее него, то нужно поставить курсор после последнего символа
            if(contents[file_offset_bytes + 1] == 0) {
              // Добавляем символ в строку, получаем ширину, удаляем символ
              buff[string_offset] = byte;
              buff[string_offset + 1] = 0;
              if(touch_x >= tft.textWidth(buff, FONT_DEFAULT)) {
                cursor_screen_pos_x = tft.textWidth(buff, FONT_DEFAULT);
                cursor_offset_bytes = file_offset_bytes + 1;
              }
              buff[string_offset] = 0;
            }

            cursor_screen_pos_y = 16 + screen_line_number * 16;
            cursor_line_number = screen_line_number;
          }
        }

        file_offset_bytes++;

        // Переводы строк завершают текущую строку, сам байт в строку не добавляется
        if(byte == '\n' || byte == '\r') {
          // Но из-за него курсор может оказаться на следующей строке!
          if(set_cursor_from_touch == 0 && cursor_offset_bytes == file_offset_bytes) {
            cursor_screen_pos_x = 0;
            cursor_screen_pos_y = 16 + (screen_line_number + 1) * 16;
            cursor_line_number = screen_line_number + 1;
          }
          break;
        }

        // Добавляем байт в строку
        buff[string_offset] = byte;
        string_offset++;
        buff[string_offset] = 0;

        prev_width = tft.textWidth(buff, FONT_DEFAULT);
        if(tft.textWidth(buff, FONT_DEFAULT) + 10 >= tft.width()) {
          break;
        }
        if(string_offset >= 60) {
          break;
        }
      }
      
      // Если курсор стоит после последнего символа, этот кусок не отрабатывает
      // Если курсор не перемещали касанием, то находим его место
      if(set_cursor_from_touch == 0 && cursor_offset_bytes == file_offset_bytes && (byte != '\n' && byte != '\r')) {
        cursor_screen_pos_x = tft.textWidth(buff, FONT_DEFAULT);
        cursor_screen_pos_y = 16 + screen_line_number * 16;
        cursor_line_number = screen_line_number;
      }

      // Если файл сдвинут на несколько строк - пропускаем их
      if(file_skip_lines > file_line_number) {
        file_line_number++;
        continue;
      }
      file_line_number++;

      // Пора показать строку
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString(buff, 1, 16 + screen_line_number * 16, FONT_DEFAULT);
      screen_line_number++;

      // Если экран заполнен - выходим
      if(screen_line_number > 10) {
        break;
      }
    }

    // Если курсор не был достигнут, нужно перезапустить вывод
    if(cursor_offset_bytes > file_offset_bytes) {
      cursor_too_low = 1;
    }
    if(cursor_line_number >= 10) {
      cursor_too_low = 1;
    }
    if(cursor_line_number <= 0) {
      cursor_too_high = 1;
    }

    // Если экран заполнен, а курсор не на экране - прокручиваем экран в нужную сторону и перезапускаем вывод
    set_cursor_from_touch = 0;
    if(file_skip_lines > 0 && cursor_too_high) {
      file_skip_lines--;
      continue;
    }
    if(cursor_too_low) {
      file_skip_lines++;
      continue;
    }

    // Рисуем курсор где нужно
    tft.fillRect(cursor_screen_pos_x, cursor_screen_pos_y, 2, 16, TFT_BLUE);

    if(symbol_flag) {
      keyboard_current = keyboard_symbol;
    }
#ifdef ALT_KEYBOARD_ENABLED
    else if(caps_flag) {
      if(alt_flag) {
        keyboard_current = keyboard_alt_caps;
      }
      else {
        keyboard_current = keyboard_caps;
      }
    }
    else {
      if(alt_flag) {
        keyboard_current = keyboard_alt_nocaps;
      }
      else {
        keyboard_current = keyboard_nocaps;
      }
    }
#else
    else if(caps_flag) {
      keyboard_current = keyboard_caps;
    }
    else {
      keyboard_current = keyboard_nocaps;
    }
#endif

    drawButtonMatrix(0, 200, tft.width(), 120, keyboard_current, 12, 4);
    
    touchWaitPress();
    button = touchCheckMatrix(0, 200, tft.width(), 120, keyboard_current, 12, 4);
    if(button != -1) {
      if(button == 11) {
        if(cursor_offset_bytes > 0) {
          for(file_offset_bytes = cursor_offset_bytes - 1; file_offset_bytes < strlen(contents); file_offset_bytes++) {
            contents[file_offset_bytes] = contents[file_offset_bytes + 1];
          }
          cursor_offset_bytes --;
        }
        changes_present = 1;
      }
      else if(button == 24) {
        caps_flag = !caps_flag;
      }
      else if(button == 36) {
        symbol_flag = !symbol_flag;
        if(!symbol_flag) {
          if(alt_flag) {
            alt_flag = 0;
          }
          else {
            alt_flag = 1;
          }
        }
      }
      else {
        if(strlen(contents) < (EDIT_FILE_LENGTH_MAX - 1)) {
          for(file_offset_bytes = strlen(contents); file_offset_bytes >= cursor_offset_bytes; file_offset_bytes--) {
            contents[file_offset_bytes + 1] = contents[file_offset_bytes];
          }
          if(button == 35) {
            contents[cursor_offset_bytes] = '\n';
          }
          else {
            contents[cursor_offset_bytes] = keyboard_current[button][0];
            caps_flag = 0;
          }
          cursor_offset_bytes++;
          changes_present = 1;
        }
      }
    }

    // Смотрим куда нажатие, ставим курсор в ближайшее место
    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);
    // В текстовую часть экрана
    set_cursor_from_touch = 0;
    if(touch_y >= 16 && touch_y < 192) {
      set_cursor_from_touch = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      drawAppTitle(title);
      if(changes_present) {
        // Спрашиваем о сохранении, сохраняем если да
        if(drawConfirm("Save changes?") == 0) {
          file = Storage.open(filename, FILE_WRITE);
          file_offset_bytes = 0;
          //while(contents[file_offset_bytes] != 0) {
            file.print(contents);
            //file_offset_bytes++;
          //}
          file.close();
        }
      }
      free(contents);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void touch_calibration(char mode, char *io_buff) {
  char buff[80];
  TS_Point p1, p2, p3;
  int offset = 10;
  
  int touch_x;
  int touch_y;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000000, B00111010,
    B01000000, B01110010,
    B01000000, B11100010,
    B01000001, B11000010,
    B01000011, B10000010,
    B01000111, B00000010,
    B01010100, B00000010,
    B01001000, B00000010,
    B01010100, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Calibration");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  clearScreen();
  tft.drawCentreString("Touch left top cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(offset - 5, offset - 5, offset + 5, offset + 5, TFT_BLACK);
  tft.drawLine(offset - 5, offset + 5, offset + 5, offset - 5, TFT_BLACK);
  delay(1000);
  touchWaitPress();
  p1 = touchscreen.getPoint();
  clearScreen();
  tft.drawCentreString("Release", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  touchWaitRelease();
  delay(1000);  

  clearScreen();
  tft.drawCentreString("Touch left bottom cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(offset - 5, tft.height() - 2 - offset - 5, offset + 5, tft.height() - 2 - offset + 5, TFT_BLACK);
  tft.drawLine(offset - 5, tft.height() - 2 - offset + 5, offset + 5, tft.height() - 2 - offset - 5, TFT_BLACK);
  delay(1000);
  touchWaitPress();
  p2 = touchscreen.getPoint();
  clearScreen();
  tft.drawCentreString("Release", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  touchWaitRelease();
  delay(1000);  

  clearScreen();
  tft.drawCentreString("Touch right top cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(tft.width() - 2 - offset - 5, offset - 5, tft.width() - 2 - offset + 5, offset + 5, TFT_BLACK);
  tft.drawLine(tft.width() - 2 - offset - 5, offset + 5, tft.width() - 2 - offset + 5, offset - 5, TFT_BLACK);
  delay(1000);
  touchWaitPress();
  p3 = touchscreen.getPoint();
  clearScreen();
  tft.drawCentreString("Release", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  touchWaitRelease();
  delay(1000);  

  // Вычисление коэффициентов ax, bx, cx, ay, by, cy методом Крамера
  // d - определитель матрицы
  d = det3(p1.x, p1.y, 1, p2.x, p2.y, 1, p3.x, p3.y, 1);

  ax = det3(offset, p1.y, 1, offset, p2.y, 1, tft.width() - offset - 1, p3.y, 1) / d;
  bx = det3(p1.x, offset, 1, p2.x, offset, 1, p3.x, tft.width() - offset - 1, 1) / d;
  cx = det3(p1.x, p1.y, offset, p2.x, p2.y, offset, p3.x, p3.y, tft.width() - offset - 1) / d;

  ay = det3(offset, p1.y, 1, tft.height() - offset - 1, p2.y, 1, offset, p3.y, 1) / d;
  by = det3(p1.x, offset, 1, p2.x, tft.height() - offset - 1, 1, p3.x, offset, 1) / d;
  cy = det3(p1.x, p1.y, offset, p2.x, p2.y, tft.height() - offset - 1, p3.x, p3.y, offset) / d;

  clearScreen();
  tft.drawCentreString("Done!", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  touchWaitRelease();
  touch_calibration_save();
  delay(1000);
}

// Сохранение данных калибровки в ФС
void touch_calibration_save() {
  fs::File file;
  char buff[80];
  file = Storage.open("/Settings/Calibration", FILE_WRITE);
  if(file) {
    sprintf(buff, "%f %f %f %f %f %f", ax, bx, cx, ay, by, cy);
    file.print(buff);
    file.close();
  }
}

void fifteen(char mode, char *io_buff) {
  int button_pressed;
  int empty_tile = 15;
  int moves_remain;
  int i;
  int level = 1;
  int steps = 0;
  char valid_move_flag;
  char shuffle_flag = 1;
  char won_flag = 0;
  char *tmp;
  char buff[80];
  char *buttons_won[] = {
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL
  };
  char *buttons[] = {
    "1", "2", "3", "4",
    "5", "6", "7", "8",
    "9", "10", "11", "12",
    "13", "14", "15", " ",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000100, B11110010,
    B01001100, B10000010,
    B01000100, B10000010,
    B01000100, B11100010,
    B01000100, B00010010,
    B01000100, B00010010,
    B01000100, B00010010,
    B01001110, B11100010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  for(i = 0; i < 16; i++) {
    buttons_won[i] = buttons[i];
  }

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Fifteen");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Fifteen");

  while(1) {
    if(shuffle_flag) {
      // Перемешиваем
      steps = 0;
      moves_remain = 1000;
      while(moves_remain > 0) {
        valid_move_flag = 0;
        button_pressed = random(0, 16);
        if(button_pressed / 4 == empty_tile / 4 && abs(button_pressed % 4 - empty_tile % 4) == 1) valid_move_flag = 1;
        if(button_pressed % 4 == empty_tile % 4 && abs(button_pressed / 4 - empty_tile / 4) == 1) valid_move_flag = 1;
        
        if(!valid_move_flag) continue;

        tmp = buttons[button_pressed];
        buttons[button_pressed] = buttons[empty_tile];
        buttons[empty_tile] = tmp;
        empty_tile = button_pressed;

        moves_remain--;
      }
      shuffle_flag = 0;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "Level: %d", level);
    tft.drawString(buff, 8, 20, FONT_DEFAULT);

    sprintf(buff, "Steps: %d", steps);
    tft.drawString(buff, tft.width() / 2, 20, FONT_DEFAULT);

    drawButtonMatrix(0, 64, tft.width(), tft.width(), buttons, 4, 4);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 64, tft.width(), tft.width(), buttons, 4, 4);
    if(button_pressed != -1) {
      valid_move_flag = 0;
      if(button_pressed / 4 == empty_tile / 4 && abs(button_pressed % 4 - empty_tile % 4) == 1) valid_move_flag = 1;
      if(button_pressed % 4 == empty_tile % 4 && abs(button_pressed / 4 - empty_tile / 4) == 1) valid_move_flag = 1;
      
      if(!valid_move_flag) continue;

      tmp = buttons[button_pressed];
      buttons[button_pressed] = buttons[empty_tile];
      buttons[empty_tile] = tmp;
      empty_tile = button_pressed;
      steps++;
    }

    won_flag = 1;
    for(i = 0; i < 16; i++) {
      if(buttons_won[i] != buttons[i]) won_flag = 0;
    }
    if(won_flag) {
      drawInfo("You won!");
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      shuffle_flag = 1;
      steps = 0;
      level++;
      won_flag = 0;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void memory_match(char mode, char *io_buff) {
  int button_pressed;
  int i;
  int j;
  int level = 1;
  int steps = 0;
  int item_selected = -1;
  char shuffle_flag = 1;
  char won_flag = 0;
  char buff[80];
  char empty[] = "";
  char *tmp = NULL;
  char *buttons_show[] = {
    empty, empty, empty, empty, empty,
    empty, empty, empty, empty, empty,
    empty, empty, empty, empty, empty,
    empty, empty, empty, empty, empty,
    empty, empty, empty, empty, empty,
    empty, empty, empty, empty, empty,
    NULL
  };
  char *buttons[] = {
    "1", "1", "2", "2", "3",
    "3", "4", "4", "5", "5",
    "6", "6", "7", "7", "8",
    "8", "9", "9", "10", "10",
    "11", "11", "12", "12", "13",
    "13", "14", "14", "15", "15",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111110, B01111110,
    B01000010, B01000010,
    B01000010, B01001010,
    B01000010, B01001010,
    B01000010, B01000010,
    B01111110, B01111110,
    B00000000, B00000000,
    B00000000, B00000000,
    B01111110, B01111110,
    B01000010, B01000010,
    B01001010, B01000010,
    B01001010, B01000010,
    B01000010, B01000010,
    B01111110, B01111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Memory Match");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Memory Match");

  shuffle_flag = 1;
  while(1) {
    if(shuffle_flag) {
      // Перемешиваем
      for(i = 0; i < 30; i++) {
        buttons_show[i] = empty;
        j = random(0, 30);
        tmp = buttons[i];
        buttons[i] = buttons[j];
        buttons[j] = tmp;
      }
      steps = 0;
      shuffle_flag = 0;
      item_selected = -1;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "Level: %d", level);
    tft.drawString(buff, 8, 20, FONT_DEFAULT);

    sprintf(buff, "Steps: %d", steps);
    tft.drawString(buff, tft.width() / 2, 20, FONT_DEFAULT);

    drawButtonMatrix(0, 44, tft.width(), tft.height() - 44, buttons_show, 5, 6);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 44, tft.width(), tft.height() - 44, buttons_show, 5, 6);
    if(button_pressed != -1) {
      if(buttons_show[button_pressed] == empty) {
        if(item_selected == -1) {
          item_selected = button_pressed;
          buttons_show[button_pressed] = buttons[button_pressed];
        }
        else {
          if(button_pressed != item_selected) {
            buttons_show[button_pressed] = buttons[button_pressed];
            drawButtonMatrix(0, 44, tft.width(), tft.height() - 44, buttons_show, 5, 6);
            if(strcmp(buttons[button_pressed], buttons[item_selected])) {
              // Если отличаются
              delay(1000);
              buttons_show[button_pressed] = empty;
              buttons_show[item_selected] = empty;
            }
            item_selected = -1;
            steps++;
          }
        }
      }
    }

    won_flag = 1;
    for(i = 0; i < 30; i++) {
      if(buttons_show[i] == empty) won_flag = 0;
    }
    if(won_flag) {
      drawInfo("You won!");
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      shuffle_flag = 1;
      steps = 0;
      level++;
      won_flag = 0;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

#define HANOI_TOWERS_MAX_LEVEL 16

void hanoi_towers(char mode, char *io_buff) {
  TS_Point p;
  int touch_x, touch_y;
  int button_pressed;
  int i;
  int j;
  int level = 3;
  int steps = 0;
  int item_selected = -1;
  int column1, column2;
  char restart_flag = 1;
  char won_flag = 0;
  char buff[80];
  int towers[HANOI_TOWERS_MAX_LEVEL * 3];
  int colors[] = {
    TFT_BLACK, TFT_RED, TFT_GREEN, TFT_YELLOW,
    TFT_BLUE, TFT_MAGENTA, TFT_CYAN, TFT_WHITE,
    TFT_MAROON, TFT_DARKGREEN, TFT_OLIVE, TFT_NAVY,
    TFT_PURPLE, TFT_DARKCYAN, TFT_LIGHTGREY, TFT_DARKGREY,
    TFT_BLACK};
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000011, B11000010,
    B01000001, B10000010,
    B01000111, B11100010,
    B01000001, B10000010,
    B01001111, B11110010,
    B01000001, B10000010,
    B01011111, B11111010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Hanoi Towers");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Hanoi Towers");

  restart_flag = 1;
  while(1) {
    if(restart_flag) {
      // Инициализируем
      for(i = 0; i < HANOI_TOWERS_MAX_LEVEL * 3; i++) {
        towers[i] = 0;
      }
      for(i = 0; i < level; i++) {
        towers[i] = level - i;
      }
      steps = 0;
      restart_flag = 0;
      column1 = -1;
      column2 = -1;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "Level: %d", level);
    tft.drawString(buff, 8, 20, FONT_DEFAULT);

    sprintf(buff, "Steps: %d", steps);
    tft.drawString(buff, tft.width() / 2, 20, FONT_DEFAULT);

    // Рисуем поле
    tft.drawLine(0, tft.height() - 16, tft.width(), tft.height() - 16, TFT_BLACK);
    for(j = 0; j < 3; j++) {
      for(i = 0; i < HANOI_TOWERS_MAX_LEVEL; i++) {
        tft.fillRect(j * tft.width() / 3 + tft.width() / 6 - 8 - HANOI_TOWERS_MAX_LEVEL * 2, tft.height() - i * 16 - 32, 16 + HANOI_TOWERS_MAX_LEVEL * 4, 16, TFT_WHITE);
        if(towers[i + j * HANOI_TOWERS_MAX_LEVEL] > 0) {
          tft.drawRect(j * tft.width() / 3 + tft.width() / 6 - 8 - towers[i + j * HANOI_TOWERS_MAX_LEVEL] * 2, tft.height() - i * 16 - 32, 16 + towers[i + j * HANOI_TOWERS_MAX_LEVEL] * 4, 17, TFT_BLACK);
          tft.fillRect(j * tft.width() / 3 + tft.width() / 6 - 8 - towers[i + j * HANOI_TOWERS_MAX_LEVEL] * 2 + 1, tft.height() - i * 16 - 32 + 1, 16 + towers[i + j * HANOI_TOWERS_MAX_LEVEL] * 4 - 2, 17 - 2, colors[towers[i + j * HANOI_TOWERS_MAX_LEVEL]]);
          if(colors[towers[i + j * HANOI_TOWERS_MAX_LEVEL]] == TFT_BLACK) {
            tft.setTextColor(TFT_WHITE, colors[towers[i + j * HANOI_TOWERS_MAX_LEVEL]]);
          }
          else {
            tft.setTextColor(TFT_BLACK, colors[towers[i + j * HANOI_TOWERS_MAX_LEVEL]]);
          }
          sprintf(buff, "%d", towers[i + j * HANOI_TOWERS_MAX_LEVEL]);
          tft.drawCentreString(buff, j * tft.width() / 3 + tft.width() / 6 + 1, tft.height() - i * 16 - 32 + 5, FONT_MONOSPACE);
        }
        else {
          tft.fillRect(j * tft.width() / 3 + tft.width() / 6 - 2, tft.height() - i * 16 - 32, 4, 17, TFT_BLACK);
        }
      }
    }

    // Проверяем победу
    won_flag = 1;
    // Проверяем что левые два столбца пустые
    for(i = 0; i < 2 * HANOI_TOWERS_MAX_LEVEL; i++) {
      if(towers[i] != 0) won_flag = 0;
    }
    if(won_flag) {
      drawInfo("You won!");
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      restart_flag = 1;
      steps = 0;
      level = min(level + 1, HANOI_TOWERS_MAX_LEVEL);
      won_flag = 0;
      continue;
    }

    touchWaitPress();
    tft.fillRect(0, tft.height() - 15, tft.width(), 15, TFT_WHITE);
    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);

    if(column1 == -1) {
      column1 = touch_x / (tft.width() / 3);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawCentreString("^", column1 * tft.width() / 3 + tft.width() / 6, tft.height() - 15, FONT_DEFAULT);
    }
    else {
      column2 = touch_x / (tft.width() / 3);
      if(column1 == column2) {
        column1 = column2;
        column2 = -1;
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.drawCentreString("^", column1 * tft.width() / 3 + tft.width() / 6, tft.height() - 15, FONT_DEFAULT);
      }
      else {
        // Верхний элемент первого столбца
        i = HANOI_TOWERS_MAX_LEVEL - 1;
        while(i > 0) {
          if(towers[i + column1 * HANOI_TOWERS_MAX_LEVEL] != 0) break;
          i--;
        }
        // Верхний элемент второго столбца
        j = HANOI_TOWERS_MAX_LEVEL - 1;
        while(j > 0) {
          if(towers[j + column2 * HANOI_TOWERS_MAX_LEVEL] != 0) break;
          j--;
        }

        // Если можно переставлять, то переставляем
        if(towers[j + column2 * HANOI_TOWERS_MAX_LEVEL] == 0) {
          towers[j + column2 * HANOI_TOWERS_MAX_LEVEL] = towers[i + column1 * HANOI_TOWERS_MAX_LEVEL];
          towers[i + column1 * HANOI_TOWERS_MAX_LEVEL] = 0;
          steps++;
        }
        else if(towers[i + column1 * HANOI_TOWERS_MAX_LEVEL] < towers[j + column2 * HANOI_TOWERS_MAX_LEVEL]) {
          towers[j + 1 + column2 * HANOI_TOWERS_MAX_LEVEL] = towers[i + column1 * HANOI_TOWERS_MAX_LEVEL];
          towers[i + column1 * HANOI_TOWERS_MAX_LEVEL] = 0;
          steps++;
        }
        column1 = -1;
        column2 = -1;
        tft.fillRect(0, tft.height() - 15, tft.width(), 15, TFT_WHITE); 
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void lights_off(char mode, char *io_buff) {
  int button_pressed;
  int moves_remain;
  int i;
  char valid_move_flag;
  char shuffle_flag = 1;
  int level = 1;
  int steps = 0;
  char buff[80];
  char won_flag = 0;
  char *on = "on";
  char *off = "";
  char *buttons[] = {
    off, off, off, off, off,
    off, off, off, off, off,
    off, off, off, off, off,
    off, off, off, off, off,
    off, off, off, off, off,
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01011011, B00000010,
    B01011011, B00000010,
    B01000000, B00000010,
    B01011000, B00000010,
    B01011000, B00000010,
    B01000000, B00011010,
    B01000000, B00011010,
    B01000000, B00000010,
    B01000000, B11011010,
    B01000000, B11011010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Lights Off");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Lights Off");

  while(1) {
    if(shuffle_flag) {
      // Перемешиваем
      steps = 0;
      moves_remain = level;
      while(moves_remain > 0) {
        valid_move_flag = 0;
        button_pressed = random(0, 25);

        buttons[button_pressed] = buttons[button_pressed] == off ? on : off;
        if(button_pressed % 5 != 0) {
          buttons[button_pressed - 1] = buttons[button_pressed - 1] == off ? on : off;
        }
        if(button_pressed % 5 != 4) {
          buttons[button_pressed + 1] = buttons[button_pressed + 1] == off ? on : off;
        }
        if(button_pressed / 5 > 0) {
          buttons[button_pressed - 5] = buttons[button_pressed - 5] == off ? on : off;
        }
        if(button_pressed / 5 < 4) {
          buttons[button_pressed + 5] = buttons[button_pressed + 5] == off ? on : off;
        }
        
        moves_remain--;
      }
      shuffle_flag = 0;
    }

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    sprintf(buff, "Level: %d", level);
    tft.drawString(buff, 8, 20, FONT_DEFAULT);

    sprintf(buff, "Steps: %d", steps);
    tft.drawString(buff, tft.width() / 2, 20, FONT_DEFAULT);

    drawButtonMatrix(0, 64, tft.width(), tft.width(), buttons, 5, 5);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 64, tft.width(), tft.width(), buttons, 5, 5);
    if(button_pressed != -1) {
      buttons[button_pressed] = buttons[button_pressed] == off ? on : off;
      if(button_pressed % 5 != 0) {
        buttons[button_pressed - 1] = buttons[button_pressed - 1] == off ? on : off;
      }
      if(button_pressed % 5 != 4) {
        buttons[button_pressed + 1] = buttons[button_pressed + 1] == off ? on : off;
      }
      if(button_pressed / 5 > 0) {
        buttons[button_pressed - 5] = buttons[button_pressed - 5] == off ? on : off;
      }
      if(button_pressed / 5 < 4) {
        buttons[button_pressed + 5] = buttons[button_pressed + 5] == off ? on : off;
      }
      steps++;
    }
    drawButtonMatrix(0, 64, tft.width(), tft.width(), buttons, 5, 5);

    // Проверка выигрыша
    won_flag = 1;
    for(i = 0; i < 25; i++) {
      if(buttons[i] == on) won_flag = 0;
    }
    if(won_flag) {
      sprintf(buff, "You won level %d in %d steps", level, steps);
      drawInfo(buff);
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, TFT_WHITE);
      level++;
      shuffle_flag = 1;
      steps = 0;
      won_flag = 0;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

void piano(char mode, char *io_buff) {
  TS_Point p;
  int touch_x, touch_y;
  int i;
  char buff[80];
  int note_index;
  int active_note_index;
  float note_to_freq_white[] = {
    261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88,
    523.25, 587.33, 659.25, 698.46, 783.99, 880.00, 987.77,
    1046.50, 1174.66
    };
  float note_to_freq_black[] = {
    0, 277.18, 311.13, 0, 369.99, 415.30, 466.16,
    0, 554.36, 622.25, 0, 739.99, 830.61, 932.33,
    0, 1108.73
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000011, B11101110,
    B01000011, B11101110,
    B01000011, B11101110,
    B01000011, B11101110,
    B01000011, B11101110,
    B01000011, B11101110,
    B01000000, B10000010,
    B01000000, B10000010,
    B01000000, B10000010,
    B01000000, B10000010,
    B01000000, B10000010,
    B01000000, B10000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Piano");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Piano");

  // Рисуем клавиатуру
  // Белые
  for(i = 0; i < 16; i++) {
    tft.drawRect(i * tft.width() / 16, 240 - 32, tft.width() / 16, 64, TFT_BLACK);
  }
  // Чёрные
  for(i = 0; i < 16; i++) {
    if(i % 7 == 0) continue;
    if(i % 7 == 3) continue;
    tft.fillRect(i * tft.width() / 16 - tft.width() / 32 + 1, 240 - 32 + 1, tft.width() / 16 - 2, 32 - 2, TFT_BLACK);
  }
  while(1) {
    if(touchCheckNowait() == 0) {
      noTone(BUZZER_PIN);
      active_note_index = -1;
      continue;
    }
    else {
      do {
        p = touchscreen.getPoint();
        touch_x = touchMapX(p.x, p.y);
        touch_y = touchMapY(p.x, p.y);

        // Белые
        if(touch_y >= 240 && touch_y < 272) {
          note_index = touch_x / (tft.width() / 16);
          if(note_index != active_note_index) {
            tone(BUZZER_PIN, note_to_freq_white[note_index]);
            active_note_index = note_index;
          }
        }
        // Чёрные
        else if(touch_y >= 240 - 32 && touch_y < 240) {
          note_index = (touch_x + 8)/ (tft.width() / 16);
          if(note_index != active_note_index - 32) {
            tone(BUZZER_PIN, note_to_freq_black[note_index]);
            active_note_index = note_index + 32;
          }
        }
        else {
          noTone(BUZZER_PIN);
          active_note_index = -1;
        }
        if(global_exit_flag) {
          break;
        }
      } while(touchCheckNowait() == 1);
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

// ====================================================
// Начиная отсюда идут общие функции
// ====================================================

// Нахождение определителя матрицы третьего порядка
double det3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33) {
  return
      x11 * x22 * x33
    + x12 * x23 * x31
    + x13 * x21 * x32
    - x13 * x22 * x31
    - x12 * x21 * x33
    - x11 * x23 * x32;
}

// Сохраняет скриншот в папку скриншотов
void saveScreenshot() {
  fs::File file;
  int x;
  int y;
  int i;
  char buff[80];
  char filename[80];
  char byte;
  int pixel_color;
  unsigned char bmp_header[118] = {
    0x42, 0x4D, 0x76, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x40, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x96,
    0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00
  };
  int colors[] = {
    TFT_BLACK, TFT_MAROON, TFT_DARKGREEN, TFT_OLIVE,
    TFT_NAVY, TFT_PURPLE, TFT_DARKCYAN, TFT_LIGHTGREY,
    TFT_DARKGREY, TFT_RED, TFT_GREEN, TFT_YELLOW,
    TFT_BLUE, TFT_MAGENTA, TFT_CYAN, TFT_WHITE};
  int color_index;
  
  tone(BUZZER_PIN, 1000, 100);

  // Создать папку если её ещё нет
  file = Storage.open("/Screenshots");
  if(!file) {
    Storage.mkdir("/Screenshots");
  }
  else {
    file.close();
  }

  // Ищем несущестующее имя файла
  i = 0;
  while(1) {
    sprintf(filename, "/Screenshots/%d.bmp", i);
    file = Storage.open(filename);
    if(file) {
      file.close();
    }
    else {
      break;
    }
    i++;
  }

  // Сохраняем скриншот
  file = Storage.open(filename, FILE_WRITE);
  file.write((const uint8_t *)bmp_header, 118);

  // Записываем данные изображения с экрана
  x = 0;
  y = tft.height() - 1;
  while(y >= 0) {
    // Половина ширины картинки (120) должна без остатка делиться на размер буфера
    for(i = 0; i < 60; i++) {
      byte = 0;
      pixel_color = tft.readPixel(x, y);
      for(color_index = 0; color_index < 16; color_index++) {
        if(pixel_color == colors[color_index]) break;
      }
      byte |= color_index << 4;
      x++;
      pixel_color = tft.readPixel(x, y);
      for(color_index = 0; color_index < 16; color_index++) {
        if(pixel_color == colors[color_index]) break;
      }
      byte |= color_index;
      x++;
      //file.write(byte);
      buff[i] = byte;
    }
    
    file.write((const uint8_t *)buff, 60);

    if(x >= tft.width()) {
      // Мигаем светодиодом для индикации прогресса
      digitalWrite(LED_RED, y % 2);
      x = 0;
      y--;
    }
  }

  file.close();

  tone(BUZZER_PIN, 1000, 100);
  digitalWrite(LED_RED, HIGH);
}

void clearScreen() {
  tft.fillScreen(TFT_WHITE);
}

void drawAppTitle(char *name) {
  char buff[80];
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.fillRect(0, 0, tft.width(), 16, TFT_BLUE);
  tft.drawString(name, 16, 0, FONT_DEFAULT);
  // Рисовать время в заголовке неплохая идея, но тогда надо ещё заголовок постоянно обновлять
  /*
  if(global_unixtime_retrieved > 0) {
    sprintf(buff, "%d:%02d", global_hours, global_minutes);
    tft.drawRightString(buff, tft.width() - 16, 0, FONT_DEFAULT);
  }
  */
}

void drawError(char *message) {
  char *buttons[] = { "OK", NULL };
  tone(BUZZER_PIN, 1000, 100);
  drawPopoupWindowWaitReply("Error", message, buttons);
}

void drawAlert(char *message) {
  char *buttons[] = { "OK", NULL };
  tone(BUZZER_PIN, 1000, 100);
  drawPopoupWindowWaitReply("Alert", message, buttons);
}

void drawInfo(char *message) {
  char *buttons[] = { "OK", NULL };
  tone(BUZZER_PIN, 1000, 100);
  drawPopoupWindowWaitReply("Info", message, buttons);
}

int drawConfirm(char *message) {
  char *buttons[] = { "OK", "Cancel", NULL };

  tone(BUZZER_PIN, 1000, 100);

  return drawPopoupWindowWaitReply("Confirm", message, buttons);
}

#define PROMPT_OFFSET_Y 100

int drawPrompt(char *message, char *user_input) {
  char *buttons[] = { "OK", "Cancel", NULL };

  int button = 0;
  char caps_flag = 0;
  char symbol_flag = 0;
  char alt_flag = 0;
  char input[80] = "";
  char visible_input[80];
  int cursor_pos = 0;
  int i;

  char *keyboard_nocaps[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "-",
    ":shift:", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", ":enter:",
    ":change:", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", " ",
    NULL
  };
  char *keyboard_caps[] = {
    "~",  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", ":backspace:",
    " ", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "_",
    ":shift:", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", ":enter:",
    ":change:", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", " ",
    NULL
  };
  char *keyboard_symbol[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ",  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "=",
    ":shift:", "[", "]", "<", ">", ".", ",", ":", ";", "\"", "'", ":enter:",
    ":change:", "{", "}", "+", "-", "*", "/", "\\", "~", "|", "?", " ",
    NULL
  };
  char *keyboard_alt_nocaps[] = {
    "\xB8",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    "\xE9", "\xF6", "\xF3", "\xEA", "\xE5", "\xED", "\xE3", "\xF8", "\xF9", "\xE7", "\xF5", "\xFA",
    ":shift:", "\xF4", "\xFB", "\xE2", "\xE0", "\xEF", "\xF0", "\xEE", "\xEB", "\xE4", "\xE6", ":enter:",
    ":change:", "\xFF", "\xF7", "\xF1", "\xEC", "\xE8", "\xF2", "\xFC", "\xE1", "\xFE", "\xFD", " ",
    NULL
  };
  char *keyboard_alt_caps[] = {
    "\xA8",  "!", "\"", "\xB9", ";", "%", ":", "?", "*", "(", ")", ":backspace:",
    "\xC9", "\xD6", "\xD3", "\xCA", "\xC5", "\xCD", "\xC3", "\xD8", "\xD9", "\xC7", "\xD5", "\xDA",
    ":shift:", "\xD4", "\xDB", "\xC2", "\xC0", "\xCF", "\xD0", "\xCE", "\xCB", "\xC4", "\xC6", ":enter:",
    ":change:", "\xDF", "\xD7", "\xD1", "\xCC", "\xC8", "\xD2", "\xDC", "\xC1", "\xDE", "\xDD", " ",
    NULL
  };
  char **keyboard_current = keyboard_nocaps;

  tone(BUZZER_PIN, 1000, 100);

  strcpy(input, user_input);
  
  // Рамка
  tft.drawRect(0, PROMPT_OFFSET_Y, tft.width(), 220, TFT_BLACK);
  // Белый фон
  tft.fillRect(1, PROMPT_OFFSET_Y + 1, tft.width() - 2, 218, TFT_WHITE);
  // Фон заголовка
  tft.fillRect(1, PROMPT_OFFSET_Y + 1, tft.width() - 2, 16, TFT_BLUE);
  // Заголовок
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.drawString(message, 16, PROMPT_OFFSET_Y + 1, FONT_DEFAULT);
  
  while(1) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.fillRect(1, PROMPT_OFFSET_Y + 20, tft.width() - 2, 16, TFT_WHITE);
    strcpy(visible_input, input);
    while(tft.textWidth(visible_input, FONT_DEFAULT) > tft.width() - 8 * 2) {
      for(i = 0; i < strlen(visible_input); i++) {
        visible_input[i] = visible_input[i + 1];
      }
    }
    cursor_pos = tft.drawString(visible_input, 8, PROMPT_OFFSET_Y + 20, FONT_DEFAULT);
    //tft.setTextColor(TFT_BLUE, TFT_WHITE);
    tft.fillRect(8 + cursor_pos + 1, PROMPT_OFFSET_Y + 20, 2, 16, TFT_BLUE);

    drawButtonMatrix(8, PROMPT_OFFSET_Y + 180, tft.width() - 8 * 2, 32, buttons, 3, 1);

    if(symbol_flag) {
      keyboard_current = keyboard_symbol;
    }
#ifdef ALT_KEYBOARD_ENABLED
    else if(caps_flag) {
      if(alt_flag) {
        keyboard_current = keyboard_alt_caps;
      }
      else {
        keyboard_current = keyboard_caps;
      }
    }
    else {
      if(alt_flag) {
        keyboard_current = keyboard_alt_nocaps;
      }
      else {
        keyboard_current = keyboard_nocaps;
      }
    }
#else
    else if(caps_flag) {
      keyboard_current = keyboard_caps;
    }
    else {
      keyboard_current = keyboard_nocaps;
    }
#endif

    drawButtonMatrix(0, PROMPT_OFFSET_Y + 40, tft.width(), 120, keyboard_current, 12, 4);
    
    touchWaitPress();
    button = touchCheckMatrix(0, PROMPT_OFFSET_Y + 40, tft.width(), 120, keyboard_current, 12, 4);
    if(button != -1) {
      if(button == 11) {
        if(strlen(input) > 0) {
          input[strlen(input) - 1] = 0;
        }
      }
      // Tab ?
      //else if(button == 12) {
      //}
      else if(button == 24) {
        caps_flag = !caps_flag;
      }
      else if(button == 35) {
        if(strlen(input) >= 79) continue;
        strcat(input, "\n");
      }
      else if(button == 36) {
        symbol_flag = !symbol_flag;
        if(!symbol_flag) {
          if(alt_flag) {
            alt_flag = 0;
          }
          else {
            alt_flag = 1;
          }
        }
      }
      else {
        if(strlen(input) >= 79) continue;
        strcat(input, keyboard_current[button]);
        caps_flag = 0;
      }
    }

    // Проверка кнопок завершения
    button = touchCheckMatrix(8, PROMPT_OFFSET_Y + 180, tft.width() - 8 * 2, 32, buttons, 3, 1);
    if(button == 0) {
      strcpy(user_input, input);
      return 0;
    }
    if(button == 1) {
      return 1;
    }
  }
}

int drawPopoupWindowWaitReply(char *title, char *message, char **buttons) {
  int reply;
  drawPopupWindow(title, message, buttons);

  while(1) {
    touchWaitPress();
    reply = touchCheckMatrix(8, 240 - 40, tft.width() - 8 * 2, 32, buttons, 3, 1);
    touchWaitRelease();
    if(reply != -1) break;
  }
  return reply;
}

void drawPopupWindow(char *title, char *message, char **buttons) {
  // Рамка
  tft.drawRect(0, 120, tft.width(), 120, TFT_BLACK);
  // Белый фон
  tft.fillRect(1, 121, 238, 118, TFT_WHITE);
  // Фон заголовка
  tft.fillRect(1, 121, 238, 16, TFT_BLUE);
  // Заголовок
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.drawString(title, 16, 121, FONT_DEFAULT);
  
  // Надпись
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString(message, 8, 121 + 16, FONT_DEFAULT);

  // Кнопки в один ряд
  drawButtonMatrix(8, 240 - 40, tft.width() - 8 * 2, 32, buttons, 3, 1);
}

void checkPasswordUntilCorrect(char *correct_password) {
  fs::File file;
  int i;
  int button;
  int button1, button2;
  char user_input[80] = "";
  char owner_info[80] = "";
  int offset = 0;
  char *tmp;
  char *buttons[] = {
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9",
    "<-", "0", "OK",
    NULL
  };

  clearScreen();
  drawAppTitle("Enter Password");

  // Читаем информацию о владельце
  file = Storage.open("/Settings/Owner");
  if(file) {
    offset = 0;
    owner_info[0] = 0;
    while(file.available()) {
      owner_info[offset] = file.read();
      offset++;
      owner_info[offset] = 0;
      if(offset == 79) break;
    }
    file.close();
  }

  // Перемешать кнопки (чтобы нельзя было узнать пароль по царапинам на экране)
  for(i = 0; i < 100; i++) {
    button1 = random(0, 12);
    button2 = random(0, 12);
    if(button1 == 9 || button1 == 11) continue;
    if(button2 == 9 || button2 == 11) continue;
    tmp = buttons[button1];
    buttons[button1] = buttons[button2];
    buttons[button2] = tmp;
  }

  while(1) {
    // Нарисовать звёздочки по числу символов
    tft.fillRect(0, 16, tft.width(), 60, TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    for(i = 0; i < strlen(user_input); i++) {
      if(8 + i * tft.textWidth("*", FONT_BIG) < tft.width()) {
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.drawString("*", 8 + i * tft.textWidth("*", FONT_BIG), 58, FONT_BIG);
      }
    }
    tft.drawString("Owner info:", 8, 20, FONT_DEFAULT);
    tft.drawString(owner_info, 8, 36, FONT_DEFAULT);

    // Нарисовать кнопки
    drawButtonMatrix(8, 100 - 8, tft.width() - 8 * 2, 220, buttons, 3, 4);

    touchWaitPress();
    button = touchCheckMatrix(8, 100 - 8, tft.width() - 8 * 2, 220, buttons, 3, 4);
    if(button != -1) {
      if(!strcmp(buttons[button], "OK")) {
        if(!strcmp(correct_password, user_input)) {
           return;
        }
        else {
          drawAlert("Wrong password!");
          //drawInfo(correct_password);
          strcpy(user_input, "");
          tft.fillRect(0, 16, tft.width(), tft.height() - 20, TFT_WHITE);
        }
      }
      else if(!strcmp(buttons[button], "<-")) {
        if(strlen(user_input) > 0) {
          user_input[strlen(user_input) - 1] = 0;
        }
      }
      else {
        strcat(user_input, buttons[button]);
      }
    }
    touchWaitRelease();
  }
}

void drawButtonMatrix(int left_x, int top_y, int width, int height, char **str, int cols, int rows) {
  int x;
  int y;
  char is_eol = 0;
  for(y = 0; y < rows; y++) {
    for(x = 0; x < cols; x++) {
      if(!is_eol) {
        if(str[x + y * cols]) {
          tft.drawRect(left_x + x * width / cols + 1, top_y + y * height / rows + 1, width / cols - 2, height / rows - 2, TFT_BLACK);
          tft.fillRect(left_x + x * width / cols + 2, top_y + y * height / rows + 2, width / cols - 4, height / rows - 4, TFT_LIGHTGREY);
          if(!strcmp(str[x + y * cols], ":enter:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, enter, TFT_BLACK, TFT_LIGHTGREY);
          }
          else if(!strcmp(str[x + y * cols], ":backspace:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, backspace, TFT_BLACK, TFT_LIGHTGREY);
          }
          else if(!strcmp(str[x + y * cols], ":shift:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, shift, TFT_BLACK, TFT_LIGHTGREY);
          }
          else if(!strcmp(str[x + y * cols], ":change:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, change_keyboard, TFT_BLACK, TFT_LIGHTGREY);
          }
          else {
            tft.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
            tft.drawCentreString(str[x + y * cols], left_x + (x + 0.5) * width / cols + 1, top_y + (y + 0.5) * height / rows - 8, FONT_DEFAULT);
          }
        }
        else {
          is_eol = 1;
        }
      }
    }
  }
}

int touchCheckMatrix(int left_x, int top_y, int width, int height, char **str, int cols, int rows) {
  int x;
  int y;
  int touch_x;
  int touch_y;
  int bg_color;
  int prev_color;
  char is_eol = 0;
  char is_touch;
  char is_inside;
  TS_Point p;
  if(!touchscreen.tirqTouched() || !touchscreen.touched()) return -1;

  p = touchscreen.getPoint();
  touch_x = touchMapX(p.x, p.y);
  touch_y = touchMapY(p.x, p.y);

  for(y = 0; y < rows; y++) {
    for(x = 0; x < cols; x++) {
      if(!is_eol) {
        if(str[x + y * cols]) {
          if(left_x + x * width / cols + 1 <= touch_x && touch_x <= left_x + (x + 1) * width / cols - 1
            && top_y + y * height / rows + 1 <= touch_y && touch_y <= top_y + (y + 1) * height / rows - 1
          ) {
            // Если пользователь отпустил кнопку внутри кнопки - засчитать срабатывание
            while(1) {
              is_touch = touchCheckNowait();
              if(left_x + x * width / cols + 1 <= touch_x && touch_x <= left_x + (x + 1) * width / cols - 1
              && top_y + y * height / rows + 1 <= touch_y && touch_y <= top_y + (y + 1) * height / rows - 1) {
                is_inside = 1;
              }
              else {
                is_inside = 0;
              }
              bg_color = TFT_LIGHTGREY;
              if(is_touch) {
                p = touchscreen.getPoint();
                touch_x = touchMapX(p.x, p.y);
                touch_y = touchMapY(p.x, p.y);
                if(is_inside) {
                  bg_color = TFT_DARKGREY;
                }
              }
              
              if(prev_color != bg_color) {
                tft.drawRect(left_x + x * width / cols + 1, top_y + y * height / rows + 1, width / cols - 2, height / rows - 2, TFT_BLACK);
                tft.fillRect(left_x + x * width / cols + 2, top_y + y * height / rows + 2, width / cols - 4, height / rows - 4, bg_color);
                if(!strcmp(str[x + y * cols], ":enter:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, enter, TFT_BLACK, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":backspace:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, backspace, TFT_BLACK, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":shift:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, shift, TFT_BLACK, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":change:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, change_keyboard, TFT_BLACK, bg_color);
                }
                else {
                  tft.setTextColor(TFT_BLACK, bg_color);
                  tft.drawCentreString(str[x + y * cols], left_x + (x + 0.5) * width / cols + 1, top_y + (y + 0.5) * height / rows - 8, FONT_DEFAULT);
                }
              prev_color = bg_color;
              }
              delay(50);
              if(!is_touch) {
                if(is_inside) {
                  return x + y * cols;
                }
                else {
                  return -1;
                }
              }
            }
          }
        }
        else {
          is_eol = 1;
        }
      }
    }
  }
  return -1;
}

void drawList(int left_x, int top_y, int width, int height, char **str, int rows_to_show, int *offset, int *selected) {
  int y;
  int last_row = 0;
  char is_eol = 0;
  char up[] = " [scroll up] ";
  char down[] = " [scroll down] ";
  char left[80];
  char right[80];
  // Для прокрутки нужно знать количество строк
  for(last_row = 0; str[last_row] != NULL; last_row++) {}
  last_row--;

  if(rows_to_show + *offset > last_row) {
    *offset = last_row - rows_to_show + 1;
  }
  if(*offset < 0) {
    *offset = 0;
  }

  // Пустой список - показываем что тут мог быть список
  if(str[0] == NULL) {
    tft.setTextColor(TFT_LIGHTGREY, TFT_WHITE);
    tft.drawString("<empty list>", left_x + 1, top_y, FONT_DEFAULT);
    return;
  }

  for(y = 0; y < rows_to_show; y++) {
    if(!is_eol) {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      // Если нужно показать [up]
      if(y == 0 && *offset > 0) {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        tft.drawString(up, left_x + 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
      }
      // Если нужно показать [down]
      else if(y == (rows_to_show - 1) && (*offset + rows_to_show) <= last_row) {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        tft.drawString(down, left_x + 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
      }
      else if(str[y + *offset]) {
        if(y + *offset == *selected) {
          tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_BLUE);
          tft.setTextColor(TFT_WHITE, TFT_BLUE);
        }
        else {
          tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        }
        getListItemParts(str[y + *offset], left, right);
        if(!strcmp(left, "") && !strcmp(right, "")) {
          tft.drawString("<empty>", left_x + 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
        }
        else {
          while(tft.textWidth(left, FONT_DEFAULT) + tft.textWidth(right, FONT_DEFAULT) > width - 2) {
            if(strlen(left) > 5) {
              left[strlen(left) - 1] = 0;
            }
            else {
              right[strlen(right) - 1] = 0;
            }
          }
          tft.drawString(left, left_x + 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
          tft.drawRightString(right, left_x + width - 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
        }
      }
      else {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        is_eol = 1;
      }
    }
    else {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
    }
  }
}

void getListItemParts(char *item, char *left, char *right) {
  char *tab_ptr;
  int left_flag = 1;
  strcpy(left, item);
  strcpy(right, "");
  tab_ptr = strchr(left, '\t');
  if(tab_ptr) {
    *tab_ptr = 0;
    strcpy(right, tab_ptr + 1);
  }
}

int touchCheckList(int left_x, int top_y, int width, int height, char **str, int rows_to_show, int *offset, int *selected) {
  int y;
  int last_row = 0;
  char up[] = " [scroll up] ";
  char down[] = " [scroll down] ";
  char match = 0;

  int touch_x;
  int touch_y;
  TS_Point p;
  
  if(!touchscreen.tirqTouched() || !touchscreen.touched()) return -1;

  p = touchscreen.getPoint();
  touch_x = touchMapX(p.x, p.y);
  touch_y = touchMapY(p.x, p.y);

  // Для прокрутки нужно знать количество строк
  for(last_row = 0; str[last_row] != NULL; last_row++) {}
  last_row--;

  if(rows_to_show + *offset > last_row) {
    *offset = last_row - rows_to_show + 1;
  }
  if(*offset < 0) {
    *offset = 0;
  }

  for(y = 0; y < rows_to_show; y++) {
    if(!str[y + *offset]) {
      break;
    }

    match = 0;
    // Если попадает в очередной пункт
    if(touch_x >= left_x && touch_x < (left_x + width)
      && touch_y >= top_y + y * height / rows_to_show
      && touch_y < top_y + (y + 1) * height / rows_to_show) {
        match = 1;
      }
    if(!match) continue;

    // Если нажато [up]
    if(y == 0 && *offset > 0) {
      *offset -= (rows_to_show - 2);
      return y;
    }
    // Если нажато [down]
    else if(y == (rows_to_show - 1) && (*offset + rows_to_show) <= last_row) {
      *offset += (rows_to_show - 2);
      return y;
    }
    else if(str[y + *offset]) {
      *selected = y + *offset;
      return y;
    }
  }
  return -1;
}

// Простые функции тач-скрина

int touchMapX(int x, int y) {
  return ax * x + bx * y + cx;
}

int touchMapY(int x, int y) {
  return ay * x + by * y + cy;
}

char touchIsExitAction() {
  // Уже стоит флаг
  if(global_exit_flag) {
    return 1;
  }

  // Нет касания
  if(!touchscreen.tirqTouched() || !touchscreen.touched()) {
    global_exit_flag_touch_begin = 0;
    return 0;
  }
  
  if(global_exit_flag_touch_begin == 0) {
    global_exit_flag_touch_begin = millis();
  }

  // Касание сместилось
  global_touch_p = touchscreen.getPoint();
  global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
  global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);

  // Мимо заголовка?
  if(global_touch_y < 0 || global_touch_y >= 32) {
    global_exit_flag_touch_begin = 0;
    global_exit_flag_touch_length = 0;
    return 0;
  }

  global_exit_flag_touch_length = millis() - global_exit_flag_touch_begin;

  // Если все условия выполнились - сообщаем о сигнале на выход
  //Serial.println(global_exit_flag_touch_length);
  if(global_exit_flag_touch_length >= 1000) {
    global_exit_flag_touch_begin = 0;
    global_exit_flag_touch_length = 0;
    global_exit_flag = 1;
    return 1;
  }
  return 0;
}

void touchExitActionReset() {
  global_exit_flag = 0;
  global_exit_flag_touch_begin = 0;
  global_exit_flag_touch_length = 0;
}

void touchWaitPress() {
  while(!touchscreen.tirqTouched() || !touchscreen.touched()) {
    global_exit_flag_touch_begin = 0;
    if(global_exit_flag) return;
    if(digitalRead(BOOT_BUTTON_PIN) == LOW) saveScreenshot();
  }
  global_touch_begin = millis();
  delay(20);
  global_touch_p = touchscreen.getPoint();
  global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
  global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);
  global_touch_present_flag = 1;
}

void touchWaitReleaseOrExit() {
  while(touchscreen.tirqTouched() && touchscreen.touched()) {
    global_touch_p = touchscreen.getPoint();
    global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
    global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);
    global_touch_length = millis() - global_touch_begin;
    touchIsExitAction();
    if(global_exit_flag) break;
  }
  global_touch_present_flag = 0;
}

void touchWaitRelease() {
  while(touchscreen.tirqTouched() && touchscreen.touched()) {
    global_touch_p = touchscreen.getPoint();
    global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
    global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);
    global_touch_length = millis() - global_touch_begin;
    touchIsExitAction();
  }
  global_touch_present_flag = 0;
}

char touchCheckNowait() {
  if(digitalRead(BOOT_BUTTON_PIN) == LOW) saveScreenshot();
  // Проверить касание без блокировки
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    if(!global_touch_present_flag) {
      global_touch_present_flag = 1;
      global_touch_begin = millis();
    }
    global_touch_p = touchscreen.getPoint();
    global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
    global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);
    global_touch_length = millis() - global_touch_begin;

    touchIsExitAction();
    return 1;
  }
  else {
    global_touch_length = 0;
    if(global_touch_present_flag) {
      global_touch_present_flag = 0;
    }
    return 0;
  }
}

/*
Прочитать файл в буфер
filename - имя файла
limit - максимальное количество символов, -1 без ограничений
buff - буфер
*/
char read_file_to_buff(char *filename, int limit, char *buff) {
  fs::File file;
  char byte;
  int offset;
  file = Storage.open(filename);
  offset = 0;
  buff[offset] = 0;
  if(file) {
    while(file.available()) {
      byte = file.read();
      buff[offset] = byte;
      offset++;
      buff[offset] = 0;
      if(limit != -1 && offset >= limit) break;
    }
    return 1;
  }
  return 0;
}

// Записать небольшой файл из буфера
int write_file_from_buff(char *filename, char *buff) {
  fs::File file;
  int offset = 0;
  file = Storage.open(filename, FILE_WRITE);
  if(file) {
    while(buff[offset]) {
      file.print(buff[offset]);
      offset++;
    }
    file.close();
    return 1;
  }
  return 0;
}

// Прочитать значение ключа из файла
int read_key_value_from_file(char *filename, char *key, char *value) {
  fs::File file;
  int offset = 0;
  char str[80];
  char byte;
  file = Storage.open(filename);
  strcpy(value, "");
  if(file) {
    while(file.available()) {
      // Читаем строку
      offset = 0;
      while(file.available()) {
        byte = file.read();
        if(byte == '\n' && file.peek() == '\r') file.read();
        if(byte == '\r' && file.peek() == '\n') file.read();
        if(byte == '\n' || byte == '\r') break;
        str[offset] = byte;
        offset++;
        str[offset] = 0;
      }
      // Если строка совпадает с ключом, то копируем значение в буфер
      if(!memcmp(key, str, strlen(key)) && str[strlen(key)] == '=') {
        strcpy(value, str + strlen(key) + 1);
        return 1;
      }
    }
    file.close();
    return 0;
  }
  return 0;
}

int write_key_value_to_file(char *filename, char *key, char *value) {
  fs::File new_file;
  fs::File old_file;
  int offset = 0;
  char buff[80];
  char str[80];
  char old_filename[80];
  char byte;
  sprintf(old_filename, "%s_old", filename);
  Storage.rename(filename, old_filename);
  new_file = Storage.open(filename, FILE_WRITE);
  old_file = Storage.open(old_filename);

  if(new_file) {
    while(old_file && old_file.available()) {
      // Читаем строку
      offset = 0;
      while(old_file.available()) {
        byte = old_file.read();
        str[offset] = byte;
        offset++;
        str[offset] = 0;
        if(byte == '\n' && old_file.peek() == '\r') old_file.read();
        if(byte == '\r' && old_file.peek() == '\n') old_file.read();
        if(byte == '\n' || byte == '\r') break;
      }
      if(memcmp(key, str, strlen(key)) || str[strlen(key)] != '=') {
        new_file.print(str);
      }
    }
    // Записываем новые ключ и значение
    sprintf(buff, "%s=%s", key, value);
    new_file.println(buff);

    new_file.close();
    old_file.close();
    Storage.remove(old_filename);
    return 1;
  }
  return 0;
}

int get_brightness() {
  return global_brightness;
}

void set_brightness(int level) {
  global_brightness = level;
  analogWrite(BACKLIGHT_LED, level);
}

void save_brightness() {
  char buff[80];
  sprintf(buff, "%d", global_brightness);
  write_file_from_buff("/Settings/Brightness", buff);
}

void image_from_bits(int start_x, int start_y, char *image, int color, int bg_color) {
  int byte_index, bit_index;
  int x, y;
  char bit;
  int width = (int)image[0];
  int height = (int)image[1];
  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      byte_index = (width - x - 1 + y * width) / 8 + 2;
      bit_index = (x + y * width) % 8;
      bit = image[byte_index] & (1 << bit_index);
      tft.drawPixel(start_x + width - x - 1, start_y + y, bit ? color : bg_color);
    }
  }
}

void setup() {
  fs::File file;
  char byte;
  char buff[80];
  char autorun_app_name[80];
  int offset;
  int i;
  char calibration_required = 0;
  char password_present;
  char fs_present = 0;

  Serial.begin(115200);

  // Output pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BACKLIGHT_LED, OUTPUT);

  pinMode(LIGHT_SENSOR, INPUT);

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(2);

  // Инициализация экрана, 
  tft.init();
  tft.setRotation(2);
  clearScreen();

  // Инициализация FFat/SD
    // Инициализация SD
#ifdef USE_SD_AS_STORAGE
  sdSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, sdSPI)) {
    Serial.println("SD Card initialization failed!");
    fs_present = 0;
  }
  else {
    Serial.println("SD Card ok!");
    fs_present = 1;
  }
#else
  if (FFat.begin(FORMAT_FS_IF_FAILED)) {
    fs_present = 1;
  }
  else {
    fs_present = 0;
  }
#endif

  // Яркость
  global_brightness = 255;
  if(fs_present && read_file_to_buff("/Settings/Brightness", 79, buff)) {
    sscanf(buff, "%d", &global_brightness);
    set_brightness(global_brightness);
  }

  // Калибровка сенсора, если нужно
  calibration_required = 1;
  if(fs_present && read_file_to_buff("/Settings/Calibration", 79, buff)) {
    calibration_required = 0;
    ax = 0;
    sscanf(buff, "%f %f %f %f %f %f", &ax, &bx, &cx, &ay, &by, &cy);
  }
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    calibration_required = 1;
  }

  if(calibration_required) {
    touch_calibration(APP_MODE_LAUNCH, NULL);
  }

  // Тут можно задавать вопросы - сенсор откалиброван
#ifndef USE_SD_AS_STORAGE
  if(!fs_present) {
    drawError("FFat mount failed");
    if(drawConfirm("Format FFat?") == 0) {
        FFat.format();
        FFat.begin(FORMAT_FS_IF_FAILED);
        Storage.mkdir("/Settings");
    }
    touch_calibration_save();
  }
#endif

  // Тут можно спросить пароль
  if(read_file_to_buff("/Settings/Password", 79, buff)) {
    password_present = 1;
    for(offset = 0; offset < strlen(buff); offset++) {
      if(buff[offset] && (buff[offset] < '0' || buff[offset] > '9')) {
          password_present = 0;
      }
    }
    if(password_present) {
      checkPasswordUntilCorrect(buff);
    }
  }

  if(read_file_to_buff("/Settings/Coordinates", 79, buff)) {
    sscanf(buff, "%f %f", &global_lat, &global_lon);
  }

#ifdef IS_WIFI_ENABLED
  WiFi.begin();
#endif

  // Получить текущее время из сохранённого в ФС
  get_current_timestamp_fs();
  get_current_timezone();

  tone(BUZZER_PIN, 1000, 100);

  // Читаем информацию об автозапуске
  autorun_app_name[0] = 0;
  if(read_file_to_buff("/Settings/Autorun", 79, autorun_app_name)) {
    if(strcmp(autorun_app_name, "")) {
      // Если он есть, ищем название приложения и запускаем
      i = 0;
      while(apps[i]) {
        apps[i](APP_MODE_RETURN_NAME, buff);
        if(strcmp(buff, autorun_app_name) == 0) {
          apps[i](APP_MODE_LAUNCH, NULL);
        }
        i++;
      }
    }
  }
  
  // Ставим приложения
  for(i = 0; i < 40; i++) {
    main_apps[i] = apps[i];
  }
}

void loop() {
  apps[0](APP_MODE_LAUNCH, NULL);
}
