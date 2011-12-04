#pragma once

enum SceneType
{
    INTRO,
    MOVIEA,
    MOVIEB,
    OUTRO,
    SceneType_End
};

enum SubSceneType
{
    STARTED,
    PLAYING,
    ENDED,
    SubSceneType_End
};

enum SceneControlType
{
    SCENEPLAY,
    SCENESTOP,
    SCENEONCE,
    SceneControlType_End
};


enum EffectType
{
    NOEFFECT,
    KINECTINPUT,
    SOUNDINPUT,
    EffectType_End
};

enum EffectControlType
{
    EFFECTON,
    EFFECTOFF,
    EFFECTONCE,
    EffectControlType_End
};
