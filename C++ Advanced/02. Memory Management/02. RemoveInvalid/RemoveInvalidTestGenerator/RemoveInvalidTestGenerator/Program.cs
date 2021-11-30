using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RandomExtensions;

namespace RemoveInvalidTestGenerator
{
    class Program
    {
        static Random r = new Random();

        static void Main(string[] args)
        {
            int divider = 4;
            GenerateTest(testName: "test.001", validCompaniesCount: 2, invalidCompaniesCount: 3);
            GenerateTest(testName: "test.002", validCompaniesCount: 1, invalidCompaniesCount: 0);
            GenerateTest(testName: "test.003", validCompaniesCount: 0, invalidCompaniesCount: 1);
            GenerateTest(testName: "test.004", validCompaniesCount: 4, invalidCompaniesCount: 2);
            GenerateTest(testName: "test.005", validCompaniesCount: 3, invalidCompaniesCount: 7);

            GenerateTest(testName: "test.006", validCompaniesCount: 10000 / divider, invalidCompaniesCount: 600000 / divider);
            GenerateTest(testName: "test.007", validCompaniesCount: 9000 / divider, invalidCompaniesCount: 700000 / divider);
            GenerateTest(testName: "test.008", validCompaniesCount: 8000 / divider, invalidCompaniesCount: 800000 / divider);
            GenerateTest(testName: "test.009", validCompaniesCount: 7000 / divider, invalidCompaniesCount: 900000 / divider);
            GenerateTest(testName: "test.010", validCompaniesCount: 6000 / divider, invalidCompaniesCount: 1000000 / divider);
        }

        class Company
        {
            public int Id { get; }
            public string Name { get; }

            public Company(int id, string name)
            {
                this.Id = id;
                this.Name = name;
            }

            public override string ToString()
            {
                return Id + " " + Name;
            }
        }

        private static void GenerateTest(string testName, int validCompaniesCount, int invalidCompaniesCount)
        {
            HashSet<int> ids = r.NextUniqueN(validCompaniesCount, () => r.Next(0, 1000000));

            List<Company> validCompanies = new List<Company>();
            List<Company> invalidCompanies = new List<Company>();
            List<Company> companies = new List<Company>();

            while (validCompanies.Count < validCompaniesCount || invalidCompanies.Count < invalidCompaniesCount)
            {
                int remainingValid = validCompaniesCount - validCompanies.Count;
                int remainingInvalid = invalidCompaniesCount - invalidCompanies.Count;
                int remainingTotal = remainingValid + remainingInvalid;

                Company c;
                if (r.NextChance(remainingValid / (double)remainingTotal))
                {
                    validCompanies.Add(c = new Company(ids.First(), r.NextWord(r.Next(1, 6 + 1), 0)));
                    ids.Remove(ids.First());
                }
                else
                {
                    invalidCompanies.Add(c = new Company(r.Next(-1000000, 0), r.NextWord(r.Next(1, 6 + 1), 0)));
                }

                companies.Add(c);
            }

            IEnumerable<string> allCompanyStrings = companies.Select(c => c.ToString());
            IEnumerable<string> validCompanyStrings = validCompanies.Select(c => c.ToString());
            System.IO.File.WriteAllText(testName + ".in.txt", string.Join(Environment.NewLine, allCompanyStrings) + System.Environment.NewLine + "end");
            System.IO.File.WriteAllText(testName + ".out.txt", string.Join(System.Environment.NewLine, validCompanyStrings));
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

        public static char NextLetter(this Random r, bool capital)
        {
            return (char)(capital ? r.Next('A', 'Z' + 1) : r.Next('a', 'z' + 1));
        }

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