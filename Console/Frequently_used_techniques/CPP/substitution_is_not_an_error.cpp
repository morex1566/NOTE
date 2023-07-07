#include <type_traits>

class Weapon
{
public:
	virtual ~Weapon() = default;
};

class Sword : Weapon
{
public:

};

class Gun : Weapon
{
	
};

class Armor
{
	
};

template <typename T> using IsWeapon = std::enable_if_t<std::is_base_of<Weapon, T>::value, T>;


template <typename T, typename = IsWeapon<T>> static T* CreateWeapon()
{
	T* weapon = new T;

	return nullptr;
}

int main()
{
	CreateWeapon<Sword>();
}