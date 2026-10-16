#include <stdio.h> //standard input library 

void word_count(FILE *fp,int *lc,int *wc,int *cc); //prototype for our function where we will take the  arguments of the File we want to use, we will also point to our int values in main, which we
						   //want to keep track of as counters. 
int main(int argc, char *argv[]) // We are taking command line arguments 
{
	int nline=0; // line counter
	int wcount=0;// word counter 
	int ccount=0;// character count
	FILE *fp; // delaring our file pointer
	if (argc==1) // if the user does not include a text file we go down this path, in this path we use the keyboard as our input, we also include a message letting the user know what to do and how to end 
	{
		printf("Use Enter for new line, when you are finished typing what you would like use cntrl + D\n");
		fp= stdin; // the file pointer is assigned to the keyboard
	 word_count(fp,&nline,&wcount,&ccount); // the word counter function where we will count line, word count, and character count.

	}
	else // if the user attempted to inlcude a file we will go down this path, the input in this path comes from a file that the user included
	{     
	fp=fopen(argv[1],"r"); // We are opening the file, we are reading from it ("r") and are assigning our file pointer to index 1 of argv which holds our file 
		if(fp==NULL) // if we are unable to open the file, then fp gets assigned the value NULL, we also let the user know we couldn't open it and exit out of the program.
	{
	printf("Could not open file for reading\n");
	return 0;
	}
	else // if we are able to open the file, we let the user know and then we use the function word_count which takes our file pointer and giving the memory address of our counter values 
	{	

	printf("was able to open\n");
	} 
	word_count(fp,&nline,&wcount,&ccount);

fclose(fp); // close the file, this is not needed in the first path since you only need to use fclose if you used fopen, it's not needed for stdin
	}
printf("Word Count: %d\n",wcount); // print out how many words were counted
printf("line count: %d\n",nline); // print out how many lines were counted
printf("character count: %d\n",ccount); // print out how many characters were counted
return 0; // exit out of the program
}
void  word_count(FILE * fp,int *lc,int *wc,int *cc) { // our word count function which will not return any values, but since we do want to make changes to our main, we are using pointers
        int boo=1; // we are initiallizing boo to act as condition checker, we set it as 1 to check to see if we have any space, we are assuming that there is a space and we start counting 
		   // "words" if we transition from a "space" to "nonspace", which is how we are able to check if "

        int ch= fgetc(fp); //initialize our  ch, we are getting the very first character from the user input
                while (ch !=EOF) // the loop will keep going until we hit EOF,if the user input  
                {
                        if(ch=='\n') //  check to see if the current character is new line
                        {
                        (*lc)++; //our pointer is being derefrenced and is modifying the lcount in main
                        }
                        if(ch==' '|| ch=='\n' || ch=='\t') // we are checking for white space, how ever our white space is not limited to just " " since we can also get " " from new line and tab
							   // our goal is to look for the switch from white space to a nonwhite space, in order to identify when a word starts, new line and tabs are not 
							   // words but words can start after then, we we are looking for those conditions
                        {
                        boo=1; // we set 
                        }
                        else // if the current character is not white space, new line, or tab, then it must be a character, it goes down this path where will check to see if it was previously a white space
			     //
                        {
                                if(boo==1) // the current character is a non white space, if it was previoulsy a white space, we have found a word, if the current character is a non white space and if
					   // it was previuolsy a non white space, boo will still have a value of 0 so it will not count as a new word
                                {
                                (*wc)++; // our pointer is being derefrenced and is modiffying the wcount in main
                                boo=0; // 
                                }
                        }
                (*cc)++; // our pointer is being derefrenced and is modiffyring the ccount in main
                ch =fgetc(fp); // assign the next character
                }
}
