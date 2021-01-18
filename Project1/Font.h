#pragma once
#include "Effect.h"
class Font :
    public Effect
{
public:
    Font(std::string dialog,D3DXVECTOR2 start_pos);
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void SetPosition(float x, float y);
    void SetDialog(std::string dialog);
protected:
    std::vector<char> c_char;
    D3DXVECTOR2 start_pos;
};
#define LETTER_0    16
#define LETTER_1    17
#define LETTER_2    18
#define LETTER_3    19
#define LETTER_4    20
#define LETTER_5    21
#define LETTER_6    22
#define LETTER_7    23
#define LETTER_8    24
#define LETTER_9    25
#define LETTER_A    65
#define LETTER_B    66
#define LETTER_C    67
#define LETTER_D    68
#define LETTER_E    69
#define LETTER_F    70
#define LETTER_G    71
#define LETTER_H    72
#define LETTER_I    73
#define LETTER_J    74
#define LETTER_K    75
#define LETTER_L    76
#define LETTER_M    77
#define LETTER_N    78
#define LETTER_O    79
#define LETTER_P    80
#define LETTER_Q    81
#define LETTER_R    82
#define LETTER_S    83
#define LETTER_T    84
#define LETTER_U    85
#define LETTER_V    86
#define LETTER_W    87
#define LETTER_X    88
#define LETTER_Y    89
#define LETTER_Z    90
#define BLANK_SPACE    0
#define EXCLAMATION_POINT    1