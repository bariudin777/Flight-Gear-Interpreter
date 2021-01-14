cmake_minimum_required(VERSION 3.13)
project(Project)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 main.cpp Command.h
        ConnectCommand.cpp ConnectCommand.h
        OpenServerCommand.cpp OpenServerCommand.h CheckClass.cpp CheckClass.h DataReaderServer.cpp DataReaderServer.h
        ConditionParser.h ConditionParser.cpp IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h
        BinaryExpression.h Command.h DefineVarCommand.cpp DefineVarCommand.h Div.h
        Expression.h Minus.h Mult.h Number.h Plus.h ShuntingYard.cpp ShuntingYard.h SymbolTable.cpp SymbolTable.h
        User.cpp User.h SleepCommand.cpp SleepCommand.h PrintCommand.cpp PrintCommand.h EntercCommand.cpp EntercCommand.h ExitCommand.cpp ExitCommand.h RunCommand.cpp RunCommand.h)