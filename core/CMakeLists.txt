file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(core ${SRC_FILES} ${HEADER_FILES})
target_include_directories(core PUBLIC include/)

add_executable(core_test test/test_vec2.cc test/stack_test.cc test/queue_test.cc test/fixvector.cc test/BasicVector.cc test/SmallVector.cc test/Vector.cc)
target_link_libraries(core_test PRIVATE core 
GTest::gtest GTest::gtest_main)

if(ENABLE_PROFILING)
   target_link_libraries(core PRIVATE Tracy::TracyClient)
target_compile_definitions(core PUBLIC TRACY_ENABLE=1)
endif(ENABLE_PROFILING)

add_test(Core core_test)