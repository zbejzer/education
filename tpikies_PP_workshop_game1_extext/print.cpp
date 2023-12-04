#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "print.h"

#include "constants.h"
#include "base64.h"

using namespace std;

void handlePrint(Player _players[], unsigned int board_size, char _arg)
{
    // Base players status
    if (_arg == '0' || _arg == '1')
    {
        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            if (_players[i].isInactive)
            {
                cout << "X ";
            }
            else
            {
                cout << _players[i].pos << " ";
            }
        }
    }

    // Extended
    if (_arg == '1')
    {
        unsigned char states = 0;
        unsigned char diode = 128; // 0b10000000

        for (int i = 0; diode > 0; i++)
        {
            states = states | (diode * _players[i].isStarted);
            diode = (diode >> 1);
            states = states | (diode * (_players[i].pos % 2));
            diode = (diode >> 1);
        }

        for (unsigned int i = 0; i < 8; i++)
        {
            if (states & (1 << (7 - i)))
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
        const uint16_t width = (uint16_t)(PLAYER_COUNT * BMP_TOKEN_SIZE);
        const uint16_t height = (uint16_t)((board_size + 1) * BMP_TOKEN_SIZE);
        unsigned int pixel_array_size = height * width * BMP_PIXEL_SIZE;
        const uint32_t size_of_bitmap_file = (uint32_t)(BMP_HEADER_SIZE + BMP_DIB_HEADER_SIZE + pixel_array_size);

        uint8_t *bitmap = (uint8_t*)malloc(size_of_bitmap_file);
        uint8_t *bmp_header = createBmpHeader(size_of_bitmap_file);
        uint8_t *bmp_dib_header = createBmpDibHeader(width, height);
        uint8_t *bmp_pixel_array = createPixelArray(_players, width, height);
        bmp_pixel_array = createReversePixelArray(bmp_pixel_array, width, height);
        
        memcpy(bitmap, bmp_header, BMP_HEADER_SIZE);
        memcpy(bitmap + BMP_HEADER_SIZE, bmp_dib_header, BMP_DIB_HEADER_SIZE);
        memcpy(bitmap + BMP_HEADER_SIZE + BMP_DIB_HEADER_SIZE, bmp_pixel_array, pixel_array_size);

        const unsigned int base64_size = getSizeInBase64(size_of_bitmap_file);
        char* base64encoded = base64Encoder(bitmap, size_of_bitmap_file);

        for (size_t i = 0; i < base64_size; i++)
        {
            cout << base64encoded[i];
        }
        
        free(bitmap);
        delete [] bmp_header;
        delete [] bmp_dib_header;
        delete [] bmp_pixel_array;
        delete [] base64encoded;
    }

    cout << endl;
}

uint8_t *createBmpHeader(uint32_t size_of_bitmap_file)
{
    uint8_t *bmp_header = new uint8_t[14];

    bmp_header[0] = 'B';
    bmp_header[1] = 'M';
    uint32_t *bmp_header_uint32 = (uint32_t*)(&(bmp_header[2]));

    bmp_header_uint32[0] = size_of_bitmap_file;
    bmp_header_uint32[1] = 0;
    bmp_header_uint32[2] = BMP_HEADER_SIZE + BMP_DIB_HEADER_SIZE;

    return bmp_header;
}

uint8_t *createBmpDibHeader(const uint16_t width, const uint16_t height)
{
    uint8_t *bmp_header = new uint8_t[12];
    uint32_t *bmp_header_uint32 = (uint32_t *)(&(bmp_header[0]));
    uint16_t *bmp_header_uint16 = (uint16_t *)(&(bmp_header[4]));

    bmp_header_uint32[0] = BMP_DIB_HEADER_SIZE;
    bmp_header_uint16[0] = width;
    bmp_header_uint16[1] = height;
    bmp_header_uint16[2] = 1;
    bmp_header_uint16[3] = BMP_BPP;

    return bmp_header;
}

uint8_t *createPixelArray(Player _player[], const unsigned int width, const unsigned int height)
{
    const unsigned int row_bytes_size = width * BMP_PIXEL_SIZE;
    uint8_t *image = new uint8_t[row_bytes_size * height];

    // set image to white
    for (size_t pos = 0; pos < row_bytes_size * height; pos++)
    {
        *(image + pos) = (uint8_t)255;
    }

    for (size_t player_ID = 0; player_ID < PLAYER_COUNT; player_ID++)
    {
        uint8_t *draw_pos = image;

        if (_player[player_ID].isInactive)
        {
            draw_pos += player_ID * BMP_TOKEN_SIZE * BMP_PIXEL_SIZE;
        }
        else
        {
            draw_pos += (row_bytes_size * _player[player_ID].pos * BMP_TOKEN_SIZE) +
                        (player_ID * BMP_TOKEN_SIZE * BMP_PIXEL_SIZE);
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

    return image;
}

void writeTokenArray(uint8_t *position, const char picture[BMP_TOKEN_SIZE][BMP_TOKEN_SIZE])
{
    for (unsigned int row = 0; row < BMP_TOKEN_SIZE; row++)
    {
        uint8_t *current_pos = position + (BMP_ROW_SIZE * row);

        for (unsigned int col = 0; col < BMP_TOKEN_SIZE; col++)
        {
            if (picture[row][col] == 1)
            {
                memcpy(current_pos, black_pixel, BMP_PIXEL_SIZE);
            }
            else
            {
                memcpy(current_pos, white_pixel, BMP_PIXEL_SIZE);
            }

            current_pos += BMP_PIXEL_SIZE;
        }
    }
}

uint8_t *createReversePixelArray(uint8_t *source_image, const unsigned int width, const unsigned int height)
{
    const unsigned int row_bytes_size = width * BMP_PIXEL_SIZE;
    uint8_t *new_image = new uint8_t[row_bytes_size * height];

    for (size_t row = 0; row < height; row++)
    {
        for (size_t col = 0; col < row_bytes_size; col++)
        {
            new_image[(row_bytes_size * row) + col] = source_image[(row_bytes_size * (height - row - 1)) + col];
        }
    }

    free(source_image);

    return new_image;
}