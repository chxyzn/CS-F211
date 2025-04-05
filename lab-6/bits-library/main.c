#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book
{
    char date[30];
    char biblio_number[30];
    char barcode[30];
    char author[60];
    char title[60];
    char edition[60];
    char publisher_code[60];
    char place[60];
    char copyright_date[30];
    char isbn[30];
    char call_number[30];
    char itype[30];
    char on_loan[30];
} book;

typedef struct vec
{
    book *books;
    int size;
} vec;

void print_empty_fields(book b);
book book_from_properties(char *fields[]);
void print_book(const book *b);

int main()
{
    FILE *f = fopen("data.csv", "r");
    int x = fscanf(f, "%*[^\n]\n");

    char buffer[1000];
    char *properties[13];
    int k = 1;
    while (k && fgets(buffer, 1000, f) != NULL)
    {
        k--;
        char *token = strtok(buffer, ",");
        int i = 0;
        while (token != NULL)
        {
            properties[i] = token;
            i++;

            printf("%d) read token %s\n", i, token);
            if (i == 3 || i == 6)
            {
                token = strtok(NULL, "\"");
            }
            else
            {
                token = strtok(NULL, ",");
            }
        }
        book b = book_from_properties(properties);
        print_book(&b);
    }
}

vec *new_vec()
{
    vec *v = (vec *)malloc(sizeof(vec));
    // v->books = (book *)malloc(sizeof(book) * 100);
    v->size = 0;
    return v;
}

book book_from_properties(char *fields[])
{
    book *b = (book *)malloc(sizeof(book));
    strncpy(b->date, fields[0], 29);
    b->date[29] = '\0';

    strncpy(b->biblio_number, fields[1], 29);
    b->biblio_number[29] = '\0';

    strncpy(b->barcode, fields[2], 29);
    b->barcode[29] = '\0';

    strncpy(b->author, fields[3], 59);
    b->author[59] = '\0';

    strncpy(b->title, fields[4], 59);
    b->title[59] = '\0';

    strncpy(b->edition, fields[5], 59);
    b->edition[59] = '\0';

    strncpy(b->publisher_code, fields[6], 59);
    b->publisher_code[59] = '\0';

    strncpy(b->place, fields[7], 59);
    b->place[59] = '\0';

    strncpy(b->copyright_date, fields[8], 29);
    b->copyright_date[29] = '\0';

    strncpy(b->isbn, fields[9], 29);
    b->isbn[29] = '\0';

    strncpy(b->call_number, fields[10], 29);
    b->call_number[29] = '\0';

    strncpy(b->itype, fields[11], 29);
    b->itype[29] = '\0';

    strncpy(b->on_loan, fields[12], 29);
    b->on_loan[29] = '\0';

    return *b;
}

void print_empty_fields(book b)
{
    if (strlen(b.date) == 0)
        printf("date is empty.\n");
    if (strlen(b.biblio_number) == 0)
        printf("biblio_number is empty.\n");
    if (strlen(b.barcode) == 0)
        printf("barcode is empty.\n");
    if (strlen(b.author) == 0)
        printf("author is empty.\n");
    if (strlen(b.title) == 0)
        printf("title is empty.\n");
    if (strlen(b.edition) == 0)
        printf("edition is empty.\n");
    if (strlen(b.publisher_code) == 0)
        printf("publisher_code is empty.\n");
    if (strlen(b.place) == 0)
        printf("place is empty.\n");
    if (strlen(b.copyright_date) == 0)
        printf("copyright_date is empty.\n");
    if (strlen(b.isbn) == 0)
        printf("isbn is empty.\n");
    if (strlen(b.call_number) == 0)
        printf("call_number is empty.\n");
    if (strlen(b.itype) == 0)
        printf("itype is empty.\n");
    if (strlen(b.on_loan) == 0)
        printf("on_loan is empty.\n");
}

void print_book(const book *b)
{
    if (b == NULL)
    {
        printf("Book is NULL.\n");
        return;
    }

    printf("Date: %s, Biblio: %s, Barcode: %s\n", b->date, b->biblio_number, b->barcode);
    printf("Author: %s, Title: %s, Edition: %s\n", b->author, b->title, b->edition);
    printf("Publisher: %s, Place: %s, Copyright: %s\n", b->publisher_code, b->place, b->copyright_date);
    printf("ISBN: %s, Call: %s, Itype: %s, Loan: %s\n", b->isbn, b->call_number, b->itype, b->on_loan);
}