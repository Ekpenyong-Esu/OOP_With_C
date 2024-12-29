#include <unity.h>
#include "shape_factory.h"
#include "shape.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Tear down code if needed
}
void test_shape_factors(void) {
    Shape* circle = createShape(CIRCLE, 5.0);
    Shape* rectangle = createShape(RECTANGLE, 4.0, 6.0);
    Shape* triangle = createShape(TRIANGLE, 4.0, 3.0);
    TEST_ASSERT_NOT_NULL(circle);
    TEST_ASSERT_NOT_NULL(rectangle);
    TEST_ASSERT_NOT_NULL(triangle);
    TEST_ASSERT_EQUAL_FLOAT(78.54, circle->calculate_area(circle));
    TEST_ASSERT_EQUAL_FLOAT(24.0, rectangle->calculate_area(rectangle));
    TEST_ASSERT_EQUAL_FLOAT(6.0, triangle->calculate_area(triangle));
    destroyShape(circle);
    destroyShape(rectangle);
    destroyShape(triangle);
}
void test_create_circle_with_positive_radius(void) {
    double radius = 5.0;
    Shape* circle = createShape(CIRCLE, radius);
    TEST_ASSERT_NOT_NULL(circle);
    TEST_ASSERT_EQUAL_FLOAT(78.54, circle->calculate_area(circle));
    destroyShape(circle);
}

void test_create_rectangle_with_positive_dimensions(void) {
    Shape* rectangle = createShape(RECTANGLE, 4.0, 6.0);
    TEST_ASSERT_NOT_NULL(rectangle);
    TEST_ASSERT_EQUAL_FLOAT(24.0, rectangle->calculate_area(rectangle));
    destroyShape(rectangle);
}

void test_create_triangle_with_positive_dimensions(void) {
    double base_length = 4.0;
    double height = 3.0;
    Shape* triangle = createShape(TRIANGLE, base_length, height);
    TEST_ASSERT_NOT_NULL(triangle);
    TEST_ASSERT_EQUAL_FLOAT(6.0, triangle->calculate_area(triangle));
    destroyShape(triangle);
}

void test_create_shape_with_large_dimensions(void) {
    double large_value = 1e10;
    Shape* circle = createShape(CIRCLE, large_value);
    Shape* rectangle = createShape(RECTANGLE, large_value, large_value);
    Shape* triangle = createShape(TRIANGLE, large_value, large_value);

    TEST_ASSERT_NOT_NULL(circle);
    TEST_ASSERT_NOT_NULL(rectangle);
    TEST_ASSERT_NOT_NULL(triangle);

    TEST_ASSERT_EQUAL_FLOAT(M_PI * large_value * large_value, circle->calculate_area(circle));
    TEST_ASSERT_EQUAL_FLOAT(large_value * large_value, rectangle->calculate_area(rectangle));
    TEST_ASSERT_EQUAL_FLOAT(0.5 * large_value * large_value, triangle->calculate_area(triangle));

    destroyShape(circle);
    destroyShape(rectangle);
    destroyShape(triangle);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_shape_factors);
    RUN_TEST(test_create_circle_with_positive_radius);
    RUN_TEST(test_create_rectangle_with_positive_dimensions);
    RUN_TEST(test_create_triangle_with_positive_dimensions);
    RUN_TEST(test_create_shape_with_large_dimensions);
    return UNITY_END();
}
