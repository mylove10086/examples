/**
 * Created by IBM on 2021/3/3.
 */
#include <iostream>
#include <Widgets/Viewer/Viewer.h>
#include <Scene/ArcGisMapServerImageryProvider.h>
#include <Core/CesiumTerrainProvider.h>
#include <Core/EllipsoidTerrainProvider.h>
#include <DataSources/Entity.h>

class Handler :  public Cesium::Object {

public:
    Cesium::Viewer *viewer;
    bool bol;

    /**
     * 鼠标抬起事件
     * @param type
     * @param position
     */
    static void mouseUp(void *handler, Cesium::ScreenEvent *event) {
        Handler *aggregator = (Handler *) handler;
        //std::string str = Cesium::OpenGL::getString(Cesium::WebGLConstants::VERSION);

        if (aggregator->bol) {
            aggregator->viewer->scene()->globe()->tileProvider->_debug->wireframe = true;
            aggregator->bol = false;
        } else {
            aggregator->viewer->scene()->globe()->tileProvider->_debug->wireframe = false;
            aggregator->bol = true;
        }
    }

};

class TestViewer {

public:
    Cesium::Viewer viewer = Cesium::Viewer(500, 300);
    //Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(6.241352842889025,-0.1223072462524295, 6.283083057311895);

    Cesium::TileCoordinatesImageryProvider *imageryProvider = NULL;
    Cesium::ImageryProvider *imageryProvider1 = NULL;
    Cesium::ImageryProvider *imageryProvider2 = NULL;
    Cesium::ScreenSpaceEventHandler *_eventHandler = NULL;

    Handler *handler = NULL;

    void startOpenGL() {
        handler = new Handler();
        handler->viewer = &viewer;
        if (this->imageryProvider == NULL) {
            this->imageryProvider = new Cesium::TileCoordinatesImageryProvider();

            std::string url = "https://services.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer";


            url = "../Assets/NaturalEarthII/{z}/{x}/{reverseY}.jpg";
            std::map<std::string, std::string> tv;
            tv["level"] = "z";
            tv["x"] = "x";
            tv["y"] = "reverseY";
            this->imageryProvider2 = new Cesium::TileMapServiceImageryProvider(url, tv);
            //this->imageryProvider1 = new Cesium::ArcGisMapServerImageryProvider(url);


            url = "https://dev.virtualearth.net";
            std::string key = "AmXdbd8UeUJtaRSn7yVwyXgQlBBUqliLbHpgn2c76DfuHwAXfRrgS5qwfHU6Rhm8";
            this->imageryProvider1 = new Cesium::BingMapsImageryProvider(url, key);

        }
        //viewer.imageryLayers()->addImageryProvider(this->imageryProvider);
        //viewer.imageryLayers()->addImageryProvider(this->imageryProvider2);
        viewer.imageryLayers()->addImageryProvider(this->imageryProvider1);
        double r = glm::radians(-90.0);
        Cesium::HeadingPitchRoll *orientation = new Cesium::HeadingPitchRoll(0.0, r, 0.0);
        glm::dvec3 initialPosition1 = Cesium::Cartesian3::fromDegrees(113.00, 23.00, 10000);
        /*initialPosition1=glm::dvec3 (956421.88504666707
                ,-20107485.354938533
                , 9492815.8520134091);*/
        //initialPosition1 = Cesium::Cartesian3::fromDegrees(-75.60908200128681, 40.04159868719826, 1000);

        viewer._scene->_camera->setView(orientation, initialPosition1
                //glm::dvec3(-3022390.857964606, -28194233.183663104, 7010326.7980251135)
                //glm::dvec3(-2357020.086372478, 5389917.561145983,2456263.1017063796)
                //glm::dvec3(-1339433.377791486, 5348863.8514741519, 2497559.3661723444)

        );
        //viewer.terrainProvider(new Cesium::CesiumTerrainProvider("D:/image/dem"));
        //viewer.terrainProvider(new Cesium::EllipsoidTerrainProvider());

        //glm::dvec3(-134.9536757244934, 6382221.456967456, 21.89334596378623));

        _eventHandler = new Cesium::ScreenSpaceEventHandler(handler);

        this->_eventHandler->setInputAction(&Handler::mouseUp,
                                            Cesium::ScreenSpaceEventType::RIGHT_UP);//设置鼠标移的函数

        viewer.startAnimating(true);

    }

};


int main(int argc, char *argv[]) {
    TestViewer t;
    t.startOpenGL();

    system("pause");
    return 0;
}
