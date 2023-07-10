/**
 * Created by IBM on 2021/3/3.
 */
#include <iostream>
#include <Widgets/Viewer/Viewer.h>

int main(int argc, char *argv[]) {
    Cesium::Viewer viewer = Cesium::Viewer(500, 300);
    std::string url = "https://dev.virtualearth.net";
    std::string key = "AmXdbd8UeUJtaRSn7yVwyXgQlBBUqliLbHpgn2c76DfuHwAXfRrgS5qwfHU6Rhm8";
    Cesium::BingMapsImageryProvider *imageryProvider1 = new Cesium::BingMapsImageryProvider(url, key);
    viewer.imageryLayers()->addImageryProvider(imageryProvider1);
    viewer.startAnimating(true);//启动opengl循环
    system("pause");
    return 0;
}
