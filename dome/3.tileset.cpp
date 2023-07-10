/**
 * Created by IBM on 2021/3/3.
 */
#include <iostream>
#include <Widgets/Viewer/Viewer.h>
#include <Scene/Cesium3DTileset.h>

class Handler {
public:
    Cesium::Viewer *viewer;
    Cesium::Cesium3DTileset *tileset = NULL;

    bool bol;
   /**
    * 鼠标右键加载tileset模型
    * @param handler
    * @param event 鼠标指针位置，屏幕坐标，与ceisum中的基本一致
    */
    static void mouseUp(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;
        if (aggregator->tileset == NULL) {
            std::string url="../data/BatchedColors/tileset.json";
            aggregator->tileset = new Cesium::Cesium3DTileset(url);
            //viewer.zoomTo(tileset);
            aggregator->viewer->_scene->primitives()->add(aggregator->tileset);
            Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(0.0, -1.5707963267948966, 0.0);
            //因为已经有glm库使用没有写cesium的Cartesian3，但是Cartesian3的很多方法是写了的，也可以用glm库提供的
            glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(-75.60908200128681, 40.04159868719826, 1000);
            aggregator->viewer->_scene->_camera->setView(orientation,initialPosition1);
            // 或者
            //aggregator->viewer->zoomTo( aggregator->tileset);
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
    //创建事件
    Cesium::ScreenSpaceEventHandler *_eventHandler = new Cesium::ScreenSpaceEventHandler(handler);
    _eventHandler->setInputAction(&Handler::mouseUp, Cesium::ScreenSpaceEventType::RIGHT_CLICK);//设置鼠标点击事件
    viewer.startAnimating(true);//启动opengl循环
    system("pause");
    return 0;
}
