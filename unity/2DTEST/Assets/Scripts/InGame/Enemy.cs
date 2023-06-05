using System;
using ScriptableObject;
using UnityEngine;
using UnityEngine.Serialization;

namespace InGame
{
    public class Enemy : MonoBehaviour
    {
        [Header("적 정보")] 
        [Space(5)] 
        
        [Tooltip("몬스터에 관한 능력치")]
        [SerializeField] private SO_Enemy data;
        
        
        private Vector2 _nextVec;
        

        #region  Getter/Setter 선언

        public ref Vector2 NextVec => ref _nextVec;
        
        public SO_Enemy Data => data;
        public CapsuleCollider2D BodyCollider2D { get; private set; }
        public GameObject Target { get; private set; }
        public Rigidbody2D Rigid2D { get; private set; }
        public SpriteRenderer Spriter { get; private set; }
        public Animator Anim { get; private set; }

        #endregion
        
        
        private void Awake()
        {
            BodyCollider2D = GetComponent<CapsuleCollider2D>();
            Rigid2D = GetComponent<Rigidbody2D>();
            Spriter = GetComponentInChildren<SpriteRenderer>();
            Anim = GetComponentInChildren<Animator>();
        }

        private void Start()
        {
            
        }
    }
}
