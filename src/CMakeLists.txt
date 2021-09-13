cmake_minimum_required(VERSION 3.11)

include(../cmake/raylib.cmake)

project(game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp config.h "Screens/Aufgabe1a.h" "Screens/Aufgabe1a.cpp" "Screens/StartScreen.h" "Screens/StartScreen.cpp" "Screens/Screen.h" "Screens/Tile/Tile.h" "Screens/Tile/Tile.cpp" "Screens/Aufgabe1b.h" "Screens/Aufgabe1b.cpp" "Screens/Aufgabe1c.h" "Screens/Aufgabe1c.cpp" "Screens/Items/ItemBase.h" "Screens/Items/Cap.h" "Screens/Items/Cap.cpp" "Screens/Inventory/Inventory.h" "Screens/Aufgabe2a.h" "Screens/Aufgabe2a.cpp" "Screens/Items/ItemBase.cpp" "Screens/InventoryScreen.h" "Screens/InventoryScreen.cpp" "Screens/Actor/Char.h" "Screens/Actor/Char.cpp" "Screens/Actor/PlayerChar.h" "Screens/Actor/PlayerChar.cpp"  "Screens/Inventory/InvContainer.h" "Screens/Aufgabe2b.h" "Screens/Aufgabe2b.cpp" "Screens/Items/SoakerGun.h" "Screens/Items/SoakerGun.cpp" "Screens/Items/ArmFloats.h" "Screens/Items/ArmFloats.cpp" "Screens/Items/PoolNoodle.h" "Screens/Items/PoolNoodle.cpp" "Screens/Items/ItemInfo.h" "Screens/Items/ItemInfo.cpp" "Screens/Items/Snorkel.h" "Screens/Items/Snorkel.cpp" "Screens/Items/FloatRing.h" "Screens/Items/FloatRing.cpp" "Screens/Items/Shuriken.h" "Screens/Items/Shuriken.cpp" "Screens/Items/ItemList.h" "Screens/Aufgabe3a.h" "Screens/Aufgabe3a.cpp" "Screens/Aufgabe3b.h" "Screens/Aufgabe3b.cpp")

# Add config.h.in file
configure_file(config.h.in config.h)
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Copy assets to assets path
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_LIST_DIR}/../cmake/copy-assets.cmake"
        )
add_dependencies(${PROJECT_NAME} copy_assets)

# CPack instructions
# call e.g. cpack -G ZIP -C Debug to create a binary distribution
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${PROJECT_NAME}_Bundle")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets" DESTINATION "${PROJECT_NAME}_Bundle")