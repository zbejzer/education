#pragma once

#include <cstdint>

const char base64_alphabet[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', '+', '/'
};

char *base64Encoder(const uint8_t *first_byte, const int numberOfBytesToBeEncoded);
char *encodeBytesAsBase64(const uint8_t octets[3]);
char getCharacterInBase64(const uint8_t character);
unsigned int getSizeInBase64(const int numberOfBytes);