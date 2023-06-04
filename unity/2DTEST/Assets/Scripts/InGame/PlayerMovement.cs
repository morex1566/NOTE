using UnityEngine;
using UnityEngine.InputSystem;

namespace InGame
{
    public class PlayerMovement : MonoBehaviour
    {
        private Player _player;

        private void Awake()
        {
            _player = GetComponent<Player>();
        }

        private void FixedUpdate()
        {
            _player.NextVec = _player.InputVec * (_player.Speed * Time.fixedDeltaTime);
            _player.Rigid2D.MovePosition(_player.Rigid2D.position + _player.NextVec);
        }
        
        public void OnMove(InputValue value)
        {
            _player.InputVec = value.Get<Vector2>();
        }
    }
}
