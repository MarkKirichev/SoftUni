using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace JA2Task2TestGenerator
{
    class Program
    {
        static Random rand = new Random();
        static BigInteger min = 1;

        static void Main(string[] args)
        {
            generateTest("test.001");
            generateTest("test.002");
            generateTest("test.003");
            generateTest("test.004");
            generateTest("test.005");
            generateTest("test.006", BigInteger.Parse("295054705193197853448422496418309845554191072600219287942999999999999999999999999"), 10);
            generateTest("test.007", BigInteger.Parse("9"), 20);
            generateTest("test.008", BigInteger.Parse("295054705193197853448422496418309845554191072600219287942099909990999099909990999"), 30);
            generateTest("test.009", BigInteger.Parse("295054705193197853448422496418309845554191072600219287942099909990999099909993210"), 40);
            generateTest("test.010", BigInteger.Parse("999999999999999999999999999999999999999999999999999999999999999999999999999999999"), 100);
        }

        private static void generateTest(string testName, int generatedCount = 0)
        {
            generateTest(testName, new BigInteger(0), generatedCount);
        }

        private static void generateTest(string testName, BigInteger start, int generatedCount = 0)
        {
            start = start != 0 ? start : min * rand.Next();

            min = start * (long)Math.Abs(1000000 * rand.NextDouble());

            BigInteger first;
            for (first = start; first % 45 != 0; first++) { }

            List<BigInteger> generated = new List<BigInteger>();
            generatedCount = generatedCount != 0 ? generatedCount : rand.Next(1, 100);
            for (int i = 0; i < generatedCount; i++)
            {
                BigInteger next = first + (45 * i);
                generated.Add(next);
            }

            BigInteger end = generated[generated.Count - 1] + rand.Next(1, 45);

            System.IO.File.WriteAllText(testName + ".in.txt", start + System.Environment.NewLine + end);
            System.IO.File.WriteAllText(testName + ".out.txt", string.Join(System.Environment.NewLine, generated));
        }
    }
}
