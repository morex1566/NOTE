using System;
using UnityEngine;

namespace InGame
{
    public class EnemyAnimation : MonoBehaviour
    {
        private Enemy _enemy;


        private void Awake()
        {
            _enemy = GetComponent<Enemy>();
        }
        
        private void LateUpdate()
        {
            // 적의 좌우 전환
            if (_enemy.NextVec.x != 0)
            {
                _enemy.Spriter.flipX = _enemy.NextVec.x < 0;
            }
        }
    }
}
