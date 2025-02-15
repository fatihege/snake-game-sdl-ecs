#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component.h"

class Entity {
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    bool active = false;

public:
    int id;

    explicit Entity(const int id) : id(id) {
        active = true;
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args &&... args) {
        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        components[std::type_index(typeid(T))] = component;
        return component;
    }

    template<typename T>
    std::shared_ptr<T> getComponent() {
        if (const auto it = components.find(std::type_index(typeid(T))); it != components.end())
            return std::static_pointer_cast<T>(it->second);
        return nullptr;
    }

    template<typename T>
    [[nodiscard]] bool hasComponent() const {
        return components.contains(std::type_index(typeid(T)));
    }

    void destroy() {
        active = false;
    }

    [[nodiscard]] bool isActive() const {
        return active;
    }
};
