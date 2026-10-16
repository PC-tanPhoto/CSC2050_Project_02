#define _GNU_SOURCE // these declirations will allow us to use the libraies we need for printf, stdin, getline, strcmp 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int uniq(FILE *fp); // a prototype was for "uniq" whos input will be a file pointer, either from a text file or stdin, in this function is where we will replicate the functionality of the uniq command
int main (int argc, char *argv[]) // we are taking in command line arguments 
{
	FILE *fp; // creating a file pointer for the file that the user will provide
	if (argc==1) // if the user did not provide a file, their input will come in from the stdin, aka the keyboard
	{
		printf ("Type your input and use cntrl+D to finish\n");
		uniq(stdin); // keyboard input will be sent into our uniqu function
        	return 0;
	}
	else // this is for if the user did provide some file, or if they at least typed something and not just the program name
	{
		fp =fopen(argv[1],"r"); // we are opening the file and storing its memory address in fp, argv[1]
					// is the index in which the file should be in and "r" is just fopen reading it

		if(fp==NULL)  // check to see if you were able to open the file,
		{	

			perror("Could not open the File"); // error checking and exiting if there is an issue with the
							   // file
			return EXIT_FAILURE;
		}	
		uniq(fp); // if there was no error and we are able to open the file, we will "feed" that file into our
			  // unique function 
		return 0;
	}
}
int uniq(FILE *fp) // this is our function that will replicate the functionality of uniq
{					

					// this is the buffer that will have our "new input" that we will be comparing"
					// aka current buffer
	size_t cbuffsize=0; // this is space that was allocated by the buffer and will be larger than what we actually
			    // need it will typically allocate 120 bytes
	char *cbuffer=NULL; // this buffer will hold our most recent string that we obtained via getline
	ssize_t c_elements_read=0; // this is how many elements we were able to fetch via getline, if it was -1 
				   // then we hit EOF


					// this buffer will hold the "old input" that we copied over from "new input"
					// aka previous buffer
	size_t pbuffsize=0;
	char *pbuffer=NULL; // buffer 2 for line "2"
	ssize_t p_elements_read=0;

	p_elements_read = getline(&pbuffer,&pbuffsize,fp);

        if(p_elements_read==-1) // make sure that there was no error with the "first line"
        {
                printf("Error reading the line");
                return 1;
        }

        printf("%s",pbuffer);

        while (c_elements_read!=-1)
        {
        	free(cbuffer);
                cbuffer = NULL;
                cbuffsize = 0;
                c_elements_read = 0;
        	c_elements_read = getline(&cbuffer,&cbuffsize,fp);
        	if(c_elements_read!=-1) 
		{
                	if (strcmp(cbuffer,pbuffer)!=0)
                	{
                        	printf("%s",cbuffer);
                        	free(pbuffer);
                        	pbuffer = cbuffer;
                        	pbuffsize = 0;
                        	p_elements_read = 0;
                        	cbuffer=NULL;
                        	cbuffsize=0;
                        	c_elements_read=0;
			}
		}
	}
		free(cbuffer);
                free(pbuffer);
                fclose(fp);
}
