#include <string.h>
#include <unity.h>
#include "triangle.h"
#include "shape.h"
#include <float.h>
#include <stdlib.h>

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Tear down code if needed
}

void test_triangle_area(void) {
    Shape* triangle = createTriangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(triangle);
    TEST_ASSERT_EQUAL_DOUBLE(25.0, triangle->calculate_area(triangle));
    free(triangle);
}

void test_draw_triangle(void) {
    Shape* triangle = createTriangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(triangle);
    // Redirect stdout to a buffer
    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
    triangle->draw(triangle);
    // Restore stdout
    freopen("/dev/tty", "a", stdout);
    TEST_ASSERT_EQUAL_STRING("Drawing a Triangle with base 5.00 and height 10.00\n", buffer);
    free(triangle);
}


void test_triangle_area_null_pointer(void)
{
    double result = triangle_area(NULL);
    TEST_ASSERT_EQUAL_FLOAT(0.0, result);
}

void test_triangle_area_zero_base_length(void) {
    Shape* shape = createTriangle(0.0, 5.0);
    double area = triangle_area(shape);
    TEST_ASSERT_EQUAL_FLOAT(0.0, area);
    free(shape);
}

void test_triangle_area_large_values(void)
{
    double base_length = 1000000.0;
    double height = 2000000.0;
    Shape* shape = createTriangle(base_length, height);

    double expected_area = 0.5 * base_length * height;
    double actual_area = triangle_area(shape);

    TEST_ASSERT_EQUAL_DOUBLE(expected_area, actual_area);

    free(shape);
}

void test_triangle_area_with_small_dimensions() {
    double base_length = 1e-10;
    double height = 1e-10;
    Shape* shape = createTriangle(base_length, height);

    double expected_area = 0.5 * base_length * height;
    double actual_area = triangle_area(shape);

    TEST_ASSERT_EQUAL_FLOAT(expected_area, actual_area);

    free(shape);
}

void test_triangle_area_max_values(void)
{
    double max_base = DBL_MAX;
    double max_height = DBL_MAX;
    Shape* shape = createTriangle(max_base, max_height);

    double expected_area = 0.5 * max_base * max_height;
    double actual_area = triangle_area(shape);

    TEST_ASSERT_EQUAL_FLOAT(expected_area, actual_area);

    free(shape);
}

void test_create_triangle(void) {
    Shape* triangle = createTriangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(triangle);
    Triangle* tri = (Triangle*)triangle;
    TEST_ASSERT_EQUAL_DOUBLE(5.0, tri->base_length);
    TEST_ASSERT_EQUAL_DOUBLE(10.0, tri->height);
    free(triangle);
}

void test_draw_triangle_large_values(void) {
    double base_length = 1e15;
    double height = 1e15;
    Shape* triangle = createTriangle(base_length, height);
    TEST_ASSERT_NOT_NULL(triangle);

    char buffer[200];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
    triangle->draw(triangle);
    freopen("/dev/tty", "a", stdout);

    char expected[200];
    snprintf(expected, sizeof(expected), "Drawing a Triangle with base %.2f and height %.2f\n", base_length, height);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    free(triangle);
}

void test_draw_triangle_decimal_dimensions(void) {
    Shape* triangle = createTriangle(3.14, 2.71);
    TEST_ASSERT_NOT_NULL(triangle);

    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
    triangle->draw(triangle);
    freopen("/dev/tty", "a", stdout);

    TEST_ASSERT_EQUAL_STRING("Drawing a Triangle with base 3.14 and height 2.71\n", buffer);
    free(triangle);
}

void test_draw_triangle_formatting(void) {
    Shape* triangle = createTriangle(3.14159, 2.71828);
    TEST_ASSERT_NOT_NULL(triangle);

    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
    triangle->draw(triangle);
    freopen("/dev/tty", "a", stdout);

    TEST_ASSERT_EQUAL_STRING("Drawing a Triangle with base 3.14 and height 2.72\n", buffer);
    free(triangle);
}

void test_draw_triangle_multiple_calls(void) {
    Shape* triangle1 = createTriangle(3.0, 4.0);
    Shape* triangle2 = createTriangle(5.0, 6.0);
    TEST_ASSERT_NOT_NULL(triangle1);
    TEST_ASSERT_NOT_NULL(triangle2);

    char buffer[200];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    triangle1->draw(triangle1);
    triangle2->draw(triangle2);

    freopen("/dev/tty", "a", stdout);

    char expected[200];
    snprintf(expected, sizeof(expected),
             "Drawing a Triangle with base 3.00 and height 4.00\n"
             "Drawing a Triangle with base 5.00 and height 6.00\n");
    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    free(triangle1);
    free(triangle2);
}

void test_draw_triangle_extreme_values(void) {
    double base_length = DBL_MIN;
    double height = DBL_MAX;
    Shape* triangle = createTriangle(base_length, height);
    TEST_ASSERT_NOT_NULL(triangle);

    char buffer[200];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
    triangle->draw(triangle);
    freopen("/dev/tty", "a", stdout);

    char expected[200];
    snprintf(expected, sizeof(expected), "Drawing a Triangle with base %.2f and height %.2f\n", base_length, height);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    free(triangle);
}

void test_draw_triangle_performance(void) {
    Shape* triangle = createTriangle(3.0, 4.0);
    TEST_ASSERT_NOT_NULL(triangle);

    char buffer[10000];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    const int num_calls = 1000;
    for (int i = 0; i < num_calls; i++) {
        triangle->draw(triangle);
    }

    freopen("/dev/tty", "a", stdout);

    char expected[100];
    snprintf(expected, sizeof(expected), "Drawing a Triangle with base 3.00 and height 4.00\n");

    for (int i = 0; i < num_calls; i++) {
        TEST_ASSERT_EQUAL_STRING(expected, buffer + (i * strlen(expected)));
    }

    free(triangle);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_triangle_area);
    RUN_TEST(test_draw_triangle);
    RUN_TEST(test_create_triangle);
    return UNITY_END();
}
