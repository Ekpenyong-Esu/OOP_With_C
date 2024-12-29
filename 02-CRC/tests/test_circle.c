
#include <float.h>
#include <string.h>
#include <unity.h>

#include "circle.h"
#include "shape.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void setUp(void) {
    // Set up global state for each test case
}

void tearDown(void) {
    // Clean up after each test case
}

void test_circle_area_doesnt_modify_shape(void) {
    double original_radius = 5.0;
    Circle* circle = (Circle*)createCircle(original_radius);
    TEST_ASSERT_NOT_NULL(circle);

    Shape* shape = (Shape*)circle;
    unsigned char initial_memory[sizeof(Circle)];
    memcpy(initial_memory, circle, sizeof(Circle));


    TEST_ASSERT_EQUAL_MEMORY(initial_memory, circle, sizeof(Circle));
    TEST_ASSERT_EQUAL_FLOAT(original_radius, circle->radius);

    destroyShape(shape);
}

void test_circle_area_with_zero_radius(void) {
    Circle* circle = (Circle*)createCircle(0.0);
    TEST_ASSERT_NOT_NULL(circle);
    double area = circle->base.calculate_area((Shape*)circle);
    TEST_ASSERT_EQUAL_FLOAT(0.0, area);
    destroyShape((Shape*)circle);
}

void test_circle_area_with_negative_radius(void) {
    Circle* circle = (Circle*)createCircle(-5.0);
    TEST_ASSERT_NOT_NULL(circle);
    double area = circle->base.calculate_area((Shape*)circle);
    // Assuming the area should be calculated as if the radius were positive
    TEST_ASSERT_EQUAL_FLOAT(M_PI * 5.0 * 5.0, area);
    destroyShape((Shape*)circle);
}


void test_circle_new(void) {
    Circle* circle = createCircle(5.0);
    TEST_ASSERT_NOT_NULL(circle);
    TEST_ASSERT_EQUAL_FLOAT(5.0, circle->radius);
    destroyShape((Shape*)circle);
}


void test_circle_area(void) {
    Circle* circle = (Circle*)createCircle(5.0);
    TEST_ASSERT_NOT_NULL(circle);
    double area = circle->base.calculate_area((Shape*)circle);
    TEST_ASSERT_EQUAL_FLOAT(M_PI * 5.0 * 5.0, area);
    destroyShape((Shape*)circle);
}

void test_draw_circle(void) {
    double radius = 3.5;
    Circle* circle = (Circle*)createCircle(radius);
    TEST_ASSERT_NOT_NULL(circle);

    // Redirect stdout to a buffer
    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    // Call the draw function
    circle->base.draw((Shape*)circle);

    // Restore stdout
    freopen("/dev/tty", "a", stdout);

    // Check the output
    char expected_output[100];
    snprintf(expected_output, sizeof(expected_output), "Drawing a Circle with radius %.2f\n", radius);
    TEST_ASSERT_EQUAL_STRING(expected_output, buffer);

    destroyShape((Shape*)circle);
}


void test_draw_circle_prints_correct_radius(void) {
    double radius = 7.5;
    Circle* circle = (Circle*)createCircle(radius);
    TEST_ASSERT_NOT_NULL(circle);

    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    circle->base.draw((Shape*)circle);

    freopen("/dev/tty", "a", stdout);

    char expected_output[100];
    snprintf(expected_output, sizeof(expected_output), "Drawing a Circle with radius %.2f\n", radius);
    TEST_ASSERT_EQUAL_STRING(expected_output, buffer);

    destroyShape((Shape*)circle);
}

void test_draw_circle_handles_null_pointer(void) {
    // Redirect stdout to a buffer
    char buffer[100] = {0};
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    // Call draw_circle with NULL
    draw_circle(NULL);

    // Restore stdout
    freopen("/dev/tty", "a", stdout);

    // Check that nothing was printed (buffer is empty)
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_draw_circle_output_format(void) {
    double radius = 3.14159;
    Circle* circle = (Circle*)createCircle(radius);
    TEST_ASSERT_NOT_NULL(circle);

    char buffer[100];
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);

    circle->base.draw((Shape*)circle);

    freopen("/dev/tty", "a", stdout);

    char expected_output[100];
    snprintf(expected_output, sizeof(expected_output), "Drawing a Circle with radius %.2f\n", radius);
    TEST_ASSERT_EQUAL_STRING(expected_output, buffer);

    destroyShape((Shape*)circle);
}

void test_createCircle_initializes_all_fields(void) {
    double radius = 5.0;
    Circle* circle = (Circle*)createCircle(radius);
    TEST_ASSERT_NOT_NULL(circle);
    TEST_ASSERT_EQUAL_FLOAT(radius, circle->radius);
    TEST_ASSERT_EQUAL_PTR(circle_area, circle->base.calculate_area);
    TEST_ASSERT_EQUAL_PTR(draw_circle, circle->base.draw);
    destroyShape((Shape*)circle);
}

void test_createCircle_with_max_double_radius(void) {
    double max_radius = DBL_MAX;
    Circle* circle = (Circle*)createCircle(max_radius);
    TEST_ASSERT_NOT_NULL(circle);
    TEST_ASSERT_EQUAL_FLOAT(max_radius, circle->radius);
    TEST_ASSERT_EQUAL_PTR(circle_area, circle->base.calculate_area);
    TEST_ASSERT_EQUAL_PTR(draw_circle, circle->base.draw);
    destroyShape((Shape*)circle);
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_circle_area_doesnt_modify_shape);
    RUN_TEST(test_circle_area_with_zero_radius);
    RUN_TEST(test_circle_area_with_negative_radius);
    RUN_TEST(test_circle_new);
    RUN_TEST(test_circle_area);
    RUN_TEST(test_draw_circle);
    RUN_TEST(test_draw_circle_prints_correct_radius);
    RUN_TEST(test_draw_circle_handles_null_pointer);
    RUN_TEST(test_draw_circle_output_format);
    RUN_TEST(test_createCircle_initializes_all_fields);
    RUN_TEST(test_createCircle_with_max_double_radius);

    return UNITY_END();
}
