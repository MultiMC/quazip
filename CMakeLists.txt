cmake_minimum_required(VERSION 3.1)

project(Launcher_quazip)

#### LIBRARY ####
find_package(ZLIB REQUIRED)
find_package(Qt5Core REQUIRED)

set(QUAZIP_SRC
	quazip/crypt.h
	quazip/ioapi.h
	quazip/JlCompress.cpp
	quazip/JlCompress.h
	quazip/qioapi.cpp
	quazip/quaadler32.cpp
	quazip/quaadler32.h
	quazip/quachecksum32.h
	quazip/quacrc32.cpp
	quazip/quacrc32.h
	quazip/quagzipfile.cpp
	quazip/quagzipfile.h
	quazip/quaziodevice.cpp
	quazip/quaziodevice.h
	quazip/quazip.cpp
	quazip/quazip.h
	quazip/quazip_global.h
	quazip/quazipdir.cpp
	quazip/quazipdir.h
	quazip/quazipfile.cpp
	quazip/quazipfile.h
	quazip/quazipfileinfo.cpp
	quazip/quazipfileinfo.h
	quazip/quazipnewinfo.cpp
	quazip/quazipnewinfo.h
	quazip/unzip.c
	quazip/unzip.h
	quazip/zip.c
	quazip/zip.h
)

if (Qt5_POSITION_INDEPENDENT_CODE)
    SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

add_library(Launcher_quazip SHARED ${QUAZIP_SRC})
target_include_directories(Launcher_quazip PUBLIC "quazip" "${CMAKE_CURRENT_BINARY_DIR}" PRIVATE ${ZLIB_INCLUDE_DIRS})
target_link_libraries(Launcher_quazip Qt5::Core ${ZLIB_LIBRARIES})
target_compile_definitions(Launcher_quazip PRIVATE "-DQUAZIP_BUILD")
set_target_properties(Launcher_quazip PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)

# Install it
install(
	TARGETS Launcher_quazip
	RUNTIME DESTINATION ${LIBRARY_DEST_DIR}
	LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
)

#### UNIT TESTS ####
find_package(Qt5Network REQUIRED)
find_package(Qt5Test REQUIRED)

set(QUAZIP_TEST_SRC
	qztest/qztest.cpp
	qztest/qztest.h
	qztest/testjlcompress.cpp
	qztest/testjlcompress.h
	qztest/testquachecksum32.cpp
	qztest/testquachecksum32.h
	qztest/testquagzipfile.cpp
	qztest/testquagzipfile.h
	qztest/testquaziodevice.cpp
	qztest/testquaziodevice.h
	qztest/testquazip.cpp
	qztest/testquazip.h
	qztest/testquazipdir.cpp
	qztest/testquazipdir.h
	qztest/testquazipfile.cpp
	qztest/testquazipfile.h
	qztest/testquazipfileinfo.cpp
	qztest/testquazipfileinfo.h
	qztest/testquazipnewinfo.cpp
	qztest/testquazipnewinfo.h
)

add_executable(Launcher_quazip_test ${QUAZIP_TEST_SRC})
target_link_libraries(Launcher_quazip_test Launcher_quazip Qt5::Network Qt5::Test)
add_test(NAME quazip_testsuite COMMAND Launcher_quazip_test)
