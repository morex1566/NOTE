using UnityEngine;

namespace ScriptableObject
{
    [CreateAssetMenu(fileName = "SO_Enemy", menuName = "Scriptable Object/Enemy")]
    public class SO_Enemy : UnityEngine.ScriptableObject
    {
        [SerializeField] private float _health;
        [SerializeField] private float _speed;
        [SerializeField] private float _damage;

        public float Health
        {
            get => _health;
            set => _health = value;
        }

        public float Speed
        {
            get => _speed;
            set => _speed = value;
        }

        public float Damage
        {
            get => _damage;
            set => _damage = value;
        }
    }
}
