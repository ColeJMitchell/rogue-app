cmake_minimum_required(VERSION 3.22)
project(rogue-app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(model)
include_directories(googletest googletest/include googletest/include/gtest)
include_directories(tools)
include_directories(test)
add_executable(unittests 
        googletest/src/gtest-all.cc
        test/unittest.cpp
        tools/Configuration.h
        tools/Configuration.cpp
        tools/Log.h
        tools/Log.cpp
        dbtools/Update.cpp
        dbtools/Update.h
        dbtools/Delete.cpp
        dbtools/Delete.h
        dbtools/Insert.cpp
        dbtools/Insert.h
        dbtools/Select.cpp
        dbtools/Select.h
        model/Game.cpp
        model/Game.h
        model/Player.cpp
        model/Player.h
        model/Coordinate.cpp
        model/Coordinate.h
        model/Room.cpp
        model/Room.h
        model/Model.cpp
        model/Model.h
        model/Hallway.cpp
        model/Hallway.h
        model/HallwayCoor.cpp
        model/HallwayCoor.h
)
target_link_libraries(unittests sqlite3)


include_directories(dbtools)
add_executable(rogue 
        TUI/rogue.cpp
        model/Game.cpp
        model/Game.h
        model/Model.cpp
        model/Model.h
        model/Player.cpp
        model/Player.h
        dbtools/Update.cpp
        dbtools/Update.h
        dbtools/Delete.cpp
        dbtools/Delete.h
        dbtools/Insert.cpp
        dbtools/Insert.h
        dbtools/Select.cpp
        dbtools/Select.h
        model/Coordinate.cpp
        model/Coordinate.h
        model/Room.cpp
        model/Room.h
        model/Hallway.cpp
        model/Hallway.h
        model/HallwayCoor.cpp
        model/HallwayCoor.h
        tools/Log.cpp
        tools/Log.h
        tools/Configuration.cpp
        tools/Configuration.h
)

target_link_libraries(rogue sqlite3)
target_link_libraries(rogue ncurses)