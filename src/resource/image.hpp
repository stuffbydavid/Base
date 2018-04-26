#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "resource/resource.hpp"
#include "render/color.hpp"
#include "util/data/size2d.hpp"


namespace Base
{
    class Image : public Resource
    {
      public:
        /* Loads an image from an external file. */
        EXPORT Image(const string& filename);

        /* Loads an image from internal memory. */
        EXPORT Image(const Data& data);

        /* Generates an image from a solid color. */
        EXPORT Image(Color color);

        GLuint glTexture;
        Size2Di glTextureSize;

        bool reload(const string& filename) override;

      private:
        void load(uchar* pixelData);
    };
}