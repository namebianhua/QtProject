#include "mainwindow.h"
#include <QApplication>
//#include <mutex>
//#include <thread>
//#include <iostream>

#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <QSemaphore>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>

struct MyTimer
{
    struct MyTimer *ptr;
    char* data;
};

#include "cal.h"
//#include <semaphore>

int talk();
int lockMain();
int lockMainWait();
int semap();
//std::counting_semaphore<2> sem;
//QSemaphore sem(2);
int fbi(int f);
int fact(int n);
int sumFact(int i);
int lengthOfsubstring( std::string s)
{
    std::unordered_set<char> set;
    int res = 0;
    
}

double findmidle(std::vector<int>& nums1, std::vector<int>& nums2)
{
    std::vector<std::vector<int>> vect;
    nums1.insert(nums1.end(), nums2.begin(), nums2.end());
    std::sort(nums1.begin(), nums1.end());
//    size_t l = sizeof (nums1)/sizeof (nums1[0]);//sizeof()是在编译时执行的，动态数组无法使用，动态数组的大小在运行时不是由编译器管理的
    size_t l = nums1.size();
    std::cout << "l: " << l << std::endl;
    double mid = 0.0;
    if(l%2 == 0)
        mid = static_cast<double>(nums1[l / 2] + nums1[l / 2 - 1]) / 2;
    else {
        mid = static_cast<double>(nums1[l / 2]);
    }
    for (auto num1 : nums1) {
        std::cout << "num1: " << num1 << std::endl;
    }
    return mid;
}

//滑动窗口实现、
/**
void moveWindow ()
{
    //外层循环扩展右边界，内层循环扩展左边界
    for (int l = 0, r = 0 ; r < n ; r++) {
    //当前考虑的元素
    while (l <= r && check()) {//区间[left,right]不符合题意
        //扩展左边界
        }
    //区间[left,right]符合题意，统计相关信息
    }
}
*/




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<int> vec1 = {1, 3, 5, 7};
    std::vector<int> vec2 = {2, 4, 6};

    findmidle(vec1, vec2);
    Cal& cal1 = Cal::getinstance();
    Cal& cal2 = Cal::getinstance();
    Dev* dev1 = new Dev();
    Dev* dev2 = new Dev();

//    lockMainWait();
//    talk();
//    semap();
    int n = 3;
    std::cout << " mult: " <<cal1.mult(4, 5)<< std::endl;
    std::cout << " mult: " <<cal2.mult(4, 5)<< std::endl;
    std::cout << " dev1: " <<dev1->mult_s(4, 5)<< std::endl;
    std::cout << " dev2: " <<dev2->mult_s(4, 5)<< std::endl;
    std::cout << " fbi(5): " <<fbi(5)<< std::endl;
    std::cout << " fbi(5): " <<fact(n)<< std::endl;
    int sum = 0;
    for(int i = n; i > 0; i--){
        sum+=fact(i);
    }
    std::cout << " sum: " <<sum<< std::endl;

    //创建一个unordered_map实例
    std::unordered_map<std::string, int> word_count;

    //向hash表中插入元素
    word_count["hello"] = 1;
    word_count["world"] = 1;

    //使用迭代器遍历hash表的元素
    for (const auto& pair : word_count) {
        std::cout << pair.first << " occurs " << pair.second << " times" << std::endl;
    }

    //查询hash表中的元素
    if(word_count.find("hello")  != word_count.end()) {
        std::cout << "Found hello in the hash table" << std::endl;   }

    //更新hash表中的元素
    word_count["hello"]++;

    //再次遍历,验证更新
    for(const auto& pair : word_count) {
        std::cout << pair.first << " occurs " <<pair.second << " times" << std::endl;
    }
//    delete cal1;
    return a.exec();
}

struct Box {
    explicit Box(int num) : num_things{num} {}

    int num_things;
    std::mutex m;
};

int fbi(int f){
    if(f  <= 1){
       return f;
    } else {
        return fbi(f-1) + fbi(f-2);
    }
}

int fact(int n){
    if(n == 1){
        return 1;
    } else {
        return n * fact(n - 1);
    }
}


void transfer(Box &from, Box &to, int num)
{
    // defer_lock表示暂时unlock，默认自动加锁
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

    //两个同时加锁
    std::lock(lock1, lock2);//或者使用lock1.lock()

    from.num_things -= num;
    to.num_things += num;
    //作用域结束自动解锁,也可以使用lock1.unlock()手动解锁
}

int lockMain()
{
    Box acc1(100);
    Box acc2(50);

    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
    std::cout << "acc1 num_things: " << acc1.num_things << std::endl;
    std::cout << "acc2 num_things: " << acc2.num_things << std::endl;

    t1.join();
    std::cout << "acc1 num_things: " << acc1.num_things << std::endl;
    std::cout << "acc2 num_things: " << acc2.num_things << std::endl;
    t2.join();
    std::cout << "acc1 num_things: " << acc1.num_things << std::endl;
    std::cout << "acc2 num_things: " << acc2.num_things << std::endl;
}


std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
    for (int i=0; i<n; ++i) {
//        std::unique_lock<std::mutex> lck(mtx);//自动上锁
//        //第二个参数为false才阻塞（wait），阻塞完即unlock，给其它线程资源
//        cv.wait(lck,shipment_available);
        // consume:
        std::cout << cargo << '\n';
        cargo=0;
    }
}

int lockMainWait ()
{
    std::thread consumer_thread (consume,10);

    for (int i=0; i<10; ++i) {
        //每次cargo每次为0才运行。
        while (shipment_available()) std::this_thread::yield();
        std::unique_lock<std::mutex> lck(mtx);
        cargo = i+1;
//        cv.notify_one();
    }

    consumer_thread.join();
    return 0;
}


//std::mutex mtx; // 全局互斥锁
int shared_data = 0; // 共享数据

void increment() {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // 使用锁保护区域
        ++shared_data;
    }
}

int talk() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl; // 输出应为20000
    return 0;
}

//void print_id(int id) {
//    sem.acquire(); // 请求资源
//    // 获取到资源后，继续执行
//    std::cout << "thread: " << id <<std::endl;
//    sem.release(); // 释放资源
//}

//int semap() {
//    std::thread threads[4];
//    for (int i = 0; i < 4; ++i) {
//        threads[i] = std::thread(print_id, i);
//    }

//    for (auto& th : threads) {
//        th.join();
//    }

//    return 0;
//}


