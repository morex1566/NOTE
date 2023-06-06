using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace InGame
{
    public class EnemySpawner : MonoBehaviour
    {
        [SerializeField] private GameObject[] enemyPrefabList;
        [SerializeField] public GameObject[] EnemyPrefabList
        {
            get => enemyPrefabList;
            set => enemyPrefabList = value;
        }
        
        private bool _isSpawnable = true;
        public bool IsSpawnable
        {
            get => _isSpawnable;
            set => _isSpawnable = value;
        }

        private List<GameObject>[] _enemyPools;
        // public GameObject Get(int index)
        // {
        //     
        // }

        
        private void Awake()
        {
            _enemyPools = new List<GameObject>[enemyPrefabList.Length];
            for (int i = 0; i < _enemyPools.Length; i++)
            {
                _enemyPools[i] = new List<GameObject>();
            }
        }

        private void Start()
        {
            StartCoroutine(spawn(3f));
        }

        
        /// <summary>
        /// 정해진 시간간격마다 적을 생성
        /// </summary>
        /// <param name="time">스폰 대기시간</param>
        private IEnumerator spawn(float time)
        {
            while (_isSpawnable)
            {
                yield return new WaitForSeconds(time);

                if (_isSpawnable)
                {
                    Instantiate(enemyPrefabList[0], transform.position, Quaternion.identity);
                }
            }
        }
    }
}