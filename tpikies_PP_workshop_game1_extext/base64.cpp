#include "base64.h"

#include <stdlib.h>
#include <algorithm>

using namespace std;

char *base64Encoder(const uint8_t *memory_to_encode, const unsigned int memory_size)
{
    unsigned int base64_lenght = getSizeInBase64(memory_size);
    char *base64_encoded = new char[base64_lenght];
    unsigned int read_offset = 0;

    for (size_t base64_pos = 0; base64_pos < base64_lenght; base64_pos += 4)
    {
        uint8_t octets[3] = {0, 0, 0};

        for (size_t i = 0; i < 3 && i + read_offset < memory_size; i++)
        {
            octets[i] = *(memory_to_encode + read_offset + i);
        }

        char *encoded_bytes = encodeBytesAsBase64(octets, min((unsigned int)4, memory_size - read_offset));

        for (size_t i = 0; i < 4; i++)
        {
            base64_encoded[base64_pos + i] = encoded_bytes[i];
        }

        delete [] encoded_bytes;

        read_offset += 3;
    }

    return base64_encoded;
}

char *encodeBytesAsBase64(const uint8_t bytes_to_encode[3], const unsigned int number_of_bytes)
{
    char *encoded_values = new char[4];
    uint8_t sextets[4];

    sextets[0] = bytes_to_encode[0] >> 2;
    sextets[1] = ((bytes_to_encode[0] & 0b00000011) << 4) | (bytes_to_encode[1] >> 4);
    sextets[2] = ((bytes_to_encode[1] & 0b00001111) << 2) | (bytes_to_encode[2] >> 6);
    sextets[3] = ((bytes_to_encode[2] & 0b00111111));

    for (size_t i = 0; i < 4; i++)
    {
        encoded_values[i] = getCharacterInBase64(sextets[i]);
    }

    if (number_of_bytes < 3)
    {
        encoded_values[3] = '=';
    }
    if (number_of_bytes < 2)
    {
        encoded_values[2] = '=';
    }

    return encoded_values;
}

char getCharacterInBase64(const uint8_t character)
{
    if (character < 26)
    {   // Uppercase letter
        return ('A' + character);
    }
    else if (character < 52)
    {   // Lowercase letter
        return ('a' + character - 26);
    }
    else
    {   // Rest
        return base64_alphabet[character - 52];
    }
}

unsigned int getSizeInBase64(const int numberOfBytes)
{
    unsigned int padding = numberOfBytes % 6;
    return (numberOfBytes * 4 / 3) + padding;
}
