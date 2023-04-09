#ifndef __HELPERS_H
#define __HELPERS_H

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <ctime>

struct test_data
{
    uint32_t*   data;
    size_t      data_size;
};

typedef void filler_t(test_data* tdata);

#define PROFILE_ACTION(action, time_delta) do                           \
{                                                                       \
    clock_t time_start = clock();                                       \
    action;                                                             \
    clock_t time_end = clock();                                         \
    time_delta = (time_end - time_start) / (CLOCKS_PER_SEC / 1000);     \
} while (0)

#define TEST_TREE_INSERT(tested_tree, tdata) do                         \
{                                                                       \
    for (size_t data_index = 0; data_index < tdata->size; ++data_index) \
        tested_tree.insert(tdata->data[data_index]);                    \
} while(0)

#define TEST_TREE_ERASE(tested_tree, tdata) do                          \
{                                                                       \
    for (size_t data_index = 0; data_index < tdata->size; data_index+=2)\
        tested_tree.erase(tdata->data[data_index]);                     \
} while(0)

#define REPEAT_TEST(tree, repetitions, tdata, filler, time_insert, time_erase) \
do {                                                                           \
    for (size_t repeat = 0; repeat < repetitions; repeat++)                    \
    {                                                                          \
        uint64_t time_delta = 0;                                               \
        filler(&tdata);                                                        \
        tree tested_tree;                                                      \
        PROFILE_ACTION(TEST_TREE_INSERT(tested_tree, tdata), time_delta);      \
        time_insert += time_delta;                                             \
        PROFILE_ACTION(TEST_TREE_ERASE(tested_tree, tdata), time_delta);       \
        time_erase += time_delta;                                              \
        if (time_erase + time_insert >= 5*60*1000)                             \
        {                                                                      \
            time_erase  = (time_erase  / (repeat + 1)) * repetitions;          \
            time_insert = (time_insert / (repeat + 1)) * repetitions;          \
            break;                                                             \
        }                                                                      \
    }                                                                          \
    time_insert /= repetitions;                                                \
    time_erase  /= repetitions;                                                \
} while(0)

#define RUN_TEST(output_insert, output_erase,tree, tdata, filler, seed) do     \
{                                                                              \
    srand(seed);                                                     \
    for (size_t sample_size = initial_size;                                    \
         sample_size <= end_size;                                              \
         sample_size += step_size)                                             \
    {                                                                          \
        tdata.data_size = sample_size;                                         \
        uint64_t time_insert = 0, time_erase = 0;                              \
        REPEAT_TEST(tree, repetitions, tdata, filler, time_insert, time_erase);\
        fprintf(output_insert, STR(tree)"%zu,%lu\n", sample_size, time_insert);\
        fpritnf(output_erase,  STR(tree)"%zu,%lu\n", sample_size, time_erase); \
        if (time_insert + time_erase >= 60*1000) break;                        \
    }                                                                          \
} while(0)

#endif
