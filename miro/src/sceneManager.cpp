#include "sceneManager.h"

void SceneManager::setup()
{
    // scene setup;
    scene = INTRO;
    sceneControl = SCENEPLAY;

    beforeScene = scene;
    beforeSceneControl = SCENESTOP;

    // 영상 추가
    addScene(INTRO, "movies/Mir_V001_Main.mov");
    addScene(MOVIEA, "movies/red.mov");
    addScene(MOVIEB, "movies/green.mov");
    addScene(OUTRO, "movies/blue.mov");
    //addScene(OUTRO, "movies/sequence.mov");

    // set movieRect = 0,0,1024,768

    // 이팩트 추가
    shout = new EffectSceneShout();
    shout->setup();
    shout->addEffect(0,0.41,0.75); //shout 1
    shout->addEffect(1,0.632,0.538); //shout 2   
    shout->addEffect(2,0.242,0.64); //shout 3
    shout->addEffect(3,0.408,0.31); // shout 4
    shout->addEffect(4,0.768,0.144);

    //set effectRect = 1024,0,1024+1024, 768
}

void SceneManager::addScene(SceneType _scene, string filePath)
{
    if (_scene == INTRO) intro.setup(filePath);
    if (_scene == MOVIEA) moviea.setup(filePath);
    if (_scene == MOVIEB) movieb.setup(filePath);
    if (_scene == OUTRO) outro.setup(filePath);
}

void SceneManager::setScene(SceneType _scene, SceneControlType _sceneControl)
{
    scene = _scene;
    sceneControl = _sceneControl;
}

void SceneManager::setEffect(EffectType _effect, EffectControlType _effectControl)
{
    shout->setEffect(0,SOUNDINPUT, _effectControl);
}

void SceneManager::setShoutEffect(int mic_id, int mic_level, EffectControlType _effectControl)
{
    ((EffectSceneShout*)shout)->setShoutEffect(mic_id,2, _effectControl);
}

bool SceneManager::sceneIsChanged(SceneType _scene, SceneControlType _sceneControl)
{
    bool changed = (beforeScene != _scene) || (beforeSceneControl != _sceneControl) ;
    beforeScene = _scene;
    beforeSceneControl = _sceneControl;
    return changed;
}

void SceneManager::update(SceneType _scene, SceneControlType _sceneControl,
                          EffectType _effect, EffectControlType _effectControl)
{
    if (sceneIsChanged(_scene, _sceneControl))  {
        setScene(_scene, _sceneControl);
        currentMovieScene = getScene();

        if (sceneControl == SCENEPLAY)
            (*currentMovieScene).play(OF_LOOP_NORMAL);

        if (sceneControl == SCENEONCE)
            (*currentMovieScene).play(OF_LOOP_NONE);

        if (sceneControl == SCENESTOP)
            (*currentMovieScene).stop();
    }

    (*currentMovieScene).update();

    //effect
    // setEffect(_effect, _effectControl);
    shout->update();
}

void SceneManager::draw()
{
    currentMovieScene = getScene();
    (*currentMovieScene).draw();

    shout->draw(1.0);
}

MovieScene* SceneManager::getScene()
{
    if (scene == INTRO) return &intro;
    if (scene == MOVIEA) return &moviea;
    if (scene == MOVIEB) return &movieb;
    if (scene == OUTRO) return &outro;
}

EffectScene* SceneManager::getEffect()
{
    return shout;
}

ofRectangle SceneManager::getMovieRect()
{
    return movieRect;
}

ofRectangle SceneManager::getEffectRect()
{
    return effectRect;
}
