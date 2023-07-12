#include <stdio.h>

int main() {

    printf("hello world""\n"
           "hello jack""\n");

    printf("long time no see\n"\
           "long time no see\n");


    //  \后边的空格会保留，但是换行符会省略
    char content[] = "first line\n\
                      second line\n";

    printf("%s", content);

    return 0;
}