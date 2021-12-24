/**
 * @file chrono_test.cpp
 * @author Richard Wang
 * @brief C++11 std::chrono时间库学习
 * @version : 1.0
 * @date 2021-12-24
 * 
 * @copyright Copyright (c), Richard Wang.
 * 
 */

#include <iostream>
#include <chrono>

/**
 * @brief steady_clock / system_clock / high_resolution_clock
 *  1.steady_clock 是单调的时钟，相当于教练手中的秒表；只会增长，适合用于记录程序耗时;
 *  2.system_clock 是系统的时钟；因为系统的时钟可以修改；甚至可以网络对时； 所以用系统时间计算时间差可能不准;
 *  3.high_resolution_clock 是当前系统能够提供的最高精度的时钟；它也是不可以修改的。相当于 steady_clock 的高精度版本。
 */
void test_clock()
{
    /* 1.几种时钟获取时间*/
    {
        std::chrono::steady_clock::time_point s_time = std::chrono::steady_clock::now();
        std::cout << "steady_clock: " << s_time.time_since_epoch().count() << std::endl;
    }
}

int main()
{
    test_clock();
    return 0;
}