# base64C
Implementation of base64 encoding and decoding functions for data arrays and files in C

___

The base64.h file contains function prototypes that allow you to encode and decode data using base64. Data can be represented as an array (buffer), or as a file.

___

1. Function for encoding of an array (data buffer)

```
size_t base64_buffer_encode(
    const void* input_data_buffer,
    size_t input_data_buffer_size,
    char* output_base64_buffer
);
```
Accepted parameters:
>_const void* input_data_buffer_ - pointer to a buffer with data to encode.
>
>_size_t input_data_buffer_size_ - buffer size in bytes with data to encode.
>
>_char* output_base64_buffer_ - pointer to a buffer for encoded data.

The return value is the number of bytes of encoded data in the _output_base64_buffer_ buffer.


___

2. Function for decoding of an array (data buffer)

```
size_t base64_buffer_decode(
    const char* input_base64_buffer,
    size_t input_base64_buffer_size,
    void* output_data_buffer
);
```
Accepted parameters:
>_const char* input_base64_buffer_ - pointer to a buffer with data to decode.
>
>_size_t input_base64_buffer_size_ - buffer size in bytes with data to dencode.
>
>_void* output_data_buffer_ - pointer to a buffer for decoded data.

The return value is the number of bytes of decoded data in the _output_data_buffer_ buffer.


___

3. Function for encoding of a file

```
void base64_file_encode(FILE* fin, FILE* fout);
```
Accepted parameters:
>_FILE* fin_ - pointer to the file descriptor with the data to encode.
>
>_FILE* fout_ - pointer to the file descriptor where the encoded data will be placed.

There are no return values.

___

4. Function for decoding of a file

```
void base64_file_decode(FILE* fin, FILE* fout);
```
Accepted parameters:
>_FILE* fin_ - pointer to the file descriptor with the data to deencode.
>
>_FILE* fout_ - pointer to the file descriptor where the decoded data will be placed.

There are no return values.

___
___
The base64_demo.c file provides an example of encoding and decoding a string using the base64_buffer_encode and base64_buffer_decode functions:

```
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

	size_t encoded_text_lenght =
            base64_buffer_encode(orig_text, sizeof(orig_text), encoded_text_buf);

	printf("\n\nEncoded text:\n\n");
	

	for (size_t i = 0; i < encoded_text_lenght; i++)
	{
		printf("%c", encoded_text_buf[i]);
	}

	size_t decoded_text_lenght =
            base64_buffer_decode(encoded_text_buf, encoded_text_lenght, decoded_text_buf);


	printf("\n\nDecoded text:\n\n");

	for (size_t i = 0; i < decoded_text_lenght; i++)
	{
		printf("%c", decoded_text_buf[i]);
	}

	printf("\n\n");
	
	return 0;
}
```

___

## License

*MIT License*

*Copyright (c) 2021 Denis Chicherov*

*Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.*

*_THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE._*
