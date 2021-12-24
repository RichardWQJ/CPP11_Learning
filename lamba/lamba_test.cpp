/**
 * @file lamba_test.cpp
 * @author Richard Wang
 * @brief Lambda表达式完整的声明格式如下：
 * [capture list] (params list) mutable exception-> return type { function body }
 * 各项具体含义如下
 *      1.capture list：    捕获外部变量列表
 *      2.params list：     形参列表
 *      3.mutable：         用来表示是否可以修改捕获的变量
 *      4.exception：       异常设定
 *      5.return type：     返回类型
 *      6.function body：   函数体
 * 
 * 此外，我们还可以省略其中的某些成分来声明“不完整”的Lambda表达式，常见的有以下几种：
 *      1. [capture list] (params list) -> return type {function body}
 *          声明了const类型的表达式，这种类型的表达式不能修改捕获列表中的值。
 * 
 *      2. [capture list] (params list) {function body}
 *          省略了返回值类型，但编译器可以根据以下规则推断出Lambda表达式的返回类型： 
 *              （1）如果function body中存在return语句，则该Lambda表达式的返回类型由return语句的返回类型确定； 
 *              （2）如果function body中没有return语句，则返回值为void类型。
 *
 *      3. [capture list] {function body}
 *          省略了参数列表，类似普通函数中的无参函数。
 * 
 * 相关知识摘自：https://www.cnblogs.com/DswCnblog/p/5629165.html
 * @version : 1.0
 * @date 2021-12-24
 * 
 * @copyright Copyright (c), Richard Wang.
 * 
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

bool cmp(int a, int b)
{
    return a < b;
}

/**
 * @brief [] (params list) -> return type {function body}
 *  忽略捕获外部变量列表的形式
 */
void test_no_capture_list()
{
    std::cout << "**************" << __FUNCTION__ << "**************" << std::endl;

    std::vector<int> val_list = {3, 2, 1, 5, 4, 6};
    std::vector<int> val_list2(val_list);

    /********** 1. 不使用匿名函数的方式 ********/
    std::cout << "Used normal function:" << std::endl;
    {
        std::cout << "[Sort Before]:";
        for (auto iter_val : val_list)
        {
            std::cout << iter_val << " ";
        }
        std::cout << std::endl;
    }

    std::sort(val_list.begin(), val_list.end(), cmp);

    {
        std::cout << "[Sort  After]:";
        for (auto iter_val : val_list)
        {
            std::cout << iter_val << " ";
        }
        std::cout << std::endl;
    }
    /****************************************/

    /************** 2. 使用匿名函数 *********/
    std::cout << "Used lamba function:" << std::endl;
    {
        std::cout << "[Sort Before]:";
        for_each(val_list2.begin(), val_list2.end(), [](int val)
                 { std::cout << val << " "; });
        std::cout << std::endl;
    }

    std::sort(val_list2.begin(), val_list2.end(), [](int a, int b) -> bool
              { return a < b; });

    {
        std::cout << "[Sort  After]:";
        for_each(val_list2.begin(), val_list2.end(), [](int val)
                 { std::cout << val << " "; });
        std::cout << std::endl;
    }
    /****************************************/

    return;
}

/**
 * @brief [capture list] (params list) -> return type {function body}
 * 使用捕获外部变量列表的形式
 *  1.值捕获
 *      [var](params list) -> return type {function body}
 *      以传值方式捕获外部变量，则在Lambda表达式函数体中无法修改该外部变量的值(类似于函数参数的值传递,且在lamba表达式中修改变脸会报错，除非使用了mutable)。
 * 
 *  2.引用捕获
 *      [&var](params list) -> return type {function body}
 *      以引用方式捕获外部变量，则在Lambda表达式函数体中可以修改该外部变量的值(类似于函数参数的引用传递)。
 * 
 *  3.捕获方式总结
 * ---------------------------------------------------------------------------------------------------------------
 * |    捕获形式         |   说明                                                                                  |
 * ---------------------------------------------------------------------------------------------------------------
 * |    []              |   不捕获任何外部变量                                                                      |
 * ---------------------------------------------------------------------------------------------------------------
 * |    [变量名, …]     |   默认以值得形式捕获指定的多个外部变量（用逗号分隔），如果引用捕获，需要显示声明（使用&说明符）   |
 * ----------------------------------------------------------------------------------------------------------------
 * |    [this]          |   以值的形式捕获this指针                                                                  |
 * ----------------------------------------------------------------------------------------------------------------
 * |    [=]             |   以值的形式捕获所有外部变量                                                               |
 * ----------------------------------------------------------------------------------------------------------------
 * |    [&]             |   以引用形式捕获所有外部变量                                                               |
 * ----------------------------------------------------------------------------------------------------------------
 * |    [=,&x]          |   变量x以引用形式捕获，其余变量以传值形式捕获                                                |
 * ----------------------------------------------------------------------------------------------------------------
 * |    [&,x]           |   变量x以值的形式捕获，其余变量以引用形式捕获                                                |
 * ----------------------------------------------------------------------------------------------------------------
 */
void test_with_capture_list()
{
    std::cout << "**************" << __FUNCTION__ << "**************" << std::endl;
    /* 1.引入auto介绍捕获 */
    {
        std::cout << "------------- test 1 ------------------" << std::endl;
        int a = 123;

        /* (1).通过"捕获外部变量列表"[capture list]传入参数 */
        auto fun = [a]
        { std::cout << a << std::endl; };
        fun();

        auto x = [](int val)
        { std::cout << val << std::endl; };
        /* (2).通过"函数体"后面的'()'传入参数 */
        x(2222);
    }

    /* 2.值捕获 */
    {
        std::cout << "------------- test 2.1 ------------------" << std::endl;
        {
            int val = 123;
            auto fun = [val]
            { std::cout << val << std::endl; };
            fun();
            val = 234;
            fun(); //值传递，外部的值变化之后，lamba内部还是原来的值
        }

        // auto fun = [val]
        // { std::cout << val++ << std::endl; }; //报错

        std::cout << "------------- test 2.2 ------------------" << std::endl;
        {
            int val = 123;
            auto fun = [val]() mutable
            { std::cout << ++val << std::endl; }; //加了mutable，不会报错
            fun();
            std::cout << val << std::endl; //值传递，lamba内部变量的值变化之后，不会影响外部的值
        }
    }

    /* 3.引用捕获 */
    {
        std::cout << "------------- test 3 ------------------" << std::endl;
        {
            int val = 123;
            auto fun = [&val]
            { std::cout << ++val << std::endl; };

            fun();
            std::cout << val << std::endl; //引用传递，lamba内部变量的值变化之后，会影响外部的值
        }
    }

    /* 4.隐式捕获*/
    {
        std::cout << "------------- test 4.1 ------------------" << std::endl;
        /* 4.1隐式值捕获*/
        {
            int val1 = 123;
            int val2 = 456;
            auto fun1 = [=]
            { std::cout << val1 << ", " << val2 << std::endl; };
            fun1();
        }

        std::cout << "------------- test 4.2 ------------------" << std::endl;
        /* 4.2隐式引用捕获*/
        {
            int val1 = 123;
            int val2 = 456;
            auto fun1 = [&]
            { std::cout << val1++ << ", " << val2++ << std::endl; };
            fun1();
            std::cout << val1 << ", " << val2 << std::endl;
        }

        std::cout << "------------- test 4.3 ------------------" << std::endl;
        /* 4.3部分隐式捕获*/
        {
            int val1 = 123;
            int val2 = 456;
            auto fun1 = [=, &val2]
            { std::cout << val1 << ", " << val2++ << std::endl; }; //[&val2, =] 编译不通过，隐式表达式=和&必须在前面
            fun1();
            std::cout << val1 << ", " << val2 << std::endl;
        }
    }

    /* 5.以值得形式捕获this指针*/
    {
        std::cout << "------------- test 5 ------------------" << std::endl;
        class test
        {
        public:
            test(int _val) : val(_val) {}

            void init()
            {
                std::thread([this]()
                            {
                                while (1)
                                {
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    std::cout << val << std::endl;
                                }
                            })
                    .join();
            }

        private:
            int val;
        };

        test t(123);
        t.init();
    }
    return;
}

int main()
{
    /************* test_no_capture_list() ************/
    test_no_capture_list();
    /************************************************/

    /************ test_with_capture_list() **********/
    test_with_capture_list();
    /************************************************/
    return 0;
}