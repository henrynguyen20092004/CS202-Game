#include "Container.hpp"

GUI::Container::Container() : mSelectedChild(-1) {}

void GUI::Container::addComponent(Component::Ptr component) {
    mChildren.push_back(component);

    if (!hasSelection() && component->isSelectable()) {
        select(mChildren.size() - 1);
    }
}

bool GUI::Container::isSelectable() const { return false; }

void GUI::Container::handleEvent(const sf::Event& event) {
    if (hasSelection() && mChildren[mSelectedChild]->isActive()) {
        mChildren[mSelectedChild]->handleEvent(event);
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                selectPrevious();
                break;

            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                selectNext();
                break;

            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                if (hasSelection()) {
                    mChildren[mSelectedChild]->activate();
                }

                break;
        }
    }
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    states.transform *= getTransform();

    for (const Component::Ptr& child : mChildren) {
        target.draw(*child, states);
    }
}

bool GUI::Container::hasSelection() const { return mSelectedChild >= 0; }

void GUI::Container::select(int index) {
    if (mChildren[index]->isSelectable()) {
        if (hasSelection()) {
            mChildren[mSelectedChild]->deselect();
        }

        mChildren[index]->select();
        mSelectedChild = index;
    }
}

void GUI::Container::selectNext() {
    if (!hasSelection()) {
        return;
    }

    int next = mSelectedChild;

    do {
        next = (next + 1) % mChildren.size();
    } while (!mChildren[next]->isSelectable());

    select(next);
}

void GUI::Container::selectPrevious() {
    if (!hasSelection()) {
        return;
    }

    int prev = mSelectedChild;

    do {
        prev = (prev + mChildren.size() - 1) % mChildren.size();
    } while (!mChildren[prev]->isSelectable());

    select(prev);
}
