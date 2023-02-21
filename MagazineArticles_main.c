/*
 * Eric Gallager
 *
 * Assignment:
 *
 * Here I want you to be able to read a file which has titles of magazine
 * articles and the page number they occur on in it.
 * I want you to ask the user for a page number, and give them the article
 * which appears on that page number.
 *
 * For example.
 *
 *	example.txt
 *	 10 The First Article
 *	 24 The Article After the first article
 *	 33 The Third Article
 *	 40 The Fourth Article
 *	 54 The Last Article
 *
 *	program
 *	 >> Enter a page number
 *	 24
 *	 >> "The Article After the first article" starts on that page number
 *
 *	program
 *	 >> Enter a page number
 *	 65
 *	 >> No Article starts on that page number
 *
 * ---
 *
 * Algorithm:
 *
 *	1. Make a struct for magazine contents with page number and article
 *	   title
 *	2. Make functions to go with this struct (scan, print, compare, etc.)
 *	3. Ask user for input
 *	4. Compare user input against the "page number" part of the magazine
 *	   contents struct
 *	5. Return an appropriate result
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // I'm probably going to need the strcmp() function

#define STRING_MAX_LENGTH 100
#define MAX_ARTICLES 21 // hardcoded because that's easier

typedef struct {
    int page_number[4];
    char title[STRING_MAX_LENGTH];
    int extra_variable;
} article_t;

typedef struct {
    int first_digit;
    int second_digit;
    double two_digit_number;
} two_digit_number_t;

/*
 * scan_contents(): looks in a file and puts contents into the article_t type
 * struct thing, then returns it
 */
article_t scan_contents(FILE*infile1, FILE*infile2, int i); // prototype
article_t scan_contents(FILE*infile1, FILE*infile2, int i) {
    int j = 0;
    j = i;
    // printf("\n j = %i \n", j); // statement for debugging
    article_t article[j];
    // int k = 0; // loop-counter
    int l = 0; // loop-counter
    if (j <= 11) {
        fscanf((FILE*)infile1, "%i%i", &article[j].page_number[0], &article[j].page_number[1]);
        article[j].page_number[2] = ((article[j].page_number[0] * 10) + article[j].page_number[1]); // convert 2 1-digit numbers into a 2-digit number
        if ((article[j].page_number[0] != EOF) && (article[j].page_number[0] != '\0')) {
            fscanf((FILE*)infile1, "%s", article[j].title);
            // printf("\n k = %i \n", k); // statement for debugging
        }
    } else if ((j > 11) && (j <= 20)) {
        fscanf((FILE*)infile2, "%i%i", &article[j].page_number[0], &article[j].page_number[1]);
        article[j].page_number[2] = ((article[j].page_number[0] * 10) + article[j].page_number[1]); // convert 2 1-digit numbers into a 2-digit number
        if ((article[j].page_number[0] != EOF) && (article[j].page_number[0] != '\0')) {
            fscanf((FILE*)infile2, "%s", article[j].title);
            // printf("\n k = %i \n", k); // statement for debugging
        }
    } else {
        for (l = 0; l < 4; l++) {
            article[j].page_number[l] = 0;
        }
        // article[j].title = "\n Error! \n";
    }
    return(article[j]);
}

/*
 * get_article(): checks to see if there is an article for that page number
 * Numbers returned:
 * 0 => no match (default)
 * 1 => match
 */
int get_article(double page_number, article_t article, int i); // prototype
int get_article(double page_number, article_t article, int i) {
    int listed = 0; // flag
    if (page_number == article.page_number[2]) {
        listed++; // increment flag to show truth
    }
    if (listed >= 1) {
        article.extra_variable = i; // this is just superfluous for now, but it could be used as a hook for something useful later on.
    }
    return(listed);
}

/*
 * Main function
 */
int main (int argc, const char * argv[]) {
    FILE *infile1;
    infile1 = fopen("MagazineContents.txt", "r");
    if (infile1 == NULL) { // check for existence of input file
        printf("\n Cannot open MagazineContents.txt for input, make sure this file exists. \n");
    } else {
        printf("\n MagazineContents.txt is good to go. \n");
    }
    FILE *infile2;
    infile2 = fopen("MagazineContents2.txt", "r");
    if (infile2 == NULL) { // check for existence of input file
        printf("\n Cannot open MagazineContents2.txt for input, make sure this file exists. \n");
    } else {
        printf("\n MagazineContents2.txt is good to go. \n");
    }
    two_digit_number_t selected_page_number;
    selected_page_number.first_digit = 0;
    selected_page_number.second_digit = 0;
    selected_page_number.two_digit_number = 0;
    int answer = 0;
    printf("\n Message for security and/or debugging: \n This program's path is %s and it is running with %i argument(s). \n", argv[0], argc); // Statement for debugging
    printf("\n Enter a page number (2 digits, with a leading 0 for 1-digit numbers, and a space between digits. For example, 8 would be \"0 8\")> ");
    scanf("%i%i", &selected_page_number.first_digit, &selected_page_number.second_digit); // get input
#ifdef DEBUG_MA
    printf("\n %i %i \n", selected_page_number.first_digit, selected_page_number.second_digit); // statement for debugging
#endif /* DEBUG_MA */
    selected_page_number.two_digit_number = ((selected_page_number.first_digit * 10) + selected_page_number.second_digit); // convert 2 1-digit numbers into a 2-digit number
#ifdef DEBUG_MA
    printf("\n selected_page_number = %.0f \n",
    	   selected_page_number.two_digit_number); // statement for debugging
#endif /* DEBUG_MA */
    article_t article[MAX_ARTICLES];
    int i = 0; // initialize loop-counter
    for (i = 1; i < MAX_ARTICLES; i++) { // goes through array for holding articles in
        if (article[i].page_number[0] != EOF) {
            article[i] = scan_contents(infile1, infile2, i);
        }
    }
    i--;
    int flag = 0; // set if we find something
    for (i = 1; i < MAX_ARTICLES; i++) { // go through array again, this time looking at what got put in in the previous loop
        answer = get_article(selected_page_number.two_digit_number, article[i], i);
#ifdef DEBUG_MA
        printf("\n Match? %i \n", answer); // statement for debugging
#endif /* DEBUG_MA */
        if (answer >= 1) {
            printf("\n Article %s starts on page %.0f. \n", *article[i].title,
                   selected_page_number.two_digit_number);
            flag++;
        }
        answer = 0; // reset
    }
    if (flag == 0) { // should have stayed unincremented if nothing was found
        printf("\n No article begins on page %.0f. \n",
               selected_page_number.two_digit_number);
    }
    fclose(infile1); // finish up cleanly
    fclose(infile2); // finish up cleanly
    return 0;
}

// newline \n
