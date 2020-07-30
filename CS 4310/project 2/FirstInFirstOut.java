import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class FirstInFirstOut
{
	 private String referenceString;
     private int numOfPageFrames; 

     private int pageFaults = 0; 
     
     // set is used to look up values and for it use of unique values 
     // queue is used to manage the order of the page frame
     private  HashSet<String> setOfPages;
     private  Queue<String> queueOfPages = new LinkedList<>(); 
     
     public FirstInFirstOut(String numOfPageframesPar, String referenceStringPar)
     {        
         this.numOfPageFrames = Integer.parseInt(numOfPageframesPar);  
         this.referenceString = referenceStringPar; 
         setOfPages = new HashSet<String>(this.numOfPageFrames);
     }

     public String RunAlgo()
     {
    	  
    	 display();
    	 
    	 // Run Through the whole reference String
         for( int i = 0; i < this.referenceString.length(); i++ )
         {
        	 String currentPage = Character.toString(referenceString.charAt(i));
        	        	 
        	 System.out.print("\t\t" + currentPage + "\t");
        	
        	 // Check if the current set is less then the max size
             if (setOfPages.size() < numOfPageFrames)
             {
                 // if the currentPage is not in the set add it to it 
                 if (!setOfPages.contains(currentPage))
                 {
                	 // Add currentPage to set and queue
                     setOfPages.add(currentPage);
                     queueOfPages.add(currentPage);
                     
                     pageFaults++;
                    
                     System.out.print("\t* Page Fault Occured: " + currentPage + " added *\t\t\t");
                 }
                 else
                 {
                	 
                	 System.out.print("\t* No Page Fault Occured *\t\t\t");
                 }
                 
             }
             else
             {	 // Check if the currentPage is in the set
            	 // if not remove the head of the queue and add the currentPage
                 if( !setOfPages.contains(currentPage) )
                 {
                	 // Remove leading item from queue and set
                     String firstQueuePage = queueOfPages.peek();
                     queueOfPages.remove();
                     setOfPages.remove(firstQueuePage);
                     
                     // Add the current page to the queue and set
                     setOfPages.add(currentPage);
                     queueOfPages.add(currentPage);

                     pageFaults++; 
                     System.out.print("\t* Page Fault Occured: " + currentPage + " added, " + firstQueuePage + " removed *\t");
                   
                 }
                 else       
                 {
                	 System.out.print("\t* No Page Fault Occured *\t\t\t");
                 }
             }             
             System.out.print(queueOfPages + "\t");
             System.out.println();
             
         }
         
         System.out.println("\n\tTotal Page Faults: " + Integer.toString(pageFaults) + "\n");
         
         return Integer.toString(pageFaults); 
     }
     
     
     // Display current reference string and pageFrames size
     private void display()
     {
    	 System.out.println("\t**************************** First IN FIRST OUT ALGORITHM ****************************" ); 
    	 System.out.println("\tReference String: " + referenceString + "\t\tPage Frames: " + numOfPageFrames);
    	 System.out.println();
    	 
    	 System.out.println("\tCurrent Page Frame" + "\t\t\tPages Fault" + "\t\t\tPage Frame Content");
    	 System.out.println("\t_________________________________________________________________________________________");
    	 
    	 
    	 
     }
     
}
