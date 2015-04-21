/* Conversion between regular decimal integer and Roman digits.
 * C code written by SETI, based on: 
 * http://www.mitbbs.com/article_t/JobHunting/32098547.html
 */

#include <stdio.h>

int getDecimal(char);
int romanToDecimal(char *);
char getRoman(int);
char * decimalToRoman(int, char *);

int main(int argc, char* argv[]){

    printf("Roman: %s\n", argv[1]);

    int d = romanToDecimal(argv[1]);

    printf("Decimal: %d\n", d);

    char r[1000];

    decimalToRoman(d, r);

    printf("Roman: %s\n", r);

}

int getDecimal(char a){

    switch(a){
        
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;

    }

    return 0;

}

int romanToDecimal(char * r){

    int d1 = getDecimal(*r), d2 = getDecimal(*++r), d = 0;

    while(1){

        if(d1 >= d2){
            d += d1;
        }
        else{
            d -= d1;
        }

        if(d2 == 0){
            break;
        }

        d1 = d2;
        d2 = getDecimal(*++r);

    }

    return d;

}

char getRoman(int d){

    switch(d){
        
    case 1:
        return 'I';
    case 5:
        return 'V';
    case 10:
        return 'X';
    case 50:
        return 'L';
    case 100:
        return 'C';
    case 500:
        return 'D';
    case 1000:
        return 'M';

    }

    return '\0';

}

char * digitToRoman(int digit, int base, char * r){

    if(digit <= 3){
        while(digit > 0){*r++ = getRoman(base); digit--;}
    }
    else if(digit == 4){
        *r++ = getRoman(base);
        *r++ = getRoman(5 * base);
    }
    else if(digit == 5){
        *r++ = getRoman(5 * base);
    }
    else if(digit <= 8){
        *r++ = getRoman(5 * base);
        digit -= 5;
        while(digit > 0){*r++ = getRoman(base); digit--;}
    }
    else if(digit == 9){
        *r++ = getRoman(base);
        *r++ = getRoman(10 * base);
    }

    return r;

}

char * decimalToRoman(int d, char * r){

    int digit = d / 1000;
    d %= 1000;

    while(digit > 0){
        *r++ = getRoman(1000);
        digit--;
    }

    digit = d / 100;
    d %= 100;

    r = digitToRoman(digit, 100, r);
        
    digit = d / 10;
    d %= 10;

    r = digitToRoman(digit, 10, r);

    r = digitToRoman(d, 1, r);

    *r = '\0';

    return r;

}
