using UnityEngine;

namespace ScriptableObject
{
    public class SO_MeleeWeapon : SO_Weapon
    {
        [SerializeField] protected float sp;
        [SerializeField] public float SP
        {
            get => sp;
            set => sp = value;
        }
    }
}
