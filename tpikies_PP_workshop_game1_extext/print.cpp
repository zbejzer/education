#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "print.h"

#include "constants.h"
#include "base64.h"

using namespace std;

uint32_t pixelArraySize(const uint16_t width, const uint16_t height)
{
    return height * BMP_TOKEN_SIZE * width * BMP_TOKEN_SIZE * BMP_BPP / 8;
}

void handlePrint(Player _player[], unsigned int board_size, char _arg)
{
    // Base players status
    if (_arg == '0' || _arg == '1')
    {
        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            if (_player[i].isInactive)
            {
                cout << "X ";
            }
            else
            {
                cout << _player[i].pos << " ";
            }
        }
    }

    // Extended
    if (_arg == '1')
    {
        unsigned char States = 0;
        unsigned char diode = 128; // 0b10000000

        for (int i = 0; diode > 0; i++)
        {
            States = States | (diode * _player[i].isStarted);
            diode = (diode >> 1);
            States = States | (diode * (_player[i].pos % 2));
            diode = (diode >> 1);
        }

        for (unsigned int i = 0; i < 8; i++)
        {
            if (States & (1 << (7 - i)))
            {
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
    }

    // Base64 of bmp screenshot
    if (_arg == '3')
    {
        uint32_t size_of_bitmap_file = BMP_HEADER_SIZE + BMP_DIB_HEADER_SIZE + pixelArraySize(PLAYER_COUNT, board_size);

        uint8_t *bitmap = (uint8_t*)malloc(size_of_bitmap_file);
        const BmpHeader bmp_header = createBmpHeader(size_of_bitmap_file);
        const BmpDIBHeader bmp_dib_header = createBmpDibHeader(PLAYER_COUNT, board_size);
        
        memcpy(bitmap, &bmp_header, BMP_HEADER_SIZE);
        memcpy(bitmap + BMP_HEADER_SIZE, &bmp_dib_header, BMP_DIB_HEADER_SIZE);
        writePixelArray(bitmap + BMP_HEADER_SIZE + BMP_DIB_HEADER_SIZE, _player, board_size);

        const unsigned int base64_size = getSizeInBase64(size_of_bitmap_file);
        char* base64encoded = base64Encoder(bitmap, size_of_bitmap_file);

        for (size_t i = 0; i < base64_size; i++)
        {
            cout << base64encoded[i];
        }
        
        free(bitmap);
        free(base64encoded);
    }

    cout << endl;
}

BmpHeader createBmpHeader(uint32_t size_of_bitmap_file)
{
    BmpHeader new_bmp_header;

    new_bmp_header.bitmap_signature_bytes[0] = 'B';
    new_bmp_header.bitmap_signature_bytes[1] = 'M';
    new_bmp_header.size_of_bitmap_file = size_of_bitmap_file;
    new_bmp_header.reserved_bytes = 0;
    new_bmp_header.pixel_data_offset = BMP_HEADER_SIZE + BMP_DIB_HEADER_SIZE;

    return new_bmp_header;
}

BmpDIBHeader createBmpDibHeader(const uint16_t width, const uint16_t height)
{
    BmpDIBHeader new_bmp_core_header;

    new_bmp_core_header.size_of_this_header = BMP_DIB_HEADER_SIZE;
    new_bmp_core_header.width = width;
    new_bmp_core_header.height = height;
    new_bmp_core_header.number_of_color_planes = 1;
    new_bmp_core_header.bits_per_pixel = BMP_BPP;

    return new_bmp_core_header;
}

void writePixelArray(uint8_t *image_start, Player _player[], unsigned int board_size)
{
    // set image to white
    for (int pos = 0; pos < BMP_TOKEN_ROW_SIZE * board_size; pos++)
    {
        *(image_start + pos) = (uint8_t)255;
    }

    for (int player_ID = 0; player_ID < PLAYER_COUNT; player_ID++)
    {
        uint8_t *draw_pos = image_start;

        if (_player[player_ID].isInactive)
        {
            draw_pos += player_ID * BMP_TOKEN_SIZE * PIXEL_BYTES;
        }
        else
        {
            draw_pos +=
                (BMP_TOKEN_ROW_SIZE * _player[player_ID].pos) + (player_ID * BMP_TOKEN_SIZE * PIXEL_BYTES);
        }

        if (player_ID == 0)
        {
            writeTokenArray(draw_pos, BMP_PLAYER_1_TOKEN);
        }
        else if (player_ID == 1)
        {
            writeTokenArray(draw_pos, BMP_PLAYER_2_TOKEN);
        }
        else if (player_ID == 2)
        {
            writeTokenArray(draw_pos, BMP_PLAYER_3_TOKEN);
        }
        else if (player_ID == 3)
        {
            writeTokenArray(draw_pos, BMP_PLAYER_4_TOKEN);
        }
    }
}

void writeTokenArray(uint8_t *start_position, const char picture[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE])
{
    uint8_t *current_pos;

    for (unsigned int row = 0; row < BMP_TOKEN_SIZE; row++)
    {
        current_pos = start_position + (BMP_ROW_SIZE * row);

        for (unsigned int col = 0; col < BMP_TOKEN_SIZE; col++)
        {
            if (picture[row][col] == 1)
            {
                memcpy(current_pos, black_pixel, 3);
            }
            else
            {
                memcpy(current_pos, white_pixel, 3);
            }

            current_pos += PIXEL_BYTES;
        }
    }
}