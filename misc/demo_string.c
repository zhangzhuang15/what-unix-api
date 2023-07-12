#include <stdio.h>
#include <string.h>
#include <errno.h>

void test_memchr() {
    /* 查询某个字符在字符串中出现的第一次的位置 */
    const char *p = "MacBook Pro 14.1 in 4th of 2021";
    char *t = (char *)memchr(p, 'P', 20);
    printf("t point str: %s\n", t);
}

void test_memcmp() {
    const char *p = "MacBook Pro 14.1 in 4th of 2021";
    const char *t = p + 8;

    /* 比较两个字符串的前3个字节大小 */
    /* MacBook Pro 14.1 in 4th of 2021
       ^       ^
       |       |
       p       t
    */
    int result = memcmp(p, t, 3);
    if (result > 0) printf("p is bigger than t\n");
    else if (result == 0) printf("p is equal with t\n");
    else printf("p is smaller than t\n");
}

void test_memcpy() {
    /* 将t指向的4个字节内容复制到m指向的4个内容中 */
    /* this is what?
            ^
            |
            t
       memcpy 函数第一个参数要传入一个数组名，传指针会报 zsh: bus error
    */
    char m[] = "this is what?";
    char *t = m+6;
    printf("m : '%s'\n", m);
    memcpy(m, t, 5);
    printf("m after cpy : '%s'\n", m);

    /* 如果 t指向的字符串的长度大于m指向的字符串的长度，运行中就会报错，
       因为在memcpy函数实现内部 操作指针m的时候，对越界现象有一定的检测。
       c语言本身不会对越界进行检测，需要程序员自己控制，避免越界的情况。
      */
    // char p[] = "dafadf fdfad ttt  qrq e  fdafdafa";
    // printf("\nbefore next test:\nm: %s\np: %s\n", m, p);
    // memcpy(m, p, strlen(p));
    // printf("after memcpy(m, p, strlen(p)):\n"\
    //        "m: %s\n"\
    //        "p: %s\n", m, p);
}

void test_memmove() {
    char p[] = "MacBook 14.1 M1X";
    const char * src = p;
    const char * dest = p+3;
    printf("p : '%s'\n", p);
    memmove((char*)dest, src, 5);
    printf("p after memmove() : '%s'\n", p);
}

void test_memset() {
    /* 对ct指向的字符串前4个字节内容，使用‘y’填充 */
    char ct[] = "just do it";
    printf("ct : '%s'\n", ct);
    memset(ct, 'y', 4);
    printf("ct after memset() :  '%s'\n", ct);
}

void test_strlen() {
    const char *p = "MacBook Pro 14.1 in 4th of 2021";
    /* 字符串长度, '\0'不计入 */
    printf("p length: %lu \n", strlen(p));
}


void test_strcmp() {
    /* 比较 p 和 t 指向的字符串大小 */
    char *p = "Mojovia";
    char *t = "Big Sur";
    printf("p: %s\nt: %s\n", p, t);
    printf("strcmp(p, t)\n");
    int result = strcmp(p, t);
    if (result > 0) { printf("p > t\n");}
    else if (result == 0) { printf("p == t\n");}
    else { printf("p < t\n");}
}

void test_strncmp() {
    /* 比较 p 、t指向的字符串前3个字节的大小 */
    char *p = "Big Sur";
    char *t = "Monterey";
    printf("p: %s\nt: %s\n", p, t);
    printf("strncmp(p, t, 3)\n");
    int result = strncmp(p, t, 3);
    if (result > 0) { printf("p > t\n");}
    else if (result == 0) { printf("p == t\n");}
    else { printf("p < t\n");}
}

void test_strcpy() {
    /* t指向的字符串复制到p 
       不能写成 char *p =  "Jack welcome to here, are you right?"  !
       这种写法是在静态存储区存储一个字符串常量，并将其地址赋值给p。
       字符串常量是不可以修改的。
       这就会造成strcpy(p, t)发生错误，因为该函数会对p指向的字符串进行修改，
       但是不会对 t指向的字符串常量进行修改，因此 t可以写成指针形式的字符串赋值。

       写成char p[] =  "Jack welcome to here, are you right?"
       则是 在栈空间中开辟连续的存储空间，存入右值中的字符串。
       */
    char p[] = "Jack welcome to here, are you right?";
    char *t = "Mike from China ";
    printf("p: '%s'\nt: '%s'\n", p, t);
    printf("strcpy(p, t)\n");
    strcpy(p, t);
    printf("p: '%s'\n", p);

    char f[] = "Mercy";
    printf("f: '%s'\nt: '%s'\n", f, t);
    printf("strcpy(f, t)\n");
    strcpy(f, t);
    printf("f: %s\n", f);
}

void test_strncpy() {
    /* t 指向的字符串复制到 p中，最多复制5个字节 */
    char p[] = "Jack";
    char *t = "Mike from China";
    printf("p: '%s'\nt: '%s'\n", p, t);
    printf("strncpy(p, t, 5)\n");
    strncpy(p, t, 5);
    printf("p: '%s'\n", p);
}

void test_strtok() {
    /* 使用t指向的字符串对p指向的字符串进行分割，类似于split操作 */
    char *p = "1001-2994-43433-3342-0071";
    char *t = "-";
    printf("p: '%s'\nt: '%s'\n", p, t);
    printf("strtok(p, t)\n");
    char *m = strtok(p, t); /* 获取分割后的第一个字符串 */
    printf("result: '%s'\n", m);
    while(m != NULL) {
        m = strtok(NULL, t); /* 获取后续分割得到的字符串 */
        printf("result: '%s'\n", m);
    }
    printf("p: '%s'\n", p);
    for(int i = 0; i < 26; i++){
        printf("p[%d]: %c\n", i, *(p+i));
    }
}

void test_strstr() {
    /* 查看t指向的字符串 在 p指向的字符串中的指针位置*/
    char *p = "Okey, I agree with you";
    char *t = "with";
    printf("p: '%s'\nt: '%s'\n", p , t);
    printf("strstr(p, t)\n");
    char * result = strstr(p, t);
    printf("result: '%s'\n", result);
}

void test_strspn() {
    /* 遍历p指向的字符串，发现某个字符不在 t指向的字符串中时，返回该字符的索引*/
    char *p = "1234567";
    char *t = "123";
    printf("p: '%s'\nt: '%s'\n", p, t);
    printf("strspn(p, t)\n");
    size_t index = strspn(p, t);
    printf("result: '%lu'\n", index);
}

void test_strcspn() {
    /*遍历p指向的字符串，如果某个字符没在t指向的字符串中出现过，由0开始，累加1，
      p指向的字符串遍历完后，返回最后的累加结果*/
    char *p = "afaarggfdg";
    char *t = "efmm";
    printf("p: '%s'\nt: '%s'\n", p, t);
    printf("strcspn(p, t)\n");
    size_t num = strspn(p, t);
    printf("result: '%lu'\n", num);
}

void test_strpbrk() {
    /* 遍历p指向的字符串，如果某个字符在t指向的字符串中出现，返回这个字符的指针*/
    char *p = "Mac Mini Air";
    char *t = "ipC";
    printf("p: '%s'\nt: '%s'\n", p, t);
    printf("strpbrk(p, t)\n");
    char * result = strpbrk(p, t);
    printf("result: '%s'\n", result);
}

void test_strchr() {
    /* 遍历p指向的字符串，如果发现某个子字符串就是t指向的字符，返回指向该字符串的指针 */
    const char *p = "test.dnk.rumor.dnk.mm";
    char t = 'd';
    char *result = strchr(p, t);
    printf("p: '%s'\nt: '%c'\n", p, t);
    printf("strchr(p, t)\n");
    printf("result: '%s'\n", result);
}

void test_strrchr() {
    /* 右遍历p指向的字符串，如果发现某个子字符串就是t指向的字符，返回指向该字符串的指针 */
    const char *p = "test.dnk.rumor.dnk.mm";
    char t = 'd';
    char *result = strrchr(p, t);
    printf("p: '%s'\nt: '%c'\n", p, t);
    printf("strrchr(p, t)\n");
    printf("result: '%s'\n", result);
}


void test_strerror() {
    /* 将错误码errno转换为错误的文本意思 */
    FILE *f;
    f = fopen("test.txt", "r");
    if (f == NULL){
        char * err_text = strerror(errno);
        printf("Error: %s\n", err_text);
    }
}

int find_index(void * element, void** array, int length) {
    char** list = (char **)array;
    char * dest = (char *)element;
    for (int i = 0; i < length; i++) {
        if (strcmp(dest, list[i]) == 0){
            return i;
        }
    }
    return -1;
}

/* 带命令行参数的 c main函数形式
   argc记录参数个数
   argv存储每个参数的内容
   argv[0] 是c二进制程序名
*/
int main(int argc, char * argv[]) {
    const char* name_list[] = {"strlen", "strcmp", "strncmp", "strcpy",
    "strncpy", "strtok", "strstr", "strspn", "strcspn", "strpbrk",
    "strchr", "strrchr", "strerror", "memcpy"};
    void (* func_list[])(void) = {test_strlen, test_strcmp, test_strncmp, test_strcpy,
    test_strncpy, test_strtok, test_strstr, test_strspn, test_strcspn, test_strpbrk,
    test_strchr, test_strrchr, test_strerror, test_memcpy};
    
    if (argc == 1) {
        printf("please type command %s -h or %s --help to see more details",
        argv[0], argv[0]);
        return -1;
    }
    else if(argc == 2) {
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("-t  %s\n", name_list[0]);
            for (int i = 1; i < sizeof(name_list)/sizeof(char*); i++){
                printf("    %s\n", name_list[i]);
            }
            printf("you can choose one or more options separated by a space after -t,and see according examples.");
       }
    }
    else {
        for (int i = 2; i < argc ; i ++) {
            int result = find_index(argv[i], (void **)name_list, sizeof(name_list)/sizeof(char*));
            if (result == -1) {
                printf("Error: unsuitable option!");
                return -1;
            }
            printf("----  %s test  ----\n", argv[i]);
            (func_list[result])();
            printf("---------------------------------------------\n\n");
        }
    }
    return 0;
}