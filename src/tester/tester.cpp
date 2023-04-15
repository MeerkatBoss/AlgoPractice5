#include "trees/binary_tree.h"
#include "trees/avl_tree.h"
#include "trees/splay_tree.h"
#include "trees/treap.h"
#include "trees/skip_list.h"

#include "tester.h"
#include "helpers.h"

static void fill_random(test_data* tdata);
static void fill_sorted(test_data* tdata);
#define CAT(x, y) __CAT(x, y)
#define __CAT(x, y, ...) x##y
#define STR(x) __STR(x)
#define __STR(x) #x

void run_all_tests()
{
#define INITIAL_SIZE(val) size_t initial_size = val;
#define END_SIZE(val)     size_t end_size = val;
#define STEP_SIZE(val)    size_t step_size = val;
#define REPEAT(val)       size_t repetitions = val;
#define FILL_TYPE(func)   filler_t *filler = func;

#define TEST_TREES(trees) CAT(TEST_TREE_A trees, _END) 
#define TEST_TREE_A(tree) \
    RUN_TEST(output_insert, output_erase, tree, tdata, filler, seed);\
    TEST_TREE_B
#define TEST_TREE_B(tree) \
    RUN_TEST(output_insert, output_erase, tree, tdata, filler, seed);\
    TEST_TREE_A
#define TEST_TREE_A_END
#define TEST_TREE_B_END

    // unsigned seed = (unsigned) time(NULL);
    unsigned seed = 0;
    // printf("seed = %u\n", seed);

    test_data tdata = { .data = NULL, .data_size = 0 };
    tdata.data = (uint32_t*) calloc(10'000'000, sizeof(*tdata.data));

    FILE* output_insert = fopen("results/" STR(TEST_CASE_NAME) "_insert.csv",
                                                                        "w+");
    FILE* output_erase  = fopen("results/" STR(TEST_CASE_NAME) "_erase.csv",
                                                                        "w+");
    setvbuf(output_insert, NULL, _IOLBF, BUFSIZ);
    setvbuf(output_erase,  NULL, _IOLBF, BUFSIZ);

    fputs("Tree,Sample Size,Elapsed Time (ms)\n", output_insert);
    fputs("Tree,Sample Size,Elapsed Time (ms)\n", output_erase);

#include STR(TEST_CASE)

    fclose(output_insert);
    fclose(output_erase);
    free(tdata.data);

#undef INITIAL_SIZE
#undef END_SIZE
#undef STEP_SIZE
#undef REPEAT
}

static void fill_random(test_data* tdata)
{
    for (size_t i = 0; i < tdata->data_size; ++i)
        tdata->data[i] = (uint32_t)rand();
}

static void fill_sorted(test_data* tdata)
{
    for (size_t i = 0; i < tdata->data_size; ++i)
        tdata->data[i] = (uint32_t)(i + 1);
}
