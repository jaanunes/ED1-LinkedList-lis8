cmake_minimum_required(VERSION 4.2)
project(ed1_linked_list_list08_cpp)

set(CMAKE_CXX_STANDARD 20)

# Inclui a pasta de cabeçalhos (.h) globalmente
include_directories(include)

# Cada questão é um executável independente
add_executable(Exer01_MiddleNode
        src/Exer01_MiddleNode.cpp
        include/LinkedList.h
        include/List.h
)

add_executable(Exer02_PalindromeList
        src/Exer02_PalindromeList.cpp
        include/LinkedList.h
        include/List.h
)

add_executable(Exer03_RemoveDuplicates
        src/Exer03_RemoveDuplicates.cpp
        include/LinkedList.h
        include/List.h
)

add_executable(Exer04_OddEvenList
        src/Exer04_OddEvenList.cpp
        include/LinkedList.h
        include/List.h
)

add_executable(Exer05_AddTwoNumbers
        src/Exer05_AddTwoNumbers.cpp
        include/LinkedList.h
        include/List.h
)
