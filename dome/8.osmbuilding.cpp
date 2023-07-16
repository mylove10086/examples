/**
 * Created by IBM on 2021/3/3.
 */
#include <iostream>
#include <Widgets/Viewer/Viewer.h>
#include <Scene/CreateOsmBuildings.h>
#include <Core/CreateWorldTerrain.h>



class Handler {
public:
    Cesium::Viewer *viewer;
    Cesium::Cesium3DTileset *tileset = NULL;

    /**
     * 鼠标抬起事件
     * @param type
     * @param position
     */
    static void mouseUp(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;

        if (aggregator->tileset == NULL) {
            aggregator->tileset = Cesium::CreateOsmBuildings::createOsmBuildings(false);
            aggregator->viewer->_scene->primitives()->add(aggregator->tileset);
        }
    }
};

int main(int argc, char *argv[]) {
    Handler *handler = new Handler();
    Cesium::Viewer viewer = Cesium::Viewer(500, 300);
    handler->viewer = &viewer;
    std::string url = "https://dev.virtualearth.net";
    std::string key = "AmXdbd8UeUJtaRSn7yVwyXgQlBBUqliLbHpgn2c76DfuHwAXfRrgS5qwfHU6Rhm8";
    Cesium::BingMapsImageryProvider *imageryProvider1 = new Cesium::BingMapsImageryProvider(url, key);
    viewer.imageryLayers()->addImageryProvider(imageryProvider1);
    Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(0.0, -1.5707963267948966, 0.0);
    glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(113.31990613014185,
                                                                  23.103726057649624, 3000);
    viewer._scene->_camera->setView(orientation,initialPosition1);
    //创建事件
    Cesium::ScreenSpaceEventHandler *_eventHandler = new Cesium::ScreenSpaceEventHandler(handler);
    _eventHandler->setInputAction(&Handler::mouseUp, Cesium::ScreenSpaceEventType::LEFT_CLICK);//设置鼠标点击事件
    viewer.startAnimating(true);//启动opengl循环
    system("pause");
    return 0;
}
