using System;
using System.Collections.Generic;
using ScriptableObject;
using UnityEngine;

namespace InGame
{
    public class WeaponRange : MonoBehaviour
    {
        private SO_Weapon _data;
        private CircleCollider2D _boundary;

        private List<GameObject> _targets;
        public List<GameObject> Targets
        {
            get => _targets;
            private set => _targets = value;
        }

        private void Awake()
        {
            _data = GetComponentInParent<Weapon>().Data;
            _boundary = GetComponent<CircleCollider2D>();
            _targets = new List<GameObject>();
        }

        private void Start()
        {
            _boundary.radius = _data.Range;
        }

        private void OnTriggerEnter2D(Collider2D opponent)
        {
            _targets.Add(opponent.gameObject);
        }

        private void OnTriggerExit2D(Collider2D opponent)
        {
            _targets.Remove(opponent.gameObject);
        }
    }
}
