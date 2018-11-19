#include "../../Headers/StateMachine/SettingsScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

SettingsScreen::SettingsScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    // MainMenu
    SpriteButton* backButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 140, 140, 12, 12, Colour{0,0,0,0}};
    backButton->addToRender(&_renderList);
    _buttons.push_back(backButton);

    //TODO: setresolution via visual facade
    // Aspect ratios
    TextButton* resizeButton1 = new TextButton {*_inputFacade->getMouseEventObservable(),"800x450", [v = visualFacade]() {  v->setResolution(800,450); }, 560, 60, 205, 280, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton1->addToRender(&_renderList);
    _buttons.push_back(resizeButton1);

    TextButton* resizeButton2 = new TextButton {*_inputFacade->getMouseEventObservable(),"1024x576", [v = visualFacade]() {  v->setResolution(1020,576); }, 560, 60, 205, 362, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton2->addToRender(&_renderList);
    _buttons.push_back(resizeButton2);

    TextButton* resizeButton3 = new TextButton {*_inputFacade->getMouseEventObservable(),"1152x648", [v = visualFacade]() {  v->setResolution(1152,648); }, 560, 60, 205, 446, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton3->addToRender(&_renderList);
    _buttons.push_back(resizeButton3);

    TextButton* resizeButton4 = new TextButton {*_inputFacade->getMouseEventObservable(),"1280x720", [v = visualFacade]() {  v->setResolution(1280,720); }, 560, 60, 205, 528, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton4->addToRender(&_renderList);
    _buttons.push_back(resizeButton4);

    TextButton* resizeButton5 = new TextButton {*_inputFacade->getMouseEventObservable(),"1366x768", [v = visualFacade]() {  v->setResolution(1366,768); }, 560, 60, 205, 609, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton5->addToRender(&_renderList);
    _buttons.push_back(resizeButton5);

    TextButton* resizeButton6 = new TextButton {*_inputFacade->getMouseEventObservable(),"1600x900", [v = visualFacade]() {  v->setResolution(1600,900); }, 560, 60, 205, 692, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton6->addToRender(&_renderList);
    _buttons.push_back(resizeButton6);

    TextButton* resizeButton7 = new TextButton {*_inputFacade->getMouseEventObservable(),"1920x1080", [v = visualFacade]() {  v->setResolution(1920,1080); }, 560, 60, 205, 773, 200, 10, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton7->addToRender(&_renderList);
    _buttons.push_back(resizeButton7);


    // Music volume control
    TextButton* lowerMusicVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [a = audioFacade]() {  a->setMusicVolume(a->getMusicVolume() - 5); }, 42, 42, 1126, 282, Colour{255,255,255,0}, Colour{255,255,255,0}};
    lowerMusicVolumeButton->addToRender(&_renderList);
    _buttons.push_back(lowerMusicVolumeButton);

    musicVolume = new ShapeText(1240, 287, std::to_string(audioFacade->getMusicVolume()), 12, 40, 40, Colour{255,255,255,0} );
    musicVolume->addToRender(&_renderList);

    TextButton* raiseMusicVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [a = audioFacade]() {  a->setMusicVolume(a->getMusicVolume() + 5); }, 42, 42, 1352, 282, Colour{255,255,255,0}, Colour{255,255,255,0}};
    raiseMusicVolumeButton->addToRender(&_renderList);
    _buttons.push_back(raiseMusicVolumeButton);

    // Music volume control
    TextButton* lowerEffectVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [a = audioFacade]() {  a->setEffectVolume(a->getEffectVolume() - 5); }, 42, 42, 1126, 375, Colour{255,255,255,0}, Colour{255,255,255,0}};
    lowerEffectVolumeButton->addToRender(&_renderList);
    _buttons.push_back(lowerEffectVolumeButton);

    effectVolume = new ShapeText(1240, 377, std::to_string(audioFacade->getEffectVolume()), 12, 40, 40, Colour{255,255,255,0} );
    effectVolume->addToRender(&_renderList);

    TextButton* raiseEffectVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"", [a = audioFacade]() {  a->setEffectVolume(a->getEffectVolume() + 5); }, 42, 42, 1352, 375, Colour{255,255,255,0}, Colour{255,255,255,0}};
    raiseEffectVolumeButton->addToRender(&_renderList);
    _buttons.push_back(raiseEffectVolumeButton);
}

SettingsScreen::~SettingsScreen() {
    for(IShape* button: _buttons) {
        delete button;
    }
}

void SettingsScreen::update(double deltaTime) {
    _renderList.clearLists();
    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "ScreenSettings.png"});
    for(int i=0; i < _buttons.size(); i++){
        _buttons[i]->addToRender(&_renderList);
    }

    // Update music volume
    musicVolume->text = std::to_string(audioFacade->getMusicVolume());

    // Update effect volume
    effectVolume->text = std::to_string(audioFacade->getEffectVolume());

    // Add to render
    _renderList._shapes[1].push_back(new ShapeText(musicVolume->xPos, musicVolume->yPos, musicVolume->text,musicVolume->fontSize, musicVolume->width,musicVolume->height,musicVolume->colour));
    _renderList._shapes[1].push_back(new ShapeText(effectVolume->xPos, effectVolume->yPos, effectVolume->text,effectVolume->fontSize, effectVolume->width,effectVolume->height,effectVolume->colour));

    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void SettingsScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}


