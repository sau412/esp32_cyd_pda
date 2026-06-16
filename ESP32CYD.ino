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
- Ханойские башни
- Найди пару (как Masterbrain)
- Пианино
- Метроном
- Просмотр текста из памяти
- Справка
- RSS
- Шифрование AES
- Хранилище паролей
- Воспроизведение монофонических мелодий
- Выбор цветовой схемы
- Три в ряд
- Терминал
- Приложения терминала: serial, ping, telnet
- Бэкап через веб-интерфейс (очень медленно)
- Восстановление через веб-интерфейс

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
2026-06-10 Соединение по https, раздел настроек, метроном, просмотр текста из памяти, справка, читалка RSS, возможность отключить звук
2026-06-11 Шифрование AES-256, хранилище паролей, монофонические мелодии
2026-06-12 Инверсия экрана, цветовые схемы
2026-06-13 Клавиши пианино белые при любой цветовой схеме, программная перезагрузка, включение альтернативной клавиатуры в настройках,
  баг цветов в игре жизнь (ничего не было видно), баг в информации о системе, доработка там же
2026-06-14 Ночная цветовая схема
2026-06-15 Три в ряд, терминал
2026-06-16 Больше команд терминала, serial, ping, telnet, бэкап через веб (медленно), восстановление через веб (не тестировал)

Направления работы:
- IRC
- (и) Воспроизведение MP3
- Повтор последовательности (игра)
- N назад (почти игра)
- Устный счёт (почти игра)
- Карточки для запоминания слов (PIM) - первая строка название, остальные - пояснение
- Интернет-радио (PIM)
- Бэкапы (на SD)
- 2048 (игра)
- Арканоид (игра)
- Тетрис (игра)
- Приложение выбор автозапуска

Улучшения тут и там:
- (б) Проблема при работе с SD, запись больше 2 кб
- (б) Гофер браузер - не прокручивать дальше конца файла
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
- (д) Преобразование из CP1251 в UTF8
- (д) Парсинг JSON
- (д) Получение погоды напрямую с weather.com
- (д) Прерывать мелодии при касании
- (д) Меньше мигания в мелодиях
- (д) Флаг автосохранения файла при редактировании и неактивности
- (д) RSS лишние теги у фонтанки
- (д) RSS текст ошибки пользователю
- (д) Автояркость
- (д) drawProgress - рисовать прогресс операции
- (д) Serial как ввод клавиатуры
- (д) Определять инверсию экрана
- (д) Ночная тема

*/

#define IS_WIFI_ENABLED
//#define IS_SSH_ENABLED

//#define USE_SD_AS_STORAGE

// CYD
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// Filesystem for FFat and SD
#include "FS.h"

// FFat
#include "FFat.h"

// SD
#include "SD.h"

// I2C
#include <Wire.h>

// MP3
//#include <Audio.h>

//#include "esp_core_dump.h"

#ifdef IS_WIFI_ENABLED

// Wi-Fi
#include "WiFi.h"

// HTTP client
#include <HTTPClient.h>
// HTTPS client
#include <WiFiClientSecure.h>

// Ping
#include <ESPping.h>

// HTTP server
#include <WebServer.h>

#ifdef IS_SSH_ENABLED

// SSH
#include <libssh_esp32.h>
#include <libssh/libssh.h>

#endif

#endif

// Encryption library for password storage
#include "mbedtls/aes.h"

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

// Audio
#define I2S_BCLK 26
#define I2S_LRC 25
#define I2S_DOUT 22

#define FONT_MONOSPACE 1
#define FONT_DEFAULT 2
#define FONT_BIG 4
#define FONT_BIGGER 6
#define FONT_BIG_SEGMENT 7
#define FONT_BIGGEST 8

#define APP_MODE_LAUNCH 1
#define APP_MODE_RETURN_NAME 0
#define APP_MODE_RETURN_ICON 2

#define EDIT_FILE_LENGTH_MAX 8192

#ifdef USE_SD_AS_STORAGE
#define Storage SD
//FS Storage = SD; 
#else
#define Storage FFat
//FS Storage = FFat;
#endif

// Терминал
#define TERMINAL_WIDTH_CHARS 40
#define TERMINAL_HEIGHT_CHARS 20

char terminal_screen[TERMINAL_WIDTH_CHARS * TERMINAL_HEIGHT_CHARS];
char terminal_colors[TERMINAL_WIDTH_CHARS * TERMINAL_HEIGHT_CHARS];
int cursor_row;
int cursor_col;
int current_color;
char cursor_visible_flag = 1;
char terminal_keyboard_redraw_flag = 0;

// Цвета
#define COLOR_INDEX_BLACK 0
#define COLOR_INDEX_MAROON 1
#define COLOR_INDEX_DARKGREEN 2
#define COLOR_INDEX_OLIVE 3
#define COLOR_INDEX_NAVY 4
#define COLOR_INDEX_PURPLE 5
#define COLOR_INDEX_DARKCYAN 6
#define COLOR_INDEX_LIGHTGREY 7
#define COLOR_INDEX_DARKGREY 8
#define COLOR_INDEX_RED 9
#define COLOR_INDEX_GREEN 10
#define COLOR_INDEX_YELLOW 11
#define COLOR_INDEX_BLUE 12
#define COLOR_INDEX_MAGENTA 13
#define COLOR_INDEX_CYAN 14
#define COLOR_INDEX_WHITE 15

int colors[] = {
  TFT_BLACK, TFT_MAROON, TFT_DARKGREEN, TFT_OLIVE,
  TFT_NAVY, TFT_PURPLE, TFT_DARKCYAN, TFT_LIGHTGREY,
  TFT_DARKGREY, TFT_RED, TFT_GREEN, TFT_YELLOW,
  TFT_BLUE, TFT_MAGENTA, TFT_CYAN, TFT_WHITE
};

// Цветовая схема
// Цвет фона и текста
int color_scheme_bg = colors[COLOR_INDEX_WHITE];
int color_scheme_fg = colors[COLOR_INDEX_BLACK];
// Цвет заголовка и текста
int color_scheme_title_bg = colors[COLOR_INDEX_BLUE];
int color_scheme_title_fg = colors[COLOR_INDEX_WHITE];
// Цвет выделения и текста
int color_scheme_selection_bg = colors[COLOR_INDEX_BLUE];
int color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
// Цвет кнопки и текста
int color_scheme_button_bg = colors[COLOR_INDEX_LIGHTGREY];
int color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
// Цвет нажатой кнопки и текста
int color_scheme_button_active_bg = colors[COLOR_INDEX_DARKGREY];
int color_scheme_button_active_fg = colors[COLOR_INDEX_BLACK];
// Цвет неактивного текста
int color_scheme_inactive_fg = colors[COLOR_INDEX_LIGHTGREY];
// Цвет ссылки
int color_scheme_link_fg = colors[COLOR_INDEX_BLUE];

// Альтернативная клавиатура
char alt_keyboard_enabled_flag = 1;

// Значки
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

// Клавиатуры
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

// Класс для прямого чтения и записи раздела FFat
class FFatContentsStream : public Stream {
private:
    long offset = 0;
    int buff_offset = -1;
    int chunk_size = 4096;
    char *buff;

    const esp_partition_t* partition = esp_partition_find_first(
        ESP_PARTITION_TYPE_DATA,         // Type (DATA or APP)
        ESP_PARTITION_SUBTYPE_DATA_FAT,  // Subtype
        NULL                             // Label name in your partition table
      );

public:
    // Конструктор
    FFatContentsStream() {
      buff = (char*)malloc(chunk_size * sizeof(char));
      esp_partition_read(partition, offset, buff, chunk_size);
      Serial.printf("Reading offset %d\n", offset);
      buff_offset = 0;
    }
    // Деструктор
    ~FFatContentsStream() {
      if(buff) {
        free(buff);
      }
    }

    // Core Print implementation requirement
    size_t write(uint8_t data) override {
      buff[buff_offset] = data;
      buff_offset++;
      if(buff_offset >= chunk_size) {
        esp_partition_erase_range(partition, offset, chunk_size);
        esp_partition_write(partition, offset, buff, chunk_size);
        Serial.printf("Writing offset %d\n", offset);
        offset += chunk_size;
        buff_offset = 0;
      }
    }
    // Core Stream implementation requirements
    int available() override {
      return offset < partition->size;
    }

    int read() override {
      int result = -1;
      if(buff_offset >= chunk_size) {
        esp_err_t result = esp_partition_read(partition, offset, buff, chunk_size);
        Serial.printf("Reading offset %d\n", offset);
        buff_offset = 0;
      }
      if(offset < partition->size) {
        offset++;
        result = buff[buff_offset];
        buff_offset++;
        return result;
      }
      else {
        return -1;
      }
    }

    int peek() override {
      char c;
      if((offset + 1) < partition->size) {
        if(buff_offset > 0 && buff_offset < chunk_size - 1) {
          return buff[buff_offset + 1];
        }
        esp_err_t result = esp_partition_read(partition, offset + 1, &c, 1);
        return c;
      }
      else {
        return -1;
      }
    }

    void flush() override {
      esp_partition_erase_range(partition, offset, chunk_size);
      esp_partition_write(partition, offset, buff, chunk_size);
      offset += chunk_size;
      buff_offset = 0;
    }

    long size() {
      return partition->size;
    }

    char* name() {
      return "ffat";
    }
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

// Звук
char is_beep_enabled = 1;

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
void rss(char mode, char *io_buff);
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
void passwords(char mode, char *io_buff);
void tunes(char mode, char *io_buff);
void music(char mode, char *io_buff);
void life(char mode, char *io_buff);
void i2c_scanner(char mode, char *io_buff);
void dashboard(char mode, char *io_buff);
void fuzzy_clock(char mode, char *io_buff);
void set_clock(char mode, char *io_buff);
void snake(char mode, char *io_buff);
void view_font(char mode, char *io_buff);
void turkish_kerchief(char mode, char *io_buff);
void memory_match(char mode, char *io_buff);
void hanoi_towers(char mode, char *io_buff);
void piano(char mode, char *io_buff);
void metronome(char mode, char *io_buff);
void user_manual(char mode, char *io_buff);
void color_settings(char mode, char *io_buff);
void reboot(char mode, char *io_buff);
void alt_keyboard_control(char mode, char *io_buff);
void match_three(char mode, char *io_buff);
void terminal(char mode, char *io_buff);
void time_and_date_group(char mode, char *io_buff);
void games_group(char mode, char *io_buff);
void settings_group(char mode, char *io_buff);
void launcher_return_back(char mode, char *io_buff);

typedef void (*function_application_pointer) (char mode, char *io_buff);
typedef void (*function_action_pointer) (int action, char *filename);
typedef void (*function_conversion_pointer) (fs::File file, char *buff);

function_application_pointer apps[40] = {
  launcher,
  calculator,
  files,
  terminal,
  notes,
  contacts,
  todo,
  schedule,
  expenses,
  books,
  passwords,
  tunes,
  //music, // Music app is not ready yet
  //system_info,
  torch,
  draw,
#ifdef IS_WIFI_ENABLED
  wifi,
  gopher,
  rss,
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
  metronome,
  //screen_test,
  screensaver,
  user_manual,
  //security,
  //brightness_app,
  //touch_calibration,
  //fifteen,
  //lights_off,
  //snake,
  //turkish_kerchief,
  //memory_match,
  //hanoi_towers,
  life,
  i2c_scanner,
  dashboard,
  //fuzzy_clock,
  //set_clock,
  //view_font,
  time_and_date_group,
  games_group,
  settings_group,
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
  turkish_kerchief,
  memory_match,
  hanoi_towers,
  match_three,
  NULL
};
function_application_pointer settings_apps[40] = {
  launcher,
  launcher_return_back,
  files,
  system_info,
  torch,
#ifdef IS_WIFI_ENABLED
  wifi,
  http_file_access,
#endif
  screen_test,
  security,
  brightness_app,
  color_settings,
  touch_calibration,
  set_clock,
  i2c_scanner,
  view_font,
  alt_keyboard_control,
  reboot,
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
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
              tft.drawString(app_name, 19 + col * tft.width() / 2, (row + 1) * 16, FONT_DEFAULT);
              image_from_bits(col * tft.width() / 2, (row + 1) * 16, app_icon, color_scheme_fg, color_scheme_bg);
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
      tft.fillRect(col * tft.width() / 2, (row + 1) * 16, tft.width() / 2, 16, color_scheme_selection_bg);
      tft.setTextColor(color_scheme_selection_fg, color_scheme_selection_bg);
      
      tft.drawString(app_name, 19 + col * tft.width() / 2, (row + 1) * 16, FONT_DEFAULT);
      image_from_bits(col * tft.width() / 2, (row + 1) * 16, app_icon, color_scheme_selection_fg, color_scheme_selection_bg);
      delay(100);
      touchWaitRelease();

      tft.fillRect(col * tft.width() / 2, (row + 1) * 16, tft.width() / 2, 16, color_scheme_bg);
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
      tft.drawString(app_name, 19 + col * tft.width() / 2, (row + 1) * 16, FONT_DEFAULT);
      image_from_bits(col * tft.width() / 2, (row + 1) * 16, app_icon, color_scheme_fg, color_scheme_bg);

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

void settings_group(char mode, char *io_buff) {
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
    strcpy(io_buff, "Settings");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  for(i = 0; i < 40; i++) {
    apps[i] = settings_apps[i];
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
    tft.fillRect(0, 16, tft.width(), 80 - 16, color_scheme_bg);
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    if(error_flag) {
      strcpy(screen, "Error");
    }
    tft.drawRightString(screen, tft.width() - 16, 40, FONT_BIG);

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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

    sprintf(buff, "Heap Total: %d bytes ", ESP.getHeapSize());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Free: %d bytes (%d%%) ", ESP.getFreeHeap(), (int)floor(100 * ESP.getFreeHeap() / ESP.getHeapSize()));
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Min Free: %d bytes ", ESP.getMinFreeHeap());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Heap Max Alloc: %d bytes ", ESP.getMaxAllocHeap());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "---");
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Flash: %d bytes ", ESP.getFlashChipSize());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    sprintf(buff, "Sketch: %d bytes ", ESP.getSketchSize());
    tft.drawString(buff, 2, 16 + i * 16, FONT_DEFAULT);
    i++;

    if(Storage.totalBytes() > 4096 * 1024) {
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

void user_manual(char mode, char *io_buff) {
  char help[] =
  "This is some help for ESP32 CYD PDA Firmware\n"
  "\n"
  "== Basic usage ==\n"
  "Touch elements to perform actions.\n"
  "\n"
  "== Tips & Tricks ==\n"
  "* Touch and hold app title more than 1 second to exit app.\n"
  "* Press BOOT button to make screenshot. There is no way to view screenshot though.\n"
  "* To force perform calibration on start hold touchscreen during reboot\n"
  "* For screensavers touch and hold anywhere to exit\n"
  "\n"
  "== Reader ==\n"
  "Touch left side of the screen to scroll back, right side to scroll forward.\n"
  "\n"
  "== Contacts ==\n"
  "First line of the file is name, second is contact."
  "\n"
  "== RSS ==\n"
  "First line of the file is name, second is RSS URL. HTTP and HTTPS are supported.\n"
  "\n"
  "== Schedule ==\n"
  "Touch day to view and edit plans for that day.\n"
  "\n"
  "== I2C Scanner ==\n"
  "Connect I2C bus to IO2 socket (3V3, IO22, IO27, GND) and press scan to scan.\n"
  "\n"
  "== Terminal ==\n"
  "Commands available:\n"
  "millis, micros, sleep, delay, date, reboot, reset, exit, serial, host, ping, cat, ping, telnet, ls, mkdir, rmdir, rm, touch, format"
  "\n"
  "== Filesystem ==\n"
  "/Settings - settings folder\n"
  "/Settings/Calibration - touchscreen calibration data\n"
  "/Settings/View - books & files view offset\n"
  "/Settings/Timestamp - latest synced timestamp\n"
  "/Settings/Nickname - nickname for chat\n"
  "/Settings/Password - prompt password after reset\n"
  "/Settings/Owner - owner info for password prompt\n"
  "/Settings/Brightness - brightness level\n"
  "/Settings/Timezone - timezone offset in seconds\n"
  "/Settings/Wifi - Wi-Fi passwords\n"
  "/Settings/Autorun - auto start app after reset\n"
  "/Notes - notes folder\n"
  "/Images - draw folder\n"
  "/Expenses - expenses folder\n"
  "/Screenshots - screenshots folder (press BOOT to make one)\n"
  "/Contacts - contacts folder\n"
  "/Todo - todo folder\n"
  "/Books - books folder\n"
  "/Schedule - schedule folder\n"
  "\n"
  ;
  int i = 0;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000111, B11100010,
    B01001111, B11110010,
    B01011100, B00111010,
    B01011000, B00111010,
    B01000000, B01110010,
    B01000000, B11100010,
    B01000001, B11000010,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };


  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "User Manual");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  view_text("User Manual", help);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    tft.fillRect(0, 16, tft.width(), 16, color_scheme_bg);
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
// Терминал
// ====================================================
void terminal(char mode, char *io_buff) {
  char buff[80];
  IPAddress ip;
  fs::File file;
  fs::File current_dir;
  char byte;
  int i;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01111111, B11111110,
    B01111111, B11111110,
    B01101111, B11111110,
    B01110111, B11111110,
    B01111011, B11111110,
    B01111101, B11111110,
    B01111101, B11111110,
    B01111011, B11111110,
    B01110111, B11111110,
    B01101111, B11111110,
    B01111111, B00000110,
    B01111111, B11111110,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Terminal");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Terminal");

  terminal_clear_screen();

  while(1) {
    terminal_print(">");
    terminal_show_screen();

    terminal_keyboard_redraw_flag = 1;
    terminal_input_string(buff);
    terminal_show_screen();

    if(global_exit_flag) {
      touchExitActionReset();
      return;
    }

    if(strcmp(buff, "millis") == 0) {
      sprintf(buff, "%d\n\r", millis());
      terminal_print(buff);
    }
    else if(strcmp(buff, "micros") == 0) {
      sprintf(buff, "%d\n\r", micros());
      terminal_print(buff);
    }
    else if(strcmp(buff, "clear") == 0) {
      terminal_clear_screen();
    }
    else if(strcmp(buff, "reset") == 0) {
      terminal_clear_screen();
    }
    else if(strcmp(buff, "reboot") == 0) {
      ESP.restart();
    }
    else if(strcmp(buff, "exit") == 0) {
      global_exit_flag = 1;
    }
    else if(strcmp(buff, "date") == 0) {
      set_local_time_from_unix_timestamp();
      sprintf(buff, "%04d-%02d-%02d %d:%02d:%02d\n\r", global_year, global_month, global_day, global_hours, global_minutes, global_seconds);
      terminal_print(buff);
    }
    else if(strcmp(buff, "sleep") == 0) {
      terminal_print("Usage: sleep {seconds}\n\r");
    }
    else if(memcmp(buff, "sleep ", 6) == 0) {
      sscanf(buff + 6, "%d", &i);
      delay(1000 * i);
    }
    else if(strcmp(buff, "delay") == 0) {
      terminal_print("Usage: sleep {milliseconds}\n\r");
    }
    else if(memcmp(buff, "delay ", 6) == 0) {
      sscanf(buff + 6, "%d", &i);
      delay(i);
    }
    else if(strcmp(buff, "serial") == 0) {
      terminal_serial("");
    }
    else if(memcmp(buff, "serial ", 7) == 0) {
      terminal_serial(buff + 7);
    }
    else if(strcmp(buff, "format ffat") == 0) {
      if(FFat.format() == true) {
        terminal_print("Format FFat completed\n\r");
      }
      else {
        terminal_print("Format FFat failed\n\r");
      }
      FFat.begin(true);
      Storage.mkdir("/Settings");
    }
    else if(strcmp(buff, "ls") == 0) {
      terminal_print("Usage: ls {directory}\n\r");
    }
    else if(memcmp(buff, "ls ", 3) == 0) {
      current_dir = Storage.open(buff + 3);
      if(current_dir && current_dir.isDirectory()) {
        while(file = current_dir.openNextFile()) {
          terminal_print((char *)file.name());
          terminal_print("\n\r");
        }
      }
      else {
        terminal_print("Unable to open directory\n\r");
      }
    }
    else if(strcmp(buff, "mkdir") == 0) {
      terminal_print("Usage: mkdir {directory}\n\r");
    }
    else if(memcmp(buff, "mkdir ", 6) == 0) {
      if(Storage.mkdir(buff + 6)) {
        terminal_print("OK\n\r");
      }
      else {
        terminal_print("Unable to create directory\n\r");
      }
    }
    else if(strcmp(buff, "rmdir") == 0) {
      terminal_print("Usage: rmdir {directory}\n\r");
    }
    else if(memcmp(buff, "rmdir ", 6) == 0) {
      if(Storage.rmdir(buff + 6)) {
        terminal_print("OK\n\r");
      }
      else {
        terminal_print("Unable to remove directory\n\r");
      }
    }
    else if(strcmp(buff, "cat") == 0) {
      terminal_print("Usage: cat {file}\n\r");
    }
    else if(memcmp(buff, "cat ", 4) == 0) {
      file = Storage.open(buff + 4);
      if(file) {
        while(file.available()) {
          byte = file.read();
          if(byte == '\n' && file.peek() == '\r') file.read();
          if(byte == '\r' && file.peek() == '\n') file.read();
          if(byte == '\n' || byte == '\r') {
            terminal_print_char('\n');
            terminal_print_char('\r');
          }
          else {
            terminal_print_char(byte);
          }
        }
        file.close();
      }
      else {
        terminal_print("File not found\n\r");
      }
    }
    else if(strcmp(buff, "touch") == 0) {
      terminal_print("Usage: touch {filename}\n\r");
    }
    else if(memcmp(buff, "touch ", 6) == 0) {
      file = Storage.open(buff + 6, FILE_APPEND);
      if(file) {
        file.close();
        terminal_print("OK\n\r");
      }
      else {
        terminal_print("File not found\n\r");
      }
    }
    else if(strcmp(buff, "rm") == 0) {
      terminal_print("Usage: rm {filename}\n\r");
    }
    else if(memcmp(buff, "rm ", 3) == 0) {
      if(Storage.remove(buff + 3)) {
        terminal_print("OK\n\r");
      }
      else {
        terminal_print("File not found\n\r");
      }
    }
#ifdef IS_WIFI_ENABLED
    else if(strcmp(buff, "ip") == 0) {
      sprintf(buff, "%s\n\r", WiFi.localIP().toString());
      terminal_print(buff);
    }
    else if(strcmp(buff, "netmask") == 0) {
      sprintf(buff, "%s\n\r", WiFi.subnetMask().toString());
      terminal_print(buff);
    }
    else if(strcmp(buff, "gateway") == 0) {
      sprintf(buff, "%s\n\r", WiFi.gatewayIP().toString());
      terminal_print(buff);
    }
    else if(strcmp(buff, "dns") == 0) {
      sprintf(buff, "%s\n\r", WiFi.dnsIP().toString());
      terminal_print(buff);
    }
    else if(strcmp(buff, "rssi") == 0) {
      sprintf(buff, "%d\n\r", WiFi.RSSI());
      terminal_print(buff);
    }
    else if(strcmp(buff, "host") == 0) {
      terminal_print("Usage: host {hostname}\n\r");
    }
    else if(memcmp(buff, "host ", 5) == 0) {
      WiFi.hostByName(buff + 5, ip);
      sprintf(buff, "%s\n\r", ip.toString().c_str());
      terminal_print(buff);
    }
    else if(strcmp(buff, "ping") == 0) {
      terminal_print("Usage: ping {hostname}\n\r");
    }
    else if(memcmp(buff, "ping ", 5) == 0) {
      terminal_ping(buff + 5);
    }
    else if(strcmp(buff, "telnet") == 0) {
      terminal_print("Usage: telnet {host} {port}");
    }
    else if(memcmp(buff, "telnet ", 7) == 0) {
      terminal_telnet(buff + 7);
    }
#ifdef IS_SSH_ENABLED
    else if(strcmp(buff, "ssh") == 0) {
      terminal_print("Usage: ssh {host} {port}");
    }
    else if(memcmp(buff, "ssh ", 4) == 0) {
      terminal_ssh(buff + 4);
    }
#endif
#endif
    else {
      if(strcmp(buff, "")) {
        terminal_print("Unknown command\n\r");
      }
    }

    if(global_exit_flag) {
      touchExitActionReset();
      return;
    }
  }
}

void terminal_print(char *string) {
  int i;
  for(i = 0; i < strlen(string); i++) {
    terminal_print_char(string[i]);
  }
}

void terminal_print_char(char c) {
  // 0x00 Ignored
  if(c == 0x00) {
  }
  else if(c == 0x07) {
    beep_if_enabled();
  }
  else if(c == 0x08) {
    if(cursor_col > 0) cursor_col--;
  }
  else if(c == 0x09) {
    cursor_col = (cursor_col / 8 + 1) * 8;
  }
  else if(c == 0x0A) {
    cursor_row++;
  }
  else if(c == 0x0B) {
    cursor_row++;
  }
  else if(c == 0x0C) {
    terminal_clear_screen();
  }
  else if(c == 0x0D) {
    cursor_col = 0;
  }
  else if(c == 0x7F) {
    if(cursor_col > 0) cursor_col--;
    terminal_screen[cursor_col + cursor_row * TERMINAL_WIDTH_CHARS] = 0;
    terminal_colors[cursor_col + cursor_row * TERMINAL_WIDTH_CHARS] = current_color;
  }
  else {
    terminal_screen[cursor_col + cursor_row * TERMINAL_WIDTH_CHARS] = c;
    terminal_colors[cursor_col + cursor_row * TERMINAL_WIDTH_CHARS] = current_color;
    cursor_col++;
  }

  if(cursor_col >= TERMINAL_WIDTH_CHARS) {
    cursor_col = 0;
    cursor_row++;
  }
  if(cursor_row >= TERMINAL_HEIGHT_CHARS) {
    terminal_scroll_down();
    cursor_row = TERMINAL_HEIGHT_CHARS - 1;
  }
}

void terminal_show_screen() {
  int row, col;
  int color_fg;
  int color_bg;
  char buff[10];
  for(row = 0; row < TERMINAL_HEIGHT_CHARS; row++) {
    for(col = 0; col < TERMINAL_WIDTH_CHARS; col++) {
      if(terminal_screen[col + row * TERMINAL_WIDTH_CHARS]) {
        sprintf(buff, "%c", terminal_screen[col + row * TERMINAL_WIDTH_CHARS]);
      }
      else {
        strcpy(buff, " ");
      }
      color_fg = terminal_colors[col + row * TERMINAL_WIDTH_CHARS] & 0x0F;
      color_bg = terminal_colors[col + row * TERMINAL_WIDTH_CHARS] >> 4;
      if(row == cursor_row && col == cursor_col) {
        color_bg = COLOR_INDEX_GREEN;
      }
      tft.setTextColor(colors[color_fg], colors[color_bg]);
      tft.drawString(buff, col * 6, 16 + row * 8, FONT_MONOSPACE);
    }
  }
}

void terminal_scroll_down() {
  int row, col;
  for(row = 1; row < TERMINAL_HEIGHT_CHARS; row++) {
    for(col = 0; col < TERMINAL_WIDTH_CHARS; col++) {
      terminal_screen[col + (row - 1) * TERMINAL_WIDTH_CHARS] = terminal_screen[col + row * TERMINAL_WIDTH_CHARS];
      terminal_colors[col + (row - 1) * TERMINAL_WIDTH_CHARS] = terminal_colors[col + row * TERMINAL_WIDTH_CHARS];
    }
  }
  row = TERMINAL_HEIGHT_CHARS - 1;
  for(col = 0; col < TERMINAL_WIDTH_CHARS; col++) {
    terminal_screen[col + row * TERMINAL_WIDTH_CHARS] = 0;
    terminal_colors[col + row * TERMINAL_WIDTH_CHARS] = current_color;
  }
}

void terminal_clear_screen() {
  int i;
  current_color = 0x07;
  for(i = 0; i < TERMINAL_WIDTH_CHARS * TERMINAL_HEIGHT_CHARS; i++) {
    terminal_screen[i] = 0;
    terminal_colors[i] = current_color;
  }
  cursor_row = 0;
  cursor_col = 0;
  cursor_visible_flag = 1;
}

#define TERMINAL_INPUT_MAX 80

void terminal_input_string(char *input_buff) {
  char buff[80];
  static char prev_buff[80];
  int byte;
  int offset;
  for(offset = 0; offset < TERMINAL_INPUT_MAX; offset++) {
    buff[offset] = 0;
  }

  offset = 0;

  terminal_keyboard_redraw_flag = 1;

  while(1) {
    if(Serial.available()) {
      byte = Serial.read();
    }
    else {
      byte = terminal_input_char();
    }
    if(byte != -1) {
      if(byte == 0x00) {
        // Ignored
      }
      else if(byte == 0x03) {
        // Ctrl+C
        buff[0] = 0;
        strcpy(input_buff, buff);
        terminal_print_char('\n');
        terminal_print_char('\r');
        terminal_show_screen();
        return;
      }
      else if(byte == 0x04) {
        // Ctrl+D
        strcpy(input_buff, buff);
        terminal_print_char('\n');
        terminal_print_char('\r');
        terminal_show_screen();
        return;
      }
      else if(byte == 0x08) {
        if(offset > 0) {
          buff[strlen(buff) - 1] = 0;
          offset--;
          terminal_print_char(0x08);
          terminal_print_char(' ');
          terminal_print_char(0x08);
          terminal_show_screen();
        }
      }
      else if(byte == 0x09) {
        // Ignored
      }
      else if(byte == 0x0C) {
        // Ctrl+L
        buff[0] = 0;
        strcpy(input_buff, buff);
        return;
      }
      else if(byte == '\n') {
        strcpy(input_buff, buff);
        terminal_print_char('\n');
        terminal_print_char('\r');
        terminal_show_screen();
        return;
      }
      else if(strlen(buff) < (TERMINAL_INPUT_MAX - 1)) {
        buff[offset] = byte;
        offset++;
        buff[offset] = 0;
        terminal_print_char(byte);
        terminal_show_screen();
      }
    }

    if(global_exit_flag) {
      return;
    }
  }
}

int terminal_input_char() {
  int button;
  char **keyboard_current;
  static char symbol_flag = 0;
  static char caps_flag = 0;
  static char alt_keyboard_flag = 0;
  static char alt_flag = 0;
  static char ctrl_flag = 0;
  static char esc_flag = 0;
  
  char *control_buttons[] = {
    "Esc", "Ctrl", "Alt", "Tab", "<", ">", "U", "D",
    NULL
  };

  while(1) {
    if(symbol_flag) {
      keyboard_current = keyboard_symbol;
    }
    else if(caps_flag) {
      if(alt_keyboard_flag) {
        keyboard_current = alt_keyboard_enabled_flag ? keyboard_alt_caps : keyboard_caps;
      }
      else {
        keyboard_current = keyboard_caps;
      }
    }
    else {
      if(alt_keyboard_flag) {
        keyboard_current = alt_keyboard_enabled_flag ? keyboard_alt_nocaps : keyboard_nocaps;
      }
      else {
        keyboard_current = keyboard_nocaps;
      }
    }

    if(terminal_keyboard_redraw_flag) {
      drawButtonMatrix(0, 176, tft.width(), 24, control_buttons, 4, 1);
      drawButtonMatrix(0, 200, tft.width(), 120, keyboard_current, 12, 4);
      terminal_keyboard_redraw_flag = 0;
    }

    if(touchCheckNowait() == 0) {
      return -1;
    }
    touchWaitPress();

    button = touchCheckMatrix(0, 176, tft.width(), 24, control_buttons, 8, 1);
    if(button != -1) {
      if(button == 0) {
        return 0x1B;
      }
      else if(button == 1) {
        if(ctrl_flag) ctrl_flag = 0;
        else ctrl_flag = 1;
      }
      else if(button == 2) {
        if(alt_flag) alt_flag = 0;
        else alt_flag = 1;
      }
      else if(button == 3) {
        return 0x09;
      }
    }

    button = touchCheckMatrix(0, 200, tft.width(), 120, keyboard_current, 12, 4);
    if(button != -1) {
      if(button == 11) {
        return 0x08;
      }
      else if(button == 24) {
        caps_flag = !caps_flag;
      }
      else if(button == 36) {
        symbol_flag = !symbol_flag;
        if(!symbol_flag) {
          if(alt_keyboard_flag) {
            alt_keyboard_flag = 0;
          }
          else {
            alt_keyboard_flag = 1;
          }
        }
      }
      else {
        if(button == 35) {
          caps_flag = 0;
          return '\n';
        }
        else {
          caps_flag = 0;
          if(ctrl_flag) {
            return keyboard_current[button][0] & 0x1F;
          }
          else {
            return keyboard_current[button][0];
          }
        }
      }
    }

    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      return -1;
    }
    touchWaitRelease();
  }
}

int terminal_serial(char *arg) {
  long speed;
  int byte;

  while(1) {
    while(Serial.available()) {
      byte = Serial.read();
      if(byte == '\n') {
        Serial.print('\r');
        terminal_print_char('\r');
      }
      else if(byte == '\r') {
        Serial.print('\n');
        terminal_print_char('\n');
      }
      Serial.print((char)byte);
      terminal_print_char(byte);
      terminal_show_screen();
    }
    byte = terminal_input_char();
    if(byte != -1) {
      // Ctrl + C
      if(byte == 0x03) {
        return 0;
      }
      // Ctrl + D
      if(byte == 0x04) {
        return 0;
      }
      // Esc
      if(byte == 0x1B) {
        return 0;
      }
      else if(byte == '\n') {
        Serial.print('\r');
        terminal_print_char('\r');
      }
      Serial.print((char)byte);
      terminal_print_char((char)byte);
      terminal_show_screen();
    }
  }
}

int terminal_telnet(char *arg) {
  long speed;
  int byte;
  int port = 0;
  char host[80];
  WiFiClient client;

  sscanf(arg, "%s %d", host, &port);
  if(port == 0) {
    port = 23;
  }

  client.connect(host, port);
  if (client.connected()) {
    terminal_print("Connected\n\r");
    terminal_show_screen();
  }
  else {
    terminal_print("Not connected\n\r");
    terminal_show_screen();
    return 0;
  }

  while(1) {
    while(client.available()) {
      byte = client.read();
      if(byte == '\n') {
        //client.print('\r');
        terminal_print_char('\r');
      }
      else if(byte == '\r') {
        //client.print('\n');
        terminal_print_char('\n');
      }
      //client.print((char)byte);
      terminal_print_char(byte);
      terminal_show_screen();
    }
    if(!client.connected()) {
      terminal_print("Disconnected\n\r");
      terminal_show_screen();
      return 0;
    }
    byte = terminal_input_char();
    if(byte != -1) {
      // Esc
      if(byte == 0x1B) {
        client.stop();
        return 0;
      }
      else if(byte == '\n') {
        client.print('\r');
        client.print('\n');
        terminal_print_char('\r');
        terminal_print_char('\n');
      }
      else {
        client.print((char)byte);
        terminal_print_char((char)byte);
        terminal_show_screen();
      }
    }
  }
}

#ifdef IS_SSH_ENABLED

int terminal_ssh(char *arg) {
  long speed;
  int byte;
  int port = 22;
  int bytes_read;
  char host[80] = "example.com";
  char ssh_user[80] = "username";
  char ssh_pass[80] = "password";
  char buff[80];
  int rc;
  ssh_channel channel;
  ssh_session my_session = ssh_new();

  ssh_options_set(my_session, SSH_OPTIONS_HOST, host);
  ssh_options_set(my_session, SSH_OPTIONS_USER, ssh_user);
  rc = ssh_connect(my_session);
  if (rc != SSH_OK) {
    terminal_print("Error connecting to server\n\r");
    terminal_print((char *)ssh_get_error(my_session));
    terminal_print("\n\r");
    terminal_show_screen();
    ssh_free(my_session);
    return 0;
  }
  
  rc = ssh_userauth_password(my_session, NULL, ssh_pass);
  if (rc != SSH_AUTH_SUCCESS) {
    terminal_print("Error authenticating\n\r");
    terminal_print((char *)ssh_get_error(my_session));
    terminal_print("\n\r");
    terminal_show_screen();
    ssh_disconnect(my_session);
    ssh_free(my_session);
    return 0;
  }

  // Open channel
  channel = ssh_channel_new(my_session);
  if (channel == NULL) {
    terminal_print("Unable to open channel\n\r");
    terminal_show_screen();
    return 0;
  }

  // Open session
  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK) {
    terminal_print("Unable to open session\n\r");
    terminal_show_screen();
    ssh_channel_free(channel);
    return 0;
  }

  // Request PTY
  if (ssh_channel_request_pty(channel) != SSH_OK) {
      terminal_print("Unable to request PTY\n\r");
      terminal_show_screen();
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      return 0;
  }

  // Request shell
  if (ssh_channel_request_shell(channel) != SSH_OK) {
      terminal_print("Unable to request shell\n\r");
      terminal_show_screen();
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      return 0;
  }

  while(1) {
    bytes_read = ssh_channel_read(channel, buff, 1, 0);
    if(bytes_read > 0) {
      byte = buff[0];
      if(byte == '\n') {
        //client.print('\r');
        terminal_print_char('\r');
      }
      else if(byte == '\r') {
        //client.print('\n');
        terminal_print_char('\n');
      }
      //client.print((char)byte);
      terminal_print_char(byte);
      terminal_show_screen();
    }

    byte = terminal_input_char();
    if(byte != -1) {
      // Esc
      if(byte == 0x1B) {
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(my_session);
        ssh_free(my_session);
        return 0;
      }
      else if(byte == '\n') {
        //client.print('\r');
        //client.print('\n');
        terminal_print_char('\r');
        terminal_print_char('\n');
      }
      else {
        //client.print((char)byte);
        terminal_print_char((char)byte);
        terminal_show_screen();
      }
    }
  }
}

#endif

#ifdef IS_WIFI_ENABLED

int terminal_ping(char *ip) {
  char buff[80];
  int seq = 1;
  long prev_millis = 0;
  long total_count = 0;
  long reply_count = 0;
  float reply_sum = 0;
  float reply_min = -1;
  float reply_max = -1;
  while(touchCheckNowait() == 0) {
    total_count++;
    if(Ping.ping(ip, 1)) {
      sprintf(buff, "Reply %s: seq=%d t=%0.2f ms\n\r", ip, seq, Ping.averageTime());
      reply_count++;
      reply_sum += Ping.averageTime();
      if(reply_min == -1) {
        reply_min = Ping.averageTime();
      }
      else {
        reply_min = min(reply_min, Ping.averageTime());
      }
      if(reply_max == -1) {
        reply_max = Ping.averageTime();
      }
      else {
        reply_max = max(reply_max, Ping.averageTime());
      }
    }
    else {
      sprintf(buff, "Error pinging %s, seq=%d\n\r", ip, seq);
    }
    terminal_print(buff);
    terminal_show_screen();
    while(millis() - prev_millis < 1000) {
      if(touchCheckNowait()) break;
    }
    if(touchCheckNowait()) {
      sprintf(buff, "-- Statistics --\n\r");
      terminal_print(buff);
      sprintf(buff, "%d pkts transmitted, %d received\n\r", total_count, reply_count);
      terminal_print(buff);
      sprintf(buff, "Rtt min/avg/max = %0.2f/%0.2f/%0.2f ms\n\r", reply_min, reply_sum / total_count, reply_max);
      terminal_print(buff);
      terminal_show_screen();
      return 0;
    }
    prev_millis = millis();
    seq++;
  }
}
#endif

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
// Проигрыватель монофонических мелодий
// ====================================================

#define TUNES_PATH "/Tunes"

void tunes_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  if(action_index == 0) {
    // Редактируем новый файл
    sprintf(buff, "%s/%s", TUNES_PATH, "__New");
    //file = Storage.open(buff, FILE_WRITE);
    //file.close();
    edit_file("New tune", buff);

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
      pim_rename_file(TUNES_PATH, "__New", NULL);
    }
  }
  else if(action_index == 1) {
    // Воспроизведение
    sprintf(buff, "%s/%s", TUNES_PATH, filename);
    tunes_play(buff);
  }
  else if(action_index == 2) {
    // Редактируем существующий файл
    sprintf(buff, "%s/%s", TUNES_PATH, filename);
    edit_file("Edit tune", buff);

    // Меняем название в соответствии с содержимым
    pim_rename_file(TUNES_PATH, filename, NULL);
  }
  else if(action_index == 3) {
    if(drawConfirm("Delete this tune?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", TUNES_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void tunes_file_to_list(fs::File file, char *buff) {
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

void tunes_play(char *filename) {
  fs::File file;
  char buff[80];
  char byte;
  int offset = 0;
  char sharp_flag = 0;
  char dot_flag = 0;
  char tempo_flag = 0;
  char octave_flag = 0;
  char note;
  int note_octave;
  int note_length;
  int base_octave = 0;
  float freq;
  int length;
  int tempo = 60;
  float note_to_freq[] = {
    //   C      C#       D      D#       E       F      F#       G      G#       A      A#       B       C
    261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25
    };

  file = Storage.open(filename);
  // Пропустить первую строчку
  while(file.available()) {
      byte = file.read();
      if(byte == '\n' && file.peek() == '\r') file.read();
      if(byte == '\r' && file.peek() == '\n') file.read();

      if(byte == '\n' || byte == '\r') {
        break;
      }
  }
  while(file.available()) {
    // Считать до пробела, перевода строки или до конца файла
    offset = 0;
    buff[offset] = 0;
    sharp_flag = 0;
    dot_flag = 0;
    tempo_flag = 0;
    note_octave = 0;
    note_length = 0;
    note = 0;
    while(file.available()) {
      byte = file.read();
      if(byte == '\n' && file.peek() == '\r') file.read();
      if(byte == '\r' && file.peek() == '\n') file.read();

      if(byte == ' ' || byte == '\n' || byte == '\r') {
        break;
      }

      if(byte == '#') {
        sharp_flag = 1;
        continue;
      }
      if(byte == '.') {
        dot_flag = 1;
        continue;
      }

      if(byte >= 'a' && byte <= 'g') note = byte;
      if(byte >= 'A' && byte <= 'G') note = byte;
      if(byte == '-') note = byte;
      if(byte == 't' || byte == 'T') tempo_flag = 1;
      if(byte == 'o' || byte == 'O') octave_flag = 1;


      buff[offset] = byte;
      offset++;
      buff[offset] = 0;
    }

//Serial.println(buff);
//delay(100);

    // Воспроизвести
    if(tempo_flag) {
      sscanf(buff, "%c%d", &note, &tempo);
      continue;
    }
    else if(octave_flag) {
      sscanf(buff, "%c%d", &note, &base_octave);
      continue;
    }
    else {
      sscanf(buff, "%d%c%d", &note_length, &byte, &note_octave);
    }

//Serial.print("note_length = "); Serial.println(note_length);
//Serial.print("note = "); Serial.println(note);
//Serial.print("note_octave = "); Serial.println(note_octave);
//Serial.print("dot_flag = "); Serial.println(dot_flag ? 1 : 0);
//Serial.print("sharp_flag = "); Serial.println(sharp_flag ? 1 : 0);
//delay(100);
    freq = 0;
    if(note == 'c' || note == 'C') {
      if(sharp_flag) freq = note_to_freq[1];
      else freq = note_to_freq[0];
    }
    else if(note == 'd' || note == 'D') {
      if(sharp_flag) freq = note_to_freq[3];
      else freq = note_to_freq[2];
    }
    else if(note == 'e' || note == 'E') {
      if(sharp_flag) freq = note_to_freq[5];
      else freq = note_to_freq[4];
    }
    else if(note == 'f' || note == 'F') {
      if(sharp_flag) freq = note_to_freq[6];
      else freq = note_to_freq[5];
    }
    else if(note == 'g' || note == 'G') {
      if(sharp_flag) freq = note_to_freq[8];
      else freq = note_to_freq[7];
    }
    else if(note == 'a' || note == 'A') {
      if(sharp_flag) freq = note_to_freq[10];
      else freq = note_to_freq[9];
    }
    else if(note == 'b' || note == 'B') {
      if(sharp_flag) freq = note_to_freq[12];
      else freq = note_to_freq[11];
    }
    else if(note == '-') {
      freq = 0;
    }
    else {
      continue;
    }

    freq *= pow(2, note_octave + base_octave);
    length = 60000 / (tempo * note_length);
    if(dot_flag) length *= 1.5;

//Serial.print("freq = "); Serial.println(freq);
//Serial.print("length = "); Serial.println(length);
//delay(100);

    if(freq > 0) {
      tone(BUZZER_PIN, freq, length);
    }
    delay(length);
  }
  file.close();
}

void tunes(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Play", "Edit", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B00110110, B01101100,
    B01001001, B10010010,
    B01000000, B00000010,
    B01000000, B10000010,
    B01000000, B11000010,
    B01000000, B10100010,
    B01000000, B10010010,
    B01000011, B10000010,
    B01000111, B10000010,
    B01000111, B10000010,
    B01000011, B00000010,
    B01000000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Tunes");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Tunes", TUNES_PATH, tunes_file_to_list, buttons, tunes_action);
}

// ====================================================
// Проигрыватель MP3
// ====================================================

#define MUSIC_PATH "/Music"

void music_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  char old_path_filename[80];
  char new_path_filename[80];
  if(action_index == 0) {
    // Воспроизведение
    sprintf(buff, "%s/%s", MUSIC_PATH, filename);
    music_play(buff);
  }
  else if(action_index == 1) {
    // Переименование
    strcpy(buff, filename);
    if(drawPrompt("New file name", buff) == 0) {
      // Если название не пустое
      if(strcmp(buff, "")) {
        sprintf(old_path_filename, "%s/%s", MUSIC_PATH, filename);
        sprintf(new_path_filename, "%s/%s", MUSIC_PATH, buff);
        Storage.rename(old_path_filename, new_path_filename);
      }
    }
  }
  else if(action_index == 2) {
    if(drawConfirm("Delete this file?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", MUSIC_PATH, filename);
      Storage.remove(buff);
    }
  }
}

void music_file_to_list(fs::File file, char *buff) {
  sprintf(buff, "%s", file.name());
}

void music_play(char *filename) {
  drawError("Not implemented yet");
  /*Audio audio;
  fs::File file;
  Serial.println(filename);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21);
  //audio.setBufferSize(32000);
  audio.connecttoFS(FFat, filename);
  Serial.println("Loop...");
  while(1) {
    audio.loop();
  }*/
}

void music(char mode, char *io_buff) {
  char *buttons[] = {
    "Play", "Rename", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000110, B00000010,
    B01000101, B00000010,
    B01000100, B10000010,
    B01000100, B01000010,
    B01000100, B00100010,
    B01000100, B00100010,
    B01000100, B01000010,
    B01000100, B10000010,
    B01000101, B00000010,
    B01000110, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Music");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("Music", MUSIC_PATH, music_file_to_list, buttons, music_action);
}

// ====================================================
// Пароли
// ====================================================

#define PASSWORDS_PATH "/Passwords"
#define PASSWORDS_AES_BITS 256

char aes_encryption_key[32] __attribute__((aligned(4)));

void passwords_action(int action_index, char *filename) {
  fs::File file;
  char filename_with_path[80];
  char filename_with_path_new[80];
  char *data_in;
  char *data_out;
  int data_length;
  int index;
  if(action_index == 0) {
    // Редактируем новый файл
    sprintf(filename_with_path_new, "%s/%s", PASSWORDS_PATH, "__New");
    edit_file("New password", filename_with_path_new);

    file = Storage.open(filename_with_path_new);
    if(!file) {
      return;
    }
    else if(file.size() == 0) {
      file.close();
      Storage.remove(filename_with_path_new);
    }
    else {
      file.close();
      // Меняем название на первое свободное число
      index = 1;
      while(1) {
        sprintf(filename_with_path, "%s/%d", PASSWORDS_PATH, index);
        file = Storage.open(filename_with_path);
        if(file) {
          file.close();
        }
        else {
          break;
        }
        index++;
      }

      passwords_file_encrypt(filename_with_path);
    }
  }
  else if(action_index == 1) {
    // Редактируем существующий файл
    sprintf(filename_with_path_new, "%s/%s", PASSWORDS_PATH, "__New");
    sprintf(filename_with_path, "%s/%s", PASSWORDS_PATH, filename);

    // Расшифровываем если не __New
    if(strcmp(filename_with_path, filename_with_path_new)) {
      passwords_file_decrypt(filename_with_path);
    }
    // Придумываем новое название если __New
    else {
      // Меняем название на первое свободное число
      index = 1;
      while(1) {
        sprintf(filename_with_path, "%s/%d", PASSWORDS_PATH, index);
        file = Storage.open(filename_with_path);
        if(file) {
          file.close();
        }
        else {
          break;
        }
        index++;
      }
    }

    // Редактируем
    edit_file("Edit password", filename_with_path_new);

    // Шифруем обратно
    passwords_file_encrypt(filename_with_path);

    free(data_out);
    free(data_in);
  }
  else if(action_index == 2) {
    if(drawConfirm("Delete this password?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(filename_with_path, "%s/%s", PASSWORDS_PATH, filename);
      Storage.remove(filename_with_path);
    }
  }
}

void passwords_file_encrypt(char *filename_with_path) {
  fs::File file;
  char filename_with_path_new[80];
  char *data_in = NULL;
  char *data_out = NULL;

  data_in = (char *)malloc(EDIT_FILE_LENGTH_MAX * sizeof(char));
  if(!data_in) {
    drawError("Cannot allocate memory");
    return;
  }
  data_out = (char *)malloc((EDIT_FILE_LENGTH_MAX + 16) * sizeof(char));
  if(!data_out) {
    free(data_in);
    drawError("Cannot allocate memory");
    return;
  }

  sprintf(filename_with_path_new, "%s/%s", PASSWORDS_PATH, "__New");
  // Читаем
  read_file_to_buff(filename_with_path_new, EDIT_FILE_LENGTH_MAX, data_in);

  // Шифруем
  encryptAES((uint8_t*) data_in, strlen(data_in) + 1, (uint8_t*) data_out, (((strlen(data_in) + 1) / 16) + 1) * 16);
  //strcpy(data_out, data_in);

  // Записываем двочиный файл
  // write_file_from_buff только для текстовых файлов
  file = Storage.open(filename_with_path, FILE_WRITE);
  file.write((const uint8_t *)data_out, 16 + (((strlen(data_in) + 1) / 16) + 1) * 16);
  file.close();

  // Удалить расшифрованный файл
  Storage.remove(filename_with_path_new);

  free(data_in);
  free(data_out);
}

void passwords_file_decrypt(char *filename_with_path) {
  fs::File file;
  char filename_with_path_new[80];
  char *data_in = NULL;
  char *data_out = NULL;
  long file_size = 0;

  // Нужен размер файла
  file = Storage.open(filename_with_path);
  file_size = file.size();
  file.close();
  
  data_in = (char *)malloc((EDIT_FILE_LENGTH_MAX + 16) * sizeof(char));
  if(!data_in) {
    drawError("Cannot allocate memory");
    return;
  }
  data_out = (char *)malloc(EDIT_FILE_LENGTH_MAX * sizeof(char));
  if(!data_out) {
    free(data_in);
    drawError("Cannot allocate memory");
    return;
  }

  // Читаем двоичный файл (!)
  // read_file_to_buff только для текстовых файлов
  file = Storage.open(filename_with_path);
  file.read((unsigned char*)data_in, file.size());
  file.close();
  //read_file_to_buff(filename_with_path, EDIT_FILE_LENGTH_MAX + 16, data_in);
  
  // Расшифровываем
  decryptAES((uint8_t*) data_in, file_size, (uint8_t*) data_out);
  //strcpy(data_out, data_in);

  // Записываем в __New
  sprintf(filename_with_path_new, "%s/%s", PASSWORDS_PATH, "__New");
  write_file_from_buff(filename_with_path_new, data_out);

  // Исходный файл не трогаем

  free(data_in);
  free(data_out);
}

void passwords_file_to_list(fs::File file, char *buff) {
  char left[82];
  char right[80];
  char byte;
  int offset;
  // Левая колонка - первая строчка файла
  offset = 0;
  memset(left, 0, 80);
  
  // Читаем первые 80 байт, из них первые 16 байт вектор инициализации, 64 байта шифрованных данных
  while(file.available()) {
    byte = file.read();
    left[offset] = byte;
    offset++;
    left[offset] = 0;
    if(offset > 80) {
      break;
    }
  }

  if(strcmp(file.name(), "__New") == 0) {
    // Файл __New не расшифровывать, дописать в название что он незашифрован
    strcpy(right, "!Unencrypted!");
    for(offset = 0; offset < 20; offset++) {
      right[strlen(right) + 1] = 0;
      right[strlen(right)] = left[offset];
    }
  }
  else {
    // Остальные расшифровывать, первые 64 байта
    decryptAES((uint8_t*) left, min(64, (int)file.size()), (uint8_t*) right);
//Serial.println(__LINE__);
  }

  // Обрезать название до первого перевода строки
//Serial.println(__LINE__);
  for(offset = 0; offset < 64; offset++) {
    if(right[offset] == '\n') {
      right[offset] = 0;
      break;
    }
  }
//Serial.println(__LINE__);
  right[offset] = 0;
//Serial.println(right);
  sprintf(buff, "%s", right);
}

void passwords(char mode, char *io_buff) {
  int i;
  char buff[80];
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
    B01000111, B11100010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01000111, B11100010,
    B01000001, B00000010,
    B01000001, B00000010,
    B01000001, B11000010,
    B01000001, B10000010,
    B01000001, B11000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Passwords");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  buff[0] = 0;
  if(drawPrompt("Enter password:", buff) == 0) {
    // Пароль - первые 16 символов, дополненные нулями 
    memset(aes_encryption_key, 0, 32);
    for(i = 0; i < 32; i++) {
      aes_encryption_key[i] = buff[i];
      if(buff[i] == 0) break;
    }
    pim_app("Passwords", PASSWORDS_PATH, passwords_file_to_list, buttons, passwords_action);
  }
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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);

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
        tft.fillRect(0, 16, tft.width(), tft.height() - 16 - 32 + 1, color_scheme_bg);
      }
      prev_day = day;

      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
            tft.fillRect(cal_col * tft.width() / 7, 70 + cal_row * 32 - 8, tft.width() / 7, 32, color_scheme_selection_bg);
            tft.setTextColor(color_scheme_selection_fg, color_scheme_selection_bg);
          }
          else {
            tft.setTextColor(color_scheme_fg, color_scheme_bg);
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

    tft.fillRect(0, 16, tft.width(), 100, color_scheme_bg);
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
        tft.fillRect(0, 16, tft.width(), tft.height(), color_scheme_bg);
        continue;
      }

      // Смена информации о владельце
      if(button_pressed == 0) {
        if(drawPrompt("Enter owner info", owner_info) == 0) {
          write_file_from_buff("/Settings/Owner", owner_info);
        }
        tft.fillRect(0, 16, tft.width(), tft.height(), color_scheme_bg);
      }
      // Смена пароля
      else if(button_pressed == 1) {
        if(drawPrompt("Enter new password (digits only)", user_input) == 0) {
          write_file_from_buff("/Settings/Password", user_input);
        }
        tft.fillRect(0, 16, tft.width(), tft.height(), color_scheme_bg);
      }
      // Удаление пароля
      else if(button_pressed == 2) {
        Storage.remove("/Settings/Password");
        drawInfo("Password deleted");
        tft.fillRect(0, 16, tft.width(), tft.height(), color_scheme_bg);
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
    tft.fillRect(0, 16, tft.width(), 30, color_scheme_bg);

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
      tft.fillRect(0, 16, tft.width(), 34, color_scheme_bg);
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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

      tft.fillRect(0, 16, tft.width(), 34, color_scheme_bg);
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
          tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
          minutes = preset_minutes;
          seconds = preset_seconds;
          timer_run = 0;
          redraw_flag = 1;
          continue;
        }
        else {
          start_millis = millis();
          beep_if_enabled();
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    tft.drawCentreString(buff, tft.width() / 2, 20, FONT_BIG);

    // Если таймер запущен и касаний нет - остальное не рисуем
    if(stopwatch_run && touchCheckNowait() == 0 && redraw_flag == 0) {
      continue;
    }

    drawButtonMatrix(0, 52, tft.width(), 64, buttons_control, 4, 1);
    drawButtonMatrix(0, 288, tft.width(), 32, buttons_lap_control, 2, 1);

    tft.setTextColor(color_scheme_fg, color_scheme_bg);

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
          beep_if_enabled();
          tft.fillRect(0, 16, tft.width(), 132, color_scheme_bg);
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
          beep_if_enabled();
          tft.fillRect(0, 16, tft.width(), 132, color_scheme_bg);
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
          beep_if_enabled();
          tft.fillRect(0, 16, tft.width(), 132, color_scheme_bg);
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
          beep_if_enabled();
          tft.fillRect(0, 16, tft.width(), 132, color_scheme_bg);
          step_start_millis = millis();
          step = 0;
        }
      }

      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
        tft.fillRect(0, 16, tft.width(), 132, color_scheme_bg);
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
        cell_color = color_scheme_bg;
        if(life_get_cell(x, y, field)) {
          cell_color = color_scheme_fg;
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
  int hiscore = length;
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
  
  tft.drawLine(0, 16, tft.width(), tft.height(), color_scheme_fg);
  tft.drawLine(tft.width(), 16, 0, tft.height(), color_scheme_fg);
  tft.setTextColor(color_scheme_fg, color_scheme_bg);
  tft.drawCentreString("UP", tft.width() / 2, tft.height() / 4, FONT_DEFAULT);
  tft.drawCentreString("DOWN", tft.width() / 2, 3 * tft.height() / 4, FONT_DEFAULT);
  tft.drawCentreString("LEFT", tft.width() / 4, tft.height() / 2, FONT_DEFAULT);
  tft.drawCentreString("RIGHT", 3 * tft.width() / 4, tft.height() / 2, FONT_DEFAULT);
  touchWaitPress();
  touchWaitRelease();

  restart_flag = 1;
  while(1) {
    if(restart_flag) {
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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
        if(length > hiscore) hiscore = length;
        beep_if_enabled();
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    sprintf(buff, "Length: %d", length);
    tft.drawString(buff, 1, 16, FONT_DEFAULT);
    sprintf(buff, "Hi-score: %d", hiscore);
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


void turkish_kerchief(char mode, char *io_buff) {
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
    strcpy(io_buff, "Turkish Kerchief");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Turkish Kerchief");
  
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

void color_settings(char mode, char *io_buff) {
  int scheme_offset = 0;
  int scheme_selected = 0;
  int i;
  int inversion;
  int button_pressed;
  char redraw_flag;
  char buff[80];
  char *scheme_text;
  char *color_schemes[] = {
    "Classic",
    "Yellow",
    "Black & White",
    "Red",
    "Green",
    "Night",
    "Random",
    NULL
  };
  char *buttons_apply[] = {
    "Apply",
    NULL
  };
  char *buttons_inversion[] = {
    "Inversion", NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000110,
    B01000000, B00001110,
    B01000000, B00011110,
    B01000000, B00111110,
    B01000000, B01111110,
    B01000000, B11111110,
    B01000001, B11111110,
    B01000011, B11111110,
    B01000111, B11111110,
    B01001111, B11111110,
    B01011111, B11111110,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Color Settings");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  if(read_file_to_buff("/Settings/Inversion", 79, buff)) {
    sscanf(buff, "%d", &inversion);
    tft.invertDisplay(inversion ? true : false);
  }

  redraw_flag = 1;
  while(1) {
    if(redraw_flag) {
      clearScreen();
      drawAppTitle("Color Settings");
      redraw_flag = 0;
    }

    drawButtonMatrix(0, 32, tft.width() / 2, 32, buttons_inversion, 1, 1);
    drawButtonMatrix(0, tft.height() - 32, tft.width(), 32, buttons_apply, 1, 1);

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    if(inversion) {
      tft.drawCentreString(" on ", 3 * tft.width() / 4, 40, FONT_DEFAULT);
    }
    else {
      tft.drawCentreString(" off ", 3 * tft.width() / 4, 40, FONT_DEFAULT);
    }

    tft.drawString("Color scheme:", 1, 70, FONT_DEFAULT);

    touchCheckList(0, 86, tft.width(), tft.height() - 70 - 32 - 26, color_schemes, 12, &scheme_offset, &scheme_selected);
    drawList(0, 86, tft.width(), tft.height() - 70 - 32 - 26, color_schemes, 12, &scheme_offset, &scheme_selected);
    
    touchWaitPress();
    touchCheckList(0, 86, tft.width(), tft.height() - 70 - 32 - 26, color_schemes, 12, &scheme_offset, &scheme_selected);

    button_pressed = touchCheckMatrix(0, 32, tft.width() / 2, 32, buttons_inversion, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        if(inversion) {
          inversion = 0;
        }
        else {
          inversion = 1;
        }
        tft.invertDisplay(inversion ? true : false);
      }
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, tft.height() - 32, tft.width(), 32, buttons_apply, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        // Classic
        if(scheme_selected == 0) {
          // Цвет фона и текста
          color_scheme_bg = colors[COLOR_INDEX_WHITE];
          color_scheme_fg = colors[COLOR_INDEX_BLACK];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[COLOR_INDEX_BLUE];
          color_scheme_title_fg = colors[COLOR_INDEX_WHITE];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[COLOR_INDEX_BLUE];
          color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[COLOR_INDEX_LIGHTGREY];
          color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[COLOR_INDEX_DARKGREY];
          color_scheme_button_active_fg = colors[COLOR_INDEX_BLACK];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[COLOR_INDEX_LIGHTGREY];
          // Цвет ссылки
          color_scheme_link_fg = colors[COLOR_INDEX_BLUE];
        }
        // Yellow
        else if(scheme_selected == 1) {
          // Цвет фона и текста
          color_scheme_bg = colors[COLOR_INDEX_WHITE];
          color_scheme_fg = colors[COLOR_INDEX_BLACK];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[COLOR_INDEX_YELLOW];
          color_scheme_title_fg = colors[COLOR_INDEX_BLACK];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[COLOR_INDEX_YELLOW];
          color_scheme_selection_fg = colors[COLOR_INDEX_BLACK];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[COLOR_INDEX_LIGHTGREY];
          color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[COLOR_INDEX_DARKGREY];
          color_scheme_button_active_fg = colors[COLOR_INDEX_BLACK];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[COLOR_INDEX_LIGHTGREY];
          // Цвет ссылки
          color_scheme_link_fg = colors[COLOR_INDEX_BLUE];
        }
        // Black & White
        else if(scheme_selected == 2) {
          // Цвет фона и текста
          color_scheme_bg = colors[COLOR_INDEX_WHITE];
          color_scheme_fg = colors[COLOR_INDEX_BLACK];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[COLOR_INDEX_BLACK];
          color_scheme_title_fg = colors[COLOR_INDEX_WHITE];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[COLOR_INDEX_BLACK];
          color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[COLOR_INDEX_WHITE];
          color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[COLOR_INDEX_BLACK];
          color_scheme_button_active_fg = colors[COLOR_INDEX_WHITE];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[COLOR_INDEX_WHITE];
          // Цвет ссылки
          color_scheme_link_fg = colors[COLOR_INDEX_WHITE];
        }
        // Red
        else if(scheme_selected == 3) {
          // Цвет фона и текста
          color_scheme_bg = colors[COLOR_INDEX_WHITE];
          color_scheme_fg = colors[COLOR_INDEX_BLACK];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[COLOR_INDEX_RED];
          color_scheme_title_fg = colors[COLOR_INDEX_WHITE];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[COLOR_INDEX_RED];
          color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[COLOR_INDEX_LIGHTGREY];
          color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[COLOR_INDEX_DARKGREY];
          color_scheme_button_active_fg = colors[COLOR_INDEX_BLACK];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[COLOR_INDEX_LIGHTGREY];
          // Цвет ссылки
          color_scheme_link_fg = colors[COLOR_INDEX_BLUE];
        }
        // Green
        else if(scheme_selected == 4) {
          // Цвет фона и текста
          color_scheme_bg = colors[COLOR_INDEX_WHITE];
          color_scheme_fg = colors[COLOR_INDEX_BLACK];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[COLOR_INDEX_GREEN];
          color_scheme_title_fg = colors[COLOR_INDEX_WHITE];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[COLOR_INDEX_GREEN];
          color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[COLOR_INDEX_LIGHTGREY];
          color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[COLOR_INDEX_DARKGREY];
          color_scheme_button_active_fg = colors[COLOR_INDEX_BLACK];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[COLOR_INDEX_LIGHTGREY];
          // Цвет ссылки
          color_scheme_link_fg = colors[COLOR_INDEX_BLUE];
        }
        // Night
        else if(scheme_selected == 5) {
          // Цвет фона и текста
          color_scheme_bg = colors[COLOR_INDEX_BLACK];
          color_scheme_fg = colors[COLOR_INDEX_LIGHTGREY];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[COLOR_INDEX_NAVY];
          color_scheme_title_fg = colors[COLOR_INDEX_BLUE];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[COLOR_INDEX_NAVY];
          color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[COLOR_INDEX_BLACK];
          color_scheme_button_fg = colors[COLOR_INDEX_WHITE];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[COLOR_INDEX_NAVY];
          color_scheme_button_active_fg = colors[COLOR_INDEX_WHITE];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[COLOR_INDEX_DARKGREY];
          // Цвет ссылки
          color_scheme_link_fg = colors[COLOR_INDEX_NAVY];
        }
        // Random
        else if(scheme_selected == 6) {
          // Цвет фона и текста
          color_scheme_bg = colors[random(0, 16)];
          color_scheme_fg = colors[random(0, 16)];
          // Цвет заголовка и текста
          color_scheme_title_bg = colors[random(0, 16)];
          color_scheme_title_fg = colors[random(0, 16)];
          // Цвет выделения и текста
          color_scheme_selection_bg = colors[random(0, 16)];
          color_scheme_selection_fg = colors[random(0, 16)];
          // Цвет кнопки и текста
          color_scheme_button_bg = colors[random(0, 16)];
          color_scheme_button_fg = colors[random(0, 16)];
          // Цвет нажатой кнопки и текста
          color_scheme_button_active_bg = colors[random(0, 16)];
          color_scheme_button_active_fg = colors[random(0, 16)];
          // Цвет неактивного текста
          color_scheme_inactive_fg = colors[random(0, 16)];
          // Цвет ссылки
          color_scheme_link_fg = colors[random(0, 16)];
        }
      }
      redraw_flag = 1;
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();

      if(drawConfirm("Save settings?") == 0) {
        sprintf(buff, "%d", inversion);
        write_file_from_buff("/Settings/Inversion", buff);

        scheme_text = (char*)malloc(2000);
        scheme_text[0] = 0;
        sprintf(buff, "background=%d\n", color_to_index(color_scheme_bg));
        strcat(scheme_text, buff);
        sprintf(buff, "foreground=%d\n", color_to_index(color_scheme_fg));
        strcat(scheme_text, buff);
        sprintf(buff, "title_background=%d\n", color_to_index(color_scheme_title_bg));
        strcat(scheme_text, buff);
        sprintf(buff, "title_foreground=%d\n", color_to_index(color_scheme_title_fg));
        strcat(scheme_text, buff);
        sprintf(buff, "selection_background=%d\n", color_to_index(color_scheme_selection_bg));
        strcat(scheme_text, buff);
        sprintf(buff, "selection_foreground=%d\n", color_to_index(color_scheme_selection_fg));
        strcat(scheme_text, buff);
        sprintf(buff, "button_background=%d\n", color_to_index(color_scheme_button_bg));
        strcat(scheme_text, buff);
        sprintf(buff, "button_foreground=%d\n", color_to_index(color_scheme_button_fg));
        strcat(scheme_text, buff);
        sprintf(buff, "button_active_background=%d\n", color_to_index(color_scheme_button_active_bg));
        strcat(scheme_text, buff);
        sprintf(buff, "button_active_foreground=%d\n", color_to_index(color_scheme_button_active_fg));
        strcat(scheme_text, buff);
        sprintf(buff, "inactive_foreground=%d\n", color_to_index(color_scheme_inactive_fg));
        strcat(scheme_text, buff);
        sprintf(buff, "link_foreground=%d\n", color_to_index(color_scheme_link_fg));
        strcat(scheme_text, buff);
        write_file_from_buff("/Settings/Colors", scheme_text);
        free(scheme_text);
      }
      touchExitActionReset();
      return;
    }

    touchWaitRelease();
  }
}

int color_to_index(int color) {
  int i;
  for(i = 0; i < 16; i++) {
    if(colors[i] == color) return i;
  }
  return 0;
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
    tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
    if(rescan_flag) {
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
            sprintf(buff2, "3 pings avg=%0.2f ms", Ping.averageTime());
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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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
  if(get_file_https("https://arikado.ru/cyd/unixtime.php", buff) == 200) {
    sscanf(buff, "%lu", &global_unixtime_retrieved);
    global_unixtime_retrieved_millis = millis();
  }
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

    tft.fillRect(0, 16, tft.width(), 16 - 1, color_scheme_inactive_fg);
    tft.setTextColor(color_scheme_fg, color_scheme_inactive_fg);
    tft.drawString(address, 1, 20, FONT_MONOSPACE);

    // Выводим всё
    tft.fillRect(0, 32, tft.width(), tft.height() - 32, color_scheme_bg);
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
      //Serial.println(line);
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
        tft.setTextColor(color_scheme_fg, color_scheme_bg);
      }
      else if(line_type == '0' || line_type == '1') {
        if(get_touch_address && touch_line == screen_offset) {
          tft.setTextColor(color_scheme_bg, color_scheme_link_fg);
          sprintf(address_to_go, "%s:%s/%c%s", server, port, line_type, path);
        }
        else {
          tft.setTextColor(color_scheme_link_fg, color_scheme_bg);
        }
      }
      else if(line_type == '7') {
        if(get_touch_address && touch_line == screen_offset) {
          tft.setTextColor(color_scheme_bg, color_scheme_link_fg);
          strcpy(query, "");
          drawPrompt("Query", query);
          sprintf(address_to_go, "%s:%s/%c%s\t%s", server, port, line_type, path, query);
        }
        else {
          tft.setTextColor(color_scheme_link_fg, color_scheme_bg);
        }
      }
      else if(line_type == '3') {
        tft.setTextColor(TFT_RED, color_scheme_bg);
      }
      else {
        tft.setTextColor(color_scheme_inactive_fg, color_scheme_bg);
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
  int button_pressed;
  int wifi_status;
  long prev_update_data_millis;
  int i;
  char url[80];
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
      sprintf(url, "https://arikado.ru/cyd/weather.php?lat=%f&lon=%f", global_lat, global_lon);
      if(get_file_https(url, buff) == 200) {
        prev_update_data_millis = millis();

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
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
        tft.setTextColor(color_scheme_fg, color_scheme_bg);
        tft.drawCentreString(temp, tft.width() / 2, 35, FONT_BIGGER);

        tft.drawCentreString(wind, tft.width() / 2, 100, FONT_BIG);
        tft.drawCentreString(weather, tft.width() / 2, 150, FONT_DEFAULT);
        update_flag = 0;
      }
    }

    drawButtonMatrix(0, tft.height() - 96, tft.width() / 2, 96, buttons, 1, 3);
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    sprintf(buff, "%f", global_lat);
    tft.drawCentreString(buff, 3 * tft.width() / 4, tft.height() - 64 + 8, FONT_DEFAULT);
    sprintf(buff, "%f", global_lon);
    tft.drawCentreString(buff, 3 * tft.width() / 4, tft.height() - 32 + 8, FONT_DEFAULT);

    while(!touchCheckNowait()) {
      tft.setTextColor(color_scheme_inactive_fg, color_scheme_bg);
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
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
      }
      else if(button_pressed == 2) {
        sprintf(buff, "%f", global_lon);
        drawPrompt("Enter longitude", buff);
        if(strlen(buff) > 0) {
          sscanf(buff, "%f", &global_lon);
          sprintf(buff, "%f %f", global_lat, global_lon);
          write_file_from_buff("/Settings/Coordinates", buff);
        }
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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
  tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
  
  messages = (char*)malloc(2048 * sizeof(char));
  prev_messages = (char*)malloc(2048 * sizeof(char));
  query = (char*)malloc(300 * sizeof(char));

  messages[0] = 0;
  prev_messages[0] = 0;

  update_flag = 1;
  while(1) {
    if(update_flag) {
      if(get_file_https("https://arikado.ru/cyd/chat_data.txt", messages) == 200) {
        // Если сообщения изменились - бибикнуть
        if(strlen(prev_messages) > 0 && strcmp(messages, prev_messages)) {
          beep_if_enabled();
        }
        strcpy(prev_messages, messages);
        screen_line = 0;
        buff_offset = 0;
        memset(buff, ' ', 40);
        buff[40] = 0;
        tft.setTextColor(color_scheme_fg, color_scheme_bg);
        
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
      tft.setTextColor(color_scheme_inactive_fg, color_scheme_bg);
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
            sprintf(query, "https://arikado.ru/cyd/chat_post.php?nickname=%s&message=%s", nickname, message);
            if(get_file_https(query, buff) == 200) {
              if(strcmp(buff, "ok")) {
                drawError(buff);
              }
              else {
                strcpy(message, "");
              }
            }
            else {
              drawError("Sending error");
            }
          }
          else {
            drawError("Message too long");
          }
        }
        update_flag = 1;
      }
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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

  tft.setTextColor(color_scheme_fg, color_scheme_bg);
  tft.drawString("Use next URL to control files:", 1, 20, FONT_DEFAULT);
  sprintf(buff, "http://%s/", WiFi.localIP().toString());
  tft.drawString(buff, 1, 36, FONT_DEFAULT);

  httpServer.begin();
  httpServer.on("/", http_file_access_handle);
  httpServer.on("/backup_and_restore", http_file_backup_and_restore_handle);
  httpServer.on("/backup", http_fs_backup_handle);
  httpServer.on("/restore", HTTP_POST, http_file_upload_handle_done, http_fs_restore_handle);
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

void http_file_backup_and_restore_handle() {
  char *contents = "<a href='/'>Back</a> or <a href='/backup'>Download FFat backup</a><br>"
  "<form method='POST' action='/restore' enctype='multipart/form-data'>"
  "<p>Upload file to restore:</p>"
  "<input type=file name=file>\n<input type=submit value='Upload'>\n"
  "</form>"
  ;
  httpServer.send(200, "text/html", contents);
}

void http_fs_backup_handle() {
  FFatContentsStream ffat_stream;
  httpServer.sendHeader("Content-Disposition", "attachment; filename=\"fs.bin\"");
  httpServer.streamFile(ffat_stream, "text/plain");
}

fs::File uploadFile;
FFatContentsStream ffat_restore_stream;

void http_fs_restore_handle() {
  int i;
  HTTPUpload& upload = httpServer.upload();

  if (upload.status == UPLOAD_FILE_START) {
  } 
  else if (upload.status == UPLOAD_FILE_WRITE) {
    Serial.printf("Uploaded chunk size %d\n", upload.currentSize);
    for(i = 0; i < upload.currentSize; i++) {
      ffat_restore_stream.write(upload.buf[i]);
    }
  } 
  else if (upload.status == UPLOAD_FILE_END) {
    ffat_restore_stream.flush();
    // Обновляем ФС
    if(FFat.begin(FORMAT_FS_IF_FAILED)) {
      Serial.println("Restore ok");
    }
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
      sprintf(buff, "Used: %d bytes of %d bytes (%d %%)", Storage.usedBytes(), Storage.totalBytes(), (int)floor(100 * Storage.usedBytes() / Storage.totalBytes()));
      strcat(contents, buff);
      strcat(contents, " (<a href='/backup_and_restore'>backup and restore</a>)<br>\n");
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
  //Serial.println(path);
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

    //Serial.printf("Start upload: %s\n", filename.c_str());
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
      //Serial.printf("Upload success: %u bytes\n", upload.totalSize);
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

int get_file_http(char *url, char *buff) {
  HTTPClient http;
  int httpResponseCode;
  http.begin(url);
  httpResponseCode = http.GET();
  if(httpResponseCode > 0) {
    strcpy(buff, http.getString().c_str());
    http.end();
    return httpResponseCode;
  }
  http.end();
  return 0;
}

int get_file_https(char *url, char *buff) {
  int httpResponseCode;
  char byte;
  int offset;
  WiFiClientSecure *client = new WiFiClientSecure;
  HTTPClient https;
  WiFiClient* stream;

  //Serial.println(url);

  if(client) {
    client->setInsecure();
    if (https.begin(*client, url)) {
      httpResponseCode = https.GET();
      //Serial.println(httpResponseCode);
      //Serial.println(https.errorToString(httpResponseCode));
      if (httpResponseCode > 0) {
        strcpy(buff, https.getString().c_str());
        // Чтение через stream добавляет лишние байты (?!)
        /*stream = https.getStreamPtr();
        offset = 0;
        while(stream->available()) {
          byte = stream->read();
          buff[offset] = byte;
          offset++;
          buff[offset] = 0;
        }*/
        //Serial.println(offset);
        //Serial.println("---");
        //Serial.println(buff);
        //Serial.println("---");
        https.end();
      }
      https.end();
      return httpResponseCode;
    }
  }
  return 0;
}

void utf8_to_cp1251(char *buff) {
  int read_offset = 0;
  int write_offset = 0;
  unsigned char byte;
  int length = strlen(buff);
  while(read_offset < length) {
    byte = buff[read_offset];
    read_offset++;
    if(byte == 0xC2) {
      // Кавычки-ёлочки
      if(buff[read_offset] == 0xAB) {
        byte = '"';
      }
      if(buff[read_offset] == 0xBB) {
        byte = '"';
      }
      read_offset++;
    }
    else if(byte == 0xD0) {
      //Serial.println("---");
      //Serial.println((int)byte, HEX);
      //Serial.println((int)buff[read_offset], HEX);
      if(buff[read_offset] == 0x81) {
        byte = 0xA8; // Ё
      }
      else if(buff[read_offset] < 0xA0) {
        byte = 0xC0 + buff[read_offset] - 0x90; // А-П
      }
      else {
        byte = 0xD0 + buff[read_offset] - 0xA0; // Р-Я а-п
      }
      //Serial.println((int)byte, HEX);
      read_offset++;
    }
    else if(byte == 0xD1) {
      if(buff[read_offset] == 0x91) {
        byte = 0xB8; // ё
      }
      else {
        byte = 0xF0 + buff[read_offset] - 0x80; // р-я
      }
      read_offset++;
    }
    
    buff[write_offset] = byte;
    write_offset++;
  }
  buff[write_offset] = 0;
}

// ====================================================
// Читалка RSS
// ====================================================

#define RSS_PATH "/RSS"

void rss_action(int action_index, char *filename) {
  fs::File file;
  char buff[80];
  char name[80];
  char *data;
  char name_line_flag;
  char byte;
  int offset;
  int http_code;

  if(action_index == 0) {
    // Редактируем новый файл
    sprintf(buff, "%s/%s", RSS_PATH, "__New");
    //file = Storage.open(buff, FILE_WRITE);
    //file.close();
    edit_file("New RSS", buff);

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
      pim_rename_file(RSS_PATH, "__New", NULL);
    }
  }
  else if(action_index == 1) {
    // Чтение RSS
    // Получить ссылку
    sprintf(buff, "%s/%s", RSS_PATH, filename);
    file = Storage.open(buff);
    name_line_flag = 1;
    offset = 0;
    while(file.available()) {
      byte = file.read();
      if(byte == '\n') {
        offset = 0;
        if(name_line_flag) {
          name_line_flag = 0;
          continue;
        }
        else {
          break;
        }
      }
      if(name_line_flag) {
        name[offset] = byte;
        offset++;
        name[offset] = 0;
      }
      else {
        buff[offset] = byte;
        offset++;
        buff[offset] = 0;
      }
      if(offset > 79) {
        break;
      }
    }

    //Serial.println(name);
    //Serial.println(buff);

    // Резервируем память
    data = (char*)malloc(20000 * sizeof(char));
    if(!data) {
      drawError("Unable to reserve memory");
      return;
    }

    // Получить данные в XML
    data[0] = 0;
    if(buff[4] == 's') {
      //Serial.println("Before https");
      
      http_code = get_file_https(buff, data);
      if(http_code != 200) {
        sprintf(buff, "Error %d", http_code);
        drawError(buff);
        free(data);
        return;
      }
      //Serial.println("After https");
    }
    else {
      //Serial.println("Before http");
      http_code = get_file_http(buff, data);
      if(http_code != 200) {
        sprintf(buff, "Error %d", http_code);
        drawError(buff);
        free(data);
        return;
      }
      //Serial.println("After http");
    }

    // Нет данных
    if(strcmp(data, "") == 0) {
      drawError("No data");
      free(data);
      return;
    }
    // Убрать лишнее
    utf8_to_cp1251(data);
    rss_convert_to_text(data);

    // Просмотр текста из памяти
    view_text(name, data);
    free(data);
  }
  else if(action_index == 2) {
    // Редактируем существующий файл
    sprintf(buff, "%s/%s", RSS_PATH, filename);
    edit_file("Edit RSS", buff);

    // Меняем название в соответствии с содержимым
    pim_rename_file(RSS_PATH, filename, NULL);
  }
  else if(action_index == 3) {
    if(drawConfirm("Delete this RSS?") == 0) {
      // Удаляем заметку с соответствующим названием
      sprintf(buff, "%s/%s", RSS_PATH, filename);
      Storage.remove(buff);
    }
  }
}

// Преобразовать XML RSS в текст
void rss_convert_to_text(char *data) {
  char inside_tag = 0;
  char inside_cdata = 0;
  char new_line_flag = 0;
  char skip_tag_contents = 0;
  char byte;
  int read_offset = 0;
  int write_offset = 0;
  int length = strlen(data);
  char tag_name[80];

  while(read_offset < length) {
    byte = data[read_offset];
    read_offset++;

    if(byte == '\n') {
      new_line_flag = 1;
      if(data[read_offset] == '\r') {
        read_offset++;
      }
      continue;
    }
    if(byte == '\r') {
      new_line_flag = 1;
      if(data[read_offset] == '\n') {
        read_offset++;
      }
      continue;
    }
    if(new_line_flag && byte == ' ') continue;

    if(inside_tag) {
      if(byte == '>') {
        inside_tag = 0;
      }
      continue;
    }
    if(byte == '<') {
      if(memcmp(data + read_offset, "![CDATA[", 8) == 0) {
        inside_cdata = 1;
        read_offset += 8;
      }
      else {
        if(memcmp(data + read_offset, "item>", 5) == 0) {
          data[write_offset] = '\n';
          write_offset++;
        }
        if(memcmp(data + read_offset, "guid", 4) == 0) {
          skip_tag_contents = 1;
        }
        if(memcmp(data + read_offset, "url>", 4) == 0) {
          skip_tag_contents = 1;
        }
        if(data[read_offset] == '/') {
          skip_tag_contents = 0;
        }
        inside_tag = 1;
      }
      continue;
    }
    if(byte == ']' && inside_cdata) {
      if(memcmp(data + read_offset, "]>", 2) == 0) {
        inside_cdata = 0;
        read_offset += 2;
        continue;
      }
    }
    if(skip_tag_contents) {
      continue;
    }
    if(new_line_flag) {
      if(write_offset != 0) {
        data[write_offset] = '\n';
        write_offset++;
      }
      new_line_flag = 0;
    }
    data[write_offset] = byte;
    write_offset++;
  }
  data[write_offset] = 0;
}

void rss_file_to_list(fs::File file, char *buff) {
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

void rss(char mode, char *io_buff) {
  char *buttons[] = {
    "New", "Read", "Edit", "Delete",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00000010,
    B01011111, B10000010,
    B01000000, B01000010,
    B01001111, B00100010,
    B01000000, B10010010,
    B01001100, B01010010,
    B01000010, B01010010,
    B01000001, B01010010,
    B01011001, B01010010,
    B01011000, B00000010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };
  
  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "RSS");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  pim_app("RSS", RSS_PATH, rss_file_to_list, buttons, rss_action);
}

#endif
// IS_WIFI_ENABLED

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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
  int wifi_status;

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
      sprintf(buff, "https://arikado.ru/cyd/weather.php?lat=%f&lon=%f", global_lat, global_lon);
      if(get_file_https(buff, weather) != 200) {
        strcpy(weather, "Weather unknown");
      }

      // Курсы валют
      if(get_file_https("https://arikado.ru/cyd/rates.php", rates) != 200) {
        strcpy(rates, "Rates unknown");
      }
#endif

      tft.fillRect(0, 242, tft.width(), tft.height() - 242, color_scheme_bg);
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
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
      }
      prev_day = day;

      // Выводим всё
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
            tft.fillRect(cal_col * tft.width() / 7, 130 + cal_row * 16, tft.width() / 7, 16, color_scheme_selection_bg);
            tft.setTextColor(color_scheme_selection_fg, color_scheme_selection_bg);
          }
          else {
            tft.setTextColor(color_scheme_fg, color_scheme_bg);
          }
          tft.drawCentreString(buff, (cal_col + 0.5) * tft.width() / 7, 130 + cal_row * 16, FONT_DEFAULT);
        }
      }

      // Лунный день
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
      sprintf(buff, "Moon day: %d", moon_day);
      tft.drawCentreString(buff, tft.width() / 2, 242, FONT_DEFAULT);
      tft.drawCentreString(weather, tft.width() / 2, 258, FONT_DEFAULT);
      tft.drawCentreString(rates, tft.width() / 2, 274, FONT_DEFAULT);

      // До следующего обновления данных
      tft.setTextColor(color_scheme_inactive_fg, color_scheme_bg);
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
          tft.setTextColor(color_scheme_inactive_fg, color_scheme_bg);
          // it is
          if(row == 0 && (col == 0 || col == 1 || col == 3 || col == 4)) {
            tft.setTextColor(color_scheme_fg, color_scheme_bg);
          }
          if(oclock_flag) {
            if(row == 9 && col >= 5) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(past_flag) {
            if(row == 4 && col < 4) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(to_flag) {
            if(row == 3 && col >= 8 && col < 10) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(five_flag) {
            if(row == 1 && col >= 7) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(ten_flag) {
            if(row == 2 && col >= 8) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(quarter_flag) {
            if(row == 2 && col < 7) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(twenty_flag) {
            if(row == 1 && col < 6) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(half_flag) {
            if(row == 0 && col >= 6 && col < 10) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(minutes_flag) {
            if(row == 3 && col < 7) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[0]) {
            if(row == 4 && col >= 5) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[1]) {
            if(row == 5 && col < 3) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[2]) {
            if(row == 6 && col >= 8) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[3]) {
            if(row == 5 && col >= 6) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[4]) {
            if(row == 6 && col < 4) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[5]) {
            if(row == 9 && col < 4) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[6]) {
            if(row == 5 && col >= 3 && col < 6) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[7]) {
            if(row == 8 && col < 5) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[8]) {
            if(row == 7 && col < 5) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[9]) {
            if(row == 8 && col >= 6 && col < 10) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[10]) {
            if(row == 6 && col >= 5 && col < 8) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
            }
          }
          if(hour_flag[11]) {
            if(row == 7 && col >= 5) {
              tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);

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
        tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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
    tft.setTextColor(color_scheme_fg, color_scheme_bg);

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
// Перезагрузка
// ====================================================

void reboot(char mode, char *io_buff) {
  int i;
  unsigned char byte;
  int button_pressed;
  char buff[80];
  char *buttons[] = {
    "Reboot",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000001, B10000010,
    B01001001, B10010010,
    B01010001, B10001010,
    B01010001, B10001010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01001000, B00010010,
    B01000111, B11100010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Reboot");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Reboot");

  while(1) {
    tft.setTextColor(color_scheme_fg, color_scheme_bg);

    drawButtonMatrix(0, 20, tft.width(), 32, buttons, 1, 1);

    touchWaitPress();

    button_pressed = touchCheckMatrix(0, 20, tft.width(), 32, buttons, 1, 1);
    if(button_pressed != -1) {
      ESP.restart();
    }

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
// Доп клавиатура вкл/выкл
// ====================================================

void alt_keyboard_control(char mode, char *io_buff) {
  int i;
  unsigned char byte;
  int button_pressed;
  char buff[80];
  char *buttons[] = {
    "Change state",
    NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000111, B11111010,
    B01001000, B00001010,
    B01010000, B00001010,
    B01010000, B00001010,
    B01001000, B00001010,
    B01000111, B11111010,
    B01000010, B00001010,
    B01000100, B00001010,
    B01001000, B00001010,
    B01010000, B00001010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Alt Keyboard");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Alt Keyboard");

  while(1) {
    tft.setTextColor(color_scheme_fg, color_scheme_bg);

    drawButtonMatrix(0, 20, tft.width() / 2, 32, buttons, 1, 1);

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    sprintf(buff, "  %s  ", alt_keyboard_enabled_flag ? "ON" : "OFF");
    tft.drawCentreString(buff, 3 * tft.width() / 4, 28, FONT_DEFAULT);

    touchWaitPress();

    button_pressed = touchCheckMatrix(0, 20, tft.width() / 2, 32, buttons, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        if(alt_keyboard_enabled_flag) {
          alt_keyboard_enabled_flag = 0;
        }
        else {
          alt_keyboard_enabled_flag = 1;
        }
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      store_current_timestamp();
      touchWaitRelease();

      if(drawConfirm("Save changes?") == 0) {
        write_key_value_to_file("/Settings/Keyboard", "alt_keyboard_enabled_flag", (char*)(alt_keyboard_enabled_flag ? "1" : "0"));
      }

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
  tft.setTextColor(color_scheme_fg, color_scheme_bg);

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
    tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);

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
      if(strlen(current_string) == 0 && tft.textWidth(current_word, FONT_DEFAULT) >= (tft.width() - 2)) {
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
        word_offset = strlen(current_word);
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
          word_offset = strlen(current_word);
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

// Почти полная копия view_file, по не файл, а буфер
// Совместить две функции сложно
void view_text(char *title, char *data) {
  int word_offset;
  int word_in_line_offset = 0;
  int show_file_offset_lines = 0;
  int current_file_offset_lines = 0;
  int current_line_on_screen = 0;
  int touch_x, touch_y;
  int i;
  int data_offset = 0;
  int data_length = strlen(data);
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
  tft.setTextColor(color_scheme_fg, color_scheme_bg);

  while(1) {
    // Вывести текст по текущему смещению
    // Начинаем с начала файла и читаем пока не попадём на отображаемую часть
    data_offset = 0;
    current_file_offset_lines = 0;
    current_line_on_screen = 0;
    word_in_line_offset = 0;
    current_string[0] = 0;
    tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);

    word_offset = 0;
    current_word[word_offset] = 0;
    while(data_offset < data_length) {
      // Читаем слово
      new_line_flag = 0;
      show_line_flag = 0;
      long_string_flag = 0;
      while(data_offset < data_length) {
        byte = data[data_offset];
        data_offset++;
        current_word[word_offset] = byte;
        word_offset++;
        current_word[word_offset] = 0;
        if(byte == '\n') {
          if(data[data_offset + 1] == '\r') data_offset++;
        }
        if(byte == '\r') {
          if(data[data_offset + 1] == '\n') data_offset++;
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
        if(new_line_flag == 0 && data_offset < data_length) {
          continue;
        }
      }

      // Если строка пустая, а слово не поместилось, то нужно вывести часть слова, остальное оставить на потом
      if(strlen(current_string) == 0 && tft.textWidth(current_word, FONT_DEFAULT) >= (tft.width() - 2)) {
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
        word_offset = strlen(current_word);
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
        if(data_offset >= data_length || new_line_flag) {
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
          word_offset = strlen(current_word);
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
        if(data_offset < data_length || strlen(current_word) > 0) {
          show_file_offset_lines += 19;
        }
      }
    }

    touchWaitReleaseOrExit();
    if(global_exit_flag) {
      drawAppTitle("Exit");
      touchWaitRelease();
      drawAppTitle(title);
      touchExitActionReset();
      return;
    }
    touchWaitRelease();
  }
}

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
  
  char **keyboard_current = keyboard_nocaps;
  fs::File file;

  contents = (char *)malloc(EDIT_FILE_LENGTH_MAX * sizeof(char));

  clearScreen();
  drawAppTitle(title);
  tft.setTextColor(color_scheme_fg, color_scheme_bg);

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
    tft.fillRect(0, 16, tft.width(), 200 - 16, color_scheme_bg);

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
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.fillRect(cursor_screen_pos_x, cursor_screen_pos_y, 2, 16, color_scheme_selection_bg);

    if(symbol_flag) {
      keyboard_current = keyboard_symbol;
    }
    else if(caps_flag) {
      if(alt_flag) {
        keyboard_current = alt_keyboard_enabled_flag ? keyboard_alt_caps : keyboard_caps;
      }
      else {
        keyboard_current = keyboard_caps;
      }
    }
    else {
      if(alt_flag) {
        keyboard_current = alt_keyboard_enabled_flag ? keyboard_alt_nocaps : keyboard_nocaps;
      }
      else {
        keyboard_current = keyboard_nocaps;
      }
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

  tft.setTextColor(color_scheme_fg, color_scheme_bg);

  clearScreen();
  tft.drawCentreString("Touch left top cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(offset - 5, offset - 5, offset + 5, offset + 5, color_scheme_fg);
  tft.drawLine(offset - 5, offset + 5, offset + 5, offset - 5, color_scheme_fg);
  delay(1000);
  touchWaitPress();
  p1 = touchscreen.getPoint();
  clearScreen();
  tft.drawCentreString("Release", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  touchWaitRelease();
  delay(1000);  

  clearScreen();
  tft.drawCentreString("Touch left bottom cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(offset - 5, tft.height() - 2 - offset - 5, offset + 5, tft.height() - 2 - offset + 5, color_scheme_fg);
  tft.drawLine(offset - 5, tft.height() - 2 - offset + 5, offset + 5, tft.height() - 2 - offset - 5, color_scheme_fg);
  delay(1000);
  touchWaitPress();
  p2 = touchscreen.getPoint();
  clearScreen();
  tft.drawCentreString("Release", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  touchWaitRelease();
  delay(1000);  

  clearScreen();
  tft.drawCentreString("Touch right top cross center", tft.width() / 2, tft.height() / 2 - 16, FONT_DEFAULT);
  tft.drawLine(tft.width() - 2 - offset - 5, offset - 5, tft.width() - 2 - offset + 5, offset + 5, color_scheme_fg);
  tft.drawLine(tft.width() - 2 - offset - 5, offset + 5, tft.width() - 2 - offset + 5, offset - 5, color_scheme_fg);
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
      restart_flag = 1;
      steps = 0;
      level = min(level + 1, HANOI_TOWERS_MAX_LEVEL);
      won_flag = 0;
      continue;
    }

    touchWaitPress();
    tft.fillRect(0, tft.height() - 15, tft.width(), 15, color_scheme_bg);
    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);

    if(column1 == -1) {
      column1 = touch_x / (tft.width() / 3);
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
      tft.drawCentreString("^", column1 * tft.width() / 3 + tft.width() / 6, tft.height() - 15, FONT_DEFAULT);
    }
    else {
      column2 = touch_x / (tft.width() / 3);
      if(column1 == column2) {
        column1 = column2;
        column2 = -1;
        tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
        tft.fillRect(0, tft.height() - 15, tft.width(), 15, color_scheme_bg); 
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

#define MATCH_THREE_FIELD_WIDTH 8
#define MATCH_THREE_FIELD_HEIGHT 8
#define MATCH_THREE_FIELD_FIGURES 6
#define MATCH_THREE_ACTION_COUNT_ONLY 0
#define MATCH_THREE_ACTION_REMOVE_MATCHES 1

// Три в ряд, как Bejeweled
void match_three(char mode, char *io_buff) {
  TS_Point p;
  int touch_x, touch_y;
  int row1, col1;
  int row2, col2;
  int button_pressed;
  int moves = 3;
  int user_moves = 0;
  int score = 0;
  int hiscore = 0;
  int i;
  char changes_found_flag = 0;
  int column1, column2;
  char restart_flag = 1;
  char won_flag = 0;
  int field[MATCH_THREE_FIELD_WIDTH * MATCH_THREE_FIELD_HEIGHT];
  char buff[80];
  char tmp;
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000001, B10000010,
    B01000001, B10000010,
    B01000010, B01000010,
    B01000010, B01000010,
    B01000100, B00100010,
    B01000100, B00100010,
    B01001000, B00010010,
    B01001000, B00010010,
    B01010000, B00001010,
    B01011111, B11111010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Match Three");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Match Three");

  restart_flag = 1;
  while(1) {
    if(restart_flag) {
      // Инициализируем
      for(i = 0; i < MATCH_THREE_FIELD_WIDTH * MATCH_THREE_FIELD_HEIGHT; i++) {
        field[i] = random(0, MATCH_THREE_FIELD_FIGURES);
      }
      score = 0;
      restart_flag = 0;
      user_moves = 0;
      row1 = -1;
      col1 = -1;
      row2 = -1;
      col2 = -1;
    }

    // Рисуем поле
    match_three_show_field(field, col1, row1);

    // Убираем совпадения, сдвигаем вниз, и снова убираем
    changes_found_flag = 1;
    while(changes_found_flag) {
      score += match_three_find_matches(field, MATCH_THREE_ACTION_REMOVE_MATCHES);
      match_three_show_field(field, col1, row1);
      hiscore = max(hiscore, score);

      tft.setTextColor(color_scheme_fg, color_scheme_bg);
      sprintf(buff, "Score: %d     ", score);
      tft.drawString(buff, 1, 20, FONT_DEFAULT);
      sprintf(buff, "Hi-score: %d     ", hiscore);
      tft.drawString(buff, tft.width() / 2, 20, FONT_DEFAULT);
      
      changes_found_flag = 0;
      while(match_three_shift_down(field) > 0) {
        delay(100);
        match_three_show_field(field, col1, row1);
        changes_found_flag = 1;
      }
    }

    // Проверяем доступные ходы
    moves = match_three_moves_available(field);
    if(moves == 0) {
      drawInfo("No more moves");
      restart_flag = 1;
      continue;
    }

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    sprintf(buff, "Score: %d     ", score);
    tft.drawString(buff, 1, 20, FONT_DEFAULT);
    sprintf(buff, "Hi-score: %d     ", hiscore);
    tft.drawString(buff, tft.width() / 2, 20, FONT_DEFAULT);

    // Ждём пользователя
    touchWaitPress();
    tft.fillRect(0, tft.height() - 15, tft.width(), 15, color_scheme_bg);
    TS_Point p = touchscreen.getPoint();
    touch_x = touchMapX(p.x, p.y);
    touch_y = touchMapY(p.x, p.y);
    if(col1 == -1) {
      col1 = touch_x / (tft.width() / MATCH_THREE_FIELD_WIDTH);
      row1 = (touch_y - 40) / (tft.width() / MATCH_THREE_FIELD_WIDTH);
      if(col1 >= MATCH_THREE_FIELD_WIDTH || row1 >= MATCH_THREE_FIELD_HEIGHT) {
        col1 = -1;
        row1 = -1;
      }
    }
    else {
      col2 = touch_x / (tft.width() / MATCH_THREE_FIELD_WIDTH);
      row2 = (touch_y - 40) / (tft.width() / MATCH_THREE_FIELD_WIDTH);
      if(col2 >= MATCH_THREE_FIELD_WIDTH || row2 >= MATCH_THREE_FIELD_HEIGHT) {
        col2 = -1;
        row2 = -1;
      }
      // Проверяем валидность хода
      else if(col1 == col2 && abs(row1 - row2) == 1 || row1 == row2 && abs(col1 - col2) == 1) {
        tmp = field[col1 + row1 * MATCH_THREE_FIELD_WIDTH];
        field[col1 + row1 * MATCH_THREE_FIELD_WIDTH] = field[col2 + row2 * MATCH_THREE_FIELD_WIDTH];
        field[col2 + row2 * MATCH_THREE_FIELD_WIDTH] = tmp;
        match_three_show_field(field, col1, row1);
        if(match_three_find_matches(field, MATCH_THREE_ACTION_COUNT_ONLY) > 0) {
          user_moves++;
        }
        else {
          delay(100);
          tmp = field[col1 + row1 * MATCH_THREE_FIELD_WIDTH];
          field[col1 + row1 * MATCH_THREE_FIELD_WIDTH] = field[col2 + row2 * MATCH_THREE_FIELD_WIDTH];
          field[col2 + row2 * MATCH_THREE_FIELD_WIDTH] = tmp;
        }
      }
      col1 = -1;
      row1 = -1;
      col2 = -1;
      row2 = -1;
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

int match_three_moves_available(int *field) {
  int row, col;
  int moves = 0;
  int tmp;
  for(row = 0; row < MATCH_THREE_FIELD_HEIGHT - 1; row++) {
    for(col = 0; col < MATCH_THREE_FIELD_WIDTH - 1; col++) {
      // Переставляем со следующим по горизонтали, считаем ходы, откатываем
      tmp = field[col + row * MATCH_THREE_FIELD_WIDTH];
      field[col + row * MATCH_THREE_FIELD_WIDTH] = field[col + 1 + row * MATCH_THREE_FIELD_WIDTH];
      field[col + 1 + row * MATCH_THREE_FIELD_WIDTH] = tmp;
      moves += match_three_find_matches(field, MATCH_THREE_ACTION_COUNT_ONLY);
      tmp = field[col + row * MATCH_THREE_FIELD_WIDTH];
      field[col + row * MATCH_THREE_FIELD_WIDTH] = field[col + 1 + row * MATCH_THREE_FIELD_WIDTH];
      field[col + 1 + row * MATCH_THREE_FIELD_WIDTH] = tmp;

      // Переставляем со следующим по вертикали, считаем ходы, откатываем
      tmp = field[col + row * MATCH_THREE_FIELD_WIDTH];
      field[col + row * MATCH_THREE_FIELD_WIDTH] = field[col + (row + 1) * MATCH_THREE_FIELD_WIDTH];
      field[col + (row + 1) * MATCH_THREE_FIELD_WIDTH] = tmp;
      moves += match_three_find_matches(field, MATCH_THREE_ACTION_COUNT_ONLY);
      tmp = field[col + row * MATCH_THREE_FIELD_WIDTH];
      field[col + row * MATCH_THREE_FIELD_WIDTH] = field[col + (row + 1) * MATCH_THREE_FIELD_WIDTH];
      field[col + (row + 1) * MATCH_THREE_FIELD_WIDTH] = tmp;
    }
  }
  return moves;
}

void match_three_show_field(int *field, int col_selected, int row_selected) {
  int row, col;
  char buff[80];
  // Эти цвета неплохо видно и на чёрном, и на белом
  int item_to_color[] = {TFT_DARKGREY, TFT_RED, TFT_GREEN, TFT_BLUE, TFT_OLIVE, TFT_MAGENTA};
  for(row = 0; row < MATCH_THREE_FIELD_HEIGHT; row++) {
    for(col = 0; col < MATCH_THREE_FIELD_WIDTH; col++) {
      tft.fillRect(
        col * tft.width() / MATCH_THREE_FIELD_WIDTH,
        40 + row * tft.width() / MATCH_THREE_FIELD_HEIGHT,
        tft.width() / MATCH_THREE_FIELD_WIDTH,
        tft.width() / MATCH_THREE_FIELD_HEIGHT,
        color_scheme_bg
      );
      Serial.print((int)field[col + row * MATCH_THREE_FIELD_WIDTH]);
      Serial.print(" ");
      if(field[col + row * MATCH_THREE_FIELD_WIDTH] != -1) {
        tft.setTextColor(item_to_color[field[col + row * MATCH_THREE_FIELD_WIDTH]], color_scheme_bg);
        sprintf(buff, "%c", field[col + row * MATCH_THREE_FIELD_WIDTH] + 'A');
        tft.drawCentreString(
          buff,
          col * tft.width() / MATCH_THREE_FIELD_WIDTH + tft.width() / (2 * MATCH_THREE_FIELD_WIDTH),
          34 + row * tft.width() / MATCH_THREE_FIELD_HEIGHT + tft.width() / (3 * MATCH_THREE_FIELD_WIDTH),
          FONT_BIG
        );
      }
      if(col == col_selected && row == row_selected) {
        tft.drawRect(
        col * tft.width() / MATCH_THREE_FIELD_WIDTH,
        40 + row * tft.width() / MATCH_THREE_FIELD_HEIGHT,
        tft.width() / MATCH_THREE_FIELD_WIDTH,
        tft.width() / MATCH_THREE_FIELD_HEIGHT,
        color_scheme_fg
        );
      }
    }
    Serial.println();
  }
}

int match_three_find_matches(int *field, int action) {
  int field_next[MATCH_THREE_FIELD_WIDTH * MATCH_THREE_FIELD_HEIGHT];
  int row, col;
  int i;
  int matches = 0;
  char current_item;
  int current_item_count;
  // Копируем поле в следующее поле
  for(i = 0; i < MATCH_THREE_FIELD_HEIGHT * MATCH_THREE_FIELD_WIDTH; i++) {
    *(field_next + i) = *(field + i);
  }
  // Горизонтали
  for(row = 0; row < MATCH_THREE_FIELD_HEIGHT; row++) {
    for(col = 0; col < MATCH_THREE_FIELD_WIDTH; col++) {
      if(col == 0) {
        current_item = field[col + row * MATCH_THREE_FIELD_WIDTH];
        current_item_count = 1;
        continue;
      }
      else if(field[col + row * MATCH_THREE_FIELD_WIDTH] == current_item) {
        current_item_count++;
        if(current_item_count >= 3) {
          matches++;
          if(action == MATCH_THREE_ACTION_REMOVE_MATCHES) {
            for(i = 0; i < current_item_count; i++) {
              field_next[col - i + row * MATCH_THREE_FIELD_WIDTH] = -1;
            }
          }
        }
      }
      else {
        current_item = field[col + row * MATCH_THREE_FIELD_WIDTH];
        current_item_count = 1;
      }
    }
  }
  // Вертикали
  for(col = 0; col < MATCH_THREE_FIELD_WIDTH; col++) {
    for(row = 0; row < MATCH_THREE_FIELD_HEIGHT; row++) {
      if(row == 0) {
        current_item = field[col + row * MATCH_THREE_FIELD_WIDTH];
        current_item_count = 1;
      }
      else if(field[col + row * MATCH_THREE_FIELD_WIDTH] == current_item) {
        current_item_count++;
        if(current_item_count >= 3) {
          matches++;
          if(action == MATCH_THREE_ACTION_REMOVE_MATCHES) {
            for(i = 0; i < current_item_count; i++) {
              field_next[col + (row - i) * MATCH_THREE_FIELD_WIDTH] = -1;
            }
          }
        }
      }
      else {
        current_item = field[col + row * MATCH_THREE_FIELD_WIDTH];
        current_item_count = 1;
      }
    }
  }

  // Копируем следущее поле в поле
  for(i = 0; i < MATCH_THREE_FIELD_HEIGHT * MATCH_THREE_FIELD_WIDTH; i++) {
    *(field + i) = *(field_next + i);
  }

  return matches;
}

int match_three_shift_down(int * field) {
  int row, col;
  int count = 0;
  // Опускаем всё вниз
  for(row = MATCH_THREE_FIELD_HEIGHT - 1; row > 0; row--) {
    for(col = 0; col < MATCH_THREE_FIELD_WIDTH; col++) {
      if(field[col + (row - 1) * MATCH_THREE_FIELD_WIDTH] != -1 && field[col + row * MATCH_THREE_FIELD_WIDTH] == -1) {
        // Опускаем элемент
        field[col + row * MATCH_THREE_FIELD_WIDTH] = field[col + (row - 1) * MATCH_THREE_FIELD_WIDTH];
        field[col + (row - 1) * MATCH_THREE_FIELD_WIDTH] = -1;
        count++;
      }
    }
  }
  // Заполняем пустые места сверху
  row = 0;
  for(col = 0; col < MATCH_THREE_FIELD_WIDTH; col++) {
    if(field[col + row * MATCH_THREE_FIELD_WIDTH] == -1) {
      field[col + row * MATCH_THREE_FIELD_WIDTH] = random(0, MATCH_THREE_FIELD_FIGURES);
        count++;
    }
  }
  return count;
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

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
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
    tft.fillRect(i * tft.width() / 16 + 1, 240 - 32 + 1, tft.width() / 16 - 2, 64 - 2, TFT_WHITE);

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

void metronome(char mode, char *io_buff) {
  int button_pressed;
  int i;
  int preset_minutes = 1;
  int preset_seconds = 0;
  long start_millis;
  long time_remains;
  char timer_run = 0;
  char auto_restart = 0;
  char redraw_flag = 0;
  char started_flag = 0;
  int tempo = 100;
  long interval;
  long prev_beep_millis;
  char buff[80];
  char *buttons_presets[] = {
    "Grave", "Largo", "Adagio",
    "Andante", "Moderato", "Allegro",
    "Vivace", "Presto", "Prestissimo",
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
  char *buttons_set_tempo[] = {
    "Set Tempo", NULL
  };
  char app_icon[] = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01000000, B00000010,
    B01000000, B00100010,
    B01000000, B01000010,
    B01000000, B01000010,
    B01000000, B10000010,
    B01000000, B10000010,
    B01000111, B11100010,
    B01001000, B00010010,
    B01010011, B11001010,
    B01010010, B01001010,
    B01011111, B11111010,
    B01000000, B00000010,
    B01111111, B11111110,
    B00000000, B00000000
  };

  if(mode == APP_MODE_RETURN_NAME) {
    strcpy(io_buff, "Metronome");
    return;
  }
  if(mode == APP_MODE_RETURN_ICON) {
    memcpy(io_buff, app_icon, 34);
    return;
  }

  clearScreen();
  drawAppTitle("Metronome");

  started_flag = 0;
  prev_beep_millis = 0;
  while(1) {
    if(started_flag) {
      interval = 60000 / tempo;
      if(millis() - prev_beep_millis > interval) {
        prev_beep_millis = millis();
        if(interval >= 200) {
          tone(BUZZER_PIN, 1000, 100);
        }
        else {
          tone(BUZZER_PIN, 1000, 10);
        }
      }
    }

    // Если таймер запущен и касаний нет - остальное не рисуем
    if(started_flag && touchCheckNowait() == 0 && !redraw_flag) {
      continue;
    }

    if(redraw_flag) {
      tft.fillRect(0, 16, tft.width(), tft.height() - 16, color_scheme_bg);
      redraw_flag = 0;
    }

    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    sprintf(buff, "  %d  ", tempo);
    tft.drawCentreString(buff, 3 * tft.width() / 4, 28, FONT_DEFAULT);

    drawButtonMatrix(0, 20, tft.width() / 2, 32, buttons_set_tempo, 1, 1);

    drawButtonMatrix(0, 60, tft.width(), 32, buttons_start_stop, 2, 1);

    drawButtonMatrix(0, 200, tft.width(), tft.height() - 200, buttons_presets, 3, 3);

    if(!started_flag) {
      touchWaitPress();
    }

    button_pressed = touchCheckMatrix(0, 60, tft.width(), 32, buttons_start_stop, 2, 1);
    if(button_pressed != -1) {
      // Старт
      if(button_pressed == 0) {
        started_flag = 1;
      }
      // Cтоп
      else if(button_pressed == 1) {
        started_flag = 0;
      }
    }

    button_pressed = touchCheckMatrix(0, 20, tft.width() / 2, 32, buttons_set_tempo, 1, 1);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        sprintf(buff, "%d", tempo);
        if(drawPrompt("Enter tempo", buff) == 0) {
          sscanf(buff, "%d", &tempo);
        }
      }
      redraw_flag = 1;
    }

    button_pressed = touchCheckMatrix(0, 200, tft.width(), tft.height() - 200, buttons_presets, 3, 3);
    if(button_pressed != -1) {
      if(button_pressed == 0) {
        tempo = 30;
      }
      else if(button_pressed == 1) {
        tempo = 50;
      }
      else if(button_pressed == 2) {
        tempo = 70;
      }
      else if(button_pressed == 3) {
        tempo = 90;
      }
      else if(button_pressed == 4) {
        tempo = 110;
      }
      else if(button_pressed == 5) {
        tempo = 140;
      }
      else if(button_pressed == 6) {
        tempo = 170;
      }
      else if(button_pressed == 7) {
        tempo = 190;
      }
      else if(button_pressed == 8) {
        tempo = 220;
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

  int color_index;
  
  beep_if_enabled();

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

  beep_if_enabled();
  digitalWrite(LED_RED, HIGH);
}

void clearScreen() {
  tft.fillScreen(color_scheme_bg);
}

void drawAppTitle(char *name) {
  char buff[80];
  tft.setTextColor(color_scheme_title_fg, color_scheme_title_bg);
  tft.fillRect(0, 0, tft.width(), 16, color_scheme_title_bg);
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
  beep_if_enabled();
  drawPopoupWindowWaitReply("Error", message, buttons);
}

void drawAlert(char *message) {
  char *buttons[] = { "OK", NULL };
  beep_if_enabled();
  drawPopoupWindowWaitReply("Alert", message, buttons);
}

void drawInfo(char *message) {
  char *buttons[] = { "OK", NULL };
  beep_if_enabled();
  drawPopoupWindowWaitReply("Info", message, buttons);
}

int drawConfirm(char *message) {
  char *buttons[] = { "OK", "Cancel", NULL };
  beep_if_enabled();
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

  char **keyboard_current = keyboard_nocaps;

  beep_if_enabled();

  strcpy(input, user_input);
  
  // Рамка
  tft.drawRect(0, PROMPT_OFFSET_Y, tft.width(), 220, color_scheme_fg);
  // Белый фон
  tft.fillRect(1, PROMPT_OFFSET_Y + 1, tft.width() - 2, 218, color_scheme_bg);
  // Фон заголовка
  tft.fillRect(1, PROMPT_OFFSET_Y + 1, tft.width() - 2, 16, color_scheme_title_bg);
  // Заголовок
  tft.setTextColor(color_scheme_title_fg, color_scheme_title_bg);
  tft.drawString(message, 16, PROMPT_OFFSET_Y + 1, FONT_DEFAULT);
  
  while(1) {
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    tft.fillRect(1, PROMPT_OFFSET_Y + 20, tft.width() - 2, 16, color_scheme_bg);
    strcpy(visible_input, input);
    while(tft.textWidth(visible_input, FONT_DEFAULT) > tft.width() - 8 * 2) {
      for(i = 0; i < strlen(visible_input); i++) {
        visible_input[i] = visible_input[i + 1];
      }
    }
    cursor_pos = tft.drawString(visible_input, 8, PROMPT_OFFSET_Y + 20, FONT_DEFAULT);
    
    tft.fillRect(8 + cursor_pos + 1, PROMPT_OFFSET_Y + 20, 2, 16, color_scheme_selection_bg);

    drawButtonMatrix(8, PROMPT_OFFSET_Y + 180, tft.width() - 8 * 2, 32, buttons, 3, 1);

    if(symbol_flag) {
      keyboard_current = keyboard_symbol;
    }
    else if(caps_flag) {
      if(alt_flag) {
        keyboard_current = alt_keyboard_enabled_flag ? keyboard_alt_caps : keyboard_caps;
      }
      else {
        keyboard_current = keyboard_caps;
      }
    }
    else {
      if(alt_flag) {
        keyboard_current = alt_keyboard_enabled_flag ? keyboard_alt_nocaps : keyboard_nocaps;
      }
      else {
        keyboard_current = keyboard_nocaps;
      }
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
  tft.drawRect(0, 120, tft.width(), 120, color_scheme_fg);
  // Белый фон
  tft.fillRect(1, 121, 238, 118, color_scheme_bg);
  // Фон заголовка
  tft.fillRect(1, 121, 238, 16, color_scheme_title_bg);
  // Заголовок
  tft.setTextColor(color_scheme_title_fg, color_scheme_title_bg);
  tft.drawString(title, 16, 121, FONT_DEFAULT);
  
  // Надпись
  tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
    tft.fillRect(0, 16, tft.width(), 60, color_scheme_bg);
    tft.setTextColor(color_scheme_fg, color_scheme_bg);
    for(i = 0; i < strlen(user_input); i++) {
      if(8 + i * tft.textWidth("*", FONT_BIG) < tft.width()) {
        tft.setTextColor(color_scheme_fg, color_scheme_bg);
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
          tft.fillRect(0, 16, tft.width(), tft.height() - 20, color_scheme_bg);
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
          tft.drawRect(left_x + x * width / cols + 1, top_y + y * height / rows + 1, width / cols - 2, height / rows - 2, color_scheme_button_fg);
          tft.fillRect(left_x + x * width / cols + 2, top_y + y * height / rows + 2, width / cols - 4, height / rows - 4, color_scheme_button_bg);
          if(!strcmp(str[x + y * cols], ":enter:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, enter, color_scheme_button_fg, color_scheme_button_bg);
          }
          else if(!strcmp(str[x + y * cols], ":backspace:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, backspace, color_scheme_button_fg, color_scheme_button_bg);
          }
          else if(!strcmp(str[x + y * cols], ":shift:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, shift, color_scheme_button_fg, color_scheme_button_bg);
          }
          else if(!strcmp(str[x + y * cols], ":change:")) {
            image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, change_keyboard, color_scheme_button_fg, color_scheme_button_bg);
          }
          else {
            tft.setTextColor(color_scheme_button_fg, color_scheme_button_bg);
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
  int fg_color;
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
              bg_color = color_scheme_button_bg;
              fg_color = color_scheme_button_fg;
              if(is_touch) {
                p = touchscreen.getPoint();
                touch_x = touchMapX(p.x, p.y);
                touch_y = touchMapY(p.x, p.y);
                if(is_inside) {
                  bg_color = color_scheme_button_active_bg;
                  fg_color = color_scheme_button_active_fg;
                }
              }
              
              if(prev_color != bg_color) {
                tft.drawRect(left_x + x * width / cols + 1, top_y + y * height / rows + 1, width / cols - 2, height / rows - 2, fg_color);
                tft.fillRect(left_x + x * width / cols + 2, top_y + y * height / rows + 2, width / cols - 4, height / rows - 4, bg_color);
                if(!strcmp(str[x + y * cols], ":enter:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, enter, fg_color, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":backspace:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, backspace, fg_color, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":shift:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, shift, fg_color, bg_color);
                }
                else if(!strcmp(str[x + y * cols], ":change:")) {
                  image_from_bits(left_x + x * width / cols + 6, top_y + (y + 0.5) * height / rows - 4, change_keyboard, fg_color, bg_color);
                }
                else {
                  tft.setTextColor(fg_color, bg_color);
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
    tft.setTextColor(color_scheme_inactive_fg, color_scheme_bg);
    tft.drawString("<empty list>", left_x + 1, top_y, FONT_DEFAULT);
    return;
  }

  for(y = 0; y < rows_to_show; y++) {
    if(!is_eol) {
      tft.setTextColor(color_scheme_fg, color_scheme_bg);
      // Если нужно показать [up]
      if(y == 0 && *offset > 0) {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, color_scheme_bg);
        tft.drawString(up, left_x + 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
      }
      // Если нужно показать [down]
      else if(y == (rows_to_show - 1) && (*offset + rows_to_show) <= last_row) {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, color_scheme_bg);
        tft.drawString(down, left_x + 1, top_y + y * height / rows_to_show, FONT_DEFAULT);
      }
      else if(str[y + *offset]) {
        if(y + *offset == *selected) {
          tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, color_scheme_selection_bg);
          tft.setTextColor(color_scheme_selection_fg, color_scheme_selection_bg);
        }
        else {
          tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, color_scheme_bg);
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
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, color_scheme_bg);
        is_eol = 1;
      }
    }
    else {
        tft.fillRect(left_x, top_y + y * height / rows_to_show, width, height / rows_to_show, color_scheme_bg);
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

void beep_if_enabled() {
  if(is_beep_enabled) {
    tone(BUZZER_PIN, 1000, 100);
  }
}

// Функции ширования и расшифровки - минное поле
// Скопировал их из примера, потому что переработанный вариант не работал, вылетал в Exception
// Единственное изменение - про вектор инициализации

// Encryption Function with PKCS#7 Padding
void encryptAES(uint8_t* input, int inputLen, uint8_t* output, int paddedLen) {
  char aes_iv[16];
  mbedtls_aes_context aes;
  uint8_t iv_copy[16];
  uint8_t paddingValue;
  uint8_t* paddedInput;
  int i;

  // Генерировать случайный новый вектор инициализации
  for(i = 0; i < 16; i++) {
    aes_iv[i] = random(0, 256);
  }
  // Create a temporary copy of IV because mbedtls modifies it during processing
  memcpy(iv_copy, aes_iv, 16);

  // Allocate a temporary buffer to apply PKCS#7 padding
  paddedInput = (uint8_t*)malloc(paddedLen);
  memcpy(paddedInput, input, inputLen);
  
  // Apply PKCS#7 padding bytes
  paddingValue = paddedLen - inputLen;
  for (i = inputLen; i < paddedLen; i++) {
    paddedInput[i] = paddingValue;
  }

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char*)aes_encryption_key, PASSWORDS_AES_BITS);
  /*
  Serial.println("Encryption");
  Serial.print("paddedLen="); Serial.println(paddedLen);
  Serial.print("paddingValue="); Serial.println(paddingValue);
  Serial.print("inputLen="); Serial.println(inputLen);
  Serial.print("input="); Serial.println((char*)input);
  Serial.print("paddedInput=");
  for(i = 0; i < 16; i++) {
    Serial.print(paddedInput[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
  */
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, paddedLen, iv_copy, paddedInput, output + 16);
  mbedtls_aes_free(&aes);
  /*
  Serial.print("output=");
  for(i = 0; i < 16; i++) {
    Serial.print(*(output + 16 + i), HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
  */
  // Первые 16 байт - вектор инициализации
  memcpy(output, aes_iv, 16);
  free(paddedInput);
}

// Decryption Function with PKCS#7 Unpadding
void decryptAES(uint8_t* input, int dataLen, uint8_t* output) {
  mbedtls_aes_context aes;
  uint8_t iv_copy[16];
  uint8_t paddingValue;
  int originalLen;
  int paddedLen;
  int i;

  paddedLen = ((dataLen - 16) / 16) * 16;

  // Первые 16 байт - вектор инициализации
  memcpy(iv_copy, input, 16);

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_dec(&aes, (const unsigned char*)aes_encryption_key, PASSWORDS_AES_BITS);
  /*
  Serial.println("Decryption");
  Serial.print("dataLen="); Serial.println(dataLen);
  Serial.print("paddedLen="); Serial.println(paddedLen);
  Serial.print("input=");
  for(i = 0; i < 16; i++) {
    Serial.print(*(input + 16 + i), HEX);
    Serial.print(" ");
  }
  Serial.println();

  delay(100);
  */
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, paddedLen, iv_copy, input + 16, output);
  /*
  Serial.print("output=");
  for(i = 0; i < 16; i++) {
    Serial.print(*(output + i), HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
*/
  mbedtls_aes_free(&aes);

  // Read PKCS#7 padding value from the very last byte to remove it
  paddingValue = output[paddedLen - 1];
  originalLen = paddedLen - paddingValue;
  /*
  Serial.print("paddingValue="); Serial.println(paddingValue);
  Serial.print("originalLen="); Serial.println(originalLen);
  */
  // Truncate the string to restore original length
  //output[originalLen] = 0;
}

void setup() {
  fs::File file;
  char byte;
  char buff[80];
  char autorun_app_name[80];
  int offset;
  int i;
  int inversion;
  int index;
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
  // Поворот
  tft.setRotation(2);
  // Очистка
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

  // Инверсия
  if(fs_present && read_file_to_buff("/Settings/Inversion", 79, buff)) {
    sscanf(buff, "%d", &inversion);
    tft.invertDisplay(inversion ? true : false);
  }
  else {
    tft.invertDisplay(false);
  }

  // Цветовая схема
  // Цвет фона и текста
  color_scheme_bg = colors[COLOR_INDEX_WHITE];
  color_scheme_fg = colors[COLOR_INDEX_BLACK];
  // Цвет заголовка и текста
  color_scheme_title_bg = colors[COLOR_INDEX_BLUE];
  color_scheme_title_fg = colors[COLOR_INDEX_WHITE];
  // Цвет выделения и текста
  color_scheme_selection_bg = colors[COLOR_INDEX_BLUE];
  color_scheme_selection_fg = colors[COLOR_INDEX_WHITE];
  // Цвет кнопки и текста
  color_scheme_button_bg = colors[COLOR_INDEX_LIGHTGREY];
  color_scheme_button_fg = colors[COLOR_INDEX_BLACK];
  // Цвет нажатой кнопки и текста
  color_scheme_button_active_bg = colors[COLOR_INDEX_DARKGREY];
  color_scheme_button_active_fg = colors[COLOR_INDEX_BLACK];
  // Цвет неактивного текста
  color_scheme_inactive_fg = colors[COLOR_INDEX_LIGHTGREY];
  // Цвет ссылки
  color_scheme_link_fg = colors[COLOR_INDEX_BLUE];

  if(fs_present) {
    // Цвет фона и текста
    if(read_key_value_from_file("/Settings/Colors", "background", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_bg = colors[index];
    }
    if(read_key_value_from_file("/Settings/Colors", "foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_fg = colors[index];
    }
    // Цвет заголовка и текста
    if(read_key_value_from_file("/Settings/Colors", "title_background", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_title_bg = colors[index];
    }
    if(read_key_value_from_file("/Settings/Colors", "title_foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_title_fg = colors[index];
    }
    if(read_key_value_from_file("/Settings/Colors", "selection_background", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_selection_bg = colors[index];
    }
    if(read_key_value_from_file("/Settings/Colors", "selection_foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_selection_fg = colors[index];
    }
    // Цвет кнопки и текста
    if(read_key_value_from_file("/Settings/Colors", "button_background", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_button_bg = colors[index];
    }
    if(read_key_value_from_file("/Settings/Colors", "button_foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_button_fg = colors[index];
    }
    // Цвет нажатой кнопки и текста
    if(read_key_value_from_file("/Settings/Colors", "button_active_background", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_button_active_bg = colors[index];
    }
    if(read_key_value_from_file("/Settings/Colors", "button_active_foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_button_active_fg = colors[index];
    }
    // Цвет неактивного текста
    if(read_key_value_from_file("/Settings/Colors", "inactive_foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_inactive_fg = colors[index];
    }
    // Цвет ссылки
    if(read_key_value_from_file("/Settings/Colors", "link_foreground", buff)) {
      sscanf(buff, "%d", &index);
      color_scheme_link_fg = colors[index];
    }
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

  is_beep_enabled = 1;
  if(read_file_to_buff("/Settings/Sound", 79, buff)) {
    if(buff[0] == '0') {
      is_beep_enabled = 0;
    }
  }

  // Настройки клавиатуры
  alt_keyboard_enabled_flag = 1;
  if(read_key_value_from_file("/Settings/Keyboard", "alt_keyboard_enabled_flag", buff)) {
    sscanf(buff, "%d", &alt_keyboard_enabled_flag);
  }

#ifdef IS_WIFI_ENABLED
  WiFi.begin();
#endif

  // Получить текущее время из сохранённого в ФС
  get_current_timestamp_fs();
  get_current_timezone();

  beep_if_enabled();

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

  // Копируем ссылки на приложения
  for(i = 0; i < 40; i++) {
    main_apps[i] = apps[i];
  }
}

void loop() {
  apps[0](APP_MODE_LAUNCH, NULL);
}
