/*
 @author: Randy Salazar 
 email: rjsalazar@cpp.edu
 Program: RoundRobinTimeSlice2.cs
 Due Date: 4/7/2020
 Description: This is my implementation of the Round Robin with Time Slice 2 algorithm. I left code that was used to test 20 trials of 20 sets in the program, 
              but it's all commented out. This program has it own function called CreateJobTxtFile(numOfJobs), that will create its own job.txt file with the 
              specified number of jobs that was used for testing. If you dont want to use this function for grading, then you'll have to a change the 
              file path to your job.txt file in GetJobTxtFileContent(). This program will only take one job.txt file at a time. Once the file path is set in 
              GetJobTxtFileContent() the program is ready to run. If you have any questions you can contanct me using the email address provided above. 
 */


using System;
using System.IO;

namespace RoundRobinTimeSlice2
{
    class RoundRobinTimeSlice2
    {

        static void CreateJobTxtFile(int numOfJobs)
        {
            //Number of jobs to create
            int[] jobs = new int[numOfJobs];

            //Generate random numbers 
            Random rand = new Random();


            // Create array of random interger of range 1-20
            for (int i = 0; i < numOfJobs; i++)
            {
                jobs[i] = rand.Next(20, 101);

            }

            // Write jobs to a file
            //Will create job.txt file in same directory as the this programs debuger
            using StreamWriter sw = new StreamWriter("job.txt");
            for (int i = 0; i < numOfJobs; i++)
            {

                sw.WriteLine("Job" + (i + 1));
                sw.WriteLine(jobs[i]);

            }

        }


        //This code is used for the while loop that is used to test 20 jobs
        //You have to use JobCreator to create the correct job.txt files
        static string[] GetJobTxtFileContentWithCounter(int counter, int outterCounter)
        {

            string currentJob = "job";

            currentJob += "[" + outterCounter.ToString() + "]" + "[" + counter.ToString() + "]" + ".txt";

            // Path to text File that will be read in 
            string[] jobText = System.IO.File.ReadAllLines(@"C:\\Users\\randy\\Documents\\Code\\CS4310\\project1\\project_1\\JobCreator\\bin\\Debug\\netcoreapp3.1\\" + currentJob);

            return jobText;
        }


        static string[] GetJobTxtFileContent()
        {

            // Path to text File that will be read in 
            string[] jobText = System.IO.File.ReadAllLines(@"job.txt");

            return jobText;
        }


        static int[] ParseStringArrayForBurstNums(string[] jobText)
        {
            int[] burstNum = new int[jobText.Length / 2];
            int count = 0;

            //Grab all integer values from the job.txt
            for (int i = 1; i < jobText.Length; i += 2)
            {
                burstNum[count] = Int32.Parse(jobText[i]);
                count++;

            }

            return burstNum;
        }

        static string[] ParseStringsArrayForJobNums(string[] jobText)
        {
            string[] jobsText = new string[jobText.Length / 2];
            int count = 0;

            // Grab all jobs text strings from job.txt
            for (int i = 0; i < jobText.Length; i += 2)
            {
                jobsText[count] = jobText[i];
                count++;

            }

            return jobsText;
        }

        static int[] RoundRobin(int[] jobs, string[] jobsList, int timeSlice)
        {
            int[] jobDoneTimes = new int[jobs.Length];
            int startTime;
            int EndTime = 0;
            int difference;
            Console.WriteLine("*************************** Round Robin Time Slice 2 ***************************");
            while (true)
            {
                bool isDone = true;

                for (int i = 0; i < jobs.Length; i++)
                {

                    if (jobs[i] > 0)
                    {
                        isDone = false;
                        if (jobs[i] > timeSlice)
                        {

                            jobs[i] -= timeSlice;
                            startTime = EndTime;
                            EndTime += timeSlice;

                            Console.WriteLine(jobsList[i] + "\tArrival Time: " + startTime + " \tDone Time: " + EndTime);

                        }
                        else
                        {
                            difference = timeSlice - jobs[i];
                            startTime = EndTime;

                            if (difference == 0)
                            {
                                EndTime += timeSlice;
                            }
                            else
                            {
                                EndTime += jobs[i];
                            }

                            jobs[i] = 0;
                            jobDoneTimes[i] = EndTime;

                            Console.WriteLine(jobsList[i] + "\tArrival Time: " + startTime + " \tDone Time: " + EndTime + "\t" + jobsList[i] + " Finished at: " + EndTime);

                        }

                    }
                }

                if (isDone)
                {
                    break;
                }

            }

            return jobDoneTimes;
        }

        static double CalculateAvgTurnAroundTime(int[] jobs)
        {
            double turnAroundTime = 0;

            // Find the average by adding all the done times of the jobs
            // and dividing it by the number of jobs
            for (int i = 0; i < jobs.Length; i++)
            {
                turnAroundTime += jobs[i];
            }


            return (turnAroundTime / jobs.Length);

        }


        static void Main()
        {
            //Declare Number of Jobs to create in job.txt
            int numOfJobs = 5;

            //TimeSlice for this algorithm
            int timeSlice = 2;


            /*
            //This code is used for the while loop that is used to test 20 jobs
            double[] turnAroundTimes = new double[20];
            double[] avergaeOfAverageTurnAroundTimes = new double[20];
            int outterCounter = 0;
            int counter = 0;
            double averageOfTurnAroundTimes = 0;
            double avergaeOfAverageTurnAroundTime = 0;

            while (outterCounter < 20)
            {
                // Reset values back to 0 for next set of data
                counter = 0;
                averageOfTurnAroundTimes = 0;
                //This code is used for the while loop that is used to test 20 jobs
                while (counter < 20)
                {
                */
                    //Create job.txt file with number of jobs based in passed in argument
                    //If you dont want to use it comment it out
                    //CreateJobTxtFile(numOfJobs);

                    //Get File content, You MUST specify the file location of job.txt here
                    //I left mine as an example
                    string[] jobText = GetJobTxtFileContent();

                    // This code is used for the while loop that is used to test 20 jobs
                    // If you want to use the while loop comment out the above GetJobTxtFileContent();
                    // And uncomment the below function call, You will also need to uncomment all other code used 
                    // for the while loop
                    //string[] jobText = GetJobTxtFileContentWithCounter(counter, outterCounter);

                    //Get Burst Times of each job
                    int[] jobsBurstTimes = ParseStringArrayForBurstNums(jobText);
                    string[] jobsList = ParseStringsArrayForJobNums(jobText);

                    int[] copyOfBurstTimes = jobsBurstTimes;

                    int[] jobDoneTime = RoundRobin(copyOfBurstTimes, jobsList, timeSlice);

                    //Calcualte Average Turn Around Time 
                    double turnAroundTime = CalculateAvgTurnAroundTime(jobDoneTime);

                    Console.WriteLine("Turn Around Time: " + turnAroundTime);

                    //This code is used for the while loop that is used to test 20 jobs
                    /*
                    //For finding the average
                    turnAroundTimes[counter] = turnAroundTime;
                    counter++;

                }// end of inner while loop 


                for (int i = 0; i < turnAroundTimes.Length; i++)
                {

                    Console.WriteLine(i + 1 + " turnAroundTime: " + turnAroundTimes[i]);
                    averageOfTurnAroundTimes += turnAroundTimes[i];


                }

                Console.WriteLine("Turn Around Time average: " + (averageOfTurnAroundTimes / 20));
                avergaeOfAverageTurnAroundTimes[outterCounter] = (averageOfTurnAroundTimes / 20);
                outterCounter++;

            }//End of outer while loop 

            for (int i = 0; i < avergaeOfAverageTurnAroundTimes.Length; i++)
            {

                Console.WriteLine(i + 1 + "  Average of Average TurnAround Times: " + avergaeOfAverageTurnAroundTimes[i]);
                avergaeOfAverageTurnAroundTime += avergaeOfAverageTurnAroundTimes[i];


            }

            Console.WriteLine("Turn Around Time Average of 20 Average Turnaround Times: " + (avergaeOfAverageTurnAroundTime / 20));

            */
        }

    }
}
