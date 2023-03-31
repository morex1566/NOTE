/*
    Refactoring     : vector에서 특정한 원소를 제거하고 싶은 경우에 사용합니다.
    새로운 개념      : 1. std::container에서 범용적으로 사용되는 iterator
                      2. erase-remove idiom
*/

class Component;

std::vector<Component*> components;

// need refactoring!
void GameObject::detachComponent(const Component& component_)
{
	for (auto component : components)
	{
		if (component == &component_)
		{
			components.erase(std::remove(components.begin(), components.end(), component));
		}
	}
}

// revised code!
void GameObject::detachComponent(const Component& component_)
{
    for (auto it = components.begin(); it != components.end(); )
    {
        if (*it == component_)
        {
            it = components.erase(it);
        }
        else
        {
            ++it;
        }
    }
}