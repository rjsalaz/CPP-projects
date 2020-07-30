using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Runtime.InteropServices;
using System.Text;

namespace Project2
{
    class LeastRecentlyUsed
    {

        private readonly string referenceString;
        private readonly int numOfPageFrames;

        
        private readonly HashSet<char> setOfPages;
        private readonly Dictionary<char, int> dictOfPages = new Dictionary<char, int>();

        private int pageFaults = 0;
        private int maxValue;
        private int minvalue;
        
        public LeastRecentlyUsed(string numOfPageframesPar, string referenceStringPar)
        {

            this.numOfPageFrames = Int32.Parse(numOfPageframesPar);
            this.referenceString = referenceStringPar;
            setOfPages = new HashSet<char>(this.numOfPageFrames);


        }

        public string RunAlgo()
        {

            for(int i = 0; i < referenceString.Length; i++)
            {

                if( setOfPages.Count < numOfPageFrames )
                {

                    if( !setOfPages.Contains(referenceString[i]) )
                    {
                        setOfPages.Add(referenceString[i]);
                        pageFaults++; 
                    }

                    if(dictOfPages.ContainsKey(referenceString[i]))
                    {
                        dictOfPages[referenceString[i]] = i; 

                    }
                    else
                    {
                        dictOfPages.Add(referenceString[i], i);
                    }

                }
                else
                {
                    if( !setOfPages.Contains(referenceString[i]) )
                    {

                        maxValue = int.MaxValue;
                        minvalue = int.MinValue;

                        //Find the least recently used
                        foreach( char currentPage in setOfPages)
                        {
                            
                            int temp = Int32.Parse(currentPage.ToString()); 

                            if(dictOfPages[(char)temp] < maxValue)
                            {
                                maxValue = dictOfPages[(char)temp];
                                minvalue = temp; 
                            }

                        }

                        setOfPages.Remove((char)minvalue);
                        dictOfPages.Remove((char)minvalue);

                        setOfPages.Add(referenceString[i]);

                        pageFaults++;

                    }

                    if (dictOfPages.ContainsKey(referenceString[i]))
                    {
                        dictOfPages[referenceString[i]] = i;

                    }
                    else
                    {
                        dictOfPages.Add(referenceString[i], i);
                    }

                }

            }

            return pageFaults.ToString(); 

        }

    }
}
