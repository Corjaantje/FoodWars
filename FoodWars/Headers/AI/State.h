#ifndef PROJECT_SWA_STATE_H
#define PROJECT_SWA_STATE_H

class State {
public:
    State() = default;
    virtual ~State() = default;
    //this will execute when the state is entered
    virtual void enter() = 0;
    //this is called by the update function each update step
    virtual void execute(double dt) = 0;
    //this will execute when the state is exited
    virtual void exit() = 0;
};

#endif //PROJECT_SWA_STATE_H
