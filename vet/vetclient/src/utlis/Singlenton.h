#pragma once

template <typename T>
struct Singlenton
{
    static T& getInstance()
    {
        static T value;
        return value;
    }
};
