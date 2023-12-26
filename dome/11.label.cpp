/**
 * Created by IBM on 2021/3/3.
 */
#include <iostream>
#include <Widgets/Viewer/Viewer.h>
#include <Scene/LabelCollection.h>
#include <Scene/Label.h>


class Handler {
public:
    Cesium::Viewer *viewer;
    Cesium::LabelCollection *labels = NULL;
    Cesium::Label *text = NULL;
    /**
     * 鼠标抬起事件
     * @param type
     * @param position
     */
    static void mouseUp(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;

        if (aggregator->labels == NULL) {
            // 创建BillboardCollection
            aggregator->labels = new Cesium::LabelCollection(NULL);
            aggregator->viewer->_scene->primitives()->add(aggregator->labels);
        }
        glm::dvec2 position = event->position;//鼠标屏幕位置
        glm::dvec3 coor, carthposition;
        //转换成经纬度，与cesium基本一致
        aggregator->viewer->_scene->_camera->pickEllipsoid(position,
                                                           aggregator->viewer->_scene->_globe->_ellipsoid,
                                                           &coor);
        aggregator->viewer->_scene->_globe->_ellipsoid->cartesianToCartographic(coor, &carthposition);
        double longitude = Cesium::CesiumMath::toDegrees(carthposition.x);
        double latitude = Cesium::CesiumMath::toDegrees(carthposition.y);
        //添加billboard
        glm::dvec3 initialPosition2 = Cesium::Cartesian3::fromDegrees(longitude, latitude);
        aggregator->labels->add(initialPosition2, "../data/home.png");

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
    double r = glm::radians(-90.0);
    Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(0.0, r, 0.0);
    glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(113.0041, 22.9950, 50000);
    viewer._scene->_camera->setView(orientation, initialPosition1);
    //创建事件
    Cesium::ScreenSpaceEventHandler *_eventHandler = new Cesium::ScreenSpaceEventHandler(handler);
    _eventHandler->setInputAction(&Handler::mouseUp, Cesium::ScreenSpaceEventType::LEFT_CLICK);//设置鼠标点击事件
    viewer.startAnimating(true);//启动opengl循环
    system("pause");
    return 0;
}