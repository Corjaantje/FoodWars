#include "../../Headers/StateMachine/AdvertisingScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"


AdvertisingScreen::AdvertisingScreen(ScreenStateManager& context) :
        IScreen(context),
        _fileManager(FileManager{}),
        _currentIndex(0)
{
    auto wallpaper = createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenAdvertisements.png");
    wallpaper->layer = 0;
    wallpaper->addToRender(&_renderList);

    std::string filePath = "./Assets/Sprites/Advertisements/";
    _currentAD = _fileManager.readFileLines(filePath + "current.txt")[0];
    _advertisements = _fileManager.getFiles(filePath, {"png"}, true, false);
    if (_currentAD.empty() || _advertisements.empty())
    {
        createShape<ShapeText>((1600/2)-200, 550, "No ADs found.", 80, 400, 100, Colour(0,0,0,0))->addToRender(&_renderList);
        return;
    }

    _shownAD = createShape<ShapeSprite>(400, 150, (1600/2)-200, (900/2)-90, _currentAD);
    _shownAD->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context]() {
                c->setActiveScreen<MainMenuScreen>();
            },
            120, 120, 10, 10,
            Colour{0,0,0,0})->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                swapAdvertisement(false);
            },
            50, 50, 440, 400,
            Colour(0,0,0,0))->addToRender(&_renderList);

    createShape<SpriteButton>(_inputFacade->getMouseEventObservable(), "",
            [this]() {
                swapAdvertisement(true);
            },
            50, 50, 1110, 400,
            Colour(0,0,0,0))->addToRender(&_renderList);

    createShape<TextButton>(_inputFacade->getMouseEventObservable(), "",
            [c = _context, f = _fileManager, this, filePath]() {
                f.writeFileContent(filePath + "current.txt", _shownAD->imageURL);
                c->setActiveScreen<MainMenuScreen>();
            },
            400, 100, (1600/2)-200, 600)->addToRender(&_renderList);
}

void AdvertisingScreen::update(double deltaTime)
{
    _visualFacade->render(_renderList);
    _audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void AdvertisingScreen::update(const KeyEvent& event)
{
    if(event.getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

void AdvertisingScreen::swapAdvertisement(bool directionNext) {
    if (directionNext) {
        _currentIndex++;
        if (_currentIndex >= _advertisements.size()) {
            _currentIndex = 0;
        }
        _shownAD->imageURL = _advertisements[_currentIndex];
    } else {
        _currentIndex--;
        if (_currentIndex < 0)
        {
            _currentIndex = _advertisements.size() - 1;
        }
        _shownAD->imageURL = _advertisements[_currentIndex];
    }
}
