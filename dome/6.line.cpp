/**
 * Created by IBM on 2021/3/3.
 */
#include <iostream>
#include <Widgets/Viewer/Viewer.h>
#include <Scene/PolylineCollection.h>
#include <Scene/Polyline.h>

class Handler {
public:
    Cesium::Viewer *viewer;
    Cesium::PolylineCollection *polylines = NULL;
    Cesium::Polyline *polyline = NULL;

    /**
     * 鼠标抬起事件
     * @param type
     * @param position
     */
    static void mouseUp(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;

        if (aggregator->polylines==NULL) {
            aggregator->polylines = new Cesium::PolylineCollection();
            aggregator->viewer->_scene->primitives()->add(aggregator->polylines);
            glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(113.00, 23.00);
            glm::dvec3 initialPosition2 = Cesium::Cartesian3::fromDegrees(113.01, 23.00);
            glm::dvec3 initialPosition3 = Cesium::Cartesian3::fromDegrees(113.01, 23.01);
            glm::dvec3 initialPosition4 = Cesium::Cartesian3::fromDegrees(113.00, 23.01);
            std::vector<glm::dvec3> position{initialPosition1, initialPosition2, initialPosition3, initialPosition4,
                                             initialPosition1};
            aggregator->polyline = aggregator->polylines->add(position);
            aggregator->polyline->width(5);
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
    double r = glm::radians(-45.0);
    Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(0.0, r, 0.0);
    glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(113.0041, 22.9950, 1000);
    viewer._scene->_camera->setView(orientation, initialPosition1);
    //创建事件
    Cesium::ScreenSpaceEventHandler *_eventHandler = new Cesium::ScreenSpaceEventHandler(handler);
    _eventHandler->setInputAction(&Handler::mouseUp, Cesium::ScreenSpaceEventType::LEFT_CLICK);//设置鼠标点击事件
    viewer.startAnimating(true);//启动opengl循环
    system("pause");
    return 0;
}
