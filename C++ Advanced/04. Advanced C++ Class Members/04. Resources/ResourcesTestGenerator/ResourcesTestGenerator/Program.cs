using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RandomExtensions;

namespace ResourcesTestGenerator
{
    class Resource
    {
        public readonly int id;
        public readonly string type;
        public readonly string link;

        public Resource(int id, string type, string link)
        {
            this.id = id;
            this.type = type;
            this.link = link;
        }

        public override string ToString()
        {
            return id + " " + type + " " + link;
        }
    }

    class Program
    {
        static Random random = new Random();

        static void Main(string[] args)
        {
            GenerateTest(testName: "test.001", presentationsCount: 2, demosCount: 3, videosCount: 1);
            GenerateTest(testName: "test.002", presentationsCount: 1, demosCount: 0, videosCount: 0);
            GenerateTest(testName: "test.003", presentationsCount: 0, demosCount: 1, videosCount: 0);
            GenerateTest(testName: "test.004", presentationsCount: 0, demosCount: 0, videosCount: 1);
            GenerateTest(testName: "test.005", presentationsCount: 10, demosCount: 30, videosCount: 10);

            GenerateTest(testName: "test.006", presentationsCount: 20, demosCount: 1, videosCount: 1);
            GenerateTest(testName: "test.007", presentationsCount: 1, demosCount: 30, videosCount: 1);
            GenerateTest(testName: "test.008", presentationsCount: 1, demosCount: 1, videosCount: 10);
            GenerateTest(testName: "test.009", presentationsCount: 20, demosCount: 3, videosCount: 27);
            GenerateTest(testName: "test.010", presentationsCount: 12, demosCount: 13, videosCount: 25);
        }

        static void GenerateTest(string testName, int presentationsCount, int demosCount, int videosCount)
        {
            List<Resource> orderedResources = new List<Resource>();
            List<Resource> presentations = new List<Resource>(); ;
            List<Resource> demos = new List<Resource>();
            List<Resource> videos = new List<Resource>();

            while (presentations.Count < presentationsCount || demos.Count < demosCount || videos.Count < videosCount)
            {
                int minId = orderedResources.Count > 0 ? orderedResources[orderedResources.Count - 1].id + 1 : 1;
                int id = random.Next(minId, minId + 100);
                string url = "http://" + random.NextWord(random.Next(3, 10), 0) + "." + random.NextWord(3, 0);

                Resource r;
                if (presentations.Count < presentationsCount && random.NextChance(0.33))
                {
                    r = new Resource(id, "Presentation", url);
                    presentations.Add(r);
                }
                else if (demos.Count < demosCount && random.NextChance(0.33))
                {
                    r = new Resource(id, "Demo", url);
                    demos.Add(r);
                }
                else if (videos.Count < videosCount)
                {
                    r = new Resource(id, "Video", url);
                    videos.Add(r);
                }
                else
                {
                    r = null;
                }

                if (r != null)
                {
                    orderedResources.Add(r);
                }
            }

            List<string> outputLines = new List<string>();
            outputLines.Add("... by id:");
            outputLines.AddRange(orderedResources.Select(r => r.ToString()).ToList());
            outputLines.Add("... by type:");
            if (presentations.Count != 0)
            {
                outputLines.Add("Presentation: " + presentations.Count);
            }
            if (demos.Count != 0)
            {
                outputLines.Add("Demo: " + demos.Count);
            }
            if (videos.Count != 0)
            {
                outputLines.Add("Video: " + videos.Count);
            }

            List<Resource> inputResources = new List<Resource>(orderedResources);

            random.NextShuffle(inputResources);

            List<string> inputLines = new List<string>();
            inputLines.Add(inputResources.Count + "");
            inputLines.AddRange(inputResources.Select(r => r.ToString()).ToList());

            System.IO.File.WriteAllLines(testName + ".in.txt", inputLines);
            System.IO.File.WriteAllLines(testName + ".out.txt", outputLines);
        }
    }
}

namespace RandomExtensions
{
    class Pair<T>
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
        const string Vowels = "aeiouwy";
        const string Consonants = "bcdfghjklmnpqrstvwxz";

        public static HashSet<T> NextUniqueN<T>(this Random r, int count, Func<T> generator)
        {
            HashSet<T> unique = new HashSet<T>();

            while (unique.Count < count)
            {
                unique.Add(generator.Invoke());
            }

            return unique;
        }

        public static string NextWord(this Random r, int length, double capitalsChance)
        {
            StringBuilder word = new StringBuilder();

            while (word.Length < length)
            {
                string source;
                if (word.Length == 0)
                {
                    source = r.NextChance(0.5) ? Vowels : Consonants;
                }
                else if (Vowels.Contains(word[word.Length - 1]))
                {
                    source = r.NextChance(0.8) ? Consonants : Vowels;
                }
                else
                {
                    source = r.NextChance(0.8) ? Vowels : Consonants;
                }

                word.Append(source[r.Next(0, source.Length)]);
            }

            for (int i = 0; i < word.Length; i++)
            {
                word[i] = r.NextChance(capitalsChance) ? char.ToUpper(word[i]) : word[i];
            }

            return word.ToString();
        }

        public static bool NextChance(this Random r, double probability)
        {
            // NOTE: 0 probability is always false (min NextDouble() is 0, 0 < 0 is false) and 1 probability is always true (NextDouble() always returns less than 1)
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
            int rangeElementsCount = (rangeInclusive.Second - rangeInclusive.First) + 1;
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