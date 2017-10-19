/*
 * BitsArray_test.cpp
 *
 *  Created on: Oct 2, 2017
 *      Author: super29
 */
#include <exception>
#include <stdexcept>

#include "BitsArray.hpp"
#include "../utils.hpp"

using namespace ilrd;

static size_t test_flip();
static size_t test_set_get();
static size_t test_sqr_brac();
static size_t test_shift();
static size_t test_time();

int main()
{
    size_t err_cntr = 0;

    err_cntr += test_flip();
    err_cntr += test_set_get();
    err_cntr += test_sqr_brac();
    err_cntr += test_shift();
    err_cntr += test_time();

    if (err_cntr) {
        std::cout << "test fail " << err_cntr << " errors" << std::endl;
    } else {
        std::cout << "\nBitsArray test succes!!" << std::endl;
    }

    BitsArray<25> arr;
    arr.flip_all();
    arr.flip_bit(21);
    arr.flip_bit(3);
    arr.print();
    arr <<= 8;
    arr.print();
}

static size_t test_flip()
{
    size_t err_cntr = 0;

    BitsArray<14> arr;

    try {
        ++err_cntr;
        arr.flip_bit(14);
    } catch (std::out_of_range& o) {
        --err_cntr;
    }

    arr.print();
    arr.flip_bit(1);
    arr.print();
    arr.flip_all();
    arr.print();

    err_cntr += Test<size_t>(arr.count_bits(), 13);

    BitsArray<14> arr2;

    arr.flip_all();
    arr.flip_all();

    arr2.flip_bit(0);
    arr2.flip_bit(2);
    arr2.flip_bit(3);
    arr2.flip_bit(4);
    arr2.flip_bit(5);
    arr2.flip_bit(6);
    arr2.flip_bit(7);
    arr2.flip_bit(8);
    arr2.flip_bit(9);
    arr2.flip_bit(10);
    arr2.flip_bit(11);
    arr2.flip_bit(12);
    arr2.flip_bit(13);

    err_cntr += Test(arr, arr2);

    char test = err_cntr ? 'X' : 'V';
    std::cout << "test flip - " << test << std::endl;

    return err_cntr;
}

static size_t test_set_get()
{
    size_t err_cntr(0);

    BitsArray<17> arr;
    arr.set(16, true);
    BitsArray<17> arr2;
    arr2.set(16, true);

    err_cntr += Test(arr, arr2);
    err_cntr += Test(arr[16], arr2[16]);

    try {
        ++err_cntr;
        arr.set(17, false);
    } catch (std::out_of_range& o) {
        --err_cntr;
    }

    char test = err_cntr ? 'X' : 'V';
    std::cout << "test set get - " << test << std::endl;

    return err_cntr;
}

static size_t test_sqr_brac()
{
    size_t err_cntr(0);

    BitsArray<17> arr;
    arr[16] = true;
    BitsArray<17> arr2;
    arr2[16] = true;

    err_cntr += Test(arr[9], arr2[9]);
    err_cntr += Test(arr[16], arr2[16]);

    BitsArray<17> arr3;
    arr3[3] = arr2[3];

    err_cntr += Test(arr[3], arr2[3]);

    BitsArray<17> arr4(arr2);

    err_cntr += Test(arr[9], arr2[9]);

    char test = err_cntr ? 'X' : 'V';
    std::cout << "test[] - " << test << std::endl;

    return err_cntr;
}

static size_t test_shift()
{
    size_t err_cntr = 0;

    BitsArray<15> arr;
    BitsArray<15> arr2;

    arr[5] = true;
    arr2[4] = true;

    arr >>= 1;

    err_cntr += Test(arr[4], arr2[4]);

    arr >>= 1;
    err_cntr += Test<bool>(arr[4], !arr2[4]);

    err_cntr += Test<bool>(arr[3], true);

    arr <<= 2;
    arr2 <<= 1;

    err_cntr += Test(arr[5], arr2[5]);

    char test = err_cntr ? 'X' : 'V';
    std::cout << "shift test - " << test << std::endl;

    return err_cntr;
}

static size_t test_time()
{
    size_t err_cntr = 0;
    const size_t arr_size = 99999;
    BitsArray<arr_size> arr;
    BitsArray<arr_size> arr2;

    arr[5] = true;
    arr2[4] = true;

    arr >>= 1;

    err_cntr += Test<size_t>(arr.count_bits(), 1);

    for (size_t i = 0; i < arr_size; ++i) {
        arr.set(i, true);
    }

    err_cntr += Test<size_t>(arr.count_bits(), arr_size);

    char test = err_cntr ? 'X' : 'V';
    std::cout << "time test - " << test << std::endl;

    return err_cntr;
}

