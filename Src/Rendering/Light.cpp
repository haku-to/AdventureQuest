#include "Light.h"
//コンストラクタ
Light::Light(IWorld* world) {
    world_ = world;
    name_ = "Light";
    tag_ = "LightTag";
}

//描画
void Light::draw()const {
    //影響範囲
    static const float ambient[]{ 0.0f, 0.0f, 0.0f, 1.0f };
    //拡散
    static const float diffuse[]{ 1.0f, 1.0f, 1.0f, 1.0f };
    //反射
    static const float specular[]{ 1.0f, 1.0f, 1.0f, 1.0f };
    //座標
    static const float position[]{ 100.0f, 100.0f, 100.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    GSvector3 shadow_map_light_position{ 0.0f, 100.0f, 0.0f };
    gsSetShadowMapLightPosition(&shadow_map_light_position);
}