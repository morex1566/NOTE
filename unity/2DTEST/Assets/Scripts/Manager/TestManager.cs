using System.Collections;
using UnityEngine;
using Utilities;

namespace Manager
{
    public class TestManager : MonoBehaviour
    {
        private void Start()
        {
            StartCoroutine(Test_YieldInstructionCache());
        }

        private IEnumerator Test_YieldInstructionCache()
        {
            yield return  YieldInstructionCache.WaitForSeconds(5.0f);
        
            Debug.Log("Test_YieldInstructionCache");
        }
    }
}
