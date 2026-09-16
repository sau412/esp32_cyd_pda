// Font 2

// Comment out for £ sign for character 24
#define TFT_ESPI_FONT2_DOLLAR

// The grave ( ` ) diacritical mark will show as a degree ( ° ) symbol
// Comment out next line to return character 0x60 to the grave accent:
//#define TFT_ESPI_GRAVE_IS_DEGREE

// Width has been increased by 1 pixel so pixel lengths are calculated correctly
// for the displayed string

PROGMEM const unsigned char widtbl_f16[224] =         // character width table
{
        6, 3, 4, 9, 8, 9, 9, 3, // 20-27 
        7, 7, 8, 6, 3, 6, 5, 7, // 28-2F 
        8, 8, 8, 8, 8, 8, 8, 8, // 30-37 01234567
        8, 8, 3, 3, 6, 6, 6, 8, // 38-3F 89:;<=>?
        9, 8, 8, 8, 8, 8, 8, 8, // 40-47 @ABCDEFG
        8, 4, 8, 8, 7, 10, 8, 8, // 48-4F HIJKLMNO
        8, 8, 8, 8, 8, 8, 8, 10, // 50-57 PQRSTUVW
        8, 8, 8, 4, 7, 4, 7, 9, // 58-5F XYZ[\]^_
#ifdef TFT_ESPI_GRAVE_IS_DEGREE
        5, 7, 7, 7, 7, 7, 6, 7,             // char 96 - 103 0x60 is degree symbol
#else
        4, 7, 7, 7, 7, 7, 6, 7, // 60-67 `abcdefg
#endif
        7, 4, 5, 6, 4, 8, 7, 8, // 68-6F hijklmno
        7, 8, 6, 6, 5, 7, 8, 8, // 70-77 pqrstuvw
        6, 7, 7, 5, 3, 5, 8, 6, // 78-7F xyz{|}~ 
        8, 8, 3, 5, 6, 9, 8, 8, // 80-87 ЂЃ‚ѓ„…†‡
        8, 9, 9, 4, 8, 8, 8, 8, // 88-8F €‰Љ‹ЊЌЋЏ
        7, 3, 3, 6, 6, 6, 8, 9, // 90-97 ђ‘’“”•–—
        8, 8, 9, 4, 9, 6, 7, 6, // 98-9F  ™љ›њќћџ
        8, 8, 7, 8, 8, 8, 3, 8, // A0-A7  ЎўЈ¤Ґ¦§
        8, 8, 8, 7, 8, 8, 8, 4, // A8-AF Ё©Є«¬ ®Ї
        5, 8, 4, 4, 5, 8, 8, 3, // B0-B7 °±Ііґµ¶·
        7, 8, 7, 7, 3, 8, 6, 4, // B8-BF ё№є»јЅѕї
        8, 8, 8, 8, 8, 8, 8, 8, // C0-C7 АБВГДЕЖЗ
        8, 8, 8, 8, 8, 8, 8, 8, // C8-CF ИЙКЛМНОП
        8, 8, 8, 8, 8, 8, 8, 8, // D0-D7 РСТУФХЦЧ
        8, 9, 8, 8, 8, 8, 9, 8, // D8-DF ШЩЪЫЬЭЮЯ
        7, 8, 7, 6, 8, 7, 8, 7, // E0-E7 абвгдежз
        7, 7, 7, 7, 8, 7, 8, 7, // E8-EF ийклмноп
        7, 7, 8, 7, 8, 8, 8, 7, // F0-F7 рстуфхцч
        8, 9, 8, 8, 7, 7, 9, 7  // F8-FF шщъыьэюя
};

// Row format, MSB left

PROGMEM const unsigned char chr_f16_20[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_21[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,    // row 1 - 11
        0x00, 0x40, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_22[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_23[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0xFF, 0x24, 0x24, 0xFF, 0x24,    // row 1 - 11
        0x24, 0x24, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_24[16] =         // 1 unsigned char per row
{
#ifdef TFT_ESPI_FONT2_DOLLAR
        0x00, 0x00, 0x28, 0x38, 0x6C, 0xAA, 0xA8, 0x68, 0x3C, 0x2A, 0xAA,    // row 1 - 11
        0x6C, 0x38, 0x28, 0x00, 0x00                                         // row 12 - 16
#else   // GBP sign
        0x00, 0x00, 0x00, 0x3C, 0x42, 0x40, 0x40, 0x70, 0x40, 0x70, 0x40,    // row 1 - 11
        0x40, 0xFE, 0x00, 0x00, 0x00                                         // row 12 - 16
#endif
};

PROGMEM const unsigned char chr_f16_25[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x61, 0x91, 0x92, 0x64, 0x08, 0x10, 0x26, 0x49,    // row 1 - 11
        0x89, 0x86, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_26[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x20, 0x50, 0x88, 0x88, 0x50, 0x20, 0x52, 0x8C,    // row 1 - 11
        0x8C, 0x73, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_27[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_28[16] =         // 1 unsigned char per row
{
        0x00, 0x0C, 0x10, 0x20, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80,    // row 1 - 11
        0x40, 0x40, 0x20, 0x10, 0x0C                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_29[16] =         // 1 unsigned char per row
{
        0x00, 0xC0, 0x20, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04,    // row 1 - 11
        0x08, 0x08, 0x10, 0x20, 0xC0                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_2A[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x10, 0x92, 0x54, 0x38, 0x54, 0x92, 0x10,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_2B[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_2C[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0xC0, 0xC0, 0x40, 0x80, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_2D[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_2E[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0xC0, 0xC0, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_2F[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40,    // row 1 - 11
        0x40, 0x80, 0x80, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_30[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x82, 0x82, 0x82, 0x82, 0x44,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_31[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x10, 0x10,    // row 1 - 11
        0x10, 0x7C, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_32[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x02, 0x04, 0x18, 0x20, 0x40,    // row 1 - 11
        0x80, 0xFE, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_33[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x78, 0x84, 0x02, 0x04, 0x38, 0x04, 0x02, 0x02,    // row 1 - 11
        0x84, 0x78, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_34[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x04, 0x0C, 0x14, 0x24, 0x44, 0x84, 0xFE, 0x04,    // row 1 - 11
        0x04, 0x04, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_35[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xFC, 0x80, 0x80, 0x80, 0xF8, 0x04, 0x02, 0x02,    // row 1 - 11
        0x84, 0x78, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_36[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x3C, 0x40, 0x80, 0x80, 0xB8, 0xC4, 0x82, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_37[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10,    // row 1 - 11
        0x10, 0x10, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_38[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x44, 0x38, 0x44, 0x82, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_39[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x46, 0x3A, 0x02, 0x02,    // row 1 - 11
        0x04, 0x78, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_3A[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0xC0, 0xC0,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_3B[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0xC0, 0xC0,    // row 1 - 11
        0x40, 0x80, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_3C[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20,    // row 1 - 11
        0x10, 0x08, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_3D[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_3E[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20,    // row 1 - 11
        0x40, 0x80, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_3F[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x02, 0x04, 0x08, 0x10, 0x10,    // row 1 - 11
        0x00, 0x10, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_40[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x3C, 0x42, 0x99, 0xA5, 0xA5, 0xA5, 0xA5, 0x9E,    // row 1 - 11
        0x40, 0x3E, 0x00, 0x00, 0x00                                         // row 12 - 16
};
// A
PROGMEM const unsigned char chr_f16_41[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x7C, 0x82,    // row 1 - 11
        0x82, 0x82, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_42[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xF8, 0x84, 0x82, 0x84, 0xF8, 0x84, 0x82, 0x82,    // row 1 - 11
        0x84, 0xF8, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_43[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x3C, 0x42, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,    // row 1 - 11
        0x42, 0x3C, 0x00, 0x00, 0x00                                         // row 12 - 16
};
PROGMEM const unsigned char chr_f16_44[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xF8, 0x84, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,    // row 1 - 11
        0x84, 0xF8, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_45[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xFE, 0x80, 0x80, 0x80, 0xFC, 0x80, 0x80, 0x80,    // row 1 - 11
        0x80, 0xFE, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_46[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xFE, 0x80, 0x80, 0x80, 0xF8, 0x80, 0x80, 0x80,    // row 1 - 11
        0x80, 0x80, 0x00, 0x00, 0x00                                         // row 12 - 16
};
PROGMEM const unsigned char chr_f16_47[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x3C, 0x42, 0x80, 0x80, 0x80, 0x9C, 0x82, 0x82,    // row 1 - 11
        0x42, 0x3C, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_48[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0xFC, 0x84, 0x84, 0x84,    // row 1 - 11
        0x84, 0x84, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_49[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,    // row 1 - 11
        0x40, 0xE0, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_4A[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_4B[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x84, 0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88,    // row 1 - 11
        0x84, 0x82, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_4C[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,    // row 1 - 11
        0x80, 0xFC, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_4D[32] =         // 2 unsigned chars per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x80, 0xC1, 0x80, 0xA2, 0x80,    // row 1 - 6
        0xA2, 0x80, 0x94, 0x80, 0x94, 0x80, 0x88, 0x80, 0x88, 0x80, 0x80, 0x80,    // row 7 - 12
        0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                             // row 13 - 16
};

PROGMEM const unsigned char chr_f16_4E[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xC2, 0xC2, 0xA2, 0xA2, 0x92, 0x92, 0x8A, 0x8A,    // row 1 - 11
        0x86, 0x86, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_4F[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_50[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xF8, 0x84, 0x82, 0x82, 0x82, 0x84, 0xF8, 0x80,    // row 1 - 11
        0x80, 0x80, 0x00, 0x00, 0x00                                         // row 12 - 16
};
PROGMEM const unsigned char chr_f16_51[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,    // row 1 - 11
        0x44, 0x38, 0x08, 0x06, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_52[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xF8, 0x84, 0x82, 0x82, 0x84, 0xF8, 0x90, 0x88,    // row 1 - 11
        0x84, 0x82, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_53[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x80, 0x60, 0x1C, 0x02, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_54[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xFE, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,    // row 1 - 11
        0x10, 0x10, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_55[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_56[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x44, 0x44, 0x28, 0x28,    // row 1 - 11
        0x10, 0x10, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_57[32] =         // 2 unsigned chars per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,    // row 1 - 6
        0x88, 0x80, 0x88, 0x80, 0x49, 0x00, 0x55, 0x00, 0x55, 0x00, 0x22, 0x00,    // row 7 - 12
        0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                             // row 13 - 16
};

PROGMEM const unsigned char chr_f16_58[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x82, 0x82, 0x44, 0x28, 0x10, 0x10, 0x28, 0x44,    // row 1 - 11
        0x82, 0x82, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_59[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x44, 0x28, 0x10, 0x10, 0x10,    // row 1 - 11
        0x10, 0x10, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_5A[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xFE, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x40,    // row 1 - 11
        0x80, 0xFE, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_5B[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,    // row 1 - 11
        0x80, 0x80, 0xE0, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_5C[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08,    // row 1 - 11
        0x08, 0x04, 0x04, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_5D[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,    // row 1 - 11
        0x20, 0x20, 0xE0, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_5E[32] =         // 1 unsigned chars per row
{
        0x00, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_5F[32] =         // 1 unsigned chars per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0xFF, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_60[16] =         // 1 unsigned char per row
{
#ifdef TFT_ESPI_GRAVE_IS_DEGREE
        0x00, 0x00, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11   Degree symbol
        0x00, 0x00, 0x00, 0x00, 0x00
#else
        0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11   Grave accent
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
#endif
};

PROGMEM const unsigned char chr_f16_61[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x08, 0x04, 0x74, 0x8C,    // row 1 - 11
        0x8C, 0x74, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_62[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xB0, 0xC8, 0x84, 0x84, 0x84,    // row 1 - 11
        0xC8, 0xB0, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_63[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x80, 0x80, 0x80,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_64[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x34, 0x4C, 0x84, 0x84, 0x84,    // row 1 - 11
        0x4C, 0x34, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_65[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x84, 0xF8, 0x80,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_66[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x30, 0x48, 0x40, 0x40, 0x40, 0xE0, 0x40, 0x40,    // row 1 - 11
        0x40, 0x40, 0x00, 0x00, 0x00                                         // row 12 - 16
};
PROGMEM const unsigned char chr_f16_67[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x4C, 0x84, 0x84, 0x84,    // row 1 - 11
        0x4C, 0x34, 0x04, 0x08, 0x70                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_68[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xB0, 0xC8, 0x84, 0x84, 0x84,    // row 1 - 11
        0x84, 0x84, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_69[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40,    // row 1 - 11
        0x40, 0x40, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_6A[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x10,    // row 1 - 11
        0x10, 0x10, 0x10, 0x90, 0x60                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_6B[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x88, 0x90, 0xA0, 0xC0, 0xA0,    // row 1 - 11
        0x90, 0x88, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_6C[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,    // row 1 - 11
        0x40, 0x40, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_6D[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xD2, 0x92, 0x92, 0x92,    // row 1 - 11
        0x92, 0x92, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_6E[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xC8, 0x84, 0x84, 0x84,    // row 1 - 11
        0x84, 0x84, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_6F[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82,    // row 1 - 11
        0x44, 0x38, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_70[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xC8, 0x84, 0x84, 0x84,    // row 1 - 11
        0xC8, 0xB0, 0x80, 0x80, 0x80                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_71[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x4C, 0x84, 0x84, 0x84,    // row 1 - 11
        0x4C, 0x34, 0x04, 0x04, 0x06                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_72[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80,    // row 1 - 11
        0x80, 0x80, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_73[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x70, 0x08,    // row 1 - 11
        0x88, 0x70, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_74[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x40,    // row 1 - 11
        0x40, 0x30, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_75[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84,    // row 1 - 11
        0x4C, 0x34, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_76[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x44,    // row 1 - 11
        0x28, 0x10, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_77[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x92, 0x92,    // row 1 - 11
        0xAA, 0x44, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_78[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x50, 0x20, 0x50,    // row 1 - 11
        0x88, 0x88, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_79[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84,    // row 1 - 11
        0x4C, 0x34, 0x04, 0x08, 0x70                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_7A[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x04, 0x08, 0x30, 0x40,    // row 1 - 11
        0x80, 0xFC, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_7B[16] =         // 1 unsigned char per row
{
        0x00, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40, 0x20, 0x20,    // row 1 - 11
        0x20, 0x20, 0x20, 0x20, 0x10                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_7C[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,    // row 1 - 11
        0x40, 0x40, 0x40, 0x40, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_7D[16] =         // 1 unsigned char per row
{
        0x00, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x20, 0x20,    // row 1 - 11
        0x20, 0x20, 0x20, 0x20, 0x40                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_7E[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

PROGMEM const unsigned char chr_f16_7F[16] =         // 1 unsigned char per row
{
        0x00, 0x00, 0x30, 0x48, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,    // row 1 - 11
        0x00, 0x00, 0x00, 0x00, 0x00                                         // row 12 - 16
};

// Ђ
PROGMEM const unsigned char chr_f16_80[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B01111000,
        B01000100,
        B01000010,
        B01000010,
        B01000100,
        B01011000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ѓ
PROGMEM const unsigned char chr_f16_81[16] =         // 1 unsigned char per row
{
        B00001000,
        B00010000,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ‚ (нижняя одиночная кавычка)
PROGMEM const unsigned char chr_f16_82[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B11000000,
        B11000000, // Нижняя линия большой буквы
        B01000000,
        B10000000,
        B00000000
};

// ѓ
PROGMEM const unsigned char chr_f16_83[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00010000, // Верхняя линия большой буквы
        B00100000,
        B00000000,
        B11110000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// „
PROGMEM const unsigned char chr_f16_84[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B11011000,
        B11011000, // Нижняя линия большой буквы
        B01001000,
        B10010000,
        B00000000
};

// Троеточие
PROGMEM const unsigned char chr_f16_85[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B11011011,
        B11011011, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// †
PROGMEM const unsigned char chr_f16_86[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00010000,
        B00010000, // Верхняя линия большой буквы
        B00010000,
        B11111110,
        B00010000, // Верхняя линия маленькой буквы
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000, // Нижняя линия большой буквы
        B00010000,
        B00000000,
        B00000000
};

// ‡
PROGMEM const unsigned char chr_f16_87[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00010000,
        B00010000, // Верхняя линия большой буквы
        B00010000,
        B11111110,
        B00010000, // Верхняя линия маленькой буквы
        B00010000,
        B00010000,
        B00010000,
        B11111110,
        B00010000,
        B00010000, // Нижняя линия большой буквы
        B00010000,
        B00000000,
        B00000000
};

// €
PROGMEM const unsigned char chr_f16_88[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00011110, // Верхняя линия большой буквы
        B00100000,
        B01000000,
        B11111110, // Верхняя линия маленькой буквы
        B01000000,
        B11111110,
        B01000000,
        B01000000,
        B00100000,
        B00011110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ‰
PROGMEM const unsigned char chr_f16_89[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01100001, // Верхняя линия большой буквы
        B10010001,
        B10010010,
        B01100100, // Верхняя линия маленькой буквы
        B00001000,
        B00010000,
        B00100000,
        B01010010,
        B10101101,
        B10010010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Љ
PROGMEM const unsigned char chr_f16_8A[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01111000, // Верхняя линия большой буквы
        B01001000,
        B01001000,
        B01001000, // Верхняя линия маленькой буквы
        B01001100,
        B01001010,
        B01001001,
        B01001001,
        B01001010,
        B10001100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ‹
PROGMEM const unsigned char chr_f16_8B[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00100000, // Верхняя линия маленькой буквы
        B01000000,
        B10000000,
        B01000000,
        B00100000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Њ
PROGMEM const unsigned char chr_f16_8C[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10010000, // Верхняя линия большой буквы
        B10010000,
        B10010000,
        B10010000, // Верхняя линия маленькой буквы
        B11111000,
        B10010100,
        B10010010,
        B10010010,
        B10010100,
        B10011000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ќ
PROGMEM const unsigned char chr_f16_8D[16] =         // 1 unsigned char per row
{
        B00001000,
        B00010000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000100,
        B10001000,
        B10010000, // Верхняя линия маленькой буквы
        B11100000,
        B10100000,
        B10010000,
        B10001000,
        B10000100,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ћ
PROGMEM const unsigned char chr_f16_8E[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111100, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B01111000,
        B01000100,
        B01000010,
        B01000010,
        B01000010,
        B01000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Џ
PROGMEM const unsigned char chr_f16_8F[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B10000010,
        B10000010,
        B10000010,
        B10000010,
        B11111110, // Нижняя линия большой буквы
        B00010000,
        B00000000,
        B00000000
};

// ђ
PROGMEM const unsigned char chr_f16_90[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01000000, // Верхняя линия большой буквы
        B11110000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B01011000,
        B01100100,
        B01000100,
        B01000100,
        B01000100,
        B01000100, // Нижняя линия большой буквы
        B00001000,
        B00010000,
        B00000000
};

// ‘ (верхняя левая одиночная кавычка)
PROGMEM const unsigned char chr_f16_91[16] =         // 1 unsigned char per row
{
        B00000000,
        B01000000,
        B10000000,
        B11000000, // Верхняя линия большой буквы
        B11000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ’ (верхняя правая одиночная кавычка)
PROGMEM const unsigned char chr_f16_92[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11000000, // Верхняя линия большой буквы
        B11000000,
        B01000000,
        B10000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// “ верхняя открывающая двойная кавычка
PROGMEM const unsigned char chr_f16_93[16] =         // 1 unsigned char per row
{
        B00000000,
        B01001000,
        B10010000,
        B11011000, // Верхняя линия большой буквы
        B11011000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ” закрывающая двойная кавычка
PROGMEM const unsigned char chr_f16_94[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11011000, // Верхняя линия большой буквы
        B11011000,
        B01001000,
        B10010000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// • маркер списка
PROGMEM const unsigned char chr_f16_95[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01110000, // Верхняя линия маленькой буквы
        B11111000,
        B11111000,
        B11111000,
        B01110000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// – N-dash
PROGMEM const unsigned char chr_f16_96[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B11111110,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// — M-dash
PROGMEM const unsigned char chr_f16_97[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B11111111,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// undefined/unmappable control character
PROGMEM const unsigned char chr_f16_98[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ™
PROGMEM const unsigned char chr_f16_99[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11101110, // Верхняя линия большой буквы
        B01001110,
        B01001010,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// љ
PROGMEM const unsigned char chr_f16_9A[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111000, // Верхняя линия маленькой буквы
        B01001000,
        B01001000,
        B01001110,
        B01001001,
        B01001001,
        B10001110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ›
PROGMEM const unsigned char chr_f16_9B[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000000, // Верхняя линия маленькой буквы
        B01000000,
        B00100000,
        B01000000,
        B10000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// њ
PROGMEM const unsigned char chr_f16_9C[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10001000, // Верхняя линия маленькой буквы
        B10001000,
        B10001000,
        B11111110,
        B10001001,
        B10001001,
        B10001110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ќ
PROGMEM const unsigned char chr_f16_9D[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00010000, // Верхняя линия большой буквы
        B00100000,
        B00000000,
        B10001000, // Верхняя линия маленькой буквы
        B10010000,
        B10100000,
        B11000000,
        B10100000,
        B10010000,
        B10001000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ћ
PROGMEM const unsigned char chr_f16_9E[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01000000, // Верхняя линия большой буквы
        B11110000,
        B01000000,
        B01111000, // Верхняя линия маленькой буквы
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B01000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// џ
PROGMEM const unsigned char chr_f16_9F[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10001000, // Верхняя линия маленькой буквы
        B10001000,
        B10001000,
        B10001000,
        B10001000,
        B10001000,
        B11111000, // Нижняя линия большой буквы
        B00100000,
        B00000000,
        B00000000
};

// Неразрывный пробел
PROGMEM const unsigned char chr_f16_A0[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ў
PROGMEM const unsigned char chr_f16_A1[16] =         // 1 unsigned char per row
{
        B00000000,
        B01000100,
        B00111000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B01000010, // Верхняя линия маленькой буквы
        B00111110,
        B00000010,
        B00000010,
        B00000010,
        B00000100,
        B01111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ў
PROGMEM const unsigned char chr_f16_A2[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01001000, // Верхняя линия большой буквы
        B00110000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B01000100,
        B00111100, // Нижняя линия большой буквы
        B00000100,
        B00001000,
        B01110000
};

// Ј
PROGMEM const unsigned char chr_f16_A3[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00001110, // Верхняя линия большой буквы
        B00000010,
        B00000010,
        B00000010, // Верхняя линия маленькой буквы
        B00000010,
        B00000010,
        B00000010,
        B10000010,
        B01000100,
        B00111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ¤
PROGMEM const unsigned char chr_f16_A4[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B10000010,
        B01111100,
        B01000100, // Верхняя линия маленькой буквы
        B01000100,
        B01000100,
        B01000100,
        B01111100,
        B10000010,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ґ
PROGMEM const unsigned char chr_f16_A5[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000010,
        B11111110, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ¦
PROGMEM const unsigned char chr_f16_A6[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01000000, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// §
PROGMEM const unsigned char chr_f16_A7[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01110000, // Верхняя линия большой буквы
        B10001000,
        B10000000,
        B01110000, // Верхняя линия маленькой буквы
        B10001000,
        B10001000,
        B01110000,
        B00001000,
        B10001000,
        B01110000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ё
PROGMEM const unsigned char chr_f16_A8[16] =         // 1 unsigned char per row
{
        B00000000,
        B01000100,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B11111000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B11111110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ©
PROGMEM const unsigned char chr_f16_A9[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111000, // Верхняя линия большой буквы
        B01000100,
        B10010010,
        B10101010, // Верхняя линия маленькой буквы
        B10100010,
        B10101010,
        B10010010,
        B01000100,
        B00111000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Є
PROGMEM const unsigned char chr_f16_AA[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111110, // Верхняя линия большой буквы
        B01000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B11111100,
        B10000000,
        B10000000,
        B10000000,
        B01000000,
        B00111110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// «
PROGMEM const unsigned char chr_f16_AB[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00100100, // Верхняя линия маленькой буквы
        B01001000,
        B10010000,
        B01001000,
        B00100100,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ¬
PROGMEM const unsigned char chr_f16_AC[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111110, // Верхняя линия маленькой буквы
        B00000010,
        B00000010,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Мягкий перенос
PROGMEM const unsigned char chr_f16_AD[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ®
PROGMEM const unsigned char chr_f16_AE[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111000, // Верхняя линия большой буквы
        B01000100,
        B10110010,
        B10101010, // Верхняя линия маленькой буквы
        B10110010,
        B10101010,
        B10101010,
        B01000100,
        B00111000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Ї
PROGMEM const unsigned char chr_f16_AF[16] =         // 1 unsigned char per row
{
        B00000000,
        B10100000,
        B00000000,
        B11100000, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B11100000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// °
PROGMEM const unsigned char chr_f16_B0[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01100000, // Верхняя линия большой буквы
        B10010000,
        B10010000,
        B01100000, // Верхняя линия маленькой буквы
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ±
PROGMEM const unsigned char chr_f16_B1[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00010000, // Верхняя линия большой буквы
        B00010000,
        B00010000,
        B11111110, // Верхняя линия маленькой буквы
        B00010000,
        B00010000,
        B00010000,
        B00000000,
        B11111110,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// І
PROGMEM const unsigned char chr_f16_B2[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11100000, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B11100000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// і
PROGMEM const unsigned char chr_f16_B3[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B01000000,
        B00000000,
        B11000000, // Верхняя линия маленькой буквы
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B11100000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ґ
PROGMEM const unsigned char chr_f16_B4[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00010000,
        B11110000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// µ
PROGMEM const unsigned char chr_f16_B5[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B11000100,
        B10111010, // Нижняя линия большой буквы
        B10000000,
        B10000000,
        B00000000
};

// ¶
PROGMEM const unsigned char chr_f16_B6[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111110, // Верхняя линия большой буквы
        B01111010,
        B11111010,
        B11111010, // Верхняя линия маленькой буквы
        B01111010,
        B00111010,
        B00001010,
        B00001010,
        B00001010,
        B00001010, // Нижняя линия большой буквы
        B00001010,
        B00000000,
        B00000000
};

// ·
PROGMEM const unsigned char chr_f16_B7[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00000000, // Верхняя линия маленькой буквы
        B00000000,
        B11000000,
        B11000000,
        B00000000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ё
PROGMEM const unsigned char chr_f16_B8[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B01001000,
        B00000000,
        B01111000, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B11111100,
        B10000000,
        B10000000,
        B01111100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};
// №
PROGMEM const unsigned char chr_f16_B9[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10001010, // Верхняя линия большой буквы
        B10001000,
        B11001010,
        B10101000, // Верхняя линия маленькой буквы
        B10011000,
        B10001000,
        B10001000,
        B10001000,
        B10001000,
        B10001000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// є
PROGMEM const unsigned char chr_f16_BA[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111100, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B11111000,
        B10000000,
        B10000000,
        B01111100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// »
PROGMEM const unsigned char chr_f16_BB[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10010000, // Верхняя линия маленькой буквы
        B01001000,
        B00100100,
        B01001000,
        B10010000,
        B00000000,
        B00000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ј
PROGMEM const unsigned char chr_f16_BC[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B01000000,
        B00000000,
        B11000000, // Верхняя линия маленькой буквы
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000, // Нижняя линия большой буквы
        B10000000,
        B00000000,
        B00000000
};

// Ѕ
PROGMEM const unsigned char chr_f16_BD[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111100, // Верхняя линия большой буквы
        B01000010,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B01110000,
        B00001100,
        B00000010,
        B00000010,
        B10000100,
        B01111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ѕ
PROGMEM const unsigned char chr_f16_BE[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B01110000,
        B00001000,
        B00001000,
        B11110000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// ї
PROGMEM const unsigned char chr_f16_BF[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B10100000,
        B00000000,
        B11000000, // Верхняя линия маленькой буквы
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B01000000,
        B11100000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

// Русские буквы
// А большое русское
PROGMEM const unsigned char chr_f16_C0[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00010000, // Верхняя линия большой буквы
        B00010000,
        B00101000,
        B00101000, // Верхняя линия маленькой буквы
        B01000100,
        B01000100,
        B01111100,
        B10000010,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C1[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111100, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B11111000,
        B10000100,
        B10000010,
        B10000010,
        B10000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C2[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111000, // Верхняя линия большой буквы
        B10000100,
        B10000010,
        B10000100, // Верхняя линия маленькой буквы
        B11111000,
        B10000100,
        B10000010,
        B10000010,
        B10000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C3[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C4[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111100, // Верхняя линия большой буквы
        B01000100,
        B01000100,
        B01000100, // Верхняя линия маленькой буквы
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B11111110, // Нижняя линия большой буквы
        B10000010,
        B10000010,
        B00000000
};

PROGMEM const unsigned char chr_f16_C5[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B11111000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B11111110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C6[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10010010, // Верхняя линия большой буквы
        B10010010,
        B01010100,
        B01010100, // Верхняя линия маленькой буквы
        B00111000,
        B01010100,
        B01010100,
        B01010100,
        B10010010,
        B10010010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C7[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111000, // Верхняя линия большой буквы
        B00000100,
        B00000010,
        B00000100, // Верхняя линия маленькой буквы
        B00111000,
        B00000100,
        B00000010,
        B00000010,
        B00000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C8[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000110,
        B10001010,
        B10010010,
        B10100010,
        B11000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_C9[16] =         // 1 unsigned char per row
{
        B00000000,
        B00111000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000110,
        B10001010,
        B10010010,
        B10100010,
        B11000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_CA[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000100,
        B10001000,
        B11110000, // Верхняя линия маленькой буквы
        B10001000,
        B10001000,
        B10000100,
        B10000100,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_CB[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111110, // Верхняя линия большой буквы
        B01000010,
        B01000010,
        B01000010, // Верхняя линия маленькой буквы
        B01000010,
        B01000010,
        B01000010,
        B01000010,
        B01000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_CC[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B11000110,
        B11000110,
        B10101010, // Верхняя линия маленькой буквы
        B10101010,
        B10010010,
        B10010010,
        B10000010,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_CD[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B11111110,
        B10000010,
        B10000010,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_CE[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111000, // Верхняя линия большой буквы
        B01000100,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B10000010,
        B10000010,
        B10000010,
        B01000100,
        B00111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_CF[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B10000010,
        B10000010,
        B10000010,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D0[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111000, // Верхняя линия большой буквы
        B10000100,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10000100,
        B10001000,
        B11110000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D1[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111000, // Верхняя линия большой буквы
        B01000100,
        B10000010,
        B10000000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000010,
        B01000100,
        B00111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D2[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111110, // Верхняя линия большой буквы
        B00010000,
        B00010000,
        B00010000, // Верхняя линия маленькой буквы
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D3[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B01000010, // Верхняя линия маленькой буквы
        B00111110,
        B00000010,
        B00000010,
        B00000010,
        B00000100,
        B01111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D4[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B01111100, // Верхняя линия большой буквы
        B10010010,
        B10010010,
        B10010010, // Верхняя линия маленькой буквы
        B10010010,
        B10010010,
        B01111100,
        B00010000,
        B00010000,
        B00010000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D5[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B01000100,
        B00101000, // Верхняя линия маленькой буквы
        B00010000,
        B00101000,
        B00101000,
        B01000100,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D6[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000100, // Верхняя линия большой буквы
        B10000100,
        B10000100,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B11111110, // Нижняя линия большой буквы
        B00000010,
        B00000010,
        B00000000
};

PROGMEM const unsigned char chr_f16_D7[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B01000010,
        B00111110,
        B00000010,
        B00000010,
        B00000010,
        B00000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D8[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10010010,
        B10010010,
        B10010010,
        B10010010,
        B10010010,
        B11111110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_D9[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B10010010,
        B10010010,
        B10010010,
        B10010010,
        B10010010,
        B11111111, // Нижняя линия большой буквы
        B00000001,
        B00000001,
        B00000000
};

PROGMEM const unsigned char chr_f16_DA[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11000000, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B01000000, // Верхняя линия маленькой буквы
        B01111000,
        B01000100,
        B01000010,
        B01000010,
        B01000100,
        B01111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_DB[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000010, // Верхняя линия большой буквы
        B10000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B11100010,
        B10010010,
        B10001010,
        B10001010,
        B10010010,
        B11100010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_DC[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10000000, // Верхняя линия большой буквы
        B10000000,
        B10000000,
        B10000000, // Верхняя линия маленькой буквы
        B11111000,
        B10000100,
        B10000010,
        B10000010,
        B10000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_DD[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B11111000, // Верхняя линия большой буквы
        B00000100,
        B00000010,
        B00000010, // Верхняя линия маленькой буквы
        B00111110,
        B00000010,
        B00000010,
        B00000010,
        B00000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_DE[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B10001110, // Верхняя линия большой буквы
        B10010001,
        B10010001,
        B10010001, // Верхняя линия маленькой буквы
        B11110001,
        B10010001,
        B10010001,
        B10010001,
        B10010001,
        B10001110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_DF[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111110, // Верхняя линия большой буквы
        B01000010,
        B10000010,
        B10000010, // Верхняя линия маленькой буквы
        B01000010,
        B00111110,
        B00010010,
        B00100010,
        B01000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E0[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111000, // Верхняя линия маленькой буквы
        B00000100,
        B00000100,
        B01111100,
        B10000100,
        B10000100,
        B01111100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E1[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00111110, // Верхняя линия большой буквы
        B01000000,
        B01000000,
        B00111000, // Верхняя линия маленькой буквы
        B01000100,
        B10000010,
        B10000010,
        B10000010,
        B01000100,
        B00111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E2[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111000, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B11111000,
        B10000100,
        B10000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E3[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000,
        B10000000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E4[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00011100, // Верхняя линия маленькой буквы
        B00100100,
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B11111110, // Нижняя линия большой буквы
        B10000010,
        B10000010,
        B00000000
};

PROGMEM const unsigned char chr_f16_E5[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111000, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B11111100,
        B10000000,
        B10000000,
        B01111100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E6[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10010010, // Верхняя линия маленькой буквы
        B10010010,
        B01010100,
        B00111000,
        B01010100,
        B10010010,
        B10010010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E7[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111000, // Верхняя линия маленькой буквы
        B00000100,
        B00000100,
        B00111000,
        B00000100,
        B00000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E8[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10001100,
        B10010100,
        B10100100,
        B11000100,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_E9[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00110000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10001100,
        B10010100,
        B10100100,
        B11000100,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_EA[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10001000,
        B10010000,
        B11100000,
        B10010000,
        B10001000,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_EB[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00111100, // Верхняя линия маленькой буквы
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B01000100,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_EC[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000010, // Верхняя линия маленькой буквы
        B11000110,
        B10101010,
        B10010010,
        B10000010,
        B10000010,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_ED[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B11111100,
        B10000100,
        B10000100,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_EE[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00111000, // Верхняя линия маленькой буквы
        B01000100,
        B10000010,
        B10000010,
        B10000010,
        B01000100,
        B00111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_EF[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_F0[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11110000, // Верхняя линия маленькой буквы
        B10001000,
        B10000100,
        B10000100,
        B10000100,
        B10001000,
        B11110000, // Нижняя линия большой буквы
        B10000000,
        B10000000,
        B10000000
};

PROGMEM const unsigned char chr_f16_F1[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B00111100, // Верхняя линия маленькой буквы
        B01000000,
        B10000000,
        B10000000,
        B10000000,
        B01000000,
        B00111100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_F2[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111110, // Верхняя линия маленькой буквы
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_F3[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B01000100,
        B00111100, // Нижняя линия большой буквы
        B00000100,
        B00001000,
        B01110000
};

PROGMEM const unsigned char chr_f16_F4[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111100, // Верхняя линия маленькой буквы
        B10010010,
        B10010010,
        B10010010,
        B10010010,
        B10010010,
        B01111100, // Нижняя линия большой буквы
        B00010000,
        B00010000,
        B00010000
};

PROGMEM const unsigned char chr_f16_F5[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000010, // Верхняя линия маленькой буквы
        B01000100,
        B00101000,
        B00010000,
        B00101000,
        B01000100,
        B10000010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_F6[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B10000100,
        B11111110, // Нижняя линия большой буквы
        B00000010,
        B00000010,
        B00000000
};

PROGMEM const unsigned char chr_f16_F7[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B01111100,
        B00000100,
        B00000100,
        B00000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_F8[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B10000010,
        B10010010,
        B10010010,
        B10010010,
        B11111110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_F9[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B10000010,
        B10010010,
        B10010010,
        B10010010,
        B11111111, // Нижняя линия большой буквы
        B00000001,
        B00000001,
        B00000000
};

PROGMEM const unsigned char chr_f16_FA[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11000000, // Верхняя линия маленькой буквы
        B01000000,
        B01000000,
        B01111100,
        B01000010,
        B01000010,
        B01111100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_FB[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000010, // Верхняя линия маленькой буквы
        B10000010,
        B10000010,
        B11110010,
        B10001010,
        B10001010,
        B11110010, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_FC[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10000000, // Верхняя линия маленькой буквы
        B10000000,
        B10000000,
        B11111000,
        B10000100,
        B10000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_FD[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B11111000, // Верхняя линия маленькой буквы
        B00000100,
        B00000100,
        B00111100,
        B00000100,
        B00000100,
        B11111000, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_FE[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B10001110, // Верхняя линия маленькой буквы
        B10010001,
        B10010001,
        B11110001,
        B10010001,
        B10010001,
        B10001110, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};

PROGMEM const unsigned char chr_f16_FF[16] =         // 1 unsigned char per row
{
        B00000000,
        B00000000,
        B00000000,
        B00000000, // Верхняя линия большой буквы
        B00000000,
        B00000000,
        B01111100, // Верхняя линия маленькой буквы
        B10000100,
        B10000100,
        B01111100,
        B00100100,
        B01000100,
        B10000100, // Нижняя линия большой буквы
        B00000000,
        B00000000,
        B00000000
};


PROGMEM const unsigned char* const chrtbl_f16[224] =       // character pointer table
{
        chr_f16_20, chr_f16_21, chr_f16_22, chr_f16_23, chr_f16_24, chr_f16_25, chr_f16_26, chr_f16_27, // 20-27 
        chr_f16_28, chr_f16_29, chr_f16_2A, chr_f16_2B, chr_f16_2C, chr_f16_2D, chr_f16_2E, chr_f16_2F, // 28-2F 
        chr_f16_30, chr_f16_31, chr_f16_32, chr_f16_33, chr_f16_34, chr_f16_35, chr_f16_36, chr_f16_37, // 30-37 01234567
        chr_f16_38, chr_f16_39, chr_f16_3A, chr_f16_3B, chr_f16_3C, chr_f16_3D, chr_f16_3E, chr_f16_3F, // 38-3F 89:;<=>?
        chr_f16_40, chr_f16_41, chr_f16_42, chr_f16_43, chr_f16_44, chr_f16_45, chr_f16_46, chr_f16_47, // 40-47 @ABCDEFG
        chr_f16_48, chr_f16_49, chr_f16_4A, chr_f16_4B, chr_f16_4C, chr_f16_4D, chr_f16_4E, chr_f16_4F, // 48-4F HIJKLMNO
        chr_f16_50, chr_f16_51, chr_f16_52, chr_f16_53, chr_f16_54, chr_f16_55, chr_f16_56, chr_f16_57, // 50-57 PQRSTUVW
        chr_f16_58, chr_f16_59, chr_f16_5A, chr_f16_5B, chr_f16_5C, chr_f16_5D, chr_f16_5E, chr_f16_5F, // 58-5F XYZ[\]^_
        chr_f16_60, chr_f16_61, chr_f16_62, chr_f16_63, chr_f16_64, chr_f16_65, chr_f16_66, chr_f16_67, // 60-67 `abcdefg
        chr_f16_68, chr_f16_69, chr_f16_6A, chr_f16_6B, chr_f16_6C, chr_f16_6D, chr_f16_6E, chr_f16_6F, // 68-6F hijklmno
        chr_f16_70, chr_f16_71, chr_f16_72, chr_f16_73, chr_f16_74, chr_f16_75, chr_f16_76, chr_f16_77, // 70-77 pqrstuvw
        chr_f16_78, chr_f16_79, chr_f16_7A, chr_f16_7B, chr_f16_7C, chr_f16_7D, chr_f16_7E, chr_f16_7F, // 78-7F xyz{|}~ 
        chr_f16_80, chr_f16_81, chr_f16_82, chr_f16_83, chr_f16_84, chr_f16_85, chr_f16_86, chr_f16_87, // 80-87 ЂЃ‚ѓ„…†‡
        chr_f16_88, chr_f16_89, chr_f16_8A, chr_f16_8B, chr_f16_8C, chr_f16_8D, chr_f16_8E, chr_f16_8F, // 88-8F €‰Љ‹ЊЌЋЏ
        chr_f16_90, chr_f16_91, chr_f16_92, chr_f16_93, chr_f16_94, chr_f16_95, chr_f16_96, chr_f16_97, // 90-97 ђ‘’“”•–—
        chr_f16_98, chr_f16_99, chr_f16_9A, chr_f16_9B, chr_f16_9C, chr_f16_9D, chr_f16_9E, chr_f16_9F, // 98-9F  ™љ›њќћџ
        chr_f16_A0, chr_f16_A1, chr_f16_A2, chr_f16_A3, chr_f16_A4, chr_f16_A5, chr_f16_A6, chr_f16_A7, // A0-A7  ЎўЈ¤Ґ¦§
        chr_f16_A8, chr_f16_A9, chr_f16_AA, chr_f16_AB, chr_f16_AC, chr_f16_AD, chr_f16_AE, chr_f16_AF, // A8-AF Ё©Є«¬ ®Ї
        chr_f16_B0, chr_f16_B1, chr_f16_B2, chr_f16_B3, chr_f16_B4, chr_f16_B5, chr_f16_B6, chr_f16_B7, // B0-B7 °±Ііґµ¶·
        chr_f16_B8, chr_f16_B9, chr_f16_BA, chr_f16_BB, chr_f16_BC, chr_f16_BD, chr_f16_BE, chr_f16_BF, // B8-BF ё№є»јЅѕї
        chr_f16_C0, chr_f16_C1, chr_f16_C2, chr_f16_C3, chr_f16_C4, chr_f16_C5, chr_f16_C6, chr_f16_C7, // C0-C7 АБВГДЕЖЗ
        chr_f16_C8, chr_f16_C9, chr_f16_CA, chr_f16_CB, chr_f16_CC, chr_f16_CD, chr_f16_CE, chr_f16_CF, // C8-CF ИЙКЛМНОП
        chr_f16_D0, chr_f16_D1, chr_f16_D2, chr_f16_D3, chr_f16_D4, chr_f16_D5, chr_f16_D6, chr_f16_D7, // D0-D7 РСТУФХЦЧ
        chr_f16_D8, chr_f16_D9, chr_f16_DA, chr_f16_DB, chr_f16_DC, chr_f16_DD, chr_f16_DE, chr_f16_DF, // D8-DF ШЩЪЫЬЭЮЯ
        chr_f16_E0, chr_f16_E1, chr_f16_E2, chr_f16_E3, chr_f16_E4, chr_f16_E5, chr_f16_E6, chr_f16_E7, // E0-E7 абвгдежз
        chr_f16_E8, chr_f16_E9, chr_f16_EA, chr_f16_EB, chr_f16_EC, chr_f16_ED, chr_f16_EE, chr_f16_EF, // E8-EF ийклмноп
        chr_f16_F0, chr_f16_F1, chr_f16_F2, chr_f16_F3, chr_f16_F4, chr_f16_F5, chr_f16_F6, chr_f16_F7, // F0-F7 рстуфхцч
        chr_f16_F8, chr_f16_F9, chr_f16_FA, chr_f16_FB, chr_f16_FC, chr_f16_FD, chr_f16_FE, chr_f16_FF  // F8-FF шщъыьэюя
};
