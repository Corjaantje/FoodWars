#include "../../Headers/StateMachine/AdvertisingScreen.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../../TonicEngine/Headers/Storage/AdvertisingManager.h"


AdvertisingScreen::AdvertisingScreen(std::shared_ptr<ScreenStateManager> context, const AdvertisingManager& manager) : IScreen(context), _advertisingManager(&manager)
{
    visualFacade = context->getFacade<VisualFacade>();
    audioFacade = context->getFacade<AudioFacade>();
    _inputFacade->getKeyEventObservable()->IObservable<KeyEvent>::registerObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());

    _renderList._shapes[0].push_back(createShape<ShapeSprite>(1600, 900, 0, 0, "ScreenAdvertisements.png"));

    if (_advertisingManager->getAdvertisements().empty())
    {
        _renderList._shapes[1].push_back(createShape<ShapeText>((1600/2)-200, 550, "No ADs found.", 80, 400, 100, Colour(0,0,0,0)));
        return;
    }

    //get index from currentAd
    currentIndex = 0;
    shownAD = new ShapeSprite(400, 150, (1600/2)-200, (900/2)-90, _advertisingManager->getCurrentAd());

    _renderList._shapes[1].push_back(shownAD);

    _renderList._shapes[1].push_back(createShape<SpriteButton>(*_inputFacade->getMouseEventObservable(), "", [c = _context]() {  c->setActiveScreen<MainMenuScreen>(); }, 120, 120, 10, 10, Colour{0,0,0,0}));

    _renderList._shapes[1].push_back(createShape<SpriteButton>(*_inputFacade->getMouseEventObservable(), "",
            [this] { swapAdvertisement(false); }, 50, 50, 440, 400, Colour(0,0,0,0)));
    _renderList._shapes[1].push_back(createShape<SpriteButton>(*_inputFacade->getMouseEventObservable(), "",
            [this] { swapAdvertisement(true); }, 50, 50, 1110, 400, Colour(0,0,0,0)));

    _renderList._shapes[1].push_back(createShape<TextButton>(*_inputFacade->getMouseEventObservable(),
                                                             "", [c = context, a = _advertisingManager, this] { a->setCurrentAd(shownAD->imageURL); c->setActiveScreen<MainMenuScreen>();  }, 400, 100, (1600/2)-200, 600));
}

AdvertisingScreen::~AdvertisingScreen()
{
    delete shownAD;
}

void AdvertisingScreen::update(double deltaTime)
{
    visualFacade->render(_renderList);
    audioFacade->playMusic("menu");
    _inputFacade->pollEvents();
}

void AdvertisingScreen::update(std::shared_ptr<KeyEvent> event)
{
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

//TODO: get advertisements nog maar 1 keer ophalen.
void AdvertisingScreen::swapAdvertisement(bool directionNext) {
    if (directionNext) {
        currentIndex++;
        if (currentIndex >= _advertisingManager->getAdvertisements().size()) {
            currentIndex = 0;
        }
        shownAD->imageURL = _advertisingManager->getAdvertisements()[currentIndex];
    } else {
        currentIndex--;
        if (currentIndex < 0)
        {
            currentIndex = _advertisingManager->getAdvertisements().size() - 1;
        }
        shownAD->imageURL = _advertisingManager->getAdvertisements()[currentIndex];
    }
}
