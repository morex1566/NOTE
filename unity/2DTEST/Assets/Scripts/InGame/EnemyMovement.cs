using System;
using UnityEngine;

namespace InGame
{
    public class EnemyMovement : MonoBehaviour
    {
        private Enemy _enemy;

        private Vector2 nextVec;

        private void Awake()
        {
            _enemy = GetComponent<Enemy>();
        }

        private void FixedUpdate()
        {
            _enemy.NextVec = (getNearlistPlayerPos() - transform.position).normalized
                          * (_enemy.Data.Speed * Time.fixedDeltaTime);
            
            _enemy.Rigid2D.MovePosition(_enemy.Rigid2D.position + _enemy.NextVec);
        }

        private void Update()
        {
            
        }

        private Vector3 getNearlistPlayerPos()
        {
            Vector2 resultPos = Vector2.zero;
            
            var playerList = InGameManager.Instance.PlayerList;
            {
                if (playerList.Count == 0)
                {
                    Debug.Log("There is no Player");
                }
                
                foreach (var player in playerList)
                {
                    float current = resultPos.magnitude;
                    float opponent = (player.transform.position - _enemy.transform.position).magnitude;

                    resultPos = current < opponent ? player.transform.position : resultPos;
                }
            }

            return resultPos;
        }
    }
}
