cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 98)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCE_FILES main.cpp Server.cpp Server.h Command.h StartCommand.cpp StartCommand.h JoinCommand.cpp JoinCommand.h CloseCommand.cpp CloseCommand.h PlayCommand.cpp PlayCommand.h GetGamesListCommand.cpp GetGamesListCommand.h CommandsManager.cpp CommandsManager.h Game_Room.cpp Game_Room.h GameManager.cpp GameManager.h CloseTheGames.cpp CloseTheGames.h)
add_executable(server ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} pthread)
