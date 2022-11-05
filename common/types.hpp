#pragma once
#define alpha '_':case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':case 'y':case 'z'
#define numeric '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9'
#define alphanumeric alpha:case numeric
#define control 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:case 11:

namespace iris
{
    using u8 = unsigned char;

    using s8 = signed char;

    using u16 = unsigned short;

    using s16 = signed short;

    using u32 = unsigned int;

    using s32 = signed int;

    using f32 = float;

    using u64 = unsigned long long int;

    using s64 = signed long long int;

    using f64 = double;
}