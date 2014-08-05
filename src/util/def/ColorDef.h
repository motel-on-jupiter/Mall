// Refered to color name of HTML (http://www.w3.org/TR/REC-html40/types.html#h-6.5)

#ifdef COLOR_DEF

COLOR_DEF(Black,   0x00, 0x00, 0x00)
COLOR_DEF(Silver,  0xC0, 0xC0, 0xC0)
COLOR_DEF(Gray,    0x80, 0x80, 0x80)
COLOR_DEF(White,   0xFF, 0xFF, 0xFF)
COLOR_DEF(Maroon,  0x80, 0x00, 0x00)
COLOR_DEF(Red,     0xFF, 0x00, 0x00)
COLOR_DEF(Purple,  0x80, 0x00, 0x80)
COLOR_DEF(Fuchsia, 0xFF, 0x00, 0xFF)
COLOR_DEF(Green,   0x00, 0x80, 0x00)
COLOR_DEF(Lime,    0x00, 0xFF, 0x00)
COLOR_DEF(Olive,   0x80, 0x80, 0x00)
COLOR_DEF(Yellow,  0xFF, 0xFF, 0x00)
COLOR_DEF(Navy,    0x00, 0x00, 0x80)
COLOR_DEF(Blue,    0x00, 0x00, 0xFF)
COLOR_DEF(Teal,    0x00, 0x80, 0x80)
COLOR_DEF(Aqua,    0x00, 0xFF, 0xFF)

#else

#ifdef GLM_COLOR

#ifndef COLORDEF_GLMCOLOR_H_
#define COLORDEF_GLMCOLOR_H_

#define COLOR_DEF( _name, _r, _g, _b) \
static const glm::vec3 k##_name##Color = glm::vec3(static_cast<float>(_r) / 255.0f, \
                                                   static_cast<float>(_g) / 255.0f, \
                                                   static_cast<float>(_b) / 255.0f);
#include "util/def/ColorDef.h"
#undef COLOR_DEF

#endif /* COLORDEF_GLMCOLOR_H_ */

#endif /* GLM_COLOR */

#endif /* COLOR_DEF */
