#include "common.hpp"
#include "scene/scene.hpp"
#include "render/renderfunc.hpp"
#include "render/drawfunc.hpp"
#include "apphandler.hpp"


EXPORT void Base::Scene::render(Shader* shader, Camera* camera, Camera* cullCamera)
{
    shader->select();
    drawClear(background);

    if (!camera)
        camera = this->camera;

    if (!cullCamera)
        cullCamera = camera;

    for (Object* obj : objects) 
    {
        if (cullCamera->boxVisible(obj->getBoundingBox()))
            obj->render(shader, Mat4f::identity(), camera->getViewProjection());
    }
}


EXPORT Base::Object* Base::Scene::findObject(const string& name) const
{
    auto f = objectNames.find(name);
    return (objectNames.find(name) == objectNames.end()) ? nullptr : f->second;
}