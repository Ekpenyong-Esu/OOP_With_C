
#include <unity.h>
#include "rectangle.h"
#include "shape.h"
#include "unity_internals.h"
#include <float.h>
#include <stdlib.h>

void setUp(void) {

    // Set up code if needed
}

void tearDown(void) {
    // Tear down code if needed
}

void test_create_rectangle(void) {
    Shape* rect = createRectangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(5.0, ((Rectangle*)rect)->width);
    TEST_ASSERT_EQUAL_FLOAT(10.0, ((Rectangle*)rect)->height);
    destroyShape(rect);
}

void test_rectangle_area_zero_width(void) {
    Shape* rect = createRectangle(0.0, 10.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(0.0, rect->calculate_area(rect));
    destroyShape(rect);
}

void test_rectangle_area_zero_height(void) {
    Shape* rect = createRectangle(5.0, 0.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(0.0, rect->calculate_area(rect));
    destroyShape(rect);
}

void test_rectangle_area_negative_width(void) {
    Shape* rect = createRectangle(-5.0, 10.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(-50.0, rect->calculate_area(rect));
    destroyShape(rect);
}

void test_rectangle_area_null_shape(void) {
    Shape* rect = NULL;
    TEST_ASSERT_EQUAL_FLOAT(0.0, rectangle_area(rect));
}

void test_rectangle_area_invalid_shape(void) {
    // Create a mock shape that is not a rectangle
    Shape mock_shape;
    mock_shape.calculate_area = NULL;
    mock_shape.draw = NULL;

    // Call rectangle_area with the invalid shape
    double result = rectangle_area(&mock_shape);

    // Assert that the result is 0.0 (or any other expected behavior for invalid input)
    TEST_ASSERT_EQUAL_FLOAT(0.0, result);
}

void test_rectangle_area_max_values(void) {
    double max_double = DBL_MAX;
    Shape* rect = createRectangle(max_double, max_double);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(INFINITY, rect->calculate_area(rect));
    destroyShape(rect);
}

void test_rectangle_area(void) {
    Shape* rect = createRectangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(50.0, rect->calculate_area(rect));
    free(rect);
}

void test_draw_rectangle(void) {
    Shape* rect = createRectangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(rect);
    // Redirect stdout to a buffer
    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
    rect->draw(rect);
    // Restore stdout
    freopen("/dev/tty", "a", stdout);

    char expected[100];
    snprintf(expected, sizeof(expected), "Drawing a Rectangle with width %.2f and height %.2f\n", 5.00, 10.00);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    free(rect);
}


void test_draw_rectangle_min_values(void) {
    double min_double = DBL_MIN;
    Shape* rect = createRectangle(min_double, min_double);
    TEST_ASSERT_NOT_NULL(rect);

    char buffer[200];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    rect->draw(rect);

    freopen("/dev/tty", "a", stdout);

    char expected[200];
    snprintf(expected, sizeof(expected), "Drawing a Rectangle with width %.2f and height %.2f\n", min_double, min_double);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);

    destroyShape(rect);
}


void test_create_rectangle_function_pointers(void) {
    Shape* rect = createRectangle(5.0, 10.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_PTR(rectangle_area, rect->calculate_area);
    TEST_ASSERT_EQUAL_PTR(draw_rectangle, rect->draw);
    destroyShape(rect);
}

void test_compare_createRectangle_and_createrectangle(void) {
    double width = 5.0;
    double height = 10.0;

    Shape* rect1 = createRectangle(width, height);
    Shape* rect2 = createRectangle(width, height);

    TEST_ASSERT_NOT_NULL(rect1);
    TEST_ASSERT_NOT_NULL(rect2);

    TEST_ASSERT_EQUAL_FLOAT(((Rectangle*)rect1)->width, ((Rectangle*)rect2)->width);
    TEST_ASSERT_EQUAL_FLOAT(((Rectangle*)rect1)->height, ((Rectangle*)rect2)->height);
    TEST_ASSERT_EQUAL_PTR(rect1->calculate_area, rect2->calculate_area);
    TEST_ASSERT_EQUAL_PTR(rect1->draw, rect2->draw);

    destroyShape(rect1);
    destroyShape(rect2);
}

void test_create_rectangle_one_zero_dimension(void) {
    Shape* rect = createRectangle(0.0, 5.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(0.0, ((Rectangle*)rect)->width);
    TEST_ASSERT_EQUAL_FLOAT(5.0, ((Rectangle*)rect)->height);
    TEST_ASSERT_EQUAL_PTR(rectangle_area, rect->calculate_area);
    TEST_ASSERT_EQUAL_PTR(draw_rectangle, rect->draw);
    destroyShape(rect);
}

void test_create_rectangle_both_zero_dimensions(void) {
    Shape* rect = createRectangle(0.0, 0.0);
    TEST_ASSERT_NOT_NULL(rect);
    TEST_ASSERT_EQUAL_FLOAT(0.0, ((Rectangle*)rect)->width);
    TEST_ASSERT_EQUAL_FLOAT(0.0, ((Rectangle*)rect)->height);
    TEST_ASSERT_EQUAL_PTR(rectangle_area, rect->calculate_area);
    TEST_ASSERT_EQUAL_PTR(draw_rectangle, rect->draw);
    destroyShape(rect);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_rectangle);
    RUN_TEST(test_rectangle_area_zero_width);
    RUN_TEST(test_rectangle_area_zero_height);
    RUN_TEST(test_rectangle_area_negative_width);
    RUN_TEST(test_rectangle_area_null_shape);
    RUN_TEST(test_rectangle_area_invalid_shape);
    RUN_TEST(test_rectangle_area_max_values);
    RUN_TEST(test_rectangle_area);
    RUN_TEST(test_draw_rectangle);
    RUN_TEST(test_draw_rectangle_min_values);
    RUN_TEST(test_create_rectangle_function_pointers);
    RUN_TEST(test_compare_createRectangle_and_createrectangle);
    RUN_TEST(test_create_rectangle_one_zero_dimension);
    RUN_TEST(test_create_rectangle_both_zero_dimensions);



    return UNITY_END();
}
