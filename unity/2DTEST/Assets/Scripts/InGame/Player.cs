using System;
using ScriptableObject;
using UnityEngine;

namespace InGame
{
    public class Player : MonoBehaviour
    {
        [Header("플레이어 정보")] 
        [Space(5)] 
        
        [Tooltip("플레이어의 이동속도")]
        [SerializeField] private float speed;

        [Tooltip("플레이어의 무기")] 
        [SerializeField] private SO_Weapon weapon;

        
        private Vector2 _inputVec;
        private Vector2 _nextVec;

        
        #region Getter/Setter 선언

        public ref Vector2 InputVec => ref _inputVec;
        public ref Vector2 NextVec => ref _nextVec;

        public SO_Weapon Weapon
        {
            get => weapon;
            set => weapon = value;
        }
        public SpriteRenderer Spriter { get; private set; }
        public Rigidbody2D Rigid2D { get; private set; }
        public Animator Anim { get; private set; }
        public float Speed => speed;

        #endregion


        private void Awake()
        {
            Spriter = GetComponentInChildren<SpriteRenderer>();
            Anim = GetComponentInChildren<Animator>();
            Rigid2D = GetComponent<Rigidbody2D>();
        }
    }
}
