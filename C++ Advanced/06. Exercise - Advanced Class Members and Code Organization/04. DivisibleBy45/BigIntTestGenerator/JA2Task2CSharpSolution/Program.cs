using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace JA2Task2CSharpSolution
{
    class Program
    {
        static void Main(string[] args)
        {
            BigInteger start;
            BigInteger end;

            start = BigInteger.Parse(Console.ReadLine());
            end = BigInteger.Parse(Console.ReadLine());

            for (BigInteger i = start; i < end; i++)
            {
                if (i % 45 == 0)
                {
                    Console.WriteLine(i);
                }
            }
        }
    }
}
