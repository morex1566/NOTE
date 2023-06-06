using UnityEngine;
using UnityEngine.Serialization;

namespace ScriptableObject
{
    [CreateAssetMenu(fileName = "SO_Enemy", menuName = "Scriptable Object/Enemy")]
    public class SO_Enemy : UnityEngine.ScriptableObject
    {
        [SerializeField] private float _health;
        [SerializeField] private float _speed;
        [SerializeField] private float _damage;

        [SerializeField] private RuntimeAnimatorController animController;
        [SerializeField] private Sprite bodySprite;

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

        public RuntimeAnimatorController AnimController
        {
            get => animController;
            set => animController = value;
        }

        public Sprite BodySprite
        {
            get => bodySprite;
            set => bodySprite = value;
        }
    }
}
