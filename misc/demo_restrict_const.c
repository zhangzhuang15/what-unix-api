/** restrict const 关键字 */
#include <stdio.h>

int main() {
    const int num = 5;
    //num = 6; // 无法修改值
    int age = 12;

    const int *cp = &num;
    //*cp = 4;  // 无法修改
    cp = &age; // 但可以指向别的数据
    //*cp = 10;  // 还是不能修改

    int *const pc = &num; 
    *pc = 4; // num是const int, 虽然编译可以通过，但是并没修改num值
    printf("pc change the value of variable num, now num: %d\n", num); // 5
    //pc = &age; // 无法指向别的数据

    int *restrict rp = &age; // restrict告诉编译器，目前只有 指针rp访问 num变量，编译时可以优化
    int *p = &age;
    printf("before p change the value of variable age: %d\n ", age); // 12
    *p = 15;
    printf("after p change the value of variable age: %d\n", age); // 15
    // p 指向了变量 age， 还成功修改了 age， 所以 restrict 只是告诉编译器， 并不代表实际情况下只有
    // 一个指针指向 age
    // 例子:
    //    int num[3] = { 1, 3, 4 };
    //    int *restrict p = num;
    //    p[0] += 2;
    //    p[0] += 2;
    //    可能被优化为 p[0] += 4   
    //    但是
    //      p[0] += 2;
    //      num[0] *= 2;
    //      p[0] += 2;   结果为 8
    //    可能优化成 
    //       num[0] *= 2;
    //       p[0] += 4; 结果为 6
    //    就错了
    //    这里的优化是可能发生哦
    int nums[2] = { 1, 2};
    int *restrict q = nums;
    q[0] += 2;
    nums[0] *= 2;
    q[0] += 2;
    printf("nums[0]: %d\n", nums[0]); // 8 并没有真的发生上述的优化
}