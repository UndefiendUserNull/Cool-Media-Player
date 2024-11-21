#pragma once

// Stolen

namespace Utils
{
    template<typename T>
    T trunc_decs(const T& f, int decs)
    {
        int i1 = floor(f);
        T rmnd = f - i1;
        int i2 = static_cast<int> (rmnd * pow(10, decs));
        T f1 = i2 / pow(10, decs);

        return i1 + f1;
    }
}
