#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"


int cmpf(const void *term1, const void *term2){
    return strcmp(((struct term *)term1)->term, ((struct term *)term2)->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    char line[200];
    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    int N = atoi(line);
    *terms = (struct term *)malloc(sizeof(struct term) * (N+1));
    *pnterms = N;
    int i;
    for(i = 0; i < N; i++){
        fgets(line, sizeof(line), fp);
        line[strlen(line)-1] = '\0';
        (*terms+i)->weight = atof(strtok(line, "	"));
        strcpy((*terms+i)->term, strtok(NULL, "	"));
    }
    qsort(*terms, N, sizeof(struct term), cmpf);
    fclose(fp);
}

// The function takes in a pointer to a pointer to struct term, a pointer to an int, and the name of a file that is formatted like cities.txt.

// The function allocates memory for all the terms in the file and stores a pointer to the block in *terms.
// The function stores the number of terms in *pnterms.
// The function reads in all the terms from filename, and places them in the block pointed to by *terms.

// The terms should be sorted in lexicographic order.

int lowest_match(struct term *terms, int nterms, char *substr){
    int start = 0;
    int end = nterms-1;
    int mid;
    int length = 0;
    while(*(substr+length) != '\0'){
        length ++;
    }
    char tempterm[200];
    while(start<=end){
        mid = (int)((start+end)/2);
        strcpy(tempterm, (terms+start)->term);
        tempterm[length] = '\0';
//        printf("low %d, %d, %s, %s\n", start, end, tempterm, substr);
        if(strcmp(tempterm, substr) == 0){
            return start;
        }
        if (start == end){
            return -1;
        }
        strcpy(tempterm, (terms+mid)->term);
        tempterm[length] = '\0';
        if(strcmp(tempterm, substr) < 0){
            start = mid + 1;
        } else{
            end = mid;
        }
    }
    return -1;
}

// The function returns the index in terms of the first term in lexicographic ordering that matches the string substr.

// This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.

// You can assume that terms is sorted in ascending lexicographic ordering.

int highest_match(struct term *terms, int nterms, char *substr){
    int start = 0;
    int end = nterms-1;
    int mid;
    int length = 0;
    while(*(substr+length) != '\0'){
        length++;
    }
    char tempterm[200];
    char temp2[200];
    while(start<=end){
        mid = (int)((start+end)/2);
        //printf("start: %d: %s, mid: %d: %s, end: %d: %s, substr: %s\n", start,(terms+start)->term, mid,(terms+mid)->term, end,(terms+end)->term,substr);
        //566 566 567
        strcpy(tempterm, (terms+end)->term);
        tempterm[length] = '\0';
        if(strcmp(tempterm, substr) == 0){
            return end;
        }
        if (start == end){
            return -1;
        }

        if(start + 1 == end){
            strcpy(temp2, (terms+start)->term);
            temp2[length] = '\0';
            if(strcmp(temp2, substr) == 0){
                return start;
            }else{
                return -1;
            }
        }

        strcpy(tempterm, (terms+mid)->term);
        tempterm[length] = '\0';
        if(strcmp(tempterm, substr) <= 0){
            start = mid;

        } else{
            end = mid - 1;
        }


    }
    return -1;
}


// The function returns the index in terms of the last term in lexicographic order that matches the string substr.

// This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.

// You can assume that terms is sorted in ascending lexicographic ordering.

int cmpf2(const void *term1, const void *term2){
    if (((struct term *)term2)->weight < ((struct term *)term1)->weight){
        return -1;
    } else if (((struct term *)term2)->weight > ((struct term *)term1)->weight){
        return 1;
    }
    return 0;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int low = lowest_match(terms, nterms, substr);
    int high = highest_match(terms, nterms, substr);
    //printf("%d, %d\n",low,high);
    if(low == -1){
        *n_answer = 0;
        return;
    }
    *n_answer = high - low + 1;
    *answer = (struct term *)malloc(sizeof(struct term)*(*n_answer));
    int i;
    for(i = 0; i < *n_answer; i++){
        (*answer+i)->weight = (terms+i+low)->weight;
        //printf("%f\n",(terms+i+low)->weight);
        strcpy((*answer+i)->term,(terms+i+low)->term);
    }
    qsort(*answer, *n_answer, sizeof(struct term), cmpf2);
}

// The function takes terms (assume it is sorted lexicographically), the number of terms nterms, and the query string substr, and places the answers in answer, with *n_answer being the number of answers. The answer should be sorted by weight.

// Credit: the assignment was designed by Kevin Wayne, adapted to C by Michael Guerzhoy, and done by Tabitha Kim
