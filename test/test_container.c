#include <container.h>
#include <unity.h>

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

        TEST_ASSERT_EQUAL_INT(10, vector_size(vec));

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

void test_buffer() {
    buffer buf = buffer_init(sizeof(int));

    array write_arr = array_init(10, sizeof(int));
    for (int i = 0; i < 10; i++)
        TEST_ASSERT_EQUAL_INT(0, array_set(write_arr, i, &i));

    TEST_ASSERT_EQUAL_INT(0, buffer_write(buf, write_arr, 6));

    for (int i = 0; i < 6; i++) {
        int *p;
        TEST_ASSERT_EQUAL_INT(6 - i, buffer_read_available(buf));
        TEST_ASSERT_EQUAL_INT(0, buffer_read_one((void **) &p, buf));
        TEST_ASSERT_EQUAL_INT(i, *p);
    }

    TEST_ASSERT_EQUAL(NULL, buffer_destroy(buf));
}

void test_stack() {
    stack sta = stack_init(sizeof(int));
    for (int i = 0; i < 10; i++)
        TEST_ASSERT_EQUAL_INT(0, stack_push(sta, &i));

    TEST_ASSERT_EQUAL_INT(10, stack_size(sta));

    for (int i = 9; i <= 0; i--) {
        int p;
        TEST_ASSERT_EQUAL_INT(0, stack_pop(&p, sta));
        TEST_ASSERT_EQUAL_INT(i, p);
    }

    TEST_ASSERT_EQUAL_INT(NULL, stack_destroy(sta));
}

int set_comparator(const void *const one, const void *const two) {
    return *(const int *) one - *(const int *) two;
}

void test_set() {
    set s = set_init(sizeof(int), set_comparator);
    TEST_ASSERT_EQUAL_INT(1, set_is_empty(s));

    for (int i = 0; i < 10; i++)
        TEST_ASSERT_EQUAL_INT(0, set_put(s, &i));

    {
        int p = 10;
        TEST_ASSERT_EQUAL_INT(0, set_put(s, &p));
        p = 9;
        TEST_ASSERT_EQUAL_INT(0, set_put(s, &p));
    }

    TEST_ASSERT_EQUAL_INT(11, set_size(s));

    for (int i = 0; i < 10; i++)
        TEST_ASSERT_EQUAL_INT(1, set_contains(s, &i));

    for (int i = 0; i < 11; i++)
        TEST_ASSERT_EQUAL_INT(1, set_remove(s, &i));

    TEST_ASSERT_EQUAL_INT(1, set_is_empty(s));
    set_destroy(s);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_array);
    RUN_TEST(test_vector);
    RUN_TEST(test_buffer);
    RUN_TEST(test_stack);
    RUN_TEST(test_set);
    UNITY_END();
}