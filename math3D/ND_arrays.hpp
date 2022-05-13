#pragma once

namespace ND_arrays
{
    template<typename T>
    void delete_2p(T** ptr, short rows)
    {
        for (int r = 0; r < rows; r++)
            delete[] ptr[r];
        delete[] ptr;
    }
}