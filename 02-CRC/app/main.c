
#include <stdio.h>
#include "shape.h"
#include "shape_factory.h"

#include <log.h>
#include <config.h>

int main(void) {

    log_info("Welcome to %s v%s\n", project_name, project_version);
    // Create shapes using factory method
    Shape* circle = createShape(CIRCLE, 5.0);
    Shape* rectangle = createShape(RECTANGLE, 4.0, 6.0);
    Shape* triangle = createShape(TRIANGLE, 4.0, 3.0);

    // Draw shapes
    printf("Drawing Shapes:\n");
    circle->draw(circle);
    rectangle->draw(rectangle);
    triangle->draw(triangle);

    // Calculate and print areas
    printf("\nShape Areas:\n");
    printf("Circle Area: %.2f\n", circle->calculate_area(circle));
    printf("Rectangle Area: %.2f\n", rectangle->calculate_area(rectangle));
    printf("Triangle Area: %.2f\n", triangle->calculate_area(triangle));

    // Clean up
    destroyShape(circle);
    destroyShape(rectangle);
    destroyShape(triangle);

    return 0;
}
