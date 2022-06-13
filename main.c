#include <stdio.h>
#include <stdint.h>

#include "base64.h"


const char orig_text[] = "This is a simple example of text that will be encoded with base64 and \
then decoded back. The \"base64_buffer_encode\" and \"base64_buffer_decode\" functions do not set \
the null terminator character at the end of the string, because keep this in mind.";

char encoded_text_buf[500];
char decoded_text_buf[500];

int main(int argc, char** argv)
{
	printf("\nOriginal text:\n\n%s\n", orig_text);

	size_t encoded_text_lenght = base64_buffer_encode(orig_text, sizeof(orig_text), encoded_text_buf);

	printf("\n\nEncoded text:\n\n");
	

	for (size_t i = 0; i < encoded_text_lenght; i++)
	{
		printf("%c", encoded_text_buf[i]);
	}

	size_t decoded_text_lenght = base64_buffer_decode(encoded_text_buf, encoded_text_lenght, decoded_text_buf);


	printf("\n\nDecoded text:\n\n");

	for (size_t i = 0; i < decoded_text_lenght; i++)
	{
		printf("%c", decoded_text_buf[i]);
	}

	printf("\n\n");
	
	return 0;
}