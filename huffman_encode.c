#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>


void encode(char *infile, char *outfile)
{
	char *HUFF_LUT[26] = { "1010", "011110", "10111", "1110", "010", "011111", "11010",
				    "00010", "0110", "111110000", "111111", "10110","11011", "0000", 
				    "11110", "0111001", "11111000101", "1001", "1000", "1100", "00011",
				    "1111101", "011101", "11111000100", "1111100011", "0111000" };
				    
	char symbol_to_encode;
	FILE *in = fopen(infile, "r");
	FILE *out = fopen (outfile , "w");
	char buffer[11];
    short int huff_let;

    if (in == NULL)
    {
    	printf("File cannot be opened %s\n", infile);
    	abort();
    }
		
	//Using fseek to place pointer at the begining of the file 
	fseek ( out , 0 , SEEK_SET );
	while (1) 
	{
		huff_let = fgetc(in);
		huff_let = tolower(huff_let);
		if (huff_let == EOF)
			break;
		else
		{
			 /* this if statement is used find the huffman value for space since my Huff_lut does not accomodate it
       */
			 if (huff_let == 32)
			 {
			 	fwrite ("001",1,3,out);
			 }
			 else if (huff_let == 225)
			 {
			 	fwrite ("11111001",1,8,out);
			 }
			 else
			 {	
			 	
			 	if ((huff_let > 96) & (huff_let < 123))
			 	{	 
					fwrite (HUFF_LUT[(short int)huff_let-97],1,strlen(HUFF_LUT[(short int)huff_let-97]),out);
				}
			 }
			 //Write the buffer to the file
		}
	}
	printf("Encode is complete\n");
    fclose(in);
    fclose (out);
    
}

void decode (char *infile, char *outfile)
{
	char *HUFF_LUT[26] = { "1010", "011110", "10111", "1110", "010", "011111", "11010",
				    "00010", "0110", "111110000", "111111", "10110","11011", "0000", 
				    "11110", "0111001", "11111000101", "1001", "1000", "1100", "00011",
				    "1111101", "011101", "11111000100", "1111100011", "0111000" };
	char REV_HUFF_LUT[26] = { 'a' , 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
   						   'n', 'o', 'p' , 'q', 'r' , 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char symbol_to_encode;
	FILE *in = fopen(infile, "r");
	FILE *out = fopen (outfile , "w");
	short int size_of_buffer;
    short int huff_let;
    short int i;
    short int j;

    if (in == NULL)
    {
    	printf("Cannot open %s\n", infile);
        abort();
    }
		
	//set the pointer to the begining of file	
	fseek ( out , 0 , SEEK_SET );
	
	i = 1;
	j = 0;
	char buffer[11];
	
	while ((huff_let = fgetc(in)) != EOF) 
	{
       	
       	switch (i)
       	{
       	case 4:
   			if (strncmp(buffer, "001", 3) == 0)
   			{
   				fputc(32, out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[4], 3) == 0)
   			{
   				fputc(REV_HUFF_LUT[4], out);
   				i = 1;
   				break;
   			}
       	break;
       	case 5:
   			if (strncmp(buffer, HUFF_LUT[13], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[13], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[8], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[8], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[18], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[18], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[17], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[17], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[0], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[0], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[19], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[19], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[3], 4) == 0)
   			{
   				fputc(REV_HUFF_LUT[3], out);
   				i = 1;
   				break;
   			}
       	break;
       	case 6:
   			if (strncmp(buffer, HUFF_LUT[7], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[7], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[20], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[20], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[11], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[11], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[2], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[2], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[6], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[6], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[12], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[12], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[14], 5) == 0)
   			{
   				fputc(REV_HUFF_LUT[14], out);
   				i = 1;
   				break;
   			}
       	break;
       	case 7:
   			if (strncmp(buffer, HUFF_LUT[22], 6) == 0)
   			{
   				fputc(REV_HUFF_LUT[22], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[1], 6) == 0)
   			{
   				fputc(REV_HUFF_LUT[1], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[5], 6) == 0)
   			{
   				fputc(REV_HUFF_LUT[5], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[10], 6) == 0)
   			{
   				fputc(REV_HUFF_LUT[10], out);
   				i = 1;
   				break;
   			}
       	break;
       	case 8:
   			if (strncmp(buffer, HUFF_LUT[25], 7) == 0)
   			{
   				fputc(REV_HUFF_LUT[25], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[15], 7) == 0)
   			{
   				fputc(REV_HUFF_LUT[15], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[21], 7) == 0)
   			{
   				fputc(REV_HUFF_LUT[21], out);
   				i = 1;
   				break;
   			}
       	break;
       	case 9:
       		if (strncmp(buffer, "11111001", 8) == 0)
   			{
   				fputc(225, out);
   				i = 1;
   				break;
   			}
       	break;
       	case 10:
       		if (strncmp(buffer, HUFF_LUT[9] , 9) == 0)
   			{
   				fputc(REV_HUFF_LUT[9], out);
   				i = 1;
   				break;
   			}
   		break;
       	case 11:
       		if (strncmp(buffer, HUFF_LUT[24] , 10) == 0)
   			{
   				fputc(REV_HUFF_LUT[24], out);
   				i = 1;
   				break;
   			}
   		break;
        case 12:
        	if (strncmp(buffer, HUFF_LUT[23] , 11) == 0)
   			{
   				fputc(REV_HUFF_LUT[23], out);
   				i = 1;
   				break;
   			}
   			if (strncmp(buffer, HUFF_LUT[16] , 11) == 0)
   			{
   				fputc(REV_HUFF_LUT[16], out);
   				i = 1;
   				break;
   			}
        break;
        }
		        
		buffer[i-1] = huff_let;
		i++;

    }
    printf("Decompression is complete!\n");
    fclose(in);
    fclose (out);
    
}

