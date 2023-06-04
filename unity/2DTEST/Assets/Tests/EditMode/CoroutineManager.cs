using System.Collections;
using NUnit.Framework;
using UnityEngine;
using UnityEngine.TestTools;
using Utilities;

namespace Tests.EditMode
{
    public class CoroutineManager
    {
        [UnityTest]
        public IEnumerator WaitForSeconds_ReturnsCorrectInstance()
        {
            WaitForSeconds wait1 = Utilities.YieldInstructionCache.WaitForSeconds(1.0f);
            WaitForSeconds wait2 = Utilities.YieldInstructionCache.WaitForSeconds(2.0f);
            WaitForSeconds wait3 = Utilities.YieldInstructionCache.WaitForSeconds(1.0f);
        
            Assert.AreSame(wait1, wait3);  // 같은 시간에 대한 WaitForSeconds 인스턴스는 동일해야 함
            Assert.AreNotSame(wait1, wait2);  // 다른 시간에 대한 WaitForSeconds 인스턴스는 다름
        
            yield return null;
        }
    }
}
