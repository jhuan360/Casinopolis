cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
add_subdirectory(googletest)

add_executable(DeckTests
  DeckTests.cpp 
)
add_executable(CardTests
  CardTests.cpp 
)
add_executable(SlotMachineTests
  SlotMachineTests.cpp 
)

target_link_libraries(DeckTests gtest gtest_main DeckTestsLibrary)
target_compile_options(DeckTests PRIVATE -g -O0)
target_link_libraries(CardTests gtest gtest_main CardTestsLibrary)
target_compile_options(CardTests PRIVATE -g -O0)
target_link_libraries(SlotMachineTests gtest gtest_main SlotMachineTestsLibrary)
target_compile_options(SlotMachineTests PRIVATE -g -O0)

