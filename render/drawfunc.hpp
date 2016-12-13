#pragma once

#include "render/color.hpp"
#include "render/image.hpp"
#include "render/font.hpp"
#include "util/stringfunc.hpp"
#include "window/screenpos.hpp"
#include "window/screenarea.hpp"


namespace Base
{

    /* Text alignment. */
    enum TextAlignX {
        LEFT,
        CENTER,
        RIGHT
    };

    enum TextAlignY {
        TOP,
        MIDDLE,
        BOTTOM
    };

    /* Begins drawing. */
    void drawBegin();

    /* Draws a piece of text using the drawing font. */
    void drawText(string text, ScreenPos pos, Color color = COLOR_BLACK, Font* font = nullptr);
    void drawTextAligned(string text, ScreenPos pos, TextAlignX alignX = LEFT, TextAlignY alignY = TOP, Color color = COLOR_BLACK, Font* font = nullptr);
    void drawTextSelected(string text, ScreenPos pos, int startIndex, int endIndex, Color color = COLOR_BLACK, Color selectColor = COLOR_BLUE, Color selectTextColor = COLOR_WHITE, Font* font = nullptr);

    /* Draws an image. */
    void drawImage(string name, ScreenPos pos, Color color = COLOR_WHITE, float rotation = 0.f, Vec2 scale = { 1.f, 1.f });
    void drawImage(Image* image, ScreenPos pos, Color color = COLOR_WHITE, float rotation = 0.f, Vec2 scale = { 1.f, 1.f });
    void drawSubImage(string image, int subImage, ScreenPos pos, Color color = COLOR_WHITE, float rotation = 0.f, Vec2 scale = { 1.f, 1.f });
    void drawSubImage(Image* image, int subImage, ScreenPos pos, Color color = COLOR_WHITE, float rotation = 0.f, Vec2 scale = { 1.f, 1.f });

    /* Draws a colored box. */
    void drawBox(ScreenArea box, Color color, bool outline = false, int outlineThickness = 1);
    void drawBoxEdges(ScreenArea box, Color color, string edgeImage, bool edgeTopLeft = true, bool edgeTopRight = true, bool edgeBottomRight = true, bool edgeBottomLeft = true);
    
    /* Draws a line */
    void drawLine(ScreenPos start, ScreenPos end, Color color, int thickness = 1);
    
}