/*
 *  New Concept     : async
 */

using System;
using System.Diagnostics;
using System.Net.Mail;

class Program
{
    static int currentWorkCount = 0;
    
    class Data
    {
        public void LoadData()
        {
            int thisWorkCount = currentWorkCount;
            currentWorkCount += 1;

            Task.Run(async () =>
            {
                for (int i = 0; i < 100; i++)
                {
                    Console.SetCursorPosition(0,thisWorkCount);
                    Console.Write(i);
                    Console.SetCursorPosition(0,currentWorkCount + 3);
                    await Task.Delay(10);
                }

                currentWorkCount--;
            });
        }
    }

    public static void Main()
    {
        bool done = false;
        while (!done)
        {
            Console.SetCursorPosition(0,currentWorkCount);
            Console.WriteLine("메뉴를 선택하세요!!");
            Console.WriteLine("1 : 파일 로딩");
            Console.WriteLine("2 : 프로그램 종료");

            int input = Console.Read() - '0';

            switch (input)
            {
                case 1:
                    Data data = new Data();
                    data.LoadData();
                    break;
                case 2:
                    done = true;
                    break;
            }
        }
    }
 }