#pragma once
#include <cstdint>
#include "constants.h"
#include "player.h"

const int BMP_HEADER_SIZE = 14;
const int BMP_DIB_HEADER_SIZE = 12;
const int BMP_TOKEN_SIZE = 5;
const int BMP_BPP = 24;
const int PIXEL_BYTES = 3;
const int BMP_ROW_SIZE = BMP_TOKEN_SIZE * PLAYER_COUNT * PIXEL_BYTES;
const int BMP_TOKEN_ROW_SIZE = BMP_ROW_SIZE * BMP_TOKEN_SIZE;

const char BMP_PLAYER_1_TOKEN[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE] = {
    0,0,0,0,1,
    0,0,0,1,1,
    0,0,1,0,1,
    0,0,0,0,1,
    0,0,0,0,1
};

const char BMP_PLAYER_2_TOKEN[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE] = {
    0,0,1,1,0,
    0,1,0,0,1,
    0,0,0,1,0,
    0,0,1,0,0,
    0,1,1,1,1
};

const char BMP_PLAYER_3_TOKEN[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE] = {
    0,0,1,1,0,
    0,1,0,0,1,
    0,0,0,1,0,
    0,1,0,0,1,
    0,0,1,1,0
};

const char BMP_PLAYER_4_TOKEN[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE] = {
    0,0,1,1,0,
    0,1,0,1,0,
    1,1,1,1,1,
    0,0,0,1,0,
    0,0,0,1,0
};  

const uint8_t black_pixel[PIXEL_BYTES] = {0, 0, 0};
const uint8_t white_pixel[PIXEL_BYTES] = {255, 255, 255};

struct BmpHeader
{
    int8_t bitmap_signature_bytes[2];
    uint32_t size_of_bitmap_file;
    uint32_t reserved_bytes;
    uint32_t pixel_data_offset;
};

struct BmpDIBHeader
{
    uint32_t size_of_this_header;
    uint16_t width;
    uint16_t height;
    uint16_t number_of_color_planes;
    uint16_t bits_per_pixel;
};

uint32_t pixelArraySize(const uint16_t width, const uint16_t height);
void handlePrint(Player _player[], unsigned int board_size, char _arg);
BmpHeader createBmpHeader(uint32_t size_of_bitmap_file);
BmpDIBHeader createBmpDibHeader(const uint16_t width, const uint16_t height);
void writePixelArray(uint8_t *image_start, Player _player[], unsigned int board_size);
void writeTokenArray(uint8_t *position, const char picture[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE]);