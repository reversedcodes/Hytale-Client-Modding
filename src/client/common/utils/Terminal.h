#pragma once

class Terminal {
public:
    static Terminal &GetInstance()
    {
        static Terminal instance;
        return instance;
    };

    static void Open();
    static void Close();
};