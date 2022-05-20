#pragma once

struct Window
{
private:
    struct Center
    {
        const short x;
        const short y;
    };
public:
    const short x = 640;
    const short y = 480;
    Center center = { (short)(x/2), (short)(y/2) };
};