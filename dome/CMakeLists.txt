
add_executable(1main 1.main.cpp)
target_link_libraries(1main Cesium)

add_executable(2click 2.click.cpp)
target_link_libraries(2click Cesium)

add_executable(3tileset 3.tileset.cpp)
target_link_libraries(3tileset Cesium)

add_executable(4clicktileset 4.clicktileset.cpp)
target_link_libraries(4clicktileset Cesium)

add_executable(5billbaord 5.billbaord.cpp)
target_link_libraries(5billbaord Cesium)

add_executable(6line 6.line.cpp)
target_link_libraries(6line Cesium)
add_executable(7Terrain 7.Terrain.cpp)
target_link_libraries(7Terrain Cesium)