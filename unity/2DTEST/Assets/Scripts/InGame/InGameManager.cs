using System;
using System.Collections.Generic;
using UnityEngine;

namespace InGame
{
    public class InGameManager : MonoBehaviour
    {
        public static InGameManager Instance;

        private List<GameObject> _playerList = new List<GameObject>();
        public List<GameObject> PlayerList
        {
            get => _playerList;
            private set => _playerList = value;
        }

        private void Awake()
        {
            if (Instance == null)
            {
                Instance = this;
            }
            else
            {
                Destroy(gameObject);
                return;
            }
        }

        private void Start()
        {
            GameObject[] playerList = GameObject.FindGameObjectsWithTag("Player");
            {
                foreach (var player in playerList)
                {
                    _playerList.Add(player);
                }
            }
        }
    }
}
