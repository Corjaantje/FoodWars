#ifndef PROJECT_SWA_IRENDERABLE_H
#define PROJECT_SWA_IRENDERABLE_H

class IRenderer;

class IRenderable {
public:
    IRenderable() = default;
    virtual ~IRenderable() = default;;
    virtual void render(IRenderer& renderer) const = 0;
};

#endif //PROJECT_SWA_IRENDERABLE_H
