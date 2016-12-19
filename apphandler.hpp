#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "util/math/mathfunc.hpp"
#include "file/resourcehandler.hpp"
#include "render/color.hpp"
#include "render/font.hpp"
#include "render/image.hpp"
#include "render/shader.hpp"
#include "window/window.hpp"

#define DRAWING_FONT        "fonts/opensans.ttf"
#define DRAWING_FONT_BOLD   "fonts/opensansbold.ttf"
#define DRAWING_SHADER      "shaders/texture.glsl"


namespace Base
{
    
    /* Handles an OpenGL application. Used as a parent for the project class. */
    class AppHandler
    {
        protected:

            /* Setup OpenGL and load resources. */
            AppHandler();

            /* Called by the main window. Implemented by the child. */
            virtual void loopEvent() = 0;
            virtual void mouseEvent() = 0;
            virtual void keyEvent() = 0;
            virtual void resizeEvent() = 0;

            /* Opens the window and starts the window loop. */
            void launch();

        public:

            // Window
            Window* mainWindow;

            // Resources
            ResourceHandler* resourceHandler;
            Font* drawingFont;
            Font* drawingFontBold;
            Shader* drawingShader;
            float drawingAlpha = 1.f;
            Image* solidColor;
    };

}

extern Base::AppHandler* appHandler;