cmake_minimum_required(VERSION 3.15)
project(OpenWorldProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# C kaynak dosyaları
file(GLOB C_SOURCES "src/c/*.c")
add_library(c_core STATIC ${C_SOURCES})
target_include_directories(c_core PUBLIC include)

# C++ kaynak dosyaları (Oyun Motoru Çekirdeği)
file(GLOB CPP_SOURCES "src/cpp/*.cpp")
add_executable(open_world_engine ${CPP_SOURCES})
target_link_libraries(open_world_engine c_core)
target_include_directories(open_world_engine PUBLIC include)

# C# Projesi için referans (ayrı build edilecek)
# dotnet build src/cs/OpenWorldLogic.csproj

message(STATUS "Open World Project yapısı hazırlandı!")
message(STATUS "C, C++ derlemesi için: cmake -B build && cmake --build build")
message(STATUS "C# projeleri ayrı olarak dotnet ile derlenmelidir.")
