#include "StateStack.hpp"
#include "../State/State.hpp"

StateStack::StateStack(State::Context context)
    : mStack(), mPendingList(), mContext(context), mFactories() {}

State::Ptr StateStack::createState(States::ID stateID) {
    auto found = mFactories.find(stateID);
    return found->second();
}

void StateStack::update(sf::Time dt) {
    // Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->update(dt)) break;
    }

    applyPendingChanges();
}

void StateStack::draw() {
    // Draw all active states from bottom to top
    for (State::Ptr& state : mStack) {
        state->draw();
    }
}

void StateStack::update(sf::Time dt) {
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->update(dt)) {
            break;
        }
    }

    applyPendingChanges();
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

void StateStack::pushState(States::ID stateID) {
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() { mPendingList.push_back(PendingChange(Pop)); }

void StateStack::clearStates() { mPendingList.push_back(PendingChange(Clear)); }

bool StateStack::isEmpty() const { return mStack.empty(); }

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action), stateID(stateID) {}