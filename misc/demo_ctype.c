#include <ctype.h>
#include <stdio.h>
/* <ctype.h>中的API用法
   isalnum(int c)
   isalpha(int c)
   iscntrl(int c)
   isdigit(int c)
   isgraph(int c)
   islower(int c)
   isupper(int c)
   isprint(int c)
   isspace(int c)
   ispunct(int c)
   isxdigit(int c)
   tolower(int c)
   toupper(int c)
*/
int main(int argc, char* argv[]){
    for(int i = 1; i < argc; i++){
        int dest = (int)*argv[i];
        printf("%c---------\n", dest);
        if(isalnum(dest)){
            printf("is a number or an alpha\n");
        }
        if(isalpha(dest)){
            printf("is an alpha\n");
        }
        if(iscntrl(dest)){
            printf("is a control character\n");
        }
        if(isdigit(dest)){
            printf("is a number\n");
        }
        if(isgraph(dest)){
            printf("is a character could be graphed\n");
        }
        if(islower(dest)){
            printf("is a lower character\n");
            int p = toupper(dest);
            printf("after upper operation:%c\n", p);
        }
        if(isupper(dest)){
            printf("is a upper character\n");
            int p = tolower(dest);
            printf("after lower operation:%c\n", p);
        }
        if(isprint(dest)){
            printf("is a character could be printed\n");
        }
        if(isspace(dest)){
            printf("is a space character\n");
        }
        if(ispunct(dest)){
            printf("is a punct character\n");
        }
        if(isxdigit(dest)){
            printf("is a Ox number character\n");
        }
        printf("------------\n\n");
    }
    return 0;
}