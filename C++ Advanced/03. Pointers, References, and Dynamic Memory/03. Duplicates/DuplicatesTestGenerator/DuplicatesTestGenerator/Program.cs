using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RandomExtensions;

namespace DuplicatesTestGenerator
{
    class Program
    {
        static Random r = new Random();

        static void Main(string[] args)
        {
            GenerateTest(testName: "test.001", companiesCount: 2, minEmployees: 3, maxEmployees: 3, copiesCount: 1, pointersCount: 2);
            GenerateTest(testName: "test.002", companiesCount: 1, minEmployees: 3, maxEmployees: 3, copiesCount: 3, pointersCount: 0);
            GenerateTest(testName: "test.003", companiesCount: 1, minEmployees: 1, maxEmployees: 1, copiesCount: 0, pointersCount: 3);
            GenerateTest(testName: "test.004", companiesCount: 1, minEmployees: 0, maxEmployees: 0, copiesCount: 0, pointersCount: 0);
            GenerateTest(testName: "test.005", companiesCount: 10, minEmployees: 3, maxEmployees: 9, copiesCount: 0, pointersCount: 0);

            GenerateTest(testName: "test.006", companiesCount: 20, minEmployees: 3, maxEmployees: 50, copiesCount: 10, pointersCount: 20);
            GenerateTest(testName: "test.007", companiesCount: 10, minEmployees: 3, maxEmployees: 3, copiesCount: 0, pointersCount: 300);
            GenerateTest(testName: "test.008", companiesCount: 1, minEmployees: 10, maxEmployees: 10, copiesCount: 300, pointersCount: 0);
            GenerateTest(testName: "test.009", companiesCount: 10, minEmployees: 10, maxEmployees: 100, copiesCount: 60, pointersCount: 30000);
            GenerateTest(testName: "test.010", companiesCount: 100, minEmployees: 255, maxEmployees: 255, copiesCount: 500, pointersCount: 10000);
        }

        class Company
        {
            public string Name { get; }
            public List<Pair<char>> EmployeeInitials { get; }

            public Company(string name, List<Pair<char>> employeeInitials)
            {
                this.Name = name;
                this.EmployeeInitials = employeeInitials;
            }

            public override string ToString()
            {
                return Name + " (" + string.Join(",", EmployeeInitials.Select(p => p.First + "." + p.Second + ".")) + ")";
            }
        }

        private static void GenerateTest(string testName, int companiesCount, int minEmployees, int maxEmployees, int copiesCount, int pointersCount)
        {
            HashSet<string> names = r.NextUniqueN(companiesCount, () => r.NextWord(r.Next(1, 6 + 1), 0));

            List<Company> companies = new List<Company>();
            foreach (var name in names)
            {
                List<Pair<char>> employeeInitials;
                if (maxEmployees > 0)
                {
                    employeeInitials = r.NextUniqueN(r.Next(minEmployees, maxEmployees + 1), () => new Pair<char>(r.NextLetter(true), r.NextLetter(true))).ToList();
                }
                else
                {
                    employeeInitials = new List<Pair<char>>();
                }

                companies.Add(new Company(name, employeeInitials));
            }

            Dictionary<string, Company> companiesByName = companies.ToDictionary(c => c.Name);
            List<Company> duplicates = new List<Company>();
            int pointers = 0, copies = 0;
            List<string> inputLines = new List<string>();

            inputLines.Add(companies[0].ToString());
            duplicates.Add(companies[0]);
            int i = 1;
            while(i < companies.Count)
            {
                if (r.NextChance(0.1))
                {
                    inputLines.Add(companies[i].ToString());
                    duplicates.Add(companies[i]);
                    i++;
                }
                else if (r.NextChance(1 - (pointers/(double)pointersCount)))
                {
                    AddPointer(duplicates, inputLines, companies[i - 1]);

                    pointers++;
                }
                else if (r.NextChance(1 - (copies/(double)copiesCount)))
                {
                    AddCopy(duplicates, inputLines, companies[i - 1]);

                    copies++;
                }
                else
                {
                    inputLines.Add(companies[i].ToString());
                    duplicates.Add(companies[i]);
                    i++;
                }
            }

            while (pointers < pointersCount)
            {
                AddPointer(duplicates, inputLines, companies.Last());
                pointers++;
            }

            while (copies < copiesCount)
            {
                AddCopy(duplicates, inputLines, companies.Last());
                copies++;
            }

            HashSet<string> filteredNames = new HashSet<string>();
            List<Company> filtered = new List<Company>();
            foreach (var item in duplicates)
            {
                if (!filteredNames.Contains(item.Name))
                {
                    filtered.Add(item);
                    filteredNames.Add(item.Name);
                }
            }

            inputLines.Add("end");
            System.IO.File.WriteAllText(testName + ".in.txt", string.Join(System.Environment.NewLine, inputLines));
            System.IO.File.WriteAllText(testName + ".out.txt", string.Join(System.Environment.NewLine, filtered));
        }

        private static void AddCopy(List<Company> duplicates, List<string> inputLines, Company c)
        {
            duplicates.Add(c);
            inputLines.Add(c.ToString());
        }

        private static void AddPointer(List<Company> duplicates, List<string> inputLines, Company c)
        {
            if (r.NextChance(0.5))
            {
                inputLines.Add("*begin");
                duplicates.Insert(0, c);
            }
            else
            {
                inputLines.Add("*end");
                duplicates.Insert(duplicates.Count, c);
            }
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
