#include "base64.h"

#include <stdlib.h>

char *base64Encoder(const uint8_t *first_byte, const int numberOfBytesToBeEncoded)
{
    char *base64_encoded = new char[getSizeInBase64(numberOfBytesToBeEncoded)];

    for (size_t read_offset = 0; read_offset < numberOfBytesToBeEncoded; read_offset += 3)
    {
        uint8_t octets[3] = {0, 0, 0};

        for (size_t current_byte = 0;
            current_byte < 3 && read_offset + current_byte < numberOfBytesToBeEncoded;
            current_byte++)
        {
            octets[current_byte] = *(first_byte + read_offset + current_byte);
        }

        char *encoded_bytes = encodeBytesAsBase64(octets);

        for (size_t i = 0; i < 4; i++)
        {
            base64_encoded[((read_offset / 3) * 4) + i] = encoded_bytes[i];
        }

        free(encoded_bytes);
    }

    return base64_encoded;
}

char *encodeBytesAsBase64(const uint8_t octets[3])
{
    char *encoded_values = new char[4];
    uint8_t sextets[4];

    sextets[0] = octets[0] >> 2;
    sextets[1] = ((octets[0] & 0b00000011) << 4) | (octets[1] >> 4);
    sextets[2] = ((octets[1] & 0b00001111) << 2) | (octets[2] >> 6);
    sextets[3] = ((octets[2] & 0b00111111));

    for (size_t i = 0; i < 4; i++)
    {
        encoded_values[i] = getCharacterInBase64(sextets[i]);
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
    return ((numberOfBytes * 4) + 2) / 3;
}
