#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int value;
    char *name;
    struct Node *next;
} Node, *Tree, *NodeList[2];
/* Node就是指结构体 struct Node 
   *Tree是指 Tree是一个指针类型，指向Node
   *NodeList[2]是指 NodeList是一个存放两个元素的数组类型，每个元素是指向 Node的指针
*/


/* 这里使用命令行格式的main函数
   argc表示命令行的标识符个数， argv是存储标识符的数组 
   例如：demo9 nack -r str -p 9980 
   argc=6
   argv={"demo9", "nack", "-r", "str", "-p", "9980"}
*/
int main(int argc, char* argv[]){
   if (argc > 1){
       for (int i = 0; i < argc; i++) {
           printf("arg[%d]: %s\n", i, argv[i]);
       }
   }
   Node *n = (Node*)malloc(sizeof(Node));
   n->value = 1;
   n->name = "Jackie";

   /* Tree t 等效于 Node *t  */
   Tree t = (Node*)malloc(sizeof(Node));
   t->value = 2;
   t->name = "Bike";

   NodeList l = {n, t};
   for (int i = 0; i < 2; i++){
       printf("value: %d  name: %s\n", l[i]->value, l[i]->name);
   }
   free(n);
   free(t);
   exit(200);
}