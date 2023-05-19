using System;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.InputSystem;

public class EventManager : MonoBehaviour
{
    public static EventManager Instance = null;

    [Header("인스턴싱 대상")] 
    [Space(5)]
    [SerializeField] private GameObject cube;

    private void Awake()
    {
        if (!Instance)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void OnCreateCube(InputValue value)
    {
        // 리소스 로딩
        Addressables.InstantiateAsync("Main_Cube").Completed += handle =>
        {
            cube = handle.Result;
        };
    }

    private void OnReleaseCube(InputValue value)
    {
        if (cube)
        {
            Addressables.ReleaseInstance(cube);
        }
    }
}
