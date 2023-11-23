#include "StateStack.hpp"

State::Ptr StateStack::createState(States::ID stateID) {
    auto found = mFactories.find(stateID);
    return found->second();
}

void StateStack::handleEvent(const sf::Event& event) {
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->handleEvent(event)) {
            return;
        }
    }

    applyPendingChanges();
}

void StateStack::applyPendingChanges() {
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Action::Pop:
                mStack.pop_back();
                break;
            case Action::Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}
