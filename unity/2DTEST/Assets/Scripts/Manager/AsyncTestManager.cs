using System.Collections;
using System.Threading;
using Unity.Jobs;
using UnityEngine;
using Task = System.Threading.Tasks.Task;

namespace AsyncTest
{
    public class AsyncTestManager : MonoBehaviour
    {
        private void Start()
        {
            TestNormal();
            TestCoroutine();
            TestAsync();
        }
        
        public void TestNormal() => Debug.LogFormat("동작방식 : {0}  현재 쓰레드 : {1} ", "Normal", Thread.CurrentThread.ManagedThreadId);
        public void TestCoroutine() => StartCoroutine(cor_printDebugLog());
        public void TestAsync() => async_printDebugLog();

        private async void async_printDebugLog()
        { 
            await Task.Run(()=> { Debug.LogFormat("동작방식 : {0}  현재 쓰레드 : {1} ", "Async", Thread.CurrentThread.ManagedThreadId); });
        }
        
        private IEnumerator cor_printDebugLog()
        {
            Debug.LogFormat("동작방식 : {0}  현재 쓰레드 : {1} ", "Coroutine", Thread.CurrentThread.ManagedThreadId);

            yield return null;
        }

        private IEnumerable cor_printDebugLogs()
        {
            
            
            yield return null;
        }



        private struct TestJob : IJob
        {
            public void Execute()
            {
                Debug.LogFormat("동작방식 : {0}  현재 쓰레드 : {1} ", "JobSystem", Thread.CurrentThread.ManagedThreadId);
            }
        }
    }
}
