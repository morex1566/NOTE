#include <iostream>
#include <vector>
#include <memory>

class Transform{};
class Renderer{};

class Component
{
    template <class T> using IsComponent = std::enable_if_t<std::is_same_v<Component, T>, bool>;
    
public:
    template <class T, class = IsComponent<T>> void AddComponent()
    {
        
    }
    
private:
    std::weak_ptr<Transform> transform;
    std::vector<std::shared_ptr<Component>> components;
};