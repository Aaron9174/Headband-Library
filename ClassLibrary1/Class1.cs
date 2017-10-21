using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Task;

namespace headbandController
{
    public class Movement
    {
        public int c;

        public void addValues(int a, int b)
        {
            c = a + b;
        }

        public static int generateRandom(int min, int max)
        {
            System.Random rand = new System.Random();
            return rand.Next(min, max); 
        }
    }
}
