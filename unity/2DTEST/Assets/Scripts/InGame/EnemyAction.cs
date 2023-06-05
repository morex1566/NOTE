using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Utilities;

namespace InGame
{
    public class EnemyAction : MonoBehaviour
    {
        private bool _isRepositionable;
        
        // 현재 적을 보고있는 오브젝트의 수
        private List<GameObject> _watcher = new List<GameObject>();

        #region Getter/Setter 선언

        public bool IsRepositionable
        {
            get => _isRepositionable;
            set => _isRepositionable = value;
        }

        #endregion
        public List<GameObject> Watcher
        {
            get => _watcher;
        }

        /// <summary>
        /// 적을 재배치 합니다
        /// </summary>
        /// <param name="dest">적을 재배치할 위치</param>
        /// <param name="time">적이 재배치되는데 걸리는 딜레이</param>
        public void OnRepositionAt(Vector2 dest, float time = 0f)
        {
            StartCoroutine(Reposition(dest, time));
        }

        // 적이 재배치 될 수 있는 조건
        // 1. 적어도 한번은 어떤 플레이어에게 위치가 노출되어야 합니다. (_isRepositionable)
        // 2. 현재 어떤 플레이어나 대상에게도 들키지 않아야 합니다. (_watcher.Count)
        private IEnumerator Reposition(Vector2 dest, float time)
        {
            bool isCanceled = false;
            
            while (time >= 0)
            {
                // 타이머가 끝나기 전에 관찰자가 생기면, 재배치를 종료
                if (Watcher.Count > 0)
                {
                    isCanceled = true;
                    yield break;
                }
                
                time -= Time.deltaTime;

                yield return null;
            }

            // 재배치
            if(!isCanceled)
            {
                transform.position = dest;
            }
        }
    }
}
