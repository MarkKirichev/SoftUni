using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RandomExtensions;

namespace WordsTestGenerator
{
    class Program
    {
        static Random random = new Random();

        static void Main(string[] args)
        {
            GenerateTest(testName: "test.001", firstLineUniqueCount: 5, firstLineDuplicatesCount: 2, reusedCount: 0, secondLineUniqueCount: 2, secondLineDuplicatesCount: 1);
            GenerateTest(testName: "test.002", firstLineUniqueCount: 5, firstLineDuplicatesCount: 12, reusedCount: 0, secondLineUniqueCount: 2, secondLineDuplicatesCount: 1);
            GenerateTest(testName: "test.003", firstLineUniqueCount: 5, firstLineDuplicatesCount: 0, reusedCount: 0, secondLineUniqueCount: 2, secondLineDuplicatesCount: 1);
            GenerateTest(testName: "test.004", firstLineUniqueCount: 1, firstLineDuplicatesCount: 0, reusedCount: 0, secondLineUniqueCount: 1, secondLineDuplicatesCount: 0);
            GenerateTest(testName: "test.005", firstLineUniqueCount: 1, firstLineDuplicatesCount: 0, reusedCount: 0, secondLineUniqueCount: 5, secondLineDuplicatesCount: 12);

            GenerateTest(testName: "test.006", firstLineUniqueCount: 5, firstLineDuplicatesCount: 2, reusedCount: 1, secondLineUniqueCount: 2, secondLineDuplicatesCount: 1);
            GenerateTest(testName: "test.007", firstLineUniqueCount: 5, firstLineDuplicatesCount: 12, reusedCount: 2, secondLineUniqueCount: 2, secondLineDuplicatesCount: 1);
            GenerateTest(testName: "test.008", firstLineUniqueCount: 15, firstLineDuplicatesCount: 10, reusedCount: 8, secondLineUniqueCount: 30, secondLineDuplicatesCount: 8);
            GenerateTest(testName: "test.009", firstLineUniqueCount: 30, firstLineDuplicatesCount: 0, reusedCount: 20, secondLineUniqueCount: 30, secondLineDuplicatesCount: 0);
            GenerateTest(testName: "test.010", firstLineUniqueCount: 30, firstLineDuplicatesCount: 30, reusedCount: 60, secondLineUniqueCount: 60, secondLineDuplicatesCount: 60);
        }

        static void GenerateTest(string testName, int firstLineUniqueCount, int firstLineDuplicatesCount, int reusedCount, int secondLineUniqueCount, int secondLineDuplicatesCount)
        {
            Pair<string> firstLine = GenerateTestLine(firstLineUniqueCount, firstLineDuplicatesCount, new List<string>());
            List<string> firstLineWords = firstLine.First.Split(' ').ToList();
            List<string> reused = new List<string>();
            while (reused.Count < reusedCount) {
                reused.Add(random.NextFrom(firstLineWords));
            }

            Pair<string> secondLine = GenerateTestLine(secondLineUniqueCount, secondLineDuplicatesCount, reused);


            System.IO.File.WriteAllLines(testName + ".in.txt", new string[] { firstLine.First, secondLine.First });
            System.IO.File.WriteAllLines(testName + ".out.txt", new string[] { firstLine.Second, "---" , secondLine.Second });
        }

        static Pair<string> GenerateTestLine(int uniqueCount, int duplicatesCount, List<string> startingWords)
        {
            HashSet<string> uniqueSet = new HashSet<string>(startingWords);
            while (uniqueSet.Count < uniqueCount)
            {
                uniqueSet.Add(random.NextWord(random.Next(1, 10), 0));
            }

            List<string> words = new List<string>(uniqueSet);

            SortedDictionary<string, int> wordCounts = new SortedDictionary<string, int>();
            foreach (var w in words)
            {
                wordCounts.Add(w, 1);
            }
            
            for (int i = 0; i < duplicatesCount; i++)
            {
                string word = random.NextFrom(words);
                wordCounts[word]++;
                words.Add(word);
            }

            random.NextShuffle(words);

            return new Pair<string>(string.Join(" ", words), string.Join(Environment.NewLine, wordCounts.Select(wordCount => wordCount.Key + " " + wordCount.Value)));
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

        public static string NextUrl(this Random random)
        {
            return "http://" + random.NextWord(random.Next(3, 10), 0) + "." + random.NextWord(3, 0);
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

