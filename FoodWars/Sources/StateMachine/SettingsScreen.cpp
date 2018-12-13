#include "../../Headers/StateMachine/SettingsScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

SettingsScreen::SettingsScreen(ScreenStateManager& context) : IScreen(context) {
    _inputFacade->getKeyEventObservable().registerKeyEventObserver(this);
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenSettings.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    // MainMenu
    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            140, 140, 12, 12,
            Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"800x450",
            [v = _visualFacade]() {
                v->setResolution(800,450);
            },
            560, 60, 205, 280, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"1024x576",
            [v = _visualFacade]() {
                v->setResolution(1020,576);
            },
            560, 60, 205, 362, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"1152x648",
            [v = _visualFacade]() {
                v->setResolution(1152,648);
            },
            560, 60, 205, 446, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"1280x720",
            [v = _visualFacade]() {
                v->setResolution(1280,720);
            },
            560, 60, 205, 528, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"1366x768",
            [v = _visualFacade]() {
                v->setResolution(1366,768);
            },
            560, 60, 205, 609, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"1600x900",
            [v = _visualFacade]() {
                v->setResolution(1600,900);
            },
            560, 60, 205, 692, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(),"1920x1080",
            [v = _visualFacade]() {
                v->setResolution(1920,1080);
            },
            560, 60, 205, 773, 200, 10,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    musicVolume = createShape<ShapeText>(1240, 287, std::to_string(_audioFacade->getMusicVolume()), 12, 40, 40, Colour{255, 255, 255, 0});
    musicVolume->addToRender(&_renderList);
    effectVolume = createShape<ShapeText>(1240, 377, std::to_string(_audioFacade->getEffectVolume()), 12, 40, 40, Colour{255, 255, 255, 0});
    effectVolume->addToRender(&_renderList);

    // Music volume control
    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "",
            [a = _audioFacade, m = musicVolume]() {
                a->decreaseMusicVolume();
                m->text = std::to_string(a->getMusicVolume());
            },
            42, 42, 1126, 282,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "",
            [a = _audioFacade, m = musicVolume]() {
                a->increaseMusicVolume();
                m->text = std::to_string(a->getMusicVolume());
            },
            42, 42, 1352, 282,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "",
            [a = _audioFacade, e = effectVolume]() {
                a->decreaseEffectVolume();
                e->text = std::to_string(a->getEffectVolume());
            },
            42, 42, 1126, 375,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "",
            [a = _audioFacade, e = effectVolume]() {
                a->increaseEffectVolume();
                e->text = std::to_string(a->getEffectVolume());
            },
            42, 42, 1352, 375,
            Colour{255,255,255,0},
            Colour{255,255,255,0})->addToRender(&_renderList);
}

SettingsScreen::~SettingsScreen() = default;

void SettingsScreen::update(double deltaTime) {
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void SettingsScreen::update(const KeyEvent& event){
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}