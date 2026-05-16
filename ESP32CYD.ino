/*
Что-то вроде КПК для ESP32 CYD (Cheap Yellow Display/Device)

Предположения:
- Ориентация экрана вертикальная
- ФС FFat
- Папка настроек /Settings

Функции:
- Лаунчер
- Калькулятор
- Информация о системе
- Файловый менеджер
- Виртуальная клавиатура
- Фонарик
- Калибровка тач-сенсора
- Рисование
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

Направления работы:
- Русский шрифт маленький и средний, русская клавиатура
- Вай-фай сервисы
- PIM-приложения
- Поддержка SD
- Больше приложений
- Больше игр
- Больше заставок
- Больше настроек
*/

//#define IS_WIFI_ENABLED

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "FS.h"
#include "FFat.h"

#ifdef IS_WIFI_ENABLED

#include "WiFi.h"
#include <HTTPClient.h>

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

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH tft.width()
#define SCREEN_HEIGHT tft.height()

#define FONT_TRUETYPE 1
#define FONT_DEFAULT 2
#define FONT_BIG 4
#define FONT_BIGGER 6
#define FONT_BIG_SEGMENT 7
#define FONT_BIGGEST 8

#define LED_RED 4
#define LED_GREEN 16
#define LED_BLUE 17

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

long global_touch_begin;
long global_touch_length;
TS_Point global_touch_p;
int global_touch_x;
int global_touch_y;
char global_touch_present_flag;
char global_exit_flag;
int brightness;

void launcher(char mode, char *io_buff);
void calculator(char mode, char *io_buff);
void system_info(char mode, char *io_buff);
void files(char mode, char *io_buff);
void keyboard(char mode, char *io_buff);
void torch(char mode, char *io_buff);
void draw(char mode, char *io_buff);
void wifi(char mode, char *io_buff);
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

typedef void (*app_pointer) (char mode, char *io_buff);

app_pointer apps[] = {
  launcher,
  calculator,
  files,
  system_info,
  torch,
  draw,
#ifdef IS_WIFI_ENABLED
  wifi,
#endif
  counter,
  random_numbers,
  timer,
  stopwatch_app,
  breathe,
  screen_test,
  screensaver,
  security,
  brightness_app,
  touch_calibration,
  fifteen,
  lights_off,
  NULL
};

void launcher(char mode, char *io_buff) {
  int touch_x;
  int touch_y;
  if(mode == 0) {
    strcpy(io_buff, "Launcher");
    return;
  }
  
  clearScreen();
  drawAppTitle("Launcher");

  int i;
  char app_name[80];
  int apps_eol = 0;
  for(i = 1; i < 20; i++) {
    if(!apps_eol) {
      if(apps[i]) {
        apps[i](0, app_name);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.drawString(app_name, 8, i * 16, FONT_DEFAULT);
      }
      else {
        apps_eol = i;
      }
    }
  }

  while(1) {
    global_exit_flag = 0;
    touchWaitPress();

    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);

    i = touch_y / 16;

    if(i > 0 && i < apps_eol) {
      apps[i](0, app_name);
      tft.fillRect(0, i * 16, tft.width(), 16, TFT_BLUE);
      tft.setTextColor(TFT_WHITE, TFT_BLUE);
      tft.drawString(app_name, 8, i * 16, FONT_DEFAULT);
      delay(100);
      touchWaitRelease();

      tft.fillRect(0, i * 16, tft.width(), 16, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString(app_name, 8, i * 16, FONT_DEFAULT);

      apps[i](1, NULL);
      break;
    }
  }
}

void calculator(char mode, char *io_buff) {
  double a = 0;
  double b = 0;
  double m = 0;
  double multiplier_a;
  double multiplier_b;

  char screen[20];
  char error_flag = 0;
  char dot_flag = 0;
  int dot_power = 0;
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

  if(mode == 0) {
    strcpy(io_buff, "Calculator");
    return;
  }
  // Значок
  if(mode == 2) {
    strcpy(io_buff, "");
    return;
  }
  clearScreen();
  drawAppTitle("Calculator");

  drawButtonMatrix(0, 80, tft.width(), 240, buttons, 5, 5);
  if(error_flag) {
    strcpy(screen, "Error");
  }
  else {
    sprintf(screen, "%g", a);
  }
  tft.fillRect(0, 40, tft.width(), 32, TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawRightString(screen, tft.width() - 16, 40, FONT_BIG);

  while(1) {
    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 80, tft.width(), 240, buttons, 5, 5);
    if(button_pressed != -1) {
      drawButtonMatrix(0, 80, tft.width(), 240, buttons, 5, 5);
      
      if(!error_flag) {
        // MC
        if(button_pressed == 0) {
          m = 0;
        }
        // MR
        if(button_pressed == 5) {
          a = m;
          clear_on_input = 1;
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
        }
        // +/-
        if(button_pressed == 3) a = -a;
        // 1/x
        if(button_pressed == 4) {
          if(a == 0) {
            error_flag = 1;
          }
          else {
            a = 1 / a;
          }
          clear_on_input = 1;
        }
        if(button_pressed == 6 || button_pressed == 7 || button_pressed == 8
          || button_pressed == 11 || button_pressed == 12 || button_pressed == 13
          || button_pressed == 16 || button_pressed == 17 || button_pressed == 18
          || button_pressed == 21
        ) {
          if(clear_on_input) {
            a = 0;
            dot_flag = 0;
            clear_on_input = 0;
          }
          multiplier_a = 10;
          multiplier_b = 1;
          if(dot_flag) {
            multiplier_a = 1;
            multiplier_b = 1 / pow(10, dot_power);
          }

          if(button_pressed == 6) { a = a * multiplier_a + 7 * multiplier_b; }
          if(button_pressed == 7) { a = a * multiplier_a + 8 * multiplier_b; }
          if(button_pressed == 8) { a = a * multiplier_a + 9 * multiplier_b; }
          if(button_pressed == 11) { a = a * multiplier_a + 4 * multiplier_b; }
          if(button_pressed == 12) { a = a * multiplier_a + 5 * multiplier_b; }
          if(button_pressed == 13) { a = a * multiplier_a + 6 * multiplier_b; }
          if(button_pressed == 16) { a = a * multiplier_a + 1 * multiplier_b; }
          if(button_pressed == 17) { a = a * multiplier_a + 2 * multiplier_b; }
          if(button_pressed == 18) { a = a * multiplier_a + 3 * multiplier_b; }
          if(button_pressed == 21) { a = a * multiplier_a + 0 * multiplier_b; }

          if(dot_flag) {
            dot_power ++;
          }
        }

        // Деление
        if(button_pressed == 9 || button_pressed == 14 || button_pressed == 19
          || button_pressed == 14 || button_pressed == 23 || button_pressed == 24
        ) {
          if(op == '=') b = a;
          if(op == '+') a = b + a;
          if(op == '-') a = b - a;
          if(op == '*') a = b * a;
          if(op == '/') a = b / a;
          b = a;
          clear_on_input = 1;

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
      }
      // CE
      if(button_pressed == 15) {
        a = 0;
        error_flag = 0;
        dot_flag = 0;
      }
      // C
      if(button_pressed == 20) {
        a = 0;
        b = 0;
        error_flag = 0;
        op = '=';
        clear_on_input = 0;
        dot_flag = 0;
      }
      // Десятичная точка
      if(button_pressed == 22 && dot_flag == 0) {
        dot_flag = 1;
        dot_power = 1;
      }
      if(error_flag) {
        strcpy(screen, "Error");
      }
      else {
        sprintf(screen, "%g", a);
      }
      tft.fillRect(0, 40, tft.width(), 32, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawRightString(screen, tft.width() - 16, 40, FONT_BIG);
    }
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

void system_info(char mode, char *io_buff) {
  char buff[80];
  int i = 0;
  long update_millis = millis();

  if(mode == 0) {
    strcpy(io_buff, "System Info");
    return;
  }

  clearScreen();
  drawAppTitle("System Info");
  
  while(1) {
    // 123456789012345678901234567890
    char *data[] = {
      "Hardware: ESP32-2432S028",
      "Cheap Yellow Display",
      "",
      "Software:",
      "ESP32 CYD PDA by sau412",
      "",
      "Compilation time:",
      __DATE__,
      __TIME__,
      NULL
    };

    i = 0;
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    while(data[i]) {
      tft.drawString(data[i], 2, 16 + i * 16, FONT_DEFAULT);
      i++;
    }

    sprintf(buff, "FFat Total: %d bytes ", FFat.totalBytes());
    tft.drawString(buff, 2, 32 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "FFat Used: %d bytes (%d%%) ", FFat.usedBytes(), (int)floor(100 * FFat.usedBytes() / FFat.totalBytes()));
    tft.drawString(buff, 2, 32 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Free heap: %d bytes", esp_get_free_heap_size());
    tft.drawString(buff, 2, 32 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Uptime: %dh %dm %ds     ", millis() / 3600000, (millis() / 60000) % 60, (millis() / 1000) % 60);
    tft.drawString(buff, 2, 32 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Light sensor: %d    ", analogRead(LIGHT_SENSOR));
    tft.drawString(buff, 2, 32 + i * 16, FONT_DEFAULT);
    i++;

    while(millis() - update_millis < 1000) {
      touchCheckNowait();
      if(global_exit_flag) {
        global_exit_flag = 0;
        drawAppTitle("Exit");
        touchWaitRelease();
        return;
      }
    }
    update_millis = millis();
  }
}

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
  if(mode == 0) {
    strcpy(io_buff, "Files");
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
    current_dir = FFat.open(path);
    file_index = 0;

    if (!current_dir) {
      drawError("Failed to open directory");
      return;
    }
    if (!current_dir.isDirectory()) {
      drawError("Not a directory");
      if(!strcmp("/", path)) {
        if(drawConfirm("Format FFat?") == 0) {
          FFat.format();
          FFat.begin(FORMAT_FS_IF_FAILED);
          FFat.mkdir("/Settings");
        }
      }
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
    // Занимаем память, пока на 1024 элемента, с realloc глючит
    files = (char**)malloc(1024 * sizeof(char*));
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
      sprintf(buff2, "[%c] %s", file.isDirectory() ? 'd' : 'f', file.name());
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
      current_dir = FFat.open(path);
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
          file = FFat.open(buff2, FILE_WRITE);
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
          if(!FFat.rename(buff3, buff4)) {
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
        if (!FFat.mkdir(buff3)) {
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
            current_dir = FFat.open(user_input);
            if(current_dir) {
              if(current_dir.isDirectory()) {
                sprintf(buff4, "%s/%s", user_input, file.name());
              }
              current_dir.close();
            }
            // А если нет, то ничего не трогать
          }

          // Копирование
          file = FFat.open(buff3);
          file_copy = FFat.open(buff4, FILE_WRITE);
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
            current_dir = FFat.open(user_input);
            if(current_dir && current_dir.isDirectory()) {
              sprintf(buff4, "%s/%s", user_input, file.name());
            }
            current_dir.close();
          }
          sprintf(buff4, "%s", user_input);
          if(!FFat.rename(buff3, buff4)) {
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
            FFat.rmdir(buff3);
          }
          else {
            FFat.remove(buff3);
          }
          current_op = -1;
          file_selected = 0;
        }
      }
      redraw_required = 1;
    }
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      if(files) {
        for(i = 0; files[i] != NULL; i++) {
          free(files[i]);
        }
        free(files);
      }
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
  
  if(mode == 0) {
    strcpy(io_buff, "Torch");
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
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
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
  
  if(mode == 0) {
    strcpy(io_buff, "Security");
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
        FFat.remove("/Settings/Password");
        drawInfo("Password deleted");
        tft.fillRect(0, 16, tft.width(), tft.height(), TFT_WHITE);
      }
    }
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

void counter(char mode, char *io_buff) {
  int button_pressed;
  long counter = 0;
  char buff[80] = "";
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
  
  if(mode == 0) {
    strcpy(io_buff, "Counter");
    return;
  }

  clearScreen();
  drawAppTitle("Counter");
  
  while(1) {
    tft.fillRect(0, 16, tft.width(), 30, TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);

    sprintf(buff, "%ld", counter);
    tft.drawCentreString(buff, tft.width() / 2, 20, FONT_BIG);

    drawButtonMatrix(8, 50, tft.width() - 8 * 2, 200, buttons_inc, 1, 1);
    drawButtonMatrix(8, 250, tft.width() - 8 * 2, 50, buttons_other, 2, 1);

    touchWaitPress();
    button_pressed = touchCheckMatrix(8, 50, tft.width() - 8 * 2, 200, buttons_inc, 1, 1);
    if(button_pressed != -1) {
      counter++;
    }
    button_pressed = touchCheckMatrix(8, 250, tft.width() - 8 * 2, 50, buttons_other, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        counter--;
      }
      else if(button_pressed == 1) {
        counter = 0;
      }
    }
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
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
  
  if(mode == 0) {
    strcpy(io_buff, "Random numbers");
    return;
  }

  clearScreen();
  drawAppTitle("Random numbers");

  while(1) {
    drawButtonMatrix(0, 50, tft.width(), tft.height() - 50, buttons, 2, 4);

    touchWaitPress();
    button_pressed = touchCheckMatrix(0, 50, tft.width(), tft.height() - 50, buttons, 2, 4);
    if(button_pressed != -1) {
      for(i = 0; i != 10; i++) {
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

        tft.fillRect(0, 16, tft.width(), 30, TFT_WHITE);
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        tft.drawCentreString(buff, tft.width() / 2, 20, FONT_BIG);
        delay(100);
      }
    }
    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
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
  
  if(mode == 0) {
    strcpy(io_buff, "Brightness");
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
    if(global_exit_flag) {
      global_exit_flag = 0;
      save_brightness();
      drawAppTitle("Exit");
      touchWaitRelease();
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
  
  if(mode == 0) {
    strcpy(io_buff, "Timer");
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

    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
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

  // 100 laps
  stopwatch_laps = (char **)malloc(STOPWATCH_MAX_LAPS * sizeof(char *));
  for(i = 0; i < STOPWATCH_MAX_LAPS; i++) {
    stopwatch_laps[i] = NULL;
  }

  if(mode == 0) {
    strcpy(io_buff, "Stopwatch");
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

    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      for(i = 0; i < STOPWATCH_MAX_LAPS; i++) {
        if(stopwatch_laps[i] != NULL) {
          free(stopwatch_laps[i]);
        }
        stopwatch_laps[i] = NULL;
      }
      free(stopwatch_laps);
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
  
  if(mode == 0) {
    strcpy(io_buff, "Breathe");
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

    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
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

  if(mode == 0) {
    strcpy(io_buff, "Screensaver");
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

void draw(char mode, char *io_buff) {
  char b[80];
  TS_Point p1, p2, p3;
  
  int color = TFT_BLACK;
  int color_index = 0;
  int colors[] = {TFT_BLACK, TFT_RED, TFT_GREEN, TFT_BLUE, TFT_YELLOW, TFT_MAGENTA, TFT_CYAN, TFT_WHITE};
  int touch_x;
  int touch_y;
  int prev_touch_x;
  int prev_touch_y;
  char touch_started = 0;

  if(mode == 0) {
    strcpy(io_buff, "Draw");
    return;
  }

  clearScreen();
  drawAppTitle("Draw");

  for(color_index = 0; color_index < 8; color_index++) {
    tft.fillRect(color_index * tft.width() / 8, 304, tft.width() / 8, 16, colors[color_index]);
  }
  color_index = 0;

  while(1) {
    touchWaitPress();
    while(touchscreen.tirqTouched() && touchscreen.touched()) {
      touchCheckNowait();
      TS_Point p = touchscreen.getPoint();
      touch_x = touchMapX(p.x, p.y);
      touch_y = touchMapY(p.x, p.y);

      if(touch_x >= 0 && touch_x < tft.width() && touch_y >= 16 && touch_y < 304) {
        if(touch_started) {
          tft.drawLine(prev_touch_x, prev_touch_y, touch_x, touch_y, colors[color_index]);
        }
        else {
          tft.drawPixel(touch_x, touch_y, colors[color_index]);
          touch_started = 1;
        }
      }
      prev_touch_x = touch_x;
      prev_touch_y = touch_y;
      if(touch_x >= 0 && touch_x < tft.width() && touch_y >= 304 && touch_y < tft.height()) {
        color_index = floor(touch_x * 8 / tft.width());
      }
      if(global_exit_flag) {
        global_exit_flag = 0;
        drawAppTitle("Exit");
        touchWaitRelease();
        return;
      }
    }
    touchWaitRelease();
    touch_started = 0;
  }
}

#ifdef IS_WIFI_ENABLED

#define WIFI_MAX_NETWORKS 128

void wifi(char mode, char *io_buff) {
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

  if(mode == 0) {
    strcpy(io_buff, "Wi-Fi");
    return;
  }

  networks = (char**)malloc(WIFI_MAX_NETWORKS * sizeof(char *));
  for(i = 0; i < WIFI_MAX_NETWORKS; i++) {
    networks[network_index] = NULL;
  }

  clearScreen();
  drawAppTitle("Wi-Fi");

  WiFi.STA.begin();

  rescan_flag = 1;
  while(1) {
    if(rescan_flag) {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("Scanning...      ", 0, 16, FONT_DEFAULT);
      for(i = 0; i < WIFI_MAX_NETWORKS; i++) {
        if(networks[network_index]) {
          free(networks[network_index]);
        }
        networks[network_index] = NULL;
      }

      networks_unique = 0;
      networks_found = WiFi.scanNetworks();
      for (i = 0; i < networks_found; i++) {
        network_listed = 0;
        for(network_index = 0; network_index < networks_unique; network_index++) {
          if(!strcmp(networks[network_index], WiFi.SSID(i).c_str())) {
            network_listed = 1;
          }
        }
        if(network_listed == 0) {
          Serial.println(WiFi.SSID(i).c_str());
          networks[networks_unique] = (char *)malloc(80 * sizeof(char));
          strcpy(networks[networks_unique], WiFi.SSID(i).c_str());
          networks_unique++;
        }
      }
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("Select network:", 0, 16, FONT_DEFAULT);
      rescan_flag = 0;
    }

    touchCheckList(8, 32, tft.width() - 8 * 2, tft.height() - 64, networks, 16, &network_offset, &network_selected);
    drawList(8, 32, tft.width() - 8 * 2, tft.height() - 64, networks, 16, &network_offset, &network_selected);

    drawButtonMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 2, 1);
    
    touchWaitPress();
    touchCheckList(8, 32, tft.width() - 8 * 2, tft.height() - 64, networks, 16, &network_offset, &network_selected);

    button_pressed = touchCheckMatrix(0, 280, tft.width(), tft.height() - 280, buttons, 2, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        strcpy(password, "");
        drawPrompt("Enter password", password);
        WiFi.begin(networks[network_selected], password);
        millis_connecting_start = millis();
        do {
          wifi_status = WiFi.status();
          if(millis() - millis_connecting_start >= 30000) break;
        } while (wifi_status == WL_DISCONNECTED || wifi_status == WL_IDLE_STATUS);
        
        if(wifi_status == WL_CONNECTED) {
          drawInfo("Connected");
          Serial.println(WiFi.localIP());
          show_current_time();
          drawInfo("Starting web server");
          //web_server();
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

    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

void show_current_time() {
  HTTPClient http;
  int httpResponseCode;
  char buff[800];
  http.begin("http://109.230.144.68/cyd/time.php");
  //http.begin("http://example.com/");
  httpResponseCode = http.GET();
  if(httpResponseCode > 0) {
    strcpy(buff, http.getString().c_str());
    drawInfo(buff);
  }
  else {
    drawError("Time fetching failed");
  }
  http.end();
}

#endif

void screen_test(char mode, char *io_buff) {
  int i;
  int colors[] = {TFT_WHITE, TFT_RED, TFT_GREEN, TFT_BLUE, TFT_MAGENTA, TFT_CYAN, TFT_YELLOW, TFT_BLACK};
  if(mode == 0) {
    strcpy(io_buff, "TFT Screen test");
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
  // Смещение следующей страницы мы получаем и так
  // Смещение предыдущей страницы - 
  fs::File file;
  int word_offset;
  int word_in_line_offset = 0;
  int show_file_offset_lines = 0;
  int current_file_offset_lines = 0;
  int current_line_on_screen = 0;
  int touch_x, touch_y;
  char new_line_flag = 0;
  char show_line_flag = 0;
  char show_next_line_flag = 0;
  char long_string_flag = 0;
  char last_line_visible_flag = 0;
  char byte;
  char buff[80];
  char current_string[80];

  clearScreen();
  drawAppTitle(title);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  file = FFat.open(filename);
  if(!file) {
    drawError("Cannot open file");
  }
  if(file.isDirectory()) {
    drawError("Cannot view directory");
    return;
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

    while(file.available()) {
      // Читаем слово
      word_offset = 0;
      buff[0] = 0;
      new_line_flag = 0;
      show_line_flag = 0;
      long_string_flag = 0;
      while(file.available()) {
        byte = file.read();
        buff[word_offset] = byte;
        word_offset++;
        buff[word_offset] = 0;
        // Пробел, дефис, перевод строки завершают слово
        if(byte == '\n' || byte == '\r') {
          new_line_flag = 1;
        }
        if(byte == ' ' || byte == '-' || byte == '\n' || byte == '\r') {
          break;
        }
        // Если это единственное слово в строке и оно уже не помещается
        if(current_string[0] == 0 && tft.textWidth(buff, FONT_DEFAULT) + 10 >= tft.width()) {
          show_line_flag = 1;
          long_string_flag = 1;
          break;
        }
        if(word_offset >= 60) {
          break;
        }
      }
      show_next_line_flag = 0;
      // Если файл закончился - пора показать строку
      if(!file.available() || new_line_flag) {
        show_line_flag = 1;
      }
      // Проверяем, поместится ли на текущую строку
      if(current_string[0] == 0 || tft.textWidth(buff, FONT_DEFAULT) + word_in_line_offset < tft.width()) {
        // Если поместилась - дописываем в буфер
        strcat(current_string, buff);
        word_in_line_offset += tft.textWidth(buff, FONT_DEFAULT);
      }
      else {
        show_line_flag = 1;
        // Если строка не поместилась, а файл закончился, то её нужно показать тоже
        if(!file.available()) {
          show_next_line_flag = 1;
        }
      }
      // Если пора показать строку
      if(show_line_flag) {
        word_in_line_offset = 0;
        if(current_file_offset_lines >= show_file_offset_lines) {
          tft.drawString(current_string, 1, 16 + current_line_on_screen * 16, FONT_DEFAULT);
          // Копируем в буфер непоместившееся слово, если оно есть (не новая строка)
          if(new_line_flag == 0 && long_string_flag == 0) {
            strcpy(current_string, buff);
          }
          else {
            current_string[0] = 0;
          }
          current_line_on_screen++;

          // Если экран заполнен - выходим
          if(current_file_offset_lines >= show_file_offset_lines + 18) {
            break;
          }

          last_line_visible_flag = 0;
          if(show_next_line_flag) {
            tft.drawString(current_string, 1, 16 + current_line_on_screen * 16, FONT_DEFAULT);
            current_string[0] = 0;
            current_line_on_screen++;
            last_line_visible_flag = 1;
          }
          if(!file.available()) {
            last_line_visible_flag = 1;
          }
        }
        else {
          buff[0] = 0;  
          current_string[0] = 0;        
        }
        current_file_offset_lines++;
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
        if(file.available() || last_line_visible_flag == 0) {
          show_file_offset_lines += 19;
        }
      }
    }

    if(global_exit_flag) {
      global_exit_flag = 0;
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

#define EDIT_FILE_LENGTH_MAX 8192

// Редактирование небольшого файла
void edit_file(char *title, char *filename) {
  fs::File file;
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

  int string_offset;
  int file_line_number = 0; // Номер текущей строки в файле
  int screen_line_number = 0; // Номер строки на экране в процессе вывода
  int file_skip_lines = 0; // Сколько строк фалйа пропустить
  int touch_x, touch_y;
  int button;
  char byte;
  char buff[80];
  char current_string[80];
  char contents[EDIT_FILE_LENGTH_MAX];
  char caps_flag = 0;
  char symbol_flag = 0;
  int prev_width = 0;

  char *keyboard_nocaps[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "\\",
    ":shift:", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", ":enter:",
    ":change:", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", " ",
    NULL
  };
  char *keyboard_caps[] = {
    "~",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "|",
    ":shift:", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", ":enter:",
    ":change:", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", " ",
    NULL
  };
  char *keyboard_symbol[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ",  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "=",
    ":shift:", "[", "]", "<", ">", ".", ",", ":", ";", "\"", "'", ":enter:",
    ":change:", "{", "}", "+", "-", "*", "/", "\\", "~", ";", ":", " ",
    NULL
  };
  char **keyboard_current = keyboard_nocaps;

  clearScreen();
  drawAppTitle(title);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  file = FFat.open(filename);
  if(!file) {
    drawError("Cannot open file");
    return;
  }
  if(file.isDirectory()) {
    drawError("Cannot edit directory");
    return;
  }

  // Читаем файл в буфер, но не более 8191 байт
  contents[0] = 0;
  file_offset_bytes = 0;
  while(file.available()) {
    contents[file_offset_bytes] = file.read();
    contents[file_offset_bytes + 1] = 0;
    file_offset_bytes++;
    if(file_offset_bytes >= (EDIT_FILE_LENGTH_MAX - 1)) break;
  }
  file.close();

  // Если файл ещё не кончился - сообщаем об ошибке
  if(file.available()) {
    drawError("File too large to edit");
    return;
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
    else if(caps_flag) {
      keyboard_current = keyboard_caps;
    }
    else {
      keyboard_current = keyboard_nocaps;
    }

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
      }
      else if(button == 12) {
      }
      else if(button == 24) {
        caps_flag = !caps_flag;
      }
      else if(button == 36) {
        symbol_flag = !symbol_flag;
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
          }
          cursor_offset_bytes++;
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
    /*
    // Касание нижней строки - прокрутка вниз (если не достигнут конец файла)
    if(touch_y >= 176 && touch_y < 192) {
      if(contents[file_offset_bytes] != 0) {
        file_skip_lines++;
      }
    }
    // Касание верхней строки - прокрутка вверх (если не достигнут конец файла)
    if(touch_y >= 16 && touch_y < 32) {
      if(file_skip_lines > 0) {
        file_skip_lines--;
      }
    }
    */
    if(global_exit_flag) {
      touchWaitRelease();
      // Спрашиваем о сохранении, сохраняем если да
      if(drawConfirm("Save changes?") == 0) {
        file = FFat.open(filename, FILE_WRITE);
        file_offset_bytes = 0;
        while(contents[file_offset_bytes] != 0) {
          file.print(contents[file_offset_bytes]);
          file_offset_bytes++;
        }
        file.close();
      }
      global_exit_flag = 0;
      return;
    }
    touchWaitRelease();
  }
}

void touch_calibration(char mode, char *io_buff) {
  fs::File file;
  char buff[80];
  TS_Point p1, p2, p3;
  int offset = 10;
  
  int touch_x;
  int touch_y;

  if(mode == 0) {
    strcpy(io_buff, "Calibration");
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
  touchWaitRelease();
  delay(1000);  

  clearScreen();
  tft.drawCentreString("Touch left bottom cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(offset - 5, tft.height() - 2 - offset - 5, offset + 5, tft.height() - 2 - offset + 5, TFT_BLACK);
  tft.drawLine(offset - 5, tft.height() - 2 - offset + 5, offset + 5, tft.height() - 2 - offset - 5, TFT_BLACK);
  delay(1000);
  touchWaitPress();
  p2 = touchscreen.getPoint();
  touchWaitRelease();
  delay(1000);  

  clearScreen();
  tft.drawCentreString("Touch right top cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(tft.width() - 2 - offset - 5, offset - 5, tft.width() - 2 - offset + 5, offset + 5, TFT_BLACK);
  tft.drawLine(tft.width() - 2 - offset - 5, offset + 5, tft.width() - 2 - offset + 5, offset - 5, TFT_BLACK);
  delay(1000);
  touchWaitPress();
  p3 = touchscreen.getPoint();
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
  while(touchscreen.tirqTouched() && touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);
    tft.drawPixel(touch_x, touch_y, TFT_BLACK);
  }
  touchWaitRelease();
  file = FFat.open("/Settings/Calibration", FILE_WRITE);
  if(file) {
    sprintf(buff, "%f %f %f %f %f %f", ax, bx, cx, ay, by, cy);
    file.print(buff);
    file.close();
  }
  delay(1000);
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
  
  for(i = 0; i < 16; i++) {
    buttons_won[i] = buttons[i];
  }

  if(mode == 0) {
    strcpy(io_buff, "Fifteen");
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

    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
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
  
  if(mode == 0) {
    strcpy(io_buff, "Lights Off");
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

    if(global_exit_flag) {
      global_exit_flag = 0;
      drawAppTitle("Exit");
      touchWaitRelease();
      return;
    }
    touchWaitRelease();
  }
}

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

void clearScreen() {
  tft.fillScreen(TFT_WHITE);
}

void drawAppTitle(char *name) {
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.fillRect(0, 0, tft.width(), 16, TFT_BLUE);
  tft.drawString(name, 16, 0, FONT_DEFAULT);
}

void drawError(char *message) {
  char *buttons[] = { "OK", NULL };
  drawPopoupWindowWaitReply("Error", message, buttons);
}

void drawAlert(char *message) {
  char *buttons[] = { "OK", NULL };
  drawPopoupWindowWaitReply("Alert", message, buttons);
}

void drawInfo(char *message) {
  char *buttons[] = { "OK", NULL };
  drawPopoupWindowWaitReply("Info", message, buttons);
}

int drawConfirm(char *message) {
  char *buttons[] = { "OK", "Cancel", NULL };
  return drawPopoupWindowWaitReply("Confirm", message, buttons);
}

#define PROMPT_OFFSET_Y 100

int drawPrompt(char *message, char *user_input) {
  char *buttons[] = { "OK", "Cancel", NULL };

  int button = 0;
  char caps_flag = 0;
  char symbol_flag = 0;
  char input[80] = "";
  int cursor_pos = 0;

  char *keyboard_nocaps[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "\\",
    ":shift:", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", ":enter:",
    ":change:", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", " ",
    NULL
  };
  char *keyboard_caps[] = {
    "~",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "|",
    ":shift:", "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", ":enter:",
    ":change:", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", " ",
    NULL
  };
  char *keyboard_symbol[] = {
    "`",  "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", ":backspace:",
    " ",  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "=",
    ":shift:", "[", "]", "<", ">", ".", ",", ":", ";", "\"", "'", ":enter:",
    ":change:", "{", "}", "+", "-", "*", "/", "\\", "~", ";", ":", " ",
    NULL
  };
  char **keyboard_current = keyboard_nocaps;

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
    cursor_pos = tft.drawString(input, 8, PROMPT_OFFSET_Y + 20, FONT_DEFAULT);
    tft.setTextColor(TFT_BLUE, TFT_WHITE);
    tft.drawString("_", 8 + cursor_pos + 1, PROMPT_OFFSET_Y + 20, FONT_DEFAULT);

    drawButtonMatrix(8, PROMPT_OFFSET_Y + 180, tft.width() - 8 * 2, 32, buttons, 3, 1);

    if(symbol_flag) {
      keyboard_current = keyboard_symbol;
    }
    else if(caps_flag) {
      keyboard_current = keyboard_caps;
    }
    else {
      keyboard_current = keyboard_nocaps;
    }

    drawButtonMatrix(0, PROMPT_OFFSET_Y + 40, tft.width(), 120, keyboard_current, 12, 4);
    
    touchWaitPress();
    button = touchCheckMatrix(0, PROMPT_OFFSET_Y + 40, tft.width(), 120, keyboard_current, 12, 4);
    if(button != -1) {
      if(button == 11) {
        if(strlen(input) > 0) {
          input[strlen(input) - 1] = 0;
        }
      }
      else if(button == 12) {
      }
      else if(button == 24) {
        caps_flag = !caps_flag;
      }
      else if(button == 35) {
        if(strlen(input) >= 79) continue;
        strcat(input, "\n");
      }
      else if(button == 36) {
        symbol_flag = !symbol_flag;
      }
      else {
        if(strlen(input) >= 79) continue;
        strcat(input, keyboard_current[button]);
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
  drawAppTitle("Enter password");

  // Читаем информацию о владельце
  file = FFat.open("/Settings/Owner");
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
            image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, enter, TFT_BLACK, TFT_LIGHTGREY);
          }
          else if(!strcmp(str[x + y * cols], ":backspace:")) {
            image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, backspace, TFT_BLACK, TFT_LIGHTGREY);
          }
          else if(!strcmp(str[x + y * cols], ":shift:")) {
            image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, shift, TFT_BLACK, TFT_LIGHTGREY);
          }
          else if(!strcmp(str[x + y * cols], ":change:")) {
            image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, change_keyboard, TFT_BLACK, TFT_LIGHTGREY);
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
                  image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, enter, TFT_BLACK, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":backspace:")) {
                  image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, backspace, TFT_BLACK, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":shift:")) {
                  image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, shift, TFT_BLACK, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":change:")) {
                  image_8x8_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, change_keyboard, TFT_BLACK, bg_color);
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
    if(!is_eol) {
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      // Если нужно показать [up]
      if(y == 0 && *offset > 0) {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        tft.drawString(up, left_x + 1, top_y + (y + 0.5) * height / rows_to_show - 8, FONT_DEFAULT);
      }
      // Если нужно показать [down]
      else if(y == (rows_to_show - 1) && (*offset + rows_to_show) <= last_row) {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        tft.drawString(down, left_x + 1, top_y + (y + 0.5) * height / rows_to_show - 8, FONT_DEFAULT);
      }
      else if(str[y + *offset]) {
        if(y + *offset == *selected) {
          tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_BLUE);
          tft.setTextColor(TFT_WHITE, TFT_BLUE);
        }
        else {
          tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, TFT_WHITE);
        }
        tft.drawString(str[y + *offset], left_x + 1, top_y + (y + 0.5) * height / rows_to_show - 8, FONT_DEFAULT);
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
Serial.print("touch_x = ");
Serial.println(touch_x);
Serial.print("touch_y = ");
Serial.println(touch_y);
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
  // Касание не на заголовок
  if(global_touch_y < 0 || global_touch_y >= 32) return 0;
  
  // Длительность меньше секунды
  if(global_touch_length < 1000) return 0;
  
  // Нет касания
  if(!touchscreen.tirqTouched() || !touchscreen.touched()) return 0;
  
  // Касание сместилось
  global_touch_p = touchscreen.getPoint();
  global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
  global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);
  if(global_touch_y < 0 || global_touch_y >= 32) return 0;

  // Если все условия выполнились - сообщаем о сигнале на выход
  global_exit_flag = 1;
  return 1;
}

void touchWaitPress() {
  while(!touchscreen.tirqTouched() || !touchscreen.touched()) {
    if(global_exit_flag) return;
  }
  global_touch_begin = millis();
  delay(20);
  global_touch_p = touchscreen.getPoint();
  global_touch_x = touchMapX(global_touch_p.x, global_touch_p.y);
  global_touch_y = touchMapY(global_touch_p.x, global_touch_p.y);
  global_touch_present_flag = 1;
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
  //Serial.println(global_touch_length);
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
  file = FFat.open(filename);
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

int write_file_from_buff(char *filename, char *buff) {
  fs::File file;
  int offset = 0;
  file = FFat.open(filename, FILE_WRITE);
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

int get_brightness() {
  return brightness;
}

void set_brightness(int level) {
  brightness = level;
  analogWrite(BACKLIGHT_LED, level);
}

void save_brightness() {
  char buff[80];
  sprintf(buff, "%d", brightness);
  write_file_from_buff("/Settings/Brightness", buff);
}

void image_8x8_from_bits(int start_x, int start_y, char *image, int color, int bg_color) {
  int byte_index, bit_index;
  int x, y;
  char bit;
  int width = (int)image[0];
  int height = (int)image[1];
  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      byte_index = (x + y * width) / 8 + 2;
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
  int offset;
  char calibration_required = 0;
  char password_present;

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

  // Инициализация FFat
  if (!FFat.begin(FORMAT_FS_IF_FAILED)) {
    drawError("FFat mount failed");
    if(drawConfirm("Format FFat?") == 0) {
      FFat.format();
      FFat.begin(FORMAT_FS_IF_FAILED);
      FFat.mkdir("/Settings");
    }
  }

  // Яркость
  brightness = 255;
  if(read_file_to_buff("/Settings/Brightness", 79, buff)) {
    sscanf(buff, "%d", &brightness);
    set_brightness(brightness);
  }

  // Калибровка сенсора, если нужно
  calibration_required = 1;
  if(read_file_to_buff("/Settings/Calibration", 79, buff)) {
    calibration_required = 0;
    ax = 0;
    sscanf(buff, "%f %f %f %f %f %f", &ax, &bx, &cx, &ay, &by, &cy);
  }
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    calibration_required = 1;
  }

  if(calibration_required) {
    touch_calibration(1, NULL);
  }

  // Тут можно было бы спросить пароль
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

/*
  int i, j;
  //char buff[10];
  for(j = 0; j != 16; j++) {
    for(i = 0; i != 16; i++) {
      sprintf(buff, "%c", (char)(i + j * 16));
      tft.drawString(buff, i * tft.width() / 16, j * tft.height() / 16, 2);
    }
  }
  touchWaitPress();
  touchWaitRelease();
  clearScreen();
*/

  // Отлаживаемая функция
  //files(1, NULL);
}

void loop() {
  apps[0](1, NULL);
}
