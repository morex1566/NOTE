using System;
using UnityEngine;

namespace InGame
{
    public class PlayerAnimation : MonoBehaviour
    {
        private Player _player;
        private static readonly int Speed = Animator.StringToHash("Speed");
        

        private void Awake()
        {
            _player = GetComponent<Player>();
        }

        private void Update()
        {
            _player.Anim.SetFloat(Speed, _player.InputVec.magnitude);
        }

        private void LateUpdate()
        {
            // 플레이어의 좌우 전환
            if (_player.InputVec.x != 0)
            {
                _player.Spriter.flipX = _player.InputVec.x < 0;
            }
            
            // 플레이어의 
        }
    }
}
