#include "common/container/container.h"
#include "unity.h"

#include <errno.h>

int comp(const void *a, const void *b) {
    return 0;
}

void test_array() {
    array arr = array_init(10, sizeof(int));

    {
        TEST_ASSERT_EQUAL_INT(10, array_size(arr));
        //test getter/setter
        for (int i = 0; i < 10; i++)
            TEST_ASSERT_EQUAL_INT(0, array_set(arr, i, &i));

        for (int i = 0; i < 10; i++) {
            int p;
            TEST_ASSERT_EQUAL_INT(0, array_get(&p, arr, i));
            TEST_ASSERT_EQUAL_INT(i, p);
        }
    }

    {//copy arr
        array copy = array_copy(arr);
        //copy should be as same as arr
        TEST_ASSERT_EQUAL_INT(10, array_size(copy));

        for (int i = 0; i < 10; i++)
            TEST_ASSERT_EQUAL_INT(0, array_set(copy, i, &i));

        for (int i = 0; i < 10; i++) {
            int p;
            TEST_ASSERT_EQUAL_INT(0, array_get(&p, copy, i));
            TEST_ASSERT_EQUAL_INT(i, p);
        }

        TEST_ASSERT_EQUAL(NULL, array_destroy(copy));
    }

    {
        int *ptr = (int *) malloc(sizeof(int) * 10);
        array_copy_to_array(ptr, arr);
        for (int i = 0; i < 10; i++)
            TEST_ASSERT_EQUAL(i, ptr[i]);
        free(ptr);
    }

    {
        int *ptr = (int *) array_get_data(arr);
        for (int i = 0; i < 10; i++)
            TEST_ASSERT_EQUAL(i, ptr[i]);
    }

    {//slice arr[2,4)
        array slice = array_slice(arr, 2, 4);
        TEST_ASSERT_EQUAL(2, array_size(slice));
        for (int i = 2; i < 4; i++) {
            int p;
            TEST_ASSERT_EQUAL(0, array_get(&p, slice, i - 2));
            TEST_ASSERT_EQUAL(i, p);
        }

        {
            array append = array_append(arr, slice);
            TEST_ASSERT_EQUAL_INT(12, array_size(append));
            int *ptr = (int *) array_get_data(append);
            int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3};
            TEST_ASSERT_EQUAL_INT_ARRAY(expected, ptr, 12);
            TEST_ASSERT_EQUAL(NULL, array_destroy(append));
        }
        TEST_ASSERT_EQUAL(NULL, array_destroy(slice));
    }
    TEST_ASSERT_EQUAL(NULL, array_destroy(arr));
}

void test_vector() {
    vector vec = vector_init(sizeof(int));

    TEST_ASSERT_EQUAL_INT(1, vector_is_empty(vec));

    {
        for (int i = 0; i < 10; i++)
            TEST_ASSERT_EQUAL_INT(0, vector_add_last(vec, &i));

        for (int i = 0; i < 10; i++) {
            int p;
            TEST_ASSERT_EQUAL_INT(0, vector_get_first(&p, vec));
            TEST_ASSERT_EQUAL_INT(i, p);
            TEST_ASSERT_EQUAL_INT(0, vector_remove_first(vec));
        }

        TEST_ASSERT_EQUAL_INT(-EINVAL, vector_remove_first(vec));
    }

    {
        for (int i = 0; i < 10; i++)
            TEST_ASSERT_EQUAL_INT(0, vector_add_last(vec, &i));

        for (int i = 0; i < 10; i++) {
            int p;
            TEST_ASSERT_EQUAL_INT(0, vector_get_at(&p, vec, i));
            TEST_ASSERT_EQUAL_INT(i, p);
        }
        TEST_ASSERT_EQUAL_INT(0, vector_clear(vec));
    }
    
    TEST_ASSERT_EQUAL(NULL, vector_destroy(vec));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_array);
    RUN_TEST(test_vector);
    UNITY_END();
}