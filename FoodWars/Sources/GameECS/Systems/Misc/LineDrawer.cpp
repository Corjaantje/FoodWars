#include "../../../../Headers/GameECS/Systems/Misc/LineDrawer.h"
#include "../../../../Headers/GameECS/Components/DrawableComponent.h"

LineDrawer::LineDrawer(EntityManager &entityManger) : _entityManager(&entityManger), _line{}, _displayedLine{nullptr},
                                                      _lineId{-1} {

}

void LineDrawer::setFromX(int x) {
    _line.xPos = x;
    if (_displayedLine) _displayedLine->xPos = x;
}

void LineDrawer::setFromY(int y) {
    _line.yPos = y;
    if (_displayedLine) _displayedLine->yPos = y;
}

void LineDrawer::setToX(int x) {
    _line.xPos2 = x;
    if (_displayedLine) _displayedLine->xPos2 = x;
}

void LineDrawer::setToY(int y) {
    _line.yPos2 = y;
    if (_displayedLine) _displayedLine->yPos2 = y;
}

void LineDrawer::show() {
    if (_lineId < 0) {
        _lineId = _entityManager->createEntity();
        auto &drawableComponent = _entityManager->addComponentToEntity<DrawableComponent>(_lineId,
                                                                                          std::make_unique<ShapeLine>(
                                                                                                  _line.xPos,
                                                                                                  _line.yPos,
                                                                                                  _line.xPos2,
                                                                                                  _line.yPos2,
                                                                                                  _line.colour));
        _displayedLine = static_cast<ShapeLine *>(drawableComponent.getShape());
    }
}

void LineDrawer::hide() {
    if (_lineId > 0) {
        _displayedLine = nullptr;
        _entityManager->removeEntity(_lineId);
        _lineId = -1;
    }
}