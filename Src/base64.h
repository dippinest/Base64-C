
#ifndef BASE64_H_
#define BASE64_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>


size_t base64_buffer_encode(const void *input_data_buffer, size_t input_data_buffer_size, char *output_base64_buffer);

size_t base64_buffer_decode(const char *input_base64_buffer, size_t input_base64_buffer_size, void *output_data_buffer);

void base64_file_encode(FILE *fin, FILE *fout);

void base64_file_decode(FILE *fin, FILE *fout);


#endif
