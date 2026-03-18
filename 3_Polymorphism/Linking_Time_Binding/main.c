/* main.c */

// 外部引用宣告 (External References)
extern void do_something();
extern void sit_on_it();
extern void think_it();

int main() {
    float x = 0, y = 1.0, z = 2.0; // 修正變數初始化
    
    sit_on_it();    // 呼叫外部引用
    think_it();     // 呼叫外部引用
    do_something(); // 呼叫外部引用
    
    x = y + x;
    return 0;
}
