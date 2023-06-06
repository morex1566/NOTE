using ScriptableObject;
using UnityEngine;

namespace InGame
{
    public class Weapon : MonoBehaviour
    {
        [SerializeField] private SO_Weapon data;
        [SerializeField] public SO_Weapon Data
        {
            get => data;
            set => data = value;
        }
    }
}
