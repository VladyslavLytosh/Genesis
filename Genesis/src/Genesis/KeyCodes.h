#pragma once

namespace Genesis
{
    using KeyCode = uint16_t;

    namespace Key
    {
        // KeyCodes is similar to glfw3.h
        enum : uint16_t
        {
            /* Printable keys */
            Space = 32,
            Apostrophe = 39, /* ' */
            Comma = 44,      /* , */
            Minus = 45,      /* - */
            Period = 46,     /* . */
            Slash = 47,      /* / */
            N0 = 48,
            N1 = 49,
            N2 = 50,
            N3 = 51,
            N4 = 52,
            N5 = 53,
            N6 = 54,
            N7 = 55,
            N8 = 56,
            N9 = 57,
            Semicolon = 59, /* ; */
            Equal = 61,     /* = */

            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,

            Left_bracket = 91,  /* [ */
            Backslash = 92,     /* \ */
            Right_bracket = 93, /* ] */
            Grave_accent = 96,  /* ` */
            World_1 = 161,      /* non-US #1 */
            World_2 = 162,      /* non-US #2 */

            /* Function keys */
            Escape = 256,
            Enter = 257,
            Tab = 258,
            Backspace = 259,
            Insert = 260,
            Delete = 261,
            Right = 262,
            Left = 263,
            Down = 264,
            Up = 265,
            Page_up = 266,
            Page_down = 267,
            Home = 268,
            End = 269,
            Caps_lock = 280,
            Scroll_lock = 281,
            Num_lock = 282,
            Print_screen = 283,
            Pause = 284,
            F1 = 290,
            F2 = 291,
            F3 = 292,
            F4 = 293,
            F5 = 294,
            F6 = 295,
            F7 = 296,
            F8 = 297,
            F9 = 298,
            F10 = 299,
            F11 = 300,
            F12 = 301,
            F13 = 302,
            F14 = 303,
            F15 = 304,
            F16 = 305,
            F17 = 306,
            F18 = 307,
            F19 = 308,
            F20 = 309,
            F21 = 310,
            F22 = 311,
            F23 = 312,
            F24 = 313,
            F25 = 314,

            /* Keypad keys */
            KP0 = 320,
            KP1 = 321,
            KP2 = 322,
            KP3 = 323,
            KP4 = 324,
            KP5 = 325,
            KP6 = 326,
            KP7 = 327,
            KP8 = 328,
            KP9 = 329,
            KPDecimal = 330,
            KPDivide = 331,
            KPMultiply = 332,
            KPSubtract = 333,
            KPAdd = 334,
            KPEnter = 335,
            KPEqual = 336,
            Left_Shift = 340,
            Left_Control = 341,
            Left_Alt = 342,
            Left_Super = 343,
            Right_Shift = 344,
            Right_Control = 345,
            Right_Alt = 346,
            Right_Super = 347,
            Menu = 34
        };
    }  // namespace Key
}  // namespace Genesis