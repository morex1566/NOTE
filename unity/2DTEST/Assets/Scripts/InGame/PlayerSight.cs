using System;
using UnityEngine;
using Random = UnityEngine.Random;

namespace InGame
{
    public class PlayerSight : MonoBehaviour
    {
        private Player _player;

        private void Awake()
        {
            _player = GetComponentInParent<Player>();
        }


        private void OnTriggerExit2D(Collider2D opponent)
        {
            // 특정 충돌 개체만 처리
            // if (!opponent.CompareTag("Ground") || !opponent.CompareTag("Enemy"))
            // {
            //     return;
            // }
            
            switch (opponent.tag)
            {
                // 시야에서 벗어난 타일맵을 플레이어가 이동하는 방향으로 이동
                case "Ground":
                    
                    var opponentPos = opponent.transform.position;
                    var myPos = transform.position;
                    float diffX = Math.Abs(myPos.x - opponentPos.x);
                    float diffY = Math.Abs(myPos.y - opponentPos.y);
                    
                    // 플레이어가 더 많이 이동한 축으로 타일맵을 이동
                    if (diffX > diffY) // X축
                    {
                        int repositionDirX = myPos.x - opponentPos.x > 0 ? 1 : -1;
                        Vector2 nextVec = opponentPos;
                        {
                            nextVec.x += 40 * repositionDirX;
                        }

                        opponent.transform.position = nextVec;
                    }
                    else // Y축
                    {
                        int repositionDirY = myPos.y - opponentPos.y > 0 ? 1 : -1;
                        Vector2 nextVec = opponentPos;
                        {
                            nextVec.y += 40 * repositionDirY;
                        }

                        opponent.transform.position = nextVec;
                    }
                    
                    break;
                
                // 시야에서 벗어난 Enemy의 관찰자 Count를 줄이고, 해당 적이 Reposition할 수 있도록 변경/실행
                case "Enemy":

                    EnemyAction enemy = opponent.GetComponent<EnemyAction>();
                    {
                        enemy.Watcher.Remove(transform.parent.gameObject);
                        enemy.IsRepositionable = true;
                    }

                    // 만약 내가 마지막 관찰자 였다면, 플레이어가 이동하는 방향에서 Reposition
                    if(enemy.Watcher.Count == 0)
                    {
                        enemy.OnRepositionAt(_player.Rigid2D.position
                                             + (_player.NextVec * 20)
                                             + (new Vector2(Random.Range(-3f, 3f), Random.Range(-3f, 3f))));

                        enemy.IsRepositionable = false;
                    }

                    break;
                default:
                    return;
            }
        }
    }
}
