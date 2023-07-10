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
    Cesium::Cesium3DTileFeature *feautre = NULL;
    std::vector<std::string> attrname;

    /**
    * 鼠标右键加载tileset模型
    * @param handler
    * @param event 鼠标指针位置，屏幕坐标，与ceisum中的基本一致
    */
    static void mouseUp(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;
        if (aggregator->tileset == NULL) {
            std::string url = "../data/BatchedColors/tileset.json";
            aggregator->tileset = new Cesium::Cesium3DTileset(url);
            aggregator->viewer->_scene->primitives()->add(aggregator->tileset);
            Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(0.0, -1.5707963267948966, 0.0);
            //因为已经有glm库使用没有写cesium的Cartesian3，但是Cartesian3的很多方法是写了的，也可以用glm库提供的
            glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(-75.60908200128681, 40.04159868719826, 1000);
            aggregator->viewer->_scene->_camera->setView(orientation, initialPosition1);

        }
    }

    static void onLeftClick(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;
        glm::dvec2 position = event->position;// 获取鼠标屏幕位置
        //获取选中要素
        Cesium::Feature *feature = aggregator->viewer->_scene->pick(position);
        if (feature == NULL) {
            if (aggregator->feautre != NULL) {
                glm::dvec4 co(1.0, 1.0, 1.0, 1.0);
                aggregator->feautre->color(co);//取消高亮
            }
        } else {
            if (feature->instanceof("Cesium3DTileFeature")) {
                Cesium::Cesium3DTileFeature *tfeautre = (Cesium::Cesium3DTileFeature *) feature;// 强制类型转换
                aggregator->feautre = tfeautre;
                glm::dvec4 co(1.5, 0.0, 0.0, 0.5);
                tfeautre->color(co);//高亮模型
                aggregator->attrname.clear();
                tfeautre->getPropertyNames(&aggregator->attrname);
                std::string id = tfeautre->getProperty("batchId");
                for (int i = 0; i < aggregator->attrname.size(); i++) {
                    std::cout << aggregator->attrname[i] << std::endl;//打印属性
                }
            }
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
    _eventHandler->setInputAction(&Handler::onLeftClick, Cesium::ScreenSpaceEventType::LEFT_CLICK);
    viewer.startAnimating(true);//启动opengl循环
    system("pause");
    return 0;
}
