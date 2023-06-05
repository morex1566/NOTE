using System;
using UnityEngine;

namespace InGame
{
    public class EnemyRange : MonoBehaviour
    {
        private Enemy _enemy;

        private void Start()
        {
            _enemy = transform.parent.GetComponent<Enemy>();
        }

        private void OnCollisionEnter(Collision opponent)
        {
            // 특정 충돌 개체만 처리
            if (!opponent.gameObject.CompareTag("Player"))
            {
                return;
            }
            
            // 충돌중임을 관련 스크립트에게 Notify합니다.
        }

        private void OnCollisionStay2D(Collision2D opponent)
        {
            // 특정 충돌 개체만 처리
            if (!opponent.gameObject.CompareTag("Player"))
            {
                return;
            }
            
            // 충돌중임을 관련 스크립트에게 Notify합니다.
        }

        private void OnCollisionExit(Collision opponent)
        {
            // 특정 충돌 개체만 처리
            if (!opponent.gameObject.CompareTag("Player"))
            {
                return;
            }
            
            // 충돌이 종료되었음을 관련 스크립트에게 Notify합니다.

        }
    }
}
