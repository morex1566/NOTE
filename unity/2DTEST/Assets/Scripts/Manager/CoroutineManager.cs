#nullable enable
using UnityEngine;

namespace Manager
{
    public class CoroutineManager : MonoBehaviour
    {
        private static CoroutineManager? _instance;

        public static CoroutineManager? GetInstance()
        {
            if (!_instance)
            {
                GameObject manager = new GameObject("Coroutine Manager");
                CoroutineManager component = manager.AddComponent<CoroutineManager>();
                DontDestroyOnLoad(manager);

                _instance = component;
            }

            return _instance;
        }

        private void Start()
        {
            Debug.Log("Start CoroutineManager");
        }
    }
}