#include "SceneNode.hpp"

#include <algorithm>

void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
    std::vector<Ptr>::iterator found =
        std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& child) {
            return child.get() == &node;
        });

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::processEvents(const sf::Event& event) {
    processEventsCurrent(event);
    processEventsChildren(event);
}

void SceneNode::update(sf::Time deltaTime) {
    updateCurrent(deltaTime);
    updateChildren(deltaTime);
}

void SceneNode::processEventsCurrent(const sf::Event&) {}

void SceneNode::processEventsChildren(const sf::Event& event) {
    for (Ptr& child : mChildren) {
        child->processEvents(event);
    }
}

void SceneNode::updateCurrent(sf::Time) {}

void SceneNode::updateChildren(sf::Time deltaTime) {
    for (Ptr& child : mChildren) {
        child->update(deltaTime);
    }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const {}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states)
    const {
    for (const Ptr& child : mChildren) {
        child->draw(target, states);
    }
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node; node = node->mParent) {
        transform *= node->getTransform();
    }

    return transform;
}
