#pragma once
#include "Singleton.h"
class Variables :
    public Singleton<Variables>
{
    friend class Singleton<Variables>;
    Variables() = default;
    ~Variables() = default;
    Variables(const Variables& other) = delete;
    Variables& operator=(const Variables& other) = delete;

public:
    std::string Player1TexId;
    std::string Player2TexId;
    
    std::string BackGroundTexId = "graphics/background.png";

    PlayMode SelectedPlayMode;

};

#define VAR (Variables::Instance())

