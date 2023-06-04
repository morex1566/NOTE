using System;
using UnityEngine;

namespace InGame
{
    public class Sight : MonoBehaviour
    {
        private Player _player;
        private BoxCollider2D _boundary;

        private void Awake()
        {
            _player = transform.parent.GetComponent<Player>();
            _boundary = GetComponent<BoxCollider2D>();
        }
        
        private void OnTriggerExit2D(Collider2D opponent)
        {
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
                case "Enemy":
                    break;
                default:
                    return;
            }
        }
    }
}
