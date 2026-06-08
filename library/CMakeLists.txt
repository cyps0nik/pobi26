cmake_minimum_required(VERSION 3.5)
project(Library)

set(SOURCE_FILES
        src/model/Client.cpp
        include/model/Client.h
        include/typedefs.h
        src/model/Car.cpp
        include/model/Car.h
        include/model/PoweredBy.h
        src/model/Engine.cpp
        include/model/Engine.h
        src/model/Accumulator.cpp
        include/model/Accumulator.h
        src/model/naprawa/Repair.cpp
        include/model/naprawa/Repair.h
        src/model/naprawa/Service.cpp
        include/model/naprawa/Service.h
        src/model/naprawa/DiagnosticService.cpp
        include/model/naprawa/DiagnosticService.h
        src/model/naprawa/TimeBasedService.cpp
        include/model/naprawa/TimeBasedService.h
        src/model/naprawa/PartRegenaration.cpp
        include/model/naprawa/PartRegenaration.h
        src/model/naprawa/NewPartReplacement.cpp
        include/model/naprawa/NewPartReplacement.h
        #Repa
#        src/StorageContainer.cpp
#        include/StorageContainer.h
#        src/repositories/ClientRepository.cpp
#        include/repositories/ClientRepository.h
#        src/repositories/CarRepository.cpp
#        include/repositories/CarRepository.h
#        src/repositories/MechanicRepository.cpp
#        include/repositories/MechanicRepository.h
#        src/repositories/RepairRepository.cpp
#        include/repositories/RepairRepository.h
#        src/repositories/ResourceRepository.cpp
#        include/repositories/ResourceRepository.h
        #Menagerowe
#        src/managers/ClientManager.cpp
#        include/managers/ClientManager.h
#        src/managers/CarManager.cpp
#        include/managers/CarManager.h
#        src/managers/MechanicManager.cpp
#        include/managers/MechanicManager.h
#        src/managers/ResourceManager.cpp
#        include/managers/ResourceManager.h
#        src/managers/RepairManager.cpp
#        include/managers/RepairManager.h
)

# Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

enable_testing()

#dodanie biblioteki boost:date_time
find_package (Boost 1.80.0 COMPONENTS "unit_test_framework" "date_time" "serialization" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/confi.cpp
        test/ClientTest.cpp
        test/CarTest.cpp
        test/RepositoryTest.cpp
) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTester ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_SERIALIZATION_LIBRARY}
)

#dodaj test LibraryTest. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest LibraryTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

#Aby raport testów był szczegółowo wypisany na konsolę, można dodać własny cel budowy o nazwie na przykłąd check (uruchamiany przez make check) w postaci:

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})