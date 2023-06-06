using UnityEngine;
using UnityEngine.Serialization;

namespace ScriptableObject
{
    public class SO_Weapon : UnityEngine.ScriptableObject
    {
        // 무기의 공격력
        [SerializeField] protected float damage;
        [SerializeField] public float Damage
        {
            get => damage;
            set => damage = value;
        }
        
        // 무기의 사거리
        [SerializeField] protected float range;
        [SerializeField] public float Range
        {
            get => range;
            set => range = value;
        }
        
        // 무기의 메쉬
        [SerializeField] protected Sprite bodySprite;
        [SerializeField] public Sprite BodySprite
        {
            get => bodySprite;
            set => bodySprite = value;
        }

        // 무기의 초당 공격속도
        [SerializeField] protected float attackSpeed;
        [SerializeField] public float AttackSpeed
        {
            get => attackSpeed;
            set => attackSpeed = value;
        }
        

        public virtual void Attack()
        {
            
        }

        public virtual void Reload()
        {
            
        }
    }
}
