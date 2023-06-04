using System.Collections.Generic;
using UnityEngine;

namespace Utilities
{
    public static class YieldInstructionCache
    {
        private static readonly Dictionary<float, WaitForSeconds> WaitForSecondsMap = new Dictionary<float, WaitForSeconds>();
        public static WaitForSeconds WaitForSeconds(float time)
        {
            WaitForSeconds wfs;
            {
                if (!WaitForSecondsMap.TryGetValue(time, out wfs))
                {
                    wfs = new WaitForSeconds(time);
                    WaitForSecondsMap.Add(time, wfs);
                }
            }
            
            return wfs;
        }
    }

}