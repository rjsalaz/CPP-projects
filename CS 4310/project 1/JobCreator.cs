//You can use this program to generate 20 trials of 20 job.txt files that can be used for experimental testing by the algorithms

using System;
using System.IO; 


namespace JobCreator    
{
    class JobCreator
    {
        static void Main( )
        {
            //Number of jobs to create
            int numOfJobs = 15;
            int[] jobs = new int[numOfJobs];
            string currentJob;
            //Generate random numbers 
            Random rand = new Random();

            // While loop will create 20 jobs.txt files per trial
            // With the specified number of jobs
            //There is a total of 20 trials
            for ( int counter = 0; counter  < 20; counter++)
            {
                for ( int innerCounter = 0; innerCounter< 20; innerCounter++)
                {
                    currentJob = "job";

                    currentJob += "["+ counter.ToString() +"]"+ "[" + innerCounter.ToString() +"]" + ".txt";

                    for (int i = 0; i < numOfJobs; i++)
                    {
                        //Each job will have random length value between 20 and 100
                        jobs[i] = rand.Next(20, 101);

                    }

                    // Write jobs to a file
                    using StreamWriter sw = new StreamWriter(currentJob);
                    for (int i = 0; i < numOfJobs; i++)
                    {

                        sw.WriteLine("Job" + (i + 1));
                        sw.WriteLine(jobs[i]);

                    }

                }
            }
        }
    }
}
