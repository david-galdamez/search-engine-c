cmake_minimum_required(VERSION 3.22.1)
project(search_engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_executable(search_engine src/main.cpp
        src/tokenizer.cpp
        include/inverted_index.h
        src/inverted_index.cpp
        include/searcher.h
        src/searcher.cpp
        include/httplib.h)
