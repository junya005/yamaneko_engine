cmake_minimum_required(VERSION 3.15)
project(Template_GameDev_OpenGL CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 依存パッケージの検索
find_package(SDL2 REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)

# 実行ファイルの設定
add_executable(${PROJECT_NAME} src/Core/main.cpp)

# ターゲットにライブラリをリンク
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    glad::glad
    imgui::imgui
    assimp::assimp
    OpenGL::GL
)

target_include_directories(Template_GameDev_OpenGL PRIVATE 
    third_party/tweeny/include
)
