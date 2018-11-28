#ifndef PROJECT_SWA_ISCREEN_H
#define PROJECT_SWA_ISCREEN_H

#include <utility>
#include "memory"
#include "../../../TonicEngine/Headers/Input/WindowClosedObserver.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "ScreenStateManager.h"

class IScreen : IObserver<WindowEvent> {
protected:
    std::shared_ptr<InputFacade> _inputFacade;
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    Renderlist _renderList;
    std::shared_ptr<ScreenStateManager> _context;
    bool _isClosed;
    std::vector<IShape *> _sprites;
public:

    explicit IScreen(const std::shared_ptr<ScreenStateManager> &context) : _context(context),
                                                           _inputFacade(std::make_shared<InputFacade>()),
                                                           visualFacade(context->getFacade<VisualFacade>()),
                                                           audioFacade(context->getFacade<AudioFacade>()),
                                                           _renderList(),
                                                           _isClosed(false) {
        _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
        _inputFacade->getWindowEventObservable()->registerObserver(this);
    }

    ~IScreen() {
        _inputFacade->getWindowEventObservable()->unregisterObserver(this);
        for (IShape *shape: _sprites) {
            delete shape;
        }
    }

    virtual void update(double deltaTime) = 0;

    void update(const WindowEvent& event) override {
        if (event.GetWindowEventType() == WindowEventType::Quit) {
            _isClosed = true;
        }
        if (event.GetWindowEventType() == WindowEventType::Resize) {
            visualFacade->setResolution(event.getWidth(), event.getHeight());
        }
    }

    template<typename T, typename... Args>
    T *createShape(Args &&... args) {
        T *shape = new T(std::forward<Args>(args)...);
        _sprites.push_back(shape);
        return shape;
    }

    bool isWindowClosed() const {
        return _isClosed;
    }
};

#endif //PROJECT_SWA_ISCREEN_H