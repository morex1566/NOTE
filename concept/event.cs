/*
 *  New Concept     : event-driven
 */

namespace EventTest
{
    public class Test
    {
        // Action 사용
        public Action? ButtonAction;
        
        // event 사용
        public event EventHandler? ButtonEvent;
        
        // delegate 사용
        public delegate void ButtonDelegateType();
        public ButtonDelegateType? ButtonDelegate;
        
        public void TestFunction()
        {
            Console.WriteLine("TestFunctionForAction test success");
        }
        
        public void TestFunctionForEvent1(object? sender, EventArgs args)
        {
            Console.WriteLine("TestFunctionForEvent test success");
        }
        
        public void TestFunctionForEvent2(object? sender, EventArgs args)
        {
            Console.WriteLine("TestFunctionForEvent test success");
        }
    
        
        public void Start<T>(T? obj) where T : Program
        {
            ButtonEvent?.Invoke(obj, EventArgs.Empty);
        }
    }
    
    public class Program
    {
        public static void Main()
        {
            Test test = new Test();
    
            test.ButtonAction = test.TestFunction;
            test.ButtonEvent += test.TestFunctionForEvent1;
            test.ButtonEvent += test.TestFunctionForEvent2;
            test.ButtonEvent += (object? sender, EventArgs args) => { Console.WriteLine("lamda function test success"); };
            test.ButtonDelegate = test.TestFunction;
            
            test.ButtonAction?.Invoke();
            test.ButtonDelegate.Invoke();
            test.Start<Program>(null);
        }
    }
}