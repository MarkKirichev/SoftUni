using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RangesTestGenerator.RandomExtensions;

namespace RangesTestGenerator
{
    class Program
    {
        static Random random = new Random();

        static void Main(string[] args)
        {
            GenerateTest(name: "test.001", rangesCount: 4, inRangeCount: 3, onRangeEdgeCount: 0, outsideCount: 2);
            GenerateTest(name: "test.002", rangesCount: 1, inRangeCount: 1, onRangeEdgeCount: 3, outsideCount: 0);
            GenerateTest(name: "test.003", rangesCount: 10, inRangeCount: 0, onRangeEdgeCount: 1, outsideCount: 10);

            GenerateTest(name: "test.004", rangesCount: 9970, inRangeCount: 25000, onRangeEdgeCount: 15000, outsideCount: 60000);
            GenerateTest(name: "test.005", rangesCount: 9680, inRangeCount: 10000, onRangeEdgeCount: 15000, outsideCount: 25000);
            GenerateTest(name: "test.006", rangesCount: 10000, inRangeCount: 1, onRangeEdgeCount: 99999, outsideCount: 0);
            GenerateTest(name: "test.007", rangesCount: 9780, inRangeCount: 1100, onRangeEdgeCount: 0, outsideCount: 99890);
            GenerateTest(name: "test.008", rangesCount: 9920, inRangeCount: 30, onRangeEdgeCount: 99970, outsideCount: 0);
            GenerateTest(name: "test.009", rangesCount: 9990, inRangeCount: 99990, onRangeEdgeCount: 0, outsideCount: 1);
            GenerateTest(name: "test.010", rangesCount: 10000, inRangeCount: 53200, onRangeEdgeCount: 6800, outsideCount: 40000);
        }

        static void GenerateTest(string name, int rangesCount, int inRangeCount, int onRangeEdgeCount, int outsideCount)
        {
            List<int> rangeEdges = random.NextStrictlyIncreasingInRange(rangesCount * 2, new Pair<int>(int.MinValue + 1, int.MaxValue - 1));

            for (int i = 1; i < rangeEdges.Count; i+=2)
            {
                if (random.NextChance(0.1))
                {
                    rangeEdges[i] = rangeEdges[i - 1];
                }
            }

            List<int> inRange = new List<int>();
            while (inRange.Count < inRangeCount)
            {
                int rangeStartIndex = NextRangeStart(rangeEdges);

                inRange.Add(random.Next(rangeEdges[rangeStartIndex], rangeEdges[rangeStartIndex + 1] + 1));
            }

            List<int> onRangeEdge = new List<int>();
            while (onRangeEdge.Count < onRangeEdgeCount)
            {
                int rangeStartIndex = NextRangeStart(rangeEdges);

                onRangeEdge.Add(random.NextChance(0.5) ? rangeEdges[rangeStartIndex] : rangeEdges[rangeStartIndex + 1]);
            }

            List<int> outsideList = new List<int>();
            while (outsideList.Count < outsideCount)
            {
                try
                {
                    int value;
                    int rangeStartIndex = NextRangeStart(rangeEdges);

                    if (rangeStartIndex == 0)
                    {
                        value = random.Next(int.MinValue, rangeEdges[0]);
                    }
                    else if (rangeStartIndex == rangeEdges.Count - 2)
                    {
                        value = random.Next(rangeEdges[rangeEdges.Count - 1], int.MaxValue);
                    }
                    else
                    {
                        value = random.Next(rangeEdges[rangeStartIndex + 1] + 1, rangeEdges[rangeStartIndex + 2]);
                    }

                    outsideList.Add(value);
                } catch (ArgumentOutOfRangeException)
                {
                }
            }

            List<int> insideList = new List<int>(inRange);
            insideList.AddRange(onRangeEdge);
            HashSet<int> inside = new HashSet<int>(insideList);

            List<int> values = new List<int>();
            values.AddRange(insideList);
            values.AddRange(outsideList);

            random.NextShuffle(values);
            random.NextShuffle(values);

            if (values.Count != inRangeCount + onRangeEdgeCount + outsideCount) throw new Exception("Mismatch between total values and sum of in, out and on edges");

            List<string> outputLines = values.Select(v => inside.Contains(v) ? "in" : "out").ToList();

            List<string> inputLines = new List<string>();
            for (int i = 0; i < rangeEdges.Count; i+=2)
            {
                inputLines.Add(rangeEdges[i] + " " + rangeEdges[i + 1]);
            }
            inputLines.Add(".");
            inputLines.AddRange(values.Select(v => v.ToString()));
            inputLines.Add(".");

            System.IO.File.WriteAllLines(name + ".in.txt", inputLines);
            System.IO.File.WriteAllLines(name + ".out.txt", outputLines);
        }

        private static int NextRangeStart(List<int> rangeEdges)
        {
            int rangeStartIndex = random.NextIndex(rangeEdges);
            if ((rangeStartIndex & 1) != 0)
            {
                rangeStartIndex--;
            }

            return rangeStartIndex;
        }
    }

    namespace RandomExtensions
    {
        struct Pair<T>
        {
            public T First { get; set; }
            public T Second { get; set; }
            public Pair(T first, T second)
            {
                this.First = first;
                this.Second = second;
            }
        }

        static class RandomExtensions
        {
            public static bool NextChance(this Random r, double probability)
            {
                return r.NextDouble() < probability;
            }

            public static List<int> NextIncreasingOrEqualInRange(this Random r, int length, Pair<int> rangeInclusive)
            {
                List<int> values = new List<int>();
                while (values.Count < length)
                {
                    values.Add(r.Next(values.Count > 0 ? values[values.Count - 1] : rangeInclusive.First, rangeInclusive.Second + 1));
                }

                return new List<int>(values);
            }

            public static List<int> NextStrictlyIncreasingInRange(this Random r, int length, Pair<int> rangeInclusive)
            {
                long rangeElementsCount = (((long)rangeInclusive.Second) - ((long)rangeInclusive.First)) + 1;
                if (rangeElementsCount < length)
                {
                    throw new ArgumentException("rangeInclusive does not contain enough values to generate required length");
                }

                SortedSet<int> values = new SortedSet<int>();
                while (values.Count < length)
                {
                    values.Add(r.Next(rangeInclusive.First, rangeInclusive.Second + 1));
                }

                return new List<int>(values);
            }

            public static void NextShuffle<T>(this Random r, List<T> list)
            {
                for (int repeats = 0; repeats < 10; repeats++)
                {
                    for (int i = 0; i < list.Count; i++)
                    {
                        int otherInd = r.Next(0, list.Count);
                        var swap = list[i];
                        list[i] = list[otherInd];
                        list[otherInd] = swap;
                    }
                }
            }

            public static int NextIndex<T>(this Random r, ICollection<T> range)
            {
                return r.Next(0, range.Count);
            }

            public static T NextFrom<T>(this Random r, List<T> from)
            {
                return from[NextIndex(r, from)];
            }

            public static List<int> NextIntegersFrom(this Random r, int count, List<int> from)
            {
                List<int> integers = new List<int>();

                while (integers.Count < count)
                {
                    integers.Add(NextFrom(r, from));
                }

                return integers;
            }

            public static List<int> NextIntegers(this Random r, int count)
            {
                return NextIntegersExcluding(r, count, new HashSet<int>());
            }

            public static List<int> NextIntegersExcluding(this Random r, int count, HashSet<int> excluded)
            {
                List<int> integers = new List<int>();

                while (integers.Count < count)
                {
                    integers.Add(NextExcluding(r, excluded));
                }

                return integers;
            }

            public static int NextExcluding(this Random r, HashSet<int> excluded)
            {
                int value = r.Next();
                while (excluded.Contains(value))
                {
                    value = r.Next();
                }

                return value;
            }
        }
    }

}
