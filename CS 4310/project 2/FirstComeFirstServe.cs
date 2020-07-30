using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Project2
{
    class FirstComeFirstServe
    {

        private readonly string referenceString;
        private readonly int numOfPageFrames; 


        public FirstComeFirstServe(string numOfPageframesPar, string referenceStringPar)
        {
            
            this.numOfPageFrames = Int32.Parse(numOfPageframesPar);  
            this.referenceString = referenceStringPar; 

        }

        public String RunAlgo()
        {
            int pageFaults = 0; 
            HashSet<char> setOfPages = new HashSet<char>(numOfPageFrames);
            Queue queueOfPages = new Queue(); 

            for( int i = 0; i < this.referenceString.Length; i++ )
            {
                if (setOfPages.Count < numOfPageFrames)
                {

                    if (!setOfPages.Contains(referenceString[i]))
                    {
                        setOfPages.Add(referenceString[i]);
                        queueOfPages.Enqueue(referenceString[i]);

                        pageFaults++;

                    }
                }
                else
                {
                    if( !setOfPages.Contains(referenceString[i]) )
                    {

                        char firstQueuePage = (char)queueOfPages.Peek();
                        queueOfPages.Dequeue();

                        setOfPages.Remove(firstQueuePage);
                        setOfPages.Add(referenceString[i]);

                        queueOfPages.Enqueue(referenceString[i]);

                        pageFaults++; 

                    }

                }

            }

            return pageFaults.ToString(); 
        }





    }
}
