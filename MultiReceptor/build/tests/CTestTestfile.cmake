# CMake generated Testfile for 
# Source directory: /home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests
# Build directory: /home/mahonri/Desktop/OOP_With_C/MultiReceptor/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[RunUnitTestMultireceptor]=] "UnitTestMultireceptor")
set_tests_properties([=[RunUnitTestMultireceptor]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests/CMakeLists.txt;11;add_test;/home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests/CMakeLists.txt;0;")
add_test([=[RunUnitTestMultireceptorIntegration]=] "/home/mahonri/Desktop/OOP_With_C/MultiReceptor/build/tests/UnitTestMultireceptorIntegration")
set_tests_properties([=[RunUnitTestMultireceptorIntegration]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests/CMakeLists.txt;12;add_test;/home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests/CMakeLists.txt;0;")
add_test([=[RunUnitTestMultireceptorPerformance]=] "/home/mahonri/Desktop/OOP_With_C/MultiReceptor/build/tests/UnitTestMultireceptorPerformance")
set_tests_properties([=[RunUnitTestMultireceptorPerformance]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests/CMakeLists.txt;13;add_test;/home/mahonri/Desktop/OOP_With_C/MultiReceptor/tests/CMakeLists.txt;0;")
