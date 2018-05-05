#include "test.hpp"


void Base::TestApp::testDraw()
{
    setRenderTarget(mainWindow);
    drawBegin();

    drawImage(&surfaces[0], { 0, 0 });
    drawImage(&surfaces[1], { 0, mainWindow->getSize().height / 2 });

    drawText("FPS: " + toString(mainWindow->getFps()), { 10, 10 }, Colors::YELLOW);

    static bool showMaps = false;
    if (keyPressed(GLFW_KEY_1))
        showMaps = !showMaps;

    if (showMaps)
    {
        int wid = 200;
        float scale = wid / (float)currentScene->lights[0]->getShadowMaps()[0]->getSize().width;
        ScreenPos debugPos = { mainWindow->getSize().width - 10 - wid, 10 };
        drawImage(currentScene->lights[0]->getShadowMaps()[0], debugPos, Colors::WHITE, 0.f, Vec2f(scale));
        drawImage(currentScene->lights[0]->getShadowMaps()[1], debugPos + Vec2i(0, wid + 15 ), Colors::WHITE, 0.f, Vec2f(scale));
        drawImage(currentScene->lights[0]->getShadowMaps()[2], debugPos + Vec2i(0, (wid + 15)* 2 ), Colors::WHITE, 0.f, Vec2f(scale));
    }
}