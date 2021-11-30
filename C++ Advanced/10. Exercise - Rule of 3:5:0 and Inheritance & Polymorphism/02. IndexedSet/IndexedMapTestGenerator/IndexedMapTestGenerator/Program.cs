using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IndexedMapTestGenerator
{
    class Program
    {
        static Random rand = new Random();

        static void Main(string[] args)
        {
            GenerateTest("test.001", 5, 6, 10, 4);
            GenerateTest("test.002", 20, 20, 30, 17);
            GenerateTest("test.003", 30, 30, 300, 50);
            GenerateTest("test.004", 20, 50, 100, 100);
            GenerateTest("test.005", 20, 100, 100, 100);

            GenerateTest("test.006", 30, 6, 10, 1000);
            GenerateTest("test.007", 40, 200, 300, 5000);
            GenerateTest("test.008", 50, 300, 400, 5000);
            GenerateTest("test.009", 50, 1500, 2000, 5000);
            GenerateTest("test.010", 50, 2000, 2000, 5000);
        }

        static void GenerateTest(string testName, int arraysCount, int minArrayLength, int maxArrayLength, int indicesCount)
        {
            List<List<int>> arrays = new List<List<int>>();

            StringBuilder inputBuilder = new StringBuilder();
            while (arrays.Count < arraysCount)
            {
                List<int> array = new List<int>();
                int arrayLength = rand.Next(minArrayLength, maxArrayLength + 1);

                while (array.Count < arrayLength)
                {
                    array.Add(rand.Next(0, 2000));
                }

                arrays.Add(array);

                inputBuilder.AppendLine(string.Join(" ", array));
            }
            inputBuilder.AppendLine("end");

            int minActualLength = int.MaxValue;
            for (int i = 0; i < arrays.Count; i++)
            {
                arrays[i] = SortAndRemoveDuplicates(arrays[i]);
                minActualLength = minActualLength > arrays[i].Count ? arrays[i].Count : minActualLength;
            }

            List<int> indices = new List<int>();
            while (indices.Count < indicesCount)
            {
                indices.Add(rand.Next(minActualLength));
            }
            inputBuilder.AppendLine(string.Join(" ", indices));

            List<int> maxArray = null;
            for (int i = 0; i < arrays.Count; i++)
            {
                arrays[i] = SortAndRemoveDuplicates(arrays[i]);

                if (maxArray == null || SumIndices(maxArray, indices) < SumIndices(arrays[i], indices))
                {
                    maxArray = arrays[i];
                }
            }

            System.IO.File.WriteAllText(testName + ".in.txt", inputBuilder.ToString());
            System.IO.File.WriteAllText(testName + ".out.txt", string.Join(" ", maxArray));
        }

        static int SumIndices(List<int> array, List<int> indices)
        {
            int sum = 0;
            foreach (int index in indices)
            {
                sum += array[index];
            }

            return sum;
        }

        static List<int> SortAndRemoveDuplicates(List<int> array)
        {
            return new List<int>(new SortedSet<int>(array));
        }
    }
}
