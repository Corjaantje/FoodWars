#include "../../Headers/StateMachine/SettingsScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

SettingsScreen::SettingsScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context) {
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _renderList._shapes[0].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "wallpaper.png"));

    // MainMenu
    SpriteButton* quitButton = new SpriteButton {*_inputFacade->getMouseEventObservable(), "exit.png", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 50, 50, 0, 0, Colour{0,0,0,0}};
    quitButton->addToRender(&_renderList);
    _sprites.push_back(quitButton);

    //TODO: setresolution via visual facade
    // Aspect ratios
    TextButton* resizeButton1 = new TextButton {*_inputFacade->getMouseEventObservable(),"800x450", [v = visualFacade]() {  v->setResolution(800,450); }, 250, 30, 615, 300, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton1->addToRender(&_renderList);
    _sprites.push_back(resizeButton1);

    TextButton* resizeButton2 = new TextButton {*_inputFacade->getMouseEventObservable(),"1024x576", [v = visualFacade]() {  v->setResolution(1020,576); }, 250, 30, 615, 350, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton2->addToRender(&_renderList);
    _sprites.push_back(resizeButton2);

    TextButton* resizeButton3 = new TextButton {*_inputFacade->getMouseEventObservable(),"1152x648", [v = visualFacade]() {  v->setResolution(1152,648); }, 250, 30, 615, 400, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton3->addToRender(&_renderList);
    _sprites.push_back(resizeButton3);

    TextButton* resizeButton4 = new TextButton {*_inputFacade->getMouseEventObservable(),"1280x720", [v = visualFacade]() {  v->setResolution(1280,720); }, 250, 30, 615, 450, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton4->addToRender(&_renderList);
    _sprites.push_back(resizeButton4);

    TextButton* resizeButton5 = new TextButton {*_inputFacade->getMouseEventObservable(),"1366x768", [v = visualFacade]() {  v->setResolution(1366,768); }, 250, 30, 615, 500, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton5->addToRender(&_renderList);
    _sprites.push_back(resizeButton5);

    TextButton* resizeButton6 = new TextButton {*_inputFacade->getMouseEventObservable(),"1600x900", [v = visualFacade]() {  v->setResolution(1600,900); }, 250, 30, 615, 550, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton6->addToRender(&_renderList);
    _sprites.push_back(resizeButton6);

    TextButton* resizeButton7 = new TextButton {*_inputFacade->getMouseEventObservable(),"1920x1080", [v = visualFacade]() {  v->setResolution(1920,1080); }, 250, 30, 615, 600, Colour{255,255,255,0}, Colour{255,255,255,0}};
    resizeButton7->addToRender(&_renderList);
    _sprites.push_back(resizeButton7);

    // Music volume control
    TextButton* lowerMusicVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"-", [a = audioFacade]() {  a->setMusicVolume(a->getMusicVolume() - 5); }, 10, 30, 615, 700, Colour{255,255,255,0}, Colour{255,255,255,0}};
    lowerMusicVolumeButton->addToRender(&_renderList);
    _buttons.push_back(lowerMusicVolumeButton);

    musicVolume = new ShapeText(630, 700, std::to_string(audioFacade->getMusicVolume()), 12, 50, 30, Colour{255,255,255,0} );
    musicVolume->addToRender(&_renderList);

    TextButton* raiseMusicVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"+", [a = audioFacade]() {  a->setMusicVolume(a->getMusicVolume() + 5); }, 10, 30, 695, 700, Colour{255,255,255,0}, Colour{255,255,255,0}};
    raiseMusicVolumeButton->addToRender(&_renderList);
    _buttons.push_back(raiseMusicVolumeButton);

    // Music volume control
    TextButton* lowerEffectVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"-", [a = audioFacade]() {  a->setEffectVolume(a->getEffectVolume() - 5); }, 10, 30, 615, 750, Colour{255,255,255,0}, Colour{255,255,255,0}};
    lowerEffectVolumeButton->addToRender(&_renderList);
    _buttons.push_back(lowerEffectVolumeButton);

    effectVolume = new ShapeText(630, 750, std::to_string(audioFacade->getEffectVolume()), 12, 50, 30, Colour{255,255,255,0} );
    effectVolume->addToRender(&_renderList);

    TextButton* raiseEffectVolumeButton = new TextButton {*_inputFacade->getMouseEventObservable(),"+", [a = audioFacade]() {  a->setEffectVolume(a->getEffectVolume() + 5); }, 10, 30, 695, 750, Colour{255,255,255,0}, Colour{255,255,255,0}};
    raiseEffectVolumeButton->addToRender(&_renderList);
    _buttons.push_back(raiseEffectVolumeButton);
}

SettingsScreen::~SettingsScreen() {
    for (IShape *button: _sprites) {
        delete button;
    }
}

void SettingsScreen::update(double deltaTime) {
    _renderList.clearLists();
    _renderList._shapes[0].push_back(new ShapeSprite{1600, 900, 0, 0, "wallpaper.png"});
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