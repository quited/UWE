#include <unity.h>
#include <type.h>

void test_type_size() {
    TEST_ASSERT_EQUAL_UINT32(1, sizeof(u8));
    TEST_ASSERT_EQUAL_UINT32(2, sizeof(u16));
    TEST_ASSERT_EQUAL_UINT32(4, sizeof(u32));
    TEST_ASSERT_EQUAL_UINT32(8, sizeof(u64));

    TEST_ASSERT_EQUAL_UINT32(1, sizeof(i8));
    TEST_ASSERT_EQUAL_UINT32(2, sizeof(i16));
    TEST_ASSERT_EQUAL_UINT32(4, sizeof(i32));
    TEST_ASSERT_EQUAL_UINT32(8, sizeof(i64));

    TEST_ASSERT_EQUAL_UINT32(4, sizeof(f32));
    TEST_ASSERT_EQUAL_UINT32(8, sizeof(f64));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_type_size);
    UNITY_END();
    return 0;
}