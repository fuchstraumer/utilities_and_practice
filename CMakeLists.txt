CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(InterviewPractice)

ADD_EXECUTABLE(InterviewPractice
    "main.cpp"
    "tests/lru_cache_test.cpp"
    "tests/rle_iterator_test.cpp"
    "tests/circular_deque_test.cpp"
    "tests/forward_list_test.cpp"
    "tests/stack_test.cpp"
    "tests/text_trie_test.cpp"
    "problems/stack_exercises.hpp"
)

#TARGET_LINK_LIBRARIES(InterviewPractice PRIVATE pthread)
#TARGET_COMPILE_OPTIONS(InterviewPractice PRIVATE -m64)
TARGET_COMPILE_DEFINITIONS(InterviewPractice PRIVATE "GLIBCXX_DEBUG")
TARGET_INCLUDE_DIRECTORIES(InterviewPractice PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/doctest/doctest"
    "${CMAKE_CURRENT_SOURCE_DIR}")
SET_TARGET_PROPERTIES(InterviewPractice PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
