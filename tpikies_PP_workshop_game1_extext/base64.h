#pragma once

#include <cstdint>

const char base64_alphabet[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', '+', '/'
};

char *base64Encoder(const uint8_t *memory_to_encode, const unsigned int memory_size);
char *encodeBytesAsBase64(const uint8_t bytes_to_encode[3], const unsigned int number_of_bytes);
char getCharacterInBase64(const uint8_t character);
unsigned int getSizeInBase64(const int numberOfBytes);