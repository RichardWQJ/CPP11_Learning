/**
 * @file tie_tuple_pair_test.cpp
 * @author Richard Wang
 * @brief 介绍 std::pair std::tuple 和 std::tie 的基本使用
 *  1. std::pair
 *      在C++标准库中，pair类最早出现在c++98中，它提供一个简单的类，可以将两种不同（或者相同）的值聚合在一起，类似键值对(key/value)的形式。
 *  2. std::tuple
 *      tuple类最早在TR1中引入，是pair类的扩展泛化，允许最多10个不同（或相同）类型的元素。在c++11中，tuple类重新实现了，基于可变参模版，可以容纳任意多的异质元素。
 *  3. std::tie
 *      创建左值引用的 std::tuple，或将 std::tuple 解包为独立对象。
 * 相关知识摘自：https://blog.csdn.net/weixin_42915431/article/details/107898331?spm=1001.2101.3001.6650.9&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-9.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-9.no_search_link
 * @version : 1.0
 * @date 2021-12-24
 * 
 * @copyright Copyright (c), Richard Wang.
 * 
 */
#include <iostream>
#include <list>
#include <vector>
#include <tuple>
#include <algorithm>

/**
 * @brief 介绍std::pair的使用
 * 1. 构造函数及初始化
 *      pair<T1, T2> p;
 *      pair<T1, T2> p(val1, val2);
 *      pair<T1, T2> p{val1, val2}; //初始化列表方式
 *      pair<T1, T2> p(rv1, rv2);
 *      pair<T1, T2> p(t1, tv2); //用tuple类型的t1、t2元素初始化
 *      pair<T1, T2> p(p2);
 *      pair<T1, T2> p(rv); //move构造，将rv内容移动至p，允许隐式类型转换
 * 
 * 2. 赋值函数
 *      p = p2; // 允许隐式类型转换
 *      p = rv; // 将rv值move assign给p，允许隐式转换
 * 
 * 3. 获取pair成员或给成员赋值
 *      auto left = p.first;
 *      auto right = p.second;
 * 
 *      std::get<0>(p);
 *      std::get<1>(p);
 * 
 * 4. 比较函数
 *      p1 == p2; //先比较p1.first==p2.first，再比较p1.second==p2.second，以下同
 *      p1 != p2;
 *      p1 < p2;
 *      p1 > p2;
 *      p1 <= p2;
 *      p1 >= p2;
 * 
 * 5. 交换函数
 *      p1.swap(p2);
 *      swap(p1, p2);
 * 
 * 6. 用make_pair构造pair类型变量
 *      std::make_pair(val1, val2); 返回一个std::pair类型变量
 *      auto p = std::pair<T1, T2>(val1, val2);
 *      auto p = std::make_pair(val1, val2);
 */
void pair_test()
{
    std::cout << "------------- test std::pair ------------------" << std::endl;
    std::vector<std::pair<int, std::string>> info_list;
    std::pair<int, std::string> p1(12, "Mark");
    auto p2 = std::make_pair<int, std::string>(17, "Jack");
    auto p3 = std::make_pair(11, "Jim");

    info_list.emplace_back(p1);
    info_list.emplace_back(p2);
    info_list.emplace_back(p3);
    info_list.emplace_back(std::make_pair(14, "Rose"));

    for_each(info_list.begin(), info_list.end(), [](const std::pair<int, std::string> &p)
             { std::cout << "Name: " << p.second
                         << ", Age:" << std::get<0>(p) << std::endl; });
}

/**
 * @brief 介绍std::tuple的使用
 * 1. 构造函数及初始化
 *      tuple<T1, T2,..., Tn> t;
 *      tuple<t1,T2,...,Tn> t(val1, val2,..., valn);
 *      tuple<T1, T2> t(p); //用pair初始化tuple，此tuple就两个成员
 *      tuple<T1, T2,..., Tn> t{v1, v2,...,vn}; //初始化列表方式
 * 
 * 2. 赋值函数
 *      t = t2;
 *      t = p; //pair类型的p，赋值给tuple类型的t（仅俩成员），类型必须匹配
 * 
 * 3. 获取成员变量或给成员赋值
 *      tuple<int, float, string, int> t(12, 3.6, "test", 34);
 * 
 *      int val1 = std::get<0>(t); //获取第一个成员值
 *      std::get<0>(t) = 11; //修改第一个成员变量值
 * 
 * 4. 比较函数(使用字典式比较法则)
 *      t1 == t2;
 *      t1 != t2;
 *      t1 < t2;
 *      t1 <= t2;
 *      t1 > t2;
 *      t1 >= t2;
 * 
 * 5. 交换函数
 *      t1.swap(t2);
 *      swap(t1, t2);
 * 
 * 6. 用make_tuple构造tuple类型变量
 *      std::make_tuple(val1, val2, ...); 返回一个std::tuple类型变量
 *      auto p = std::tuple<T1, T2, T3>(val1, val2, val3);
 *      auto p = std::make_tuple(val1, val2, val3);
 */
void tuple_test()
{
    std::cout << "------------- test std::tuple ------------------" << std::endl;
    std::tuple<int, std::string, int> user1{26, "Richard", 178};
    std::tuple<int, std::string, int> user2 = std::make_tuple(29, "Jack", 180);
    auto user3 = std::make_tuple(25, "Simth", 191);

    std::list<std::tuple<int, std::string, int>> userList;
    userList.emplace_back(user1);
    userList.push_back(user2);
    userList.push_back(user3);

    for_each(userList.begin(), userList.end(), [](const std::tuple<int, std::string, int> &user)
             { std::cout << "Age:" << std::get<0>(user) << ", Name: " << std::get<1>(user) << ", High: " << std::get<2>(user) << std::endl; });
}

/**
 * @brief 介绍std::tie的使用
 *  1. std::tie会将变量的引用整合为一个std::tuple对象，作为左值，对这些变量实现批量赋值，如下：
 *      int i;
 *      double d;
 *      std::string s;
 *      std::tuple<int, double, std::string> t(1, 2.50, "Hello");
 *      std::tie(i, d, s) = t; //此时i, d, s的值分别会被赋值为t中的对应位置的值，即：1, 2.50, "Hello".
 * 
 *  2. 使用std::ignore来忽略某些(也可以看成是跳过)std::tuple中的某些返回值，如：
 *      std::tie(i, std::ignore, s); //此时仅变量i和s被赋值，变量d无变化.
 *  
 *  3. 注意：tie无法直接从初始化列表获得值，比如下面这样会编译错误：
 *      std::tie(i, d, s) = {1, 2.0, "3"};
 */
void tie_test()
{
    std::cout << "------------- test std::tie ------------------" << std::endl;
    std::tuple<int, std::string, std::string> info1(12, "Feb", "China");
    std::tuple<int, std::string, std::string> info2 = std::make_tuple(24, "Jun", "America");
    auto info3 = std::make_tuple(31, "March", "English");

    std::list<std::tuple<int, std::string, std::string>> info_list;
    info_list.emplace_back(info1);
    info_list.emplace_back(info2);
    info_list.emplace_back(info3);
    info_list.emplace_back(std::make_tuple<int, std::string, std::string>(18, "Dec", "France"));

    for_each(info_list.begin(), info_list.end(), [](const std::tuple<int, std::string, std::string> &info)
             {
                 int i_date;
                 std::string str_month;
                 std::string str_country;
                 std::tie(i_date, str_month, str_country) = info;

                 std::cout << i_date << ", " << str_month << ", " << str_country << std::endl;
             });
}

int main()
{

    /******************* pair_test() ****************/
    pair_test();
    /************************************************/

    /****************** tuple_test() ****************/
    tuple_test();
    /************************************************/

    /****************** tie_test() ******************/
    tie_test();
    /************************************************/

    return 0;
}