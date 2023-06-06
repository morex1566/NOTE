using UnityEngine;

namespace ScriptableObject
{
    public class SO_RangeWeapon : SO_Weapon
    {
        [SerializeField] protected SO_Bullet bullet;
        [SerializeField] public SO_Bullet Bullet
        {
            get => bullet;
            set => bullet = value;
        }
        
        [SerializeField] protected int ammo;
        [SerializeField] public int Ammo
        {
            get => ammo;
            set => ammo = value;
        }
    }
}
