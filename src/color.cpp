// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Quantize the Colour-Umoria RGB palette onto the eight curses colors.
// Bright matches use A_BOLD. Black foreground is forced bold so a glyph is
// never drawn black-on-black. Animated colors (fire, lightning, glowing,
// random) flicker with their own counter and do not touch the game RNG.

#include "headers.h"

struct ColorRgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// Luminance is unused. Values match Colour-Umoria's color table.
static const ColorRgb color_palette_rgb[COLOR_PALETTE_COUNT] = {
    {255, 255, 255}, // Color_White
    {232, 232, 232}, // Color_Light_Grey_High
    {212, 212, 212}, // Color_Light_Grey_Low
    {188, 188, 188}, // Color_Medium_Grey_High
    {168, 168, 168}, // Color_Medium_Grey_Low
    {144, 144, 144}, // Color_Dark_Grey_High
    {120, 120, 120}, // Color_Dark_Grey_Low
    { 96,  96,  96}, // Color_Black
    {255,  80,  80}, // Color_Light_Red
    { 96, 255,  96}, // Color_Light_Green
    {255, 255,  96}, // Color_Light_Yellow
    { 96, 160, 255}, // Color_Light_Blue
    {255, 137,  49}, // Color_Light_Orange
    {188, 126, 255}, // Color_Light_Purple
    {224,   0,   0}, // Color_Red
    {  0, 224,   0}, // Color_Green
    {224, 224,   0}, // Color_Yellow
    {  0,  61, 213}, // Color_Blue
    {253,  88,   0}, // Color_Orange
    {121,   0, 253}, // Color_Purple
    {144,   0,   0}, // Color_Dark_Red
    {  0,  97,  62}, // Color_Dark_Green
    {144, 128,   0}, // Color_Dark_Yellow
    {  0,  32, 110}, // Color_Dark_Blue
    {152,  32,   0}, // Color_Dark_Orange
    { 84,   0, 176}, // Color_Dark_Purple
    {240, 240, 176}, // Color_Cream
    {240, 150,  20}, // Color_Amber
    {224, 208, 176}, // Color_Driftwood
    {224,  64,  96}, // Color_Coral
    {224, 192,  96}, // Color_Agate
    {255, 255, 240}, // Color_Ivory
    { 64,  64, 128}, // Color_Obsidian
    {224, 224, 208}, // Color_Bone
    {224, 192,   0}, // Color_Brass
    {176, 141,  87}, // Color_Bronze
    {150, 150, 192}, // Color_Pewter
    {208, 192,  96}, // Color_Tortoise_Shell
    {240, 240, 240}, // Color_Aluminum
    {160, 160, 176}, // Color_Cast_Iron
    {240, 240, 240}, // Color_Chromium
    {151,  92,  80}, // Color_Copper
    {209, 181,  85}, // Color_Gold
    {176, 176, 192}, // Color_Iron
    {240, 240, 240}, // Color_Magnesium
    {240, 240, 240}, // Color_Molybdenum
    {240, 240, 240}, // Color_Nickel
    {208,  96,  32}, // Color_Rusty
    {160, 180, 224}, // Color_Silver
    {224, 224, 240}, // Color_Steel
    {224, 224, 224}, // Color_Tin
    {160, 160, 176}, // Color_Titanium
    {192, 192, 192}, // Color_Tungsten
    { 96,  96,  96}, // Color_Zirconium
    {208, 224, 255}, // Color_Zinc
    {160, 112,  96}, // Color_Dirt
    {144, 144,  64}, // Color_Leprous
    {214, 181, 156}, // Color_Flesh
    {224, 255, 176}, // Color_Disenchanting
    {176, 128,  96}, // Color_Rotting
    {224, 224, 208}, // Color_Clay
    {192, 192, 192}, // Color_Stone
    {255,  80,  64}, // Color_Fire
    { 64, 192, 240}, // Color_Water
    {176, 112,  64}, // Color_Earth
    {255, 255, 255}, // Color_Air
    { 64, 224, 255}, // Color_Frost
    {240, 240, 176}, // Color_Glowing
    {160, 224, 160}, // Color_Gelatinous
    {208, 176,  64}, // Color_Umber
    {224, 160, 255}, // Color_Crystal
    {128,  96,  77}, // Color_Brown
    {240, 224, 160}, // Color_Ecru
    {224, 160,   0}, // Color_Furry
    {208, 208, 208}, // Color_Plaid
    { 96, 176,   0}, // Color_Slimy
    {210, 180, 140}, // Color_Tan
    {208, 144,  80}, // Color_Wooden
    {208, 208, 176}, // Color_Wrinkled
    {160, 255,   0}, // Color_Icky_Green
    {181, 101,  29}, // Color_Light_Brown
    {200, 200, 255}, // Color_Clear
    {128, 192, 255}, // Color_Azure
    {240, 240, 240}, // Color_Bubbling
    {176, 208, 112}, // Color_Chartreuse
    {112, 112, 128}, // Color_Cloudy
    {176,  64,  64}, // Color_Crimson
    {  0, 255, 255}, // Color_Cyan
    {176, 176, 176}, // Color_Hazy
    {112,   0, 192}, // Color_Indigo
    {224,   0, 224}, // Color_Magenta
    { 64, 144, 255}, // Color_Metallic_Blue
    {255,  32,  64}, // Color_Metallic_Red
    { 32, 255,  96}, // Color_Metallic_Green
    {144,  96, 208}, // Color_Metallic_Purple
    {240, 240, 240}, // Color_Misty
    {255, 144, 224}, // Color_Pink
    {176,  96, 128}, // Color_Puce
    {112,  96,  96}, // Color_Smoky
    {242, 133,   0}, // Color_Tangerine
    {224,   0, 240}, // Color_Violet
    {227,  66,  52}, // Color_Vermilion
    {112, 208,   0}, // Color_Alexandrite
    {176,   0, 255}, // Color_Amethyst
    {  0, 208, 196}, // Color_Aquamarine
    {  0, 176, 255}, // Color_Azurite
    {112, 176,  96}, // Color_Beryl
    {224,  80,  32}, // Color_Bloodstone
    {224, 224, 224}, // Color_Calcite
    {176,  48,   0}, // Color_Carnelian
    {220,  72, 123}, // Color_Corundum
    {132, 221, 233}, // Color_Diamond
    { 64, 208,  64}, // Color_Emerald
    {240, 255, 224}, // Color_Fluorite
    {224,   0,   0}, // Color_Garnet
    {112, 112, 128}, // Color_Granite
    {112, 176,  48}, // Color_Jade
    {208,  80,  48}, // Color_Jasper
    { 11,  25, 225}, // Color_Lapis_Lazuli
    {176,  80,  32}, // Color_Magma
    {112, 176,  64}, // Color_Malachite
    {128, 144, 144}, // Color_Marble
    {240, 240, 240}, // Color_Moonstone
    {224, 208, 208}, // Color_Onyx
    {240, 240, 240}, // Color_Pearl
    {230, 177, 170}, // Color_Quartz
    {208, 208, 208}, // Color_Quartzite
    {224,   0,  64}, // Color_Rhodonite
    {240,  64,  64}, // Color_Ruby
    { 53,   0, 255}, // Color_Sapphire
    {224, 128,  64}, // Color_Tiger_Eye
    {224, 208,  32}, // Color_Topaz
    {  0, 192, 192}, // Color_Turquoise
    {240, 224,  64}, // Color_Zircon
    {176, 112,  96}, // Color_Food
    {144, 208,   0}, // Color_Slime
    {120,  50,  32}, // Color_Leather
    {208, 224, 224}, // Color_Cord
    {240, 240, 224}, // Color_Paper
    {208, 192, 160}, // Color_Old_Parchment
    {208,  80,   0}, // Color_Apple
    { 80,  96, 112}, // Color_Oil
    { 80, 176, 255}, // Color_Magic_Light
    {144, 128, 112}, // Color_Mud
    { 96, 112,  96}, // Color_Acid
    {208, 224, 224}, // Color_Pottery
    {176,  64,  96}, // Color_Wine
    {255, 255, 224}, // Color_Mithril
    {224, 176,  96}, // Color_Aspen
    {240, 224, 208}, // Color_Balsa
    {224, 192, 128}, // Color_Banyan
    {144, 128, 108}, // Color_Birch
    {176,  96,  64}, // Color_Cedar
    {208, 192, 176}, // Color_Cottonwood
    {208, 192, 160}, // Color_Cypress
    {160, 128, 112}, // Color_Dogwood
    {224, 176, 112}, // Color_Elm
    {208, 192, 144}, // Color_Eucalyptus
    {208, 176, 144}, // Color_Hemlock
    {176, 128, 112}, // Color_Hickory
    {112, 112, 128}, // Color_Ironwood
    {240, 208,  64}, // Color_Locust
    {176, 112,  64}, // Color_Mahogany
    {224, 208, 144}, // Color_Maple
    {176, 128, 128}, // Color_Mulberry
    {224, 160, 112}, // Color_Oak
    {176, 160, 144}, // Color_Pine
    {208,  96,  64}, // Color_Redwood
    {160,  80,  64}, // Color_Rosewood
    {176, 176,  80}, // Color_Spruce
    {208, 160, 128}, // Color_Sycamore
    {240, 208, 128}, // Color_Teak
    {208, 176, 144}, // Color_Walnut
    { 96, 192, 255}, // Color_Magic_Missile
    {112, 192,   0}, // Color_Poison_Gas
    { 96,  96,  96}, // Color_Holy_Orb
    {240, 240, 176}, // Color_Lightning
    { 50,  50,  64}, // Color_Deep_Black
    {255,  80,  64}, // Color_Shadow_And_Flame
};

struct QuantizedColor {
    uint8_t fg; // 0..7, same order as COLOR_BLACK .. COLOR_WHITE
    bool bold;
};

static QuantizedColor color_quantized[COLOR_PALETTE_COUNT];
static bool color_quantized_ready = false;

static void colorQuantizePalette() {
    if (color_quantized_ready) {
        return;
    }

    // VGA normal colors, then the same colors at high intensity.
    static const int vga[16][3] = {
        {0, 0, 0},       {170, 0, 0},     {0, 170, 0},     {170, 170, 0},
        {0, 0, 170},     {170, 0, 170},   {0, 170, 170},   {170, 170, 170},
        {85, 85, 85},    {255, 85, 85},   {85, 255, 85},   {255, 255, 85},
        {85, 85, 255},   {255, 85, 255},  {85, 255, 255},  {255, 255, 255},
    };

    for (int i = 0; i < COLOR_PALETTE_COUNT; i++) {
        int best = 0;
        int best_distance = 1 << 30;
        for (int v = 0; v < 16; v++) {
            int dr = (int) color_palette_rgb[i].r - vga[v][0];
            int dg = (int) color_palette_rgb[i].g - vga[v][1];
            int db = (int) color_palette_rgb[i].b - vga[v][2];
            int distance = dr * dr + dg * dg + db * db;
            if (distance < best_distance) {
                best_distance = distance;
                best = v;
            }
        }
        color_quantized[i].fg = (uint8_t) (best & 7);
        color_quantized[i].bold = best >= 8;
        // COLOR_BLACK on a black background disappears. Bold black is grey.
        if (color_quantized[i].fg == 0) {
            color_quantized[i].bold = true;
        }
    }
    color_quantized_ready = true;
}

// Visual flicker only. Independent of the Moria random-number stream.
static int colorFlicker(int max_inclusive) {
    static uint32_t state = 0xC0FFEEu;
    state = state * 1664525u + 1013904223u;
    return (int) (state % (uint32_t) max_inclusive) + 1;
}

static int colorResolve(int color) {
    if (color == Color_Random) {
        return (colorFlicker(5) == 1) ? (colorFlicker(6) - 1) : (colorFlicker(8) + 7);
    }
    if (color == Color_Fire) {
        static const int fire_colors[5] = {Color_Vermilion, Color_Orange, Color_Red, Color_Light_Red, Color_Fire};
        return fire_colors[colorFlicker(5) - 1];
    }
    if (color == Color_Shadow_And_Flame) {
        static const int fire_colors[7] = {Color_Vermilion, Color_Orange, Color_Red, Color_Light_Red, Color_Fire, Color_Deep_Black, Color_Deep_Black};
        return fire_colors[colorFlicker(7) - 1];
    }
    if (color == Color_Glowing) {
        return (colorFlicker(2) == 1) ? Color_Glowing : Color_White;
    }
    if (color == Color_Lightning) {
        static const int cloud_colors[6] = {Color_Lightning, Color_Deep_Black, Color_Deep_Black, Color_Deep_Black, Color_Cloudy, Color_Cloudy};
        return cloud_colors[colorFlicker(6) - 1];
    }
    return color;
}

bool colorLookup(int color, int &fg, bool &bold) {
    colorQuantizePalette();
    if (color < 0) {
        return false;
    }
    color = colorResolve(color);
    if (color < 0 || color >= COLOR_PALETTE_COUNT) {
        color = Color_White;
    }
    fg = color_quantized[color].fg;
    bold = color_quantized[color].bold;
    return true;
}
