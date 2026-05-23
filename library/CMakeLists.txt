cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/model/Client.cpp
        include/model/Client.h
        include/typedefs.h
        src/model/Car.cpp
        include/model/Car.h
        src/model/PoweredBy.cpp
        include/model/PoweredBy.h
)

# Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
#trzeba dodac pozniej testy tj. byly w warsztatach