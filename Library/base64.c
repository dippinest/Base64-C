#include "base64.h"

static const char base64_char_array[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t base64_buffer_encode(const void *input_data_buffer, size_t input_data_buffer_size, char *output_base64_buffer)
{
	if (input_data_buffer == NULL || output_base64_buffer == NULL)
	{
		return 0;
	}
	
	char current_6bit_value;

	size_t input_data_buffer_byte_counter = 0, output_base64_buffer_byte_counter = 0;

	while (input_data_buffer_byte_counter < input_data_buffer_size)
	{
		current_6bit_value = ((char*)input_data_buffer)[input_data_buffer_byte_counter] >> 2;
		output_base64_buffer[output_base64_buffer_byte_counter++] = base64_char_array[current_6bit_value];

		current_6bit_value = (((char*)input_data_buffer)[input_data_buffer_byte_counter] << 4) |
			(((char*)input_data_buffer)[input_data_buffer_byte_counter + 1] >> 4);
		current_6bit_value &= 0x3F;

		output_base64_buffer[output_base64_buffer_byte_counter++] = base64_char_array[current_6bit_value];

		if ((input_data_buffer_size - input_data_buffer_byte_counter) < 2)
		{
			output_base64_buffer[output_base64_buffer_byte_counter++] = '=';
			output_base64_buffer[output_base64_buffer_byte_counter++] = '=';

			break;
		}

		if ((input_data_buffer_size - input_data_buffer_byte_counter) < 3)
		{

			current_6bit_value = (((char*)input_data_buffer)[input_data_buffer_byte_counter + 1] << 2) |
				(((char*)input_data_buffer)[input_data_buffer_byte_counter + 2] >> 6);

			current_6bit_value &= 0x3F;

			output_base64_buffer[output_base64_buffer_byte_counter++] = base64_char_array[current_6bit_value];

			output_base64_buffer[output_base64_buffer_byte_counter++] = '=';

			break;
		}

		current_6bit_value = (((char*)input_data_buffer)[input_data_buffer_byte_counter + 1] << 2) |
			(((char*)input_data_buffer)[input_data_buffer_byte_counter + 2] >> 6);

		current_6bit_value &= 0x3F;
		output_base64_buffer[output_base64_buffer_byte_counter++] = base64_char_array[current_6bit_value];

		current_6bit_value = ((char*)input_data_buffer)[input_data_buffer_byte_counter + 2];
		current_6bit_value &= 0x3F;
		output_base64_buffer[output_base64_buffer_byte_counter++] = base64_char_array[current_6bit_value];

		input_data_buffer_byte_counter += 3;
	}

	return output_base64_buffer_byte_counter;
}


size_t base64_buffer_decode(const char *input_base64_buffer, size_t input_base64_buffer_size, void *output_data_buffer)
{
	if (input_data_buffer == NULL || output_base64_buffer == NULL)
	{
		return 0;
	}
	
	size_t input_base64_buffer_byte_counter = 0, output_data_buffer_byte_counter = 0;

	char first_part_of_byte, second_part_of_byte;

	while (input_base64_buffer_byte_counter < input_base64_buffer_size)
	{
		if (input_base64_buffer[input_base64_buffer_byte_counter] == '=')
		{
			break;
		}

		first_part_of_byte = strchr((char*)base64_char_array, input_base64_buffer[input_base64_buffer_byte_counter]) - (char*)base64_char_array;

		if (input_base64_buffer[input_base64_buffer_byte_counter + 1] == '=')
		{
			((char*)output_data_buffer)[output_data_buffer_byte_counter++] = first_part_of_byte << 2;
			break;
		}

		second_part_of_byte = strchr((char*)base64_char_array, input_base64_buffer[input_base64_buffer_byte_counter + 1]) - (char*)base64_char_array;
		((char*)output_data_buffer)[output_data_buffer_byte_counter++] = (first_part_of_byte << 2 | second_part_of_byte >> 4);

		first_part_of_byte = second_part_of_byte;

		if (input_base64_buffer[input_base64_buffer_byte_counter + 2] == '=')
		{
			((char*)output_data_buffer)[output_data_buffer_byte_counter++] = first_part_of_byte << 4;
			break;
		}

		second_part_of_byte = strchr((char*)base64_char_array, input_base64_buffer[input_base64_buffer_byte_counter + 2]) - (char*)base64_char_array;

		((char*)output_data_buffer)[output_data_buffer_byte_counter++] = (first_part_of_byte << 4) | (second_part_of_byte >> 2);

		first_part_of_byte = second_part_of_byte;

		if (input_base64_buffer[input_base64_buffer_byte_counter + 3] == '=')
		{
			((char*)output_data_buffer)[output_data_buffer_byte_counter++] = first_part_of_byte << 6;
			break;
		}

		second_part_of_byte = strchr((char*)base64_char_array, input_base64_buffer[input_base64_buffer_byte_counter + 3]) - (char*)base64_char_array;

		((char*)output_data_buffer)[output_data_buffer_byte_counter++] = (first_part_of_byte << 6) | second_part_of_byte;

		input_base64_buffer_byte_counter += 4;
	}

	return output_data_buffer_byte_counter - 1;
}


int base64_file_encode(FILE *fin, FILE *fout)
{
	if (fin == NULL || fout == NULL)
	{
		return 1;
	}

	uint8_t current_6bit_value;
	uint8_t num_read_symb;

	uint8_t _3bytebuf[3];
	uint8_t _4bytebuf[4];

	while ((num_read_symb = fread(_3bytebuf, 1, 1, fin)) > 0)
	{

		num_read_symb += fread(_3bytebuf + 1, 1, 2, fin);

		current_6bit_value = _3bytebuf[0] >> 2;
		_4bytebuf[0] = base64_char_array[current_6bit_value];


		current_6bit_value = (_3bytebuf[0] << 4) | (_3bytebuf[1] >> 4);
		current_6bit_value &= 0x3F;
		_4bytebuf[1] = base64_char_array[current_6bit_value];


		if (num_read_symb < 2)
		{
			_4bytebuf[2] = '=';
			_4bytebuf[3] = '=';

			fwrite(_4bytebuf, 1, 4, fout);

			break;
		}

		current_6bit_value = (_3bytebuf[1] << 2) | (_3bytebuf[2] >> 6);
		current_6bit_value &= 0x3F;
		_4bytebuf[2] = base64_char_array[current_6bit_value];


		if (num_read_symb < 3)
		{
			_4bytebuf[3] = '=';

			fwrite(_4bytebuf, 1, 4, fout);

			break;
		}


		current_6bit_value = _3bytebuf[2];
		current_6bit_value &= 0x3F;

		_4bytebuf[3] = base64_char_array[current_6bit_value];

		fwrite(_4bytebuf, 1, 4, fout);
	}

	return 0;
}


int base64_file_decode(FILE *fin, FILE *fout)
{
	if (fin == NULL || fout == NULL)
	{
		return 1;
	}
	
	char first_part_of_byte, second_part_of_byte;

	uint8_t _4bytebuf[4];
	uint8_t byte;

	while (fread(_4bytebuf, 1, 1, fin) > 0)
	{
		if (_4bytebuf[0] == '=')
		{
			break;
		}

		fread(_4bytebuf + 1, 1, 3, fin);

		first_part_of_byte = strchr(base64_char_array, _4bytebuf[0]) - base64_char_array;

		if (_4bytebuf[1] == '=')
		{
			break;
		}

		second_part_of_byte = strchr(base64_char_array, _4bytebuf[1]) - base64_char_array;


		byte = (first_part_of_byte << 2 | second_part_of_byte >> 4);
		fwrite(&byte, 1, 1, fout);

		first_part_of_byte = second_part_of_byte;

		if (_4bytebuf[2] == '=')
		{
			break;
		}

		second_part_of_byte = strchr(base64_char_array, _4bytebuf[2]) - base64_char_array;

		byte = (first_part_of_byte << 4) | (second_part_of_byte >> 2);
		fwrite(&byte, 1, 1, fout);

		first_part_of_byte = second_part_of_byte;

		if (_4bytebuf[3] == '=')
		{
			break;
		}

		second_part_of_byte = strchr(base64_char_array, _4bytebuf[3]) - base64_char_array;


		byte = (first_part_of_byte << 6) | second_part_of_byte;
		fwrite(&byte, 1, 1, fout);
	}

	return 0;
}
