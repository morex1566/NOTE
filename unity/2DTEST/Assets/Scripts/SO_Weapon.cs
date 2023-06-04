using UnityEngine;

namespace ScriptableObject
{
    [CreateAssetMenu(fileName = "SO_Weapon", menuName = "Scriptable Object/Equipment/Weapon")]
    public class SO_Weapon : UnityEngine.ScriptableObject
    {
        [SerializeField] private float damage;
        public float Damage
        {
            get => damage;
            set => damage = value;
        }
    }
}
