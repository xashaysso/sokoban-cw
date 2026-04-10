#pragma once

#include <stack>
#include <memory>


class AppState;

class StateManager {
    public:
        void pushState(std::unique_ptr<AppState> newState);
        void popState();
        AppState* getCurrentState();
    private:
        std::stack<std::unique_ptr<AppState>> states;
};
