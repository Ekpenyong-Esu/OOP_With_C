//
// Created by mahon on 3/9/2024.
//
// Test fixture for Task-related tests
#include "../include/gtest/gtest.h"
#include "../include/Task.h"


class TaskTest : public ::testing::Test {
protected:
void SetUp() override {
// Setup code that will be called before each test
}

void TearDown() override {
// Teardown code that will be called after each test
    }
};

TEST(TaskTest, CreateTaskWithType) {
// Create a basic task
Task* basicTask = createTaskWithType(BASIC, 1, "Basic Task", "This is a basic task", 2);
ASSERT_NE(basicTask, nullptr); // Assert that the task is not null
ASSERT_EQ(basicTask->id, 1); // Assert that the task id is correct
ASSERT_EQ(basicTask->type, BASIC); // Assert that the task type is BASIC
ASSERT_STREQ(basicTask->name, "Basic Task"); // Assert that the task name is correct
ASSERT_STREQ(basicTask->description, "This is a basic task"); // Assert that the task description is correct
ASSERT_EQ(basicTask->priority, 2); // Assert that the task priority is correct

// Create an urgent task
Task* urgentTask = createTaskWithType(URGENT, 2, "Urgent Task", "This is an urgent task", 1);
ASSERT_NE(urgentTask, nullptr); // Assert that the task is not null
ASSERT_EQ(urgentTask->type, URGENT); // Assert that the task type is URGENT
ASSERT_STREQ(urgentTask->name, "Urgent Task"); // Assert that the task name is correct
ASSERT_STREQ(urgentTask->description, "This is an urgent task"); // Assert that the task description is correct
ASSERT_EQ(urgentTask->priority, 1); // Assert that the task priority is correct

// Clean up
destroyTask(basicTask);
destroyTask(urgentTask);
}

TEST(TaskTest, DisplayTask) {
// Create a basic task
Task* basicTask = createTaskWithType(BASIC, 1, "Basic Task", "This is a basic task", 2);

// Capture the output of displayTask
testing::internal::CaptureStdout();
displayTask(basicTask);
std::string output = testing::internal::GetCapturedStdout();

// Assert that the output contains the expected information
EXPECT_THAT(output, testing::HasSubstr("Basic Task"));
EXPECT_THAT(output, testing::HasSubstr("This is a basic task"));
EXPECT_THAT(output, testing::HasSubstr("Priority: 2"));

// Clean up
testing::internal::CaptureStdout().Stop();
destroyTask(basicTask);
}