/*
 * Name: 		Noah Mutersbaugh
 * Due Date: 	10/01/2020
 * Description: This program compares difficulty of documents based on their
 * average word length and then returns the most and least difficult file
 * names.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char filenamesMaxMin[2][50];
	int maxAvg, minAvg;
	int* avgWordSize = (int*)malloc((argc-1)*sizeof(int));

	if(argc>1){
	for(int i=1; i<argc; i++){
		FILE *fp;
		char c;
		int total=0, numWords=0, wordSize=0;

		fp = fopen(argv[i], "r");

		if(fp == NULL){
			printf("Can't open this file.\n");
			exit(0);
		}

		// Count words to determine size of wordCounter array
		c = fgetc(fp);
		while(c != EOF) {
			//printf("%c", c);
			c = fgetc(fp);
			if(isspace(c)) {
				numWords++;
			}
		}
		
		//printf("\nnumWords: %d\n", numWords);
		int* wordCounter = (int*)malloc(numWords*sizeof(int));
		numWords = 0;
		fseek(fp, 0, SEEK_SET);

		// Count and record size of each word
		c = fgetc(fp);
		while(c != EOF){
			//printf("%c", c);
			c = fgetc(fp);
			wordSize++;
			if(isspace(c)) {
				//printf("\nwordSize: %d", wordSize);
				wordCounter[numWords] = wordSize;
				numWords++;
				wordSize=0;
			}
		}
		
		fclose(fp);

		for(int n=0; n<numWords; n++) {
			total = total + wordCounter[n];
		}
		avgWordSize[i] = total/numWords;
		if(i==1){
			maxAvg = avgWordSize[i];
			minAvg = avgWordSize[i];
			strcpy(filenamesMaxMin[0], argv[i]);
			strcpy(filenamesMaxMin[1], argv[i]);
		} else {
			if(avgWordSize[i] > maxAvg) {
				maxAvg = avgWordSize[i];
				strcpy(filenamesMaxMin[0], argv[i]);
			}
			if(avgWordSize[i] < minAvg) {
				minAvg = avgWordSize[i];
				strcpy(filenamesMaxMin[1], argv[i]);
			}
		}
		free(wordCounter);
	}
	}else{
		printf("No argument passed.");
		exit(0);
	}

	printf("\nMost difficult document: %s", filenamesMaxMin[0]);
	printf("\nLeast difficult document: %s\n", filenamesMaxMin[1]);

	free(avgWordSize);

	return 0;
}


