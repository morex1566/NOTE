using ScriptableObject;
using UnityEngine;

public class Sword : MonoBehaviour
{
    [SerializeField] private SO_Weapon weaponData;
    
    private void Start()
    {
        Debug.Log(weaponData.Damage);
    }
}
